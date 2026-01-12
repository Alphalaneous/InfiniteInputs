#include "LevelKeys.hpp"
#include "Geode/cocos/CCDirector.h"
#include "Geode/modify/Modify.hpp"

#include <Geode/binding/LevelEditorLayer.hpp>
#include <alphalaneous.alphas-ui-pack/include/touch/Touch.hpp>
#include "Geode/utils/cocos.hpp"
#include "alphalaneous.alphas-ui-pack/include/touch/TouchDispatcher.hpp"

#include <Geode/modify/GJBaseGameLayer.hpp>
#include <Geode/modify/CCEGLView.hpp>
#include <alphalaneous.alphas-ui-pack/include/nodes/scroll/AdvancedScrollDelegate.hpp>
#include <alphalaneous.alphas-ui-pack/include/nodes/scroll/ScrollDispatcher.hpp>
#include <scn/scan.h>

#include <unordered_map>
#include <vector>
#include <string_view>

using namespace geode::prelude;


#define ETOSTRING(k) enchantum::to_string(k)


static gd::vector<short> getGroupIDs(GameObject* obj) {
    gd::vector<short> res;

    if (obj->m_groups && obj->m_groups->at(0))
        for (auto i = 0; i < obj->m_groupCount; i++)
            res.push_back(obj->m_groups->at(i));
    return res;
}
static bool hasGroup(GameObject* obj, int group)
{
    for (const auto& g : getGroupIDs(obj))
    {
        if (g == group)
            return true;
    }
    return false;
}



using groupId = int;

struct MyClickDelegate : public CCNode, alpha::dispatcher::TouchDelegate {
    bool clickBegan(alpha::dispatcher::TouchEvent* touch) override;
	void clickEnded(alpha::dispatcher::TouchEvent* touch) override;
};

struct MyScrollDelegate : public CCNode, alpha::dispatcher::AdvancedScrollDelegate {
    void scroll(float x, float y) override;
};

class $modify(MyBaseLayer, GJBaseGameLayer)
{
    struct Fields {
        std::unordered_map<LevelKeys, groupId> upKeyMap;
        std::unordered_map<LevelKeys, groupId> downKeyMap;
        MyClickDelegate* touchDelegate = nullptr;
        MyScrollDelegate* scrollDelegate = nullptr;
        bool controlPressed = false;
        bool altPressed = false;
        bool shiftPressed = false;
        bool scheduledModifiedKeys = false;
        bool active = false;
        GJBaseGameLayer* layer = nullptr;
        int i = 0;

        //needs to be ccarray because moveObjects takes CCArray* and converting from vector to ccarray would be stupid
        CCArrayExt<GameObject*> cursorFollowObjects;

        /*SPECIAL ONLY ONE GROUP ID!!!*/
        int cursorFollowGroupId = -1;
        int wheelUpGroup = -1;
        int wheelDownGroup = -1;

        
        void clear() {
            upKeyMap.clear();
            downKeyMap.clear();
            if(touchDelegate) {
                CCTouchDispatcher::get()->removeDelegate(touchDelegate);
                touchDelegate = nullptr;
            }
            if(scrollDelegate) {
                alpha::dispatcher::ScrollDispatcher::get()->unregisterScroll(scrollDelegate);
                scrollDelegate = nullptr;
            }
            controlPressed = false;
            altPressed = false;
            shiftPressed = false;
            scheduledModifiedKeys = false;
            active = false;
            layer = nullptr;
            //no clear() in Ext
            cursorFollowObjects.inner()->removeAllObjects();
            cursorFollowGroupId = -1;
            wheelUpGroup = -1;
            wheelDownGroup = -1;
        }
        auto& getKeysMap(bool down) {
            return down ? downKeyMap : upKeyMap;
        }


        void addKeyBind(LevelKeys key, bool down, int groupId) {
            switch(key) {
                case LevelKeys::cursor: cursorFollowGroupId = groupId; return;
                case LevelKeys::wheelUp: wheelUpGroup = groupId; return;
                case LevelKeys::wheelDown: wheelDownGroup = groupId; return;
                default: getKeysMap(down).emplace(key, groupId);
            }
        }


        std::optional<groupId> getGroupId(LevelKeys k, bool down) {
            log::debug("FINDING: {}", ETOSTRING(k));
            if(k == LevelKeys::unknown) return std::nullopt;

            auto map = getKeysMap(down);
            auto it = map.find(k);
            if(it != map.end()) {
                log::debug("{} found in map", enchantum::to_string(k));
                return it->second;
            }

            switch(k) {
                case LevelKeys::cursor: return cursorFollowGroupId;
                case LevelKeys::wheelDown: return wheelDownGroup;
                case LevelKeys::wheelUp: return wheelUpGroup;
                default: return std::nullopt;
            }
        }

        void spawnGroupIfDefined(LevelKeys k, bool down) {
            if(auto group = getGroupId(k, down)) {
                log::info("KEY: {}, {}, GROUP: {}", enchantum::to_string(k), down ? "down" : "up", *group);
                layer->spawnGroup(*group, false, 0, {}, 0, 0);
                return;
            }
        }

        ~Fields() {
            if(touchDelegate) {
                CCTouchDispatcher::get()->removeDelegate(touchDelegate);
            }
            if(scrollDelegate) {
                alpha::dispatcher::ScrollDispatcher::get()->unregisterScroll(scrollDelegate);
            }
        }
    };

    $override
    bool init() {
        if (!GJBaseGameLayer::init()) return false;

        scheduleOnce(schedule_selector(MyBaseLayer::delayedInit), 0);
        return true;
    }

    void delayedInit(float)
    {
        if(m_isEditor) {
            schedule(schedule_selector(MyBaseLayer::editorActiveHandlerLoop), 0);
            return;
        }

        scheduleOnce(schedule_selector(MyBaseLayer::setupKeybinds_step0), 0);

        //start directly in playlayer
    }


    static std::vector<std::string_view> getAllTextsFromLabels(GJBaseGameLayer* pl) {
	    std::vector<std::string_view> texts;

	    for(const auto& obj : CCArrayExt<GameObject*>(pl->m_objects)) {
	    	if(obj->m_objectID != 914) continue;
	    	texts.emplace_back(static_cast<TextGameObject*>(obj)->m_text);
	    }
	    return texts;
    }

    void editorActiveHandlerLoop(float) {
        auto fields = m_fields.self();
        auto editor = reinterpret_cast<LevelEditorLayer*>(this);
        bool inPlaytest = m_playbackMode == PlaybackMode::Playing;

        if(!fields->active && inPlaytest) {
            fields->active = true;
            setupKeybinds_step0(0);
        }
        else if(fields->active && !inPlaytest) {
            fields->active = false;
            fields->clear();
            unschedule(schedule_selector(MyBaseLayer::updateLoop));
        }
    }

    void handleClick(alpha::dispatcher::TouchEvent* touch, bool down) {
        LevelKeys btn = AlphaMouseButtonToLevelKeys(touch->getButton());
        log::info("{} {}", enchantum::to_string(touch->getButton()), enchantum::to_string(btn));
        nh_handleKeypress(btn, down);
    }


    void updateLoop(float) {
        auto kb = CCDirector::get()->getKeyboardDispatcher();
        auto fields = m_fields.self();
        bool control = kb->getControlKeyPressed();
        if(control != fields->controlPressed) {
            fields->controlPressed = control;
            nh_handleKeypress(LevelKeys::leftCtrl, control);
        }
        bool shift = kb->getShiftKeyPressed();
        if(shift != fields->shiftPressed) {
            fields->shiftPressed = shift;
            nh_handleKeypress(LevelKeys::leftShift, shift);
        }
        bool alt = kb->getAltKeyPressed();
        if(alt != fields->altPressed) {
            fields->altPressed = alt;
            nh_handleKeypress(LevelKeys::leftAlt, alt);
        }


        for(const auto& o : m_fields->cursorFollowObjects) {
            auto mousepos = getMousePos();
            // Convert mouse to the same coordinate space where the object's position is defined
            auto targetPos = o->getParent() ? o->getParent()->convertToNodeSpace(mousepos) : mousepos;
            auto currentPos = o->getRealPosition();
            //log::info("{}", currentPos);
            auto delta = targetPos - currentPos;
            moveObject(o, delta.x, delta.y, true);

        }

    }


    void resetLevelVariables() {

        GJBaseGameLayer::resetLevelVariables();

        for(const auto& o : m_fields->cursorFollowObjects) {
            o->setLastPosition(o->getPosition());
        }
    }

    struct ParsedTextLabel {
        LevelKeys key;
        bool keyDown;
        int group;
    };

    std::optional<ParsedTextLabel> getTupleFromLabel(std::string_view t) {
        if(auto result = scn::scan<std::string, int, int>(t, "@{} {} = {}")) {
            auto values = result->values();
            if(auto enumval = keyLevelIdentifierToValue(std::get<0>(values)); enumval != LevelKeys::unknown) {
                return ParsedTextLabel{enumval, std::get<1>(values) == 1, std::get<2>(values)};
            }
        }
        if(auto groupOnlyResult = scn::scan<std::string, int>(t, "@{} = {}")) {
            auto values = groupOnlyResult->values();
            if(auto enumval = keyLevelIdentifierToValue(std::get<0>(values)); enumval != LevelKeys::unknown) {
                return ParsedTextLabel{enumval, /*when no key*/0, std::get<1>(values)};
            }
        }
        return std::nullopt;
    }

    void setupText(std::string_view t)
    {
        log::debug("parsing {}", t);
        if(t.front() != '@') return;
        auto parsed_opt = getTupleFromLabel(t);
        if(!parsed_opt) {
            return;
        }
        auto& parsed = *parsed_opt;
        m_fields->addKeyBind(parsed.key, parsed.keyDown, parsed.group);
    }

    void setupCursorGroup(int cursorGroupId) {
        log::info("SETTING UP CURSOR GROUP {}", cursorGroupId);
        m_fields->cursorFollowGroupId = cursorGroupId;
        m_fields->cursorFollowObjects.inner()->removeAllObjects();
        for(const auto& o : CCArrayExt<GameObject*>(m_objects)) {
            if(hasGroup(o, cursorGroupId)) {
                m_fields->cursorFollowObjects.push_back(o);
            }
        }
    }

    //true if correctly registered atleast one keybind
    bool setupTextLabelKeys_step1() {
        auto fields = m_fields.self();
        auto texts = getAllTextsFromLabels(this);
        std::ranges::for_each(texts, [this](auto& t){setupText(t); });

        log::info("Added {} down keys", fields->downKeyMap.size());
        log::info("Added {} up keys", fields->upKeyMap.size());
        return !fields->downKeyMap.empty() || !fields->upKeyMap.empty(); 
    }

    bool isActive() {
        return m_fields->active;
    }

    void setupKeybinds_step0(float) {
        if(!setupTextLabelKeys_step1()) {
            log::error("not parsed any labels");
            return;
        }
        auto fields = m_fields.self();
        fields->layer = this;

        if(!fields->touchDelegate) {
            fields->touchDelegate = new MyClickDelegate;
            fields->touchDelegate->setID("iandyhd.keyboardsupport/touch-delegate");
            fields->touchDelegate->setContentSize(this->getContentSize());
            addChild(fields->touchDelegate, INT_MAX);
            CCTouchDispatcher::get()->addTargetedDelegate(fields->touchDelegate, INT_MIN, false);
        }

        if(!fields->scrollDelegate) {
            fields->scrollDelegate = new MyScrollDelegate;
            fields->scrollDelegate->setID("iandyhd.keyboardsupport/scroll-delegate");
            fields->scrollDelegate->setContentSize(this->getContentSize());
            addChild(fields->scrollDelegate, INT_MAX);
            alpha::dispatcher::ScrollDispatcher::get()->registerScroll(fields->scrollDelegate);
        }

        if(!fields->scheduledModifiedKeys) {
            schedule(schedule_selector(MyBaseLayer::updateLoop), 0);
            fields->scheduledModifiedKeys = true;
        }

        if(fields->cursorFollowGroupId != -1) {
            setupCursorGroup(fields->cursorFollowGroupId);
        }
        fields->active = true;

        log::info("{} {} {}", fields->cursorFollowGroupId, fields->wheelDownGroup, fields->wheelUpGroup);
    }

    void handleScroll(float x, float y) {
        if(y != 0) {
            //scrolling up is minus apparently
            m_fields->spawnGroupIfDefined(y < 0 ? LevelKeys::wheelUp : LevelKeys::wheelDown, /*this is ignored*/ false);
        }
    }


    void nh_handleKeypress(LevelKeys key, bool down) {
        log::debug("Handle key press");
        m_fields->spawnGroupIfDefined(key, down);
    }
};



void CROSSPLATFORM_ON_KEY_CALLBACK(LevelKeys key, bool down)
{
    if(auto layer = reinterpret_cast<MyBaseLayer*>(GJBaseGameLayer::get()); layer && layer->isActive()) {
        layer->nh_handleKeypress(key, down);
    }
}

bool MyClickDelegate::clickBegan(alpha::dispatcher::TouchEvent *touch) {
    log::debug("click began {}", enchantum::to_string(touch->getButton()));
    reinterpret_cast<MyBaseLayer*>(GJBaseGameLayer::get())->handleClick(touch, true);
    return true;
}

void MyClickDelegate::clickEnded(alpha::dispatcher::TouchEvent* touch) {
    log::debug("click ended {}", enchantum::to_string(touch->getButton()));
    reinterpret_cast<MyBaseLayer*>(GJBaseGameLayer::get())->handleClick(touch, false);
}

void MyScrollDelegate::scroll(float x, float y) {
    log::info("scroll {}, {}", x, y);
    reinterpret_cast<MyBaseLayer*>(GJBaseGameLayer::get())->handleScroll(x, y);

}
#include <Geode/Geode.hpp>
#include <enchantum/enchantum.hpp>
#include <string_view>
#include "TextGameObject.hpp"
#include "../TextParsing.hpp"
#include "LevelKeys.hpp"

using namespace geode::prelude;

void MyTextGameObject::setupInputTrigger() {
    auto view = std::string_view(m_text);
    if (!view.starts_with("inf_inp:")) return;

    // treat like trigger :3 (aka move out of batch node and not allow color to be set normally)
    m_addToNodeContainer = true;
    m_detailColor = nullptr;
    m_isTrigger = true;

    for (auto child : getChildrenExt()) {
        child->setVisible(false);
    }

    if (LevelEditorLayer::get()) {
        auto parsed_opt = getTupleFromLabel(m_text);
        std::string labelStr = "";

        if (parsed_opt) {
            auto parsed = *parsed_opt;
            if (parsed.key != LevelKeys::editorTab) {
                labelStr = utils::numToString(parsed.group);
            }
        }

        auto groupLabel = CCLabelBMFont::create(labelStr.c_str(), "bigFont.fnt");
        groupLabel->setScale(0.5f);
        groupLabel->setZOrder(1);

        addChild(groupLabel);

        auto spr = CCSprite::create("input_trigger.png"_spr);

        setContentSize(spr->getContentSize());
        m_width = getContentWidth();
        m_height = getContentHeight();
        updateOrientedBox();

        spr->setPosition(getContentSize() * 0.5f);
        groupLabel->setPosition({getContentWidth() * 0.5f, 10.5f});

        addChild(spr);

        spr->setColor(getColor());
    }
}

void MyTextGameObject::customObjectSetup(gd::vector<gd::string>& p0, gd::vector<void*>& p1) {
    TextGameObject::customObjectSetup(p0, p1);
    setupInputTrigger();
}

void MyTextGameObject::updateTextObject(gd::string p0, bool p1) {
    TextGameObject::updateTextObject(p0, p1);
    setupInputTrigger();
}
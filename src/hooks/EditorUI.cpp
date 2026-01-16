// #include "EditorUI.hpp"
// #include <Geode/binding/CreateMenuItem.hpp>
// #include <alphalaneous.editortab_api/include/EditorTabs.hpp>
// #include <Geode/Geode.hpp>

// using namespace geode::prelude;

// constexpr int getRandomObjectId = 53246;

// bool MyEditorUI::init(LevelEditorLayer* editor)
// {
//     if(!EditorUI::init(editor)) return false;

//     log::info("editor ui init");
//         EditorTabs::addTab(this /*The EditorUI*/, TabType::BUILD, "rawr"_spr, [](EditorUI* ui, CCMenuItemToggler* toggler) -> CCNode* { //create the tab
//         auto arr = CCArray::create();
//         auto trigger = ui->getCreateBtn(1, 4);
//         trigger->m_objectID = 53246;
//         trigger->setID("mytrigger");
//         arr->addObject(trigger);
//         CCLabelBMFont* textLabelOn = CCLabelBMFont::create("uwu", "bigFont.fnt");
//         textLabelOn->setScale(0.4f);
//         CCLabelBMFont* textLabelOff = CCLabelBMFont::create("owo", "bigFont.fnt");
//         textLabelOff->setScale(0.4f);
//         EditorTabUtils::setTabIcons(toggler, textLabelOn, textLabelOff);
//         log::info("created tab i guess");
//         return EditorTabUtils::createEditButtonBar(arr, ui);
        
//     }, [](EditorUI*, bool state, CCNode*) { //toggled the tab (activates on every tab click)
//         log::info("{}", state);
//     });

//     return true;

// }

// GameObject* MyEditorUI::createObject(int objectID, CCPoint position)
// {
//     log::info("{} {}", objectID, position);
//     if(objectID == 53246)
//     {
//         return EditorUI::createObject(1, position);
//     }
//     return EditorUI::createObject(objectID, position);

// }

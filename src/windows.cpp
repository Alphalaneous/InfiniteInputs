
#include <Geode/Geode.hpp>

#if defined(GEODE_IS_WINDOWS)
#include "LevelKeys.hpp"
#include <Geode/modify/CCEGLView.hpp>


extern void CROSSPLATFORM_ON_KEY_CALLBACK(LevelKeys key, bool down);



//for the mod reviewer reading this that will say that this could be done only in UILayer hooks:
//Know what? You're actually right, UILayer::handleKeyPress works great
//The problem ofcourse is that I assumed custom keybinds was a good mod and wouldn't fuck things up there.
//It swallows jump touches for no reason AND it sends the wrong keys for everything else.
//So no, I won't be using UILayer hooks even tho I really wanted to, that said I hope custom keybinds gets deleted one day :)

class $modify(cocos2d::CCEGLView)
{
    //action == 0, up
    //action == 1, down
    //action == 2, hold
    void onGLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
        CCEGLView::onGLFWKeyCallback(window, key, scancode, action, mods);
        if(action >= 2) return;
        geode::log::debug("key: {}, scancode: {}, action; {}, mods: {}", key, scancode, action, mods);

        CROSSPLATFORM_ON_KEY_CALLBACK(glfwKeyToLevelKey(key), action == 1);

	}
};


#endif
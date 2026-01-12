#include <cocos2d.h>
#include <alphalaneous.alphas-ui-pack/include/touch/Touch.hpp>
#include "Geode/cocos/robtop/glfw/glfw3.h"
#include <enchantum/enchantum.hpp>
using namespace cocos2d;

enum class LevelKeys {
    unknown = -1,
    f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12,
    KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0,
    q,w,e,r,t,z,u,i,o,p,
    a,s,d,f,g,h,j,k,l,
    y,x,c,v,b,n,m,
    enter,
    space,
    leftCtrl,
    leftShift,
    leftAlt,

    leftMouse,
    rightMouse,
    middleMouse,
    mouse3,
    mouse4,

    wheelUp,
    wheelDown,

    cursor
};


inline LevelKeys glfwKeyToLevelKey(int glfwKey) {
    switch (glfwKey) {
        // Function keys
        case GLFW_KEY_F1:  return LevelKeys::f1;
        case GLFW_KEY_F2:  return LevelKeys::f2;
        case GLFW_KEY_F3:  return LevelKeys::f3;
        case GLFW_KEY_F4:  return LevelKeys::f4;
        case GLFW_KEY_F5:  return LevelKeys::f5;
        case GLFW_KEY_F6:  return LevelKeys::f6;
        case GLFW_KEY_F7:  return LevelKeys::f7;
        case GLFW_KEY_F8:  return LevelKeys::f8;
        case GLFW_KEY_F9:  return LevelKeys::f9;
        case GLFW_KEY_F10: return LevelKeys::f10;
        case GLFW_KEY_F11: return LevelKeys::f11;
        case GLFW_KEY_F12: return LevelKeys::f12;

        // Number keys
        case GLFW_KEY_1: return LevelKeys::KEY_1;
        case GLFW_KEY_2: return LevelKeys::KEY_2;
        case GLFW_KEY_3: return LevelKeys::KEY_3;
        case GLFW_KEY_4: return LevelKeys::KEY_4;
        case GLFW_KEY_5: return LevelKeys::KEY_5;
        case GLFW_KEY_6: return LevelKeys::KEY_6;
        case GLFW_KEY_7: return LevelKeys::KEY_7;
        case GLFW_KEY_8: return LevelKeys::KEY_8;
        case GLFW_KEY_9: return LevelKeys::KEY_9;
        case GLFW_KEY_0: return LevelKeys::KEY_0;

        // Letter keys
        case GLFW_KEY_Q: return LevelKeys::q;
        case GLFW_KEY_W: return LevelKeys::w;
        case GLFW_KEY_E: return LevelKeys::e;
        case GLFW_KEY_R: return LevelKeys::r;
        case GLFW_KEY_T: return LevelKeys::t;
        case GLFW_KEY_Z: return LevelKeys::z;
        case GLFW_KEY_U: return LevelKeys::u;
        case GLFW_KEY_I: return LevelKeys::i;
        case GLFW_KEY_O: return LevelKeys::o;
        case GLFW_KEY_P: return LevelKeys::p;

        case GLFW_KEY_A: return LevelKeys::a;
        case GLFW_KEY_S: return LevelKeys::s;
        case GLFW_KEY_D: return LevelKeys::d;
        case GLFW_KEY_F: return LevelKeys::f;
        case GLFW_KEY_G: return LevelKeys::g;
        case GLFW_KEY_H: return LevelKeys::h;
        case GLFW_KEY_J: return LevelKeys::j;
        case GLFW_KEY_K: return LevelKeys::k;
        case GLFW_KEY_L: return LevelKeys::l;

        case GLFW_KEY_Y: return LevelKeys::y;
        case GLFW_KEY_X: return LevelKeys::x;
        case GLFW_KEY_C: return LevelKeys::c;
        case GLFW_KEY_V: return LevelKeys::v;
        case GLFW_KEY_B: return LevelKeys::b;
        case GLFW_KEY_N: return LevelKeys::n;
        case GLFW_KEY_M: return LevelKeys::m;

        // Special keys
        case GLFW_KEY_ENTER:        return LevelKeys::enter;
        case GLFW_KEY_SPACE:        return LevelKeys::space;
        case GLFW_KEY_LEFT_CONTROL: return LevelKeys::leftCtrl;
        case GLFW_KEY_LEFT_SHIFT:   return LevelKeys::leftShift;
        case GLFW_KEY_LEFT_ALT:     return LevelKeys::leftAlt;

        default: return LevelKeys::unknown;
    }
}

inline std::string_view fixKeyName(std::string_view name) {
    if (name.starts_with("KEY_")) [[unlikely]] {
        return name.substr(4);
    }
    return name;     
}

struct LevelKeyBinding
{
    enumKeyCodes key;
    int groupId;
};


inline enumKeyCodes LevelKeyToCocosKeyCode(LevelKeys key) {
    switch (key) {
        case LevelKeys::f1: return KEY_F1;
        case LevelKeys::f2: return KEY_F2;
        case LevelKeys::f3: return KEY_F3;
        case LevelKeys::f4: return KEY_F4;
        case LevelKeys::f5: return KEY_F5;
        case LevelKeys::f6: return KEY_F6;
        case LevelKeys::f7: return KEY_F7;
        case LevelKeys::f8: return KEY_F8;
        case LevelKeys::f9: return KEY_F9;
        case LevelKeys::f10: return KEY_F10;
        case LevelKeys::f11: return KEY_F11;
        case LevelKeys::f12: return KEY_F12;
        case LevelKeys::KEY_1: return KEY_One;
        case LevelKeys::KEY_2: return KEY_Two;
        case LevelKeys::KEY_3: return KEY_Three;
        case LevelKeys::KEY_4: return KEY_Four;
        case LevelKeys::KEY_5: return KEY_Five;
        case LevelKeys::KEY_6: return KEY_Six;
        case LevelKeys::KEY_7: return KEY_Seven;
        case LevelKeys::KEY_8: return KEY_Eight;
        case LevelKeys::KEY_9: return KEY_Nine;
        case LevelKeys::KEY_0: return KEY_Zero;
        case LevelKeys::q: return KEY_Q;
        case LevelKeys::w: return KEY_W;
        case LevelKeys::e: return KEY_E;
        case LevelKeys::r: return KEY_R;
        case LevelKeys::t: return KEY_T;
        case LevelKeys::z: return KEY_Z;
        case LevelKeys::u: return KEY_U;
        case LevelKeys::i: return KEY_I;
        case LevelKeys::o: return KEY_O;
        case LevelKeys::p: return KEY_P;
        case LevelKeys::a: return KEY_A;
        case LevelKeys::s: return KEY_S;
        case LevelKeys::d: return KEY_D;
        case LevelKeys::f: return KEY_F;
        case LevelKeys::g: return KEY_G;
        case LevelKeys::h: return KEY_H;
        case LevelKeys::j: return KEY_J;
        case LevelKeys::k: return KEY_K;
        case LevelKeys::l: return KEY_L;
        case LevelKeys::y: return KEY_Y;
        case LevelKeys::x: return KEY_X;
        case LevelKeys::c: return KEY_C;
        case LevelKeys::v: return KEY_V;
        case LevelKeys::b: return KEY_B;
        case LevelKeys::n: return KEY_N;
        case LevelKeys::m: return KEY_M;
        case LevelKeys::space: return KEY_Space;
        case LevelKeys::leftCtrl: return KEY_LeftControl;
        case LevelKeys::leftShift: return KEY_LeftShift;
        case LevelKeys::leftAlt: return KEY_LeftMenu;
        default: return KEY_Unknown;
    }
}

inline LevelKeys AlphaMouseButtonToLevelKeys(alpha::dispatcher::MouseButton button) {
    switch(button) {

    case alpha::dispatcher::MouseButton::LEFT: return LevelKeys::leftMouse;
    case alpha::dispatcher::MouseButton::MIDDLE: return LevelKeys::middleMouse;
    case alpha::dispatcher::MouseButton::RIGHT: return LevelKeys::rightMouse;
    case alpha::dispatcher::MouseButton::BUTTON3: return LevelKeys::mouse3;
    case alpha::dispatcher::MouseButton::BUTTON4: return LevelKeys::mouse4;
    case alpha::dispatcher::MouseButton::HOVER: return LevelKeys::unknown;
    default: return LevelKeys::unknown;
    }
}

inline LevelKeys keyLevelIdentifierToValue(std::string_view levelkeyname) {
    for(const auto& [keyVal, originalKeyName] : enchantum::entries_generator<LevelKeys>) {
        auto keyName = fixKeyName(originalKeyName);
        if(keyName == levelkeyname) {
            return keyVal;
        }
    }
    return LevelKeys::unknown;
}

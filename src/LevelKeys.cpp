#include "LevelKeys.hpp"
#include "Geode/cocos/robtop/glfw/glfw3.h"
#include "Geode/cocos/robtop/keyboard_dispatcher/CCKeyboardDelegate.h"
#include <enchantum/enchantum.hpp>

LevelKeys glfwKeyToLevelKey(int glfwKey) {
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

        // Extra keys
        case GLFW_KEY_MINUS: return LevelKeys::minus;
        case GLFW_KEY_EQUAL: return LevelKeys::equal;
        case GLFW_KEY_LEFT_BRACKET: return LevelKeys::leftBracket;
        case GLFW_KEY_RIGHT_BRACKET: return LevelKeys::rightBracket;
        case GLFW_KEY_SEMICOLON: return LevelKeys::semicolon;
        case GLFW_KEY_APOSTROPHE: return LevelKeys::apostrophe;
        case GLFW_KEY_COMMA: return LevelKeys::comma;
        case GLFW_KEY_PERIOD: return LevelKeys::period;
        case GLFW_KEY_SLASH: return LevelKeys::forwardSlash;
        case GLFW_KEY_BACKSLASH: return LevelKeys::backSlash;
        case GLFW_KEY_LEFT: return LevelKeys::arrowLeft;
        case GLFW_KEY_RIGHT: return LevelKeys::arrowRight;
        case GLFW_KEY_UP: return LevelKeys::arrowUp;
        case GLFW_KEY_DOWN: return LevelKeys::arrowDown;
        case GLFW_KEY_DELETE: return LevelKeys::del;
        case GLFW_KEY_END: return LevelKeys::end;
        case GLFW_KEY_PAGE_UP: return LevelKeys::pageUp;
        case GLFW_KEY_PAGE_DOWN: return LevelKeys::pageDown;
        case GLFW_KEY_TAB: return LevelKeys::tab;
        case GLFW_KEY_CAPS_LOCK: return LevelKeys::capsLock;
        case GLFW_KEY_BACKSPACE: return LevelKeys::backspace;

        // Special keys
        case GLFW_KEY_ENTER:        return LevelKeys::enter;
        case GLFW_KEY_SPACE:        return LevelKeys::space;
        case GLFW_KEY_LEFT_CONTROL: return LevelKeys::leftCtrl;
        case GLFW_KEY_LEFT_SHIFT:   return LevelKeys::leftShift;
        case GLFW_KEY_LEFT_ALT:     return LevelKeys::leftAlt;

        default: return LevelKeys::unknown;
    }
}

LevelKeys vkKeyToLevelKey(int vkKey) {
    switch (vkKey) {
        // Function keys
        case VK_F1:  return LevelKeys::f1;
        case VK_F2:  return LevelKeys::f2;
        case VK_F3:  return LevelKeys::f3;
        case VK_F4:  return LevelKeys::f4;
        case VK_F5:  return LevelKeys::f5;
        case VK_F6:  return LevelKeys::f6;
        case VK_F7:  return LevelKeys::f7;
        case VK_F8:  return LevelKeys::f8;
        case VK_F9:  return LevelKeys::f9;
        case VK_F10: return LevelKeys::f10;
        case VK_F11: return LevelKeys::f11;
        case VK_F12: return LevelKeys::f12;

        // Number keys
        case '1': return LevelKeys::KEY_1;
        case '2': return LevelKeys::KEY_2;
        case '3': return LevelKeys::KEY_3;
        case '4': return LevelKeys::KEY_4;
        case '5': return LevelKeys::KEY_5;
        case '6': return LevelKeys::KEY_6;
        case '7': return LevelKeys::KEY_7;
        case '8': return LevelKeys::KEY_8;
        case '9': return LevelKeys::KEY_9;
        case '0': return LevelKeys::KEY_0;

        // Letter keys
        case 'Q': return LevelKeys::q;
        case 'W': return LevelKeys::w;
        case 'E': return LevelKeys::e;
        case 'R': return LevelKeys::r;
        case 'T': return LevelKeys::t;
        case 'Y': return LevelKeys::y;
        case 'U': return LevelKeys::u;
        case 'I': return LevelKeys::i;
        case 'O': return LevelKeys::o;
        case 'P': return LevelKeys::p;

        case 'A': return LevelKeys::a;
        case 'S': return LevelKeys::s;
        case 'D': return LevelKeys::d;
        case 'F': return LevelKeys::f;
        case 'G': return LevelKeys::g;
        case 'H': return LevelKeys::h;
        case 'J': return LevelKeys::j;
        case 'K': return LevelKeys::k;
        case 'L': return LevelKeys::l;

        case 'Z': return LevelKeys::z;
        case 'X': return LevelKeys::x;
        case 'C': return LevelKeys::c;
        case 'V': return LevelKeys::v;
        case 'B': return LevelKeys::b;
        case 'N': return LevelKeys::n;
        case 'M': return LevelKeys::m;

        // Extra keys
        case VK_OEM_MINUS: return LevelKeys::minus;
        case VK_OEM_PLUS: return LevelKeys::equal;
        case VK_OEM_4: return LevelKeys::leftBracket;
        case VK_OEM_6: return LevelKeys::rightBracket;
        case VK_OEM_1: return LevelKeys::semicolon;
        case VK_OEM_7: return LevelKeys::apostrophe;
        case VK_OEM_COMMA: return LevelKeys::comma;
        case VK_OEM_PERIOD: return LevelKeys::period;
        case VK_OEM_2: return LevelKeys::forwardSlash;
        case VK_OEM_3: return LevelKeys::grave;
        case VK_OEM_5: return LevelKeys::backSlash;
        case VK_LEFT: return LevelKeys::arrowLeft;
        case VK_RIGHT: return LevelKeys::arrowRight;
        case VK_UP: return LevelKeys::arrowUp;
        case VK_DOWN: return LevelKeys::arrowDown;
        case VK_DELETE: return LevelKeys::del;
        case VK_END: return LevelKeys::end;
        case VK_PRIOR: return LevelKeys::pageUp;
        case VK_NEXT: return LevelKeys::pageDown;
        case VK_TAB: return LevelKeys::tab;
        case VK_CAPITAL: return LevelKeys::capsLock;
        case VK_BACK: return LevelKeys::backspace;

        // Special keys
        case VK_RETURN:        return LevelKeys::enter;
        case VK_SPACE:        return LevelKeys::space;
        case VK_LCONTROL: return LevelKeys::leftCtrl;
        case VK_RCONTROL: return LevelKeys::rightCtrl;
        case VK_LSHIFT:   return LevelKeys::leftShift;
        case VK_RSHIFT:   return LevelKeys::rightShift;
        case VK_LMENU:     return LevelKeys::leftAlt;
        case VK_RMENU:     return LevelKeys::rightAlt;

        default: return LevelKeys::unknown;
    }
}

std::string_view fixKeyName(std::string_view name) {
    if (name.starts_with("KEY_")) [[unlikely]] {
        return name.substr(4);
    }
    return name;     
}

enumKeyCodes LevelKeyToCocosKeyCode(LevelKeys key) {
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
        case LevelKeys::minus: return KEY_OEMMinus;
        case LevelKeys::equal: return KEY_OEMEqual;
        case LevelKeys::leftBracket: return KEY_LeftBracket;
        case LevelKeys::rightBracket: return KEY_RightBracket;
        case LevelKeys::forwardSlash: return KEY_Slash;
        case LevelKeys::backSlash: return KEY_Backslash;
        case LevelKeys::semicolon: return KEY_Semicolon;
        case LevelKeys::apostrophe: return KEY_Apostrophe;
        case LevelKeys::comma: return KEY_OEMComma;
        case LevelKeys::period: return KEY_OEMPeriod;
        case LevelKeys::arrowLeft: return KEY_Left;
        case LevelKeys::arrowRight: return KEY_Right;
        case LevelKeys::arrowUp: return KEY_Up;
        case LevelKeys::arrowDown: return KEY_Down;
        case LevelKeys::del: return KEY_Delete;
        case LevelKeys::end: return KEY_End;
        case LevelKeys::grave: return KEY_GraveAccent;
        case LevelKeys::pageUp: return KEY_PageUp;
        case LevelKeys::pageDown: return KEY_PageDown;
        case LevelKeys::tab: return KEY_Tab;
        case LevelKeys::capsLock: return KEY_CapsLock;
        case LevelKeys::backspace: return KEY_Backspace;
        case LevelKeys::space: return KEY_Space;
        case LevelKeys::leftCtrl: return KEY_LeftControl;
        case LevelKeys::leftShift: return KEY_LeftShift;
        case LevelKeys::leftAlt: return KEY_LeftMenu;
        case LevelKeys::rightCtrl: return KEY_RightContol;
        case LevelKeys::rightShift: return KEY_RightShift;
        case LevelKeys::rightAlt: return KEY_RightMenu;
        default: return KEY_Unknown;
    }
}

LevelKeys AlphaMouseButtonToLevelKeys(alpha::dispatcher::MouseButton button) {
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

LevelKeys keyLevelIdentifierToValue(std::string_view levelkeyname) {
    for(const auto& [keyVal, originalKeyName] : enchantum::entries_generator<LevelKeys>) {
        auto keyName = fixKeyName(originalKeyName);
        if(keyName == levelkeyname) {
            return keyVal;
        }
    }
    return LevelKeys::unknown;
}
#ifdef __APPLE__
#define CommentType CommentTypeDummy
#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>
#undef CommentType
#endif

#include <Geode/Geode.hpp>

#if defined(GEODE_IS_MACOS)
#include "LevelKeys.hpp"
#include <Geode/cocos/platform/mac/CCEventDispatcher.h>
#import <Geode/cocos/platform/mac/EAGLView.h>
#import <objc/runtime.h>

using namespace geode::prelude;

using EventType = void(*)(EAGLView*, SEL, NSEvent*);

extern void CROSSPLATFORM_ON_KEY_CALLBACK(LevelKeys key, bool down);

namespace {
    // macOS virtual key codes mapping
    LevelKeys convertMacKey(int keycode) {
        switch (keycode) {
            case 0: return LevelKeys::a;
            case 1: return LevelKeys::s;
            case 2: return LevelKeys::d;
            case 3: return LevelKeys::f;
            case 4: return LevelKeys::h;
            case 5: return LevelKeys::g;
            case 6: return LevelKeys::z;
            case 7: return LevelKeys::x;
            case 8: return LevelKeys::c;
            case 9: return LevelKeys::v;
            case 11: return LevelKeys::b;
            case 12: return LevelKeys::q;
            case 13: return LevelKeys::w;
            case 14: return LevelKeys::e;
            case 15: return LevelKeys::r;
            case 16: return LevelKeys::y;
            case 17: return LevelKeys::t;
            case 18: return LevelKeys::KEY_1;
            case 19: return LevelKeys::KEY_2;
            case 20: return LevelKeys::KEY_3;
            case 21: return LevelKeys::KEY_4;
            case 22: return LevelKeys::KEY_6;
            case 23: return LevelKeys::KEY_5;
            case 25: return LevelKeys::KEY_9;
            case 26: return LevelKeys::KEY_7;
            case 28: return LevelKeys::KEY_8;
            case 29: return LevelKeys::KEY_0;
            case 31: return LevelKeys::o;
            case 32: return LevelKeys::u;
            case 34: return LevelKeys::i;
            case 35: return LevelKeys::p;
            case 36: return LevelKeys::enter;
            case 37: return LevelKeys::l;
            case 38: return LevelKeys::j;
            case 40: return LevelKeys::k;
            case 45: return LevelKeys::n;
            case 46: return LevelKeys::m;
            case 49: return LevelKeys::space;
            case 56: return LevelKeys::leftShift;
            case 58: return LevelKeys::leftAlt;
            case 59: return LevelKeys::leftCtrl;
            case 96: return LevelKeys::f5;
            case 97: return LevelKeys::f6;
            case 98: return LevelKeys::f7;
            case 99: return LevelKeys::f3;
            case 100: return LevelKeys::f8;
            case 101: return LevelKeys::f9;
            case 103: return LevelKeys::f11;
            case 109: return LevelKeys::f10;
            case 111: return LevelKeys::f12;
            case 118: return LevelKeys::f4;
            case 120: return LevelKeys::f2;
            case 122: return LevelKeys::f1;
            default: return LevelKeys::unknown;
        }
    };

    static EventType originalKeyDown;
    static EventType originalKeyUp;

    void keyDownHook(EAGLView* self, SEL _cmd, NSEvent* event) {
        originalKeyDown(self, _cmd, event);

        if (event.isARepeat) return;
        auto key = convertMacKey(event.keyCode);
        
        Loader::get()->queueInMainThread([=]() {
            CROSSPLATFORM_ON_KEY_CALLBACK(key, true);
        });
    }

    void keyUpHook(EAGLView* self, SEL _cmd, NSEvent* event) {
        originalKeyUp(self, _cmd, event);

        if (event.isARepeat) return;
        auto key = convertMacKey(event.keyCode);
        
        Loader::get()->queueInMainThread([=]() {
            CROSSPLATFORM_ON_KEY_CALLBACK(key, false);
        });
    }

    #define OBJC_SWIZZLE(method, swizzle, original) do { \
        auto method##Method = class_getInstanceMethod(class_, @selector(method:)); \
        original = reinterpret_cast<decltype(original)>(method_getImplementation(method##Method)); \
        method_setImplementation(method##Method, reinterpret_cast<IMP>(swizzle)); \
    } while(0)

    $execute {
        Class class_ = NSClassFromString(@"EAGLView");
        OBJC_SWIZZLE(keyDown, keyDownHook, originalKeyDown);
        OBJC_SWIZZLE(keyUp, keyUpHook, originalKeyUp);
    }
}

#endif
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
using EventType = void(*)(id, SEL, NSEvent*);

extern void CROSSPLATFORM_ON_KEY_CALLBACK(LevelKeys key, bool down);

namespace {
    LevelKeys convertMacKey(unsigned short keyCode) {
        // macOS virtual key codes
        switch(keyCode) {
            // Function keys
            case 0x7A: return LevelKeys::f1;
            case 0x78: return LevelKeys::f2;
            case 0x63: return LevelKeys::f3;
            case 0x76: return LevelKeys::f4;
            case 0x60: return LevelKeys::f5;
            case 0x61: return LevelKeys::f6;
            case 0x62: return LevelKeys::f7;
            case 0x64: return LevelKeys::f8;
            case 0x65: return LevelKeys::f9;
            case 0x6D: return LevelKeys::f10;
            case 0x67: return LevelKeys::f11;
            case 0x6F: return LevelKeys::f12;

            // Number keys (top row)
            case 0x12: return LevelKeys::KEY_1;
            case 0x13: return LevelKeys::KEY_2;
            case 0x14: return LevelKeys::KEY_3;
            case 0x15: return LevelKeys::KEY_4;
            case 0x17: return LevelKeys::KEY_5;
            case 0x16: return LevelKeys::KEY_6;
            case 0x1A: return LevelKeys::KEY_7;
            case 0x1C: return LevelKeys::KEY_8;
            case 0x19: return LevelKeys::KEY_9;
            case 0x1D: return LevelKeys::KEY_0;

            // Letter keys - QWERTY layout
            case 0x0C: return LevelKeys::q;
            case 0x0D: return LevelKeys::w;
            case 0x0E: return LevelKeys::e;
            case 0x0F: return LevelKeys::r;
            case 0x11: return LevelKeys::t;
            case 0x06: return LevelKeys::z;
            case 0x20: return LevelKeys::u;
            case 0x22: return LevelKeys::i;
            case 0x1F: return LevelKeys::o;
            case 0x23: return LevelKeys::p;

            case 0x00: return LevelKeys::a;
            case 0x01: return LevelKeys::s;
            case 0x02: return LevelKeys::d;
            case 0x03: return LevelKeys::f;
            case 0x05: return LevelKeys::g;
            case 0x04: return LevelKeys::h;
            case 0x26: return LevelKeys::j;
            case 0x28: return LevelKeys::k;
            case 0x25: return LevelKeys::l;

            case 0x10: return LevelKeys::y;
            case 0x07: return LevelKeys::x;
            case 0x08: return LevelKeys::c;
            case 0x09: return LevelKeys::v;
            case 0x0B: return LevelKeys::b;
            case 0x2D: return LevelKeys::n;
            case 0x2E: return LevelKeys::m;

            // Special keys
            case 0x24: return LevelKeys::enter;     // Return
            case 0x4C: return LevelKeys::enter;     // Enter (numpad)
            case 0x31: return LevelKeys::space;
            case 0x3B: return LevelKeys::leftCtrl;  // Left Control
            case 0x38: return LevelKeys::leftShift; // Left Shift
            case 0x3A: return LevelKeys::leftAlt;   // Left Option/Alt

            default: return LevelKeys::unknown;
        }
    }
}

@interface MacKeyboardEvent : NSObject
    +(MacKeyboardEvent*) sharedEvent;
    -(void) keyDown:(NSEvent*)event;
    -(void) keyUp:(NSEvent*)event;
@end

static MacKeyboardEvent* s_sharedKeyboardEvent = nil;

@implementation MacKeyboardEvent

static EventType s_originalKeyDown;
- (void)keyDownHook:(NSEvent*)event {
    s_originalKeyDown(self, @selector(keyDown:), event);
    [[MacKeyboardEvent sharedEvent] keyDown:event];
}

static EventType s_originalKeyUp;
- (void)keyUpHook:(NSEvent*)event {
    s_originalKeyUp(self, @selector(keyUp:), event);
    [[MacKeyboardEvent sharedEvent] keyUp:event];
}

#define OBJC_SWIZZLE(method, swizzle, original)                               \
Method method##Method = class_getInstanceMethod(class_, @selector(method:));            \
Method swizzle##Method = class_getInstanceMethod([self class], @selector(swizzle:));    \
original = (decltype(original))method_getImplementation(method##Method);                \
method_exchangeImplementations(method##Method, swizzle##Method);

+ (void)load {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        Class class_ = NSClassFromString(@"EAGLView");
        OBJC_SWIZZLE(keyDown, keyDownHook, s_originalKeyDown)
        OBJC_SWIZZLE(keyUp, keyUpHook, s_originalKeyUp)
    });
}

+(MacKeyboardEvent*) sharedEvent {
    @synchronized(self) {
        if (s_sharedKeyboardEvent == nil) {
            s_sharedKeyboardEvent = [[self alloc] init];
        }
    }
    
    return s_sharedKeyboardEvent;
}

-(void) keyDown:(NSEvent*)event {
    unsigned short keyCode = [event keyCode];
    LevelKeys key = convertMacKey(keyCode);
    
    Loader::get()->queueInMainThread([key]() {
        CROSSPLATFORM_ON_KEY_CALLBACK(key, true);
    });
    
}

-(void) keyUp:(NSEvent*)event {
    unsigned short keyCode = [event keyCode];
    LevelKeys key = convertMacKey(keyCode);
    
    
    Loader::get()->queueInMainThread([key]() {
        CROSSPLATFORM_ON_KEY_CALLBACK(key, false);
    });
    
}

@end

#endif
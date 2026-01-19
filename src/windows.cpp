
#include <Geode/Geode.hpp>

#if defined(GEODE_IS_WINDOWS)
#include "LevelKeys.hpp"
#include <Geode/modify/CCEGLView.hpp>


extern void CROSSPLATFORM_ON_KEY_CALLBACK(LevelKeys key, bool down);

std::unordered_map<int, bool> g_keyDown;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        int key = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;

        bool sendPress = false;
        bool down = false;
        
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            down = true;
            sendPress = true;
        }
        else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
            down = false;
            sendPress = true;
        }

        if (sendPress && (!g_keyDown[key] || !down)) {
            g_keyDown[key] = down;
            CROSSPLATFORM_ON_KEY_CALLBACK(vkKeyToLevelKey(key), down);
            geode::log::debug("key: {}, down: {}", key, down);
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

$execute {
    SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
}

#endif
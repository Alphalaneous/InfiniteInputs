#include "hooks/GJBaseGameLayer.hpp"

using namespace geode::prelude;

void CROSSPLATFORM_ON_KEY_CALLBACK(LevelKeys key, bool down)
{
    if(auto layer = reinterpret_cast<MyBaseLayer*>(GJBaseGameLayer::get()); layer && layer->isActive()) {
        layer->nh_handleKeypress(key, down);
    } else {
        log::info("unhandled press");
    }
}
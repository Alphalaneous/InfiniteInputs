#include "TextParsing.hpp"
#include "LevelKeys.hpp"
#include <scn/scan.h>
#include <Geode/utils/string.hpp>
#include <Geode/utils/casts.hpp>
#include <Geode/modify/Modify.hpp>

using namespace geode::prelude;

std::optional<bool> praseKeyUpDownSpecifier(char specifier) {
    switch(specifier) {
        case 'U': [[fallthrough]];
        case '0': return false;
        case 'D': [[fallthrough]];
        case '1': return true;

        default: return std::nullopt;
    }
}

std::optional<ParsedTextLabel> getTupleFromLabel(std::string_view t) {
    std::string keyStr;
    bool keyDown = false;
    int group = 0;
    
    if (auto result = scn::scan<std::string, char, int>(t, "@{} {} = {}")) {
        auto [key, keyDownParsed, groupParsed] = result->values();
        keyStr = std::move(key);

        if(auto keyDownOpt = praseKeyUpDownSpecifier(keyDownParsed)) {
            keyDown = *keyDownOpt;
        } else {
            geode::log::error("Not accepted key down/up specifier: {}", keyDownParsed);
            return std::nullopt;
        }

        group = groupParsed;
    }
    else if (auto result = scn::scan<std::string, int>(t, "@{} = {}")) {
        auto [key, groupParsed] = result->values();
        keyStr = std::move(key);
        group = groupParsed;
    }
    else {
        return std::nullopt;
    }
    
    auto enumval = keyLevelIdentifierToValue(keyStr);
    if (enumval == LevelKeys::unknown) {
        log::error("Unknown key name: {} (for group: {})", keyStr, group);
        return std::nullopt;
    }
    
    return ParsedTextLabel{enumval, keyDown, group};
}
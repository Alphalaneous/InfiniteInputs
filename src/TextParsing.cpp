#include "TextParsing.hpp"
#include "LevelKeys.hpp"
#include <scn/scan.h>
#include <Geode/utils/string.hpp>
#include <Geode/utils/casts.hpp>
#include <Geode/modify/Modify.hpp>

using namespace geode::prelude;

std::optional<ParsedTextLabel> getTupleFromLabel(std::string_view t) {
    if(auto result = scn::scan<std::string, int, int>(t, "@{} {} = {}")) {
        auto values = result->values();
        if(auto enumval = keyLevelIdentifierToValue(std::get<0>(values)); enumval != LevelKeys::unknown) {
            return ParsedTextLabel{enumval, std::get<1>(values) == 1, std::get<2>(values)};
        }
    }
    if(auto groupOnlyResult = scn::scan<std::string, int>(t, "@{} = {}")) {
        auto values = groupOnlyResult->values();
        if(auto enumval = keyLevelIdentifierToValue(std::get<0>(values)); enumval != LevelKeys::unknown) {
            return ParsedTextLabel{enumval, /*when no key*/0, std::get<1>(values)};
        }
    }
    return std::nullopt;
}
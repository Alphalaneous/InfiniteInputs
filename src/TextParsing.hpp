#pragma once
#include <string_view>
#include <optional>
#include "LevelKeys.hpp"

struct ParsedTextLabel {
    LevelKeys key;
    bool keyDown;
    int group;
};

std::optional<ParsedTextLabel> getTupleFromLabel(std::string_view t);
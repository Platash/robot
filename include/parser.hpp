#pragma once

#include <iostream>
#include <fstream>
#include <optional>
#include <vector>

#include "commonTypes.hpp"

struct Parser
{
    static bool isValidPath(const std::string& line);
    static std::optional<Command> parsePlaceCmd(const std::string& string);
    static std::optional<Direction> parseDirection(const std::string& string);
    static std::optional<Command> parseCommand(const std::string& line);
    static std::vector<std::string> split(std::string string, const std::string& delimiter);
};

#pragma once

#include <optional>
#include <tuple>

enum class Direction
{
    WEST,
    NORTH,
    EAST,
    SOUTH,
    END
};

const std::string EAST{"EAST"};
const std::string WEST{"WEST"};
const std::string NORTH{"NORTH"};
const std::string SOUTH{"SOUTH"};

enum class Status
{
    OK,
    BAD_ACTION
};

struct Position
{
    uint32_t x;
    uint32_t y;

    bool operator==(const Position& other) const;
};

enum class Keyword
{
    PLACE,
    MOVE,
    LEFT,
    RIGHT,
    REPORT
};

const std::string PLACE = "PLACE";
const std::string MOVE{"MOVE"};
const std::string LEFT{"LEFT"};
const std::string RIGHT{"RIGHT"};
const std::string REPORT{"REPORT"};

struct Command
{
    Keyword keyword;
    std::optional<std::tuple<Position, Direction>> args;
};

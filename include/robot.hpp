#pragma once

#include <cstdint>
#include <iostream>

#include "commonTypes.hpp"

constexpr uint32_t tableSize = 5;
constexpr uint32_t maxPosition = 4;

// DO NOT EDIT THE ORDER OF DIRECTIONS!
// It is needed for ++ operator to work properly

class Robot
{
    Direction direction;
    Position position;
    bool isOnTable = false;

public:
    bool isAbleToMove();
    Status moveInDirection();
    bool isValidPosition(const Position& position);
    Status move();
    Status place(const Position& newPosition, const Direction& newDirection);
    Status left();
    Status right();
    Status report();
    Direction getDirection();
    Position getPosition();
    Status executeCommand(const Command& command);
};

#include <iostream>
#include <utility>

#include "robot.hpp"
#include "parser.hpp"

namespace
{
     std::ostream& operator <<(std::ostream& out, Direction& direction) {
        switch (direction) 
        {
            case Direction::EAST: out << EAST; break;
            case Direction::WEST: out << WEST; break;
            case Direction::NORTH: out << NORTH; break;
            case Direction::SOUTH: out << SOUTH; break;
            default: out << int(direction); break;
        }
    return out;
    }

    Direction& operator++(Direction &direction)
    {
        using IntType = typename std::underlying_type<Direction>::type;
        direction = static_cast<Direction>(static_cast<IntType>(direction) + 1);
        if(direction == Direction::END)
        {
            direction = static_cast<Direction>(0);
        }

        return direction;
    }

    Direction operator++(Direction &direction, int)
    {
        Direction result = direction;
        ++direction;
        return result;
    }

    Direction& operator--(Direction &direction)
    {
        using IntType = typename std::underlying_type<Direction>::type;
        auto directionId = static_cast<IntType>(direction);

        if(static_cast<IntType>(directionId) == 0)
        {
            direction = static_cast<Direction>(static_cast<IntType>(Direction::END) - 1);
        }
        else
        {
            direction = static_cast<Direction>(directionId - 1);
        }

        return direction;
    }

    Direction operator--(Direction &direction, int)
    {
        Direction result = direction;
        --direction;
        return result;
    }
} // namespace
    
bool Position::operator==(const Position& other) const
{
    return(x == other.x) && (y == other.y);
}

bool Robot::isAbleToMove()
{
    if((!isOnTable) ||
        ((position.x == 0 && direction == Direction::WEST) ||
        (position.x == maxPosition && direction == Direction::EAST) ||
        (position.y == 0 && direction == Direction::SOUTH) ||
        (position.y == maxPosition && direction == Direction::NORTH)))
    {
        return false;
    }
    return true;
}

Status Robot::moveInDirection()
{
    Status status = Status::OK;
    switch (direction)
    {
    case Direction::EAST: 
        position.x++;
        break;
    case Direction::WEST:
        position.x--;
        break;
    case Direction::SOUTH:
        position.y--;
        break;
    case Direction::NORTH:
        position.y++;
        break;
        
    default:
    status = Status::BAD_ACTION;
        break;
    }

    return status;
}

bool Robot::isValidPosition(const Position& position)
{
    return position.x <= maxPosition && position.y <= maxPosition;
}

Status Robot::move()
{
    if(isOnTable && isAbleToMove())
    {
        return moveInDirection();
    }
    else
    {
        return Status::BAD_ACTION;
    }
}

Status Robot::place(const Position& newPosition, const Direction& newDirection)
{
    if(isValidPosition(newPosition))
    {
        position = newPosition;
        direction = newDirection;
        isOnTable = true;

        return Status::OK;
    }
    return Status::BAD_ACTION;
}

Status Robot::left()
{
    if(isOnTable)
    {
        direction--;
        return Status::OK;
    }
    return Status::BAD_ACTION;
}

Status Robot::right()
{
    if(isOnTable)
    {
        direction++;
        return Status::OK;
    }
    return Status::BAD_ACTION;
}

Status Robot::report()
{
    if(isOnTable)
    {
        std::cout << "Current position: X: " << position.x << " Y: " << position.y << " direction: " << direction << std::endl;
    }
    else
    {
        std::cout << "Robot is not on the table! Use place(Position, Direction) to place it." << std::endl;
    }
    return Status::OK;
}

Direction Robot::getDirection()
{
    return direction;
}

Position Robot::getPosition()
{
    return position;
}

Status Robot::executeCommand(const Command& command)
{
    Status status;

    switch (command.keyword)
    {
    case Keyword::MOVE:
        status = move();
        break;
    
    case Keyword::LEFT:
        status = left();
        break;

    case Keyword::RIGHT:
        status = right();
        break;

    case Keyword::REPORT:
        status = report();
        break;

    case Keyword::PLACE:
        if(command.args.has_value())
        {
            auto args = command.args.value();
            status = place(std::get<0>(args), std::get<1>(args));
        }
        else
        {
            status = Status::BAD_ACTION;
        }

        break;
    }
    return status;
}

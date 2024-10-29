#include <catch2/catch_test_macros.hpp>
#include "robot.hpp"

TEST_CASE("Ability to move")
{
    Robot robot;
    REQUIRE(!robot.isAbleToMove());
    robot.place({0,0}, Direction::NORTH);
    REQUIRE(robot.isAbleToMove());
    robot.right(); // EAST
    REQUIRE(robot.isAbleToMove());
    robot.right(); // SOUTH
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // WEST
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // NORTH
    REQUIRE(robot.isAbleToMove());

    robot.place({maxPosition,0}, Direction::NORTH);
    REQUIRE(robot.isAbleToMove());
    robot.right(); // EAST
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // SOUTH
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // WEST
    REQUIRE(robot.isAbleToMove());
    robot.right(); // NORTH
    REQUIRE(robot.isAbleToMove());

    robot.place({maxPosition,maxPosition}, Direction::NORTH);
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // EAST
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // SOUTH
    REQUIRE(robot.isAbleToMove());
    robot.right(); // WEST
    REQUIRE(robot.isAbleToMove());
    robot.right(); // NORTH
    REQUIRE(!robot.isAbleToMove());

    robot.place({0,maxPosition}, Direction::NORTH);
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // EAST
    REQUIRE(robot.isAbleToMove());
    robot.right(); // SOUTH
    REQUIRE(robot.isAbleToMove());
    robot.right(); // WEST
    REQUIRE(!robot.isAbleToMove());
    robot.right(); // NORTH
    REQUIRE(!robot.isAbleToMove());
}

TEST_CASE("Ignored behavior")
{
    Robot robot;
    SECTION("Before placement")
    {
        REQUIRE(!robot.isAbleToMove());
        REQUIRE(robot.move() == Status::BAD_ACTION);
        REQUIRE(robot.left() == Status::BAD_ACTION);
        REQUIRE(robot.right() == Status::BAD_ACTION);
        REQUIRE(robot.place({maxPosition+1, maxPosition+2}, Direction::NORTH) == Status::BAD_ACTION);
    }

    SECTION("After placement")
    {
        robot.place({0,0}, Direction::NORTH);
        REQUIRE(robot.isAbleToMove());
        REQUIRE(robot.place({maxPosition+1, maxPosition+2}, Direction::SOUTH) == Status::BAD_ACTION);
    }
}

TEST_CASE("Standard behavior")
{
    Robot robot;
    robot.place({1,1}, Direction::NORTH);
    REQUIRE(robot.isAbleToMove());
    REQUIRE(robot.move() == Status::OK);
    REQUIRE(robot.getDirection() == Direction::NORTH);
    REQUIRE(robot.getPosition() == Position{1,2});

    SECTION("Rotating right")
    {
        REQUIRE(robot.right() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::EAST);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{2,2});

        REQUIRE(robot.right() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::SOUTH);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{2,1});

        REQUIRE(robot.right() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::WEST);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{1,1});

        REQUIRE(robot.right() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::NORTH);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{1,2});
    }

    SECTION("Rotating left")
    {
        REQUIRE(robot.left() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::WEST);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{0,2});

        REQUIRE(robot.left() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::SOUTH);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{0,1});

        REQUIRE(robot.left() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::EAST);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{1,1});

        REQUIRE(robot.left() == Status::OK);
        REQUIRE(robot.getDirection() == Direction::NORTH);
        REQUIRE(robot.move() == Status::OK);
        REQUIRE(robot.getPosition() == Position{1,2});
    }
}

TEST_CASE("Is valid position")
{
    Robot robot;
    Position position{0,5};
    REQUIRE(!robot.isValidPosition(position));

    position.y = 4;
    REQUIRE(robot.isValidPosition(position));
}

TEST_CASE("Execute command")
{
    Robot robot;
    Command command;
    command.keyword = Keyword::MOVE;
    REQUIRE(robot.executeCommand(command) == Status::BAD_ACTION);

    command.keyword = Keyword::PLACE;
    command.args = std::make_tuple(Position{1,2}, Direction::NORTH);
    REQUIRE(robot.executeCommand(command) == Status::OK);

    command.keyword = Keyword::MOVE;
    REQUIRE(robot.executeCommand(command) == Status::OK);
    REQUIRE(robot.getDirection() == Direction::NORTH);
    REQUIRE(robot.getPosition() == Position{1,3});

    command.keyword = Keyword::RIGHT;
    REQUIRE(robot.executeCommand(command) == Status::OK);
    REQUIRE(robot.getDirection() == Direction::EAST);
    REQUIRE(robot.getPosition() == Position{1,3});

    command.keyword = Keyword::LEFT;
    REQUIRE(robot.executeCommand(command) == Status::OK);
    REQUIRE(robot.getDirection() == Direction::NORTH);
    REQUIRE(robot.getPosition() == Position{1,3});

    command.keyword = Keyword::REPORT;
    REQUIRE(robot.executeCommand(command) == Status::OK);
    REQUIRE(robot.getDirection() == Direction::NORTH);
    REQUIRE(robot.getPosition() == Position{1,3});

    command.keyword = Keyword::PLACE;
    command.args = std::make_tuple(Position{4,4}, Direction::NORTH);
    REQUIRE(robot.executeCommand(command) == Status::OK);
    REQUIRE(robot.getDirection() == Direction::NORTH);
    REQUIRE(robot.getPosition() == Position{4,4});

    command.keyword = Keyword::PLACE;
    command.args = std::make_tuple(Position{5,4}, Direction::NORTH);
    REQUIRE(robot.executeCommand(command) == Status::BAD_ACTION);
}

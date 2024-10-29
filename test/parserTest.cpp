#include <catch2/catch_test_macros.hpp>
#include "parser.hpp"

TEST_CASE("Split")
{
    std::vector<std::string> tokens = Parser::split(", aaa, bbb,ccc,ddd,", ",");
    REQUIRE(tokens.size() == 4);
    REQUIRE(tokens.at(0) == " aaa");
    REQUIRE(tokens.at(1) == " bbb");
    REQUIRE(tokens.at(2) == "ccc");
    REQUIRE(tokens.at(3) == "ddd");

    tokens = Parser::split("  aaa   ", " ");
    REQUIRE(tokens.size() == 1);
    REQUIRE(tokens.at(0) == "aaa");

    tokens = Parser::split("  aaa   bb ", " ");
    REQUIRE(tokens.size() == 2);
    REQUIRE(tokens.at(0) == "aaa");
    REQUIRE(tokens.at(1) == "bb");
}

TEST_CASE("Parse direction")
{
    REQUIRE(Parser::parseDirection(NORTH) == Direction::NORTH);
    REQUIRE(Parser::parseDirection(SOUTH) == Direction::SOUTH);
    REQUIRE(Parser::parseDirection(WEST) == Direction::WEST);
    REQUIRE(Parser::parseDirection(EAST) == Direction::EAST);
    REQUIRE(Parser::parseDirection("RANDOM") == std::nullopt);
}

TEST_CASE("Valid path")
{
    bool isValid = Parser::isValidPath("");
    REQUIRE(!isValid);

    isValid = Parser::isValidPath("/aaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    REQUIRE(!isValid);

    isValid = Parser::isValidPath("/home");
    REQUIRE(isValid);
}

TEST_CASE("Parse command")
{
    std::optional<Command> command = Parser::parseCommand("LEFT");
    REQUIRE(command.has_value());
    REQUIRE(command.value().keyword == Keyword::LEFT);
    REQUIRE(!command.value().args.has_value());

    command = Parser::parseCommand("  RIGHT  ");
    REQUIRE(command.has_value());
    REQUIRE(command.value().keyword == Keyword::RIGHT);
    REQUIRE(!command.value().args.has_value());

    command = Parser::parseCommand("  MOVE");
    REQUIRE(command.has_value());
    REQUIRE(command.value().keyword == Keyword::MOVE);
    REQUIRE(!command.value().args.has_value());

    command = Parser::parseCommand("REPORT ");
    REQUIRE(command.has_value());
    REQUIRE(command.value().keyword == Keyword::REPORT);
    REQUIRE(!command.value().args.has_value());

    command = Parser::parseCommand("  PLACE 0,4,SOUTH ");
    REQUIRE(command.has_value());
    REQUIRE(command.value().keyword == Keyword::PLACE);
    REQUIRE(command.value().args.has_value());
    REQUIRE(std::get<0>(command.value().args.value()).x == 0);
    REQUIRE(std::get<0>(command.value().args.value()).y == 4);
    REQUIRE(std::get<1>(command.value().args.value()) == Direction::SOUTH);

    command = Parser::parseCommand("PLACE 1,100,NORTH ");
    REQUIRE(command.has_value());
    REQUIRE(command.value().keyword == Keyword::PLACE);
    REQUIRE(command.value().args.has_value());
    REQUIRE(std::get<0>(command.value().args.value()).x == 1);
    REQUIRE(std::get<0>(command.value().args.value()).y == 100);
    REQUIRE(std::get<1>(command.value().args.value()) == Direction::NORTH);
}
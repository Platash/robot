#include <fstream>
#include <filesystem>

#include "parser.hpp"

constexpr uint32_t MAX_INPUT_LEN = 333; // Max allowed user input

std::vector<std::string> Parser::split(std::string string, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = string.find(delimiter)) != std::string::npos) {
        token = string.substr(0, pos);
        if(!token.empty())
        {
            tokens.push_back(token);
        }
        string.erase(0, pos + delimiter.length());
    }
    if(!string.empty())
    {
        tokens.push_back(string);
    }

    return tokens;
}


bool Parser::isValidPath(const std::string& line)
{
    if(line.size() > MAX_INPUT_LEN || line.empty())
    {
        return false;
    }
    try
    {
        std::filesystem::path pathToFile(line);
        return std::filesystem::exists(pathToFile);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return false;
}

std::optional<Command> Parser::parsePlaceCmd(const std::string& string)
{
    auto args = split(string, ",");
    if(args.size() != 3)
    {
        return std::nullopt;
    }

    uint32_t x = 0;
    uint32_t y = 0;

    try
    {
        x = std::stoi(args.at(0));
        y = std::stoi(args.at(1));
    }
    catch (std::invalid_argument const& ex)
    {
        return std::nullopt;
    }
    catch (std::out_of_range const& ex)
    {
        return std::nullopt;
    }
    
    std::optional<Direction> direction = parseDirection(args.at(2));
    if(!direction.has_value())
    {
        return std::nullopt;
    }
    
    Command cmd{
        .keyword = Keyword::PLACE,
        .args = std::make_tuple(Position{x,y}, direction.value())
    };

    return cmd;
}

std::optional<Direction> Parser::parseDirection(const std::string& string)
{
    if(string == NORTH)
    {
        return Direction::NORTH;
    }
    else if(string == SOUTH)
    {
        return Direction::SOUTH;
    }
    else if(string == EAST)
    {
        return Direction::EAST;
    }
    else if(string == WEST)
    {
        return Direction::WEST;
    }

    return std::nullopt;
}

std::optional<Command> Parser::parseCommand(const std::string& line)
{
    auto commands = split(line, " ");

    if(commands.empty())
    {
        return std::nullopt;
    }
    else if(commands.at(0) == PLACE)
    {
        return parsePlaceCmd(commands.at(1));
    }
    else if(commands.size() > 1)
    {
        return std::nullopt;         
    }
    else if(commands.at(0) == MOVE)
    {
        return Command({Keyword::MOVE});
    }
    else if(commands.at(0) == LEFT)
    {
        return Command({Keyword::LEFT});
    }
    else if(commands.at(0) == RIGHT)
    {
        return Command({Keyword::RIGHT});
    }
    else if(commands.at(0) == REPORT)
    {
        return Command({Keyword::REPORT});
    }

    return std::nullopt;
}

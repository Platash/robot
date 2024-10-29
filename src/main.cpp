#include <string>
#include "parser.hpp"
#include "robot.hpp"

int main(void)
{
    Robot robot;
    std::string line;
    std::ifstream commandFile;
    const std::string exitCommand = "exit";
    const uint32_t BUFF_SIZE = 32;

    while(true)
    {
        std::cout << std::endl;
        std::cout << "Enter address of the file with commands" << std::endl;
        std::cout << "Enter < exit > to exit" << std::endl;
        std::getline(std::cin, line);

        if(line == exitCommand)
        {
            break;
        }
        else if(Parser::isValidPath(line))
        {
            commandFile.open(line, std::ifstream::in);
            if(commandFile.is_open())
            {
                std::cout << "File is open, executing commands" << std::endl;

                char buff[BUFF_SIZE];
                while(commandFile.good())
                {
                    commandFile.getline(buff, BUFF_SIZE);
                    auto cmd = Parser::parseCommand(buff);
                    if(cmd.has_value())
                    {
                        robot.executeCommand(cmd.value());
                    }
                    else
                    {
                        std::cout << "Invalid command " << buff << ". Finishing execution." << std::endl;
                        break;
                    }
                }
                commandFile.close();
            }
            else
            {
                std::cout << "Failed to open file " << line << std::endl;        
            }
        }
        else
        {
            std::cout << "Invalid input. Provide a valid path to file with instructions." << std::endl;
        }
    }
    
    return 0;
}
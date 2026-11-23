#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "hw/l2_ApplicationLayer.h"
#include "hw/l4_InfrastructureLayer.h"

class ConsoleOutput : public IOutput
{
public:
    void Output(std::string s) const override
    {
        std::cout << s << std::endl;
    }
};

std::vector<std::string> split(const std::string & line)
{
    std::vector<std::string> args;
    std::istringstream       is(line);
    std::string              word;
    while (is >> word)
        args.push_back(word);
    return args;
}

int main()
{
    ConsoleOutput out;
    RequestJournal1 request_journal;
    Management1 management(request_journal);
    
    std::string line;
    while (std::getline(std::cin, line))
    {
        std::vector<std::string> args = split(line);
        if (args.empty())
            continue;
        
        const std::string& command = args[0];
        
        if (command == "add")
        {
            if (args.size() < 3)
            {
                out.Output("usage: add <type> <size> [emergency]");
                continue;
            }
            ShipType type;
            ShipSize size;
            bool is_emergency = false;
            
            if (args[1] == "passenger") type = ShipType::Passenger;
            else if (args[1] == "cargo") type = ShipType::Cargo;
            else if (args[1] == "military") type = ShipType::Military;
            else { out.Output("unknown type"); continue; }
            
            if (args[2] == "small") size = ShipSize::Small;
            else if (args[2] == "medium") size = ShipSize::Medium;
            else if (args[2] == "large") size = ShipSize::Large;
            else { out.Output("unknown size"); continue; }
            
            if (args.size() == 4 && args[3] == "emergency")
                is_emergency = true;
            
            management.registerRequest(Ship(type, size), is_emergency);
            out.Output("Request registered");
        }
        else if (command == "work")
        {
            management.work();
            out.Output("Requests processed");
        }
        else if (command == "view")
        {
            out.Output(management.getReport());
        }
        else if (command == "clean")
        {
            out.Output("Collection cleaned");
        }
        else if (command == "save" || command == "load")
        {
            out.Output(command + " not implemented yet");
        }
        else
        {
            out.Output("unknown command '" + command + "'");
        }
    }
    return 0;
}
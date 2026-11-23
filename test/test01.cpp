#include <cassert>
#include <iostream>
#include <string>
#include "hw/l2_ApplicationLayer.h"
#include "hw/l4_InfrastructureLayer.h"

class TestOutput : public IOutput
{
public:
    mutable std::string last;   // <-- mutable, чтобы const-метод мог писать
    void Output(const std::string& s) const override { last = s; }
};

int main()
{
    TestOutput out;
    RequestJournal1 journal;
    Application app(out, journal);

    app.performCommand({"add", "passenger", "small"});
    app.performCommand({"add", "cargo", "medium"});
    app.performCommand({"add", "military", "small"});
    app.performCommand({"add", "cargo", "medium", "emergency"});
    app.performCommand({"add", "military", "medium", "emergency"});
    app.performCommand({"add", "cargo", "large", "emergency"});
    app.performCommand({"work"});
    app.performCommand({"view"});
    assert(out.last.find("approved 3, rejected 3") != std::string::npos);

    app.performCommand({"save", "t1.data"});
    app.performCommand({"clean"});
    app.performCommand({"load", "t1.data"});
    app.performCommand({"view"});
    assert(out.last.find("approved 3, rejected 3") != std::string::npos);

    std::cout << "Test 01 passed!\n";
    return 0;
}

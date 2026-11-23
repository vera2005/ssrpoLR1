#include <iostream>
#include <cassert>
#include "hw/l2_ApplicationLayer.h"
#include "hw/l4_InfrastructureLayer.h"

int main()
{
    RequestJournal1 journal;
    Management1 management(journal);
    
    management.registerRequest(Ship(ShipType::Passenger, ShipSize::Small), false);
    management.work();
    management.work();
    
    assert(journal.getInfo().size() == 1);
    
    std::cout << "Test 02 passed!" << std::endl;
    return 0;
}
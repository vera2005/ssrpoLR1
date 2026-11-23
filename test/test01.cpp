#include <iostream>
#include <cassert>
#include "hw/l2_ApplicationLayer.h"
#include "hw/l4_InfrastructureLayer.h"

int main()
{
    RequestJournal1 journal;
    Management1 management(journal);
    
    management.registerRequest(Ship(ShipType::Passenger, ShipSize::Small), false);
    management.registerRequest(Ship(ShipType::Cargo, ShipSize::Medium), false);
    management.registerRequest(Ship(ShipType::Military, ShipSize::Small), false);
    management.registerRequest(Ship(ShipType::Passenger, ShipSize::Medium), true);
    management.registerRequest(Ship(ShipType::Military, ShipSize::Medium), true);
    management.registerRequest(Ship(ShipType::Cargo, ShipSize::Large), true);
    
    management.work();
    
    std::string report = management.getReport();
    std::cout << report;
    
    assert(report.find("одобрен") != std::string::npos);
    assert(report.find("отклонён") != std::string::npos);
    assert(report.find("Итого: одобрено 3, отклонено 3.") != std::string::npos);
    
    std::cout << "Test 01 passed!" << std::endl;
    return 0;
}
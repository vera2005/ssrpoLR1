#ifndef L2_APPLICATIONLAYER_H
#define L2_APPLICATIONLAYER_H

#include "hw/l3_DomainLayer.h"
#include "hw/l4_InfrastructureLayer.h"
#include <vector>
#include <string>

class IOutput
{
public:
    virtual ~IOutput() = default;
    virtual void Output(std::string s) const = 0;
};

class Management1
{
public:
    explicit Management1(IRequestJournal& request_journal);
    void registerRequest(const Ship& ship, bool is_emergency);
    void work();
    std::string getReport() const;
private:
    using PendingRequest = std::tuple<Ship, bool, TimePoint>;
    bool checkInvariant() const;
    IRequestJournal& _request_journal;
    std::vector<PendingRequest> _pending_requests;
};

#endif // L2_APPLICATIONLAYER_H
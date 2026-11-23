#include "hw/l2_ApplicationLayer.h"
#include <cassert>
#include <chrono>

Management1::Management1(IRequestJournal& request_journal)
    : _request_journal(request_journal)
{
    assert(checkInvariant());
}

void Management1::registerRequest(const Ship& ship, bool is_emergency)
{
    _pending_requests.emplace_back(
        ship, is_emergency, std::chrono::system_clock::now());
    assert(checkInvariant());
}

void Management1::work()
{
    for (const PendingRequest& pending_request : _pending_requests)
    {
        const Ship& ship = std::get<0>(pending_request);
        const bool is_emergency = std::get<1>(pending_request);
        const TimePoint request_time = std::get<2>(pending_request);
        const TimePoint response_time = std::chrono::system_clock::now();
        const RequestStatus status = checkCanLand(ship, is_emergency)
            ? RequestStatus::Approved
            : RequestStatus::Rejected;
        _request_journal.addRequest(
            Request(ship, request_time, response_time, status, is_emergency));
    }
    _pending_requests.clear();
    assert(checkInvariant());
}

std::string Management1::getReport() const
{
    ReportSystem1 report_system(_request_journal);
    return report_system.makeReport();
}

bool Management1::checkInvariant() const
{
    return true;
}
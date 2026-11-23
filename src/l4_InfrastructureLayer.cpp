#include "hw/l4_InfrastructureLayer.h"
#include <cassert>
#include <sstream>
#include <string>

RequestJournal1::RequestJournal1()
{
    assert(checkInvariant());
}

void RequestJournal1::addRequest(const Request& request)
{
    _requests.push_back(request);
    assert(checkInvariant());
}

const std::vector<Request>& RequestJournal1::getInfo() const
{
    return _requests;
}

bool RequestJournal1::checkInvariant() const
{
    for (const Request& request : _requests)
    {
        if (request.getResponseTime() < request.getRequestTime())
        {
            return false;
        }
    }
    return true;
}

namespace
{
std::string getShipTypeName(ShipType type)
{
    switch (type)
    {
    case ShipType::Passenger: return "пассажирский";
    case ShipType::Cargo: return "грузовой";
    case ShipType::Military: return "военный";
    }
    return "неизвестный";
}

std::string getShipSizeName(ShipSize size)
{
    switch (size)
    {
    case ShipSize::Large: return "большой";
    case ShipSize::Medium: return "средний";
    case ShipSize::Small: return "малый";
    }
    return "неизвестный";
}

std::string getStatusName(RequestStatus status)
{
    switch (status)
    {
    case RequestStatus::Approved: return "одобрен";
    case RequestStatus::Rejected: return "отклонён";
    }
    return "неизвестен";
}
}

ReportSystem1::ReportSystem1(IRequestJournal& request_journal)
    : _request_journal(request_journal)
{
    assert(checkInvariant());
}

std::string ReportSystem1::makeReport() const
{
    const std::vector<Request>& requests = _request_journal.getInfo();
    std::size_t approved_count = 0;
    std::size_t rejected_count = 0;
    std::size_t request_number = 0;
    std::ostringstream report;
    report << "Отчёт о разрешениях на посадку\n";
    for (const Request& request : requests)
    {
        ++request_number;
        if (request.getStatus() == RequestStatus::Approved)
        {
            ++approved_count;
        }
        else
        {
            ++rejected_count;
        }
        report << request_number << ". Тип: "
               << getShipTypeName(request.getShip().getType())
               << "; размер: "
               << getShipSizeName(request.getShip().getSize())
               << "; экстренный: "
               << (request.isEmergency() ? "да" : "нет")
               << "; статус: "
               << getStatusName(request.getStatus()) << '\n';
    }
    report << "Итого: одобрено " << approved_count
           << ", отклонено " << rejected_count << ".\n";
    return report.str();
}

bool ReportSystem1::checkInvariant() const
{
    return true;
}
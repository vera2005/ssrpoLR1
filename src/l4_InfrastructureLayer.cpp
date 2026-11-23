#include "hw/l4_InfrastructureLayer.h"
#include <cassert>
#include <cstddef>
#include <fstream>
#include <sstream>
#include <string>

RequestJournal1::RequestJournal1() { assert(checkInvariant()); }
void RequestJournal1::addRequest(const Request& request)
{
    _requests.push_back(request);
    assert(checkInvariant());
}
const std::vector<Request>& RequestJournal1::getInfo() const { return _requests; }
void RequestJournal1::clean() { _requests.clear(); }
bool RequestJournal1::checkInvariant() const
{
    for (const Request& r : _requests)
        if (r.getResponseTime() < r.getRequestTime())
            return false; // GCOVR_EXCL_LINE
    return true;
}

/// Текстовый формат строки журнала:
/// <type> <size> <emergency> <req_sec> <resp_sec> <status>
bool RequestJournal1::loadCollection(const std::string& file_name)
{
    std::ifstream is(file_name);
    if (!is)
        return false;
    clean();
    std::string line;
    while (std::getline(is, line))
    {
        std::istringstream ls(line);
        int type, size, emergency, req_sec, resp_sec, status;
        if (!(ls >> type >> size >> emergency >> req_sec >> resp_sec >> status))
            return false;
        _requests.emplace_back(
            Ship(static_cast<ShipType>(type), static_cast<ShipSize>(size)),
            TimePoint(std::chrono::seconds(req_sec)),
            TimePoint(std::chrono::seconds(resp_sec)),
            static_cast<RequestStatus>(status),
            emergency != 0);
    }
    return true;
}
bool RequestJournal1::saveCollection(const std::string& file_name) const
{
    std::ofstream os(file_name);
    if (!os)
        return false;
    for (const Request& r : _requests)
    {
        os << static_cast<int>(r.getShip().getType()) << ' '
           << static_cast<int>(r.getShip().getSize()) << ' '
           << (r.isEmergency() ? 1 : 0) << ' '
           << std::chrono::duration_cast<std::chrono::seconds>(
                  r.getRequestTime().time_since_epoch()).count() << ' '
           << std::chrono::duration_cast<std::chrono::seconds>(
                  r.getResponseTime().time_since_epoch()).count() << ' '
           << static_cast<int>(r.getStatus()) << '\n';
    }
    return os.good();
}

namespace
{
std::string typeName(ShipType t)
{
    switch (t)
    {
    case ShipType::Passenger: return "пассажирский";
    case ShipType::Cargo:     return "грузовой";
    case ShipType::Military:  return "военный";
    }
    return "неизвестный"; // GCOVR_EXCL_LINE
}
std::string sizeName(ShipSize s)
{
    switch (s)
    {
    case ShipSize::Large:  return "большой";
    case ShipSize::Medium: return "средний";
    case ShipSize::Small:  return "малый";
    }
    return "неизвестный"; // GCOVR_EXCL_LINE
}
std::string statusName(RequestStatus st)
{
    switch (st)
    {
    case RequestStatus::Approved: return "одобрен";
    case RequestStatus::Rejected: return "отклонён";
    }
    return "неизвестен"; // GCOVR_EXCL_LINE
}
} // namespace

ReportSystem1::ReportSystem1(const IRequestJournal& j) : _request_journal(j)
{
    assert(checkInvariant());
}
std::string ReportSystem1::makeReport() const
{
    const std::vector<Request>& reqs = _request_journal.getInfo();
    std::size_t approved = 0, rejected = 0, n = 0;
    std::ostringstream rep;
    rep << "Отчёт о разрешениях на посадку\n";
    for (const Request& r : reqs)
    {
        ++n;
        if (r.getStatus() == RequestStatus::Approved) ++approved; else ++rejected;
        rep << n << ". Тип: " << typeName(r.getShip().getType())
            << "; размер: " << sizeName(r.getShip().getSize())
            << "; экстренный: " << (r.isEmergency() ? "да" : "нет")
            << "; статус: " << statusName(r.getStatus()) << '\n';
    }
    rep << "Итого: одобрено " << approved << ", отклонено " << rejected << ".\n";
    return rep.str();
}
bool ReportSystem1::checkInvariant() const { return true; }
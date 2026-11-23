#ifndef L4_INFRASTRUCTURELAYER_H
#define L4_INFRASTRUCTURELAYER_H

#include "hw/l3_DomainLayer.h"
#include <vector>
#include <string>

class IRequestJournal
{
public:
    virtual ~IRequestJournal() = default;
    virtual void addRequest(const Request& request) = 0;
    virtual const std::vector<Request>& getInfo() const = 0;
};

class RequestJournal1 : public IRequestJournal
{
public:
    RequestJournal1();
    void addRequest(const Request& request) override;
    const std::vector<Request>& getInfo() const override;
private:
    bool checkInvariant() const;
    std::vector<Request> _requests;
};

class IReportSystem
{
public:
    virtual ~IReportSystem() = default;
    virtual std::string makeReport() const = 0;
};

class ReportSystem1 : public IReportSystem
{
public:
    explicit ReportSystem1(IRequestJournal& request_journal);
    std::string makeReport() const override;
private:
    bool checkInvariant() const;
    IRequestJournal& _request_journal;
};

#endif // L4_INFRASTRUCTURELAYER_H
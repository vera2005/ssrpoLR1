#ifndef HW_L2_APPLICATIONLAYER_H_
#define HW_L2_APPLICATIONLAYER_H_

#include "hw/l3_DomainLayer.h"
#include "hw/l4_InfrastructureLayer.h"
#include <string>
#include <vector>

class IOutput {
public:
    virtual ~IOutput() = default;
    virtual void Output(const std::string& s) const = 0;
};

class Application {
public:
    Application(const IOutput& out, RequestJournal1& journal);
    bool performCommand(const std::vector<std::string>& args);
private:
    bool add(const std::vector<std::string>& args);
    bool work(const std::vector<std::string>& args);
    bool view(const std::vector<std::string>& args);
    bool clean(const std::vector<std::string>& args);
    bool save(const std::vector<std::string>& args);
    bool load(const std::vector<std::string>& args);
    bool parseShip(const std::string& t, const std::string& s, Ship& ship);
    bool error(const std::string& msg);

    const IOutput& _out;
    RequestJournal1& _journal;
    
    struct PendingRequest {
        Ship ship;
        bool is_emergency;
        TimePoint request_time;
    };
    std::vector<PendingRequest> _pending;
};

#endif // HW_L2_APPLICATIONLAYER_H_
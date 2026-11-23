#include "hw/l3_DomainLayer.h"
#include <cassert>
#include <utility>

Ship::Ship(ShipType type, ShipSize size) : _type(type), _size(size) {
    assert(checkInvariant());
}
ShipType Ship::getType() const { return _type; }
ShipSize Ship::getSize() const { return _size; }
bool Ship::checkInvariant() const {
    bool is_type_valid = (_type == ShipType::Passenger || _type == ShipType::Cargo || _type == ShipType::Military);
    bool is_size_valid = (_size == ShipSize::Large || _size == ShipSize::Medium || _size == ShipSize::Small);
    return is_type_valid && is_size_valid;
}

Request::Request(Ship ship, TimePoint request_time, TimePoint response_time,
                 RequestStatus status, bool is_emergency)
    : _ship(std::move(ship)), _request_time(request_time),
      _response_time(response_time), _status(status), _is_emergency(is_emergency) {
    assert(checkInvariant());
}
const Ship& Request::getShip() const { return _ship; }
TimePoint Request::getRequestTime() const { return _request_time; }
TimePoint Request::getResponseTime() const { return _response_time; }
RequestStatus Request::getStatus() const { return _status; }
bool Request::isEmergency() const { return _is_emergency; }
bool Request::checkInvariant() const {
    bool is_status_valid = (_status == RequestStatus::Approved || _status == RequestStatus::Rejected);
    return is_status_valid && _response_time >= _request_time;
}

bool checkCanLand(const Ship& ship, bool is_emergency) {
    const bool is_small_civil = ship.getSize() == ShipSize::Small && ship.getType() != ShipType::Military;
    const bool is_emergency_exception = is_emergency && (ship.getSize() == ShipSize::Medium || ship.getType() == ShipType::Military);
    return is_small_civil || is_emergency_exception;
}
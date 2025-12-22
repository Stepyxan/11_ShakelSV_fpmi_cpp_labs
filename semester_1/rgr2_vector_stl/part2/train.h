#pragma once

#include <string>
#include "time_utility.h"

using TrainId = size_t;
using namespace time_utility;


enum class TrainType { 
    PASSENGER, FREIGHT, HIGH_SPEED, SUBWAY, SPECIALIZED
};


class Train {
private:
    TrainId id_;
    TrainType type_;
    std::string destination_;
    std::time_t dispatch_time_;
    std::time_t travelling_time_;

public:
    Train() = default;

    Train(TrainId id, TrainType type, const std::string& destination,
            std::time_t dispatch_time, std::time_t travelling_time)
        : id_(id), type_(type), destination_(destination),
            dispatch_time_(dispatch_time), travelling_time_(travelling_time) {}
    
    TrainId getId() const {
        return id_;
    }

    TrainType getType() const {
        return type_;
    }

    const std::string& getDestination() const {
        return destination_;
    }

    std::time_t getDispatchTime() const {
        return dispatch_time_;
    }

    std::time_t getTravellingTime() const {
        return travelling_time_;
    }

    bool operator<(const Train& rhs) const {
        return dispatch_time_ < rhs.dispatch_time_;
    }
};


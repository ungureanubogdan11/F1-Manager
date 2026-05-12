#include "car.h"
#include "part.h"
#include <algorithm>

Car::Car(int ts, int acc, int cs) 
    : baseTopSpeed(ts), baseAcceleration(acc), baseCornering(cs) {}

Car::~Car() {
    for(auto p : parts) delete p;
}

Car::Car(const Car& other) 
    : baseTopSpeed(other.baseTopSpeed), baseAcceleration(other.baseAcceleration), 
      baseCornering(other.baseCornering) {
    for(auto p : other.parts) parts.push_back(p->clone());
}

void swap(Car& first, Car& second) noexcept {
    std::swap(first.parts, second.parts);
    std::swap(first.baseTopSpeed, second.baseTopSpeed);
    std::swap(first.baseAcceleration, second.baseAcceleration);
    std::swap(first.baseCornering, second.baseCornering);
}

Car& Car::operator=(Car other) {
    swap(*this, other);
    return *this;
}

double Car::computeCarPower(const Track* track) const {
    double topSpeedMod = 1.0, corneringMod = 1.0, accelMod = 1.0;

    for (Part* p : parts) {
        if (auto* e = dynamic_cast<Engine*>(p)) topSpeedMod = e->getModifier();
        else if (auto* a = dynamic_cast<AeroKit*>(p)) corneringMod = a->getModifier();
        else if (auto* c = dynamic_cast<Chassis*>(p)) accelMod = c->getModifier();
    }

    return (this->baseTopSpeed * topSpeedMod * track->get_topSpeed_weight()) +
           (this->baseCornering * corneringMod * track->get_cornerSpeed_weight()) +
           (this->baseAcceleration * accelMod);
}
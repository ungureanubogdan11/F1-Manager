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
int Car::get_topSpeed() const {
    double mult = 1.0;
    for(Part* p : parts) {
        if(dynamic_cast<Engine*>(p)) mult *= p->getModifier();
    }
    return (int)(baseTopSpeed * mult);
}

int Car::get_acceleration() const {
    double mult = 1.0;
    for(Part* p : parts) {
        if(dynamic_cast<Chassis*>(p)) mult *= p->getModifier();
    }
    return (int)(baseAcceleration * mult);
}

int Car::get_cornerSpeed() const {
    double mult = 1.0;
    for(Part* p : parts) {
        if(dynamic_cast<AeroKit*>(p)) mult *= p->getModifier();
    }
    return (int)(baseCornering * mult);
}

std::ostream& operator<<(std::ostream& os, const Car& c) {
    os << "Car Performance [TS: " << c.get_topSpeed() << " | ACC: " << c.get_acceleration() << "]\n";
    
    for(auto p : c.parts) {
        os << " - " << *p << "\n"; 
    }
    return os;
}
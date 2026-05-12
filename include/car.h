#ifndef CAR_H
#define CAR_H

#include "part.h"
#include "track.h"
#include <vector>

class Car {
    std::vector<Part*> parts; 
    
    int baseTopSpeed;
    int baseAcceleration;
    int baseCornering;

public:
    Car(int ts, int acc, int cs);
    ~Car();

    Car(const Car& other);
    Car& operator=(Car other);
    friend void swap(Car& first, Car& second) noexcept;

    void addPart(Part* p) { parts.push_back(p); }
    const std::vector<Part*>& getParts() const { return parts; }
    double computeCarPower(const Track * track) const;

    friend std::ostream& operator<<(std::ostream& os, const Car& c);
};

#endif
#ifndef CAR_H
#define CAR_H

#include "part.h"
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

    int get_topSpeed() const;
    int get_acceleration() const;
    int get_cornerSpeed() const;

    friend std::ostream& operator<<(std::ostream& os, const Car& c);
};

#endif
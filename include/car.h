#ifndef CAR_H
#define CAR_H

#include <iostream>

class Car {
    int topSpeed, acceleration, cornerSpeed, aeroPerformance;

public:
    Car(int topSpeed, int acceleration, int cornerSpeed, int aeroPerformance);
    Car(const Car& other);
    Car& operator=(const Car& other);
    ~Car() = default;

    int get_topSpeed() const { return topSpeed; }
    int get_cornerSpeed() const { return cornerSpeed; }
    int get_acceleration() const { return acceleration; }
    int get_aeroPerformance() const { return aeroPerformance; }

    friend std::ostream& operator<<(std::ostream& os, const Car& c);
};

#endif
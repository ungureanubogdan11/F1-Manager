#ifndef CAR_H
#define CAR_H

#include <iostream>

class Car {
    int topSpeed, acceleration, cornerSpeed, aeroPerformance;

public:
    Car(int topSpeed, int acceleration, int cornerSpeed, int aeroPerformance);
    Car(const Car& other);
    Car& operator=(const Car& other);

    int get_topSpeed() const;
    int get_cornerSpeed() const;
    int get_acceleration() const;
    int get_aeroPerformance() const;

    friend std::ostream& operator<<(std::ostream& os, const Car& c);
};

#endif
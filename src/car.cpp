#include "car.h"

Car::Car(int ts, int acc, int cs, int aero) 
    : topSpeed(ts), acceleration(acc), cornerSpeed(cs), aeroPerformance(aero) {}

Car::Car(const Car& other) 
    : topSpeed(other.topSpeed), acceleration(other.acceleration), 
      cornerSpeed(other.cornerSpeed), aeroPerformance(other.aeroPerformance) {}

Car& Car::operator=(const Car& other) {
    if(this == &other) return *this;
    topSpeed = other.topSpeed;
    acceleration = other.acceleration;
    cornerSpeed = other.cornerSpeed;
    aeroPerformance = other.aeroPerformance;
    return *this;
}

int Car::get_topSpeed() const { return topSpeed; }
int Car::get_cornerSpeed() const { return cornerSpeed; }
int Car::get_acceleration() const { return acceleration; }
int Car::get_aeroPerformance() const { return aeroPerformance; }

std::ostream& operator<<(std::ostream& os, const Car& c) {
    os << "Top Speed: " << c.topSpeed << "\nAccel: " << c.acceleration 
       << "\nCornering: " << c.cornerSpeed << "\nAero: " << c.aeroPerformance << "\n";
    return os;
}
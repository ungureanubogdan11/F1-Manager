#include "driver.h"

const std::vector<int> gp_points = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

Driver::Driver(int id, const std::string& name, Team* team, double price, 
               int exp, int pace, int agg, int aware, int tyre) 
    : id(id), name(name), team(team), price(price), experience(exp), 
      pace(pace), aggressiveness(agg), awareness(aware), tyreManagement(tyre) {}

void Driver::update(int place) {
    racesWon += (place == 1);
    poles += (place >= 1 && place <= 3);
    if(place <= 10) points += gp_points[place - 1];
}

bool Driver::operator<(const Driver& other) const {
    return this->points > other.points;
}

std::ostream& operator<<(std::ostream& os, const Driver& d) {
    os << "Driver: " << d.name << " | Points: " << d.points << " | Wins: " << d.racesWon;
    return os;
}
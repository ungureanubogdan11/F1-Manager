#include "driver.h"
#include "championship.h"

int Driver::next_id = 1;

Driver::Driver(const std::string& name, Team* team, double price, 
               int exp, int pace, int agg, int aware, int tyre) 
    : name(name), team(team), price(price), experience(exp), 
      pace(pace), aggressiveness(agg), awareness(aware), tyreManagement(tyre) {
        id = next_id++;
      }

void Driver::update(int place) {
    racesWon += (place == 1);
    poles += (place >= 1 && place <= 3);
    if(place <= 10) points += Championship::getPointsForPlace(place);
}

bool Driver::operator<(const Driver& other) const {
    return this->points > other.points;
}

std::ostream& operator<<(std::ostream& os, const Driver& d) {
    os << "Driver: " << d.name << " | Points: " << d.points << " | Wins: " << d.racesWon;
    return os;
}
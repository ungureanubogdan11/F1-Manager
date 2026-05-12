#include "driver.h"

const std::vector<int> gp_points = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

Driver::Driver(int id, const std::string& name, int team_id, double price, 
               int exp, int pace, int agg, int aware, int tyre) 
    : id(id), name(name), team_id(team_id), price(price), experience(exp), 
      pace(pace), aggressiveness(agg), awareness(aware), tyreManagement(tyre) {}

void Driver::update(int place) {
    racesWon += (place == 1);
    poles += (place >= 1 && place <= 3);
    if(place <= 10) points += gp_points[place - 1];
}

bool Driver::operator<(const Driver& other) const {
    return this->points > other.points;
}

// Getters...
int Driver::get_points() const { return points; }
const std::string& Driver::get_name() const { return name; }
int Driver::get_id() const { return id; }
int Driver::get_team_id() const { return team_id; }
int Driver::get_pace() const { return pace; }
int Driver::get_experience() const { return experience; }
int Driver::get_aggressiveness() const { return aggressiveness; }
int Driver::get_awareness() const { return awareness; }
int Driver::get_tyreManagement() const { return tyreManagement; }

std::ostream& operator<<(std::ostream& os, const Driver& d) {
    os << "Name: " << d.name << "\nPoints: " << d.points << "\nWins: " << d.racesWon << "\n";
    return os;
}
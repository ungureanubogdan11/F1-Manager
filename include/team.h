#ifndef TEAM_H
#define TEAM_H

#include "car.h"
#include <string>
#include <vector>

class Driver; 

class Team {
    int id;
    std::string name;
    std::vector<Driver*> drivers;
    Car* car;
    
    int budget, designEfficiency, researchPower, pitCrewSpeed, strategyIntel;
    int racesWon = 0, poles = 0, points = 0;

public:
    Team(int id, const std::string& name, int budget, int design, int research, int pit, int strategy);
    ~Team();
    Team(const Team& other);
    Team& operator=(const Team& other);

    void add_driver(Driver* d) { drivers.push_back(d); }
    void build_car();
    void update(int place);

    bool operator<(const Team& other) const { return this->points > other.points; }

    Car* get_car() const { return car; }
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    int get_points() const { return points; }
    const std::vector<Driver*>& get_drivers() const { return drivers; }

    friend std::ostream& operator<<(std::ostream& os, const Team& t);
};

#endif
#ifndef TEAM_H
#define TEAM_H

#include "driver.h"
#include "car.h"
#include <vector>

class Team {
    int id;
    std::string name;
    std::vector<Driver*> drivers;
    Car* car;
    int budget, designEfficiency, researchPower, pitCrewSpeed, strategyIntel;
    int racesWon = 0, poles = 0, points = 0;

public:
    Team(int id, const std::string& name, const std::vector<Driver*>& drivers, 
         int budget, int design, int research, int pit, int strategy);
    Team(const Team& other);
    Team& operator=(const Team& other);
    ~Team();

    void build_car();
    void update(int place);
    bool operator<(const Team& other) const;

    const std::vector<Driver*>& get_drivers() const;
    const std::string& get_name() const;
    int get_points() const;
    int get_id() const;
    Car* get_car() const;

    friend std::ostream& operator<<(std::ostream& os, const Team& t);
};

#endif
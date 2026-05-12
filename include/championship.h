#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "race.h"

class Championship {
    std::vector<Driver*> driverStandings;
    std::vector<Team*> teamStandings;
    std::vector<Race*> races;

public:
    void add_team(Team* t);
    void add_race(Race* r) { races.push_back(r); }
    void sim_championship();
    void update_standings(const Race* r);
    void print_table();
};
#endif
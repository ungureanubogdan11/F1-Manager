#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "race.h"

class Championship {
    std::vector<Driver*> driverStandings;
    std::vector<Team*> teamStandings;
    std::vector<Race*> races;
    std::unordered_map<int, Driver*> driverLookup;
    std::unordered_map<int, Team*> teamLookup;

public:
    void add_team(Team* team);
    void add_race(Race* race);
    void update_standings(const Race* race);
    void sim_championship();
    void print_table();
};
#endif
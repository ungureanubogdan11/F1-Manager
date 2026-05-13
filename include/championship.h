#ifndef CHAMPIONSHIP_H
#define CHAMPIONSHIP_H

#include "race.h"

class Championship {
    static const std::vector<int> gp_points;
    std::vector<Driver*> driverStandings;
    std::vector<Team*> teamStandings;
    std::vector<Race*> races;
    static int computeRaceIntensity(const Track * track, const Driver * driver, const Race * r);
    
public:

    void add_team(Team* t);
    void add_driver(Driver* d);
    void add_race(Race* r) { races.push_back(r); }
    void sim_championship();
    void update_standings(const Race* r);
    void print_table();

    static int getPointsForPlace(int place) {
        if (place >= 1 && place <= 10) {
            return gp_points[place - 1];
        }
        return 0;
    }
};
#endif
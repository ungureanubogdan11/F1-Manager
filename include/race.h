#ifndef RACE_H
#define RACE_H

#include "team.h"
#include "track.h"
#include <unordered_map>

enum Weather { DRY, WET, RAINING };

class Race {
    int raceNumber;
    Weather weather;
    Track* track;
    std::vector<Driver*> runningOrder;
    std::unordered_map<int, Team*> teamLookup;

public:
    Race(int num, Weather w, const std::vector<Driver*>& order, const std::vector<Team*>& teams, Track* t);
    void sim_race();
    const std::vector<Driver*>& get_runningOrder() const;
    friend std::ostream& operator<<(std::ostream& os, const Race& r);
};
#endif
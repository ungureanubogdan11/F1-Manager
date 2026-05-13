#ifndef RACE_H
#define RACE_H

#include "driver.h"
#include "team.h"
#include "track.h"
#include <vector>


class Race {
public:
    enum Weather { DRY, WET, RAINING };
private:
   [[maybe_unused]] int raceNumber;
    Weather weather;
    Track* track;
    std::vector<Driver*> runningOrder;
    
public:
    Race(int num, Weather w, const std::vector<Driver*>& order, Track* t);
    void sim_race();
    const std::vector<Driver*>& get_runningOrder() const { return runningOrder; }
    Weather get_weather() const {return weather;}
    Track * get_track() const {return track;}
};
#endif
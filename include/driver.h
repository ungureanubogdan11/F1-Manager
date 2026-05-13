#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <vector>
#include <iostream>

class Team; 

class Driver {
    static int next_id;
    int id;
    std::string name;
    Team* team; 
    [[maybe_unused]] double price; 

    int experience, pace, aggressiveness, awareness, tyreManagement;
    int racesWon = 0, poles = 0, points = 0;

public:
    Driver(const std::string& name, Team* team, double price, 
           int exp, int pace, int agg, int aware, int tyre);

    void update(int place);
    bool operator<(const Driver& other) const;

    // Getters
    [[maybe_unused]] int get_id() const { return id; }
    [[maybe_unused]] const std::string& get_name() const { return name; }
    [[maybe_unused]] Team* get_team() const { return team; }
    [[maybe_unused]] int get_points() const { return points; }
    [[maybe_unused]] int get_pace() const { return pace; }
    [[maybe_unused]] int get_experience() const { return experience; }
    [[maybe_unused]] int get_aggressiveness() const { return aggressiveness; }
    [[maybe_unused]] int get_awareness() const { return awareness; }
    [[maybe_unused]] int get_tyreManagement() const { return tyreManagement; }

    friend std::ostream& operator<<(std::ostream& os, const Driver& d);
};

#endif
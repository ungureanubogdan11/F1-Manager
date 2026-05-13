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
    double price; 

    int experience, pace, aggressiveness, awareness, tyreManagement;
    int racesWon = 0, poles = 0, points = 0;

public:
    Driver(const std::string& name, Team* team, double price, 
           int exp, int pace, int agg, int aware, int tyre);

    void update(int place);
    bool operator<(const Driver& other) const;

    // Getters
    int get_id() const { return id; }
    const std::string& get_name() const { return name; }
    Team* get_team() const { return team; }
    int get_points() const { return points; }
    int get_pace() const { return pace; }
    int get_experience() const { return experience; }
    int get_aggressiveness() const { return aggressiveness; }
    int get_awareness() const { return awareness; }
    int get_tyreManagement() const { return tyreManagement; }

    friend std::ostream& operator<<(std::ostream& os, const Driver& d);
};

#endif
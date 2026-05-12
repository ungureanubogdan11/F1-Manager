#ifndef DRIVER_H
#define DRIVER_H

#include <string>
#include <iostream>
#include <vector>

extern const std::vector<int> gp_points;

class Driver {
    int id;
    std::string name;
    int team_id;
    double price; 
    int experience, pace, aggressiveness, awareness, tyreManagement;
    int racesWon = 0, poles = 0, points = 0;

public:
    Driver(int id, const std::string& name, int team_id, double price, 
           int exp, int pace, int agg, int aware, int tyre);

    void update(int place);
    bool operator<(const Driver& other) const;
    
    int get_points() const;
    const std::string& get_name() const;
    int get_id() const;
    int get_team_id() const;
    int get_pace() const;
    int get_experience() const;
    int get_aggressiveness() const;
    int get_awareness() const;
    int get_tyreManagement() const;

    friend std::ostream& operator<<(std::ostream& os, const Driver& d);
};

#endif
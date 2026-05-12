#include "championship.h"
#include <algorithm>
#include <iostream>

void Championship::add_team(Team* team) {
    teamStandings.push_back(team);
    teamLookup[team->get_id()] = team;

    for(Driver* d : team->get_drivers()) {
        driverStandings.push_back(d);
        driverLookup[d->get_id()] = d;
    }
}

void Championship::add_race(Race* race) {
    races.push_back(race);
}

void Championship::update_standings(const Race* race) {
    const auto& results = race->get_runningOrder();
    
    for(int i = 0; i < (int)results.size(); ++i) {
        Driver* d = driverLookup[results[i]->get_id()];
        Team* t = teamLookup[d->get_team_id()];
        
        d->update(i + 1);
        t->update(i + 1);
    }

    std::sort(driverStandings.begin(), driverStandings.end(), [](Driver* a, Driver* b) {
        return *a < *b; 
    });
    
    std::sort(teamStandings.begin(), teamStandings.end(), [](Team* a, Team* b) {
        return *a < *b;
    }); 
}

void Championship::sim_championship() {
    for(Race* race : races) {
        race->sim_race();
        update_standings(race);
        std::cout << *race << "\n";
    }
    print_table();
}

void Championship::print_table() {
    std::cout << "========================================\n";
    std::cout << "       FINAL DRIVER STANDINGS\n";
    std::cout << "========================================\n";
    for(int i = 0; i < (int)driverStandings.size(); ++i) {
        std::cout << i + 1 << ". " << driverStandings[i]->get_name() 
                  << " - " << driverStandings[i]->get_points() << " pts\n";
    }

    std::cout << "\n========================================\n";
    std::cout << "       FINAL TEAM STANDINGS\n";
    std::cout << "========================================\n";
    for(int i = 0; i < (int)teamStandings.size(); ++i) {
        std::cout << i + 1 << ". " << teamStandings[i]->get_name() 
                  << " - " << teamStandings[i]->get_points() << " pts\n";
    }
}
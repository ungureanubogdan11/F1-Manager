#include "championship.h"
#include <iostream>
#include <algorithm>

void Championship::add_team(Team* t) {
    teamStandings.push_back(t);
    for(Driver* d : t->get_drivers()) driverStandings.push_back(d);
}

void Championship::update_standings(const Race* r) {
    const auto& results = r->get_runningOrder();
    for(int i = 0; i < (int)results.size(); ++i) {
        results[i]->update(i + 1);
        results[i]->get_team()->update(i + 1);
    }
    std::sort(driverStandings.begin(), driverStandings.end(), [](Driver* a, Driver* b) { return *a < *b; });
    std::sort(teamStandings.begin(), teamStandings.end(), [](Team* a, Team* b) { return *a < *b; });
}

void Championship::sim_championship() {
    for(Race* r : races) {
        r->sim_race();
        update_standings(r);
    }
    print_table();
}

void Championship::print_table() {
    std::cout << "\n--- STANDINGS ---\n";
    for(auto d : driverStandings) std::cout << *d << "\n";
}
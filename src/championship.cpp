#include "championship.h"
#include <iostream>
#include <algorithm>
#include <random>

const std::vector<int> Championship::gp_points = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};

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
    static std::mt19937 gen(time(0));
    std::uniform_real_distribution<double> chanceDist(0.0, 1.0);
    double upgradeThreshold = 0.2;
    double damageThreshold = 0.4; 

    for(Race* r : races) {
        r->sim_race();
        
        update_standings(r);

        for (Team* t : teamStandings) {
            
            
            
            for (Driver* d : t->get_drivers()) {
                if(chanceDist(gen) < damageThreshold) {
                    std::cout << ">>> Driver " << d->get_name() << " damaged the car! <<<\n";
                    int intensity = computeRI(r->get_track(), d, r);
                    t->processDamage(intensity);
                }
            }

            if (chanceDist(gen) < upgradeThreshold) {
                std::cout << ">>> Team " << t->get_name() << " brought upgrades! <<<\n";
                t->upgradeCar();
            }

            
        }
        
        std::cout << "Round complete.\n";
    }
    
    print_table();
}

void Championship::print_table() {
    std::cout << "\n--- STANDINGS ---\n";
    for(auto d : driverStandings) std::cout << *d << "\n";
}

int computeRI(const Track * track, const Driver * driver, const Race * r) {
    double trackFactor = (track->get_tyreWear() + track->get_topSpeed_weight()) / 2.0;

    double driverFactor = driver->get_aggressiveness() * 0.5;

    double weatherMultiplier = (r->get_weather() == DRY) ? 1.0 : 1.25;

    return static_cast<int>((trackFactor + driverFactor) * weatherMultiplier);
}
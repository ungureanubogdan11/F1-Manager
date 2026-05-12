#include "race.h"
#include <algorithm>
#include <random>
#include <ctime>

Race::Race(int num, Weather w, const std::vector<Driver*>& order, 
           const std::vector<Team*>& teams, Track* t) 
    : raceNumber(num), weather(w), runningOrder(order), track(t) {
    
    for(Team* team : teams) {
        teamLookup[team->get_id()] = team;
    }
}

void Race::sim_race() {
    static std::mt19937 gen(time(0));
    std::vector<std::pair<double, Driver*>> results;

    for (Driver* d : runningOrder) {
        Team* t = teamLookup[d->get_team_id()];
        Car* c = t->get_car();

        double carPower = (c->get_topSpeed() * (track->get_topSpeed_weight() / 100.0)) +
                          (c->get_cornerSpeed() * (track->get_cornerSpeed_weight() / 100.0)) +
                          (c->get_acceleration() * 0.2) + 
                          (c->get_aeroPerformance() * 0.2);

        double driverSkill = (d->get_pace() * 0.5) + 
                             (d->get_experience() * 0.3) + 
                             (d->get_awareness() * 0.2);
        
        double strategyFactor = (track->get_tyreWear() / 10.0) * (d->get_tyreManagement() / 100.0);
        
        double riskSpread = 2.0 + (d->get_aggressiveness() * 0.1); 
        std::normal_distribution<double> riskDistribution(0, riskSpread);
        double riskOutcome = riskDistribution(gen);

        double totalScore = carPower + driverSkill + riskOutcome + strategyFactor;
        results.push_back({totalScore, d});
    }

    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    runningOrder.clear();
    for (const auto& p : results) {
        runningOrder.push_back(p.second);
    }
}

const std::vector<Driver*>& Race::get_runningOrder() const {
    return runningOrder;
}

std::ostream& operator<<(std::ostream& os, const Race& r) {
    os << "--- Race Result: " << r.raceNumber << " ---\n";
    for (int i = 0; i < (int)r.runningOrder.size(); ++i) {
        os << i + 1 << ". " << r.runningOrder[i]->get_name() << "\n";
    }
    return os;
}
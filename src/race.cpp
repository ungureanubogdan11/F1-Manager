#include "race.h"
#include <algorithm>
#include <random>

Race::Race(int num, Weather w, const std::vector<Driver*>& order, Track* t)
    : raceNumber(num), weather(w), track(t), runningOrder(order) {}

void Race::sim_race() {
    static std::mt19937 gen(time(0));
    std::vector<std::pair<double, Driver*>> results;

    for (Driver* d : runningOrder) {
        Car* c = d->get_team()->get_car(); 

        double carPower = c->computeCarPower(track);
        double driverSkill = (d->get_pace() * 0.5) + (d->get_experience() * 0.3);
        
        std::normal_distribution<double> riskDist(0, 2.0 + (d->get_aggressiveness() * 0.1));
        double totalScore = carPower + driverSkill + riskDist(gen);

        results.push_back({totalScore, d});
    }

    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    runningOrder.clear();
    for (auto& p : results) runningOrder.push_back(p.second);
}


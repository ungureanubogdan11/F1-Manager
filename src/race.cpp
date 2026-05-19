#include "race.h"
#include <algorithm>
#include <random>
#include <cmath>

Race::Race(int num, Weather w, const std::vector<Driver*>& order, Track* t)
    : raceNumber(num), weather(w), track(t), runningOrder(order) {}

void Race::sim_race() {
    static std::mt19937 gen(time(0));
    std::vector<std::pair<double, Driver*>> results;

    for (Driver* d : runningOrder) {
        const Car* c = d->get_team()->get_car(); 

        // double carPower = c->computeCarPower(track);
        double carPower = std::sqrt(c->computeCarPower(track)) * 10.0;

        double driverSkill = (d->get_pace() * 1.5) + 
                     (d->get_experience() * 0.8) + 
                     (d->get_tyreManagement() * 0.5);

        double volatility = (d->get_aggressiveness() * 0.2);
        std::normal_distribution<double> riskDist(0, volatility);

        double totalScore = carPower + driverSkill + riskDist(gen);

        results.push_back({totalScore, d});
    }

    std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) {
        return a.first > b.first;
    });

    runningOrder.clear();
    for (const auto& p : results) runningOrder.push_back(p.second);
}

void Race::print_runningOrder() const {
    std::cout << "------------------\n";
    std::cout << "Race number " << raceNumber << ". " << track->get_name() << '\n';
    int pos = 1;
    for(const auto* d : get_runningOrder()) {
        std::cout << pos++ << ". " << d->get_name() << '\n';
    }
    std::cout << "------------------\n";
}
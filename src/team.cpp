#include "team.h"
#include "driver.h"
#include <random>
#include <ctime>

int interval(int val, int st, int dr) {
    if(val < st) return st;
    if(val > dr) return dr;
    return val;
}

Team::Team(int id, const std::string& name, int budget, int design, int research, int pit, int strategy)
    : id(id), name(name), budget(budget), designEfficiency(design), 
      researchPower(research), pitCrewSpeed(pit), strategyIntel(strategy), car(nullptr) {}

Team::~Team() { delete car; }

Team::Team(const Team& other) 
    : id(other.id), name(other.name), drivers(other.drivers), budget(other.budget),
      designEfficiency(other.designEfficiency), researchPower(other.researchPower),
      pitCrewSpeed(other.pitCrewSpeed), strategyIntel(other.strategyIntel),
      racesWon(other.racesWon), poles(other.poles), points(other.points) {
    this->car = other.car ? new Car(*other.car) : nullptr;
}

Team& Team::operator=(const Team& other) {
    if(this == &other) return *this;
    delete car;
    id = other.id;
    name = other.name;
    drivers = other.drivers;
    budget = other.budget;
    designEfficiency = other.designEfficiency;
    researchPower = other.researchPower;
    pitCrewSpeed = other.pitCrewSpeed;
    strategyIntel = other.strategyIntel;
    racesWon = other.racesWon;
    poles = other.poles;
    points = other.points;
    car = other.car ? new Car(*other.car) : nullptr;
    return *this;
}

void Team::build_car() {
    static std::mt19937 gen(time(0));
    std::normal_distribution<double> dist(0, 5.0);

    int ts = interval(int(researchPower + dist(gen)), 60, 99);
    int acc = interval(int((designEfficiency + budget) / 2 + dist(gen)), 60, 99);
    int cs = interval(int((designEfficiency + researchPower + budget) / 3 + dist(gen)), 60, 99);
    int aero = interval(int((researchPower + budget) / 2 + dist(gen)), 60, 99);

    if(car) delete car;
    car = new Car(ts, acc, cs, aero);
}

void Team::update(int place) {
    racesWon += (place == 1);
    if(place <= 10) points += gp_points[place - 1];
}

std::ostream& operator<<(std::ostream& os, const Team& t) {
    os << "Team: " << t.name << " | Pts: " << t.points;
    return os;
}
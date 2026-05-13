#include "team.h"
#include "driver.h"
#include "car.h"
#include "championship.h"
#include "exceptions.h"
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

    if(car) delete car;
    car = new Car(ts, acc, cs);
}

void Team::update(int place) {
    racesWon += (place == 1);
    if(place <= 10) points += Championship::getPointsForPlace(place);
}

std::ostream& operator<<(std::ostream& os, const Team& t) {
    os << "Team: " << t.name << " | Pts: " << t.points;
    return os;
}

void Team::upgradeCar() {
    if (!car) {throw CarNotReadyException(); return;}

    if (budget < 50) {
        throw InsufficientFundsException(50);
    }

    for(Part* p : car->getParts()) {
        p->develop(this->researchPower); 
    }
}

void Team::processDamage(int raceIntensity) {
    if (!car) {throw CarNotReadyException(); return;}

    static std::mt19937 gen(time(0));
    std::uniform_real_distribution<double> damageProb(0.0, 1.0);

    for (Part* p : car->getParts()) {
        double baseDamage = raceIntensity / 10;

        if (Engine* e = dynamic_cast<Engine*>(p)) {
            e->applyDamage(baseDamage * 1.5);
        } 
        else if (AeroKit* a = dynamic_cast<AeroKit*>(p)) {
            if (damageProb(gen) < 0.2) { 
                a->applyDamage(0.1); 
            }
        } 
        else if (Chassis* c = dynamic_cast<Chassis*>(p)) {
            c->applyDamage(baseDamage * 0.5);
        }
    }
}
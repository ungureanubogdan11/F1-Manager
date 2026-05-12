#include "team.h"
#include <random>
#include <ctime>

// Helper
int interval(int val, int st, int dr) {
    if(val < st) return st;
    if(val > dr) return dr;
    return val;
}

Team::Team(int id, const std::string& name, const std::vector<Driver*>& drivers, 
           int budget, int design, int research, int pit, int strategy)
    : id(id), name(name), drivers(drivers), budget(budget), designEfficiency(design),
      researchPower(research), pitCrewSpeed(pit), strategyIntel(strategy), car(nullptr) {}

Team::~Team() { delete car; }

Team::Team(const Team& other) : Team(other.id, other.name, other.drivers, other.budget, 
                                     other.designEfficiency, other.researchPower, 
                                     other.pitCrewSpeed, other.strategyIntel) {
    points = other.points;
    racesWon = other.racesWon;
    if (other.car) car = new Car(*other.car);
}

Team& Team::operator=(const Team& other) {
    if (this == &other) return *this;
    delete car;
    // Copy members... (Implementation omitted for brevity, identical to copy constructor logic)
    return *this;
}

void Team::build_car() {
    static std::mt19937 gen(time(0));
    std::normal_distribution<double> dist(0, 5.0);

    int ts = interval(int(researchPower + dist(gen)), 60, 99);
    int acc = interval(int((designEfficiency + budget) / 2 + dist(gen)), 60, 99);
    int cs = interval(int((designEfficiency + researchPower + budget) / 3 + dist(gen)), 60, 99); // Mapping cs to aero index
    int aero = interval(int((researchPower + budget) / 2 + dist(gen)), 60, 99);

    car = new Car(ts, acc, cs, aero);
}

void Team::update(int place) {
    racesWon += (place == 1);
    if(place <= 10) points += gp_points[place - 1];
}

bool Team::operator<(const Team& other) const { return this->points > other.points; }
const std::vector<Driver*>& Team::get_drivers() const { return drivers; }
const std::string& Team::get_name() const { return name; }
int Team::get_points() const { return points; }
int Team::get_id() const { return id; }
Car* Team::get_car() const { return car; }

std::ostream& operator<<(std::ostream& os, const Team& t) {
    os << "Team: " << t.name << " | Points: " << t.points << "\n";
    if(t.car) os << *t.car;
    return os;
}
#include <iostream>
#include <array>
#include <vector>
#include "include/Example.h"
#include <random>
#include <ctime>
#include <algorithm> 
#include <unordered_map>
// This also works if you do not want `include/`, but some editors might not like it
// #include "Example.h"

const std::vector<int> gp_points = {25, 18, 15, 12, 10, 8, 6, 4, 2, 1};
class Driver {
    int id;
    std::string name;
    int team_id;
    double price; 

    // driving stats from 1-100
    int experience;
    int pace;
    int aggressiveness;
    int awareness;
    int tyreManagement;

    // championship stats
    // int morale = 100;
    int racesWon = 0;
    int poles = 0;
    int points = 0;

    public:
    Driver(const int id, const std::string & name, const int team_id, const double price, const int experience, const int pace, const int aggressiveness, const int awareness, const int tyreManagement) {
        this->id = id;
        this->name = name;
        this->team_id = team_id;
        this->price = price;
        this->experience = experience;
        this->pace = pace;
        this->aggressiveness = aggressiveness;
        this->awareness = awareness;
        this->tyreManagement = tyreManagement;
    };

    friend std::ostream& operator<<(std::ostream& os, const Driver& d) {
        os << "name: " << d.name << '\n';
        os << "points: " << d.points << '\n';
        os << "wins: " << d.racesWon << '\n'; 

        return os;
    }
    

    void update(int place) {
        racesWon += (place == 1);
        poles += (place >= 1 && place <= 3);
        if(place <= 10) points += gp_points[place - 1];
    }

    bool operator < (const Driver & other) const {
        return this->get_points() > other.get_points();
    }

    const int get_points() const {
        return points;
    }

    const std::string & get_name() const {
        return name;
    }

    const int get_id() const {
        return id;
    }

    const int get_team_id() const {
        return team_id;
    }

    const int get_pace() const { return pace; }
    const int get_experience() const { return experience; }
    const int get_aggressiveness() const { return aggressiveness; }
    const int get_awareness() const { return awareness; }
    const int get_tyreManagement() const { return tyreManagement; }

    ~Driver() = default;

};  
class Car {

    // performance stats from 1-100
    int topSpeed;
    int acceleration;
    int cornerSpeed;
    int aeroPerformance;
    // int enginePower;
    
    public:
    Car() = default;

    Car(const int topSpeed, const int acceleration, const int cornerSpeed, const int aeroPerformance) {
        
        this->topSpeed = topSpeed;
        this->acceleration = acceleration;
        this->cornerSpeed = cornerSpeed;
        this->aeroPerformance = aeroPerformance;
        // this->enginePower = enginePower;
    };

    Car(const Car & other) {
        this->topSpeed = other.topSpeed;
        this->acceleration = other.acceleration;
        this->cornerSpeed = other.cornerSpeed;
        this->aeroPerformance = other.aeroPerformance;
        // this->enginePower = other.enginePower;
    };

    friend std::ostream& operator<<(std::ostream& os, const Car& c) {
        os << "Top Speed:    " << c.topSpeed << "\n";
        os << "Acceleration: " << c.acceleration << "\n";
        os << "Cornering:    " << c.cornerSpeed << "\n";
        os << "Aero:         " << c.aeroPerformance << "\n";
        return os;
    }

    Car& operator=(const Car & other) {
        if(this != &other) return *this;

        this->topSpeed = other.topSpeed;
        this->acceleration = other.acceleration;
        this->cornerSpeed = other.cornerSpeed;
        this->aeroPerformance = other.aeroPerformance;
        
        return *this;
    }

    const int get_topSpeed() const { return topSpeed; }
    const int get_cornerSpeed() const { return cornerSpeed; }
    const int get_acceleration() const { return acceleration; }
    const int get_aeroPerformance() const { return aeroPerformance; }

    ~Car() = default;
};

int interval(int val, int st, int dr) {
    if(val < st) return st;
    if(val > dr) return dr;
    return val;
}

class Team {
    int id;
    std::string name;
    std::vector<Driver* > drivers;
    Car* car;
    
    // team stats from 1-100
    int budget;
    int designEfficiency;
    int researchPower;
    int pitCrewSpeed;
    int strategyIntel;

    // championship stats
    int racesWon = 0;
    int poles = 0;
    int points = 0;

    public:
    Team(const int id, const std::string & name, const std::vector<Driver *> & drivers, const int budget, const int designEfficiency, const int researchPower, const int pitCrewSpeed, const int strategyIntel) {
        this->id = id;
        this->name = name;
        this->drivers = drivers;
        this->budget = budget;
        this->designEfficiency = designEfficiency;
        this->researchPower = researchPower;
        this->pitCrewSpeed = pitCrewSpeed;
        this->strategyIntel = strategyIntel;
    };

    friend std::ostream& operator<<(std::ostream& os, const Team& t) {
        os << "Team Name: " << t.name << " (ID: " << t.id << ")\n";
        os << "Points:    " << t.points << " | Wins: " << t.racesWon << "\n";
        os << *t.car; 
        
        return os;
    }

    void build_car() {

        // random car based on each teams stats
        // teams with better stats have a higher chance of building a better car
        static std::mt19937 gen(time(0)); 
        std::normal_distribution<double> dist(0, 5.0); 

        int topSpeed = interval(int(researchPower + dist(gen)), 60, 99);
        int accel = interval(int((designEfficiency + budget) / 2 + dist(gen)), 60, 99);
        int aero = interval(int((designEfficiency + researchPower + budget) / 3 + dist(gen)), 60, 99);
        int engine = interval(int((researchPower + budget) / 2 + dist(gen)), 60, 99);

        car = new Car(topSpeed, accel, aero, engine);
    }

    void add_driver(Driver* const d) {
        drivers.push_back(d);
    }

    void update(int place) {
        racesWon += (place == 1);
        poles += (place >= 1 && place <= 3);
        if(place <= 10) points += gp_points[place - 1];
    }

    bool operator < (const Team & other) const {
        return this->get_points() > other.get_points();
    }

    const std::vector<Driver *>& get_drivers() const {
        return drivers;
    }

    const std::string & get_name() const {
        return name;
    }

    const int get_points() const {
        return points;
    }

    const int get_id() const {
        return id;
    }

    Car * const get_car() const {
        return car;
    }

    ~Team() {
        delete car;
    }
};

class Track {
    std::string name;
    int laps;

    // track stats from 1-100
    int overtakeDifficulty;
    int tyreWear;
    int rainProbability;
    
    // importance of:
    int topSpeed; 
    int cornerSpeed;

    public:
    Track() = default;

    Track(const std::string & name, const int laps, const int overtakeDifficulty, const int tyreWear, const int rainProbability, const int topSpeed, const int cornerSpeed) {
        this->name = name;
        this->laps = laps;
        this->overtakeDifficulty = overtakeDifficulty;
        this->tyreWear = tyreWear;
        this->rainProbability = rainProbability;
        this->topSpeed = topSpeed;
        this->cornerSpeed = cornerSpeed;
    };

    friend std::ostream& operator<<(std::ostream& os, const Track& tr) {
        os << "Track: " << tr.name << " (" << tr.laps << " Laps)\n";
        os << "Difficulty: " << tr.overtakeDifficulty << " | Tyre Wear: " << tr.tyreWear << "\n";
        os << "Weights -> Top Speed: " << tr.topSpeed << " | Cornering: " << tr.cornerSpeed << "\n";
        return os;
    }

    const int get_topSpeed_weight() const { return topSpeed; }
    const int get_cornerSpeed_weight() const { return cornerSpeed; }
    const int get_tyreWear() const { return tyreWear; }

    ~Track() = default;
};

enum Weather {
    DRY,
    WET,
    RAINING
};

class Race {
    int raceNumber;
    int currentLap;
    Weather weather;
    Track * track;
    std::vector<Driver* > runningOrder;
    std::vector<Team * > teams;
    std::vector<int> gaps;
    std::unordered_map<int, Team* > teamLookup;

    public: 
    Race(const int raceNumber, const Weather weather, const std::vector<Driver* > & runningOrder, const std::vector<Team* > & teams, Track * const track) {
        this->raceNumber = raceNumber;
        this->weather = weather;
        this->runningOrder = runningOrder;
        this->teams = teams;
        this->track = track;
        
        for(Team * const t : teams) {
            teamLookup[t->get_id()] = t;
        }
    };

    friend std::ostream& operator<<(std::ostream& os, const Race& r) {
        os << "Race Number: " << r.raceNumber << " | Weather: ";
        if (r.weather == DRY) os << "Dry";
        else if (r.weather == WET) os << "Wet";
        else os << "Raining";
        
        for (int i = 0; i < r.runningOrder.size(); ++i) {
            os << i + 1 << ". " << r.runningOrder[i]->get_name() << "\n";
        }
        return os;
    }

    const std::vector<Driver* > & get_runningOrder() const {
        return runningOrder;
    }

    void sim_race() {
        static std::mt19937 gen(time(0));
        std::normal_distribution<double> luck(0, 8.0);
        std::vector<std::pair<double, Driver*>> results;

        for (Driver* d : runningOrder) {
            Team* t = teamLookup[d->get_team_id()];
            const Car* c = t->get_car();

            double carPower = (c->get_topSpeed() * (track->get_topSpeed_weight() / 100.0)) +
                              (c->get_cornerSpeed() * (track->get_cornerSpeed_weight() / 100.0)) +
                              (c->get_acceleration() * 0.2) + (c->get_aeroPerformance() * 0.2);

            double driverSkill = (d->get_pace() * 0.5) + (d->get_experience() * 0.3) + (d->get_awareness() * 0.2);
            
            double strategyFactor = (track->get_tyreWear() / 10.0) * (d->get_tyreManagement() / 100.0);
            
            double riskSpread = 2.0 + (d->get_aggressiveness() * 0.1); 
            std::normal_distribution<double> riskDistribution(0, riskSpread);
            double riskOutcome = riskDistribution(gen);

            if (riskOutcome < 0) {
                riskOutcome *= (1.0 - (d->get_awareness() / 200.0)); 
            }

            double totalScore = carPower + driverSkill + riskOutcome;
            results.push_back({totalScore, d});
        }

        std::sort(results.begin(), results.end(), [](const auto& a, const auto& b) { return a.first > b.first; });

        runningOrder.clear();
        for (auto& p : results) runningOrder.push_back(p.second);
    }

    ~Race() = default;
};

class Championship {
    std::vector<Driver*> driverStandings;
    std::vector<Team*> teamStandings;
    std::vector<Race*> races;
    int currentRound;

    std::unordered_map<int, Driver* > driverLookup;
    std::unordered_map<int, Team* > teamLookup;

    public:
    
    void add_team(Team* team) {
        teamStandings.push_back(team);
        teamLookup[team->get_id()] = team;

        for(Driver * d : team->get_drivers()) {
            driverStandings.push_back(d);
            driverLookup[d->get_id()] = d;
        }
        
    }

    void update_standings(Race * const race) {
        auto results = race->get_runningOrder();
        for(int i = 0; i < results.size(); ++i) {
            Driver* d = driverLookup[results[i]->get_id()];
            Team* t = teamLookup[d->get_team_id()];
            d->update(i + 1);
            t->update(i + 1);
        }

        sort(driverStandings.begin(), driverStandings.end(), [](Driver* a, Driver* b) {
            return *a < *b;
        });
        sort(teamStandings.begin(), teamStandings.end(), [](Team* a, Team* b) {
            return *a < *b;
        }); 

    }

    void add_race(Race * const race) {
        races.push_back(race);
    }

    void print_table() {
        std::cout << "Driver's Standings:\n";
        for(int i = 0; i < driverStandings.size(); ++i) {
            std::cout << "Driver: " << driverStandings[i]->get_name();
            std::cout << "   Points: " << driverStandings[i]->get_points() << '\n';  
        }

        std::cout << "\n";
        std::cout << "Team's Standings:\n";
        for(int i = 0; i < teamStandings.size(); ++i) {
            std::cout << "Team: " << teamStandings[i]->get_name();
            std::cout << "   Points: " << teamStandings[i]->get_points() << '\n';
        }
        
    }

    void sim_championship() {
        for(Race * const race : races) {
            race->sim_race();
            update_standings(race);
        }

        print_table();
    }
};

int main() {
    Championship f1;

    Driver* d1 = new Driver(1, "Charles Leclerc", 101, 50.0, 91, 98, 85, 90, 82);
    Driver* d2 = new Driver(2, "Lewis Hamilton", 101, 55.0, 99, 94, 80, 98, 95);
    std::vector<Driver*> ferrariDrivers = {d1, d2};
    Team* t1 = new Team(101, "Scuderia Ferrari", ferrariDrivers, 100, 98, 98, 95, 92);
    t1->build_car(); 

    

    Driver* d3 = new Driver(3, "Max Verstappen", 102, 55.0, 92, 99, 90, 90, 92);
    Driver* d4 = new Driver(4, "Liam Lawson", 102, 15.0, 60, 81, 75, 70, 70);
    std::vector<Driver*> redbullDrivers = {d3, d4};
    Team* t2 = new Team(102, "Red Bull Racing", redbullDrivers, 95, 90, 92, 98, 95);
    t2->build_car();

    Driver* d5 = new Driver(5, "Lando Norris", 103, 40.0, 80, 93, 80, 82, 85);
    Driver* d6 = new Driver(6, "Oscar Piastri", 103, 30.0, 85, 92, 85, 88, 85);
    std::vector<Driver*> mclarenDrivers = {d5, d6};
    Team* t3 = new Team(103, "McLaren", mclarenDrivers, 85, 92, 88, 85, 85);
    t3->build_car();

    f1.add_team(t1);
    f1.add_team(t2);
    f1.add_team(t3);

    Track* bahrain = new Track("Sakhir", 57, 40, 60, 5, 70, 50);
    Track* jeddah = new Track("Jeddah", 50, 80, 10, 5, 90, 80);
    Track* melbourne = new Track("Albert Park", 58, 50, 40, 30, 60, 70);

    std::vector<Driver*> allParticipants = {d1, d2, d3, d4, d5, d6};
    std::vector<Team*> allTeams = {t1, t2, t3};

    Race* r1 = new Race(1, DRY, allParticipants, allTeams, bahrain);
    Race* r2 = new Race(2, DRY, allParticipants, allTeams, jeddah);
    Race* r3 = new Race(3, RAINING, allParticipants, allTeams, melbourne);

    f1.add_race(r1);
    f1.add_race(r2);
    f1.add_race(r3);

    f1.sim_championship();

    std::cout << *d1 << '\n';
    std::cout << *d2 << '\n';
    std::cout << *t1 << '\n';

    for(auto d : allParticipants) delete d;
    for(auto t : allTeams) delete t;



    return 0;
}
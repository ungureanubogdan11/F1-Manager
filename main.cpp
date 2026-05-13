#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "championship.h"
#include "exceptions.h"
#include "race.h"

int main() {
    Championship f1_season;
    std::vector<Team*> Teams;
    std::vector<Driver*> Drivers;
    std::vector<Race*> Races;
    std::vector<Track*> Tracks;

    std::ifstream inputFile("data.txt");
    
    try {
        if (!inputFile.is_open()) {
            throw RacingException("Nu s-a putut deschide fisierul data.txt!");
        }

        std::string type;
        while (inputFile >> type) {
            if (type == "TEAM") {
                std::string name;
                int b, d, r, p, s; // budget, design, research, pit, strategy
                
                inputFile >> name >> b >> d >> r >> p >> s;

                Team* t = new Team(name, b, d, r, p, s);
                
                for(char &c : name) if(c == '_') c = ' ';
                
                t->build_car(); 
                Teams.push_back(t);
                f1_season.add_team(t);

            } else if (type == "DRIVER") {
                std::string name;
                int teamIdx;
                double price;
                int exp, pace, agg, aware, tyre;
                
                inputFile >> name >> teamIdx >> price >> exp >> pace >> agg >> aware >> tyre;
                
                for(char &c : name) if(c == '_') c = ' ';

                if (teamIdx < 0) {
                    throw InvalidAttributeException("ID Echipa invalid pentru pilotul " + name);
                }

                Driver* drv = new Driver(name, Teams[teamIdx], price, exp, pace, agg, aware, tyre);
                
                Drivers.push_back(drv);
                Teams[teamIdx]->add_driver(drv);
                f1_season.add_driver(drv);

            } else if (type == "RACE_DATA") {
                int raceNum;
                std::string weatherStr, trackName;
                int laps, diff, wear, rain, ts, cs;

                if (!(inputFile >> raceNum >> weatherStr >> trackName >> laps >> diff >> wear >> rain >> ts >> cs)) {
                    throw RacingException("Format invalid pentru RACE_DATA!");
                }

                Race::Weather w;
                if (weatherStr == "DRY") {
                    w = Race::DRY;
                } else if (weatherStr == "WET") {
                    w = Race::WET;
                } else if (weatherStr == "RAINING") {
                    w = Race::RAINING;
                } 

                for(char &c : trackName) if(c == '_') c = ' ';

                Track* t = new Track(trackName, laps, diff, wear, rain, ts, cs);

                Race* r = new Race(raceNum, w, Drivers, t);

                Races.push_back(r);
                Tracks.push_back(t);
                f1_season.add_race(r);
            }
        }
        inputFile.close();

        f1_season.sim_championship();
        
    } catch (const RacingException& e) {
        std::cerr << "EROARE JOC: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "EROARE CRITICA: " << e.what() << std::endl;
    }

    for (auto d : Drivers) delete d;
    for (auto t : Teams) delete t;
    for (auto tr: Tracks) delete tr;
    for (auto r : Races) delete r;

    return 0;
}
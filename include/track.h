#ifndef TRACK_H
#define TRACK_H
#include <string>

class Track {
    std::string name;
    int laps, overtakeDifficulty, tyreWear, rainProbability, topSpeed, cornerSpeed;

public:
    Track(const std::string& name, int laps, int diff, int wear, int rain, int ts, int cs)
        : name(name), laps(laps), overtakeDifficulty(diff), tyreWear(wear), 
          rainProbability(rain), topSpeed(ts), cornerSpeed(cs) {}

    int get_topSpeed_weight() const { return topSpeed; }
    int get_cornerSpeed_weight() const { return cornerSpeed; }
    int get_tyreWear() const { return tyreWear; }
    const std::string& get_name() const { return name; }
};
#endif
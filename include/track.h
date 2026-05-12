#ifndef TRACK_H
#define TRACK_H
#include <string>
#include <iostream>

class Track {
    std::string name;
    int laps, overtakeDifficulty, tyreWear, rainProbability, topSpeed, cornerSpeed;
public:
    Track(const std::string& name, int laps, int diff, int wear, int rain, int ts, int cs);
    int get_topSpeed_weight() const { return topSpeed; }
    int get_cornerSpeed_weight() const { return cornerSpeed; }
    int get_tyreWear() const { return tyreWear; }
    friend std::ostream& operator<<(std::ostream& os, const Track& tr);
};
#endif
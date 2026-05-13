#ifndef PART_H
#define PART_H

#include <iostream>
#include <vector>

class Part {
protected:
    double modifier; 

    virtual void updateModifier(int teamStat) = 0;

public:
    Part() : modifier(1.0) {}
    virtual ~Part() = default;

    virtual Part* clone() const = 0;

    void develop(int teamStat) {
        updateModifier(teamStat); 
    }

    double getModifier() const { return modifier; }

    virtual void display(std::ostream& os) const = 0;

    friend std::ostream& operator<<(std::ostream& os, const Part& p) {
        p.display(os);
        os << " [x" << p.modifier << "]";
        return os;
    }

    void applyDamage(double severity) {
        modifier -= severity;
        if (modifier < 0.5) modifier = 0.5;
    }
};

class Engine : public Part {
public:
    Engine() : Part() {}
    Part* clone() const override { return new Engine(*this); }
    void updateModifier(int stat) override { modifier += (stat / 1000.0); }
    void display(std::ostream& os) const override { os << "Type: Power Unit"; }
};

class AeroKit : public Part {
public:
    AeroKit() : Part() {}
    Part* clone() const override { return new AeroKit(*this); }
    void updateModifier(int stat) override { modifier += (stat / 1200.0); }
    void display(std::ostream& os) const override { os << "Type: Aero System"; }
};

class Chassis : public Part {
public:
    Chassis() : Part() {}
    Part* clone() const override { return new Chassis(*this); }
    void updateModifier(int stat) override { modifier += (stat / 1500.0); }
    void display(std::ostream& os) const override { os << "Type: Chassis Frame"; }
};

class Gearbox : public Part {
public:
    Gearbox() : Part() {}
    Part* clone() const override { return new Gearbox(*this); }
    void updateModifier(int stat) override { modifier += (stat / 1400.0); }
    void display(std::ostream& os) const override { os << "Transmission System"; }
};

#endif
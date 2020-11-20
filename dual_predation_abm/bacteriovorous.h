#ifndef BACTERIOVOROUS_H
#define BACTERIOVOROUS_H

#include "bacteria.h"

/* ------------ Create Bacteriovorus class. ------------ */
// Bacteriovorus is derived from Bacteria.
class Bacteriovorous: public Bacteria
{
public:
    // Default constructor.
    Bacteriovorous() : Bacteria()
    {

    }
    // Constructor to take in the x and y coordinates of the bacteriovorus, the bacteriovorus' ID, and the bacteriovorus' name.
    Bacteriovorous(int i, int j, int num, std::string org) : Bacteria(i, j, num, org)
    {

    }
    // Constructor to take in the x and y coordinates of the bacteriovorus, the bacteriovorus' ID,
    //  the bacteriovorus' name, and the mortality rate of the bacteriovorus.
    Bacteriovorous(int i, int j, int num, std::string org, double attack_rate, double mortality_rate) :
        Bacteria(i, j, num, org), attack_rate(attack_rate), mortality_rate(mortality_rate)
    {
        this->attack_rate = attack_rate;
        this->mortality_rate = mortality_rate;
    }

    void set_attack_rate(double attack_rate)
    {
        this->attack_rate = attack_rate;
    }

    double get_attack_rate()
    {
        return this->attack_rate;
    }

    double attack_rate;         // Rate at which the bacteriovorous cell attacks Ecoli cells.
    double mortality_rate;      // The rate at which bacteriovorus cells dies.

};

#endif

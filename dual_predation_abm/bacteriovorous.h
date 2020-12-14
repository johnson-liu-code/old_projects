#ifndef BACTERIOVOROUS_H
#define BACTERIOVOROUS_H

#include "bacteria.h"

/* ------------ Bacteriovorus class. ------------ */
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
    //  the bacteriovorus' name, the bacteriovorous' attack rate, the bdelloplast incubation period,
    //  and the bacteriovorous' mortality rate.
    Bacteriovorous(int i, int j, int num, std::string org, double attack_rate, int bdelloplast_incubation_period,
        double mortality_rate) : Bacteria(i, j, num, org), attack_rate(attack_rate),
        bdelloplast_incubation_period(bdelloplast_incubation_period), mortality_rate(mortality_rate)
    {
        // How often the bacteriovorous carries out a successful attack on an Ecoli cell.
        this->attack_rate = attack_rate;
        // The time it takes for a bdelloplast to burst and release new bacteriovorous cells into the node.
        this->bdelloplast_incubation_period = bdelloplast_incubation_period;
        // How often the bacteriovori dies from old age.
        this->mortality_rate = mortality_rate;
    }

    // Set the attack rate for the bacteriovorous.
    void set_attack_rate(double attack_rate)
    {
        this->attack_rate = attack_rate;
    }
    // Get the attack rate for the bacteriovorous.
    double get_attack_rate()
    {
        return this->attack_rate;
    }
    // Set the bdelloplast incubation period.
    void set_bdelloplast_incubation_period(int bdelloplast_incubation_period)
    {
        this->bdelloplast_incubation_period = bdelloplast_incubation_period;
    }


    double attack_rate;                 // Rate at which the bacteriovorous cell attacks Ecoli cells.
    int bdelloplast_incubation_period;  // How long it takes for a bdelloplast cell to burst.
    double mortality_rate;              // The rate at which bacteriovorus cells dies.

};

#endif

#ifndef BACTERIOVOROUS_H
#define BACTERIOVOROUS_H

#include "bacteria.h"

/* ------------ Bacteriovorous class. ------------ */
// Bacteriovorous is derived from Bacteria.
class Bacteriovorous: public Bacteria
{
public:
    // Default constructor.
    Bacteriovorous() : Bacteria()
    {

    }
    // Constructor to take in the x and y coordinates of the bacteriovorous cell.
    Bacteriovorous(int i, int j) : Bacteria(i, j)
    {

    }
    // Constructor to take in the x and y coordinates of the bacteriovorous, the
    //  bacteriovorous' attack rate, the bdelloplast incubation period, and the
    //  bacteriovorous' mortality rate.
    Bacteriovorous(int i, int j, double attack_rate, int bdelloplast_incubation_period,
        double mortality_rate) : Bacteria(i, j), attack_rate(attack_rate),
        bdelloplast_incubation_period(bdelloplast_incubation_period)
    {
        // How often the bacteriovorous carries out a successful attack on an Ecoli cell.
        this->attack_rate = attack_rate;
        // The time it takes for a bdelloplast to burst and release new bacteriovorous cells into the node.
        this->bdelloplast_incubation_period = bdelloplast_incubation_period;
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
    int age = 0;

};

#endif

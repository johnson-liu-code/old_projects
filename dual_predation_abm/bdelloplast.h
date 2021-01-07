#ifndef BDELLOPLAST_H
#define BDELLOPLAST_H

#include "ecoli.h"

/* ------------ Create Bdelloplast class. ------------ */
// Bdelloplast is derived from Ecoli.
class Bdelloplast: public Ecoli
{
public:
    // Default constructor.
    Bdelloplast() : Ecoli()
    {

    }

    Bdelloplast(int i, int j) : Ecoli(i, j)
    {

    }

    // Constructor to take in the x and y coordinates of the bdelloplast.
    Bdelloplast(int i, int j, double attack_rate, int bdelloplast_incubation_period)
        : Ecoli(i, j), bacteriovorous_attack_rate(attack_rate),
        bdelloplast_incubation_period(bdelloplast_incubation_period)
    {
        this->bacteriovorous_attack_rate = attack_rate;
        this->bdelloplast_incubation_period = bdelloplast_incubation_period;
        this->time_alive = 0;
    }


    double bacteriovorous_attack_rate;
    int bdelloplast_incubation_period;
    int time_alive;
    double bacteriovorous_mortality_rate;
};

#endif

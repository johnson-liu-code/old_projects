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

    Bdelloplast(int i, int j, int num, std::string org) : Ecoli(i, j, num, org)
    {

    }

    // Constructor to take in the x and y coordinates of the bdelloplast, the bdelloplast's ID, and the bdelloplast's name.
    Bdelloplast(int i, int j, int num, std::string org, double attack_rate, int bdelloplast_incubation_period,
        double mortality_rate) : Ecoli(i, j, num, org), bacteriovorous_attack_rate(attack_rate),
        bdelloplast_incubation_period(bdelloplast_incubation_period), bacteriovorous_mortality_rate(mortality_rate)
    {
        this->bacteriovorous_attack_rate = attack_rate;
        this->bdelloplast_incubation_period = bdelloplast_incubation_period;
        this->time_alive = 0;
        this->bacteriovorous_mortality_rate = mortality_rate;
    }


    double bacteriovorous_attack_rate;
    int bdelloplast_incubation_period;
    int time_alive;
    double bacteriovorous_mortality_rate;
};

#endif

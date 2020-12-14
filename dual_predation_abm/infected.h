#ifndef INFECTED_H
#define INFECTED_H

#include "ecoli.h"

/* ------------ Infected class. ------------ */
// Infected is derived from Ecoli.
class Infected: public Ecoli
{
public:
    // Default constructor.
    Infected() : Ecoli()
    {

    }
    // Constructor to take in the x and y coordinates of the infected, the infected's ID, and the infected's name.
    Infected(int i, int j, int num, std::string org) : Ecoli(i, j, num, org)
    {

    }
    Infected(int i, int j, int num, std::string org, double attack_rate, int infected_incubation_period)
        : Ecoli(i, j, num, org), virus_attack_rate(attack_rate), infected_incubation_period(infected_incubation_period)
    {
        this->virus_attack_rate = attack_rate;
        this->infected_incubation_period = infected_incubation_period;
        this->time_alive = 0;
    }

    double virus_attack_rate;
    int infected_incubation_period;
    int time_alive;
};

#endif

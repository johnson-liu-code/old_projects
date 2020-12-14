#ifndef VIRUS_H
#define VIRUS_H

#include "agent.h"

/* ------------ Virus class. ------------ */
// Virus is derived from Agent.
class Virus: public Agent
{
public:
    // Default constructor.
    Virus() : Agent()
    {

    }
    // Constructor to take in the x and y coordinates of the virus, the virus' ID, and the virus' name.
    Virus(int i, int j, int num, std::string org) : Agent(i, j, num, org)
    {

    }
    // Constructor to take in the x and y coordinates of the virus, the virus' ID, and the virus' name.
    Virus(int i, int j, int num, std::string org, double attack_rate, int infected_incubation_period)
        : Agent(i, j, num, org), attack_rate(attack_rate), infected_incubation_period(infected_incubation_period)
    {
        // How often the virus carries out a successful attack on an Ecoli cell.
        this->attack_rate = attack_rate;
        // The time it takes for an infected Ecoli cell to burst and release new virus' into the node.
        this->infected_incubation_period = infected_incubation_period;
    }

    // Set the attack rate for the virus.
    void set_attack_rate(double attack_rate)
    {
        this->attack_rate = attack_rate;
    }
    // Get the attack rate for the virus.
    double get_attack_rate()
    {
        return this->attack_rate;
    }
    // Set the infected incubation period.
    void set_infected_incubation_period(int infected_incubation_period)
    {
        this->infected_incubation_period = infected_incubation_period;
    }


    double attack_rate;                 // Rate at which the virus attacks Ecoli cells.
    int infected_incubation_period;



};

#endif

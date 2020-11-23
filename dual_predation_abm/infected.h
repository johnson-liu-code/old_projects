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
};

#endif

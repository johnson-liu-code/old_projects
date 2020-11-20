#ifndef VIRUS_H
#define VIRUS_H

#include "agent.h"

/* ------------ Create Virus class. ------------ */
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
};

#endif

#ifndef BACTERIA_H
#define BACTERIA_H

#include "agent.h"

/* ------------ Create Bacteria class. ------------ */
// Bacteria is derived from Agent.
class Bacteria: public Agent
{
public:
    // Default constructor.
    Bacteria() : Agent()
    {

    }
    // Constructor to take in the x and y coordinates of the bacteria, the bacteria's ID, and the bacteria's name.
    Bacteria(int i, int j, int num, std::string org) : Agent(i, j, num, org)
    {

    }

};

#endif

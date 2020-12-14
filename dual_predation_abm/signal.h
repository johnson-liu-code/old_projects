#ifndef SIGNAL_H
#define SIGNAL_H

#include "agent.h"

/* ------------ Signal class. ------------ */
// Signal is derived from Agent.
class Signal: public Agent
{
public:
    // Default constructor.
    Signal() : Agent()
    {

    }
    // Constructor to take in the x and y coordinates of the signal, the signal's ID, and the signal's name.
    Signal(int i, int j, int num, std::string org) : Agent(i, j, num, org)
    {

    }

};

#endif

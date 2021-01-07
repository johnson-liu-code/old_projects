#ifndef AGENT_H
#define AGENT_H

#include<string>

/* ------------ Agent class. ------------ */
class Agent
{
public:
    // Default constructor.
    Agent()
    {

    }
    // Constructor to take in the x and y coordinates of the agent.
    Agent(int i, int j)
    {
        this->i = i;
        this->j = j;
        // All agents start out unmoved. This variable keeps track of whether or not an agent has moved
        //  when in the part of the simulation where agents and particles move from their node to
        //  neighboring nodes.
        this->moved = false;
    }

    // Print the agent's name and location.
    void print_me()
    {
        std::cout << "node: " << this->i << "_" << this->j << std::endl;
        std::cout << "##########################################################################" << std::endl;
    }

    // Set the x coordinate of the agent.
    void set_i(int i)
    {
        this->i = i;
    }
    // Set the y coordinate of the agent.
    void set_j(int j)
    {
        this->j = j;
    }
    // Return the agent's x location.
    int get_i()
    {
        return this->i;
    }
    // Return the agent's y location.
    int get_j()
    {
        return this->j;
    }

    int i, j;      // x and y location of the agent.
    bool moved;         // Whether or not the agent has moved during a step in the simulation.
};

#endif

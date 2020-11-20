#ifndef AGENT_H
#define AGENT_H

#include<string>

/* ------------ Create Agent class. ------------ */
class Agent
{
public:
    // Default constructor.
    Agent()
    {
        // this->org = "generic";
    }
    // Constructor to take in the x and y coordinates of the agent, the agent's ID, and the agent's name.
    Agent(int i, int j, int num, std::string org)
    {
        this->i = i;
        this->j = j;
        this->num = num;
        this->org = org;
        this->moved = false;
    }

    // Print the agent's name and location.
    void print_me()
    {
        std::cout << "Organism: " << this->org << std::endl;
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
    // Set the agent's ID.
    void set_num(int num)
    {
        this->num = num;
    }
    // Set the agent's name.
    void set_org(std::string org)
    {
        this->org = org;
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
    // Return the agent's ID.
    int get_num()
    {
        return this->num;
    }
    // Return the agent's name.
    std::string get_org()
    {
        return this->org;
    }

    int i, j, num;      // x and y location and agent ID.
    std::string org;    // Agent name. (Includes the type of organism, the agent's location, and the agent's ID)
    bool moved;
};

#endif

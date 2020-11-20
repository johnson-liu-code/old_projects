#ifndef NODE_H
#define NODE_H

#include<string>
#include<vector>
#include<random>

#include "ecoli.h"
#include "bdelloplast.h"
#include "infected.h"
#include "virus.h"
#include "bacteriovorous.h"

/* ------------ Create Node class. ------------ */
// A lattice of nodes is used to contain the agent vectors and the functions that act on the agents.
class node
{
public:
    // Default constructor.
    node()
    {

    }

    // Constructor to take in the node's x and y location and the initial amounts of nutrients, ecoli cells,
    //  bdelloplasts, infected, viruses, and bacteriovori in the node.
    node(int i, int j, int init_nutrients, int init_ecoli_in_node, int init_bdelloplast_in_node,
        int init_infected_in_node, int init_virus_in_node, int init_bacteriovorous_in_node)
    {
        this->i = i;
        this->j = j;
        this->nutrients = init_nutrients;
        // Initial amount of bacteriovorous resistance conversion signals in the node.
        this->signal = 0;

        this->num_ecoli = init_ecoli_in_node;
        this->num_bdelloplast = init_bdelloplast_in_node;
        this->num_infected = init_infected_in_node;
        this->num_virus = init_virus_in_node;
        this->num_bacteriovorous = init_bacteriovorous_in_node;

        std::string org;
        // String that contains the x and y location of the node. Used in the naming of the individual agents.
        std::string mid_string = std::to_string(i) + "_" + std::to_string(j) + "_";
        int num;

        // Create vector of ecoli cells.
        for (int n = 0; n < init_ecoli_in_node; n++)
        {
            org = "Ecoli_" + mid_string + std::to_string(n);
            Ecoli ecoli(i, j, n, org);
            ecoli_list.push_back(ecoli);
        }

        // Create vector of viruses.
        for (int n = 0; n < init_virus_in_node; n++)
        {
            org = "Virus_" + mid_string + std::to_string(n);
            Virus virus(i, j, n, org);
            virus_list.push_back(virus);
        }

        // Create vector of bacteriovorous cells.
        for (int n = 0; n < init_bacteriovorous_in_node; n++)
        {
            org = "bacteriovorous_" + mid_string + std::to_string(n);
            Bacteriovorous bacteriovorous(i, j, n, org);
            bacteriovorous_list.push_back(bacteriovorous);
        }

        // Create vector of bdelloplast cells.
        for (int n = 0; n < init_bdelloplast_in_node; n++)
        {
            org = "Bdelloplast_" + mid_string + std::to_string(n);
            Bdelloplast bdelloplast(i, j, n, org);
            bdelloplast_list.push_back(bdelloplast);
        }

        // Create vector of infected ecoli cells.
        for (int n = 0; n < init_infected_in_node; n++)
        {
            org = "Infected_" + mid_string + std::to_string(n);
            Infected infected(i, j, n, org);
            ecoli_list.push_back(infected);
        }
    }

    // Various functions.
    void set_bacteriovorous_cell_attack_rate(int location, double attack_rate);
    double get_bacteriovorous_cell_attack_rate(int location);
    void bacteriovorous_attack_prey();
    void remove_ecoli(int index);
    void add_ecoli(Ecoli ecoli);
    int get_next_available_num(std::string org_type);

    // Return the number of ecoli cells in the node.
    int get_num_ecoli()
    {
        return this->num_ecoli;
    }
    int get_num_bacteriovorous()
    {
        return this->num_bacteriovorous;
    }

    // These print functions are mostly just for debugging.
    void print_ecoli_list()
    {
        for (int n = 0; n < this->num_ecoli; n++)
        {
            this->ecoli_list[n].print_me();
        }
    }
    void print_virus_list()
    {
        for (int n = 0; n < this->num_virus; n++)
        {
            this->virus_list[n].print_me();
        }
    }
    void print_bacteriovorous_list()
    {
        for (int n = 0; n < this->num_bacteriovorous; n++)
        {
            this->bacteriovorous_list[n].print_me();
        }
    }

// private:
    int i, j, nutrients, signal;
    int num_ecoli, num_bdelloplast, num_infected, num_virus, num_bacteriovorous;

    std::vector<Ecoli> ecoli_list;
    std::vector<Bdelloplast> bdelloplast_list;
    std::vector<Infected> infected_list;
    std::vector<Virus> virus_list;
    std::vector<Bacteriovorous> bacteriovorous_list;
};


void node::set_bacteriovorous_cell_attack_rate(int location, double attack_rate)
{
    this->bacteriovorous_list[location].set_attack_rate(attack_rate);
}
double node::get_bacteriovorous_cell_attack_rate(int location)
{
    return this->bacteriovorous_list[location].get_attack_rate();
}

// Function to iterate through the bacteriovorous in the node and determine whether they are successful
//  in entering ecoli cells.
void node::bacteriovorous_attack_prey()
{

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<> dis(0, 1);
    std::uniform_int_distribution<int> uni(0, this->num_ecoli);

    double rand_num;
    int selected_position;

    // Iterate over the bacteriovori in the node.
    for (int n = 0; n < this->num_bacteriovorous; n++)
    {
        rand_num = dis(gen);
        std::cout << rand_num << std::endl;
        if (rand_num <= this->bacteriovorous_list[n].get_attack_rate())
        {
            std::cout << "yes" << std::endl;
            selected_position = uni(gen);
        }





        // bacteriovorous_list[n].print_me();
        // std::cout << dis(gen) << std::endl;
        // std::cout << uni(gen) << std::endl;

    }
}

// Function to add an ecoli cell to the ecoli vector.
void node::add_ecoli(Ecoli ecoli)
{
    this->ecoli_list.push_back(ecoli);
    // Increment the number of ecoli in the node.
    this->num_ecoli++;
}

// Function to remove an ecoli cell from the ecoli vector based on the intended index.
void node::remove_ecoli(int index)
{
    this->ecoli_list.erase(ecoli_list.begin() + index);
    // Decrement the number of ecoli in the node.
    this->num_ecoli--;
}

// Function to return the next available ID for new agents.
int node::get_next_available_num(std::string org_type)
{
    int n, y;

    if (org_type == "Ecoli")
    {
        for (int x = 0; x < this->num_ecoli; x++)
        {
            y = this->ecoli_list[x].get_num();
            if (n != y)
            {
                return n;
            }
            n++;
        }
    }
    return n;
}

#endif

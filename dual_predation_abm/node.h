#ifndef NODE_H
#define NODE_H

#include<string>
#include<vector>
#include<random>
#include<numeric>
#include<algorithm>

#include "ecoli.h"
#include "bdelloplast.h"
#include "infected.h"
#include "virus.h"
#include "bacteriovorous.h"

/* ------------ Create Node class. ------------ */
// A lattice of nodes is used to contain the agent vectors and the signal and nutrient particles.
class node
{
public:
    // Default constructor.
    node()
    {

    }

    // Constructor to take in the node's x and y location as well as the initial amounts of nutrients, Ecoli cells,
    //  bdelloplasts, infected, viruses, and bacteriovori in the node.
    node(int i, int j, int init_nutrients, int init_ecoli_in_node, int init_bdelloplast_in_node,
        int init_infected_in_node, int init_virus_in_node, int init_bacteriovorous_in_node)
    {
        this->i = i;
        this->j = j;
        this->nutrients = init_nutrients;

        std::string org;
        // String that contains the x and y location of the node. Used in the naming of the individual agents.
        std::string mid_string = std::to_string(i) + "_" + std::to_string(j) + "_";
        int num;

        // Create a vector of Ecoli cells.
        for (int n = 0; n < init_ecoli_in_node; n++)
        {
            org = "Ecoli_" + mid_string + std::to_string(n);
            Ecoli ecoli(i, j, n, org);
            this->add_ecoli(ecoli);
        }
        // Create a vector of bacteriovorous cells.
        for (int n = 0; n < init_bacteriovorous_in_node; n++)
        {
            org = "bacteriovorous_" + mid_string + std::to_string(n);
            Bacteriovorous bacteriovorous(i, j, n, org);
            this->add_bacteriovorous(bacteriovorous);
        }
        // Create a vector of bdelloplast cells.
        for (int n = 0; n < init_bdelloplast_in_node; n++)
        {
            org = "Bdelloplast_" + mid_string + std::to_string(n);
            Bdelloplast bdelloplast(i, j, n, org);
            this->add_bdelloplast(bdelloplast);
        }
        // Create a vector of viruses.
        for (int n = 0; n < init_virus_in_node; n++)
        {
            std::cout << "here" << std::endl;
            org = "Virus_" + mid_string + std::to_string(n);
            Virus virus(i, j, n, org);
            this->add_virus(virus);
        }
        // Create a vector of infected ecoli cells.
        for (int n = 0; n < init_infected_in_node; n++)
        {
            org = "Infected_" + mid_string + std::to_string(n);
            Infected infected(i, j, n, org);
            this->add_infected(infected);
        }
    }

    // Various functions.
    void set_bacteriovorous_cell_attack_rate(int location, double attack_rate);
    double get_bacteriovorous_cell_attack_rate(int location);
    void set_bdelloplast_incubation_period(int location, int bdelloplast_incubation_period);

    void ecoli_consume_nutrients();
    void iterate_ecoli_mutate_die_reproduce();

    void bacteriovorous_attack_prey();
    void convert_ecoli_to_bdelloplast(int selected_ecoli_position, Bacteriovorous bacteriovorous);
    void burst_bdelloplasts();

    void virus_infect_prey();
    void convert_ecoli_to_infected(int selected_ecoli_position);

    void remove_bacteriovorous(int index);
    void remove_many_bacteriovori(std::vector<int> bacteriovorous_removal_list);
    void remove_ecoli(int index);
    void remove_many_ecoli(std::vector<int> ecoli_removal_list);
    void remove_bdelloplast(int index);
    void remove_virus(int index);
    void remove_many_viri(std::vector<int> virus_removal_list);

    void add_ecoli(Ecoli ecoli);
    void add_bdelloplast(Bdelloplast bdelloplast);
    void add_bacteriovorous(Bacteriovorous bacteriovorous);
    void add_virus(Virus virus);
    void add_infected(Infected infected);

    int get_next_available_num(std::string org_type);

    // Return the number of ecoli cells in the node.
    int get_num_ecoli()
    {
        return this->num_ecoli;
    }
    // Return the number of bacteriovorous cells in the node.
    int get_num_bacteriovorous()
    {
        return this->num_bacteriovorous;
    }
    // Return the number of bdelloplast cells in the node.
    int get_num_bdelloplast()
    {
        return this->num_bdelloplast;
    }
    // Return the number of virus' in the node.
    int get_num_virus()
    {
        return this->num_virus;
    }
    // Return the number of infected E. coli cells.
    int get_num_infected()
    {
        return this->num_infected;
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

    // Class members.
    int i, j, nutrients, signal = 0;
    int num_ecoli = 0;
    int num_bdelloplast = 0;
    int num_infected = 0;
    int num_virus = 0;
    int num_bacteriovorous = 0;
    float phage_resistance_mutation_probability = 1;
    float phage_resistance_reversion_probability = .5;

    // Vectors that hold the agent objects.
    std::vector<Ecoli> ecoli_list;
    std::vector<Bdelloplast> bdelloplast_list;
    std::vector<Infected> infected_list;
    std::vector<Virus> virus_list;
    std::vector<Bacteriovorous> bacteriovorous_list;
};

void node::ecoli_consume_nutrients()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uni(0, 10);

    // std::vector<int> index_vector;
    // for (int i = 0; i < this->num_ecoli; i++)
    // {
    //     index_vector.push_back(i);
    // }
    std::vector<int> index_vector(this->num_ecoli);
    std::iota(std::begin(index_vector), std::end(index_vector), 0);

    std::random_shuffle(index_vector.begin(), index_vector.end());

    int nutrients_consumed;

    for (int i = 0; i < this->num_ecoli; i++)
    {
        if (this->nutrients <= 0)
        {
            break;
        }
        else
        {
            std::cout << "index vector element: " << index_vector[i] << std::endl;
            nutrients_consumed = uni(gen);
            this->nutrients -= nutrients_consumed;
            this->ecoli_list[index_vector[i]].add_energy(nutrients_consumed);
            if (this->nutrients <= 0)
            {
                this->ecoli_list[index_vector[i]].remove_energy(std::abs(this->nutrients));
            }
            std::cout << "nutrients: " << this->nutrients << std::endl;
        }
    }
}

void node::iterate_ecoli_mutate_die_reproduce()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // dis(min, max) gives a uniform random number between min and max.
    std::uniform_real_distribution<> dis(0, 1);
    float rand_num;

    std::vector<int> ecoli_reproduce_list;
    std::vector<int> ecoli_death_list;

    int energy;

    for (int i = 0; i < this->num_ecoli; i++)
    {
        rand_num = dis(gen);

        if (rand_num < this->phage_resistance_mutation_probability)
        {
            this->ecoli_list[i].phage_resistant = true;
        }
        if (rand_num < this->phage_resistance_reversion_probability)
        {
            this->ecoli_list[i].phage_resistant = false;
        }

        energy = this->ecoli_list[i].energy;

        if (energy <= 0)
        {
            ecoli_death_list.push_back(i);
        }
        else if (energy >= 20)
        {
            ecoli_reproduce_list.push_back(i);
        }
    }

    this->remove_many_ecoli(ecoli_death_list);

    int i, j, num;
    std::string org;
    bool phage_resistant, bacteriovorous_resistant;
    Ecoli ecoli;

    for (int j = 0; j < ecoli_reproduce_list.size(); j++)
    {
        ecoli = this->ecoli_list[ecoli_reproduce_list[j]];
        i = ecoli.i;
        j = ecoli.j;
        org = ecoli.org;
        num = this->get_next_available_num(org);
        phage_resistant = ecoli.phage_resistant;
        bacteriovorous_resistant = ecoli.bacteriovorous_resistant;

        Ecoli ecoli(i, j, num, org, phage_resistant, bacteriovorous_resistant);
        ecoli.add_energy(10);
        this->ecoli_list[ecoli_reproduce_list[j]].remove_energy(10);

        this->add_ecoli(ecoli);
    }
}

// Set the attack rate for a specific bacteriovorous cell in the node.
void node::set_bacteriovorous_cell_attack_rate(int location, double attack_rate)
{
    this->bacteriovorous_list[location].set_attack_rate(attack_rate);
}
// Get the attack rate for a specific bacteriovorous cell in the node.
double node::get_bacteriovorous_cell_attack_rate(int location)
{
    return this->bacteriovorous_list[location].attack_rate;
}
// Set the bdelloplast incubation period for a specific bacteriovorous cell in the node.
void node::set_bdelloplast_incubation_period(int location, int bdelloplast_incubation_period)
{
    this->bacteriovorous_list[location].set_bdelloplast_incubation_period(bdelloplast_incubation_period);
}

// Add a bdelloplast cell to the node and remove the affected Ecoli cell.
void node::convert_ecoli_to_bdelloplast(int selected_ecoli_position, Bacteriovorous bacteriovorous)
{
    std::string org = "bdelloplast";

    // Create new bdelloplast cell that retains information about the bacteriovorous
    //  that invaded the Ecoli cell.
    Bdelloplast bdelloplast(this->i, this->j, this->ecoli_list[selected_ecoli_position].num,
        org, bacteriovorous.bdelloplast_incubation_period,
        bacteriovorous.attack_rate, bacteriovorous.mortality_rate);

    // Add the bdelloplast cell to the bdelloplast vector.
    this->add_bdelloplast(bdelloplast);
    // Remove the Ecoli cell from the Ecoli vector.
    this->remove_ecoli(selected_ecoli_position);
}
// Function to iterate through the bacteriovori cells in the node and determine whether
//  they are successful at invading Ecoli cells.
void node::bacteriovorous_attack_prey()
{
    // Set up random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());

    // dis(min, max) gives a uniform random number between min and max.
    std::uniform_real_distribution<> dis(0, 1);

    // Vector to store the positions of the bacteriovori that are to be removed from the node.
    std::vector<int> bacteriovorous_remove_list;

    // Declare a variable to store a random number.
    double rand_num;
    // Declare a variable to store the position of the selected Ecoli to be invaded.
    int selected_ecoli_position;

    // Iterate over the bacteriovori in the node.
    for (int n = 0; n < this->num_bacteriovorous; n++)
    {
        // If there are no remaining Ecoli cells in the node, break out of the iteration.
        if (this->num_ecoli == 0)
        {
            break;
        }

        // Get random number between 0 and 1.
        rand_num = dis(gen);

        // Check to see if the random number is equal to or less than the bacteriovorous
        //  attack rate.
        if (rand_num <= this->bacteriovorous_list[n].attack_rate)
        {
            // Generate random integer to select an Ecoli cell to attack.
            std::uniform_int_distribution<int> uni(0, this->num_ecoli - 1);
            selected_ecoli_position = uni(gen);
            std::cout << "selected_ecoli_position: " << selected_ecoli_position << std::endl;

            // Check to see if the Ecoli cell is resistant to the bacteriovorous.
            if (this->ecoli_list[selected_ecoli_position].bacteriovorous_resistant == false )
            {
                // Remove the Ecoli cell from the node and add a new bdelloplast cell.
                this->convert_ecoli_to_bdelloplast(selected_ecoli_position,
                    this->bacteriovorous_list[n]);

                // Add the location of the bacteriovorous to the vector to keep track
                //  of which bacteriovorous cell to remove at the end of the iteration.
                bacteriovorous_remove_list.push_back(n);
            }
        }
    }

    // Remove all of the bacteriovorous cells tagged to be removed.
    // for (int k = 0; k < bacteriovorous_remove_list.size(); k++ )
    // {
    //     this->remove_bacteriovorous(bacteriovorous_remove_list[k]);
    // }
    this->remove_many_bacteriovori(bacteriovorous_remove_list);
}
// Function to destroy bdelloplast cells and to release new bacteriovori cells into the node.
void node::burst_bdelloplasts()
{
    // Set up random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uni(0, 10);

    // Create vector to store the positions of the bdelloplasts marked for destruction.
    std::vector<int> bdelloplast_burst_list;
    Bdelloplast bdelloplast;

    // Declare variables.
    double bacteriovorous_attack_rate;
    int bdelloplast_incubation_period;
    double bacteriovorous_mortality_rate;

    int num = 0;
    std::string org = "place_holder";

    // Iterate over the bdelloplast cells in the node.
    for (int n = 0; n < this->num_bdelloplast; n++)
    {
        // Check to see if the amount of time that the bdelloplast has been alive is equal
        //  to its incubation period.
        if (this->bdelloplast_list[n].time_alive == this->bdelloplast_list[n].bdelloplast_incubation_period)
        {
            // Add the bdelloplast's position to the destruction vector.
            bdelloplast_burst_list.push_back(n);
        }
        else
        {
            // Increment the amount of time that the bdelloplast has been alive.
            this->bdelloplast_list[n].time_alive++;
        }
    }

    // Iterate over the positions of the bdelloplasts marked for destruction.
    for (int k = 0; k < bdelloplast_burst_list.size(); k++)
    {
        // Assign various values to variables.
        bdelloplast = this->bdelloplast_list[bdelloplast_burst_list[k]];
        bacteriovorous_attack_rate = bdelloplast.bacteriovorous_attack_rate;
        bdelloplast_incubation_period = bdelloplast.bdelloplast_incubation_period;
        bacteriovorous_mortality_rate = bdelloplast.bacteriovorous_mortality_rate;

        // Create a new bacteriovorous cell (should allow for multiple cells to be
        //  created).
        Bacteriovorous bacteriovorous(this->i, this->j, num, org,
            bacteriovorous_attack_rate, bdelloplast_incubation_period,
            bacteriovorous_mortality_rate);

        // Add the new bacteriovorous cell to the node.
        this->add_bacteriovorous(bacteriovorous);
        // Remove the bdelloplast cell.
        this->remove_bdelloplast(bdelloplast_burst_list[k]);

        // Add a random number of signal molecules to the node.
        this->signal += uni(gen);
    }
}

// Function to convert an Ecoli cell to an infected cell.
void node::convert_ecoli_to_infected(int selected_ecoli_position)
{
    std::string org = "virus";
    // Create new infected cell.
    Infected infected(this->i, this->j, this->ecoli_list[selected_ecoli_position].num, org);
    // Add the infected cell to the node.
    this->add_infected(infected);
    // Remove the Ecoli cell from the node.
    this->remove_ecoli(selected_ecoli_position);
}
// Function to have viruses infect Ecoli cells.
void node::virus_infect_prey()
{
    // Set up random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());

    // Vector to store the locations of the viruses to be removed.
    std::vector<int> virus_remove_list;

    // Declare a variable to store the position of the selected Ecoli cell.
    int selected_ecoli_position;

    // Iterate over the viruses in the node.
    for (int n = 0; n < this->num_virus; n++)
    {
        // If there are no Ecoli cells left in the node, break out of the iteration.
        if (this->num_ecoli == 0)
        {
            break;
        }

        // Generate random integer to select an Ecoli cell to attack.
        std::uniform_int_distribution<int> uni(0, this->num_ecoli - 1);
        selected_ecoli_position = uni(gen);
        std::cout << "selected_ecoli_position: " << selected_ecoli_position << std::endl;

        // Check to see if the Ecoli cell is resistant to attacks by the virus.
        if (this->ecoli_list[selected_ecoli_position].phage_resistant == false )
        {
            // Remove the Ecoli cell from the node and add an infected cell to the node.
            this->convert_ecoli_to_infected(selected_ecoli_position);

            // Record the location of the virus to be removed.
            virus_remove_list.push_back(n);
        }
    }

    // Remove all of the viruses tagged to be removed.
    // for (int k = 0; k < virus_remove_list.size(); k++ )
    // {
    //     this->remove_virus(virus_remove_list[k]);
    // }
    this->remove_many_viri(virus_remove_list);
}

// Function to remove an Ecoli cell from the Ecoli vector based on the intended index.
void node::remove_ecoli(int index)
{
    this->ecoli_list.erase(this->ecoli_list.begin() + index);
    // Decrement the number of ecoli in the node.
    this->num_ecoli--;
}
void node::remove_many_ecoli(std::vector<int> ecoli_removal_list)
{
    std::sort(ecoli_removal_list.begin(), ecoli_removal_list.end(), std::greater<>());

    for (int i = 0; i < ecoli_removal_list.size(); i++)
    {
        std::cout << "removing ecoli " << std::endl;
        this->remove_ecoli(ecoli_removal_list[i]);
    }
}
// Function to remove a bacteriovorous cell from the bacteriovorous vector based on the intended index.
void node::remove_bacteriovorous(int index)
{
    this->bacteriovorous_list.erase(this->bacteriovorous_list.begin() + index);
    // Decrement the number of bacteriovori in the node.
    this->num_bacteriovorous--;
}
void node::remove_many_bacteriovori(std::vector<int> bacteriovorous_removal_list)
{
    std::sort(bacteriovorous_removal_list.begin(), bacteriovorous_removal_list.end(), std::greater<>());

    for (int i = 0; i < bacteriovorous_removal_list.size(); i++)
    {
        this->remove_bacteriovorous(bacteriovorous_removal_list[i]);
    }
}
// Function to remove a bdelloplast cell from the bdelloplast vector based on the intended index.
void node::remove_bdelloplast(int index)
{
    this->bdelloplast_list.erase(this->bdelloplast_list.begin() + index);
    // Decrement the number of bdelloplasts in the node.
    this->num_bdelloplast--;
}
// Function to remove virus from the virus vector based on the intended index.
void node::remove_virus(int index)
{
    this->virus_list.erase(this->virus_list.begin() + index);
    // Decrement the number of viruses in the node.
    this->num_virus--;
}
void node::remove_many_viri(std::vector<int> virus_removal_list)
{
    std::sort(virus_removal_list.begin(), virus_removal_list.end(), std::greater<>());

    for (int i = 0; i < virus_removal_list.size(); i++)
    {
        this->remove_virus(virus_removal_list[i]);
    }
}
// Function to add an Ecoli cell to the Ecoli vector.
void node::add_ecoli(Ecoli ecoli)
{
    this->ecoli_list.push_back(ecoli);
    // Increment the number of Ecoli in the node.
    this->num_ecoli++;
}
// Function to add a bacteriovorous cell to the bacteriovorous vector.
void node::add_bacteriovorous(Bacteriovorous bacteriovorous)
{
    this->bacteriovorous_list.push_back(bacteriovorous);
    // Increment the number of bacteriovori in the node.
    this->num_bacteriovorous++;
}
// Function to add an bdelloplast cell to the bdelloplast vector.
void node::add_bdelloplast(Bdelloplast bdelloplast)
{
    this->bdelloplast_list.push_back(bdelloplast);
    // Increment the number of bdelloplasts in the node.
    this->num_bdelloplast++;
}
// Function to add a virus cell to the virus vector.
void node::add_virus(Virus virus)
{
    this->virus_list.push_back(virus);
    // Increment the number of viruses in the node.
    this->num_virus++;
}
// Function to add an infected Ecoli cell to the infected vector.
void node::add_infected(Infected infected)
{
    this->infected_list.push_back(infected);
    // Increment the number of infected Ecoli cells in the node.
    this->num_infected++;
}

// Function to return the next available ID number for new agents.
int node::get_next_available_num(std::string org_type)
{
    int n, y;

    if (org_type == "Ecoli")
    {
        for (int x = 0; x < this->num_ecoli; x++)
        {
            y = this->ecoli_list[x].num;
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

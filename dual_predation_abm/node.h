#ifndef NODE_H
#define NODE_H

#include<string>
#include<vector>
#include<random>
#include<numeric>
#include<algorithm>

#include "agent.h"
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
    node(int i, int j, double init_nutrients, int init_ecoli_in_node, int init_bdelloplast_in_node,
        int init_infected_in_node, int init_virus_in_node, int init_bacteriovorous_in_node,
        double phage_resistance_mutation_probability, double phage_resistance_reversion_probability,
        double bacteriovorous_resistance_mutation_probability,
        double bacteriovorous_resistance_reversion_probability, double ecoli_max_nutrient_consumption,
        double ecoli_exist_energy_cost, double ecoli_reproduce_energy_cost, int max_signal_released,
        int max_bacteriorovorous_released, int max_virus_released, int bacteriovorous_mortality_period)
    {
        this->i = i;
        this->j = j;
        this->nutrients = init_nutrients;

        this->ecoli_max_nutrient_consumption = ecoli_max_nutrient_consumption;
        this->ecoli_exist_energy_cost = ecoli_exist_energy_cost;
        this->ecoli_reproduce_energy_cost = ecoli_reproduce_energy_cost;

        this->bacteriovorous_mortality_period = bacteriovorous_mortality_period;

        this->max_signal_released = max_signal_released;
        this->max_bacteriorovorous_released = max_bacteriorovorous_released;
        this->max_virus_released = max_virus_released;

        this->phage_resistance_mutation_probability = phage_resistance_mutation_probability;
        this->phage_resistance_reversion_probability = phage_resistance_reversion_probability;
        this->bacteriovorous_resistance_mutation_probability = bacteriovorous_resistance_mutation_probability;
        this->bacteriovorous_resistance_reversion_probability = bacteriovorous_resistance_reversion_probability;

        // Create a vector of Ecoli cells.
        for (int n = 0; n < init_ecoli_in_node; n++)
        {
            Ecoli ecoli(i, j);
            this->add_ecoli(ecoli);
        }
        // Create a vector of bacteriovorous cells.
        for (int n = 0; n < init_bacteriovorous_in_node; n++)
        {
            Bacteriovorous bacteriovorous(i, j);
            this->add_bacteriovorous(bacteriovorous);
        }
        // Create a vector of bdelloplast cells.
        for (int n = 0; n < init_bdelloplast_in_node; n++)
        {
            Bdelloplast bdelloplast(i, j);
            this->add_bdelloplast(bdelloplast);
        }
        // Create a vector of viruses.
        for (int n = 0; n < init_virus_in_node; n++)
        {
            Virus virus(i, j);
            this->add_virus(virus);
        }
        // Create a vector of infected ecoli cells.
        for (int n = 0; n < init_infected_in_node; n++)
        {
            Infected infected(i, j);
            this->add_infected(infected);
        }
    }

    // Various functions.
    void ecoli_consume_nutrients();
    void iterate_ecoli_die_mutate_reproduce();

    double return_sigmoid_probability();

    void set_bacteriovorous_attack_rate(int location, double attack_rate);
    double get_bacteriovorous_attack_rate(int location);
    void set_bdelloplast_incubation_period(int location, int bdelloplast_incubation_period);

    void set_virus_attack_rate(int location, double attack_rate);
    double get_virus_attack_rate(int location);
    void set_infected_incubation_period(int location, int infected_incubation_period);

    void bacteriovorous_attack_prey();
    void bacteriovorous_mortality();
    void convert_ecoli_to_bdelloplast(int selected_ecoli_position, Bacteriovorous bacteriovorous);
    void burst_bdelloplasts();

    void virus_infect_prey();
    void convert_ecoli_to_infected(int selected_ecoli_position, Virus virus);
    void burst_infected();

    void demove_organisms();

    void remove_bacteriovorous(int index);
    void remove_many_bacteriovori(std::vector<int> bacteriovorous_removal_list);
    void remove_ecoli(int index);
    void remove_many_ecoli(std::vector<int> ecoli_removal_list);
    void remove_bdelloplast(int index);
    void remove_many_bdelloplasts(std::vector<int> bdelloplast_removal_list);
    void remove_virus(int index);
    void remove_many_viri(std::vector<int> virus_removal_list);
    void remove_infected(int index);
    void remove_many_infected(std::vector<int> infected_removal_list);

    void add_ecoli(Ecoli ecoli);
    void add_bdelloplast(Bdelloplast bdelloplast);
    void add_bacteriovorous(Bacteriovorous bacteriovorous);
    void add_virus(Virus virus);
    void add_infected(Infected infected);
    // void add_particle(P particle);

    // template <typename P>
    // void add_particle(P particle)
    // {
    //     if (particle.org == "ecoli")
    //     {
    //         Ecoli ecoli = particle;
    //         node::add_ecoli(ecoli);
    //     }
    //     // elif ()
    // }

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
    int i, j, sigmoid_inflection_point, signal = 0;
    int max_signal_released, max_bacteriorovorous_released, max_virus_released;
    int bacteriovorous_mortality_period;
    double ecoli_exist_energy_cost, ecoli_reproduce_energy_cost;
    double nutrients, ecoli_max_nutrient_consumption;
    int num_ecoli = 0;
    int num_bdelloplast = 0;
    int num_infected = 0;
    int num_virus = 0;
    int num_bacteriovorous = 0;
    double phage_resistance_mutation_probability;
    double phage_resistance_reversion_probability;
    double bacteriovorous_resistance_mutation_probability;
    double bacteriovorous_resistance_reversion_probability;

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

    // std::vector<int> index_vector;
    // for (int i = 0; i < this->num_ecoli; i++)
    // {
    //     index_vector.push_back(i);
    // }
    std::vector<int> index_vector(this->num_ecoli);
    std::iota(std::begin(index_vector), std::end(index_vector), 0);
    std::random_shuffle(index_vector.begin(), index_vector.end());

    double rand_num;
    double nutrients_consumed;
    std::uniform_real_distribution<> dis(0, this->ecoli_max_nutrient_consumption);

    for (int i = 0; i < this->num_ecoli; i++)
    {
        if (this->nutrients <= 0)
        {
            break;
        }
        else
        {
            rand_num = dis(gen);
            nutrients_consumed = std::min(this->nutrients, rand_num);

            this->nutrients -= nutrients_consumed;
            this->ecoli_list[index_vector[i]].energy += nutrients_consumed;
        }
    }
}
double node::return_sigmoid_probability()
{
    return 1 / ( 1 + exp(-(this->signal - this->sigmoid_inflection_point) ) );
}
void node::iterate_ecoli_die_mutate_reproduce()
{
    std::random_device rd;
    std::mt19937 gen(rd());

    // dis(min, max) gives a uniform random number between min and max.
    std::uniform_real_distribution<> dis(0, 1);
    float rand_num;

    std::vector<int> ecoli_reproduce_list;
    std::vector<int> ecoli_death_list;

    double sigmod_probability;
    double adjusted_rand;
    int energy;
    bool bacteriovorous_resistant;

    // Iterate over the Ecoli cells to kill off cells without energy energy and
    //  to perform mutations.
    for (int i = 0; i < this->num_ecoli; i++)
    {
        // Get the energy of the Ecoli cell.
        energy = this->ecoli_list[i].energy;
        energy = energy - this->ecoli_exist_energy_cost;
        // Ecoli cell death due to lack of energy;
        if (energy <= 0)
        {
            ecoli_death_list.push_back(i);
        }
        else
        {
            // Phage resistance mutations.
            rand_num = dis(gen);
            if (this->ecoli_list[i].bacteriovorous_resistant == false)
            {
                if(this->ecoli_list[i].phage_resistant == false)
                {
                    sigmod_probability = this->return_sigmoid_probability();
                    adjusted_rand = rand_num + sigmod_probability;
                    if (adjusted_rand <= this->bacteriovorous_resistance_mutation_probability)
                    {
                        this->ecoli_list[i].bacteriovorous_resistant = true;
                        this->signal -= this->max_signal_released;
                    }
                }
            }
            else if(this->ecoli_list[i].bacteriovorous_resistant == true)
            {
                if (rand_num <= this->bacteriovorous_resistance_reversion_probability)
                {
                    this->ecoli_list[i].bacteriovorous_resistant = false;
                }
            }

            rand_num = dis(gen);
            if (this->ecoli_list[i].phage_resistant == false)
            {
                if (this->ecoli_list[i].bacteriovorous_resistant == false)
                {
                    if (rand_num <= this->phage_resistance_mutation_probability)
                    {
                        this->ecoli_list[i].phage_resistant = true;
                    }
                }
            }
            else if(this->ecoli_list[i].phage_resistant == true)
            {
                if (rand_num <= this->phage_resistance_reversion_probability)
                {
                    this->ecoli_list[i].phage_resistant = false;
                }
            }
        }
        // Make a list of all of the Ecoli cells that have enough energy to reproduce.
        if (energy >= 20)
        {
            // Only allow the Ecoli cell to reproduce if it is not
            //  bacteriovorous resistant.
            bacteriovorous_resistant = this->ecoli_list[i].bacteriovorous_resistant;
            if (bacteriovorous_resistant == false)
            {
                ecoli_reproduce_list.push_back(i);
            }
        }
    }

    this->remove_many_ecoli(ecoli_death_list);
    int i, j;
    bool phage_resistant;
    Ecoli ecoli;
    double split_energy;

    // Have the Ecoli cells reproduce.
    for (int k = 0; k < ecoli_reproduce_list.size(); k++)
    {
        ecoli = this->ecoli_list[ecoli_reproduce_list[k]];
        i = ecoli.i;
        j = ecoli.j;
        phage_resistant = ecoli.phage_resistant;
        bacteriovorous_resistant = false;
        energy = ecoli.energy - this->ecoli_reproduce_energy_cost;
        split_energy = energy/2;
        ecoli.energy = split_energy;
        Ecoli ecoli(i, j, phage_resistant, bacteriovorous_resistant);
        // ecoli.add_energy(split_energy);
        // this->ecoli_list[ecoli_reproduce_list[j]].remove_energy(split_energy);

        this->add_ecoli(ecoli);
    }
}

// Set the attack rate for a specific bacteriovorous cell in the node.
void node::set_bacteriovorous_attack_rate(int location, double attack_rate)
{
    this->bacteriovorous_list[location].set_attack_rate(attack_rate);
}
// Get the attack rate for a specific bacteriovorous cell in the node.
double node::get_bacteriovorous_attack_rate(int location)
{
    return this->bacteriovorous_list[location].attack_rate;
}
// Set the bdelloplast incubation period for a specific bacteriovorous cell in the node.
void node::set_bdelloplast_incubation_period(int location, int bdelloplast_incubation_period)
{
    this->bacteriovorous_list[location].set_bdelloplast_incubation_period(bdelloplast_incubation_period);
}

// Set the attack rate for a specific virus cell in the node.
void node::set_virus_attack_rate(int location, double attack_rate)
{
    this->virus_list[location].set_attack_rate(attack_rate);
}
// Get the attack rate for a specific virus cell in the node.
double node::get_virus_attack_rate(int location)
{
    return this->virus_list[location].attack_rate;
}
// Set the bdelloplast incubation period for a specific bacteriovorous cell in the node.
void node::set_infected_incubation_period(int location, int infected_incubation_period)
{
    this->virus_list[location].set_infected_incubation_period(infected_incubation_period);
}

// Add a bdelloplast cell to the node and remove the affected Ecoli cell.
void node::convert_ecoli_to_bdelloplast(int selected_ecoli_position, Bacteriovorous bacteriovorous)
{
    // Create new bdelloplast cell that retains information about the bacteriovorous
    //  that invaded the Ecoli cell.
    Bdelloplast bdelloplast(this->i, this->j, bacteriovorous.bdelloplast_incubation_period,
        bacteriovorous.attack_rate);

    // Add the bdelloplast cell to the bdelloplast vector.
    this->add_bdelloplast(bdelloplast);
    // Remove the Ecoli cell from the Ecoli vector.
    this->remove_ecoli(selected_ecoli_position);
}
void node::bacteriovorous_mortality()
{
    std::vector<int> kill_bacteriovorous_list;
    for (int i = 0; i < this->num_bacteriovorous; i++)
    {
        if (this->bacteriovorous_list[i].age == this->bacteriovorous_mortality_period)
        {
            kill_bacteriovorous_list.push_back(i);
        }
        else
        {
            // std::cout << this->bacteriovorous_list[i].age << std::endl;
            this->bacteriovorous_list[i].age += 1;
        }
    }

    this->remove_many_bacteriovori(kill_bacteriovorous_list);
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
    std::uniform_int_distribution<int> uni1(1, this->max_signal_released);
    std::uniform_int_distribution<int> uni2(0, this->max_bacteriorovorous_released);

    // Create vector to store the positions of the bdelloplasts marked for destruction.
    std::vector<int> bdelloplast_burst_list;
    Bdelloplast bdelloplast;

    // Declare variables.
    double bacteriovorous_attack_rate;
    int bdelloplast_incubation_period;
    double bacteriovorous_mortality_rate;

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

    int num_bacteriovorous_added = uni2(gen);
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
        Bacteriovorous bacteriovorous(this->i, this->j, bacteriovorous_attack_rate,
            bdelloplast_incubation_period, bacteriovorous_mortality_rate);
        num_bacteriovorous_added = uni2(gen);
        // Add the new bacteriovorous cell(s) to the node.
        for (int i = 0; i < num_bacteriovorous_added; i++)
        {
            this->add_bacteriovorous(bacteriovorous);
        }

        // Add a random number of signal molecules to the node.
        this->signal += uni1(gen);
    }

    this->remove_many_bdelloplasts(bdelloplast_burst_list);
}

// Function to convert an Ecoli cell to an infected cell.
void node::convert_ecoli_to_infected(int selected_ecoli_position, Virus virus)
{
    // Create new infected cell.

    Infected infected(this->i, this->j, virus.infected_incubation_period,
        virus.attack_rate);

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

    // dis(min, max) gives a uniform random number between min and max.
    std::uniform_real_distribution<> dis(0, 1);

    // Vector to store the locations of the viruses to be removed.
    std::vector<int> virus_remove_list;

    // Declare a variable to store a random number.
    double rand_num;
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

        // Get random number between 0 and 1.
        rand_num = dis(gen);

        if (rand_num <= this->virus_list[n].attack_rate)
        {
            // Generate random integer to select an Ecoli cell to attack.
            std::uniform_int_distribution<int> uni(0, this->num_ecoli - 1);
            selected_ecoli_position = uni(gen);

            // Check to see if the Ecoli cell is resistant to attacks by the virus.
            if (this->ecoli_list[selected_ecoli_position].phage_resistant == false )
            {
                // Remove the Ecoli cell from the node and add an infected cell to the node.
                this->convert_ecoli_to_infected(selected_ecoli_position,
                    this->virus_list[n]);

                // Record the location of the virus to be removed.
                virus_remove_list.push_back(n);
            }
        }
    }

    // Remove all of the viruses tagged to be removed.
    // for (int k = 0; k < virus_remove_list.size(); k++ )
    // {
    //     this->remove_virus(virus_remove_list[k]);
    // }
    this->remove_many_viri(virus_remove_list);
}

void node::burst_infected()
{
    // Set up random number generator.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> uni(0, this->max_virus_released);

    // Create vector to store the positions of the infected Ecoli cells marked for destruction.
    std::vector<int> infected_burst_list;
    Infected infected;

    // Declare variables.
    double virus_attack_rate;
    int infected_incubation_period;
    int num_virus_released;

    // Iterate over the infected Ecoli cells in the node.
    for (int n = 0; n < this->num_infected; n++)
    {
        // Check to see if the amount of time that the infected Ecoli cell has been alive is equal
        //  to its incubation period.
        if (this->infected_list[n].time_alive == this->infected_list[n].infected_incubation_period)
        {
            // Add the infected Ecoli cell's position to the destruction vector.
            infected_burst_list.push_back(n);
        }
        else
        {
            // Increment the amount of time that the infected Ecoli cell has been alive.
            this->infected_list[n].time_alive++;
        }
    }

    // Iterate over the positions of the infected Ecoli cells marked for destruction.
    for (int k = 0; k < infected_burst_list.size(); k++)
    {
        // Assign various values to variables.
        infected = this->infected_list[infected_burst_list[k]];
        virus_attack_rate = infected.virus_attack_rate;
        infected_incubation_period = infected.infected_incubation_period;

        // Create a new virus (should allow for multiple individuals to be
        //  created).
        Virus virus(this->i, this->j, virus_attack_rate, infected_incubation_period);

        num_virus_released = uni(gen);

        // Add the new virus to the node.
        for (int i = 0; i < num_virus_released; i++)
        {
            this->add_virus(virus);
        }
        // Remove the infected Ecoli cell.
        // this->remove_infected(infected_burst_list[k]);
    }

    this->remove_many_infected(infected_burst_list);
}

void node::demove_organisms()
{
    for (int i = 0; i < this->num_ecoli; i++)
    {
        this->ecoli_list[i].moved = false;
    }
    for (int i = 0; i < this->num_bacteriovorous; i++)
    {
        this->bacteriovorous_list[i].moved = false;
    }
    for (int i = 0; i < this->num_virus; i++)
    {
        this->virus_list[i].moved = false;
    }

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
void node::remove_many_bdelloplasts(std::vector<int> bdelloplast_removal_list)
{
    std::sort(bdelloplast_removal_list.begin(), bdelloplast_removal_list.end(), std::greater<>());

    for (int i = 0; i < bdelloplast_removal_list.size(); i++)
    {
        this->remove_bdelloplast(bdelloplast_removal_list[i]);
    }
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
void node::remove_infected(int index)
{
    this->infected_list.erase(this->infected_list.begin() + index);
    // Decrement the number of infected Ecoli cells in the node.
    this->num_infected--;
}
void node::remove_many_infected(std::vector<int> infected_removal_list)
{
    std::sort(infected_removal_list.begin(), infected_removal_list.end(), std::greater<>());

    for (int i = 0; i < infected_removal_list.size(); i++)
    {
        this->remove_infected(infected_removal_list[i]);
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

#endif

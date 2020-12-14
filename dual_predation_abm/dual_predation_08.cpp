
// Import libraries.
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


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

/* ------------ Create Bacteriovorus class. ------------ */
// Bacteriovorus is derived from Bacteria.
class Bacteriovorus: public Bacteria
{
public:
    // Default constructor.
    Bacteriovorus() : Bacteria()
    {

    }
    // Constructor to take in the x and y coordinates of the bacteriovorus, the bacteriovorus' ID, and the bacteriovorus' name.
    Bacteriovorus(int i, int j, int num, std::string org) : Bacteria(i, j, num, org)
    {

    }
    // Constructor to take in the x and y coordinates of the bacteriovorus, the bacteriovorus' ID,
    //  the bacteriovorus' name, and the mortality rate of the bacteriovorus.
    Bacteriovorus(int i, int j, int num, std::string org, float mortality_rate) : Bacteria(i, j, num, org), mortality_rate(mortality_rate)
    {
        this->mortality_rate = mortality_rate;
    }

    float mortality_rate;   // The rate at which bacteriovorus cells dies.

};

/* ------------ Create Ecoli class. ------------ */
// Ecoli is derived from Bacteria.
class Ecoli: public Bacteria
{
public:
    // Default constructor.
    Ecoli() : Bacteria()
    {
        // Ecoli agent is not phage resistant nor bacteriovorus resistant by default.
        this->phage_resistant = false;
        this->bacteriovorus_resistant = false;
    }

    // Constructor to take in the x and y coordinates of the ecoli, the ecoli's ID, and the ecoli's name.
    Ecoli(int i, int j, int num, std::string org) : Bacteria(i, j, num, org)
    {
        this->i = i;
        this->j = j;
        this->num = num;
        this->org = org;
        this->phage_resistant = false;
        this->bacteriovorus_resistant = false;
    }
    // Constructor to take in the x and y coordinates of the ecoli, the ecoli's ID, the ecoli's name,
    //  the ecoli's phage resistance, and the ecoli's bacteriovorus resistance.
    Ecoli(int i, int j, int num, std::string org, bool phage_resistant, bool bacteriovorus_resistant)
        : Bacteria(i, j, num, org), phage_resistant(phage_resistant), bacteriovorus_resistant(bacteriovorus_resistant)
    {
        this->i = i;
        this->j = j;
        this->num = num;
        this->org = org;
        this->phage_resistant = phage_resistant;
        this->bacteriovorus_resistant = bacteriovorus_resistant;
    }

    // Print the ecoli's name, location, phage resistance, and bacteriovorus resistance.
    void print_me()
    {
        std::cout << "Organism: " << this->org << std::endl;
        std::cout << "node: " << this->i << "_" << this->j << std::endl;
        std::cout << "Phage resistant: " << this->phage_resistant << std::endl;
        std::cout << "Bacteriovorus resistant: " << this->bacteriovorus_resistant << std::endl;
        std::cout << "##########################################################################" << std::endl;
    }

    // Set the ecoli's phage resistance.
    void set_phage_resistant(bool phage_resistant)
    {
        this->phage_resistant = phage_resistant;
    }
    // Set the ecoli's bacteriovorus resistance.
    void set_bacteriovorus_resistant(bool bacteriovorus_resistant)
    {
        this->bacteriovorus_resistant = bacteriovorus_resistant;
    }

    // Return the ecoli's phage resistance.
    bool get_phage_resistant()
    {
        return this->phage_resistant;
    }
    // Return the ecoli's bacteriovorus resistance.
    bool get_bacteriovorus_resistant()
    {
        return this->bacteriovorus_resistant;
    }

    bool phage_resistant;           // Whether or not the ecoli is resistant to viral infection. true/false
    bool bacteriovorus_resistant;   // Whether or not the ecoli is resistant to bacteriovorus predation. true/false
};

/* ------------ Create Bdelloplast class. ------------ */
// Bdelloplast is derived from Ecoli.
class Bdelloplast: public Ecoli
{
public:
    // Default constructor.
    Bdelloplast() : Ecoli()
    {

    }

    // Constructor to take in the x and y coordinates of the bdelloplast, the bdelloplast's ID, and the bdelloplast's name.
    Bdelloplast(int i, int j, int num, std::string org) : Ecoli(i, j, num, org)
    {

    }
};

/* ------------ Create Infected class. ------------ */
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
        int init_infected_in_node, int init_virus_in_node, int init_bacteriovorus_in_node)
    {
        this->i = i;
        this->j = j;
        this->nutrients = init_nutrients;
        // Initial amount of bacteriovorus resistance conversion signals in the node.
        this->signal = 0;

        this->num_ecoli = init_ecoli_in_node;
        this->num_bdelloplast = init_bdelloplast_in_node;
        this->num_infected = init_infected_in_node;
        this->num_virus = init_virus_in_node;
        this->num_bacteriovorus = init_bacteriovorus_in_node;

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

        // Create vector of bacteriovorus cells.
        for (int n = 0; n < init_bacteriovorus_in_node; n++)
        {
            org = "Bacteriovorus_" + mid_string + std::to_string(n);
            Bacteriovorus bacteriovorus(i, j, n, org);
            bacteriovorus_list.push_back(bacteriovorus);
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
    void bacteriovorus_attack_prey();
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
        return this->num_bacteriovorus;
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
    void print_bacteriovorus_list()
    {
        for (int n = 0; n < this->num_bacteriovorus; n++)
        {
            this->bacteriovorus_list[n].print_me();
        }
    }

private:
    int i, j, nutrients, signal;
    int num_ecoli, num_bdelloplast, num_infected, num_virus, num_bacteriovorus;
    std::vector<Ecoli> ecoli_list;
    std::vector<Bdelloplast> bdelloplast_list;
    std::vector<Infected> infected_list;
    std::vector<Virus> virus_list;
    std::vector<Bacteriovorus> bacteriovorus_list;
};

// Function to iterate through the bacteriovorus in the node and determine whether they are successful
//  in entering ecoli cells.
void node::bacteriovorus_attack_prey()
{
    // Iterate over the bacteriovori in the node.
    for (int n = 0; n < this->num_bacteriovorus; n++)
    {
        bacteriovorus_list[n].print_me();
        // Iterate over the ecoli in the node.
        for (int m = 0; m < this->num_ecoli; m++)
        {

        }
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

int main()
{
    // The dimensions of the lattice.
    int x_len = 2;
    int y_len = 2;

    // Initial quantities.
    int init_nutrients = 100;
    int init_ecoli_in_node = 4;
    int init_bdelloplast_in_node = 0;
    int init_infected_in_node = 0;
    int init_virus_in_node = 0;
    int init_bacteriovorus_in_node = 1;

    // Paramaterizable variables.
    float bacteriovorus_attack_success_rate = .5;
    float virus_attach_succes_rate = .5;
    int incubation_period = 2;

    // Create lattice of nodes.
    node lattice[x_len][y_len];

    // Initialize every node in the lattice according to initial quantities.
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
        {

            lattice[i][j] = node(i, j, init_nutrients, init_ecoli_in_node, init_bdelloplast_in_node,
                init_infected_in_node, init_virus_in_node, init_bacteriovorus_in_node);
            // lattice[i][j].print_ecoli_list();
        }
    }

/*
    // Testing removal of ecoli cells.
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
       {
           // lattice[i][j].bacteriovorus_attack_prey();
           // std::cout << "here" << std::endl;
           lattice[i][j].remove_ecoli(1);
           // lattice[i][j].print_ecoli_list();
           // lattice[i][j].print_virus_list();
           // lattice[i][j].print_bacteriovorus_list();
       }
    }
*/
/*
    int num;
    std::string org_name;

    // Testing addition of ecoli cells.
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
       {
           num = lattice[i][j].get_next_available_num("Ecoli");
           org_name = "Ecoli_" + std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(num);
           Ecoli ecoli(i, j, num, org_name);
           // lattice[i][j].add_ecoli(ecoli);
           // std::cout << "here2" << std::endl;
           // lattice[i][j].print_ecoli_list();
       }
    }
*/
    int num_ecoli;
    int num_bacteriovorus;

    // Testing printing out the number of ecoli cells in each node.
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
       {
           std::cout << "Location: " << i << ", " << j << std::endl;
           num_ecoli = lattice[i][j].get_num_ecoli();
           num_bacteriovorus = lattice[i][j].get_num_bacteriovorous();
           std::cout << "Amount of ecoli in this node: " << num_ecoli << std::endl;
           std::cout << "Amount of bacteriovorus in this node: " << num_bacteriovorus << std::endl;
           std::cout << "####################################################" << std::endl;
           for (int n = 0; n < num_ecoli; n++)
           {

               std::cout << lattice[i][j].ecoli_list[n].moved << std::endl;
           }
       }
    }

    // std::string ecoli_dir_name = "ecoli/";
    // std::string bacteriovorous_dir_name = "bacteriovorous/";
    //
    // std::filesystem::create_directories(ecoli_dir_name);
    // std::filesystem::create_directories(bacteriovorous_dir_name);
    //
    // std::ofstream ecoli_file;
    // std::ofstream bacteriovorous_file;
    //
    // ecoli_file.open(ecoli_dir_name + "ecoli_grid.txt");
    // bacteriovorous_file.open(bacteriovorous_dir_name + "bacteriovorous_grid.txt");
    //
    // for (int i = 0; i < x_len; i++)
    // {
    //     for (int j = 0; j < y_len; j++)
    //    {
    //        num_ecoli = lattice[i][j].get_num_ecoli();
    //        num_bacteriovorus = lattice[i][j].get_num_bacteriovorous();
    //
    //        ecoli_file << num_ecoli << " ";
    //        bacteriovorous_file << num_bacteriovorus << " ";
    //    }
    //    ecoli_file << "\n";
    //    // ecoli_file << std::endl;
    //    bacteriovorous_file << "\n";
    // }
    //
    // ecoli_file.close();
    // bacteriovorous_file.close();


}

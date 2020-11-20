
// Import libraries.
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


#include "determine_ij.h"
#include "agent.h"
#include "virus.h"
#include "bacteria.h"
#include "bacteriovorous.h"
#include "ecoli.h"
#include "bdelloplast.h"
#include "infected.h"
#include "node.h"




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
    double bacteriovorous_attack_rate = .9;
    double virus_attach_succes_rate = .5;
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
            for (int n = 0; n < init_bacteriovorus_in_node; n++)
            {
                lattice[i][j].set_bacteriovorous_cell_attack_rate(n, bacteriovorous_attack_rate);
                // std::cout << lattice[i][j].get_bacteriovorous_cell_attack_rate(n) << std::endl;
            }
            // lattice[i][j].print_ecoli_list();

            lattice[i][j].bacteriovorous_attack_prey();
        }
    }

    // std::cout << "test" << std::endl;

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
    int i_up, i_down, j_left, j_right;
    std::vector<int> ij_coordinates;

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
           // for (int n = 0; n < num_ecoli; n++)
           // {
           //
           //     std::cout << lattice[i][j].ecoli_list[n].moved << std::endl;
           // }
           ij_coordinates = determine_ij(i, j, x_len, y_len);
           i_up = ij_coordinates[0];
           i_down = ij_coordinates[1];
           j_left = ij_coordinates[2];
           j_right = ij_coordinates[3];

           std::cout << "i: " << i << ", j: " << j
                        << ", i_up: " << i_up << ", i_down: " << i_down
                        << ", j_left: " << j_left << ", j_right: " << j_right << std::endl;
           std::cout << "####################################################" << std::endl;

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

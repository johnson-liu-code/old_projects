
// Import libraries.
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>


// Import header files.
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
    int x_len = 10;
    int y_len = 10;
    int simulation_length = 100;

    // Initial quantities.
    double init_nutrients = 999999999999999999;

    int init_ecoli_in_node = 40;
    int init_bdelloplast_in_node = 0;
    int init_infected_in_node = 0;

    int init_bacteriovorous_in_node = 10;
    int init_virus_in_node = 10;

    double init_ecoli_energy = 40;
    double ecoli_max_nutrient_consumption = 10;
    double ecoli_exist_energy_cost = 20;
    double ecoli_move_energy_cost = 10;
    double ecoli_reproduce_energy_cost = 10;

    double bacteriovorous_attack_rate = .4;
    int bacteriovorous_mortality_period = 4;
    int bdelloplast_incubation_period = 2;
    int max_signal_released = 2;
    int max_bacteriorovorous_released = 4;

    double virus_attack_rate = .4;
    int infected_incubation_period = 2;
    int max_virus_released = 4;

    double bacteriovorous_resistance_mutation_probability = .9;
    double bacteriovorous_resistance_reversion_probability = .4;

    double phage_resistance_mutation_probability = .9;
    double phage_resistance_reversion_probability = .4;

    double ecoli_diffuse_probability = .25;
    double bacteriovorous_diffuse_probability = .25;
    double virus_diffuse_probability = .25;
    double bdelloplast_diffuse_probability = .25;
    double infected_diffuse_probability = .25;
    double signal_diffuse_probability = .25;

    std::random_device rd;
    std::mt19937 gen(rd());

    // dis(min, max) gives a uniform random number between min and max.
    std::uniform_real_distribution<> dis(0, 1);
    float r, rr;

    int i_up, i_down, j_left, j_right;
    std::vector<int> ij_coordinates;

    // std::vector<std::string> particle_list = {"ecoli", "bacteriovorous",
    //     "bdelloplast", "virus", "infected"};
    std::vector<std::string> particle_list = {"ecoli", "bacteriovorous", "virus"};
    std::string particle_type;

    Agent particle;
    Ecoli ecoli;
    Bacteriovorous bacteriovorous;
    Bdelloplast bdelloplast;
    Virus virus;
    Infected infected;

    int amount_in_current_node;
    double diffuse_probability;

    // Variables used for debugging.
    int num_ecoli;
    int num_bacteriovorous, num_bdelloplast;
    int num_virus, num_infected;

    int num_susceptible_ecoli_on_lattice;
    int num_bacteriovorous_resistant_ecoli_on_lattice;
    int num_phage_resistant_ecoli_on_lattice;
    int num_bacteriovorous_on_lattice;
    int num_bdelloplast_on_lattice;
    int num_virus_on_lattice;
    int num_infected_on_lattice;

    int susceptible_ecoli_over_time [simulation_length + 1];
    int bacteriovorous_resistant_over_time [simulation_length + 1];
    int phage_resistant_over_time [simulation_length + 1];
    int bacteriovorous_over_time [simulation_length + 1];
    int bdelloplast_over_time [simulation_length + 1];
    int virus_over_time [simulation_length + 1];
    int infected_over_time [simulation_length + 1];

    susceptible_ecoli_over_time[0] = init_ecoli_in_node * x_len * y_len;
    bacteriovorous_resistant_over_time[0] = 0;
    phage_resistant_over_time[0] = 0;
    bacteriovorous_over_time[0] = init_bacteriovorous_in_node * x_len * y_len;
    bdelloplast_over_time[0] = init_bdelloplast_in_node * x_len * y_len;
    virus_over_time[0] = init_virus_in_node * x_len * y_len;
    infected_over_time[0] = init_infected_in_node * x_len * y_len;

    // Create a lattice of nodes.
    node lattice[x_len][y_len];

    // Initialize every node in the lattice according to initial quantities.
    for (int i = 0; i < x_len; i++)
    {
        for (int j = 0; j < y_len; j++)
        {
            // Create node.
            lattice[i][j] = node(i, j, init_nutrients, init_ecoli_in_node, init_bdelloplast_in_node,
                init_infected_in_node, init_virus_in_node, init_bacteriovorous_in_node,
                phage_resistance_mutation_probability, phage_resistance_reversion_probability,
                bacteriovorous_resistance_mutation_probability,
                bacteriovorous_resistance_reversion_probability, ecoli_max_nutrient_consumption,
                ecoli_exist_energy_cost, ecoli_reproduce_energy_cost, max_signal_released,
                max_bacteriorovorous_released, max_virus_released, bacteriovorous_mortality_period);

            for (int n = 0; n < init_ecoli_in_node; n++)
            {
                lattice[i][j].ecoli_list[n].energy = init_ecoli_energy;
            }

            // Set the bacteriovorous attack rate and the bdelloplast incubation period
            //  for each bacteriovorous in the node.
            for (int n = 0; n < init_bacteriovorous_in_node; n++)
            {
                lattice[i][j].set_bacteriovorous_attack_rate(n, bacteriovorous_attack_rate);
                lattice[i][j].set_bdelloplast_incubation_period(n, bdelloplast_incubation_period);
            }
            for (int n = 0; n < init_virus_in_node; n++)
            {
                lattice[i][j].set_virus_attack_rate(n, virus_attack_rate);
                lattice[i][j].set_infected_incubation_period(n, infected_incubation_period);
            }
        }
    }

    for (int k = 0; k < simulation_length; k++)
    {
        std::cout << "step " << k << std::endl;
        for (int i = 0; i < x_len; i++)
        {
            for (int j = 0; j < y_len; j++)
            {
                lattice[i][j].ecoli_consume_nutrients();
                lattice[i][j].iterate_ecoli_die_mutate_reproduce();
                lattice[i][j].bacteriovorous_attack_prey();
                lattice[i][j].virus_infect_prey();
                lattice[i][j].burst_bdelloplasts();
                lattice[i][j].burst_infected();
                lattice[i][j].bacteriovorous_mortality();
            }
        }

        for (int i = 0; i < x_len; i++)
        {
            for (int j = 0; j < y_len; j++)
            {
                ij_coordinates = determine_ij(i, j, x_len, y_len);
                i_up = ij_coordinates[0];
                i_down = ij_coordinates[1];
                j_left = ij_coordinates[2];
                j_right = ij_coordinates[3];

                for (int h = 0; h < particle_list.size(); h++)
                {
                    std::vector<int> move_north_list;
                    std::vector<int> move_south_list;
                    std::vector<int> move_west_list;
                    std::vector<int> move_east_list;
                    std::vector<int> move_list;

                    double north_node_amount, south_node_amount, west_node_amount, east_node_amount;
                    double n, s, w, e, t, pn, ps, pw, pe;

                    particle_type = particle_list[h];

                    if (particle_type == "ecoli")
                    {
                        north_node_amount = lattice[i_up][j].num_ecoli;
                        south_node_amount = lattice[i_down][j].num_ecoli;
                        west_node_amount = lattice[i][j_left].num_ecoli;
                        east_node_amount = lattice[i][j_right].num_ecoli;

                        amount_in_current_node = lattice[i][j].num_ecoli;
                    }
                    else if (particle_type == "bacteriovorous")
                    {
                        north_node_amount = lattice[i_up][j].num_bacteriovorous;
                        south_node_amount = lattice[i_down][j].num_bacteriovorous;
                        west_node_amount = lattice[i][j_left].num_bacteriovorous;
                        east_node_amount = lattice[i][j_right].num_bacteriovorous;

                        amount_in_current_node = lattice[i][j].num_bacteriovorous;
                    }
                    else if (particle_type == "virus")
                    {
                        north_node_amount = lattice[i_up][j].num_virus;
                        south_node_amount = lattice[i_down][j].num_virus;
                        west_node_amount = lattice[i][j_left].num_virus;
                        east_node_amount = lattice[i][j_right].num_virus;

                        amount_in_current_node = lattice[i][j].num_virus;
                    }

                    for (int k = 0; k < amount_in_current_node; k++)
                    {
                        if (particle_type == "ecoli")
                            Ecoli particle = lattice[i][j].ecoli_list[k];
                        else if (particle_type == "bacteriovorous")
                            Bacteriovorous particle = lattice[i][j].bacteriovorous_list[k];
                        else if (particle_type == "virus")
                            Virus particle = lattice[i][j].virus_list[k];

                        if (particle.moved == false)
                        {
                            if (particle_type == "ecoli")
                                diffuse_probability = ecoli_diffuse_probability;
                            else if (particle_type == "bacteriovorous")
                                diffuse_probability = bacteriovorous_diffuse_probability;
                            else if (particle_type == "virus")
                                diffuse_probability = virus_diffuse_probability;

                            r = dis(gen);

                            if (r <= diffuse_probability)
                            {
                                move_list.push_back(k);

                                if (north_node_amount == 0) north_node_amount = 1;
                                if (south_node_amount == 0) south_node_amount = 1;
                                if (west_node_amount == 0)  west_node_amount = 1;
                                if (east_node_amount == 0)  east_node_amount = 1;

                                n = 1/north_node_amount;
                                s = 1/south_node_amount;
                                w = 1/west_node_amount;
                                e = 1/east_node_amount;

                                t = n + s + w + e;

                                pn = n/t;
                                ps = s/t;
                                pw = w/t;
                                pe = e/t;

                                rr = dis(gen);

                                if (0 <= rr < pn)
                                {
                                    move_north_list.push_back(k);
                                }
                                else if (pn <= rr < pn + ps)
                                {
                                    move_south_list.push_back(k);
                                }
                                else if (pn + ps <= rr < pn + ps + pw)
                                {
                                    move_west_list.push_back(k);
                                }
                                else if (pn + ps + pw <= rr <= 1)
                                {
                                    move_east_list.push_back(k);
                                }
                            }
                        }
                    }

                    // std::cout << "here1" << std::endl;
                    for (int n = 0; n < move_north_list.size(); n++)
                    {
                        if (particle_type == "ecoli")
                        {
                            // std::cout << "here1.1" << std::endl;
                            ecoli = lattice[i][j].ecoli_list[move_north_list[n]];
                            // std::cout << "here1.2" << std::endl;
                            ecoli.moved = true;
                            ecoli.energy = ecoli.energy - ecoli_move_energy_cost;
                            // std::cout << "here1.3" << std::endl;
                            lattice[i_up][j].add_ecoli(ecoli);
                            // std::cout << "here1.4" << std::endl;
                        }
                        else if (particle_type == "bacteriovorous")
                        {
                            // std::cout << "here1.5" << std::endl;
                            bacteriovorous = lattice[i][j].bacteriovorous_list[move_north_list[n]];
                            // std::cout << "here1.6" << std::endl;
                            bacteriovorous.moved = true;
                            // std::cout << "here1.7" << std::endl;
                            lattice[i_up][j].add_bacteriovorous(bacteriovorous);
                            // std::cout << "here1.8" << std::endl;
                        }
                        else if (particle_type == "virus")
                        {
                            // std::cout << "here1.9" << std::endl;
                            virus = lattice[i][j].virus_list[move_north_list[n]];
                            // std::cout << "here1.10" << std::endl;
                            virus.moved = true;
                            // std::cout << "here1.11" << std::endl;
                            lattice[i_up][j].add_virus(virus);
                            // std::cout << "here1.12" << std::endl;
                        }
                    }
                    // std::cout << "here2" << std::endl;
                    for (int n = 0; n < move_south_list.size(); n++)
                    {
                        if (particle_type == "ecoli")
                        {
                            // std::cout << "here2.1" << std::endl;
                            ecoli = lattice[i][j].ecoli_list[move_south_list[n]];
                            // std::cout << "here2.2" << std::endl;
                            ecoli.moved = true;
                            ecoli.energy = ecoli.energy - ecoli_move_energy_cost;
                            // std::cout << "here2.3" << std::endl;
                            lattice[i_down][j].add_ecoli(ecoli);
                            // std::cout << "here2.4" << std::endl;
                        }
                        else if (particle_type == "bacteriovorous")
                        {
                            // std::cout << "here2.5" << std::endl;
                            bacteriovorous = lattice[i][j].bacteriovorous_list[move_south_list[n]];
                            // std::cout << "here2.6" << std::endl;
                            bacteriovorous.moved = true;
                            // std::cout << "here2.7" << std::endl;
                            lattice[i_down][j].add_bacteriovorous(bacteriovorous);
                            // std::cout << "here2.8" << std::endl;
                        }
                        else if (particle_type == "virus")
                        {
                            // std::cout << "here2.9" << std::endl;
                            virus = lattice[i][j].virus_list[move_south_list[n]];
                            // std::cout << "here2.10" << std::endl;
                            virus.moved = true;
                            // std::cout << "here2.11" << std::endl;
                            lattice[i_down][j].add_virus(virus);
                            // std::cout << "here2.12" << std::endl;
                        }
                    }
                    // std::cout << "here3" << std::endl;
                    for (int n = 0; n < move_west_list.size(); n++)
                    {
                        if (particle_type == "ecoli")
                        {
                            // std::cout << "here3.1" << std::endl;
                            ecoli = lattice[i][j].ecoli_list[move_west_list[n]];
                            // std::cout << "here3.2" << std::endl;
                            ecoli.moved = true;
                            ecoli.energy = ecoli.energy - ecoli_move_energy_cost;
                            // std::cout << "here3.3" << std::endl;
                            lattice[i][j_left].add_ecoli(ecoli);
                            // std::cout << "here3.4" << std::endl;
                        }
                        else if (particle_type == "bacteriovorous")
                        {
                            // std::cout << "here3.5" << std::endl;
                            bacteriovorous = lattice[i][j].bacteriovorous_list[move_west_list[n]];
                            // std::cout << "here3.6" << std::endl;
                            bacteriovorous.moved = true;
                            // std::cout << "here3.7" << std::endl;
                            lattice[i][j_left].add_bacteriovorous(bacteriovorous);
                            // std::cout << "here3.8" << std::endl;
                        }
                        else if (particle_type == "virus")
                        {
                            // std::cout << "here3.9" << std::endl;
                            virus = lattice[i][j].virus_list[move_west_list[n]];
                            // std::cout << "here3.10" << std::endl;
                            virus.moved = true;
                            // std::cout << "here3.11" << std::endl;
                            lattice[i][j_left].add_virus(virus);
                            // std::cout << "here3.12" << std::endl;
                        }
                    }
                    // std::cout << "here4" << std::endl;
                    for (int n = 0; n < move_east_list.size(); n++)
                    {
                        if (particle_type == "ecoli")
                        {
                            // std::cout << "here4.1" << std::endl;
                            ecoli = lattice[i][j].ecoli_list[move_east_list[n]];
                            // std::cout << "here4.2" << std::endl;
                            ecoli.moved = true;
                            ecoli.energy = ecoli.energy - ecoli_move_energy_cost;
                            // std::cout << "here4.3" << std::endl;
                            lattice[i][j_right].add_ecoli(ecoli);
                            // std::cout << "here4.4" << std::endl;
                        }
                        else if (particle_type == "bacteriovorous")
                        {
                            // std::cout << "here4.5" << std::endl;
                            bacteriovorous = lattice[i][j].bacteriovorous_list[move_east_list[n]];
                            // std::cout << "here4.6" << std::endl;
                            bacteriovorous.moved = true;
                            // std::cout << "here4.7" << std::endl;
                            lattice[i][j_right].add_bacteriovorous(bacteriovorous);
                            // std::cout << "here4.8" << std::endl;
                        }
                        else if (particle_type == "virus")
                        {
                            // std::cout << "here4.9" << std::endl;
                            virus = lattice[i][j].virus_list[move_east_list[n]];
                            // std::cout << "here4.10" << std::endl;
                            virus.moved = true;
                            // std::cout << "here4.11" << std::endl;
                            lattice[i][j_right].add_virus(virus);
                            // std::cout << "here4.12" << std::endl;
                        }
                    }

                    // std::cout << "here10" << std::endl;
                    if (particle_type == "ecoli")
                    {
                        // std::cout << "here10.1" << std::endl;
                        lattice[i][j].remove_many_ecoli(move_list);
                        // std::cout << "here10.2" << std::endl;
                    }
                    else if (particle_type == "bacteriovorous")
                    {
                        // std::cout << "here10.3" << std::endl;
                        lattice[i][j].remove_many_bacteriovori(move_list);
                        // std::cout << "here10.4" << std::endl;
                    }
                    else if (particle_type == "virus")
                    {
                        // std::cout << "here10.5" << std::endl;
                        lattice[i][j].remove_many_viri(move_list);
                        // std::cout << "here10.6" << std::endl;
                    }
                    // std::cout << "here11" << std::endl;
                }
            }
        }

        num_susceptible_ecoli_on_lattice = 0;
        num_bacteriovorous_resistant_ecoli_on_lattice = 0;
        num_phage_resistant_ecoli_on_lattice = 0;
        num_bacteriovorous_on_lattice = 0;
        num_bdelloplast_on_lattice = 0;
        num_virus_on_lattice = 0;
        num_infected_on_lattice = 0;

        for (int i = 0; i < x_len; i++)
        {
            for (int j = 0; j < y_len; j++)
            {
                lattice[i][j].demove_organisms();

                for (int p = 0; p < lattice[i][j].ecoli_list.size(); p++)
                {
                    if (lattice[i][j].ecoli_list[p].bacteriovorous_resistant == true)
                    {
                        num_bacteriovorous_resistant_ecoli_on_lattice += 1;
                    }
                    else if (lattice[i][j].ecoli_list[p].phage_resistant == true)
                    {
                        num_phage_resistant_ecoli_on_lattice += 1;
                    }
                    else
                    {
                        num_susceptible_ecoli_on_lattice += 1;
                    }
                }

                num_bacteriovorous_on_lattice += lattice[i][j].num_bacteriovorous;
                num_bdelloplast_on_lattice += lattice[i][j].num_bdelloplast;
                num_virus_on_lattice += lattice[i][j].num_virus;
                num_infected_on_lattice += lattice[i][j].num_infected;
            }
        }

        susceptible_ecoli_over_time[k+1] = num_susceptible_ecoli_on_lattice;
        bacteriovorous_resistant_over_time[k+1] = num_bacteriovorous_resistant_ecoli_on_lattice;
        phage_resistant_over_time[k+1] = num_phage_resistant_ecoli_on_lattice;
        bacteriovorous_over_time[k+1] = num_bacteriovorous_on_lattice;
        bdelloplast_over_time[k+1] = num_bdelloplast_on_lattice;
        virus_over_time[k+1] = num_virus_on_lattice;
        infected_over_time[k+1] = num_infected_on_lattice;
    }

    // Printing out the amount of each agent in each node as well as a node's neighbors
    //  for testing purposes.
    // for (int i = 0; i < x_len; i++)
    // {
    //     for (int j = 0; j < y_len; j++)
    //    {
    //        std::cout << "Location: " << i << ", " << j << std::endl;
    //
    //        num_ecoli = lattice[i][j].num_ecoli;
    //        num_bacteriovorous = lattice[i][j].num_bacteriovorous;
    //        num_bdelloplast = lattice[i][j].num_bdelloplast;
    //        num_virus = lattice[i][j].num_virus;
    //        num_infected = lattice[i][j].num_infected;
    //
    //        std::cout << "Amount of E. coli in this node: " << num_ecoli << std::endl;
    //
    //        std::cout << "Amount of bacteriovorous in this node: " << num_bacteriovorous << std::endl;
    //        std::cout << "Amount of bdelloplast in this node: " << num_bdelloplast << std::endl;
    //
    //        std::cout << "Amount of virus' in this node: " << num_virus << std::endl;
    //        std::cout << "Amount of infected E. coli cells in this node: " << num_infected << std::endl;

           // ij_coordinates = determine_ij(i, j, x_len, y_len);
           //
           // i_up = ij_coordinates[0];
           // i_down = ij_coordinates[1];
           // j_left = ij_coordinates[2];
           // j_right = ij_coordinates[3];
           //
           // std::cout << "i: " << i << ", j: " << j
           //              << ", i_up: " << i_up << ", i_down: " << i_down
           //              << ", j_left: " << j_left << ", j_right: " << j_right << std::endl;
           // std::cout << "##########################################################" << std::endl;
       // }
    // }


    // Create directories to store data generated by the simulation.
    // std::string ecoli_dir_name = "ecoli/";
    // std::string bacteriovorous_dir_name = "bacteriovorous/";

    // std::filesystem::create_directories(ecoli_dir_name);
    // std::filesystem::create_directories(bacteriovorous_dir_name);

    // Open files and specify file names.
    std::ofstream susceptible_ecoli_over_time_file;
    std::ofstream bacteriovorous_resistant_over_time_file;
    std::ofstream phage_resistant_over_time_file;
    std::ofstream bacteriovorous_over_time_file;
    std::ofstream bdelloplast_over_time_file;
    std::ofstream virus_over_time_file;
    std::ofstream infected_over_time_file;

    susceptible_ecoli_over_time_file.open("susceptible_ecoli_over_time.txt");
    bacteriovorous_resistant_over_time_file.open("bacteriovorous_resistant_over_time.txt");
    phage_resistant_over_time_file.open("phage_resistant_over_time.txt");
    bacteriovorous_over_time_file.open("bacteriovorous_over_time.txt");
    bdelloplast_over_time_file.open("bdelloplast_over_time.txt");
    virus_over_time_file.open("virus_over_time.txt");
    infected_over_time_file.open("infected_over_time.txt");

    for (int k = 0; k < simulation_length + 1; k++)
    {
        susceptible_ecoli_over_time_file << susceptible_ecoli_over_time[k] << std::endl;
        bacteriovorous_resistant_over_time_file << bacteriovorous_resistant_over_time[k] << std::endl;
        phage_resistant_over_time_file << phage_resistant_over_time[k] << std::endl;
        bacteriovorous_over_time_file << bacteriovorous_over_time[k] << std::endl;
        bdelloplast_over_time_file << bdelloplast_over_time[k] << std::endl;
        virus_over_time_file << virus_over_time[k] << std::endl;
        infected_over_time_file << infected_over_time[k] << std::endl;
    }

    // Iterate over the lattice and record the number of each agent onto output files.
    // for (int i = 0; i < x_len; i++)
    // {
    //     for (int j = 0; j < y_len; j++)
    //    {
    //        num_ecoli = lattice[i][j].num_ecoli;
    //        num_bacteriovorous = lattice[i][j].num_bacteriovorous;
    //
    //        ecoli_file << num_ecoli << " ";
    //        bacteriovorous_file << num_bacteriovorous << " ";
    //    }
    //    ecoli_file << "\n";
    //    // ecoli_file << std::endl;
    //    bacteriovorous_file << "\n";
    // }

    // Close the output files.
    // ecoli_file.close();
    // bacteriovorous_file.close();

    susceptible_ecoli_over_time_file.close();
    bacteriovorous_resistant_over_time_file.close();
    phage_resistant_over_time_file.close();
    bacteriovorous_over_time_file.close();
    bdelloplast_over_time_file.close();
    virus_over_time_file.close();
    infected_over_time_file.close();

}

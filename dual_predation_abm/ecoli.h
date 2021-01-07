#ifndef ECOLI_H
#define ECOLI_H

#include "bacteria.h"

/* ------------ Ecoli class. ------------ */
// Ecoli is derived from Bacteria.
class Ecoli: public Bacteria
{
public:
    // Default constructor.
    Ecoli() : Bacteria()
    {
        // Ecoli agent is not phage resistant nor bacteriovorous resistant by default.
        this->phage_resistant = false;
        this->bacteriovorous_resistant = false;
    }

    // Constructor to take in the x and y coordinates of the Ecoli cell.
    Ecoli(int i, int j) : Bacteria(i, j)
    {
        this->i = i;
        this->j = j;
        // Ecoli agent is not phage resistant nor bacteriovorous resistant by default.
        this->phage_resistant = false;
        this->bacteriovorous_resistant = false;
    }
    // Constructor to take in the x and y coordinates of the Ecoli, the Ecoli's phage
    //  resistance, and the Ecoli's bacteriovorous resistance.
    Ecoli(int i, int j, bool phage_resistant, bool bacteriovorous_resistant)
        : Bacteria(i, j), phage_resistant(phage_resistant), bacteriovorous_resistant(bacteriovorous_resistant)
    {
        this->i = i;
        this->j = j;
        this->phage_resistant = phage_resistant;
        this->bacteriovorous_resistant = bacteriovorous_resistant;
    }

    // Print the Ecoli cell's location, phage resistance, and bacteriovorous resistance.
    void print_me()
    {
        std::cout << "node: " << this->i << "_" << this->j << std::endl;
        std::cout << "Phage resistant: " << this->phage_resistant << std::endl;
        std::cout << "bacteriovorous resistant: " << this->bacteriovorous_resistant << std::endl;
        std::cout << "##########################################################################" << std::endl;
    }

    void add_energy(int energy)
    {
        this->energy += energy;
    }
    void remove_energy(int energy_lost)
    {
        this->energy -= energy_lost;
    }
    int get_energy()
    {
        return this->energy;
    }

    // Set the Ecoli's phage resistance.
    void set_phage_resistant(bool phage_resistant)
    {
        this->phage_resistant = phage_resistant;
    }
    // Set the Ecoli's bacteriovorous resistance.
    void set_bacteriovorous_resistant(bool bacteriovorous_resistant)
    {
        this->bacteriovorous_resistant = bacteriovorous_resistant;
    }

    // Return the Ecoli's phage resistance.
    bool get_phage_resistant()
    {
        return this->phage_resistant;
    }
    // Return the Ecoli's bacteriovorous resistance.
    bool get_bacteriovorous_resistant()
    {
        return this->bacteriovorous_resistant;
    }

    double energy = 0;
    bool phage_resistant;           // Whether or not the ecoli is resistant to viral infection. true/false
    bool bacteriovorous_resistant;   // Whether or not the ecoli is resistant to bacteriovorous predation. true/false
};

#endif

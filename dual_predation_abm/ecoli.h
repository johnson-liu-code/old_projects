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
        // Ecoli agent is not phage resistant nor bacteriovorus resistant by default.
        this->phage_resistant = false;
        this->bacteriovorus_resistant = false;
    }
    // Constructor to take in the x and y coordinates of the Ecoli, the Ecoli's ID, the Ecoli's name,
    //  the Ecoli's phage resistance, and the Ecoli's bacteriovorus resistance.
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

    // Set the Ecoli's phage resistance.
    void set_phage_resistant(bool phage_resistant)
    {
        this->phage_resistant = phage_resistant;
    }
    // Set the Ecoli's bacteriovorus resistance.
    void set_bacteriovorus_resistant(bool bacteriovorus_resistant)
    {
        this->bacteriovorus_resistant = bacteriovorus_resistant;
    }

    // Return the Ecoli's phage resistance.
    bool get_phage_resistant()
    {
        return this->phage_resistant;
    }
    // Return the Ecoli's bacteriovorus resistance.
    bool get_bacteriovorus_resistant()
    {
        return this->bacteriovorus_resistant;
    }

    bool phage_resistant;           // Whether or not the ecoli is resistant to viral infection. true/false
    bool bacteriovorus_resistant;   // Whether or not the ecoli is resistant to bacteriovorus predation. true/false
};

#endif

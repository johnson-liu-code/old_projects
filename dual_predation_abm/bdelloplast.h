#ifndef BDELLOPLAST_H
#define BDELLOPLAST_H

#include "ecoli.h"

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

#endif

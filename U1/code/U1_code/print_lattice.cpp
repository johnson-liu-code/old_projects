#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <chrono>
using namespace std;

#include "site.h"

// Print out the links of the lattice.
void print_lattice(site lattice[], int lattice_size, int number_of_dimensions)
{
    for (int i = 0; i < lattice_size; i++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
            printf("site %i, dir: %i, real: %f, imag: %f\n", i, l, (lattice[i].link[l]).real(), (lattice[i].link[l]).imag());
            cout << "++++++++++++++++++++++++++++++" << endl;
        }
    }
}
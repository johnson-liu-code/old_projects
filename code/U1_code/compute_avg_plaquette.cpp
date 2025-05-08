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

#include "n_choose_k.h"
#include "site.h"
#include "compute_real_plaquettes_at_site.h"

double compute_avg_plaquette(vector<int> dimension_lengths, int lattice_size, site lattice[], int number_of_dimensions)
{
    double real_plaquettes_at_site;
    double total_real_plaquettes = 0;

    int number_of_plaquettes = choose(number_of_dimensions, 2) * lattice_size;

    for (int direction = 0; direction < number_of_dimensions; direction++)
    {
        // Iterate over sites.
        for (int s = 1; s <= lattice_size; s++)
        {
            // Iterate over directions.
            if (direction < number_of_dimensions - 1)
            {
                real_plaquettes_at_site = compute_real_plaquettes_at_site(s, dimension_lengths, direction, lattice, number_of_dimensions);
            }
            else
            {
                real_plaquettes_at_site = 0;
            }

            total_real_plaquettes += real_plaquettes_at_site;
        }
    }

    double avg_real_plaquettes = total_real_plaquettes / number_of_plaquettes;

//    cout << "PLAQ   " << avg_real_plaquettes << endl;

    return avg_real_plaquettes;
}
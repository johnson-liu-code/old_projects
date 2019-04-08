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

void initialize_lattice(site lattice[], int lattice_size, vector<int> dimension_lengths, double init_angle, int number_of_dimensions)
{
    for (int s = 1; s <= lattice_size; s++)
    {
        for (int l = 0; l < number_of_dimensions; l++)
        {
            lattice[s-1].link.push_back(complex<double> (cos(init_angle), sin(init_angle)));
        }
    }
}
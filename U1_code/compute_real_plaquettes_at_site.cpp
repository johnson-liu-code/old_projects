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
#include "looper_forward.h"
#include "looper_backward.h"

double compute_real_plaquettes_at_site(int index, vector<int> dimension_lengths, int direction, site lattice[], int number_of_dimensions)
{
    int index_loop = index;

    double real_plaquettes_at_site = 0;

    for (int second_direction = direction + 1; second_direction < number_of_dimensions; second_direction++)
    {
        complex<double> a = lattice[index_loop-1].link[direction];
        complex<double> b = conj(lattice[index_loop-1].link[second_direction]);

        index_loop = looper_forward(index_loop, dimension_lengths, direction);

        complex<double> c = lattice[index_loop-1].link[second_direction];

        index_loop = looper_backward(index_loop, dimension_lengths, direction);
        index_loop = looper_forward(index_loop, dimension_lengths, second_direction);

        complex<double> d = conj(lattice[index_loop-1].link[direction]);

        real_plaquettes_at_site += (a*b*c*d).real();
    }

    return real_plaquettes_at_site;
}
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

complex<double>* update_polyakov(vector<int> dimension_lengths, site lattice[], complex<double>* polyakov_list, int number_of_dimensions)
{
    int time_dimension_position = number_of_dimensions - 1;

    complex<double> total_polyakov(0.0, 0.0);

    int spacial_dimension = 1;

    for (int s = 0; s < number_of_dimensions-1; s++)
    {
        spacial_dimension *= dimension_lengths[s];
    }

    complex<double> polyakov;
    for (int i = 1; i <= spacial_dimension; i++)
    {
        polyakov = 1;
        int time_index = i;
        for (int t = 1; t <= dimension_lengths[time_dimension_position]; t++)
        {
            polyakov *= lattice[time_index-1].link[time_dimension_position];
            time_index = looper_forward(time_index, dimension_lengths, time_dimension_position);
        }

        polyakov_list[i-1] = polyakov;

        total_polyakov += polyakov;
    }

    double avg_polyakov_real = total_polyakov.real()/spacial_dimension;
    double avg_polyakov_imag = total_polyakov.imag()/spacial_dimension;

    double avg_polyakov = sqrt(total_polyakov.real()*total_polyakov.real() + total_polyakov.imag()*total_polyakov.imag()) / spacial_dimension;

    return polyakov_list;

}
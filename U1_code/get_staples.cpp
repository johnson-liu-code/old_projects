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

// Collect the staples.
complex<double> get_staples(int index, vector<int> dimension_lengths, int direction, site lattice[], int number_of_dimensions)
{
    complex<double> staples(0.0, 0.0);
    complex<double> top(1.0, 0.0);
    complex<double> bot(1.0, 0.0);

    for (int dir = 0; dir < number_of_dimensions; dir++)
    {
        if (dir != direction)
        {            
            int index_top = index;
            int index_bot = index;

            top *= conj(lattice[index_top-1].link[dir]);

            index_top = looper_forward(index_top, dimension_lengths, direction);

            top *= lattice[index_top-1].link[dir];

            index_top = looper_backward(index_top, dimension_lengths, direction);
            index_top = looper_forward(index_top, dimension_lengths, dir);

            top *= conj(lattice[index_top-1].link[direction]);

            index_bot = looper_backward(index_bot, dimension_lengths, dir);

            bot *= lattice[index_bot-1].link[dir];

            bot *= conj(lattice[index_bot-1].link[direction]);

            index_bot = looper_forward(index_bot, dimension_lengths, direction);

            bot *= conj(lattice[index_bot-1].link[dir]);

            staples += top + bot;
        }
    }

    return staples;
}
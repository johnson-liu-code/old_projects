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

vector<int> convert_index_to_multiple(vector<int> dimension_lengths, int index, int number_of_dimensions)
{    
    vector<int> multiple_indices;
    multiple_indices.reserve(number_of_dimensions);
    
    int leng = 1;

    int m, mm;

    for (int d = 0; d < number_of_dimensions; d++)
    {
        m = index / leng;
        mm = m % dimension_lengths[d];

        multiple_indices.push_back(mm);

        leng *= dimension_lengths[d];
    }

    return multiple_indices;
}
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

int convert_index_to_single(vector<int> dimension_lengths, vector<int> indices)
{
    int d_len = 1;
    int single_index = indices[0];
    
    for (int i = 1; i < indices.size(); i++)
    {
        d_len *= dimension_lengths[i-1];

        single_index += d_len * indices[i];
    }
    
    return single_index;
}
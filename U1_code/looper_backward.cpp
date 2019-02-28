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

// Go backwards in one direction.
int looper_backward(int index, vector<int> dimension_lengths, int direction)
{
    int divisor = 1;
    int multiple = 1;

    for (int i = 0; i <= direction; i++)
        {
            divisor = divisor * dimension_lengths[i];
        }
    for (int i = 0; i < direction; i++)
        {
            multiple = multiple * dimension_lengths[i];
        }
    if (direction == 0)
    {
        if ( ( (index - 1) % dimension_lengths[direction] ) == 0 )
        {
            index = index + (dimension_lengths[direction] - 1);
        }
        else
        {
            index = index - 1;
        }
    }
    else
    {
        if ( index % divisor <= multiple && index % divisor != 0 )
        {
            index = index + (dimension_lengths[direction] - 1) * multiple;
        }
        else
        {
            index = index - multiple;
        }
    }

    return index;
}
#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
using namespace std;



double init_real = 1;
double init_imag = 0;


vector<int> user_dimensions(string L)   // Returns a vector with the dimension lengths.
{
    string delim = "x";

    vector<int> dimensions;
    int index = 0;

    int start = 0U;
    int end = L.find(delim);
    
    while (end != string::npos)
    {
        dimensions.push_back(stoi(L.substr(start, end - start)));
        start = end + delim.length();
        end = L.find(delim, start);
        index ++;
    }
    dimensions.push_back(stoi(L.substr(start, end - start)));

    return dimensions;
}

struct site
{
    vector< complex<double> > link;
};


void initialize_lattice(site lattice[], int lattice_size, int number_of_dimensions)
{
    for (int i = 0; i < lattice_size; i+= 1)
    {
        for (int l = 0; l < number_of_dimensions; l += 1)
        {
            lattice[i].link.push_back( complex<double>(init_real, init_imag) );
        }
    }
}

void print_lattice(site lattice[], int lattice_size, int number_of_dimensions)
{
    for (int i = 0; i < lattice_size; i++)
    {
        for (int l = 0; l < number_of_dimensions; l ++)
        {
            cout << lattice[i].link[l];
        }
    }
}


int looper_forward(int index, vector<int> dimensions, int direction)
{
    int divisor = 1;
    int multiple = 1;
    
    for (int i = 0; i <= direction; i++)
        {
            divisor = divisor * dimensions[i];
        }
    for (int i = 0; i < direction; i++)
        {
            multiple = multiple * dimensions[i];
        }
        
    //cout << "divisor: " << divisor << endl;
    //cout << "multiple: " << multiple << endl;
    
    if (direction == 0)
    {
        if ( index % dimensions[direction] == 0 )
        {
            index = index - (dimensions[direction] - 1);
        }
        else
        {
            index = index + 1;
        }
    }
    
    else
    {
        if ( (index % divisor > (dimensions[direction] - 1 ) * multiple) || (index % divisor == 0) )
        {
            index = index - (dimensions[direction] - 1) * multiple;
        }
        else
        {
            index = index + multiple;
        }
    }

    return index;
}


int looper_backward(int index, vector<int> dimensions, int direction)
{
    int divisor = 1;
    int multiple = 1;
    
    for (int i = 0; i <= direction; i++)
        {
            divisor = divisor * dimensions[i];
        }
    for (int i = 0; i < direction; i++)
        {
            multiple = multiple * dimensions[i];
        }
        
    //cout << "divisor: " << divisor << endl;
    //cout << "multiple: " << multiple << endl;
    
    if (direction == 0)
    {
        if ( ( (index - 1) % dimensions[direction] ) == 0 )
        {
            index = index + (dimensions[direction] - 1);
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
            index = index + (dimensions[direction] - 1) * multiple;
        }
        else
        {
            index = index - multiple;
        }
    }

    return index;
}

/*
void find_neighbors(int index, vector<int> dimensions)
{
    for (int i = 0; i < dimensions.size(); i ++)
    {
        cout << dimensions[i] << endl;
    }
}
*/


int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Wrong number of arguments." << endl;
        return 1;
    }

    string L = argv[1];
    
    vector<int> dimensions = user_dimensions(L);
    int number_of_dimensions = dimensions.size();
    
    int lattice_size = 1;
    
    for (int i = 0; i < number_of_dimensions; i ++)
    {
        lattice_size = lattice_size * dimensions[i];
    }

    site lattice[lattice_size];
    initialize_lattice(lattice, lattice_size, number_of_dimensions);
    //print_lattice(lattice, lattice_size, number_of_dimensions);
    
    //find_neighbors(2, dimensions);
    
    /*
    for (int i = 1; i <= 16; i ++)
    {
        cout << "index: " << i << ". ";
        cout << "forward: " << looper_forward(i, dimensions, 3) << endl;
    }
    */

    for (int i = 1; i <= 16; i ++)
    {
        cout << "index: " << i << ". ";
        cout << "backward: " << looper_backward(i, dimensions, 3) << endl;
    }
    
    return 0;
}

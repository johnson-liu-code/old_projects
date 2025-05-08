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



/*
struct U
{
}

*/

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
    
    
    
    
    return 0;
}

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

#include "unitarize.h"
#include "n_choose_k.h"
#include "user_dimensions.h"
#include "initialize_lattice.h"
#include "convert_index_to_single.h"
#include "looper_forward.h"
#include "looper_backward.h"
#include "update.h"
#include "site.h"
#include "print_lattice.h"
#include "initialize_lattice.h"
#include "get_staples.h"
#include "compute_real_plaquettes_at_site.h"
#include "compute_avg_plaquette.h"


//void compute_polyakov_pairs(vector<int> dimension_lengths, complex<double>* polyakov_list, int number_of_dimensions)
//{
//    int spacial_dimension = 1;
//    
//    for (int s = 0; s < number_of_dimensions-1; s++)
//    {
//        spacial_dimension *= dimension_lengths[s];
//    }
//    
//    complex<double> origin_poly = polyakov_list[0];
//    
//    for (int i = 0; i < spacial_dimension; i++)
//    {
//        int sum_of_squares = 0;
//        int leng = 1;
//
//        for (int d = 0; d < number_of_dimensions-1; d++)
//        {
//            int m = i / leng;
//            int mm = m % dimension_lengths[d];
//
//            sum_of_squares += mm*mm;
//
//            leng *= dimension_lengths[d];
//        }
//        
//        double r = sqrt(sum_of_squares);
//
//        complex<double> other_poly = polyakov_list[i];
//
//        complex<double> PP = origin_poly * conj(other_poly);
//    }
//    
//}

double compute_magnetic_flux(vector<int> dimension_lengths, int index, site lattice[])
{
    
    complex<double> flux = 0;
    
//    complex<double> botx(1, 0);
//    complex<double> boty(1, 0);
//    complex<double> botz(1, 0);
//    complex<double> topx(1, 0);
//    complex<double> topy(1, 0);
//    complex<double> topz(1, 0);
    
    double botx = 0;
    double boty = 0;
    double botz = 0;
    double topx = 0;
    double topy = 0;
    double topz = 0;
    
//    botx *= lattice[index-1].link[2] * conj(lattice[index-1].link[1]);
    botx += arg(lattice[index-1].link[2]) + arg(conj(lattice[index-1].link[1]));

//    cout << lattice[index-1].link[2] << endl;
//    cout << lattice[index-1].link[1] << endl;
//    cout << "botx " << arg(lattice[index-1].link[2]) << endl;
//    cout << "botx " << arg(conj(lattice[index-1].link[1])) << endl;
    
//    boty *= lattice[index-1].link[0] * conj(lattice[index-1].link[2]);
    boty += arg(lattice[index-1].link[0]) + arg(conj(lattice[index-1].link[2]));

//    botz *= lattice[index-1].link[1] * conj(lattice[index-1].link[0]);
    botz += arg(lattice[index-1].link[1]) + arg(conj(lattice[index-1].link[0]));
    
    index = looper_forward(index, dimension_lengths, 2);
    
//    botx *= lattice[index-1].link[1];
    botx += arg(lattice[index-1].link[1]);
//    cout << lattice[index-1].link[1] << endl;
//    cout << "botx " << arg(lattice[index-1].link[1]) << endl;
//    topz *= lattice[index-1].link[1] * conj(lattice[index-1].link[0]);
    topz += arg(lattice[index-1].link[1]) + arg(conj(lattice[index-1].link[0]));

    index = looper_forward(index, dimension_lengths, 1);
    
//    topy *= conj(lattice[index-1].link[0]);
    topy += arg(conj(lattice[index-1].link[0]));
    
//    topz *= lattice[index-1].link[0];
    topz += arg(lattice[index-1].link[0]);
    
    index = looper_backward(index, dimension_lengths, 2);
    
//    botx *= conj(lattice[index-1].link[2]);
    botx += arg(conj(lattice[index-1].link[2]));

//    cout << lattice[index-1].link[2] << endl;
//    cout << "botx " << arg(conj(lattice[index-1].link[2])) << endl;
//    botz *= lattice[index-1].link[0];
    botz += arg(lattice[index-1].link[0]);
    
//    topy *= lattice[index-1].link[0] * conj(lattice[index-1].link[2]);
    topy += arg(lattice[index-1].link[0]) + arg(conj(lattice[index-1].link[2]));
    
    index = looper_forward(index, dimension_lengths, 0);
    
//    topx *= conj(lattice[index-1].link[2]);
    topx += arg(conj(lattice[index-1].link[2]));
    
//    topy *= lattice[index-1].link[2];
    topy += arg(lattice[index-1].link[2]);
    
    index = looper_backward(index, dimension_lengths, 1);
    
//    boty *= lattice[index-1].link[2];
    boty += arg(lattice[index-1].link[2]);

//    botz *= conj(lattice[index-1].link[1]);
    botz += arg(conj(lattice[index-1].link[1]));
    
//    topx *= lattice[index-1].link[2] * conj(lattice[index-1].link[1]);
    topx += arg(lattice[index-1].link[2]) + arg(conj(lattice[index-1].link[1]));
//    cout << "topx " << arg(lattice[index-1].link[2]) << endl;
//    cout << "topx " << arg(conj(lattice[index-1].link[1])) << endl;
    
    index = looper_forward(index, dimension_lengths, 2);
    
//    topx *= lattice[index-1].link[1];
    topx += arg(lattice[index-1].link[1]);
//    cout << "topx " << arg(lattice[index-1].link[1]) << endl;
//    topz *= conj(lattice[index-1].link[1]);
    topz += arg(conj(lattice[index-1].link[1]));
//    cout << "botx: " << botx << endl;
//    cout << "arg(botx): " << arg(botx) << endl;
//    
//    cout << "topx: " << topx << endl;
//    cout << "arg(topx): " << arg(topx) << endl;
//    
//    cout << "boty: " << boty << endl;
//    cout << "arg(boty): " << arg(boty) << endl;
//    
//    cout << "topy: " << topy << endl;
//    cout << "arg(topy): " << arg(topy) << endl;
//    
//    cout << "botz: " << botz << endl;
//    cout << "arg(botz): " << arg(botz) << endl;
//    
//    cout << "topz: " << topz << endl;
//    cout << "arg(topz): " << arg(topz) << endl;
//    cout << "x: " << arg(topx) - arg(botx) << endl;
//    cout << "y: " << arg(topy) - arg(boty) << endl;
//    cout << "z: " << arg(topz) - arg(botz) << endl;

//    double divergence = arg(conj(topx)*botx*conj(topy)*boty*conj(topz)*botz);
//    double divergence = arg(topx*botx*topy*boty*topz*botz);

    double divergence = topx + botx + topy + boty + topz + botz;

//    printf("DIVG    %f\n", divergence);

    return divergence;
}



double* fillarr(double* arr)
{
    arr[0] = 2;
    return arr;
}


int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        cout << "Wrong number of arguments." << endl;
        return 1;
    }

    string L = argv[1];
    double beta = atof(argv[2]);
    double scale = atof(argv[3]);
    int traj_length = atof(argv[4]);
    int meas = atof(argv[5]);

    double init_angle = 0;

    vector<int> dimension_lengths = user_dimensions(L);
    
//    auto start = chrono::system_clock::now();
    int number_of_dimensions = dimension_lengths.size();
//    auto end = chrono::system_clock::now();    
//    chrono::duration<double> elapsed = end - start;
//    cout << elapsed.count() << "s\n";

    int lattice_size = 1;

    for (int i = 0; i < number_of_dimensions; i++)
    {
        lattice_size = lattice_size * dimension_lengths[i];
    }

//    auto start = chrono::system_clock::now();
    site lattice[lattice_size];
//    auto end = chrono::system_clock::now();
//    chrono::duration<double> elapsed = end-start;
//    cout << "creating lattice: " << elapsed.count() << "s\n";
    
//    start = chrono::system_clock::now();
    initialize_lattice(lattice, lattice_size, dimension_lengths, init_angle, number_of_dimensions);
//    end = chrono::system_clock::now();
//    elapsed = end - start;
//    cout << "initializing lattice: " << elapsed.count() << "s\n";

    int spacial_dimension = 1;
    for (int s = 0; s < number_of_dimensions-1; s++)
    {
        spacial_dimension *= dimension_lengths[s];
    }
    
    int number_of_boxes = (dimension_lengths[0] - 1) * (dimension_lengths[1] - 1) * (dimension_lengths[2] - 1);

    printf("Lattice:    %s\n", L.c_str());
    printf("Beta:       %f\n", beta);
    printf("Scale:      %f\n", scale);
    printf("Trajecs:    %d\n", traj_length);
    printf("Meas:       %d\n", meas);

//    start = chrono::system_clock::now();
    compute_avg_plaquette(dimension_lengths, lattice_size, lattice, number_of_dimensions);
//    end = chrono::system_clock::now();
//    elapsed = end - start;
//    cout << "compute avg plaquette: " << elapsed.count() << "s\n";

    // Iterate over number of frames.
    for (int traj = 1; traj <= traj_length; traj++)
    {
//        start = chrono::system_clock::now();
        
        // Iterate over sites.
        for (int s = 1; s <= lattice_size; s++)
        {
            // Iterate over directions.
            for (int direction = 0; direction < number_of_dimensions; direction++)
            {
//                start = chrono::system_clock::now();
                complex<double> staples = get_staples(s, dimension_lengths, direction, lattice, number_of_dimensions);
//                end = chrono::system_clock::now();
//                elapsed = end - start;
//                cout << "get staples: " << elapsed.count() << "s\n\n";
                
//                start = chrono::system_clock::now();                
                complex<double> U = lattice[s-1].link[direction];
//                end = chrono::system_clock::now();
//                elapsed = end - start;
//                cout << "get U: " << elapsed.count() << "s\n\n";

//                start = chrono::system_clock::now();
                U = update(U, staples, beta, scale);
//                end = chrono::system_clock::now();
//                elapsed = end - start;
//                cout << "update U: " << elapsed.count() << "s\n\n";

                lattice[s-1].link[direction] = U;
            }
        }
        
//        end = chrono::system_clock::now();
//        elapsed = end - start;
//        cout << "update lattice: " << elapsed.count() << "s\n\n";
        
        if (traj % meas == 0)
        {
//            start = chrono::system_clock::now();
            compute_avg_plaquette(dimension_lengths, lattice_size, lattice, number_of_dimensions);
//            end = chrono::system_clock::now();
//            elapsed = end - start;
//            cout << "compute avg plaquette: " << elapsed.count() << "s\n\n";

//            start = chrono::system_clock::now();
//            polyakov_list_pointer = update_polyakov(dimension_lengths, lattice, polyakov_list, number_of_dimensions);
//            end = chrono::system_clock::now();
//            elapsed = end - start;
//            cout << "update polyakov: " << elapsed.count() << "s\n\n";
//            compute_polyakov_pairs(dimension_lengths, polyakov_list, number_of_dimensions);

//            start = chrono::system_clock::now();
//            double total_div = 0;
//            for (int s = 1; s <= lattice_size; s++)
//            {
//                if (s <= spacial_dimension)
//                {
//                    start = chrono::system_clock::now();
//                    vector<int> multi_index = convert_index_to_multiple(dimension_lengths, s-1);
//                    end = chrono::system_clock::now();
//                    elapsed = end - start;
//                    cout << "convert index to multiple: " << elapsed.count() << "s\n\n";
    
//                    bool skip = false;
//                    for (int m = 0; m < number_of_dimensions-1; m++)
//                    {
//                        cout << multi_index[m] << endl;
//                        if (multi_index[m] >= dimension_lengths[m]-1)
//                        {
//                            skip = true;
//                            break;
//                        }
//                    }
//                    if (skip == false)
//                    {
//                        start = chrono::system_clock::now();
//                        total_div += compute_magnetic_flux(dimension_lengths, s, lattice);
//                        end = chrono::system_clock::now();
//                        elapsed = end - start;
//                        cout << "compute magnetic flux: " << elapsed.count() << "s\n\n";
//                        compute_magnetic_flux(dimension_lengths, s, lattice);
//                    }
//                }
//            }
            
//            double avg_div = total_div / number_of_boxes;
//            end = chrono::system_clock::now();
//            elapsed = end - start;
//            cout << "compute divg: " << elapsed.count() << "s\n\n";
//            cout << "DIVG: " << avg_div << endl;

        }
        
//        end = chrono::system_clock::now();
//        elapsed = end - start;
//        cout << "1 iteration: " << elapsed.count() << "s\n";
    }


//complex<double> a(cos(3./4 * M_PI), sin(3./4 * M_PI));

//cout << a << endl;
//cout << arg(a) << endl;

//    vector< vector<int> > all_indices;
//    all_indices.reserve(lattice_size);
//
//    for (int l = 0; l < lattice_size; l++)
//    {
//        vector<int> temporary;
//        temporary.reserve(number_of_dimensions);
//        all_indices.push_back(temporary);
//    }

//    for (int d = 0; d < number_of_dimensions; d++)
//    {
//        for (int x = 0; x < dimension_lengths[d]; x++)
//        {
//            int y = x;
//            while ( y < lattice_size)
//            {
//                cout << "y: " << y << endl;
//                all_indices[x].push_back(y);
//                y += dimension_lengths[d];
//            }
//        }
//    }
    
//    for (int a = 0; a < lattice_size; a++)
//    {
//        for (int d = 0; d < number_of_dimensions; d++)
//        {
//            cout << all_indices[a][d];
//        }
//        cout << endl;
//        cout << convert_index_to_single(dimension_lengths, all_indices[a]) << endl;
//    }
    
//    vector<int> temp;
//    temp.push_back(1);
//    temp.push_back(1);
//    temp.push_back(0);
//    
//    cout << convert_index_to_single(dimension_lengths, temp) << endl;

//     int index = 0;

//    for (int index = 0; index < lattice_size; index++)
//    {
//        convert_index_to_multiple(dimension_lengths, index);
//        cout << endl;
//    }

//    double y[10];
//    double *a = fillarr(y);
//    cout << y[0] << endl;

//    a = fillarr(y);
//    cout << y[0] << endl;

//    y = a;

//    int lx = 4;
//    int ly = 3;
//    int lz = 2;
//    int i = 19;
//    
//    cout << i/lx << endl;
//    cout << i/(lx*ly) << endl;

//    cout << i % lx << endl;

    return 0;
}
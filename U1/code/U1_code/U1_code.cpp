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
#include <fftw3.h>

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

complex<double> *****lattice_4d;
fftw_complex *plp, *plpout, *plp_recover;

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


complex<double> get_staples_4d(vector<int> dimension_lengths, int t, int x, int y, int z, int dir)
{
    complex<double> staples, stptmp;
        
    switch(dir)
    {
        case 0:
        // upward staples
        stptmp  = lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][1];
        stptmp *= conj(lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][1]);
        staples = stptmp;
        stptmp  = lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][2];
        stptmp *= conj(lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][2]);
        staples += stptmp;
        stptmp  = lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][3];
        stptmp *= conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][3]);
        staples += stptmp;

        // downward staples
        stptmp  = conj(lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][(z+1)%dimension_lengths[3]][1]);
        stptmp *= conj(lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][dir]);
        stptmp *= lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][1];
        staples += stptmp;
        stptmp  = conj(lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][(z+1)%dimension_lengths[3]][2]);
        stptmp *= conj(lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][dir]);
        stptmp *= lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][2];
        staples += stptmp;
        stptmp  = conj(lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][(z+1)%dimension_lengths[3]][3]);
        stptmp *= conj(lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][z][dir]);
        stptmp *= lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][z][3];
        staples += stptmp;
        break;

        case 1:
        // upward staples
        stptmp  = lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][0];
        stptmp *= conj(lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][0]);
        staples = stptmp;
        stptmp  = lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][2];
        stptmp *= conj(lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][2]);
        staples += stptmp;
        stptmp  = lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][3];
        stptmp *= conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][3]);
        staples += stptmp;

        // downward staples
        stptmp  = conj(lattice_4d[t][x][(y+1)%dimension_lengths[2]][(z-1+dimension_lengths[3])%dimension_lengths[3]][0]);
        stptmp *= conj(lattice_4d[t][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][dir]);
        stptmp *= lattice_4d[t][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][0];
        staples += stptmp;
        stptmp  = conj(lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][(y+1)%dimension_lengths[2]][z][2]);
        stptmp *= conj(lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][dir]);
        stptmp *= lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][2];
        staples += stptmp;
        stptmp  = conj(lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][(y+1)%dimension_lengths[2]][z][3]);
        stptmp *= conj(lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][z][dir]);
        stptmp *= lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][z][3];
        staples += stptmp;
        break;

        case 2:
        // upward staples
        stptmp  = lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][0];
        stptmp *= conj(lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][0]);
        staples = stptmp;
        stptmp  = lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][1];
        stptmp *= conj(lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][1]);
        staples += stptmp;
        stptmp  = lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][3];
        stptmp *= conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][3]);
        staples += stptmp;

        // downward staples
        stptmp  = conj(lattice_4d[t][(x+1)%dimension_lengths[1]][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][0]);
        stptmp *= conj(lattice_4d[t][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][dir]);
        stptmp *= lattice_4d[t][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][0];
        staples += stptmp;
        stptmp  = conj(lattice_4d[t][(x+1)%dimension_lengths[1]][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][1]);
        stptmp *= conj(lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][dir]);
        stptmp *= lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][1];
        staples += stptmp;
        stptmp  = conj(lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][(x+1)%dimension_lengths[1]][y][z][3]);
        stptmp *= conj(lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][z][dir]);
        stptmp *= lattice_4d[(t-1+dimension_lengths[0])%dimension_lengths[0]][x][y][z][3];
        staples += stptmp;
        break;
            
        case 3:
        // upward staples
        stptmp  = lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][0];
        stptmp *= conj(lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][0]);
        staples = stptmp;
        stptmp  = lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][1];
        stptmp *= conj(lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][1]);
        staples += stptmp;
        stptmp  = lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][2];
        stptmp *= conj(lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][dir]);
        stptmp *= conj(lattice_4d[t][x][y][z][2]);
        staples += stptmp;

        // downward staples
        stptmp  = conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][0]);
        stptmp *= conj(lattice_4d[t][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][dir]);
        stptmp *= lattice_4d[t][x][y][(z-1+dimension_lengths[3])%dimension_lengths[3]][0];
        staples += stptmp;
        stptmp  = conj(lattice_4d[(t+1)%dimension_lengths[0]][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][1]);
        stptmp *= conj(lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][dir]);
        stptmp *= lattice_4d[t][x][(y-1+dimension_lengths[2])%dimension_lengths[2]][z][1];
        staples += stptmp;
        stptmp  = conj(lattice_4d[(t+1)%dimension_lengths[0]][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][2]);
        stptmp *= conj(lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][dir]);
        stptmp *= lattice_4d[t][(x-1+dimension_lengths[1])%dimension_lengths[1]][y][z][2];
        staples += stptmp;
        break;
    }
    
    return staples;
}


double measure_avg_plaq_4d(vector<int> dimension_lengths)
{
    complex<double> staple, stptmp, p;
    int x, y, z, t;

    p = (1.0, 0.0);
    
    for(t = 0; t < dimension_lengths[0]; t++)
    {
        for(x = 0; x < dimension_lengths[1]; x++)
        {
            for(y = 0; y < dimension_lengths[2]; y++)
            {
                for(z = 0; z < dimension_lengths[3]; z++)
                {
                    // p01, p02, p03
                    stptmp  = lattice_4d[t][x][y][z][0];
                    stptmp *= lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][1];
                    stptmp *= conj(lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][0]);
                    stptmp *= conj(lattice_4d[t][x][y][z][1]);
                    p += stptmp;

                    stptmp  = lattice_4d[t][x][y][z][0];
                    stptmp *= lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][2];
                    stptmp *= conj(lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][0]);
                    stptmp *= conj(lattice_4d[t][x][y][z][2]);
                    p += stptmp;

                    stptmp  = lattice_4d[t][x][y][z][0];
                    stptmp *= lattice_4d[t][x][y][(z+1)%dimension_lengths[3]][3];
                    stptmp *= conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][0]);
                    stptmp *= conj(lattice_4d[t][x][y][z][3]);
                    p += stptmp;
                  
                    // p12, p13
                    stptmp  = lattice_4d[t][x][y][z][1];
                    stptmp *= lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][2];
                    stptmp *= conj(lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][1]);
                    stptmp *= conj(lattice_4d[t][x][y][z][2]);
                    p += stptmp;

                    stptmp  = lattice_4d[t][x][y][z][1];
                    stptmp *= lattice_4d[t][x][(y+1)%dimension_lengths[2]][z][3];
                    stptmp *= conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][1]);
                    stptmp *= conj(lattice_4d[t][x][y][z][3]);
                    p += stptmp;

                    // p23
                    stptmp  = lattice_4d[t][x][y][z][2];
                    stptmp *= lattice_4d[t][(x+1)%dimension_lengths[1]][y][z][3];
                    stptmp *= conj(lattice_4d[(t+1)%dimension_lengths[0]][x][y][z][2]);
                    stptmp *= conj(lattice_4d[t][x][y][z][3]);
                    p += stptmp;
                }
            }
        }
    }

    p /= dimension_lengths[0]*dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]*6;
    
    double avg_p = p.real();
    
    return avg_p;
}

int xyz_index_4d(vector<int> dimension_lengths, int x, int y, int z)
{
    return z + dimension_lengths[3]*(y + dimension_lengths[2]*x);
}

complex<double> measure_avg_poly_4d(vector<int> dimension_lengths)
{
    complex<double> poly, poly_tot = 0, poly_avg;
    int t, x, y, z;
    
    for (x = 0; x < dimension_lengths[1]; x++)
    {
        for (y = 0; y < dimension_lengths[2]; y++)
        {
            for (z = 0; z < dimension_lengths[3]; z++)
            {
                poly = lattice_4d[0][x][y][z][3];
                
                for (t = 1; t < dimension_lengths[0]; t++)
                {
                    poly *= lattice_4d[t][x][y][z][3];
                }
                poly_tot += poly;
                plp[xyz_index_4d(dimension_lengths, x, y, z)][0] = poly.real();
                plp[xyz_index_4d(dimension_lengths, x, y, z)][1] = poly.imag();
            }
        }
    }
    double volume = dimension_lengths[0]*dimension_lengths[1]*dimension_lengths[2];
    
    poly_avg = poly_tot / volume;
    
    return poly_avg;
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

//    printf("Lattice:    %s\n", L.c_str());
//    printf("Beta:       %f\n", beta);
//    printf("Scale:      %f\n", scale);
//    printf("Trajecs:    %d\n", traj_length);
//    printf("Meas:       %d\n", meas);
//    printf("######################\n");

    double init_angle = 0;

    vector<int> dimension_lengths = user_dimensions(L);
    
    int number_of_dimensions = dimension_lengths.size();

    int lattice_size = 1;

    for (int i = 0; i < number_of_dimensions; i++)
    {
        lattice_size = lattice_size * dimension_lengths[i];
    }

    if (number_of_dimensions != 4)
    {
        double avg_plaq;
        
        site lattice[lattice_size];

        initialize_lattice(lattice, lattice_size, dimension_lengths, init_angle, number_of_dimensions);

        int spacial_dimension = 1;
        for (int s = 0; s < number_of_dimensions-1; s++)
        {
            spacial_dimension *= dimension_lengths[s];
        }
        
        int number_of_boxes = (dimension_lengths[0] - 1) * (dimension_lengths[1] - 1) * (dimension_lengths[2] - 1);

        compute_avg_plaquette(dimension_lengths, lattice_size, lattice, number_of_dimensions);

        // Iterate over number of frames.
        for (int traj = 1; traj <= traj_length; traj++)
        {        
            // Iterate over sites.
            for (int s = 1; s <= lattice_size; s++)
            {
                // Iterate over directions.
                for (int direction = 0; direction < number_of_dimensions; direction++)
                {
                    complex<double> staples = get_staples(s, dimension_lengths, direction, lattice, number_of_dimensions);
                    complex<double> U = lattice[s-1].link[direction];
                    U = update(U, staples, beta, scale);
                    lattice[s-1].link[direction] = U;
                }
            }
            
            if (traj % meas == 0)
            {
                avg_plaq = compute_avg_plaquette(dimension_lengths, lattice_size, lattice, number_of_dimensions);
                printf("PLAQ    %g\n", avg_plaq);
            }
            
        }
    }
    else
    {
        int t, x, y, z, dir;
        
//        complex<double> *****lattice_4d;
        
//        lattice_4d = (complex<double> *****)malloc(dimension_lengths[0] * sizeof(complex<double> ****));
//        for (t = 0; t < dimension_lengths[0]; t++)
//        {
//            lattice_4d[t] = (complex<double> ****)malloc(dimension_lengths[1] * sizeof(complex<double> ***));
//            for (x = 0; x < dimension_lengths[1]; x++)
//            {
//                lattice_4d[t][x] = (complex<double> ***)malloc(dimension_lengths[2] * sizeof(complex<double> **));
//                for (y = 0; y < dimension_lengths[2]; y++)
//                {
//                    lattice_4d[t][x][y] = (complex<double> **)malloc(dimension_lengths[3] * sizeof(complex<double> *));
//                    for (z = 0; z < dimension_lengths[3]; z++)
//                    {
//                        lattice_4d[t][x][y][z] = (complex<double> *)malloc(4 * sizeof(complex<double>));
//                        for (dir = 0; dir < 4; dir++)
//                        {
////                            if (x%4==0 and y%4==0 and z%4==0 and dir == 0)
////                            {
////                                lattice_4d[t][x][y][z][dir] = 1.0;
////                            }
////                            else
////                            {
//                                lattice_4d[t][x][y][z][dir] = 0.0;
////                            }
//                        }
//                    }
//                }
//            }
//        }

        plp = (fftw_complex*) fftw_malloc( dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]*sizeof(fftw_complex) );
        plpout = (fftw_complex*) fftw_malloc( dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]*sizeof(fftw_complex) );
        plp_recover = (fftw_complex*) fftw_malloc( dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]*sizeof(fftw_complex) );

        fftw_plan fftplan_f, fftplan_b;

        fftplan_f = fftw_plan_dft_3d( dimension_lengths[1], dimension_lengths[2], dimension_lengths[3], plp, plpout, FFTW_FORWARD, FFTW_ESTIMATE );
        fftplan_b = fftw_plan_dft_3d( dimension_lengths[1], dimension_lengths[2], dimension_lengths[3], plpout, plp_recover, FFTW_BACKWARD, FFTW_ESTIMATE );
        
//        complex<double> staples;
//        double avg_plaq;
//        complex<double> poly;

//        avg_plaq = measure_avg_plaq_4d(dimension_lengths);
//        poly = measure_avg_poly_4d(dimension_lengths);
//        printf("PLAQ   %g   POLY    %g\n", avg_plaq, poly.real());
        
        for (x = 0; x < dimension_lengths[1]; x++)
        {
            for (y = 0; y < dimension_lengths[2]; y++)
            {
                for (z = 0; z < dimension_lengths[3]; z++)
                {
                    int index = xyz_index_4d(dimension_lengths, x, y, z);
//                    printf("x: %d y: %d z: %d\n", x, y, z);
//                    printf("x/: %d y/: %d z/: %d\n\n", x%2, y%2, z%2);

                    if ( x%4==0 and y%4==0 and z%4==0)
                    {
//                        printf("x: %d   y: %d   z: %d\n", x, y, z);
                        plp[index][0] = 1.0;
                        plp[index][1] = 0.0;
                        
                    }
                    else
                    {
                        plp[index][0] = 0.0;
                        plp[index][1] = 0.0;
                    }
                }
            }
        }
        
        plp[0][0] = 1.0;
        plp[0][1] = 0.0;

        fftw_execute(fftplan_f);
        for (int j = 0; j < dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]; j++)
        {
            plpout[j][0] = plpout[j][0]*plpout[j][0] + plpout[j][1]*plpout[j][1];
            plpout[j][1] = 0;
        }

        fftw_execute(fftplan_b);            
//        for (int j = 0; j < dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]; j++)
//        {
//            printf("plp %g  recover %g\n", plp[j][0], plp_recover[j][0]/(dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]) );
//        }

        for (x = 0; x < dimension_lengths[1]; x++)
        {
            for (y = 0; y < dimension_lengths[2]; y++)
            {
                for (z = 0; z < dimension_lengths[3]; z++)
                {
                    int index = xyz_index_4d(dimension_lengths, x, y, z);
                    plp_recover[index][0] = plp_recover[index][0]/(dimension_lengths[1]*dimension_lengths[2]*dimension_lengths[3]);
                    printf("x:%d y:%d z:%d  plp_rec:%g\n", x, y, z, plp_recover[index][0]);

                }
            }
        }

    }

    return 0;
}
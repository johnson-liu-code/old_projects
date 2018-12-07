#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

#include "zeng_eos.h"
#include "vinet_eos.h"
#include "bme_eos.h"
#include "compute_pressure_mass.h"
#include "euler.h"
#include "invert_3x3_matrix.h"
#include "solve_quadratic.h"
#include "interpolate_surface.h"
#include "rk4.h"
#include "trajecs.h"



double G = 6.673 * pow(10, -8);                     // cm^3 g^-1 s^-2 (Graviational constant).

vector<double> parse_parameters(string user_input)
{
    string delim = "x";

    vector<double> parameters;
    int index = 0;

    int start = 0;
    int end = user_input.find(delim);
    
    while (end != string::npos)
    {
        parameters.push_back( stod( user_input.substr( start, end - start ) ) );

        start = end + delim.length();
        end = user_input.find( delim, start );
        index++;
    }
    parameters.push_back( stod( user_input.substr( start, end - start) ) );

    return parameters;
}


int main(int argc, char* argv[])
{
    
    bool print_meas = false;
    bool starting_euler = false;
    
    for (int i = 1; i < argc; i++)
    {
        if (string(argv[i]) == "-p")
        {
            print_meas = true;
        }
        if (string(argv[i]) == "-s")
        {
            starting_euler = true;
        }
    }
    
    int number_of_layers = atof(argv[1]);                                               // Number of layers within the planet.
    
    if (number_of_layers != 1 && number_of_layers != 2 && number_of_layers != 3)
    {
        printf("Please enter in '1', '2', or '3' for the first positional argument\n.");
        exit(EXIT_FAILURE);
    }
    
    string radii_input = argv[2];                                                                // List of the layer radii.
    string rho_input = argv[3];                                                                 // List of the densities at zero pressure.
    string K_input = argv[4];                                                                     // List of the bulk moduli of the materials.
    
    vector<double> radii_list = parse_parameters(radii_input);
    vector<double> rho_list = parse_parameters(rho_input);
    vector<double> K_list = parse_parameters(K_input);

    double pressure = atof(argv[5]);                                                           // (GPa) The pressure at the center of the planet.
    double delta_r = atof(argv[6]);                                                             // (cm) Integration step size.
    double r = delta_r;                                                                                  // (cm) Initial radius to start integration.
//    double Rp = atof(argv[7]);                                                                     // (cm) Radius of the planet.
//    double Mp = atof(argv[8]);                                                                    // (g) Mass of the planet.

    string integrator = argv[7];                                                                     // Select (e)uler, (r)unge-kutta 4th order, or euler-(c)romer.
    string eos = argv[8];
    
    double expected_radius = atof(argv[9]);
    double expected_mass = atof(argv[10]);
    double expected_core_mass_frac = atof(argv[11]);
    
    double mass_core = expected_core_mass_frac * expected_mass;
    
//    for (int i = 0; i < radii_list.size(); i++)
//    {
//        radii_list[i] = radii_list[i] * expected_radius;
//        printf("radii_list: %f\n", radii_list[i]);
//    }

    double thresh = pow(10., -10.);          // Threshold for computing rho.

    double frac_radius;
    double frac_mass;

    printf("Initial Pressure (GPa): %f\n", pressure);
    printf("Integrator: %s\n", integrator.c_str());


    double K0p = 0;
    if (eos == "v")
    {
        K0p = 6.08;
    }
    else if (eos == "b")
    {
        K0p = 5.5;
    }
    
    double rho = 1;                                                                                         // (g cm^-3) Intial guess for rho.
    
    if (eos == "z")
    {
        rho = compute_rho_zeng(pressure, K_list[0], rho_list[0], rho, thresh);  // Compute rho from initial guess.
    }
    else if (eos == "v")
    {
        rho = compute_rho_vinet(pressure, K_list[0], K0p, rho_list[0], rho, thresh);
    }
    else if (eos == "b")
    {
        rho = compute_rho_bme(pressure, K_list[0], K0p, rho_list[0], rho, thresh);
    }

    double mass = rho * 4*M_PI/3 * r*r*r;                                               // (g) Initial mass.

    double interface;


    
    vector<double> all_quantities;
    all_quantities.reserve(9);
    
    all_quantities = run_trajectory(number_of_layers, print_meas, pressure, mass, integrator, rho, r, delta_r, radii_list, rho_list, K_list, K0p, thresh, G, eos, mass_core, expected_mass);

    pressure = all_quantities[0];
    mass = all_quantities[1];
    rho = all_quantities[2];
    double prev_pressure = all_quantities[3], prevprev_pressure = all_quantities[4], prev_mass = all_quantities[5], prevprev_mass = all_quantities[6];
    r = all_quantities[7];

    // (P, R) format for interpolation for surface radius.
   vector< vector<double> > three_points_pressure = {{pressure, r}, {prev_pressure, r - delta_r}, {prevprev_pressure, r - 2*delta_r}};
    vector<double> final_pressure_radius = interpolate_surface_radius(three_points_pressure, r);

    double final_pressure = final_pressure_radius[0];
    double final_radius = final_pressure_radius[1];
    
    // (M, R) format for interpolation of surface mass.
//    vector< vector<double> > three_points_mass = {{mass, r}, {prev_mass, r - delta_r}, {prevprev_mass, r - 2*delta_r}};
//    double final_mass = interpolate_surface_mass(three_points_mass, final_radius);

//    frac_radius = final_radius / Rp;
//    frac_mass = final_mass / Mp;
//    frac_mass = mass / Mp;
//   printf("frac_r: %.10g   density: %.10g     pressure: %.10g    frac_mass: %.10g\n", frac_radius, rho, pressure, frac_mass);

    double mass_iron, mass_rock;
    mass_iron = all_quantities[8];
//    if (radii_list[0] > expected_radius)
//    {
//        mass_iron = mass;
//    }
    mass_rock = mass - mass_iron;
    
    printf("mass_iron: %10f\n", mass_iron);
    printf("mass_rock: %f\n", mass_rock);

    
    double radius_ratio = final_radius/expected_radius;
    double mass_ratio = mass/expected_mass;
    
    double mass_frac_iron = mass_iron/mass;
    double mass_frac_rock = mass_rock/mass;
    double core_mass_frac_ratio = mass_frac_iron / expected_core_mass_frac;
    
    printf("mass_frac_iron: %.6g\n", mass_frac_iron);

    printf("r: %.6g     density: %.6g     pressure: %.6g     mass: %.6g     mass_iron: %.6g     mass_rock: %.6g\n", final_radius, rho, final_pressure, mass, mass_iron, mass_rock);
//    printf("radius_ratio: %.10g    mass_ratio: %.10g    mass_frac_iron: %.10g    mass_frac_rock: %.10g\n", radius_ratio, mass_ratio, mass_frac_iron, mass_frac_rock);
//    printf("radius: %.10g    mass_ratio: %.10g    mass_frac_iron: %.10g    mass_frac_rock: %.10g\n", r, mass_ratio, mass_frac_iron, mass_frac_rock);
//    printf("radius: %.10g    mass_ratio: %.10g    core_mass_frac_ratio: %.10g\n", r, mass_ratio, core_mass_frac_ratio);
    printf("core_mass_frac: %.10g\n", mass_frac_iron);
//    printf("radius_ratio: %.10g    mass_ratio: %.10g    core_mass_frac_ratio: %.10g\n", radius_ratio, mass_ratio, core_mass_frac_ratio);
//    printf("radius_ratio: %.10g    mass_ratio: %.10g    core_mass_frac_ratio: %.10g\n", radius_ratio, mass_ratio, core_mass_frac_ratio);
    
    typedef numeric_limits< double > dbl;
    
    cout.precision(dbl::max_digits10);
    cout << "radius_ratio: " << radius_ratio << "    mass_ratio: " << mass_ratio << "    core_mass_frac_ration: " << core_mass_frac_ratio << endl;
}
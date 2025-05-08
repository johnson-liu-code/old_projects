#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <complex>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;



// Compute pressure.
double compute_new_pressure(double pressure, double mass, double rho, double r, double delta_r, double G)
{
    return pressure - (( rho * (G * mass / (r*r) ) ) * delta_r) * pow(10, -10);
}

// Compute mass.
double compute_new_mass(double mass, double rho, double r, double delta_r)
{
    return mass + ( 4. * M_PI * r*r * rho * delta_r);
}
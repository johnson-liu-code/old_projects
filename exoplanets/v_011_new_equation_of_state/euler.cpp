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

#include "compute_pressure_mass.h"
#include "zeng_eos.h"



// Euler update.
vector<double> euler_update(double pressure, double mass, double rho, double r, double delta_r, double K0, double rho0, double thresh, double G)
{
    vector<double> quantities;
    quantities.reserve(3);
    
    quantities.push_back( compute_new_pressure(pressure, mass, rho, r, delta_r, G) );          // This is the Euler algorithm. For the Euler-Cromer algorithm, compute mass first then pressure.
    quantities.push_back( compute_new_mass(mass, rho, r, delta_r) );
    quantities.push_back( compute_rho_zeng(pressure, K0, rho0, rho, thresh) );
    
    return quantities;
}

// Euler-Cromer update. It doesn't seem like this is working.
vector<double> euler_cromer_update(double pressure, double mass, double rho, double r, double delta_r, double K0, double rho0, double thresh, double G)
{
    vector<double> quantities;
    quantities.reserve(3);

    quantities.push_back( compute_new_mass(mass, rho, r, delta_r) );    
    quantities.push_back( compute_new_pressure(pressure, mass, rho, r, delta_r, G) );
    quantities.push_back( compute_rho_zeng(pressure, K0, rho0, rho, thresh) );
    
    return quantities;
}
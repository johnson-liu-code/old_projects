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

#include "zeng_eos.h"
#include "vinet_eos.h"
#include "bme_eos.h"
#include "solve_2x2_matrix.h"
#include "solve_quadratic.h"



// 4th Order Runge-Kutta update.
vector<double> RK4_update(double pressure, double mass, double rho, double r, double delta_r, double K0, double K0p, double rho0, double thresh, double G, string eos, vector<double> temporary_rho)
{
//    
//    double x1 = r;
//    double x2 = r-delta_r;
//    double x3 = r-2*delta_r;
//    double y1 = rho;
//    double y2 = temporary_rho[2];
//    double y3 = temporary_rho[1];
//
//    vector< vector<double> > three_points = {{y1, x1}, {y2, x2}, {y3, x3}};
//    vector<double> constants = solve_quadratic_coefficients(three_points);
//
//    double rho_next = constants[0] + constants[1]*(r+delta_r/2.) + constants[2]*(r+delta_r/2.)*(r+delta_r/2.);
//    double rho_nextnext = constants[0] + constants[1]*(r+delta_r) + constants[2]*(r+delta_r)*(r+delta_r);

//    printf("%.30g\n%.30g\n%.30g\n", y1, y2, y3);
    
//    vector<double> first_point;
//    first_point.push_back(x1);
//    first_point.push_back(y1);
//    vector<double> second_point;
//    second_point.push_back(x2);
//    second_point.push_back(y2);
//    
//    vector<double> constants = solve_2x2_constants(first_point, second_point);
//
//    double rho_next = constants[0] + constants[1]*(r+delta_r/2.);
//    double rho_nextnext = constants[0] + constants[1]*(r+delta_r);
    
    // Compute k and l for pressure and mass.
    double k1 = delta_r * ( -rho * (G * mass)/(r*r) ) * pow(10, -10);                 // pressure
    double l1 = delta_r * ( 4. * M_PI * rho * r*r );                                                // mass    
    
    double k2 = delta_r * ( -rho * (G * (mass + l1/2.))/((r + delta_r/2.)*(r + delta_r/2.)) ) * pow(10, -10);
    double l2 = delta_r * ( 4. * M_PI * rho * (r + delta_r/2.)*(r + delta_r/2.) );

    double k3 = delta_r * ( -rho * (G * (mass + l2/2.))/((r + delta_r/2.)*(r + delta_r/2.)) ) * pow(10, -10);
    double l3 = l2;
    // l3 is equal to l2 because the mass does not depend explicitly on pressure.

    double k4 = delta_r * ( -rho* (G * (mass + l3))/((r + delta_r)*(r + delta_r)) ) * pow(10, -10);
    double l4 = delta_r * ( 4. * M_PI * rho * (r + delta_r)*(r + delta_r) );
    
    double k = (1./6.) * (k1 + 2.*k2 + 2.*k3 + k4);
    double l = (1./6.) * (l1 + 2.*l2 + 2.*l3 + l4);

    vector<double> quantities;
    quantities.reserve(3);
    quantities.push_back(pressure + k);     // pressure
    quantities.push_back(mass + l);         // mass
    
    if (eos == "z")
    {
        quantities.push_back( compute_rho_zeng(pressure, K0, rho0, rho, thresh) );
    }
    else if (eos == "v")
    {
        quantities.push_back( compute_rho_vinet(pressure, K0, K0p, rho0, rho, thresh) );
    }
    else if (eos == "b")
    {
        quantities.push_back( compute_rho_bme(pressure, K0, K0p, rho0, rho, thresh) );
    }
    return quantities;
}
#ifndef COMPUTE_PRESSURE_MASS_H
#define COMPUTE_PRESSURE_MASS_H

using namespace std;

double compute_new_pressure(double pressure, double mass, double rho, double r, double delta_r, double G);
double compute_new_mass(double mass, double rho, double r, double delta_r);

#endif
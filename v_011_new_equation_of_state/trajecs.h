#ifndef TRAJECS_H
#define TRAJECS_H

using namespace std;

vector<double> run_trajectory(double number_of_layers, bool print_meas, double pressure, double mass, string integrator, double rho, double r, double delta_r, vector<double> radii_list, vector<double> rho_list, vector<double> K_list, double K0p, double thresh, double G, string eos, double mass_core, double Mp);

#endif
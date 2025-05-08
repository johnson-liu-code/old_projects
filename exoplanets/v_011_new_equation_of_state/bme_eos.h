#ifndef BME_EOS_H
#define BME_EOS_H

using namespace std;

double bme_eos(double K0, double K0p, double rho0, double x);
double compute_rho_bme(double pressure, double K0, double K0p, double rho0, double rho, double thresh);

#endif
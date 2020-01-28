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



double vinet_eos(double K0, double K0p, double rho0, double x)
{
    return 3. * K0 * pow(x, 2./3) * (1. - pow(x, -1./3)) * exp(3./2 * (K0p - 1.)*(1. - pow(x, -1./3)));
}

double compute_rho_vinet(double pressure, double K0, double K0p, double rho0, double rho, double thresh)
{
    
    double x = 1.;
    double previous_x = x;
    
    double change = .1;                             // Initial incremental change in x.
    bool found = false;
    
    while (found == false)
    {
        if ( vinet_eos(K0, K0p, rho0, x) > pressure )
        {
            x -= change;                            // Subtract change from x if we overshoot.
        }
        else
        {
            x += change;                            // Add change to x if we undershoot.
        }
        
        if ( abs(vinet_eos(K0, K0p, rho0, x) - pressure) < thresh)         // Stop if we get x = a within the desired tolerance.
        {
            found = true;
            return rho0 * x;
        }
        
        else
        {
            if ( (vinet_eos(K0, K0p, rho0, previous_x) > pressure and vinet_eos(K0, K0p, rho0, x) < pressure) or (vinet_eos(K0, K0p, rho0, previous_x) < pressure and vinet_eos(K0, K0p, rho0, x) > pressure) )
            {
                change *= .1;                       // Progressively make the change smaller and smaller to home in on a.
            }
            
            previous_x = x;
        }
    }
}
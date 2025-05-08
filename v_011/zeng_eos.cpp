
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



double pow_diff(double num)                         // Find the difference x^(7/3) - x^(5/3).
{
    return pow(num, 7./3.) - pow(num, 5./3.);
}

double compute_rho_zeng(double pressure, double K0, double rho0, double rho, double thresh)      // Find the density.
{
    double a = (2. * pressure) / (3. * K0);
    double x = rho/rho0;
    double previous_x = x;
    
    double change = .1;                             // Initial incremental change in x.
    bool found = false;
    
    while (found == false)
    {
        if ( pow_diff(x) > a )
        {
            x -= change;                            // Subtract change from x if we overshoot.
        }
        else
        {
            x += change;                            // Add change to x if we undershoot.
        }
        
        if ( abs(pow_diff(x) - a) < thresh)         // Stop if we get x = a within the desired tolerance.
        {
            found = true;
            return rho0 * x;
        }
        
        else
        {
            if ( (pow_diff(previous_x) > a and pow_diff(x) < a) or (pow_diff(previous_x) < a and pow_diff(x) > a) )
            {
                change *= .1;                       // Progressively make the change smaller and smaller to home in on a.
            }
            
            previous_x = x;
        }
    }
}
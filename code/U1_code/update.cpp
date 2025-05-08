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

#include "unitarize.h"

complex<double> update(complex<double> U, complex<double> staples, double beta, double scale)
{
    double theta = scale * 2 * ( drand48()-.5 );
    
    complex<double> U_change(cos(theta), sin(theta));
    
    complex<double> new_U = unitarize(U * U_change);

    double old_action = (U*staples).real();
    double new_action = (new_U*staples).real();

    if (new_action > old_action)
    {
        U = new_U;
    }
    else
    {
        double r = drand48();

        if (r < exp(beta * (new_action - old_action)))
        {
            U = new_U;
        }
    }
    
    return U;
}
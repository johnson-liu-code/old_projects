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

#include "solve_quadratic.h"



vector<double> interpolate_surface_radius(vector< vector<double> > three_points, double radius)
{
    vector<double> pressure_radius;
    vector<double> coefficients = solve_quadratic_coefficients(three_points);
    
    double a0 = coefficients[0], a1 = coefficients[1], a2 = coefficients[2];
    
//    cout << "a0: " << a0 << ", a1: " << a1 << ", a2: " << a2 << endl;
    
    double root1 = (-a1 + sqrt(a1*a1 - 4*a2*a0)) / (2*a2);
    double root2 = (-a1 - sqrt(a1*a1 - 4*a2*a0)) / (2*a2);


    if ( abs(radius - root1 ) < abs(radius - root2) )
    {
        double pressure  = a0 + a1*root1 + a2*root1*root1;
        pressure_radius = {pressure, root1};
//        return root1;
    }
    else
    {
        double pressure = a0 + a1*root2 + a2*root2*root2;
        pressure_radius = {pressure, root2};
//        return root2;
    }
    return pressure_radius;
}

double interpolate_surface_mass(vector< vector<double> > three_points, double radius)
{
    vector<double> coefficients = solve_quadratic_coefficients(three_points);
    
//    cout << "a0: " << coefficients[0] << endl;
//    cout << "a1: " << coefficients[1] << endl;
//    cout << "a2: " << coefficients[2] << endl;
    
    double mass = coefficients[0] + coefficients[1]*radius + coefficients[2]*radius*radius;
    
    return mass;
}
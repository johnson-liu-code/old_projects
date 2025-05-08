#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <typeinfo>
#include <iostream>
#include <vector>


using namespace std;



vector<double> solve_2x2_constants(vector<double> first_point, vector<double> second_point)
{
    double x1 = first_point[0];
    double y1 = first_point[1];
    double x2 = second_point[0];
    double y2 = second_point[1];

    double a1 = (1./(x2-x1)) * (x2*y1 - x1*y2);
    double a2 = (1./(x2-x1)) * (y2 - y1);
    
    vector<double> constants;
    constants.push_back(a1);
    constants.push_back(a2);
    
    return constants;
}
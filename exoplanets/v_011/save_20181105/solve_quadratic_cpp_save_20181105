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

#include "invert_3x3_matrix.h"



vector<double> solve_quadratic_coefficients(vector< vector<double> > three_points)
{
    matrixStruct mat;

    // Matrix to represent three polynomials.
    mat.matrix[0][0] = 1;
    mat.matrix[0][1] = three_points[0][1];
    mat.matrix[0][2] = three_points[0][1]*three_points[0][1];
    
    mat.matrix[1][0] = 1;
    mat.matrix[1][1] = three_points[1][1];
    mat.matrix[1][2] = three_points[1][1]*three_points[1][1];
    
    mat.matrix[2][0] = 1;
    mat.matrix[2][1] = three_points[2][1];
    mat.matrix[2][2] = three_points[2][1]*three_points[2][1];

    // Invert the matrix.
    matrixStruct inv_mat = invert_3x3_matrix(mat);
        
    double y0 = three_points[0][0], y1 = three_points[1][0], y2 = three_points[2][0];

    // Find the coefficents a0, a1, and a2 of the polynomial.
    double a0 = inv_mat.matrix[0][0]*y0 + inv_mat.matrix[0][1]*y1 + inv_mat.matrix[0][2]*y2;
    double a1 = inv_mat.matrix[1][0]*y0 + inv_mat.matrix[1][1]*y1 + inv_mat.matrix[1][2]*y2;
    double a2 = inv_mat.matrix[2][0]*y0 + inv_mat.matrix[2][1]*y1 + inv_mat.matrix[2][2]*y2;

//    printf("a0: %f, a1: %f, a2: %f\n", a0, a1, a2);

    vector<double> coefficients = {a0, a1, a2};
    
    return coefficients;
}
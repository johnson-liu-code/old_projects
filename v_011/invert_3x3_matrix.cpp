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



// Function to invert a 3x3 matrix.
matrixStruct invert_3x3_matrix(matrixStruct mat)
{
    double determinant = (mat.matrix[1][1]*mat.matrix[2][2] - mat.matrix[1][2]*mat.matrix[2][1])*mat.matrix[0][0] - (mat.matrix[1][0]*mat.matrix[2][2] - mat.matrix[1][2]*mat.matrix[2][0])*mat.matrix[0][1] + (mat.matrix[1][0]*mat.matrix[2][1] - mat.matrix[1][1]*mat.matrix[2][0])*mat.matrix[0][2];

    matrixStruct m;

    m.matrix[0][0] = (mat.matrix[1][1]*mat.matrix[2][2] - mat.matrix[1][2]*mat.matrix[2][1]) / determinant;
    m.matrix[0][1] = -(mat.matrix[0][1]*mat.matrix[2][2] - mat.matrix[0][2]*mat.matrix[2][1]) / determinant;
    m.matrix[0][2] = (mat.matrix[0][1]*mat.matrix[1][2] - mat.matrix[0][2]*mat.matrix[1][1]) / determinant;
    
    m.matrix[1][0] = -(mat.matrix[1][0]*mat.matrix[2][2] - mat.matrix[1][2]*mat.matrix[2][0]) / determinant;
    m.matrix[1][1] = (mat.matrix[0][0]*mat.matrix[2][2] - mat.matrix[0][2]*mat.matrix[2][0]) / determinant;
    m.matrix[1][2] = -(mat.matrix[0][0]*mat.matrix[1][2] - mat.matrix[0][2]*mat.matrix[1][0]) / determinant;
    
    m.matrix[2][0] = (mat.matrix[1][0]*mat.matrix[2][1] - mat.matrix[1][1]*mat.matrix[2][0]) / determinant;
    m.matrix[2][1] = -(mat.matrix[0][0]*mat.matrix[2][1] - mat.matrix[0][1]*mat.matrix[2][0]) / determinant;
    m.matrix[2][2] = (mat.matrix[0][0]*mat.matrix[1][1] - mat.matrix[0][1]*mat.matrix[1][0]) / determinant;

    return m;
}
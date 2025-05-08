#ifndef INVERT_3X3_MATRIX_H
#define INVERT_3X3_MATRIX_H

using namespace std;


struct matrixStruct
{
    double matrix[3][3];
};

matrixStruct invert_3x3_matrix(matrixStruct mat);

#endif
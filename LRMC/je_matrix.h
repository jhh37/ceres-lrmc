#ifndef _JE_MATRIX_H_
#define _JE_MATRIX_H_

#include <string>

void createIdentityMatrix(double *matrix, const int rank);
void computeHadamardProduct(double *productMatrix, const double *inputMatrixA, const double *inputMatrixB, const int nRows, const int nCols);
bool readDenseMatrix(const std::string filePath, double *matrix, const int nRows, const int nCols);
void writeDenseMatrix(const std::string filePath, const double *matrix, const int nRows, const int nCols);
void showMatrix(const double *matrix, const int nRows, const int nCols);

#endif

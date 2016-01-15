#include <iostream>
#include <fstream>

#include "matrix.h"
#include "config.h"

// Read matrix (in doubles) from a MATLAB column-major binary file in the row-major order.
bool readDenseMatrix(const std::string filePath, double *matrix, const int nRows, const int nCols)
{
  // If the matrix memory is unavaiable, terminate with the corresponding message.
  if (matrix == NULL) {
    std::cout << "ERROR: Cannot access memory for the output matrix." << std::endl;
    return false;
  }

  std::ifstream inputStream(filePath.c_str(), std::ios::binary);
  if (!inputStream.is_open()) {
    std::cout << "ERROR: Unable to open the input file \"" << filePath << "\"." << std::endl;
    return false;
  }

  std::ifstream::streampos length;
  // std::cout << "Number of elements to be read: " << nRows * nCols << std::endl;

  double buffer;
  for (int j = 0; j < nCols; j++) {
    for (int i = 0; i < nRows; i++) {
      inputStream.read((char*)(&buffer), DOUBLE_SIZE);
      matrix[i*nCols + j] = buffer;
    }
  }

  inputStream.close();
  return true;
}

// Write matrix (in doubles) to a binary file in the row-major order.
void writeDenseMatrix(const std::string filePath, const double *matrix, const int nRows, const int nCols)
{
  // If the matrix memory is unavailable, terminate with the corresponding message.0000
  if (matrix == NULL) {
    std::cout << "ERROR: Cannot access memory for the output matrix." << std::endl;
    return;
  }

  std::ofstream outputStream(filePath.c_str(), std::ios::binary);
  if (!outputStream.is_open()) {
    std::cout << "ERROR: Unable to open the output file." << std::endl;
    return;
  }

  std::ofstream::streampos length;
  // std::cout << "Number of elements to be written: " << nRows * nCols << std::endl;

  double buffer;
  for (int j = 0; j < nCols; j++) {
    for (int i = 0; i < nRows; i++) {
      buffer = matrix[i*nCols + j];
      outputStream.write((char*)(&buffer), DOUBLE_SIZE);
    }
  }
  outputStream.close();
}

// Shows matrix
void showMatrix(const double *matrix, const int nRows, const int nCols)
{
  int i, j;
  std::cout << "[ " << std::endl;
  for (i = 0; i<nRows; i++) {
    for (j = 0; j<nCols; j++) {
      std::cout << matrix[nCols*i + j] << "\t";
    }
    std::cout << " ;" << std::endl;
  }
  std::cout << "]" << std::endl;
}

// Create a square matrix
void createIdentityMatrix(double *matrix, const int rank)
{
  // If the matrix memory is unavailable, terminate with the corresponding message.
  if (matrix == NULL) {
    std::cout << "ERROR: Cannot access memory for the output matrix." << std::endl;
    return;
  }

  int i, nElements = rank * rank;

  // Set up OpenMP for parallel computation.
#pragma omp parallel shared(matrix, nElements, rank) private(i)
  {
    // Fill the entire matrix with '0's.
#pragma omp for nowait
    for (i = 0; i<nElements; i++)
      matrix[i] = (double)0;

    // Fill the diagonal with '1's.
#pragma omp for nowait
    for (i = 0; i<rank; i++)
      matrix[i*rank + i] = (double)1;
  }
}

// Compute the Hadamard product.
void computeHadamardProduct(double *productMatrix, const double *inputMatrixA, const double *inputMatrixB, const int nRows, const int nCols)
{
  // If the matrix memory is unavailable, terminate with the corresponding message.
  if (productMatrix == NULL) {
    std::cout << "ERROR: Cannot access memory for the output matrix." << std::endl;
    return;
  }

  int i, nElements = nRows * nCols;

  // Set up OpenMP for parallel computation.
#pragma omp parallel shared(productMatrix, inputMatrixA, inputMatrixB, nElements) private(i)
  {
    // Fill the entire matrix with '0's.
#pragma omp for nowait
    for (i = 0; i<nElements; i++)
      productMatrix[i] = inputMatrixA[i] * inputMatrixB[i];
  }
}

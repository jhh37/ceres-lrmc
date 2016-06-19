#include <iostream>
#include <fstream>

#include "matrix.h"
#include "config.h"

// Read matrix (in doubles) from a MATLAB column-major binary file in the row-major order.
bool read_dense_matrix(const std::string file_path, double *matrix, const int num_rows, const int num_cols)
{
  // If the matrix memory is unavaiable, terminate with the corresponding message.
  if (matrix == NULL) {
    std::cout << "ERROR: Cannot access memory for the output matrix." << std::endl;
    return false;
  }

  std::ifstream inputStream(file_path.c_str(), std::ios::binary);
  if (!inputStream.is_open()) {
    std::cout << "ERROR: Unable to open the input file \"" << file_path << "\"." << std::endl;
    return false;
  }

  std::ifstream::streampos length;
  // std::cout << "Number of elements to be read: " << num_rows * num_cols << std::endl;

  double buffer;
  for (int j = 0; j < num_cols; j++) {
    for (int i = 0; i < num_rows; i++) {
      inputStream.read((char*)(&buffer), DOUBLE_SIZE);
      matrix[i*num_cols + j] = buffer;
    }
  }

  inputStream.close();
  return true;
}

// Write matrix (in doubles) to a binary file in the row-major order.
void write_dense_matrix(const std::string file_path, const double *matrix, const int num_rows, const int num_cols)
{
  // If the matrix memory is unavailable, terminate with the corresponding message.0000
  if (matrix == NULL) {
    std::cout << "ERROR: Cannot access memory for the output matrix." << std::endl;
    return;
  }

  std::ofstream outputStream(file_path.c_str(), std::ios::binary);
  if (!outputStream.is_open()) {
    std::cout << "ERROR: Unable to open the output file." << std::endl;
    return;
  }

  std::ofstream::streampos length;
  // std::cout << "Number of elements to be written: " << num_rows * num_cols << std::endl;

  double buffer;
  for (int j = 0; j < num_cols; j++) {
    for (int i = 0; i < num_rows; i++) {
      buffer = matrix[i*num_cols + j];
      outputStream.write((char*)(&buffer), DOUBLE_SIZE);
    }
  }
  outputStream.close();
}

// Show the matrix on screen.
void show_matrix(const double *matrix, const int num_rows, const int num_cols)
{
  int i, j;
  std::cout << "[ " << std::endl;
  for (i = 0; i<num_rows; i++) {
    for (j = 0; j<num_cols; j++) {
      std::cout << matrix[num_cols*i + j] << "\t";
    }
    std::cout << " ;" << std::endl;
  }
  std::cout << "]" << std::endl;
}


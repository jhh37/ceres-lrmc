#ifndef _JE_MATRIX_H_
#define _JE_MATRIX_H_

#include <string>

bool read_dense_matrix(const std::string file_path, double *matrix, const int num_rows, const int num_cols);
void write_dense_matrix(const std::string file_path, const double *matrix, const int num_rows, const int num_cols);
void show_matrix(const double *matrix, const int num_rows, const int num_cols);

#endif

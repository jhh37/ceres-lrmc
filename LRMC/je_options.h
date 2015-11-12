#ifndef _JE_OPTIONS_H_
#define _JE_OPTIONS_H_

#include <string>

/*
* (STRUCT) OPTIONS: Experiment options and parameters
*/
struct OPTIONS {

  // Destructor
  ~OPTIONS();

  // Constructor
  OPTIONS();
  OPTIONS(std::string dataset, int nRows, int nCols, int rank);

  // Reset function
  void reset();                   // Resets all the values.

  // Declare variables
  std::string dataset = "";            // Dataset name

  int m = 0;                      // Number of rows
  int n = 0;                      // Number of columns
  int r = 0;                      // Rank of V
  int max_iter = 2000;            // Maximum number of iterations
  int nproc = 1;                  // Number of CPUs to be used

  double sqrt_nu = 0;             // Square root of the regularization parameter
  double tol = 1e-10;             // Function value tolerance

  bool USE_INNER_ITERS = false;   // Flag for CERES inner iterations
  bool USE_AUTO_DIFF = false;     // Flag for CERES auto-differential cost function
  bool USE_PCA = false;           // Flag for using PCA-mode (M -> (U * V' + t * 1'))
  bool DISPLAY = true;            // Flag for displaying the output thoroughly
  bool ELIMINATE_U_FIRST = false; // Flag for deciding the order of elimination
  bool DEBUG = false;             // Flag for showing debug information
  bool HELP = false;              // Flag for showing whether the experiment options are sufficient.

};

#endif
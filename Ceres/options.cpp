#include "options.h"

/*
 * (STRUCT) OPTIONS: Experiment options and parameters
 */

options::options() {}

options::options(std::string dataset, int nRows, int nCols, int rank)
: m(nRows), n(nCols), r(rank) {}

// Reset function
void options::reset() {
  // Declare variables
  dataset = "";               // Dataset name
  folder = ".";               // Folder name
  
  m = 0;                      // Number of rows
  n = 0;                      // Number of columns
  r = 0;                      // Rank of V
  max_iter = 300;             // Maximum number of iterations
  nproc = 1;                  // Number of CPUs to be used
  
  sqrt_nu = 0;                // Square root of the regularization parameter
  tol = 1e-9;                 // Function value tolerance
  
  USE_INNER_ITERS = false;    // Flag for CERES inner iterations
  USE_AUTO_DIFF = false;      // Flag for CERES auto-differential cost function
  USE_PCA = false;            // Flag for using PCA-mode (M -> (U * V' + t * 1'))
  DISPLAY = true;             // Flag for displaying the output thoroughly
  ELIMINATE_U_FIRST = false;  // Flag for deciding the order of elimination
  DEBUG = false;              // Flag for showing debug information
  HELP = false;               // Flag for showing whether the experiment options are sufficient.
}
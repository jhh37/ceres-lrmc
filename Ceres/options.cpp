#include "options.h"

/*
 * (STRUCT) OPTIONS: Experiment options and parameters
 */

// Reset function
void options::reset() {
  // Name and path of the dataset
  dataset = "";
  path = ".";
  
  num_rows = 0;
  num_cols = 0;
  rank = 0;
  max_eval = 300;             // Maximum number of evaluations
  num_procs = 1;              // Number of processors to be used
  
  sqrt_nu = 0.0;              // Square root of the regularization parameter
  func_tol = 1.0e-9;          // Function value tolerance
  
  use_jacobi_scaling = false; // Set Jacobi scaling.
  use_inner_iters = false;    // Set inner iterations.
  use_auto_diff = false;      // Set auto-differential cost function.
  use_pca = false;            // Set PCA-mode: M -> U * V' + t * 1'.
  display = true;             // Turn on/off per-iteration display.
  eliminate_u_first = false;  // Determine the order of elimination.
  debug = false;              // Turn on/off debug information.
  help = false;               // Show help.
}
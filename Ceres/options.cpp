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
  max_num_iterations = 300;             // Maximum number of evaluations
  num_threads = 1;            // Number of threads to be used
  
  sqrt_nu = 0.0;              // Square root of the regularization parameter
  func_tol = 1.0e-9;          // Function value tolerance
  
  // Existing Ceres options
  use_jacobi_scaling = false; // Set Jacobi scaling.
  use_inner_iterations = false;    // Set inner iterations.
  use_auto_differentiation = false;      // Set auto-differential cost function.
  eliminate_u_first = false;  // Determine the order of elimination.
  
  // New Ceres options
  use_levenberg_damping = false;
  use_traditional_damping_update = false;
  use_rw2_for_inner_iterations = false;
  use_linear_inner_iterations = false;
  use_inner_iterations_for_v_only = false;
  use_block_qr_for_rw2 = false;
  initialize_with_inner_iteration = false;
  
  // Other
  use_pca = false;            // Set PCA-mode: M -> U * V' + t * 1'.
  display = true;             // Turn on/off per-iteration display.
  debug = false;              // Turn on/off debug information.
  help = false;               // Show help.
}
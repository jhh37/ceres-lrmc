#ifndef _OPTIONS_H_
#define _OPTIONS_H_

#include <string>

/*
* (STRUCT) OPTIONS: Experiment options and parameters
*/
typedef struct options {

  options() : dataset(""),
              path("."),
              num_rows(0),
              num_cols(0),
              rank(0),
              max_eval(300),
              num_threads(1),
              sqrt_nu(0.0),
              func_tol(1.0e-9),
              use_jacobi_scaling(false),
              use_inner_iterations(false),
              use_auto_differentiation(false),
              eliminate_u_first(false),
              use_levenberg_damping(false),
              use_traditional_damping_update(false),
              use_rw2_for_inner_iterations(false),
              use_linear_inner_iterations(false),
              use_inner_iterations_for_v_only(false),
              use_block_qr_for_rw2(false),
              initialize_with_inner_iteration(false),
              use_pca(false),
              display(true),
              debug(false),
              help(false) {
  };

  // Reset parameters.
  void reset();

  // Name and path of the dataset
  std::string dataset = "";
  std::string path = ".";

  int num_rows;
  int num_cols;
  int rank;
  int max_eval;             // Maximum number of evaluations
  int num_threads;          // Number of processors to be used

  double sqrt_nu;           // Square root of the regularization parameter
  double func_tol;          // Function value tolerance

  // Existing Ceres options
  bool use_jacobi_scaling;        // Set Jacobi scaling.
  bool use_inner_iterations;      // Set inner iterations.
  bool use_auto_differentiation;  // Set auto-differential cost function.
  bool eliminate_u_first;         // Determine the order of elimination.
  
  // New Ceres options
  bool use_levenberg_damping;
  bool use_traditional_damping_update;
  bool use_rw2_for_inner_iterations;
  bool use_linear_inner_iterations;
  bool use_inner_iterations_for_v_only;
  bool use_block_qr_for_rw2;
  bool initialize_with_inner_iteration;
  
  // Other
  bool use_pca;             // Set PCA-mode: M -> U * V' + t * 1'.
  bool display;             // Turn on/off per-iteration display.
  bool debug;               // Turn on/off debug information.
  bool help;                // Show help.

} options_t;

#endif
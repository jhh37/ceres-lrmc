#include "experiment.h"
#include "matrix.h"
#include "residuals_analytic.h"
#include "residuals_autodiff.h"
#include "config.h"

void runExperiment(options_t options) {

  // Declare local variables for frequently-used variables.
  int m = options.m;                                        // Number of rows
  int n = options.n;                                        // Number of columns
  int r = options.r;                                        // Rank
  int rt = options.r + int(options.USE_PCA);                // Rank of U (rt = r for non-PCA, rt = r + 1 for PCA)

  double sqrt_nu = options.sqrt_nu * int(!options.USE_PCA); // Regularization parameter (nu = nu for non-PCA, nu = 0 for PCA)

  // Initialize matrix pointers with adequate size.
  double* M = new double[m * n * DOUBLE_SIZE];
  double* W = new double[m * n * DOUBLE_SIZE];
  double* U = new double[m * rt * DOUBLE_SIZE];
  double* V = new double[n * r * DOUBLE_SIZE];

  // Set sample prefix.
  std::string samplePrefix = options.folder + "/" + options.dataset + "_r" + std::to_string(r);

  // Read matrix from pre-made binary files.
  if (!readDenseMatrix(samplePrefix + "_M.bin", M, m, n)) return;
  else if (!readDenseMatrix(samplePrefix + "_W.bin", W, m, n)) return;
  else if (!readDenseMatrix(samplePrefix + "_U0.bin", U, m, rt)) return;
  else if (!readDenseMatrix(samplePrefix + "_V0.bin", V, n, r)) return;

  // Declare a CERES problem.
  ceres::Problem problem;

  // Add row-wise parameter blocks of size rt from matrix U.
  for (int i = 0; i < m; i++) {
    problem.AddParameterBlock(&(U[i * rt]), rt);
  }
  // Add row-wise parameter blocks of size r from matrix V.
  for (int j = 0; j < n; j++) {
    problem.AddParameterBlock(&(V[j * r]), r);
  }

  if (options.USE_AUTO_DIFF) {
	// Use automatic derivatives

    // Declare a dynamic AD residual.
    ceres::DynamicAutoDiffCostFunction<AD_WeightedElementResidual, 4>* residual;

    // Add residuals of the original problem E(U,V).
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (W[i*n + j] != 0) {
          residual = new ceres::DynamicAutoDiffCostFunction<AD_WeightedElementResidual, 4>(new AD_WeightedElementResidual(M[i*n + j], W[i*n + j], r, options.USE_PCA));
          residual->AddParameterBlock(rt);
          residual->AddParameterBlock(r);
          residual->SetNumResiduals(1);
          problem.AddResidualBlock(residual, NULL, &(U[i*rt]), &(V[j*r]));
        }
      }
    }

    // Add residuals of the regularization term vec(U) and vec(V).
    if (sqrt_nu > 0) {

      ceres::DynamicAutoDiffCostFunction<AD_RegularizationResidual, 4>* reg_residual;

      // Add residuals of vec(U)
      for (int i = 0; i < m; i++) {
        reg_residual = new ceres::DynamicAutoDiffCostFunction<AD_RegularizationResidual, 4>(new AD_RegularizationResidual(sqrt_nu, rt));
        reg_residual->AddParameterBlock(rt);
        reg_residual->SetNumResiduals(rt);
        problem.AddResidualBlock(reg_residual, NULL, &(U[i*rt]));
      }

      // Add residuals of vec(V)
      for (int j = 0; j < n; j++) {
        reg_residual = new ceres::DynamicAutoDiffCostFunction<AD_RegularizationResidual, 4>(new AD_RegularizationResidual(sqrt_nu, r));
        reg_residual->AddParameterBlock(r);
        reg_residual->SetNumResiduals(r);
        problem.AddResidualBlock(reg_residual, NULL, &(V[j*r]));
      }
    }

  } else {
	// Otherwise, use analytic derivatives.

    // Add residuals of the original problem E(U,V).
    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
        if (W[i*n + j] != 0)
          problem.AddResidualBlock(new WeightedElementResidual(M[i*n + j], W[i*n + j], r, options.USE_PCA), NULL, &(U[i*rt]), &(V[j*r]));

    // Add residuals of the regularization term vec(U) and vec(V).
    if (sqrt_nu > 0) {

      // Add residuals of vec(U)
      for (int i = 0; i < m; i++) {
        problem.AddResidualBlock(new RegularizationResidual(sqrt_nu, r), NULL, &(U[i*rt]));
      }

      // Add residuals of vec(V)
      for (int j = 0; j < n; j++) {
        problem.AddResidualBlock(new RegularizationResidual(sqrt_nu, r), NULL, &(V[j*r]));
      }
    }
  }

  // Set CERES solver options.
  ceres::Solver::Options ce_opts;
  ce_opts.minimizer_progress_to_stdout = options.DISPLAY;
  ce_opts.max_num_iterations = options.max_iter;
  ce_opts.function_tolerance = options.tol;
  ce_opts.inner_iteration_tolerance = options.tol;
  ce_opts.check_gradients = false;
  ce_opts.lm_damping_type = ceres::LEVENBERG;
  ce_opts.lm_damping_update_rule = ceres::TRADITIONAL_RULE;
  ce_opts.lm_damping_decrease_factor = 10.0;

  // Set the number of threads
  ce_opts.num_threads = options.nproc;
  ce_opts.num_linear_solver_threads = options.nproc;

  // Set the solver type and ordering.
  ce_opts.linear_solver_type = ceres::SPARSE_SCHUR;
  ce_opts.linear_solver_ordering.reset(new ceres::ParameterBlockOrdering);

  // Ordering depends on the input ELIMINATE_U_FIRST.
  for (int i = 0; i < m; ++i) {
    ce_opts.linear_solver_ordering->AddElementToGroup(&(U[i*rt]), int(!options.ELIMINATE_U_FIRST));
  }
  for (int j = 0; j < n; ++j) {
    ce_opts.linear_solver_ordering->AddElementToGroup(&(V[j*r]), int(options.ELIMINATE_U_FIRST));
  }

  // Set whether to use Jacobi scaling.
  ce_opts.jacobi_scaling = options.USE_JACOBI_SCALING;
  
  // Set options related to inner iterations.
  ce_opts.use_inner_iterations = options.USE_INNER_ITERS;

  if (options.USE_INNER_ITERS)
  {
    ce_opts.inner_iteration_tolerance = options.tol;

    // Set the inner iteration ordering.
    ce_opts.inner_iteration_ordering.reset(new ceres::ParameterBlockOrdering);

    // Ordering depends on the input ELIMINATE_U_FIRST.  
    for (int i = 0; i < m; ++i) {
      ce_opts.inner_iteration_ordering->AddElementToGroup(&(U[i*rt]), int(!options.ELIMINATE_U_FIRST));
    }
    for (int j = 0; j < n; ++j) {
      ce_opts.inner_iteration_ordering->AddElementToGroup(&(V[j*r]), int(options.ELIMINATE_U_FIRST));
    }
  }

  // Run the solver.
  ceres::Solver::Summary summary;
  Solve(ce_opts, &problem, &summary);

  // Output report.
  if (options.DISPLAY) {
    std::cout << summary.FullReport() << std::endl;
  }
  else {
    std::cout << summary.BriefReport() << std::endl;
  }
  std::cout << std::endl;

  // Write the output files including the number of iterations.
  double iters_[] = { double(summary.iterations.size() - 1) };
  writeDenseMatrix(samplePrefix + "_U.bin", U, m, rt);
  writeDenseMatrix(samplePrefix + "_V.bin", V, n, r);
  writeDenseMatrix(samplePrefix + "_iters.bin", iters_, 1, 1);

  // Free manually-allocated memory space.
  delete[] V;
  delete[] U;
  delete[] W;
  delete[] M;
}

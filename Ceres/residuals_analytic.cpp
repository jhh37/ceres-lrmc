#include "residuals_analytic.h"

/*
 * {ANALYTIC} Weighted residual:  f_ij = W_ij .* (M_ij - U_i * V_j')
 */

// Destructor
WeightedElementResidual::~WeightedElementResidual() {};

// Constructors
WeightedElementResidual::WeightedElementResidual(double measurement, double weight, int rank, bool USE_PCA) {

  this->m_ij = measurement;
  this->w_ij = weight;
  this->r = rank;
  this->USE_PCA = USE_PCA;

  // Set the number of parameters for U and V.
  mutable_parameter_block_sizes()->push_back(r + int(USE_PCA));
  mutable_parameter_block_sizes()->push_back(r);
  set_num_residuals(1);

}

WeightedElementResidual::WeightedElementResidual(double measurement, double weight, int rank) {

  this->m_ij = measurement;
  this->w_ij = weight;
  this->r = rank;
  this->USE_PCA = false;

  // Set the number of parameters for U and V.
  mutable_parameter_block_sizes()->push_back(r + int(USE_PCA));
  mutable_parameter_block_sizes()->push_back(r);
  set_num_residuals(1);

}

// Evaluator
bool WeightedElementResidual::Evaluate(double const* const* parameters, double* residuals, double** jacobians) const {

  // Calculate the residuals.
  residuals[0] = m_ij;

  for (int k = 0; k < r; k++) {
    residuals[0] -= parameters[0][k] * parameters[1][k];
  }

  // If PCA formulation is enabled, subtract translational element embedded in the last column of U.
  if (USE_PCA) { residuals[0] -= parameters[0][r]; }

  // If weight is not 1, multiply by the weight.
  if (w_ij != 1) { residuals[0] *= w_ij; }

  // Compute the Jacobian matrix.
  if (jacobians != NULL) {
    for (int k = 0; k < r; k++) {

      if (jacobians[0] != NULL) {

        jacobians[0][k] = - parameters[1][k];

        // If weight is not 1, multiply by the weight.
        if (w_ij != 1) { jacobians[0][k] *= w_ij; }
      }

      if (jacobians[1] != NULL) {

        jacobians[1][k] = - parameters[0][k];

        // If weight is not 1, multiply by the weight.
        if (w_ij != 1) { jacobians[1][k] *= w_ij; }
      }
    }

    // If PCA formulation is enabled, add the last entry of Jacobian for the translational vector.
    if (jacobians[0] != NULL && USE_PCA) { jacobians[0][r] = - w_ij; }
  }

  return true;
}


/*
* {ANALYTIC} Regularization residual:  f_ij = x_ij ^ 2
*/

// Destructor
RegularizationResidual::~RegularizationResidual() {}

// Constructor
RegularizationResidual::RegularizationResidual(double sqrt_nu_, int rank) {

  this->r = rank;
  this->sqrt_nu = sqrt_nu_;

  // Set the number of parameters for X.
  mutable_parameter_block_sizes()->push_back(r);
  set_num_residuals(r);
}

// Evaluator
bool RegularizationResidual::Evaluate(double const* const* parameters, double* residuals, double** jacobians) const {

  // Calculate the residuals.
  for (int k = 0; k < r; k++) {
    residuals[k] = sqrt_nu * parameters[0][k];
  }

  if (jacobians != NULL && jacobians[0] != NULL) {
    for (int kk = 0; kk < r*r; kk++) {
      jacobians[0][kk] = 0;
    }
    for (int k = 0; k < r; k++) {
      jacobians[0][k*(r + 1)] = sqrt_nu;
    }
  }

  return true;
}
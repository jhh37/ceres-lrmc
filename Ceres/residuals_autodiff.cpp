#include "residuals_autodiff.h"

/*
 * (AUTODIFF) Weighted residual:  f_ij = W_ij .* (M_ij - U_i * V_j')
 */

// Constructors
AD_WeightedElementResidual::AD_WeightedElementResidual(double measurement, double weight, int rank, bool use_pca)
  : m_ij(measurement), w_ij(weight), r(rank), USE_PCA(use_pca) {}

AD_WeightedElementResidual::AD_WeightedElementResidual(double measurement, double weight, int rank)
  : m_ij(measurement), w_ij(weight), r(rank), USE_PCA(false) {}

// Operator
template <typename T> bool AD_WeightedElementResidual::operator() (T const* const* parameters, T* residual) const {

  residual[0] = T(m_ij);

  for (int k = 0; k < r; k++) {
    residual[0] -= parameters[0][k] * parameters[1][k];
  }

  // If PCA formulation is enabled, subtract translational element embedded in the last column of U.
  if (USE_PCA) { residual[0] -= parameters[0][r]; }
  
  if (w_ij != 1) { residual[0] *= T(w_ij); }

  return true;
}

// Specific links to two structures used for LRMC
template bool AD_WeightedElementResidual::operator() < struct ceres::Jet <double, 4> > (struct ceres::Jet <double, 4> const* const* parameters, struct ceres::Jet <double, 4>* residual) const;
template bool AD_WeightedElementResidual::operator() < double > (double const* const* parameters, double* residual) const;

/*
 * (AUTODIFF) Frobenius residual:  f_ij = x_ij ^ 2
 */

// Constructor
AD_RegularizationResidual::AD_RegularizationResidual(double sqrt_of_reg_param, int rank)
  : r(rank), sqrt_nu(sqrt_of_reg_param) {}

// Operator
template <typename T> bool AD_RegularizationResidual::operator() (T const* const* parameters, T* residual) const {

  for (int k = 0; k < r; k++) {
    residual[k] = T(sqrt_nu) * parameters[0][k];
  }

  return true;
}

// Specific links to two structures used for LRMC
template bool AD_RegularizationResidual::operator() < struct ceres::Jet <double, 4> > (struct ceres::Jet <double, 4> const* const* parameters, struct ceres::Jet <double, 4>* residual) const;
template bool AD_RegularizationResidual::operator() < double > (double const* const* parameters, double* residual) const;

#ifndef _RESIDUALS_AUTODIFF_H_
#define _RESIDUALS_AUTODIFF_H_

#include "ceres/ceres.h"
#include "options.h"

/*
 * (AUTO_DIFF) Weighted residual:  f_ij = W_ij .* (M_ij - U_i * V_j')
 */
struct AD_WeightedElementResidual {

  // Constructors
  AD_WeightedElementResidual(double measurement, double weight, int rank, bool USE_PCA);
  AD_WeightedElementResidual(double measurement, double weight, int rank);

  // Operator
  template <typename T> bool operator() (T const* const* parameters, T* residual) const;

  // Private variables
  private:
    const double m_ij;
    const double w_ij;
    const int r;
    const bool USE_PCA;
};

/*
 * (AUTO_DIFF) Regularization residual:  f_ij = x_ij^2
 */
struct AD_RegularizationResidual {

  // Constructor
  AD_RegularizationResidual(double sqrt_of_reg_param, int rank);

  // Operator
  template <typename T> bool operator() (T const* const* parameters, T* residual) const;

  // Private variables
  private:
    int r;
    double sqrt_nu;

};

#endif
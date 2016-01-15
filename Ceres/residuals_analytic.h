#ifndef _RESIDUALS_ANALYTIC_H_
#define _RESIDUALS_ANALYTIC_H_

#include "ceres/ceres.h"
#include "options.h"

/*
 * (ANALYTIC) Weighted element residual:  f_ij = W_ij .* (M_ij - U_i * V_j')
 */
struct WeightedElementResidual : public ceres::CostFunction {

  // Destructor
  virtual ~WeightedElementResidual();

  // Constructors
  WeightedElementResidual(double measurement, double weight, int rank, bool USE_PCA);
  WeightedElementResidual(double measurement, double weight, int rank);

  // Evaluator
  virtual bool Evaluate(double const* const* parameters, double* residuals, double** jacobians) const;

  // Private variables
  private:
    int r;
    double m_ij;
    double w_ij;
    bool USE_PCA;
};

/*
* (ANALYTIC) Regularization residual:  f_ij = x_ij ^ 2
*/
struct RegularizationResidual : public ceres::CostFunction {

  // Destructor
  virtual ~RegularizationResidual();

  // Constructor
  RegularizationResidual(double sqrt_nu_, int rank);

  // Evaluator
  virtual bool Evaluate(double const* const* parameters, double* residuals, double** jacobians) const;

  // Private variables
  private:
    int r;
    double sqrt_nu;
};

#endif
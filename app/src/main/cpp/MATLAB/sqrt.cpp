/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * sqrt.cpp
 *
 * Code generation for function 'sqrt'
 *
 */

/* Include files */
#include "sqrt.h"
#include "compute_eig.h"
#include "compute_eig_rtwutil.h"
#include "rt_nonfinite.h"
#include "xhseqr.h"
#include <cmath>

/* Function Definitions */
void b_sqrt(creal32_T *x)
{
  float xr;
  float xi;
  float absxi;
  float absxr;
  xr = x->re;
  xi = x->im;
  if (xi == 0.0F) {
    if (xr < 0.0F) {
      absxi = 0.0F;
      xr = std::sqrt(-xr);
    } else {
      absxi = std::sqrt(xr);
      xr = 0.0F;
    }
  } else if (xr == 0.0F) {
    if (xi < 0.0F) {
      absxi = std::sqrt(-xi / 2.0F);
      xr = -absxi;
    } else {
      absxi = std::sqrt(xi / 2.0F);
      xr = absxi;
    }
  } else if (rtIsNaNF(xr)) {
    absxi = xr;
  } else if (rtIsNaNF(xi)) {
    absxi = xi;
    xr = xi;
  } else if (rtIsInfF(xi)) {
    absxi = std::abs(xi);
    xr = xi;
  } else if (rtIsInfF(xr)) {
    if (xr < 0.0F) {
      absxi = 0.0F;
      xr = xi * -xr;
    } else {
      absxi = xr;
      xr = 0.0F;
    }
  } else {
    absxr = std::abs(xr);
    absxi = std::abs(xi);
    if ((absxr > 8.50705867E+37F) || (absxi > 8.50705867E+37F)) {
      absxr *= 0.5F;
      absxi = rt_hypotf_snf(absxr, absxi * 0.5F);
      if (absxi > absxr) {
        absxi = std::sqrt(absxi) * std::sqrt(absxr / absxi + 1.0F);
      } else {
        absxi = std::sqrt(absxi) * 1.41421354F;
      }
    } else {
      absxi = std::sqrt((rt_hypotf_snf(absxr, absxi) + absxr) * 0.5F);
    }

    if (xr > 0.0F) {
      xr = 0.5F * (xi / absxi);
    } else {
      if (xi < 0.0F) {
        xr = -absxi;
      } else {
        xr = absxi;
      }

      absxi = 0.5F * (xi / xr);
    }
  }

  x->re = absxi;
  x->im = xr;
}

/* End of code generation (sqrt.cpp) */

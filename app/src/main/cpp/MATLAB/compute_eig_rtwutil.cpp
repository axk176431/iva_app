/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_eig_rtwutil.cpp
 *
 * Code generation for function 'compute_eig_rtwutil'
 *
 */

/* Include files */
#include "compute_eig_rtwutil.h"
#include "compute_eig.h"
#include "rt_nonfinite.h"
#include <cmath>

/* Function Definitions */
float rt_hypotf_snf(float u0, float u1)
{
  float y;
  float a;
  a = std::abs(u0);
  y = std::abs(u1);
  if (a < y) {
    a /= y;
    y *= std::sqrt(a * a + 1.0F);
  } else if (a > y) {
    y /= a;
    y = a * std::sqrt(y * y + 1.0F);
  } else {
    if (!rtIsNaNF(y)) {
      y = a * 1.41421354F;
    }
  }

  return y;
}

/* End of code generation (compute_eig_rtwutil.cpp) */

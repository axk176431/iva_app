/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdlapy3.cpp
 *
 * Code generation for function 'xdlapy3'
 *
 */

/* Include files */
#include "xdlapy3.h"
#include "compute_eig.h"
#include "rt_nonfinite.h"
#include <cmath>

/* Function Definitions */
float xdlapy3(float x1, float x2, float x3)
{
  float y;
  float a;
  float b;
  float c;
  a = std::abs(x1);
  b = std::abs(x2);
  c = std::abs(x3);
  if ((a > b) || rtIsNaNF(b)) {
    y = a;
  } else {
    y = b;
  }

  if (c > y) {
    y = c;
  }

  if ((y > 0.0F) && (!rtIsInfF(y))) {
    a /= y;
    b /= y;
    c /= y;
    y *= std::sqrt((a * a + c * c) + b * b);
  } else {
    y = (a + b) + c;
  }

  return y;
}

/* End of code generation (xdlapy3.cpp) */

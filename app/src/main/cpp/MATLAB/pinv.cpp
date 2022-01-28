/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * pinv.cpp
 *
 * Code generation for function 'pinv'
 *
 */

/* Include files */
#include "pinv.h"
#include "compute_iva.h"
#include "init_iva.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include <cmath>

/* Function Definitions */
void pinv(const creal32_T A[4], creal32_T X[4])
{
  bool p;
  creal32_T U[4];
  float s[2];
  creal32_T V[4];
  float absx;
  int exponent;
  int r;
  int vcol;
  int ia;
  int ic;
  float temp_re;
  int i;
  int ar;
  float U_im;
  float f;
  X[0].re = 0.0F;
  X[0].im = 0.0F;
  p = ((!rtIsInfF(A[0].re)) && (!rtIsInfF(A[0].im)) && ((!rtIsNaNF(A[0].re)) &&
        (!rtIsNaNF(A[0].im))));
  X[1].re = 0.0F;
  X[1].im = 0.0F;
  if ((!p) || (rtIsInfF(A[1].re) || rtIsInfF(A[1].im) || (rtIsNaNF(A[1].re) ||
        rtIsNaNF(A[1].im)))) {
    p = false;
  }

  X[2].re = 0.0F;
  X[2].im = 0.0F;
  if ((!p) || (rtIsInfF(A[2].re) || rtIsInfF(A[2].im) || (rtIsNaNF(A[2].re) ||
        rtIsNaNF(A[2].im)))) {
    p = false;
  }

  X[3].re = 0.0F;
  X[3].im = 0.0F;
  if ((!p) || (rtIsInfF(A[3].re) || rtIsInfF(A[3].im) || (rtIsNaNF(A[3].re) ||
        rtIsNaNF(A[3].im)))) {
    p = false;
  }

  if (!p) {
    X[0].re = rtNaNF;
    X[0].im = 0.0F;
    X[1].re = rtNaNF;
    X[1].im = 0.0F;
    X[2].re = rtNaNF;
    X[2].im = 0.0F;
    X[3].re = rtNaNF;
    X[3].im = 0.0F;
  } else {
    svd(A, U, s, V);
    absx = std::abs(s[0]);
    if ((!rtIsInfF(absx)) && (!rtIsNaNF(absx))) {
      if (absx <= 1.17549435E-38F) {
        absx = 1.4013E-45F;
      } else {
        std::frexp(absx, &exponent);
        absx = std::ldexp(1.0F, exponent - 24);
      }
    } else {
      absx = rtNaNF;
    }

    absx *= 2.0F;
    r = -1;
    exponent = 0;
    while ((exponent < 2) && (s[exponent] > absx)) {
      r++;
      exponent++;
    }

    if (r + 1 > 0) {
      vcol = 1;
      for (ia = 0; ia <= r; ia++) {
        temp_re = 1.0F / s[ia];
        i = vcol + 1;
        for (exponent = vcol; exponent <= i; exponent++) {
          U_im = V[exponent - 1].im;
          f = V[exponent - 1].re;
          absx = temp_re * U_im + 0.0F * f;
          f = temp_re * f - 0.0F * U_im;
          V[exponent - 1].re = f;
          V[exponent - 1].im = absx;
        }

        vcol += 2;
      }

      for (ic = 1; ic < 3; ic++) {
        X[ic - 1].re = 0.0F;
        X[ic - 1].im = 0.0F;
      }

      for (ic = 3; ic < 5; ic++) {
        X[ic - 1].re = 0.0F;
        X[ic - 1].im = 0.0F;
      }

      ar = -1;
      i = r << 1;
      exponent = i + 1;
      for (vcol = 1; vcol <= exponent; vcol += 2) {
        absx = U[vcol - 1].re;
        U_im = -U[vcol - 1].im;
        temp_re = absx - 0.0F * U_im;
        absx = U_im + 0.0F * absx;
        ia = ar;
        for (ic = 1; ic < 3; ic++) {
          ia++;
          X[ic - 1].re += temp_re * V[ia].re - absx * V[ia].im;
          X[ic - 1].im += temp_re * V[ia].im + absx * V[ia].re;
        }

        ar += 2;
      }

      ar = -1;
      exponent = i + 2;
      for (vcol = 2; vcol <= exponent; vcol += 2) {
        absx = U[vcol - 1].re;
        U_im = -U[vcol - 1].im;
        temp_re = absx - 0.0F * U_im;
        absx = U_im + 0.0F * absx;
        ia = ar;
        for (ic = 3; ic < 5; ic++) {
          ia++;
          X[ic - 1].re += temp_re * V[ia].re - absx * V[ia].im;
          X[ic - 1].im += temp_re * V[ia].im + absx * V[ia].re;
        }

        ar += 2;
      }
    }
  }
}

/* End of code generation (pinv.cpp) */

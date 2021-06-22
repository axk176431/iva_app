/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgerc.cpp
 *
 * Code generation for function 'xgerc'
 *
 */

/* Include files */
#include "xgerc.h"
#include "compute_eig.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xgerc(int m, int n, const creal32_T alpha1, int ix0, const creal32_T y[3],
           creal32_T A[9], int ia0)
{
  int jA;
  int jy;
  int j;
  float temp_re;
  float temp_im;
  int ix;
  int i;
  int ijA;
  float A_im;
  if ((!(alpha1.re == 0.0F)) || (!(alpha1.im == 0.0F))) {
    jA = ia0;
    jy = 0;
    for (j = 0; j < n; j++) {
      if ((y[jy].re != 0.0F) || (y[jy].im != 0.0F)) {
        temp_re = y[jy].re * alpha1.re + y[jy].im * alpha1.im;
        temp_im = y[jy].re * alpha1.im - y[jy].im * alpha1.re;
        ix = ix0;
        i = m + jA;
        for (ijA = jA; ijA < i; ijA++) {
          A_im = A[ix - 1].re * temp_im + A[ix - 1].im * temp_re;
          A[ijA - 1].re += A[ix - 1].re * temp_re - A[ix - 1].im * temp_im;
          A[ijA - 1].im += A_im;
          ix++;
        }
      }

      jy++;
      jA += 3;
    }
  }
}

/* End of code generation (xgerc.cpp) */

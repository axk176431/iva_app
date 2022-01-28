/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * flip.cpp
 *
 * Code generation for function 'flip'
 *
 */

/* Include files */
#include "flip.h"
#include "compute_iva.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void flip(creal32_T x[63])
{
  int k;
  float tmp_re;
  float tmp_im;
  for (k = 0; k < 31; k++) {
    tmp_re = x[k].re;
    tmp_im = x[k].im;
    x[k] = x[62 - k];
    x[62 - k].re = tmp_re;
    x[62 - k].im = tmp_im;
  }
}

/* End of code generation (flip.cpp) */

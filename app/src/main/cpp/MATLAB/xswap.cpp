/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xswap.cpp
 *
 * Code generation for function 'xswap'
 *
 */

/* Include files */
#include "xswap.h"
#include "compute_iva.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xswap(creal32_T x[4])
{
  float temp_re;
  float temp_im;
  temp_re = x[0].re;
  temp_im = x[0].im;
  x[0] = x[2];
  x[2].re = temp_re;
  x[2].im = temp_im;
  temp_re = x[1].re;
  temp_im = x[1].im;
  x[1] = x[3];
  x[3].re = temp_re;
  x[3].im = temp_im;
}

/* End of code generation (xswap.cpp) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xdotc.cpp
 *
 * Code generation for function 'xdotc'
 *
 */

/* Include files */
#include "xdotc.h"
#include "compute_iva.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Function Definitions */
creal32_T xdotc(const creal32_T x[4], const creal32_T y[4])
{
  creal32_T d;
  d.re = x[0].re * y[2].re + x[0].im * y[2].im;
  d.im = x[0].re * y[2].im - x[0].im * y[2].re;
  d.re += x[1].re * y[3].re + x[1].im * y[3].im;
  d.im += x[1].re * y[3].im - x[1].im * y[3].re;
  return d;
}

/* End of code generation (xdotc.cpp) */

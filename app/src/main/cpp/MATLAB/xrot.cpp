/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xrot.cpp
 *
 * Code generation for function 'xrot'
 *
 */

/* Include files */
#include "xrot.h"
#include "compute_iva.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void xrot(creal32_T x[4], int ix0, int iy0, float c, float s)
{
  int ix;
  int iy;
  float temp_re;
  float temp_im;
  float s_im;
  ix = ix0 - 1;
  iy = iy0 - 1;
  temp_re = c * x[ix].re + (s * x[iy].re - 0.0F * x[iy].im);
  temp_im = c * x[ix].im + (s * x[iy].im + 0.0F * x[iy].re);
  s_im = s * x[ix].im + 0.0F * x[ix].re;
  x[iy].re = c * x[iy].re - (s * x[ix].re - 0.0F * x[ix].im);
  x[iy].im = c * x[iy].im - s_im;
  x[ix].re = temp_re;
  x[ix].im = temp_im;
  iy++;
  ix++;
  temp_re = c * x[ix].re + (s * x[iy].re - 0.0F * x[iy].im);
  temp_im = c * x[ix].im + (s * x[iy].im + 0.0F * x[iy].re);
  s_im = s * x[ix].im + 0.0F * x[ix].re;
  x[iy].re = c * x[iy].re - (s * x[ix].re - 0.0F * x[ix].im);
  x[iy].im = c * x[iy].im - s_im;
  x[ix].re = temp_re;
  x[ix].im = temp_im;
}

/* End of code generation (xrot.cpp) */

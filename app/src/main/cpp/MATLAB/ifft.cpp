/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * ifft.cpp
 *
 * Code generation for function 'ifft'
 *
 */

/* Include files */
#include "ifft.h"
#include "compute_iva.h"
#include "compute_iva_data.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void ifft(const creal32_T x[128], creal32_T y[128])
{
  int ix;
  int ju;
  int iy;
  int i;
  bool tst;
  float twid_re;
  float temp_re;
  float twid_im;
  int iheight;
  float temp_im;
  float re;
  float im;
  int istart;
  int temp_re_tmp;
  int j;
  static const float b_fv[65] = { 0.0F, 0.0490676761F, 0.0980171412F,
    0.146730468F, 0.195090324F, 0.242980197F, 0.290284663F, 0.336889863F,
    0.382683456F, 0.427555084F, 0.471396744F, 0.514102757F, 0.555570245F,
    0.59569931F, 0.634393334F, 0.671559F, 0.707106769F, 0.740951121F,
    0.773010433F, 0.803207517F, 0.831469595F, 0.857728601F, 0.881921232F,
    0.903989315F, 0.923879504F, 0.941544056F, 0.956940353F, 0.970031261F,
    0.980785251F, 0.989176512F, 0.99518472F, 0.99879545F, 1.0F, 0.99879545F,
    0.99518472F, 0.989176512F, 0.980785251F, 0.970031261F, 0.956940353F,
    0.941544056F, 0.923879504F, 0.903989315F, 0.881921232F, 0.857728601F,
    0.831469595F, 0.803207517F, 0.773010433F, 0.740951121F, 0.707106769F,
    0.671559F, 0.634393334F, 0.59569931F, 0.555570245F, 0.514102757F,
    0.471396744F, 0.427555084F, 0.382683456F, 0.336889863F, 0.290284663F,
    0.242980197F, 0.195090324F, 0.146730468F, 0.0980171412F, 0.0490676761F, 0.0F
  };

  int ihi;
  ix = 0;
  ju = 0;
  iy = 0;
  for (i = 0; i < 127; i++) {
    y[iy] = x[ix];
    iy = 128;
    tst = true;
    while (tst) {
      iy >>= 1;
      ju ^= iy;
      tst = ((ju & iy) == 0);
    }

    iy = ju;
    ix++;
  }

  y[iy] = x[ix];
  for (i = 0; i <= 126; i += 2) {
    twid_re = y[i + 1].re;
    temp_re = twid_re;
    twid_im = y[i + 1].im;
    temp_im = twid_im;
    re = y[i].re;
    im = y[i].im;
    twid_re = y[i].re - twid_re;
    y[i + 1].re = twid_re;
    twid_im = y[i].im - twid_im;
    y[i + 1].im = twid_im;
    y[i].re = re + temp_re;
    y[i].im = im + temp_im;
  }

  iy = 2;
  ix = 4;
  ju = 32;
  iheight = 125;
  while (ju > 0) {
    for (i = 0; i < iheight; i += ix) {
      temp_re_tmp = i + iy;
      temp_re = y[temp_re_tmp].re;
      temp_im = y[temp_re_tmp].im;
      y[temp_re_tmp].re = y[i].re - y[temp_re_tmp].re;
      y[temp_re_tmp].im = y[i].im - y[temp_re_tmp].im;
      y[i].re += temp_re;
      y[i].im += temp_im;
    }

    istart = 1;
    for (j = ju; j < 64; j += ju) {
      twid_re = fv[j];
      twid_im = b_fv[j];
      i = istart;
      ihi = istart + iheight;
      while (i < ihi) {
        temp_re_tmp = i + iy;
        temp_re = twid_re * y[temp_re_tmp].re - twid_im * y[temp_re_tmp].im;
        temp_im = twid_re * y[temp_re_tmp].im + twid_im * y[temp_re_tmp].re;
        y[temp_re_tmp].re = y[i].re - temp_re;
        y[temp_re_tmp].im = y[i].im - temp_im;
        y[i].re += temp_re;
        y[i].im += temp_im;
        i += ix;
      }

      istart++;
    }

    ju /= 2;
    iy = ix;
    ix += ix;
    iheight -= iy;
  }

  for (iy = 0; iy < 128; iy++) {
    y[iy].re *= 0.0078125F;
    y[iy].im *= 0.0078125F;
  }
}

/* End of code generation (ifft.cpp) */

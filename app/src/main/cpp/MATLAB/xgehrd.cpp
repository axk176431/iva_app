/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgehrd.cpp
 *
 * Code generation for function 'xgehrd'
 *
 */

/* Include files */
#include "xgehrd.h"
#include "compute_eig.h"
#include "compute_eig_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "xdlapy3.h"
#include "xgerc.h"
#include "xhseqr.h"
#include <cmath>
#include <cstring>

/* Function Definitions */
void xgehrd(creal32_T a[9], creal32_T tau[2])
{
  creal32_T work[3];
  creal32_T alpha1;
  float c_re;
  float beta1;
  int lastv;
  int knt;
  int lastc;
  int i;
  float c_im;
  bool exitg2;
  float temp_re;
  creal32_T b_a;
  int ix;
  int b_i;
  int ia;
  int exitg1;
  int i1;
  int ijA;
  work[0].re = 0.0F;
  work[0].im = 0.0F;
  work[1].re = 0.0F;
  work[1].im = 0.0F;
  work[2].re = 0.0F;
  work[2].im = 0.0F;
  alpha1 = a[1];
  tau[0].re = 0.0F;
  tau[0].im = 0.0F;
  c_re = rt_hypotf_snf(a[2].re, a[2].im);
  if ((c_re != 0.0F) || (a[1].im != 0.0F)) {
    beta1 = xdlapy3(a[1].re, a[1].im, c_re);
    if (a[1].re >= 0.0F) {
      beta1 = -beta1;
    }

    if (std::abs(beta1) < 9.86076132E-32F) {
      knt = -1;
      do {
        knt++;
        for (i = 3; i < 4; i++) {
          temp_re = 1.01412048E+31F * a[2].im + 0.0F * a[2].re;
          a[2].re = 1.01412048E+31F * a[2].re - 0.0F * a[2].im;
          a[2].im = temp_re;
        }

        beta1 *= 1.01412048E+31F;
        alpha1.re *= 1.01412048E+31F;
        alpha1.im *= 1.01412048E+31F;
      } while (!(std::abs(beta1) >= 9.86076132E-32F));

      beta1 = xdlapy3(alpha1.re, alpha1.im, rt_hypotf_snf(a[2].re, a[2].im));
      if (alpha1.re >= 0.0F) {
        beta1 = -beta1;
      }

      c_re = beta1 - alpha1.re;
      if (0.0F - alpha1.im == 0.0F) {
        tau[0].re = c_re / beta1;
        tau[0].im = 0.0F;
      } else if (c_re == 0.0F) {
        tau[0].re = 0.0F;
        tau[0].im = (0.0F - alpha1.im) / beta1;
      } else {
        tau[0].re = c_re / beta1;
        tau[0].im = (0.0F - alpha1.im) / beta1;
      }

      b_a.re = alpha1.re - beta1;
      b_a.im = alpha1.im;
      alpha1 = recip(b_a);
      c_re = alpha1.re;
      c_im = alpha1.im;
      for (i = 3; i < 4; i++) {
        temp_re = c_re * a[2].im + c_im * a[2].re;
        a[2].re = c_re * a[2].re - c_im * a[2].im;
        a[2].im = temp_re;
      }

      for (i = 0; i <= knt; i++) {
        beta1 *= 9.86076132E-32F;
      }

      alpha1.re = beta1;
      alpha1.im = 0.0F;
    } else {
      c_re = beta1 - a[1].re;
      c_im = 0.0F - a[1].im;
      if (c_im == 0.0F) {
        tau[0].re = c_re / beta1;
        tau[0].im = 0.0F;
      } else if (c_re == 0.0F) {
        tau[0].re = 0.0F;
        tau[0].im = c_im / beta1;
      } else {
        tau[0].re = c_re / beta1;
        tau[0].im = c_im / beta1;
      }

      b_a.re = a[1].re - beta1;
      b_a.im = a[1].im;
      alpha1 = recip(b_a);
      c_re = alpha1.re;
      c_im = alpha1.im;
      for (i = 3; i < 4; i++) {
        temp_re = c_re * a[2].im + c_im * a[2].re;
        a[2].re = c_re * a[2].re - c_im * a[2].im;
        a[2].im = temp_re;
      }

      alpha1.re = beta1;
      alpha1.im = 0.0F;
    }
  }

  a[1].re = 1.0F;
  a[1].im = 0.0F;
  if ((tau[0].re != 0.0F) || (tau[0].im != 0.0F)) {
    lastv = 1;
    i = 2;
    while ((lastv + 1 > 0) && ((a[i].re == 0.0F) && (a[i].im == 0.0F))) {
      lastv--;
      i--;
    }

    lastc = 3;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      knt = lastc + 3;
      ia = knt;
      do {
        exitg1 = 0;
        if (ia <= knt + lastv * 3) {
          if ((a[ia - 1].re != 0.0F) || (a[ia - 1].im != 0.0F)) {
            exitg1 = 1;
          } else {
            ia += 3;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = -1;
    lastc = 0;
  }

  if (lastv + 1 > 0) {
    if (lastc != 0) {
      if (0 <= lastc - 1) {
        std::memset(&work[0], 0, lastc * sizeof(creal32_T));
      }

      ix = 1;
      b_i = 3 * lastv + 4;
      for (knt = 4; knt <= b_i; knt += 3) {
        c_re = a[ix].re - 0.0F * a[ix].im;
        c_im = a[ix].im + 0.0F * a[ix].re;
        i = 0;
        i1 = (knt + lastc) - 1;
        for (ia = knt; ia <= i1; ia++) {
          work[i].re += a[ia - 1].re * c_re - a[ia - 1].im * c_im;
          work[i].im += a[ia - 1].re * c_im + a[ia - 1].im * c_re;
          i++;
        }

        ix++;
      }
    }

    c_re = -tau[0].re;
    c_im = -tau[0].im;
    if ((!(-tau[0].re == 0.0F)) || (!(-tau[0].im == 0.0F))) {
      knt = 3;
      i = 1;
      for (ia = 0; ia <= lastv; ia++) {
        if ((a[i].re != 0.0F) || (a[i].im != 0.0F)) {
          temp_re = a[i].re * c_re + a[i].im * c_im;
          beta1 = a[i].re * c_im - a[i].im * c_re;
          ix = 0;
          b_i = knt + 1;
          i1 = lastc + knt;
          for (ijA = b_i; ijA <= i1; ijA++) {
            a[ijA - 1].re += work[ix].re * temp_re - work[ix].im * beta1;
            a[ijA - 1].im += work[ix].re * beta1 + work[ix].im * temp_re;
            ix++;
          }
        }

        i++;
        knt += 3;
      }
    }
  }

  if ((tau[0].re != 0.0F) || (-tau[0].im != 0.0F)) {
    lastv = 2;
    i = 2;
    while ((lastv > 0) && ((a[i].re == 0.0F) && (a[i].im == 0.0F))) {
      lastv--;
      i--;
    }

    lastc = 2;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      knt = (lastc - 1) * 3 + 5;
      ia = knt;
      do {
        exitg1 = 0;
        if (ia <= (knt + lastv) - 1) {
          if ((a[ia - 1].re != 0.0F) || (a[ia - 1].im != 0.0F)) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      if (0 <= lastc - 1) {
        std::memset(&work[0], 0, lastc * sizeof(creal32_T));
      }

      i = 0;
      b_i = 3 * (lastc - 1) + 5;
      for (knt = 5; knt <= b_i; knt += 3) {
        ix = 1;
        c_re = 0.0F;
        c_im = 0.0F;
        i1 = (knt + lastv) - 1;
        for (ia = knt; ia <= i1; ia++) {
          c_re += a[ia - 1].re * a[ix].re + a[ia - 1].im * a[ix].im;
          c_im += a[ia - 1].re * a[ix].im - a[ia - 1].im * a[ix].re;
          ix++;
        }

        work[i].re += c_re - 0.0F * c_im;
        work[i].im += c_im + 0.0F * c_re;
        i++;
      }
    }

    b_a.re = -tau[0].re;
    b_a.im = tau[0].im;
    xgerc(lastv, lastc, b_a, 2, work, a, 5);
  }

  a[1] = alpha1;
  alpha1 = a[5];
  tau[1].re = 0.0F;
  tau[1].im = 0.0F;
  if (a[5].im != 0.0F) {
    beta1 = xdlapy3(a[5].re, a[5].im, 0.0F);
    if (a[5].re >= 0.0F) {
      beta1 = -beta1;
    }

    if (std::abs(beta1) < 9.86076132E-32F) {
      knt = -1;
      do {
        knt++;
        beta1 *= 1.01412048E+31F;
        alpha1.re *= 1.01412048E+31F;
        alpha1.im *= 1.01412048E+31F;
      } while (!(std::abs(beta1) >= 9.86076132E-32F));

      beta1 = xdlapy3(alpha1.re, alpha1.im, 0.0F);
      if (alpha1.re >= 0.0F) {
        beta1 = -beta1;
      }

      c_re = beta1 - alpha1.re;
      if (0.0F - alpha1.im == 0.0F) {
        tau[1].re = c_re / beta1;
        tau[1].im = 0.0F;
      } else if (c_re == 0.0F) {
        tau[1].re = 0.0F;
        tau[1].im = (0.0F - alpha1.im) / beta1;
      } else {
        tau[1].re = c_re / beta1;
        tau[1].im = (0.0F - alpha1.im) / beta1;
      }

      for (i = 0; i <= knt; i++) {
        beta1 *= 9.86076132E-32F;
      }

      alpha1.re = beta1;
      alpha1.im = 0.0F;
    } else {
      c_re = beta1 - a[5].re;
      c_im = 0.0F - a[5].im;
      if (c_im == 0.0F) {
        tau[1].re = c_re / beta1;
        tau[1].im = 0.0F;
      } else if (c_re == 0.0F) {
        tau[1].re = 0.0F;
        tau[1].im = c_im / beta1;
      } else {
        tau[1].re = c_re / beta1;
        tau[1].im = c_im / beta1;
      }

      alpha1.re = beta1;
      alpha1.im = 0.0F;
    }
  }

  a[5].re = 1.0F;
  a[5].im = 0.0F;
  if ((tau[1].re != 0.0F) || (tau[1].im != 0.0F)) {
    lastv = 0;
    i = 5;
    while ((lastv + 1 > 0) && ((a[i].re == 0.0F) && (a[i].im == 0.0F))) {
      lastv--;
      i--;
    }

    lastc = 3;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      knt = lastc + 6;
      ia = knt;
      do {
        exitg1 = 0;
        if (ia <= knt + lastv * 3) {
          if ((a[ia - 1].re != 0.0F) || (a[ia - 1].im != 0.0F)) {
            exitg1 = 1;
          } else {
            ia += 3;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = -1;
    lastc = 0;
  }

  if (lastv + 1 > 0) {
    if (lastc != 0) {
      if (0 <= lastc - 1) {
        std::memset(&work[0], 0, lastc * sizeof(creal32_T));
      }

      ix = 5;
      b_i = 3 * lastv + 7;
      for (knt = 7; knt <= b_i; knt += 3) {
        c_re = a[ix].re - 0.0F * a[ix].im;
        c_im = a[ix].im + 0.0F * a[ix].re;
        i = 0;
        i1 = (knt + lastc) - 1;
        for (ia = knt; ia <= i1; ia++) {
          work[i].re += a[ia - 1].re * c_re - a[ia - 1].im * c_im;
          work[i].im += a[ia - 1].re * c_im + a[ia - 1].im * c_re;
          i++;
        }

        ix++;
      }
    }

    c_re = -tau[1].re;
    c_im = -tau[1].im;
    if ((!(-tau[1].re == 0.0F)) || (!(-tau[1].im == 0.0F))) {
      knt = 6;
      i = 5;
      for (ia = 0; ia <= lastv; ia++) {
        if ((a[i].re != 0.0F) || (a[i].im != 0.0F)) {
          temp_re = a[i].re * c_re + a[i].im * c_im;
          beta1 = a[i].re * c_im - a[i].im * c_re;
          ix = 0;
          b_i = knt + 1;
          i1 = lastc + knt;
          for (ijA = b_i; ijA <= i1; ijA++) {
            a[ijA - 1].re += work[ix].re * temp_re - work[ix].im * beta1;
            a[ijA - 1].im += work[ix].re * beta1 + work[ix].im * temp_re;
            ix++;
          }
        }

        i++;
        knt += 3;
      }
    }
  }

  if ((tau[1].re != 0.0F) || (-tau[1].im != 0.0F)) {
    lastv = 1;
    if ((a[5].re == 0.0F) && (a[5].im == 0.0F)) {
      lastv = 0;
    }

    lastc = 1;
    ia = 9;
    do {
      exitg1 = 0;
      if (ia <= lastv + 8) {
        if ((a[8].re != 0.0F) || (a[8].im != 0.0F)) {
          exitg1 = 1;
        } else {
          ia = 10;
        }
      } else {
        lastc = 0;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      work[0].re = 0.0F;
      work[0].im = 0.0F;
      i = 0;
      for (knt = 9; knt <= 9; knt += 3) {
        ix = 5;
        c_re = 0.0F;
        c_im = 0.0F;
        for (ia = 9; ia < 10; ia++) {
          c_re += a[8].re * a[ix].re + a[8].im * a[ix].im;
          c_im += a[8].re * a[ix].im - a[8].im * a[ix].re;
          ix++;
        }

        work[i].re += c_re - 0.0F * c_im;
        work[i].im += c_im + 0.0F * c_re;
        i++;
      }
    }

    b_a.re = -tau[1].re;
    b_a.im = tau[1].im;
    xgerc(1, lastc, b_a, 6, work, a, 9);
  }

  a[5] = alpha1;
}

/* End of code generation (xgehrd.cpp) */

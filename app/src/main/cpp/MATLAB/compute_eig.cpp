/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_eig.cpp
 *
 * Code generation for function 'compute_eig'
 *
 */

/* Include files */
#include "compute_eig.h"
#include "compute_eig_data.h"
#include "compute_eig_initialize.h"
#include "rt_nonfinite.h"
#include "xgehrd.h"
#include "xgerc.h"
#include "xhseqr.h"
#include "xzggev.h"
#include <cmath>
#include <cstring>

/* Function Definitions */
void compute_eig(const creal32_T A[9], creal32_T V[9], creal32_T D[9])
{
  bool p;
  int info;
  int i;
  int j;
  bool exitg2;
  int b_i;
  creal32_T At[9];
  creal32_T work[3];
  creal32_T beta1[3];
  int exitg1;
  float colnorm;
  int kend;
  float scale;
  creal32_T tau[2];
  float t;
  float absxk;
  creal32_T b_tau;
  int lastv;
  int ix;
  if (isInitialized_compute_eig == false) {
    compute_eig_initialize();
  }

  p = true;
  for (info = 0; info < 9; info++) {
    if ((!p) || (rtIsInfF(A[info].re) || rtIsInfF(A[info].im) || (rtIsNaNF
          (A[info].re) || rtIsNaNF(A[info].im)))) {
      p = false;
    }
  }

  if (!p) {
    for (i = 0; i < 9; i++) {
      V[i].re = rtNaNF;
      V[i].im = 0.0F;
      D[i].re = 0.0F;
      D[i].im = 0.0F;
    }

    D[0].re = rtNaNF;
    D[0].im = 0.0F;
    D[4].re = rtNaNF;
    D[4].im = 0.0F;
    D[8].re = rtNaNF;
    D[8].im = 0.0F;
  } else {
    p = true;
    j = 0;
    exitg2 = false;
    while ((!exitg2) && (j < 3)) {
      b_i = 0;
      do {
        exitg1 = 0;
        if (b_i <= j) {
          info = j + 3 * b_i;
          kend = b_i + 3 * j;
          if ((!(A[kend].re == A[info].re)) || (!(A[kend].im == -A[info].im))) {
            p = false;
            exitg1 = 1;
          } else {
            b_i++;
          }
        } else {
          j++;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    if (p) {
      p = true;
      for (info = 0; info < 9; info++) {
        if ((!p) || (rtIsInfF(A[info].re) || rtIsInfF(A[info].im) || (rtIsNaNF
              (A[info].re) || rtIsNaNF(A[info].im)))) {
          p = false;
        }
      }

      if (!p) {
        for (i = 0; i < 9; i++) {
          V[i].re = rtNaNF;
          V[i].im = 0.0F;
        }

        for (b_i = 2; b_i < 4; b_i++) {
          V[b_i - 1].re = 0.0F;
          V[b_i - 1].im = 0.0F;
        }

        V[5].re = 0.0F;
        V[5].im = 0.0F;
        for (i = 0; i < 9; i++) {
          D[i].re = rtNaNF;
          D[i].im = 0.0F;
        }
      } else {
        std::memcpy(&D[0], &A[0], 9U * sizeof(creal32_T));
        xgehrd(D, tau);
        std::memcpy(&V[0], &D[0], 9U * sizeof(creal32_T));
        for (b_i = 0; b_i < 2; b_i++) {
          i = b_i + 6;
          V[i].re = 0.0F;
          V[i].im = 0.0F;
        }

        V[3].re = 0.0F;
        V[3].im = 0.0F;
        b_tau = V[2];
        V[5] = b_tau;
        V[1].re = 0.0F;
        V[1].im = 0.0F;
        V[2].re = 0.0F;
        V[2].im = 0.0F;
        V[0].re = 1.0F;
        V[0].im = 0.0F;
        work[0].re = 0.0F;
        work[0].im = 0.0F;
        work[1].re = 0.0F;
        work[1].im = 0.0F;
        work[2].re = 0.0F;
        work[2].im = 0.0F;
        V[8].re = 1.0F - tau[1].re;
        V[8].im = 0.0F - tau[1].im;
        V[7].re = 0.0F;
        V[7].im = 0.0F;
        V[4].re = 1.0F;
        V[4].im = 0.0F;
        if ((tau[0].re != 0.0F) || (tau[0].im != 0.0F)) {
          lastv = 2;
          b_i = 8;
          while ((lastv > 0) && ((V[b_i - 3].re == 0.0F) && (V[b_i - 3].im ==
                   0.0F))) {
            lastv--;
            b_i--;
          }

          info = 1;
          kend = 8;
          do {
            exitg1 = 0;
            if (kend <= lastv + 7) {
              if ((V[kend - 1].re != 0.0F) || (V[kend - 1].im != 0.0F)) {
                exitg1 = 1;
              } else {
                kend++;
              }
            } else {
              info = 0;
              exitg1 = 1;
            }
          } while (exitg1 == 0);
        } else {
          lastv = 0;
          info = 0;
        }

        if (lastv > 0) {
          if (info != 0) {
            work[0].re = 0.0F;
            work[0].im = 0.0F;
            j = 0;
            i = lastv + 7;
            for (b_i = 8; b_i <= 8; b_i += 3) {
              ix = 4;
              scale = 0.0F;
              absxk = 0.0F;
              for (kend = 8; kend <= i; kend++) {
                scale += V[kend - 1].re * V[ix].re + V[kend - 1].im * V[ix].im;
                absxk += V[kend - 1].re * V[ix].im - V[kend - 1].im * V[ix].re;
                ix++;
              }

              work[j].re += scale - 0.0F * absxk;
              work[j].im += absxk + 0.0F * scale;
              j++;
            }
          }

          b_tau.re = -tau[0].re;
          b_tau.im = -tau[0].im;
          xgerc(lastv, info, b_tau, 5, work, V, 8);
        }

        scale = -tau[0].re;
        absxk = -tau[0].im;
        for (info = 6; info < 7; info++) {
          t = scale * V[5].im + absxk * V[5].re;
          V[5].re = scale * V[5].re - absxk * V[5].im;
          V[5].im = t;
        }

        V[4].re = 1.0F - tau[0].re;
        V[4].im = 0.0F - tau[0].im;
        xhseqr(D, V);
      }

      D[0].im = 0.0F;
      D[4].im = 0.0F;
      D[1].re = 0.0F;
      D[1].im = 0.0F;
      D[3].re = 0.0F;
      D[3].im = 0.0F;
      D[8].im = 0.0F;
      D[5].re = 0.0F;
      D[5].im = 0.0F;
      for (b_i = 0; b_i < 2; b_i++) {
        D[b_i + 6].re = 0.0F;
        D[b_i + 6].im = 0.0F;
      }
    } else {
      std::memcpy(&At[0], &A[0], 9U * sizeof(creal32_T));
      xzggev(At, &info, work, beta1, V);
      for (b_i = 0; b_i <= 6; b_i += 3) {
        colnorm = 0.0F;
        scale = 1.29246971E-26F;
        kend = b_i + 3;
        for (info = b_i + 1; info <= kend; info++) {
          absxk = std::abs(V[info - 1].re);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = colnorm * t * t + 1.0F;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }

          absxk = std::abs(V[info - 1].im);
          if (absxk > scale) {
            t = scale / absxk;
            colnorm = colnorm * t * t + 1.0F;
            scale = absxk;
          } else {
            t = absxk / scale;
            colnorm += t * t;
          }
        }

        colnorm = scale * std::sqrt(colnorm);
        i = b_i + 3;
        for (j = b_i + 1; j <= i; j++) {
          absxk = V[j - 1].re;
          t = V[j - 1].im;
          if (t == 0.0F) {
            scale = absxk / colnorm;
            t = 0.0F;
          } else if (absxk == 0.0F) {
            scale = 0.0F;
            t /= colnorm;
          } else {
            scale = absxk / colnorm;
            t /= colnorm;
          }

          V[j - 1].re = scale;
          V[j - 1].im = t;
        }
      }

      std::memset(&D[0], 0, 9U * sizeof(creal32_T));
      if (beta1[0].im == 0.0F) {
        if (work[0].im == 0.0F) {
          D[0].re = work[0].re / beta1[0].re;
          D[0].im = 0.0F;
        } else if (work[0].re == 0.0F) {
          D[0].re = 0.0F;
          D[0].im = work[0].im / beta1[0].re;
        } else {
          D[0].re = work[0].re / beta1[0].re;
          D[0].im = work[0].im / beta1[0].re;
        }
      } else if (beta1[0].re == 0.0F) {
        if (work[0].re == 0.0F) {
          D[0].re = work[0].im / beta1[0].im;
          D[0].im = 0.0F;
        } else if (work[0].im == 0.0F) {
          D[0].re = 0.0F;
          D[0].im = -(work[0].re / beta1[0].im);
        } else {
          D[0].re = work[0].im / beta1[0].im;
          D[0].im = -(work[0].re / beta1[0].im);
        }
      } else {
        t = std::abs(beta1[0].re);
        absxk = std::abs(beta1[0].im);
        if (t > absxk) {
          absxk = beta1[0].im / beta1[0].re;
          scale = beta1[0].re + absxk * beta1[0].im;
          D[0].re = (work[0].re + absxk * work[0].im) / scale;
          D[0].im = (work[0].im - absxk * work[0].re) / scale;
        } else if (absxk == t) {
          if (beta1[0].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[0].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          D[0].re = (work[0].re * scale + work[0].im * absxk) / t;
          D[0].im = (work[0].im * scale - work[0].re * absxk) / t;
        } else {
          absxk = beta1[0].re / beta1[0].im;
          scale = beta1[0].im + absxk * beta1[0].re;
          D[0].re = (absxk * work[0].re + work[0].im) / scale;
          D[0].im = (absxk * work[0].im - work[0].re) / scale;
        }
      }

      if (beta1[1].im == 0.0F) {
        if (work[1].im == 0.0F) {
          D[4].re = work[1].re / beta1[1].re;
          D[4].im = 0.0F;
        } else if (work[1].re == 0.0F) {
          D[4].re = 0.0F;
          D[4].im = work[1].im / beta1[1].re;
        } else {
          D[4].re = work[1].re / beta1[1].re;
          D[4].im = work[1].im / beta1[1].re;
        }
      } else if (beta1[1].re == 0.0F) {
        if (work[1].re == 0.0F) {
          D[4].re = work[1].im / beta1[1].im;
          D[4].im = 0.0F;
        } else if (work[1].im == 0.0F) {
          D[4].re = 0.0F;
          D[4].im = -(work[1].re / beta1[1].im);
        } else {
          D[4].re = work[1].im / beta1[1].im;
          D[4].im = -(work[1].re / beta1[1].im);
        }
      } else {
        t = std::abs(beta1[1].re);
        absxk = std::abs(beta1[1].im);
        if (t > absxk) {
          absxk = beta1[1].im / beta1[1].re;
          scale = beta1[1].re + absxk * beta1[1].im;
          D[4].re = (work[1].re + absxk * work[1].im) / scale;
          D[4].im = (work[1].im - absxk * work[1].re) / scale;
        } else if (absxk == t) {
          if (beta1[1].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[1].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          D[4].re = (work[1].re * scale + work[1].im * absxk) / t;
          D[4].im = (work[1].im * scale - work[1].re * absxk) / t;
        } else {
          absxk = beta1[1].re / beta1[1].im;
          scale = beta1[1].im + absxk * beta1[1].re;
          D[4].re = (absxk * work[1].re + work[1].im) / scale;
          D[4].im = (absxk * work[1].im - work[1].re) / scale;
        }
      }

      if (beta1[2].im == 0.0F) {
        if (work[2].im == 0.0F) {
          D[8].re = work[2].re / beta1[2].re;
          D[8].im = 0.0F;
        } else if (work[2].re == 0.0F) {
          D[8].re = 0.0F;
          D[8].im = work[2].im / beta1[2].re;
        } else {
          D[8].re = work[2].re / beta1[2].re;
          D[8].im = work[2].im / beta1[2].re;
        }
      } else if (beta1[2].re == 0.0F) {
        if (work[2].re == 0.0F) {
          D[8].re = work[2].im / beta1[2].im;
          D[8].im = 0.0F;
        } else if (work[2].im == 0.0F) {
          D[8].re = 0.0F;
          D[8].im = -(work[2].re / beta1[2].im);
        } else {
          D[8].re = work[2].im / beta1[2].im;
          D[8].im = -(work[2].re / beta1[2].im);
        }
      } else {
        t = std::abs(beta1[2].re);
        absxk = std::abs(beta1[2].im);
        if (t > absxk) {
          absxk = beta1[2].im / beta1[2].re;
          scale = beta1[2].re + absxk * beta1[2].im;
          D[8].re = (work[2].re + absxk * work[2].im) / scale;
          D[8].im = (work[2].im - absxk * work[2].re) / scale;
        } else if (absxk == t) {
          if (beta1[2].re > 0.0F) {
            scale = 0.5F;
          } else {
            scale = -0.5F;
          }

          if (beta1[2].im > 0.0F) {
            absxk = 0.5F;
          } else {
            absxk = -0.5F;
          }

          D[8].re = (work[2].re * scale + work[2].im * absxk) / t;
          D[8].im = (work[2].im * scale - work[2].re * absxk) / t;
        } else {
          absxk = beta1[2].re / beta1[2].im;
          scale = beta1[2].im + absxk * beta1[2].re;
          D[8].re = (absxk * work[2].re + work[2].im) / scale;
          D[8].im = (absxk * work[2].im - work[2].re) / scale;
        }
      }
    }
  }
}

/* End of code generation (compute_eig.cpp) */

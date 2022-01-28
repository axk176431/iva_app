/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * svd.cpp
 *
 * Code generation for function 'svd'
 *
 */

/* Include files */
#include "svd.h"
#include "compute_iva.h"
#include "compute_iva_rtwutil.h"
#include "init_iva.h"
#include "rt_nonfinite.h"
#include "xdotc.h"
#include "xnrm2.h"
#include "xrot.h"
#include "xrotg.h"
#include "xswap.h"
#include <cmath>

/* Function Definitions */
void svd(const creal32_T A[4], creal32_T U[4], float s[2], creal32_T V[4])
{
  creal32_T b_A[4];
  float nrm;
  creal32_T b_s[2];
  float ztest;
  int m;
  creal32_T e[2];
  float r_re;
  float b;
  float re;
  float r_im;
  float scale;
  creal32_T fc;
  creal32_T Vf[4];
  float rt;
  int iter;
  float snorm;
  int qs;
  int q;
  bool exitg1;
  int kase;
  int i;
  b_A[0] = A[0];
  b_A[1] = A[1];
  b_A[2] = A[2];
  b_A[3] = A[3];
  nrm = xnrm2(A);
  if (nrm > 0.0F) {
    if ((A[0].re == 0.0F) && (A[0].im == 0.0F)) {
      b_s[0].re = nrm;
      b_s[0].im = 0.0F;
    } else {
      ztest = nrm / rt_hypotf_snf(A[0].re, A[0].im);
      b_s[0].re = ztest * A[0].re;
      b_s[0].im = ztest * A[0].im;
    }

    if (rt_hypotf_snf(b_s[0].re, b_s[0].im) >= 9.86076132E-32F) {
      if (b_s[0].im == 0.0F) {
        r_re = 1.0F / b_s[0].re;
        r_im = 0.0F;
      } else if (b_s[0].re == 0.0F) {
        r_re = 0.0F;
        r_im = -(1.0F / b_s[0].im);
      } else {
        b = std::abs(b_s[0].re);
        nrm = std::abs(b_s[0].im);
        if (b > nrm) {
          nrm = b_s[0].im / b_s[0].re;
          ztest = b_s[0].re + nrm * b_s[0].im;
          r_re = (1.0F + nrm * 0.0F) / ztest;
          r_im = (0.0F - nrm) / ztest;
        } else if (nrm == b) {
          if (b_s[0].re > 0.0F) {
            nrm = 0.5F;
          } else {
            nrm = -0.5F;
          }

          if (b_s[0].im > 0.0F) {
            ztest = 0.5F;
          } else {
            ztest = -0.5F;
          }

          r_re = (nrm + 0.0F * ztest) / b;
          r_im = (0.0F * nrm - ztest) / b;
        } else {
          nrm = b_s[0].re / b_s[0].im;
          ztest = b_s[0].im + nrm * b_s[0].re;
          r_re = nrm / ztest;
          r_im = (nrm * 0.0F - 1.0F) / ztest;
        }
      }

      b_A[0].re = r_re * A[0].re - r_im * A[0].im;
      b_A[0].im = r_re * A[0].im + r_im * A[0].re;
      b_A[1].re = r_re * A[1].re - r_im * A[1].im;
      b_A[1].im = r_re * A[1].im + r_im * A[1].re;
    } else {
      if (b_s[0].im == 0.0F) {
        if (A[0].im == 0.0F) {
          re = A[0].re / b_s[0].re;
          scale = 0.0F;
        } else if (A[0].re == 0.0F) {
          re = 0.0F;
          scale = A[0].im / b_s[0].re;
        } else {
          re = A[0].re / b_s[0].re;
          scale = A[0].im / b_s[0].re;
        }
      } else if (b_s[0].re == 0.0F) {
        if (A[0].re == 0.0F) {
          re = A[0].im / b_s[0].im;
          scale = 0.0F;
        } else if (A[0].im == 0.0F) {
          re = 0.0F;
          scale = -(A[0].re / b_s[0].im);
        } else {
          re = A[0].im / b_s[0].im;
          scale = -(A[0].re / b_s[0].im);
        }
      } else {
        b = std::abs(b_s[0].re);
        nrm = std::abs(b_s[0].im);
        if (b > nrm) {
          nrm = b_s[0].im / b_s[0].re;
          ztest = b_s[0].re + nrm * b_s[0].im;
          re = (A[0].re + nrm * A[0].im) / ztest;
          scale = (A[0].im - nrm * A[0].re) / ztest;
        } else if (nrm == b) {
          if (b_s[0].re > 0.0F) {
            nrm = 0.5F;
          } else {
            nrm = -0.5F;
          }

          if (b_s[0].im > 0.0F) {
            ztest = 0.5F;
          } else {
            ztest = -0.5F;
          }

          re = (A[0].re * nrm + A[0].im * ztest) / b;
          scale = (A[0].im * nrm - A[0].re * ztest) / b;
        } else {
          nrm = b_s[0].re / b_s[0].im;
          ztest = b_s[0].im + nrm * b_s[0].re;
          re = (nrm * A[0].re + A[0].im) / ztest;
          scale = (nrm * A[0].im - A[0].re) / ztest;
        }
      }

      b_A[0].re = re;
      b_A[0].im = scale;
      if (b_s[0].im == 0.0F) {
        if (A[1].im == 0.0F) {
          re = A[1].re / b_s[0].re;
          scale = 0.0F;
        } else if (A[1].re == 0.0F) {
          re = 0.0F;
          scale = A[1].im / b_s[0].re;
        } else {
          re = A[1].re / b_s[0].re;
          scale = A[1].im / b_s[0].re;
        }
      } else if (b_s[0].re == 0.0F) {
        if (A[1].re == 0.0F) {
          re = A[1].im / b_s[0].im;
          scale = 0.0F;
        } else if (A[1].im == 0.0F) {
          re = 0.0F;
          scale = -(A[1].re / b_s[0].im);
        } else {
          re = A[1].im / b_s[0].im;
          scale = -(A[1].re / b_s[0].im);
        }
      } else {
        b = std::abs(b_s[0].re);
        nrm = std::abs(b_s[0].im);
        if (b > nrm) {
          nrm = b_s[0].im / b_s[0].re;
          ztest = b_s[0].re + nrm * b_s[0].im;
          re = (A[1].re + nrm * A[1].im) / ztest;
          scale = (A[1].im - nrm * A[1].re) / ztest;
        } else if (nrm == b) {
          if (b_s[0].re > 0.0F) {
            nrm = 0.5F;
          } else {
            nrm = -0.5F;
          }

          if (b_s[0].im > 0.0F) {
            ztest = 0.5F;
          } else {
            ztest = -0.5F;
          }

          re = (A[1].re * nrm + A[1].im * ztest) / b;
          scale = (A[1].im * nrm - A[1].re * ztest) / b;
        } else {
          nrm = b_s[0].re / b_s[0].im;
          ztest = b_s[0].im + nrm * b_s[0].re;
          re = (nrm * A[1].re + A[1].im) / ztest;
          scale = (nrm * A[1].im - A[1].re) / ztest;
        }
      }

      b_A[1].re = re;
      b_A[1].im = scale;
    }

    b_A[0].re++;
    b_s[0].re = -b_s[0].re;
    b_s[0].im = -b_s[0].im;
    fc = xdotc(b_A, b_A);
    if (b_A[0].im == 0.0F) {
      if (fc.im == 0.0F) {
        re = fc.re / b_A[0].re;
        scale = 0.0F;
      } else if (fc.re == 0.0F) {
        re = 0.0F;
        scale = fc.im / b_A[0].re;
      } else {
        re = fc.re / b_A[0].re;
        scale = fc.im / b_A[0].re;
      }
    } else if (b_A[0].re == 0.0F) {
      if (fc.re == 0.0F) {
        re = fc.im / b_A[0].im;
        scale = 0.0F;
      } else if (fc.im == 0.0F) {
        re = 0.0F;
        scale = -(fc.re / b_A[0].im);
      } else {
        re = fc.im / b_A[0].im;
        scale = -(fc.re / b_A[0].im);
      }
    } else {
      b = std::abs(b_A[0].re);
      nrm = std::abs(b_A[0].im);
      if (b > nrm) {
        nrm = b_A[0].im / b_A[0].re;
        ztest = b_A[0].re + nrm * b_A[0].im;
        re = (fc.re + nrm * fc.im) / ztest;
        scale = (fc.im - nrm * fc.re) / ztest;
      } else if (nrm == b) {
        if (b_A[0].re > 0.0F) {
          nrm = 0.5F;
        } else {
          nrm = -0.5F;
        }

        if (b_A[0].im > 0.0F) {
          ztest = 0.5F;
        } else {
          ztest = -0.5F;
        }

        re = (fc.re * nrm + fc.im * ztest) / b;
        scale = (fc.im * nrm - fc.re * ztest) / b;
      } else {
        nrm = b_A[0].re / b_A[0].im;
        ztest = b_A[0].im + nrm * b_A[0].re;
        re = (nrm * fc.re + fc.im) / ztest;
        scale = (nrm * fc.im - fc.re) / ztest;
      }
    }

    if ((!(-re == 0.0F)) || (!(-scale == 0.0F))) {
      b_A[2].re = A[2].re + (-re * b_A[0].re - -scale * b_A[0].im);
      b_A[2].im = A[2].im + (-re * b_A[0].im + -scale * b_A[0].re);
      b_A[3].re = A[3].re + (-re * b_A[1].re - -scale * b_A[1].im);
      b_A[3].im = A[3].im + (-re * b_A[1].im + -scale * b_A[1].re);
    }
  } else {
    b_s[0].re = 0.0F;
    b_s[0].im = 0.0F;
  }

  m = 2;
  b_s[1] = b_A[3];
  e[0] = b_A[2];
  e[1].re = 0.0F;
  e[1].im = 0.0F;
  U[0] = b_A[0];
  U[2].re = 0.0F;
  U[2].im = 0.0F;
  U[1] = b_A[1];
  U[3].re = 1.0F;
  U[3].im = 0.0F;
  if ((b_s[0].re != 0.0F) || (b_s[0].im != 0.0F)) {
    fc = xdotc(U, U);
    if (b_A[0].im == 0.0F) {
      if (fc.im == 0.0F) {
        re = fc.re / b_A[0].re;
        scale = 0.0F;
      } else if (fc.re == 0.0F) {
        re = 0.0F;
        scale = fc.im / b_A[0].re;
      } else {
        re = fc.re / b_A[0].re;
        scale = fc.im / b_A[0].re;
      }
    } else if (b_A[0].re == 0.0F) {
      if (fc.re == 0.0F) {
        re = fc.im / b_A[0].im;
        scale = 0.0F;
      } else if (fc.im == 0.0F) {
        re = 0.0F;
        scale = -(fc.re / b_A[0].im);
      } else {
        re = fc.im / b_A[0].im;
        scale = -(fc.re / b_A[0].im);
      }
    } else {
      b = std::abs(b_A[0].re);
      nrm = std::abs(b_A[0].im);
      if (b > nrm) {
        nrm = b_A[0].im / b_A[0].re;
        ztest = b_A[0].re + nrm * b_A[0].im;
        re = (fc.re + nrm * fc.im) / ztest;
        scale = (fc.im - nrm * fc.re) / ztest;
      } else if (nrm == b) {
        if (b_A[0].re > 0.0F) {
          nrm = 0.5F;
        } else {
          nrm = -0.5F;
        }

        if (b_A[0].im > 0.0F) {
          ztest = 0.5F;
        } else {
          ztest = -0.5F;
        }

        re = (fc.re * nrm + fc.im * ztest) / b;
        scale = (fc.im * nrm - fc.re * ztest) / b;
      } else {
        nrm = b_A[0].re / b_A[0].im;
        ztest = b_A[0].im + nrm * b_A[0].re;
        re = (nrm * fc.re + fc.im) / ztest;
        scale = (nrm * fc.im - fc.re) / ztest;
      }
    }

    if ((!(-re == 0.0F)) || (!(-scale == 0.0F))) {
      U[2].re = -re * b_A[0].re - -scale * b_A[0].im;
      U[2].im = -re * b_A[0].im + -scale * b_A[0].re;
      U[3].re = 1.0F + (-re * b_A[1].re - -scale * b_A[1].im);
      U[3].im = -re * b_A[1].im + -scale * b_A[1].re;
    }

    U[0].im = -b_A[0].im;
    U[1].re = -b_A[1].re;
    U[1].im = -b_A[1].im;
    U[0].re = -b_A[0].re + 1.0F;
  } else {
    U[1].re = 0.0F;
    U[1].im = 0.0F;
    U[0].re = 1.0F;
    U[0].im = 0.0F;
  }

  Vf[2].re = 0.0F;
  Vf[2].im = 0.0F;
  Vf[3].re = 1.0F;
  Vf[3].im = 0.0F;
  Vf[1].re = 0.0F;
  Vf[1].im = 0.0F;
  Vf[0].re = 1.0F;
  Vf[0].im = 0.0F;
  if ((b_s[0].re != 0.0F) || (b_s[0].im != 0.0F)) {
    rt = rt_hypotf_snf(b_s[0].re, b_s[0].im);
    if (b_s[0].im == 0.0F) {
      r_re = b_s[0].re / rt;
      r_im = 0.0F;
    } else if (b_s[0].re == 0.0F) {
      r_re = 0.0F;
      r_im = b_s[0].im / rt;
    } else {
      r_re = b_s[0].re / rt;
      r_im = b_s[0].im / rt;
    }

    b_s[0].re = rt;
    b_s[0].im = 0.0F;
    if (r_im == 0.0F) {
      if (b_A[2].im == 0.0F) {
        re = b_A[2].re / r_re;
        scale = 0.0F;
      } else if (b_A[2].re == 0.0F) {
        re = 0.0F;
        scale = b_A[2].im / r_re;
      } else {
        re = b_A[2].re / r_re;
        scale = b_A[2].im / r_re;
      }
    } else if (r_re == 0.0F) {
      if (b_A[2].re == 0.0F) {
        re = b_A[2].im / r_im;
        scale = 0.0F;
      } else if (b_A[2].im == 0.0F) {
        re = 0.0F;
        scale = -(b_A[2].re / r_im);
      } else {
        re = b_A[2].im / r_im;
        scale = -(b_A[2].re / r_im);
      }
    } else {
      b = std::abs(r_re);
      nrm = std::abs(r_im);
      if (b > nrm) {
        nrm = r_im / r_re;
        ztest = r_re + nrm * r_im;
        re = (b_A[2].re + nrm * b_A[2].im) / ztest;
        scale = (b_A[2].im - nrm * b_A[2].re) / ztest;
      } else if (nrm == b) {
        if (r_re > 0.0F) {
          nrm = 0.5F;
        } else {
          nrm = -0.5F;
        }

        if (r_im > 0.0F) {
          ztest = 0.5F;
        } else {
          ztest = -0.5F;
        }

        re = (b_A[2].re * nrm + b_A[2].im * ztest) / b;
        scale = (b_A[2].im * nrm - b_A[2].re * ztest) / b;
      } else {
        nrm = r_re / r_im;
        ztest = r_im + nrm * r_re;
        re = (nrm * b_A[2].re + b_A[2].im) / ztest;
        scale = (nrm * b_A[2].im - b_A[2].re) / ztest;
      }
    }

    e[0].re = re;
    e[0].im = scale;
    for (qs = 1; qs < 3; qs++) {
      ztest = U[qs - 1].im;
      nrm = U[qs - 1].re;
      scale = r_re * ztest + r_im * nrm;
      nrm = r_re * nrm - r_im * ztest;
      U[qs - 1].re = nrm;
      U[qs - 1].im = scale;
    }
  }

  if ((e[0].re != 0.0F) || (e[0].im != 0.0F)) {
    rt = rt_hypotf_snf(e[0].re, e[0].im);
    if (e[0].im == 0.0F) {
      r_re = rt / e[0].re;
      r_im = 0.0F;
    } else if (e[0].re == 0.0F) {
      if (rt == 0.0F) {
        r_re = 0.0F / e[0].im;
        r_im = 0.0F;
      } else {
        r_re = 0.0F;
        r_im = -(rt / e[0].im);
      }
    } else {
      b = std::abs(e[0].re);
      nrm = std::abs(e[0].im);
      if (b > nrm) {
        nrm = e[0].im / e[0].re;
        ztest = e[0].re + nrm * e[0].im;
        r_re = (rt + nrm * 0.0F) / ztest;
        r_im = (0.0F - nrm * rt) / ztest;
      } else if (nrm == b) {
        if (e[0].re > 0.0F) {
          nrm = 0.5F;
        } else {
          nrm = -0.5F;
        }

        if (e[0].im > 0.0F) {
          ztest = 0.5F;
        } else {
          ztest = -0.5F;
        }

        r_re = (rt * nrm + 0.0F * ztest) / b;
        r_im = (0.0F * nrm - rt * ztest) / b;
      } else {
        nrm = e[0].re / e[0].im;
        ztest = e[0].im + nrm * e[0].re;
        r_re = nrm * rt / ztest;
        r_im = (nrm * 0.0F - rt) / ztest;
      }
    }

    e[0].re = rt;
    e[0].im = 0.0F;
    b_s[1].re = b_A[3].re * r_re - b_A[3].im * r_im;
    b_s[1].im = b_A[3].re * r_im + b_A[3].im * r_re;
    Vf[2].re = r_re * 0.0F - r_im * 0.0F;
    Vf[2].im = r_re * 0.0F + r_im * 0.0F;
    Vf[3].re = r_re - r_im * 0.0F;
    Vf[3].im = r_re * 0.0F + r_im;
  }

  if ((b_s[1].re != 0.0F) || (b_s[1].im != 0.0F)) {
    rt = rt_hypotf_snf(b_s[1].re, b_s[1].im);
    if (b_s[1].im == 0.0F) {
      r_re = b_s[1].re / rt;
      r_im = 0.0F;
    } else if (b_s[1].re == 0.0F) {
      r_re = 0.0F;
      r_im = b_s[1].im / rt;
    } else {
      r_re = b_s[1].re / rt;
      r_im = b_s[1].im / rt;
    }

    b_s[1].re = rt;
    b_s[1].im = 0.0F;
    for (qs = 3; qs < 5; qs++) {
      ztest = U[qs - 1].im;
      nrm = U[qs - 1].re;
      scale = r_re * ztest + r_im * nrm;
      nrm = r_re * nrm - r_im * ztest;
      U[qs - 1].re = nrm;
      U[qs - 1].im = scale;
    }
  }

  iter = 0;
  snorm = 0.0F;
  nrm = std::abs(b_s[0].re);
  ztest = std::abs(e[0].re);
  if ((nrm > ztest) || rtIsNaNF(ztest)) {
    ztest = nrm;
  }

  if (!rtIsNaNF(ztest)) {
    snorm = ztest;
  }

  nrm = std::abs(b_s[1].re);
  if (nrm > 0.0F) {
    ztest = nrm;
  } else {
    ztest = 0.0F;
  }

  if ((!(snorm > ztest)) && (!rtIsNaNF(ztest))) {
    snorm = ztest;
  }

  while ((m > 0) && (iter < 75)) {
    q = m - 1;
    exitg1 = false;
    while (!(exitg1 || (q == 0))) {
      nrm = std::abs(e[0].re);
      if ((nrm <= 1.1920929E-7F * (std::abs(b_s[0].re) + std::abs(b_s[1].re))) ||
          (nrm <= 9.86076132E-32F) || ((iter > 20) && (nrm <= 1.1920929E-7F *
            snorm))) {
        e[0].re = 0.0F;
        e[0].im = 0.0F;
        exitg1 = true;
      } else {
        q = 0;
      }
    }

    if (q == m - 1) {
      kase = 4;
    } else {
      qs = m;
      kase = m;
      exitg1 = false;
      while ((!exitg1) && (kase >= q)) {
        qs = kase;
        if (kase == q) {
          exitg1 = true;
        } else {
          nrm = 0.0F;
          if (kase < m) {
            nrm = std::abs(e[0].re);
          }

          if (kase > q + 1) {
            nrm += std::abs(e[0].re);
          }

          ztest = std::abs(b_s[kase - 1].re);
          if ((ztest <= 1.1920929E-7F * nrm) || (ztest <= 9.86076132E-32F)) {
            b_s[kase - 1].re = 0.0F;
            b_s[kase - 1].im = 0.0F;
            exitg1 = true;
          } else {
            kase--;
          }
        }
      }

      if (qs == q) {
        kase = 3;
      } else if (qs == m) {
        kase = 1;
      } else {
        kase = 2;
        q = qs;
      }
    }

    switch (kase) {
     case 1:
      r_im = e[0].re;
      e[0].re = 0.0F;
      e[0].im = 0.0F;
      i = m - 1;
      if (i >= q + 1) {
        b_s[0].im = 0.0F;
      }

      for (qs = i; qs >= q + 1; qs--) {
        nrm = b_s[0].re;
        xrotg(&nrm, &r_im, &rt, &r_re);
        b_s[0].re = nrm;
        xrot(Vf, 1, ((m - 1) << 1) + 1, rt, r_re);
      }
      break;

     case 2:
      r_im = e[q - 1].re;
      e[q - 1].re = 0.0F;
      e[q - 1].im = 0.0F;
      for (qs = q + 1; qs <= m; qs++) {
        nrm = b_s[qs - 1].re;
        xrotg(&nrm, &r_im, &rt, &r_re);
        b_s[qs - 1].re = nrm;
        b_s[qs - 1].im = 0.0F;
        ztest = e[qs - 1].re;
        r_im = -r_re * ztest;
        ztest *= rt;
        e[qs - 1].re = ztest;
        e[qs - 1].im *= rt;
        xrot(U, ((qs - 1) << 1) + 1, ((q - 1) << 1) + 1, rt, r_re);
      }
      break;

     case 3:
      scale = std::abs(b_s[m - 1].re);
      ztest = std::abs(b_s[0].re);
      if ((!(scale > ztest)) && (!rtIsNaNF(ztest))) {
        scale = ztest;
      }

      ztest = std::abs(e[0].re);
      if ((!(scale > ztest)) && (!rtIsNaNF(ztest))) {
        scale = ztest;
      }

      ztest = std::abs(b_s[q].re);
      if ((!(scale > ztest)) && (!rtIsNaNF(ztest))) {
        scale = ztest;
      }

      ztest = std::abs(e[q].re);
      if ((!(scale > ztest)) && (!rtIsNaNF(ztest))) {
        scale = ztest;
      }

      rt = b_s[m - 1].re / scale;
      nrm = b_s[0].re / scale;
      ztest = e[0].re / scale;
      r_re = b_s[q].re / scale;
      b = ((nrm + rt) * (nrm - rt) + ztest * ztest) / 2.0F;
      nrm = rt * ztest;
      nrm *= nrm;
      if ((b != 0.0F) || (nrm != 0.0F)) {
        ztest = std::sqrt(b * b + nrm);
        if (b < 0.0F) {
          ztest = -ztest;
        }

        ztest = nrm / (b + ztest);
      } else {
        ztest = 0.0F;
      }

      r_im = (r_re + rt) * (r_re - rt) + ztest;
      nrm = r_re * (e[q].re / scale);
      for (qs = q + 1; qs < 2; qs++) {
        xrotg(&r_im, &nrm, &rt, &r_re);
        r_im = rt * b_s[0].re + r_re * e[0].re;
        re = rt * e[0].re - r_re * b_s[0].re;
        scale = rt * e[0].im - r_re * b_s[0].im;
        e[0].re = re;
        e[0].im = scale;
        nrm = r_re * b_s[1].re;
        ztest = rt * b_s[1].re;
        xrot(Vf, 1, 3, rt, r_re);
        xrotg(&r_im, &nrm, &b, &r_re);
        b_s[0].re = r_im;
        b_s[0].im = 0.0F;
        r_im = b * re + r_re * ztest;
        ztest = -r_re * re + b * ztest;
        b_s[1].re = ztest;
        b_s[1].im = -r_re * scale + b * (rt * b_s[1].im);
        nrm = r_re * e[1].re;
        e[1].re *= b;
        e[1].im *= b;
        xrot(U, 1, 3, b, r_re);
      }

      e[0].re = r_im;
      e[0].im = 0.0F;
      iter++;
      break;

     default:
      if (b_s[q].re < 0.0F) {
        b_s[q].re = -b_s[q].re;
        b_s[q].im = 0.0F;
        kase = q << 1;
        i = kase + 2;
        for (qs = kase + 1; qs <= i; qs++) {
          ztest = Vf[qs - 1].im;
          nrm = Vf[qs - 1].re;
          scale = -ztest + 0.0F * nrm;
          nrm = -nrm - 0.0F * ztest;
          Vf[qs - 1].re = nrm;
          Vf[qs - 1].im = scale;
        }
      }

      while ((q + 1 < 2) && (b_s[0].re < b_s[1].re)) {
        rt = b_s[0].re;
        b_s[0].re = b_s[1].re;
        b_s[0].im = 0.0F;
        b_s[1].re = rt;
        b_s[1].im = 0.0F;
        xswap(Vf);
        xswap(U);
        q = 1;
      }

      iter = 0;
      m--;
      break;
    }
  }

  s[0] = b_s[0].re;
  V[0] = Vf[0];
  V[1] = Vf[1];
  s[1] = b_s[1].re;
  V[2] = Vf[2];
  V[3] = Vf[3];
}

/* End of code generation (svd.cpp) */

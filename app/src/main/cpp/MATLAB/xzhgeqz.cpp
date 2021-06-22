/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzhgeqz.cpp
 *
 * Code generation for function 'xzhgeqz'
 *
 */

/* Include files */
#include "xzhgeqz.h"
#include "compute_eig.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xzlartg.h"
#include <cmath>

/* Function Definitions */
void xzhgeqz(creal32_T A[9], int ilo, int ihi, creal32_T Z[9], int *info,
             creal32_T alpha1[3], creal32_T beta1[3])
{
  float eshift_re;
  float eshift_im;
  creal32_T ctemp;
  float anorm;
  float scale;
  float reAij;
  float sumsq;
  float b_atol;
  bool firstNonZero;
  int j;
  int ctemp_tmp;
  float ascale;
  int i;
  int jp1;
  float imAij;
  bool guard1 = false;
  bool guard2 = false;
  int ifirst;
  int istart;
  float temp2;
  int ilast;
  int ilastm1;
  int iiter;
  bool goto60;
  bool goto70;
  bool goto90;
  int jiter;
  int exitg1;
  bool b_guard1 = false;
  bool guard3 = false;
  bool exitg2;
  creal32_T shift;
  float ad22_re;
  float ad22_im;
  float t1_re;
  float t1_im;
  float t1_im_tmp;
  creal32_T b_ascale;
  int ad22_re_tmp;
  *info = 0;
  alpha1[0].re = 0.0F;
  alpha1[0].im = 0.0F;
  beta1[0].re = 1.0F;
  beta1[0].im = 0.0F;
  alpha1[1].re = 0.0F;
  alpha1[1].im = 0.0F;
  beta1[1].re = 1.0F;
  beta1[1].im = 0.0F;
  alpha1[2].re = 0.0F;
  alpha1[2].im = 0.0F;
  beta1[2].re = 1.0F;
  beta1[2].im = 0.0F;
  eshift_re = 0.0F;
  eshift_im = 0.0F;
  ctemp.re = 0.0F;
  ctemp.im = 0.0F;
  anorm = 0.0F;
  if (ilo <= ihi) {
    scale = 0.0F;
    sumsq = 0.0F;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      ctemp_tmp = j + 1;
      if (ihi < j + 1) {
        ctemp_tmp = ihi;
      }

      for (i = ilo; i <= ctemp_tmp; i++) {
        jp1 = (i + 3 * (j - 1)) - 1;
        reAij = A[jp1].re;
        imAij = A[jp1].im;
        if (reAij != 0.0F) {
          anorm = std::abs(reAij);
          if (firstNonZero) {
            sumsq = 1.0F;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = sumsq * temp2 * temp2 + 1.0F;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0F) {
          anorm = std::abs(imAij);
          if (firstNonZero) {
            sumsq = 1.0F;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = sumsq * temp2 * temp2 + 1.0F;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    anorm = scale * std::sqrt(sumsq);
  }

  reAij = 1.1920929E-7F * anorm;
  b_atol = 1.17549435E-38F;
  if (reAij > 1.17549435E-38F) {
    b_atol = reAij;
  }

  reAij = 1.17549435E-38F;
  if (anorm > 1.17549435E-38F) {
    reAij = anorm;
  }

  ascale = 1.0F / reAij;
  firstNonZero = true;
  ctemp_tmp = ihi + 1;
  for (j = ctemp_tmp; j < 4; j++) {
    alpha1[j - 1] = A[(j + 3 * (j - 1)) - 1];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 0;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1) - 1) {
        b_guard1 = false;
        if (ilast + 1 == ilo) {
          goto60 = true;
          b_guard1 = true;
        } else {
          ctemp_tmp = ilast + 3 * ilastm1;
          if (std::abs(A[ctemp_tmp].re) + std::abs(A[ctemp_tmp].im) <= b_atol) {
            A[ctemp_tmp].re = 0.0F;
            A[ctemp_tmp].im = 0.0F;
            goto60 = true;
            b_guard1 = true;
          } else {
            j = ilastm1;
            guard3 = false;
            exitg2 = false;
            while ((!exitg2) && (j + 1 >= ilo)) {
              if (j + 1 == ilo) {
                guard3 = true;
                exitg2 = true;
              } else {
                ctemp_tmp = j + 3 * (j - 1);
                if (std::abs(A[ctemp_tmp].re) + std::abs(A[ctemp_tmp].im) <=
                    b_atol) {
                  A[ctemp_tmp].re = 0.0F;
                  A[ctemp_tmp].im = 0.0F;
                  guard3 = true;
                  exitg2 = true;
                } else {
                  j--;
                  guard3 = false;
                }
              }
            }

            if (guard3) {
              ifirst = j + 1;
              goto70 = true;
            }

            if (goto70) {
              b_guard1 = true;
            } else {
              alpha1[0].re = rtNaNF;
              alpha1[0].im = 0.0F;
              beta1[0].re = rtNaNF;
              beta1[0].im = 0.0F;
              alpha1[1].re = rtNaNF;
              alpha1[1].im = 0.0F;
              beta1[1].re = rtNaNF;
              beta1[1].im = 0.0F;
              alpha1[2].re = rtNaNF;
              alpha1[2].im = 0.0F;
              beta1[2].re = rtNaNF;
              beta1[2].im = 0.0F;
              for (ctemp_tmp = 0; ctemp_tmp < 9; ctemp_tmp++) {
                Z[ctemp_tmp].re = rtNaNF;
                Z[ctemp_tmp].im = 0.0F;
              }

              *info = 1;
              exitg1 = 1;
            }
          }
        }

        if (b_guard1) {
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = A[ilast + 3 * ilast];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              firstNonZero = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0F;
              eshift_im = 0.0F;
              jiter++;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              if (iiter - iiter / 10 * 10 != 0) {
                jp1 = ilastm1 + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  shift.re = anorm / 0.577350259F;
                  shift.im = 0.0F;
                } else if (anorm == 0.0F) {
                  shift.re = 0.0F;
                  shift.im = reAij / 0.577350259F;
                } else {
                  shift.re = anorm / 0.577350259F;
                  shift.im = reAij / 0.577350259F;
                }

                jp1 = ilast + 3 * ilast;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  ad22_re = anorm / 0.577350259F;
                  ad22_im = 0.0F;
                } else if (anorm == 0.0F) {
                  ad22_re = 0.0F;
                  ad22_im = reAij / 0.577350259F;
                } else {
                  ad22_re = anorm / 0.577350259F;
                  ad22_im = reAij / 0.577350259F;
                }

                t1_re = 0.5F * (shift.re + ad22_re);
                t1_im = 0.5F * (shift.im + ad22_im);
                t1_im_tmp = t1_re * t1_im;
                jp1 = ilastm1 + 3 * ilast;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  imAij = anorm / 0.577350259F;
                  temp2 = 0.0F;
                } else if (anorm == 0.0F) {
                  imAij = 0.0F;
                  temp2 = reAij / 0.577350259F;
                } else {
                  imAij = anorm / 0.577350259F;
                  temp2 = reAij / 0.577350259F;
                }

                jp1 = ilast + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  sumsq = anorm / 0.577350259F;
                  anorm = 0.0F;
                } else if (anorm == 0.0F) {
                  sumsq = 0.0F;
                  anorm = reAij / 0.577350259F;
                } else {
                  sumsq = anorm / 0.577350259F;
                  anorm = reAij / 0.577350259F;
                }

                reAij = shift.re * ad22_re - shift.im * ad22_im;
                scale = shift.re * ad22_im + shift.im * ad22_re;
                shift.re = ((t1_re * t1_re - t1_im * t1_im) + (imAij * sumsq -
                  temp2 * anorm)) - reAij;
                shift.im = ((t1_im_tmp + t1_im_tmp) + (imAij * anorm + temp2 *
                  sumsq)) - scale;
                b_sqrt(&shift);
                if ((t1_re - ad22_re) * shift.re + (t1_im - ad22_im) * shift.im <=
                    0.0F) {
                  shift.re += t1_re;
                  shift.im += t1_im;
                } else {
                  shift.re = t1_re - shift.re;
                  shift.im = t1_im - shift.im;
                }
              } else {
                jp1 = ilast + 3 * ilastm1;
                anorm = ascale * A[jp1].re;
                reAij = ascale * A[jp1].im;
                if (reAij == 0.0F) {
                  imAij = anorm / 0.577350259F;
                  temp2 = 0.0F;
                } else if (anorm == 0.0F) {
                  imAij = 0.0F;
                  temp2 = reAij / 0.577350259F;
                } else {
                  imAij = anorm / 0.577350259F;
                  temp2 = reAij / 0.577350259F;
                }

                eshift_re += imAij;
                eshift_im += temp2;
                shift.re = eshift_re;
                shift.im = eshift_im;
              }

              j = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = j + 1;
                ctemp_tmp = j + 3 * j;
                ctemp.re = ascale * A[ctemp_tmp].re - shift.re * 0.577350259F;
                ctemp.im = ascale * A[ctemp_tmp].im - shift.im * 0.577350259F;
                anorm = std::abs(ctemp.re) + std::abs(ctemp.im);
                jp1 += 3 * j;
                temp2 = ascale * (std::abs(A[jp1].re) + std::abs(A[jp1].im));
                reAij = anorm;
                if (temp2 > anorm) {
                  reAij = temp2;
                }

                if ((reAij < 1.0F) && (reAij != 0.0F)) {
                  anorm /= reAij;
                  temp2 /= reAij;
                }

                ctemp_tmp = j + 3 * (j - 1);
                if ((std::abs(A[ctemp_tmp].re) + std::abs(A[ctemp_tmp].im)) *
                    temp2 <= anorm * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = j;
                  j--;
                }
              }

              if (!goto90) {
                istart = ifirst;
                ctemp_tmp = (ifirst + 3 * (ifirst - 1)) - 1;
                ctemp.re = ascale * A[ctemp_tmp].re - shift.re * 0.577350259F;
                ctemp.im = ascale * A[ctemp_tmp].im - shift.im * 0.577350259F;
              }

              goto90 = false;
              jp1 = istart + 3 * (istart - 1);
              b_ascale.re = ascale * A[jp1].re;
              b_ascale.im = ascale * A[jp1].im;
              b_xzlartg(ctemp, b_ascale, &anorm, &shift);
              j = istart;
              jp1 = istart - 2;
              while (j < ilast + 1) {
                if (j > istart) {
                  ctemp_tmp = j + 3 * jp1;
                  xzlartg(A[3 * jp1 + 1], A[ctemp_tmp], &anorm, &shift, &A[3 *
                          jp1 + 1]);
                  A[ctemp_tmp].re = 0.0F;
                  A[ctemp_tmp].im = 0.0F;
                }

                for (jp1 = j; jp1 < 4; jp1++) {
                  ctemp_tmp = j + 3 * (jp1 - 1);
                  ad22_re_tmp = ctemp_tmp - 1;
                  ad22_re = anorm * A[ad22_re_tmp].re + (shift.re * A[ctemp_tmp]
                    .re - shift.im * A[ctemp_tmp].im);
                  ad22_im = anorm * A[ad22_re_tmp].im + (shift.re * A[ctemp_tmp]
                    .im + shift.im * A[ctemp_tmp].re);
                  reAij = A[ad22_re_tmp].im;
                  scale = A[ad22_re_tmp].re;
                  A[ctemp_tmp].re = anorm * A[ctemp_tmp].re - (shift.re *
                    A[ad22_re_tmp].re + shift.im * A[ad22_re_tmp].im);
                  A[ctemp_tmp].im = anorm * A[ctemp_tmp].im - (shift.re * reAij
                    - shift.im * scale);
                  A[ad22_re_tmp].re = ad22_re;
                  A[ad22_re_tmp].im = ad22_im;
                }

                shift.re = -shift.re;
                shift.im = -shift.im;
                jp1 = j;
                if (ilast + 1 < j + 2) {
                  jp1 = ilast - 1;
                }

                for (i = 1; i <= jp1 + 2; i++) {
                  ctemp_tmp = (i + 3 * (j - 1)) - 1;
                  ad22_re_tmp = (i + 3 * j) - 1;
                  ad22_re = anorm * A[ad22_re_tmp].re + (shift.re * A[ctemp_tmp]
                    .re - shift.im * A[ctemp_tmp].im);
                  ad22_im = anorm * A[ad22_re_tmp].im + (shift.re * A[ctemp_tmp]
                    .im + shift.im * A[ctemp_tmp].re);
                  reAij = A[ad22_re_tmp].im;
                  scale = A[ad22_re_tmp].re;
                  A[ctemp_tmp].re = anorm * A[ctemp_tmp].re - (shift.re *
                    A[ad22_re_tmp].re + shift.im * A[ad22_re_tmp].im);
                  A[ctemp_tmp].im = anorm * A[ctemp_tmp].im - (shift.re * reAij
                    - shift.im * scale);
                  A[ad22_re_tmp].re = ad22_re;
                  A[ad22_re_tmp].im = ad22_im;
                }

                ctemp_tmp = 3 * (j - 1);
                ad22_re = anorm * Z[3 * j].re + (shift.re * Z[ctemp_tmp].re -
                  shift.im * Z[ctemp_tmp].im);
                ad22_im = anorm * Z[3 * j].im + (shift.re * Z[ctemp_tmp].im +
                  shift.im * Z[ctemp_tmp].re);
                reAij = Z[3 * j].im;
                scale = Z[3 * j].re;
                Z[ctemp_tmp].re = anorm * Z[ctemp_tmp].re - (shift.re * Z[3 * j]
                  .re + shift.im * Z[3 * j].im);
                Z[ctemp_tmp].im = anorm * Z[ctemp_tmp].im - (shift.re * reAij -
                  shift.im * scale);
                Z[3 * j].re = ad22_re;
                Z[3 * j].im = ad22_im;
                jp1 = ctemp_tmp + 1;
                ad22_re_tmp = 3 * j + 1;
                ad22_re = anorm * Z[ad22_re_tmp].re + (shift.re * Z[jp1].re -
                  shift.im * Z[jp1].im);
                ad22_im = anorm * Z[ad22_re_tmp].im + (shift.re * Z[jp1].im +
                  shift.im * Z[jp1].re);
                reAij = Z[ad22_re_tmp].im;
                scale = Z[ad22_re_tmp].re;
                Z[jp1].re = anorm * Z[jp1].re - (shift.re * Z[ad22_re_tmp].re +
                  shift.im * Z[ad22_re_tmp].im);
                Z[jp1].im = anorm * Z[jp1].im - (shift.re * reAij - shift.im *
                  scale);
                Z[ad22_re_tmp].re = ad22_re;
                Z[ad22_re_tmp].im = ad22_im;
                ctemp_tmp += 2;
                ad22_re_tmp = 3 * j + 2;
                ad22_re = anorm * Z[ad22_re_tmp].re + (shift.re * Z[ctemp_tmp].
                  re - shift.im * Z[ctemp_tmp].im);
                ad22_im = anorm * Z[ad22_re_tmp].im + (shift.re * Z[ctemp_tmp].
                  im + shift.im * Z[ctemp_tmp].re);
                reAij = Z[ad22_re_tmp].im;
                scale = Z[ad22_re_tmp].re;
                Z[ctemp_tmp].re = anorm * Z[ctemp_tmp].re - (shift.re *
                  Z[ad22_re_tmp].re + shift.im * Z[ad22_re_tmp].im);
                Z[ctemp_tmp].im = anorm * Z[ctemp_tmp].im - (shift.re * reAij -
                  shift.im * scale);
                Z[ad22_re_tmp].re = ad22_re;
                Z[ad22_re_tmp].im = ad22_im;
                jp1 = j - 1;
                j++;
              }
            }

            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (firstNonZero) {
      *info = ilast + 1;
      for (jp1 = 0; jp1 <= ilast; jp1++) {
        alpha1[jp1].re = rtNaNF;
        alpha1[jp1].im = 0.0F;
        beta1[jp1].re = rtNaNF;
        beta1[jp1].im = 0.0F;
      }

      for (ctemp_tmp = 0; ctemp_tmp < 9; ctemp_tmp++) {
        Z[ctemp_tmp].re = rtNaNF;
        Z[ctemp_tmp].im = 0.0F;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j <= ilo - 2; j++) {
      alpha1[j] = A[j + 3 * j];
    }
  }
}

/* End of code generation (xzhgeqz.cpp) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xztgevc.cpp
 *
 * Code generation for function 'xztgevc'
 *
 */

/* Include files */
#include "xztgevc.h"
#include "compute_eig.h"
#include "rt_nonfinite.h"
#include <cmath>

/* Function Definitions */
void xztgevc(const creal32_T A[9], creal32_T V[9])
{
  float rworka_idx_1;
  float rworka_idx_2;
  float anorm;
  int i;
  float d_re;
  float ascale;
  int je;
  int x_tmp_tmp_tmp;
  float temp;
  float salpha_re;
  float salpha_im;
  float acoeff;
  bool lscalea;
  float z;
  bool lscaleb;
  float scale;
  creal32_T work1[3];
  float dmin;
  int b_i;
  int V_re_tmp;
  int j;
  creal32_T work2[3];
  int b_j;
  float d_im;
  float brm;
  rworka_idx_1 = 0.0F;
  rworka_idx_2 = 0.0F;
  anorm = std::abs(A[0].re) + std::abs(A[0].im);
  for (i = 0; i < 1; i++) {
    rworka_idx_1 += std::abs(A[3].re) + std::abs(A[3].im);
  }

  d_re = rworka_idx_1 + (std::abs(A[4].re) + std::abs(A[4].im));
  if (d_re > anorm) {
    anorm = d_re;
  }

  for (i = 0; i < 2; i++) {
    rworka_idx_2 += std::abs(A[i + 6].re) + std::abs(A[i + 6].im);
  }

  d_re = rworka_idx_2 + (std::abs(A[8].re) + std::abs(A[8].im));
  if (d_re > anorm) {
    anorm = d_re;
  }

  rworka_idx_2 = anorm;
  if (1.17549435E-38F > anorm) {
    rworka_idx_2 = 1.17549435E-38F;
  }

  ascale = 1.0F / rworka_idx_2;
  for (je = 0; je < 3; je++) {
    x_tmp_tmp_tmp = 3 * (2 - je);
    i = (x_tmp_tmp_tmp - je) + 2;
    rworka_idx_2 = (std::abs(A[i].re) + std::abs(A[i].im)) * ascale;
    if (1.0F > rworka_idx_2) {
      rworka_idx_2 = 1.0F;
    }

    temp = 1.0F / rworka_idx_2;
    salpha_re = ascale * (temp * A[i].re);
    salpha_im = ascale * (temp * A[i].im);
    acoeff = temp * ascale;
    if ((temp >= 1.17549435E-38F) && (acoeff < 2.95822839E-31F)) {
      lscalea = true;
    } else {
      lscalea = false;
    }

    z = std::abs(salpha_re) + std::abs(salpha_im);
    if ((z >= 1.17549435E-38F) && (z < 2.95822839E-31F)) {
      lscaleb = true;
    } else {
      lscaleb = false;
    }

    scale = 1.0F;
    if (lscalea) {
      rworka_idx_2 = anorm;
      if (3.3804017E+30F < anorm) {
        rworka_idx_2 = 3.3804017E+30F;
      }

      scale = 2.95822839E-31F / temp * rworka_idx_2;
    }

    if (lscaleb) {
      d_re = 2.95822839E-31F / z;
      if (d_re > scale) {
        scale = d_re;
      }
    }

    if (lscalea || lscaleb) {
      rworka_idx_2 = acoeff;
      if (1.0F > acoeff) {
        rworka_idx_2 = 1.0F;
      }

      if (z > rworka_idx_2) {
        rworka_idx_2 = z;
      }

      d_re = 1.0F / (1.17549435E-38F * rworka_idx_2);
      if (d_re < scale) {
        scale = d_re;
      }

      if (lscalea) {
        acoeff = ascale * (scale * temp);
      } else {
        acoeff *= scale;
      }

      salpha_re *= scale;
      salpha_im *= scale;
    }

    work1[0].re = 0.0F;
    work1[0].im = 0.0F;
    work1[1].re = 0.0F;
    work1[1].im = 0.0F;
    work1[2].re = 0.0F;
    work1[2].im = 0.0F;
    work1[2 - je].re = 1.0F;
    work1[2 - je].im = 0.0F;
    d_re = 1.1920929E-7F * (std::abs(salpha_re) + std::abs(salpha_im));
    dmin = 1.1920929E-7F * acoeff * anorm;
    if (d_re > dmin) {
      dmin = d_re;
    }

    if (1.17549435E-38F > dmin) {
      dmin = 1.17549435E-38F;
    }

    b_i = 1 - je;
    for (i = 0; i <= b_i; i++) {
      V_re_tmp = i + x_tmp_tmp_tmp;
      work1[i].re = acoeff * A[V_re_tmp].re;
      work1[i].im = acoeff * A[V_re_tmp].im;
    }

    work1[2 - je].re = 1.0F;
    work1[2 - je].im = 0.0F;
    b_i = static_cast<int>((((-1.0 - ((-static_cast<double>(je) + 3.0) - 1.0)) +
      1.0) / -1.0));
    for (j = 0; j < b_i; j++) {
      b_j = 1 - (je + j);
      i = b_j + 3 * b_j;
      d_re = acoeff * A[i].re - salpha_re;
      d_im = acoeff * A[i].im - salpha_im;
      if (std::abs(d_re) + std::abs(d_im) <= dmin) {
        d_re = dmin;
        d_im = 0.0F;
      }

      brm = std::abs(d_re);
      scale = std::abs(d_im);
      rworka_idx_2 = brm + scale;
      if (rworka_idx_2 < 1.0F) {
        z = std::abs(work1[b_j].re) + std::abs(work1[b_j].im);
        if (z >= 2.83568648E+37F * rworka_idx_2) {
          temp = 1.0F / z;
          V_re_tmp = 2 - je;
          for (i = 0; i <= V_re_tmp; i++) {
            work1[i].re *= temp;
            work1[i].im *= temp;
          }
        }
      }

      if (d_im == 0.0F) {
        if (-work1[b_j].im == 0.0F) {
          scale = -work1[b_j].re / d_re;
          rworka_idx_2 = 0.0F;
        } else if (-work1[b_j].re == 0.0F) {
          scale = 0.0F;
          rworka_idx_2 = -work1[b_j].im / d_re;
        } else {
          scale = -work1[b_j].re / d_re;
          rworka_idx_2 = -work1[b_j].im / d_re;
        }
      } else if (d_re == 0.0F) {
        if (-work1[b_j].re == 0.0F) {
          scale = -work1[b_j].im / d_im;
          rworka_idx_2 = 0.0F;
        } else if (-work1[b_j].im == 0.0F) {
          scale = 0.0F;
          rworka_idx_2 = -(-work1[b_j].re / d_im);
        } else {
          scale = -work1[b_j].im / d_im;
          rworka_idx_2 = -(-work1[b_j].re / d_im);
        }
      } else if (brm > scale) {
        z = d_im / d_re;
        rworka_idx_2 = d_re + z * d_im;
        scale = (-work1[b_j].re + z * -work1[b_j].im) / rworka_idx_2;
        rworka_idx_2 = (-work1[b_j].im - z * -work1[b_j].re) / rworka_idx_2;
      } else if (scale == brm) {
        if (d_re > 0.0F) {
          z = 0.5F;
        } else {
          z = -0.5F;
        }

        if (d_im > 0.0F) {
          rworka_idx_2 = 0.5F;
        } else {
          rworka_idx_2 = -0.5F;
        }

        scale = (-work1[b_j].re * z + -work1[b_j].im * rworka_idx_2) / brm;
        rworka_idx_2 = (-work1[b_j].im * z - -work1[b_j].re * rworka_idx_2) /
          brm;
      } else {
        z = d_re / d_im;
        rworka_idx_2 = d_im + z * d_re;
        scale = (z * -work1[b_j].re + -work1[b_j].im) / rworka_idx_2;
        rworka_idx_2 = (z * -work1[b_j].im - (-work1[b_j].re)) / rworka_idx_2;
      }

      work1[b_j].re = scale;
      work1[b_j].im = rworka_idx_2;
      if (b_j + 1 > 1) {
        rworka_idx_2 = std::abs(work1[1].re) + std::abs(work1[1].im);
        if (rworka_idx_2 > 1.0F) {
          temp = 1.0F / rworka_idx_2;
          if (acoeff * rworka_idx_1 >= 2.83568648E+37F * temp) {
            V_re_tmp = 2 - je;
            for (i = 0; i <= V_re_tmp; i++) {
              work1[i].re *= temp;
              work1[i].im *= temp;
            }
          }
        }

        d_re = acoeff * work1[1].re;
        d_im = acoeff * work1[1].im;
        work1[0].re += d_re * A[3].re - d_im * A[3].im;
        work1[0].im += d_re * A[3].im + d_im * A[3].re;
      }
    }

    work2[0].re = 0.0F;
    work2[0].im = 0.0F;
    work2[1].re = 0.0F;
    work2[1].im = 0.0F;
    work2[2].re = 0.0F;
    work2[2].im = 0.0F;
    b_i = 2 - je;
    for (i = 0; i <= b_i; i++) {
      work2[0].re += V[3 * i].re * work1[i].re - V[3 * i].im * work1[i].im;
      work2[0].im += V[3 * i].re * work1[i].im + V[3 * i].im * work1[i].re;
      V_re_tmp = 3 * i + 1;
      work2[1].re += V[V_re_tmp].re * work1[i].re - V[V_re_tmp].im * work1[i].im;
      work2[1].im += V[V_re_tmp].re * work1[i].im + V[V_re_tmp].im * work1[i].re;
      V_re_tmp = 3 * i + 2;
      work2[2].re += V[V_re_tmp].re * work1[i].re - V[V_re_tmp].im * work1[i].im;
      work2[2].im += V[V_re_tmp].re * work1[i].im + V[V_re_tmp].im * work1[i].re;
    }

    rworka_idx_2 = std::abs(work2[0].re) + std::abs(work2[0].im);
    d_re = std::abs(work2[1].re) + std::abs(work2[1].im);
    if (d_re > rworka_idx_2) {
      rworka_idx_2 = d_re;
    }

    d_re = std::abs(work2[2].re) + std::abs(work2[2].im);
    if (d_re > rworka_idx_2) {
      rworka_idx_2 = d_re;
    }

    if (rworka_idx_2 > 1.17549435E-38F) {
      temp = 1.0F / rworka_idx_2;
      V[x_tmp_tmp_tmp].re = temp * work2[0].re;
      V[x_tmp_tmp_tmp].im = temp * work2[0].im;
      b_i = x_tmp_tmp_tmp + 1;
      V[b_i].re = temp * work2[1].re;
      V[b_i].im = temp * work2[1].im;
      b_i = x_tmp_tmp_tmp + 2;
      V[b_i].re = temp * work2[2].re;
      V[b_i].im = temp * work2[2].im;
    } else {
      V[x_tmp_tmp_tmp].re = 0.0F;
      V[x_tmp_tmp_tmp].im = 0.0F;
      b_i = x_tmp_tmp_tmp + 1;
      V[b_i].re = 0.0F;
      V[b_i].im = 0.0F;
      b_i = x_tmp_tmp_tmp + 2;
      V[b_i].re = 0.0F;
      V[b_i].im = 0.0F;
    }
  }
}

/* End of code generation (xztgevc.cpp) */

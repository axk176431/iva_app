/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_iva.cpp
 *
 * Code generation for function 'compute_iva'
 *
 */

/* Include files */
#include "compute_iva.h"
#include "compute_iva_data.h"
#include "compute_iva_initialize.h"
#include "compute_iva_rtwutil.h"
#include "fft.h"
#include "flip.h"
#include "ifft.h"
#include "init_iva.h"
#include "pinv.h"
#include "rt_nonfinite.h"
#include "svd.h"
#include <cmath>
#include <cstring>

/* Function Definitions */
void compute_iva(const float x[256], int source, float eta, float beta, float y
                 [128], creal32_T G[260], float xi[65])
{
  int xoffset;
  int i;
  int k;
  float y_new[128];
  creal32_T fcv[128];
  static const float w[128] = { 0.0F, 0.000602271874F, 0.00240763673F,
    0.00541174505F, 0.00960736F, 0.014984373F, 0.0215298329F, 0.0292279683F,
    0.038060233F, 0.0480053537F, 0.0590393692F, 0.0711356923F, 0.0842651948F,
    0.0983962342F, 0.113494776F, 0.12952444F, 0.146446615F, 0.164220527F,
    0.182803363F, 0.202150345F, 0.222214878F, 0.242948622F, 0.264301628F,
    0.286222458F, 0.308658272F, 0.331555068F, 0.354857653F, 0.378509909F,
    0.402454853F, 0.426634759F, 0.450991422F, 0.475466162F, 0.5F, 0.524533808F,
    0.549008548F, 0.573365211F, 0.597545147F, 0.621490061F, 0.645142317F,
    0.668444932F, 0.691341698F, 0.713777542F, 0.735698342F, 0.757051349F,
    0.777785122F, 0.797849655F, 0.817196667F, 0.835779488F, 0.853553414F,
    0.87047559F, 0.886505246F, 0.901603758F, 0.915734828F, 0.9288643F,
    0.940960646F, 0.951994658F, 0.961939752F, 0.970772F, 0.978470147F,
    0.985015631F, 0.990392625F, 0.994588256F, 0.99759239F, 0.999397755F, 1.0F,
    0.999397755F, 0.99759239F, 0.994588256F, 0.990392625F, 0.985015631F,
    0.978470147F, 0.970772F, 0.961939752F, 0.951994658F, 0.940960646F,
    0.9288643F, 0.915734828F, 0.901603758F, 0.886505246F, 0.87047559F,
    0.853553414F, 0.835779488F, 0.817196667F, 0.797849655F, 0.777785122F,
    0.757051349F, 0.735698342F, 0.713777542F, 0.691341698F, 0.668444932F,
    0.645142317F, 0.621490061F, 0.597545147F, 0.573365211F, 0.549008548F,
    0.524533808F, 0.5F, 0.475466162F, 0.450991422F, 0.426634759F, 0.402454853F,
    0.378509909F, 0.354857653F, 0.331555068F, 0.308658272F, 0.286222458F,
    0.264301628F, 0.242948622F, 0.222214878F, 0.202150345F, 0.182803363F,
    0.164220527F, 0.146446615F, 0.12952444F, 0.113494776F, 0.0983962342F,
    0.0842651948F, 0.0711356923F, 0.0590393692F, 0.0480053537F, 0.038060233F,
    0.0292279683F, 0.0215298329F, 0.014984373F, 0.00960736F, 0.00541174505F,
    0.00240763673F, 0.000602271874F };

  int xpageoffset;
  int G_re_tmp;
  creal32_T X[256];
  int b_G_re_tmp;
  float z;
  creal32_T S[130];
  float b_x[130];
  float temp_idx_0;
  float temp_idx_1;
  creal32_T temp2[4];
  float f;
  float f1;
  creal32_T R[260];
  creal32_T Y_new[128];
  float f2;
  float f3;
  float f4;
  creal32_T fcv1[63];
  int i1;
  if (isInitialized_compute_iva == false) {
    compute_iva_initialize();
  }

  /*     %% compute FFT */
  /*  use first and last signals only */
  for (xoffset = 0; xoffset < 2; xoffset++) {
    for (i = 0; i < 128; i++) {
      y_new[i] = w[i] * x[xoffset + (i << 1)];
    }

    fft(y_new, fcv);
    for (i = 0; i < 128; i++) {
      X[xoffset + (i << 1)] = fcv[i];
    }
  }

  /*     %% compute demixed signal using old demixing tensor */
  for (k = 0; k < 65; k++) {
    xpageoffset = k << 2;
    xoffset = k << 1;
    G_re_tmp = xpageoffset + 2;
    b_G_re_tmp = xoffset + 1;
    S[xoffset].re = (G[xpageoffset].re * X[xoffset].re - G[xpageoffset].im *
                     X[xoffset].im) + (G[G_re_tmp].re * X[b_G_re_tmp].re -
      G[G_re_tmp].im * X[b_G_re_tmp].im);
    S[xoffset].im = (G[xpageoffset].re * X[xoffset].im + G[xpageoffset].im *
                     X[xoffset].re) + (G[G_re_tmp].re * X[b_G_re_tmp].im +
      G[G_re_tmp].im * X[b_G_re_tmp].re);
    G_re_tmp = xpageoffset + 1;
    xpageoffset += 3;
    S[b_G_re_tmp].re = (G[G_re_tmp].re * X[xoffset].re - G[G_re_tmp].im *
                        X[xoffset].im) + (G[xpageoffset].re * X[b_G_re_tmp].re -
      G[xpageoffset].im * X[b_G_re_tmp].im);
    S[b_G_re_tmp].im = (G[G_re_tmp].re * X[xoffset].im + G[G_re_tmp].im *
                        X[xoffset].re) + (G[xpageoffset].re * X[b_G_re_tmp].im +
      G[xpageoffset].im * X[b_G_re_tmp].re);
  }

  /*     %% update gradient normalization factor xi */
  for (k = 0; k < 130; k++) {
    xoffset = k % 2 + ((k / 2) << 1);
    z = rt_hypotf_snf(X[xoffset].re, X[xoffset].im);
    b_x[k] = z * z;
  }

  for (xoffset = 0; xoffset < 65; xoffset++) {
    xpageoffset = xoffset << 1;
    xi[xoffset] = beta * xi[xoffset] + (1.0F - beta) * ((b_x[xpageoffset] +
      b_x[xpageoffset + 1]) / 2.0F);
  }

  /*     %% update natural gradient of G */
  /*  compute score */
  for (k = 0; k < 130; k++) {
    z = rt_hypotf_snf(S[k].re, S[k].im);
    b_x[k] = z * z;
  }

  temp_idx_0 = b_x[0];
  temp_idx_1 = b_x[1];
  for (k = 0; k < 64; k++) {
    xoffset = (k + 1) << 1;
    temp_idx_0 += b_x[xoffset];
    temp_idx_1 += b_x[xoffset + 1];
  }

  temp_idx_0 = std::sqrt(temp_idx_0);
  temp_idx_1 = std::sqrt(temp_idx_1);

  /*  compute score correlation */
  /*  compute gradient */
  temp2[0].re = -0.0F;
  temp2[0].im = -0.0F;
  temp2[3].re = -0.0F;
  temp2[3].im = -0.0F;
  for (k = 0; k < 65; k++) {
    xpageoffset = k << 1;
    if (S[xpageoffset].im == 0.0F) {
      z = S[xpageoffset].re;
      f = S[xpageoffset].re / (temp_idx_0 + 2.22044605E-16F);
      f1 = 0.0F;
    } else {
      z = S[xpageoffset].re;
      if (S[xpageoffset].re == 0.0F) {
        f = 0.0F;
        f1 = S[xpageoffset].im / (temp_idx_0 + 2.22044605E-16F);
      } else {
        f = S[xpageoffset].re / (temp_idx_0 + 2.22044605E-16F);
        f1 = S[xpageoffset].im / (temp_idx_0 + 2.22044605E-16F);
      }
    }

    xoffset = xpageoffset + 1;
    if (S[xoffset].im == 0.0F) {
      f2 = S[xoffset].re;
      f3 = S[xoffset].re / (temp_idx_1 + 2.22044605E-16F);
      f4 = 0.0F;
    } else {
      f2 = S[xoffset].re;
      if (S[xoffset].re == 0.0F) {
        f3 = 0.0F;
        f4 = S[xoffset].im / (temp_idx_1 + 2.22044605E-16F);
      } else {
        f3 = S[xoffset].re / (temp_idx_1 + 2.22044605E-16F);
        f4 = S[xoffset].im / (temp_idx_1 + 2.22044605E-16F);
      }
    }

    i = k << 2;
    b_G_re_tmp = i + 3;
    i1 = i + 1;
    temp2[1].re = -(f3 * z - f4 * -S[xpageoffset].im);
    temp2[1].im = -(f3 * -S[xpageoffset].im + f4 * z);
    G_re_tmp = i + 2;
    temp2[2].re = -(f * f2 - f1 * -S[xoffset].im);
    temp2[2].im = -(f * -S[xoffset].im + f1 * f2);
    for (xpageoffset = 0; xpageoffset < 2; xpageoffset++) {
      xoffset = xpageoffset + i;
      z = temp2[xpageoffset + 2].re;
      f = temp2[xpageoffset + 2].im;
      R[xoffset].re = (temp2[xpageoffset].re * G[i].re - temp2[xpageoffset].im *
                       G[i].im) + (z * G[i1].re - f * G[i1].im);
      R[xoffset].im = (temp2[xpageoffset].re * G[i].im + temp2[xpageoffset].im *
                       G[i].re) + (z * G[i1].im + f * G[i1].re);
      xoffset += 2;
      R[xoffset].re = (temp2[xpageoffset].re * G[G_re_tmp].re -
                       temp2[xpageoffset].im * G[G_re_tmp].im) + (z *
        G[b_G_re_tmp].re - f * G[b_G_re_tmp].im);
      R[xoffset].im = (temp2[xpageoffset].re * G[G_re_tmp].im +
                       temp2[xpageoffset].im * G[G_re_tmp].re) + (z *
        G[b_G_re_tmp].im + f * G[b_G_re_tmp].re);
    }
  }

  /*  update */
  for (k = 0; k < 65; k++) {
    z = eta / std::sqrt(xi[k] + 2.22044605E-16F);
    i = k << 2;
    G[i].re += z * R[i].re;
    G[i].im += z * R[i].im;
    b_G_re_tmp = i + 1;
    G[b_G_re_tmp].re += z * R[b_G_re_tmp].re;
    G[b_G_re_tmp].im += z * R[b_G_re_tmp].im;
    b_G_re_tmp = i + 2;
    G[b_G_re_tmp].re += z * R[b_G_re_tmp].re;
    G[b_G_re_tmp].im += z * R[b_G_re_tmp].im;
    i += 3;
    G[i].re += z * R[i].re;
    G[i].im += z * R[i].im;
  }

  /*     %% apply minimum distortion scaling to demixing tensor G */
  for (k = 0; k < 65; k++) {
    pinv(*(creal32_T (*)[4])&G[k << 2], temp2);
    i = k << 2;
    R[i].re = temp2[0].re * G[i].re - temp2[0].im * G[i].im;
    R[i].im = temp2[0].re * G[i].im + temp2[0].im * G[i].re;
    b_G_re_tmp = i + 2;
    R[b_G_re_tmp].re = temp2[0].re * G[b_G_re_tmp].re - temp2[0].im *
      G[b_G_re_tmp].im;
    R[b_G_re_tmp].im = temp2[0].re * G[b_G_re_tmp].im + temp2[0].im *
      G[b_G_re_tmp].re;
    b_G_re_tmp = i + 1;
    R[b_G_re_tmp].re = temp2[3].re * G[b_G_re_tmp].re - temp2[3].im *
      G[b_G_re_tmp].im;
    R[b_G_re_tmp].im = temp2[3].re * G[b_G_re_tmp].im + temp2[3].im *
      G[b_G_re_tmp].re;
    i += 3;
    R[i].re = temp2[3].re * G[i].re - temp2[3].im * G[i].im;
    R[i].im = temp2[3].re * G[i].im + temp2[3].im * G[i].re;
  }

  /*     %% demix selected source using updated tensor and reconstruct all  */
  /*  frequency bins */
  std::memset(&Y_new[0], 0, 128U * sizeof(creal32_T));
  for (k = 0; k < 65; k++) {
    xpageoffset = source + (k << 2);
    G_re_tmp = xpageoffset - 1;
    b_G_re_tmp = k << 1;
    xpageoffset++;
    xoffset = b_G_re_tmp + 1;
    Y_new[k].re = (R[G_re_tmp].re * X[b_G_re_tmp].re - R[G_re_tmp].im *
                   X[b_G_re_tmp].im) + (R[xpageoffset].re * X[xoffset].re -
      R[xpageoffset].im * X[xoffset].im);
    Y_new[k].im = (R[G_re_tmp].re * X[b_G_re_tmp].im + R[G_re_tmp].im *
                   X[b_G_re_tmp].re) + (R[xpageoffset].re * X[xoffset].im +
      R[xpageoffset].im * X[xoffset].re);
  }

  std::memcpy(&fcv1[0], &Y_new[1], 63U * sizeof(creal32_T));
  flip(fcv1);
  for (i = 0; i < 63; i++) {
    Y_new[i + 65].re = fcv1[i].re;
    Y_new[i + 65].im = -fcv1[i].im;
  }

  /*     %% IFFT and overlap add */
  ifft(Y_new, fcv);
  for (i = 0; i < 128; i++) {
    y_new[i] = fcv[i].re;
  }

  for (i = 0; i < 64; i++) {
    y_new[i] += y[i + 64];
  }

  std::memcpy(&y[0], &y_new[0], 128U * sizeof(float));
}

/* End of code generation (compute_iva.cpp) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xhseqr.cpp
 *
 * Code generation for function 'xhseqr'
 *
 */

/* Include files */
#include "xhseqr.h"
#include "compute_eig.h"
#include "compute_eig_rtwutil.h"
#include "recip.h"
#include "rt_nonfinite.h"
#include "sqrt.h"
#include "xdlapy3.h"
#include <cmath>

/* Function Definitions */
int xhseqr(creal32_T h[9], creal32_T z[9])
{
  int info;
  float tst;
  float htmp2;
  float br;
  int i;
  bool exitg1;
  creal32_T sc;
  int L;
  bool goto140;
  int its;
  float re;
  bool exitg2;
  float im;
  int k;
  bool exitg3;
  int sc_tmp;
  float ba;
  int tst_tmp_tmp;
  int t_re_tmp;
  float bb;
  float t_re;
  int knt;
  float ab;
  creal32_T v;
  bool goto70;
  int m;
  int htmp2_tmp;
  float u_re;
  float u_im;
  float s;
  int b_k;
  creal32_T b_v[2];
  info = 0;
  h[2].re = 0.0F;
  h[2].im = 0.0F;
  if (h[1].im != 0.0F) {
    tst = h[1].re;
    htmp2 = h[1].im;
    br = std::abs(h[1].re) + std::abs(h[1].im);
    if (htmp2 == 0.0F) {
      sc.re = tst / br;
      sc.im = 0.0F;
    } else if (tst == 0.0F) {
      sc.re = 0.0F;
      sc.im = htmp2 / br;
    } else {
      sc.re = tst / br;
      sc.im = htmp2 / br;
    }

    br = rt_hypotf_snf(sc.re, sc.im);
    if (-sc.im == 0.0F) {
      re = sc.re / br;
      im = 0.0F;
    } else if (sc.re == 0.0F) {
      re = 0.0F;
      im = -sc.im / br;
    } else {
      re = sc.re / br;
      im = -sc.im / br;
    }

    h[1].re = rt_hypotf_snf(h[1].re, h[1].im);
    h[1].im = 0.0F;
    for (k = 5; k <= 8; k += 3) {
      htmp2 = re * h[k - 1].im + im * h[k - 1].re;
      h[k - 1].re = re * h[k - 1].re - im * h[k - 1].im;
      h[k - 1].im = htmp2;
    }

    for (k = 4; k < 7; k++) {
      htmp2 = re * h[k - 1].im + -im * h[k - 1].re;
      h[k - 1].re = re * h[k - 1].re - -im * h[k - 1].im;
      h[k - 1].im = htmp2;
      htmp2 = re * z[k - 1].im + -im * z[k - 1].re;
      z[k - 1].re = re * z[k - 1].re - -im * z[k - 1].im;
      z[k - 1].im = htmp2;
    }
  }

  if (h[5].im != 0.0F) {
    tst = h[5].re;
    htmp2 = h[5].im;
    br = std::abs(h[5].re) + std::abs(h[5].im);
    if (htmp2 == 0.0F) {
      sc.re = tst / br;
      sc.im = 0.0F;
    } else if (tst == 0.0F) {
      sc.re = 0.0F;
      sc.im = htmp2 / br;
    } else {
      sc.re = tst / br;
      sc.im = htmp2 / br;
    }

    br = rt_hypotf_snf(sc.re, sc.im);
    if (-sc.im == 0.0F) {
      re = sc.re / br;
      im = 0.0F;
    } else if (sc.re == 0.0F) {
      re = 0.0F;
      im = -sc.im / br;
    } else {
      re = sc.re / br;
      im = -sc.im / br;
    }

    h[5].re = rt_hypotf_snf(h[5].re, h[5].im);
    h[5].im = 0.0F;
    for (k = 9; k <= 9; k += 3) {
      htmp2 = re * h[8].im + im * h[8].re;
      h[8].re = re * h[8].re - im * h[8].im;
      h[8].im = htmp2;
    }

    for (k = 7; k < 10; k++) {
      htmp2 = re * h[k - 1].im + -im * h[k - 1].re;
      h[k - 1].re = re * h[k - 1].re - -im * h[k - 1].im;
      h[k - 1].im = htmp2;
      htmp2 = re * z[k - 1].im + -im * z[k - 1].re;
      z[k - 1].re = re * z[k - 1].re - -im * z[k - 1].im;
      z[k - 1].im = htmp2;
    }
  }

  i = 2;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = -1;
    goto140 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 301)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > L + 2)) {
        sc_tmp = k + 3 * (k - 1);
        htmp2 = std::abs(h[sc_tmp].re);
        ba = htmp2 + std::abs(h[sc_tmp].im);
        if (ba <= 2.95822839E-31F) {
          exitg3 = true;
        } else {
          tst_tmp_tmp = k + 3 * k;
          bb = std::abs(h[tst_tmp_tmp].re) + std::abs(h[tst_tmp_tmp].im);
          knt = sc_tmp - 1;
          tst = (std::abs(h[knt].re) + std::abs(h[knt].im)) + bb;
          if (tst == 0.0F) {
            if (k - 1 >= 1) {
              tst = std::abs(h[(k + 3 * (k - 2)) - 1].re);
            }

            if (k + 2 <= 3) {
              tst += std::abs(h[tst_tmp_tmp + 1].re);
            }
          }

          if (htmp2 <= 1.1920929E-7F * tst) {
            htmp2_tmp = tst_tmp_tmp - 1;
            htmp2 = std::abs(h[htmp2_tmp].re) + std::abs(h[htmp2_tmp].im);
            if (ba > htmp2) {
              ab = ba;
              ba = htmp2;
            } else {
              ab = htmp2;
            }

            htmp2 = std::abs(h[knt].re - h[tst_tmp_tmp].re) + std::abs(h[knt].im
              - h[tst_tmp_tmp].im);
            if (bb > htmp2) {
              tst = bb;
              bb = htmp2;
            } else {
              tst = htmp2;
            }

            s = tst + ab;
            htmp2 = 1.1920929E-7F * (bb * (tst / s));
            if ((2.95822839E-31F > htmp2) || rtIsNaNF(htmp2)) {
              htmp2 = 2.95822839E-31F;
            }

            if (ba * (ab / s) <= htmp2) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }

      L = k - 1;
      if (k + 1 > 1) {
        sc_tmp = k + 3 * (k - 1);
        h[sc_tmp].re = 0.0F;
        h[sc_tmp].im = 0.0F;
      }

      if (k + 1 >= i + 1) {
        goto140 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          t_re_tmp = k + 3 * k;
          t_re = 0.75F * std::abs(h[(k + 3 * k) + 1].re) + h[t_re_tmp].re;
          ab = h[t_re_tmp].im;
        } else if (its == 20) {
          t_re_tmp = i + 3 * i;
          t_re = 0.75F * std::abs(h[i + 3 * (i - 1)].re) + h[t_re_tmp].re;
          ab = h[t_re_tmp].im;
        } else {
          t_re_tmp = i + 3 * i;
          t_re = h[t_re_tmp].re;
          ab = h[t_re_tmp].im;
          v = h[t_re_tmp - 1];
          b_sqrt(&v);
          sc_tmp = i + 3 * (i - 1);
          sc = h[sc_tmp];
          b_sqrt(&sc);
          u_re = v.re * sc.re - v.im * sc.im;
          u_im = v.re * sc.im + v.im * sc.re;
          s = std::abs(u_re) + std::abs(u_im);
          if (s != 0.0F) {
            knt = sc_tmp - 1;
            ba = 0.5F * (h[knt].re - h[t_re_tmp].re);
            im = 0.5F * (h[knt].im - h[t_re_tmp].im);
            bb = std::abs(ba) + std::abs(im);
            if ((!(s > bb)) && (!rtIsNaNF(bb))) {
              s = bb;
            }

            if (im == 0.0F) {
              t_re = ba / s;
              ab = 0.0F;
            } else if (ba == 0.0F) {
              t_re = 0.0F;
              ab = im / s;
            } else {
              t_re = ba / s;
              ab = im / s;
            }

            re = t_re * t_re - ab * ab;
            tst = t_re * ab;
            if (u_im == 0.0F) {
              sc.re = u_re / s;
              sc.im = 0.0F;
            } else if (u_re == 0.0F) {
              sc.re = 0.0F;
              sc.im = u_im / s;
            } else {
              sc.re = u_re / s;
              sc.im = u_im / s;
            }

            htmp2 = sc.re * sc.re - sc.im * sc.im;
            ab = sc.re * sc.im;
            v.re = re + htmp2;
            v.im = (tst + tst) + (ab + ab);
            b_sqrt(&v);
            sc.re = s * v.re;
            sc.im = s * v.im;
            if (bb > 0.0F) {
              if (im == 0.0F) {
                t_re = ba / bb;
                ab = 0.0F;
              } else if (ba == 0.0F) {
                t_re = 0.0F;
                ab = im / bb;
              } else {
                t_re = ba / bb;
                ab = im / bb;
              }

              if (t_re * sc.re + ab * sc.im < 0.0F) {
                sc.re = -sc.re;
                sc.im = -sc.im;
              }
            }

            br = ba + sc.re;
            ab = im + sc.im;
            if (ab == 0.0F) {
              if (u_im == 0.0F) {
                ba = u_re / br;
                tst = 0.0F;
              } else if (u_re == 0.0F) {
                ba = 0.0F;
                tst = u_im / br;
              } else {
                ba = u_re / br;
                tst = u_im / br;
              }
            } else if (br == 0.0F) {
              if (u_re == 0.0F) {
                ba = u_im / ab;
                tst = 0.0F;
              } else if (u_im == 0.0F) {
                ba = 0.0F;
                tst = -(u_re / ab);
              } else {
                ba = u_im / ab;
                tst = -(u_re / ab);
              }
            } else {
              bb = std::abs(br);
              tst = std::abs(ab);
              if (bb > tst) {
                s = ab / br;
                tst = br + s * ab;
                ba = (u_re + s * u_im) / tst;
                tst = (u_im - s * u_re) / tst;
              } else if (tst == bb) {
                if (br > 0.0F) {
                  htmp2 = 0.5F;
                } else {
                  htmp2 = -0.5F;
                }

                if (ab > 0.0F) {
                  tst = 0.5F;
                } else {
                  tst = -0.5F;
                }

                ba = (u_re * htmp2 + u_im * tst) / bb;
                tst = (u_im * htmp2 - u_re * tst) / bb;
              } else {
                s = br / ab;
                tst = ab + s * br;
                ba = (s * u_re + u_im) / tst;
                tst = (s * u_im - u_re) / tst;
              }
            }

            t_re = h[t_re_tmp].re - (u_re * ba - u_im * tst);
            ab = h[t_re_tmp].im - (u_re * tst + u_im * ba);
          }
        }

        goto70 = false;
        m = i;
        exitg3 = false;
        while ((!exitg3) && (m > k + 1)) {
          sc.re = h[4].re - t_re;
          sc.im = h[4].im - ab;
          tst = h[5].re;
          s = (std::abs(sc.re) + std::abs(sc.im)) + std::abs(tst);
          if (sc.im == 0.0F) {
            re = sc.re / s;
            im = 0.0F;
          } else if (sc.re == 0.0F) {
            re = 0.0F;
            im = sc.im / s;
          } else {
            re = sc.re / s;
            im = sc.im / s;
          }

          sc.re = re;
          sc.im = im;
          tst /= s;
          b_v[0] = sc;
          b_v[1].re = tst;
          b_v[1].im = 0.0F;
          if (std::abs(h[1].re) * std::abs(tst) <= 1.1920929E-7F * ((std::abs(re)
                + std::abs(im)) * ((std::abs(h[4].re) + std::abs(h[4].im)) +
                (std::abs(h[8].re) + std::abs(h[8].im))))) {
            goto70 = true;
            exitg3 = true;
          } else {
            m = 1;
          }
        }

        if (!goto70) {
          sc_tmp = k + 3 * k;
          sc.re = h[sc_tmp].re - t_re;
          sc.im = h[sc_tmp].im - ab;
          tst = h[(k + 3 * k) + 1].re;
          s = (std::abs(sc.re) + std::abs(sc.im)) + std::abs(tst);
          if (sc.im == 0.0F) {
            b_v[0].re = sc.re / s;
            b_v[0].im = 0.0F;
          } else if (sc.re == 0.0F) {
            b_v[0].re = 0.0F;
            b_v[0].im = sc.im / s;
          } else {
            b_v[0].re = sc.re / s;
            b_v[0].im = sc.im / s;
          }

          tst /= s;
          b_v[1].re = tst;
          b_v[1].im = 0.0F;
        }

        for (b_k = m; b_k <= i; b_k++) {
          if (b_k > m) {
            b_v[0] = h[1];
            b_v[1] = h[2];
          }

          ba = b_v[1].re;
          im = b_v[1].im;
          sc = b_v[0];
          t_re = 0.0F;
          ab = 0.0F;
          tst = rt_hypotf_snf(b_v[1].re, b_v[1].im);
          if ((tst != 0.0F) || (b_v[0].im != 0.0F)) {
            htmp2 = xdlapy3(b_v[0].re, b_v[0].im, tst);
            if (b_v[0].re >= 0.0F) {
              htmp2 = -htmp2;
            }

            if (std::abs(htmp2) < 9.86076132E-32F) {
              knt = -1;
              do {
                knt++;
                ba *= 1.01412048E+31F;
                im *= 1.01412048E+31F;
                htmp2 *= 1.01412048E+31F;
                sc.re *= 1.01412048E+31F;
                sc.im *= 1.01412048E+31F;
              } while (!(std::abs(htmp2) >= 9.86076132E-32F));

              htmp2 = xdlapy3(sc.re, sc.im, rt_hypotf_snf(ba, im));
              if (sc.re >= 0.0F) {
                htmp2 = -htmp2;
              }

              tst = htmp2 - sc.re;
              if (0.0F - sc.im == 0.0F) {
                t_re = tst / htmp2;
                ab = 0.0F;
              } else if (tst == 0.0F) {
                t_re = 0.0F;
                ab = (0.0F - sc.im) / htmp2;
              } else {
                t_re = tst / htmp2;
                ab = (0.0F - sc.im) / htmp2;
              }

              v.re = sc.re - htmp2;
              v.im = sc.im;
              sc = recip(v);
              re = sc.re * ba - sc.im * im;
              im = sc.re * im + sc.im * ba;
              ba = re;
              for (htmp2_tmp = 0; htmp2_tmp <= knt; htmp2_tmp++) {
                htmp2 *= 9.86076132E-32F;
              }

              sc.re = htmp2;
              sc.im = 0.0F;
            } else {
              tst = htmp2 - b_v[0].re;
              if (0.0F - b_v[0].im == 0.0F) {
                t_re = tst / htmp2;
                ab = 0.0F;
              } else if (tst == 0.0F) {
                t_re = 0.0F;
                ab = (0.0F - b_v[0].im) / htmp2;
              } else {
                t_re = tst / htmp2;
                ab = (0.0F - b_v[0].im) / htmp2;
              }

              v.re = b_v[0].re - htmp2;
              v.im = b_v[0].im;
              v = recip(v);
              ba = v.re * b_v[1].re - v.im * b_v[1].im;
              im = v.re * b_v[1].im + v.im * b_v[1].re;
              sc.re = htmp2;
              sc.im = 0.0F;
            }
          }

          b_v[0] = sc;
          b_v[1].re = ba;
          b_v[1].im = im;
          if (b_k > m) {
            h[1] = sc;
            h[2].re = 0.0F;
            h[2].im = 0.0F;
          }

          tst = t_re * ba - ab * im;
          for (tst_tmp_tmp = b_k; tst_tmp_tmp < 4; tst_tmp_tmp++) {
            htmp2_tmp = b_k + 3 * (tst_tmp_tmp - 1);
            t_re_tmp = htmp2_tmp - 1;
            sc.re = (t_re * h[t_re_tmp].re - -ab * h[t_re_tmp].im) + tst *
              h[htmp2_tmp].re;
            sc.im = (t_re * h[t_re_tmp].im + -ab * h[t_re_tmp].re) + tst *
              h[htmp2_tmp].im;
            h[t_re_tmp].re -= sc.re;
            h[t_re_tmp].im -= sc.im;
            h[htmp2_tmp].re -= sc.re * ba - sc.im * im;
            h[htmp2_tmp].im -= sc.re * im + sc.im * ba;
          }

          for (tst_tmp_tmp = 0; tst_tmp_tmp <= i; tst_tmp_tmp++) {
            t_re_tmp = tst_tmp_tmp + 3 * (b_k - 1);
            sc_tmp = tst_tmp_tmp + 3 * b_k;
            sc.re = (t_re * h[t_re_tmp].re - ab * h[t_re_tmp].im) + tst *
              h[sc_tmp].re;
            sc.im = (t_re * h[t_re_tmp].im + ab * h[t_re_tmp].re) + tst *
              h[sc_tmp].im;
            h[t_re_tmp].re -= sc.re;
            h[t_re_tmp].im -= sc.im;
            h[sc_tmp].re -= sc.re * ba - sc.im * -im;
            h[sc_tmp].im -= sc.re * -im + sc.im * ba;
          }

          t_re_tmp = 3 * (b_k - 1);
          sc.re = (t_re * z[t_re_tmp].re - ab * z[t_re_tmp].im) + tst * z[3 *
            b_k].re;
          sc.im = (t_re * z[t_re_tmp].im + ab * z[t_re_tmp].re) + tst * z[3 *
            b_k].im;
          z[t_re_tmp].re -= sc.re;
          z[t_re_tmp].im -= sc.im;
          z[3 * b_k].re -= sc.re * ba - sc.im * -im;
          z[3 * b_k].im -= sc.re * -im + sc.im * ba;
          htmp2_tmp = t_re_tmp + 1;
          sc_tmp = 3 * b_k + 1;
          sc.re = (t_re * z[htmp2_tmp].re - ab * z[htmp2_tmp].im) + tst *
            z[sc_tmp].re;
          sc.im = (t_re * z[htmp2_tmp].im + ab * z[htmp2_tmp].re) + tst *
            z[sc_tmp].im;
          z[htmp2_tmp].re -= sc.re;
          z[htmp2_tmp].im -= sc.im;
          z[sc_tmp].re -= sc.re * ba - sc.im * -im;
          z[sc_tmp].im -= sc.re * -im + sc.im * ba;
          t_re_tmp += 2;
          sc_tmp = 3 * b_k + 2;
          sc.re = (t_re * z[t_re_tmp].re - ab * z[t_re_tmp].im) + tst * z[sc_tmp]
            .re;
          sc.im = (t_re * z[t_re_tmp].im + ab * z[t_re_tmp].re) + tst * z[sc_tmp]
            .im;
          z[t_re_tmp].re -= sc.re;
          z[t_re_tmp].im -= sc.im;
          z[sc_tmp].re -= sc.re * ba - sc.im * -im;
          z[sc_tmp].im -= sc.re * -im + sc.im * ba;
          if ((b_k == m) && (m > k + 1)) {
            br = rt_hypotf_snf(1.0F - t_re, 0.0F - ab);
            if (0.0F - ab == 0.0F) {
              re = (1.0F - t_re) / br;
              im = 0.0F;
            } else if (1.0F - t_re == 0.0F) {
              re = 0.0F;
              im = (0.0F - ab) / br;
            } else {
              re = (1.0F - t_re) / br;
              im = (0.0F - ab) / br;
            }

            htmp2 = h[5].re * -im + h[5].im * re;
            h[5].re = h[5].re * re - h[5].im * -im;
            h[5].im = htmp2;
            for (tst_tmp_tmp = 2; tst_tmp_tmp <= i + 1; tst_tmp_tmp++) {
              if (tst_tmp_tmp != 3) {
                htmp2 = re * h[7].im + im * h[7].re;
                h[7].re = re * h[7].re - im * h[7].im;
                h[7].im = htmp2;
                htmp2 = re * h[3].im + -im * h[3].re;
                h[3].re = re * h[3].re - -im * h[3].im;
                h[3].im = htmp2;
                htmp2 = re * z[3].im + -im * z[3].re;
                z[3].re = re * z[3].re - -im * z[3].im;
                z[3].im = htmp2;
                htmp2 = re * z[4].im + -im * z[4].re;
                z[4].re = re * z[4].re - -im * z[4].im;
                z[4].im = htmp2;
                htmp2 = re * z[5].im + -im * z[5].re;
                z[5].re = re * z[5].re - -im * z[5].im;
                z[5].im = htmp2;
              }
            }
          }
        }

        sc_tmp = i + 3 * (i - 1);
        sc = h[sc_tmp];
        if (h[sc_tmp].im != 0.0F) {
          htmp2 = rt_hypotf_snf(h[sc_tmp].re, h[sc_tmp].im);
          h[sc_tmp].re = htmp2;
          h[sc_tmp].im = 0.0F;
          if (sc.im == 0.0F) {
            re = sc.re / htmp2;
            im = 0.0F;
          } else if (sc.re == 0.0F) {
            re = 0.0F;
            im = sc.im / htmp2;
          } else {
            re = sc.re / htmp2;
            im = sc.im / htmp2;
          }

          if (3 > i + 1) {
            htmp2 = re * h[7].im + -im * h[7].re;
            h[7].re = re * h[7].re - -im * h[7].im;
            h[7].im = htmp2;
          }

          knt = i * 3;
          htmp2_tmp = i * 3 + 1;
          sc_tmp = knt + i;
          for (k = htmp2_tmp; k <= sc_tmp; k++) {
            htmp2 = re * h[k - 1].im + im * h[k - 1].re;
            h[k - 1].re = re * h[k - 1].re - im * h[k - 1].im;
            h[k - 1].im = htmp2;
          }

          sc_tmp = knt + 3;
          for (k = htmp2_tmp; k <= sc_tmp; k++) {
            htmp2 = re * z[k - 1].im + im * z[k - 1].re;
            z[k - 1].re = re * z[k - 1].re - im * z[k - 1].im;
            z[k - 1].im = htmp2;
          }
        }

        its++;
      }
    }

    if (!goto140) {
      info = i + 1;
      exitg1 = true;
    } else {
      i = L;
    }
  }

  return info;
}

/* End of code generation (xhseqr.cpp) */

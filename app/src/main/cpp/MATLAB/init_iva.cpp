/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * init_iva.cpp
 *
 * Code generation for function 'init_iva'
 *
 */

/* Include files */
#include "init_iva.h"
#include "compute_iva.h"
#include "compute_iva_data.h"
#include "compute_iva_initialize.h"
#include "rt_nonfinite.h"
#include <cstring>

/* Function Definitions */
void init_iva(float y[128], creal32_T G[260], float xi[65])
{
  int k;
  int i;
  int i1;
  if (isInitialized_compute_iva == false) {
    compute_iva_initialize();
  }

  /*  init output signal y */
  std::memset(&y[0], 0, 128U * sizeof(float));

  /*  init demixing tensor G */
  /*  init gradient normalization factor xi */
  for (k = 0; k < 65; k++) {
    i = k << 2;
    G[i].re = 1.0F;
    G[i].im = 0.0F;
    i1 = i + 1;
    G[i1].re = 0.0F;
    G[i1].im = 0.0F;
    i1 = i + 2;
    G[i1].re = 0.0F;
    G[i1].im = 0.0F;
    i += 3;
    G[i].re = 1.0F;
    G[i].im = 0.0F;
    xi[k] = 1.0F;
  }
}

/* End of code generation (init_iva.cpp) */

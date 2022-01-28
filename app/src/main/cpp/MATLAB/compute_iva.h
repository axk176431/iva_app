/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_iva.h
 *
 * Code generation for function 'compute_iva'
 *
 */

#ifndef COMPUTE_IVA_H
#define COMPUTE_IVA_H

/* Include files */
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "compute_iva_types.h"

/* Function Declarations */
extern void compute_iva(const float x[256], int source, float eta, float beta,
  float y[128], creal32_T G[260], float xi[65]);

#endif

/* End of code generation (compute_iva.h) */

/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xgerc.h
 *
 * Code generation for function 'xgerc'
 *
 */

#ifndef XGERC_H
#define XGERC_H

/* Include files */
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "compute_eig_types.h"

/* Function Declarations */
extern void xgerc(int m, int n, const creal32_T alpha1, int ix0, const creal32_T
                  y[3], creal32_T A[9], int ia0);

#endif

/* End of code generation (xgerc.h) */

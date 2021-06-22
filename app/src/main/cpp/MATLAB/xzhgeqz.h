/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * xzhgeqz.h
 *
 * Code generation for function 'xzhgeqz'
 *
 */

#ifndef XZHGEQZ_H
#define XZHGEQZ_H

/* Include files */
#include <cstddef>
#include <cstdlib>
#include "rtwtypes.h"
#include "compute_eig_types.h"

/* Function Declarations */
extern void xzhgeqz(creal32_T A[9], int ilo, int ihi, creal32_T Z[9], int *info,
                    creal32_T alpha1[3], creal32_T beta1[3]);

#endif

/* End of code generation (xzhgeqz.h) */

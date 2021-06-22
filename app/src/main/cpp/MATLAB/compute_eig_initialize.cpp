/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_eig_initialize.cpp
 *
 * Code generation for function 'compute_eig_initialize'
 *
 */

/* Include files */
#include "compute_eig_initialize.h"
#include "compute_eig.h"
#include "compute_eig_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void compute_eig_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_compute_eig = true;
}

/* End of code generation (compute_eig_initialize.cpp) */

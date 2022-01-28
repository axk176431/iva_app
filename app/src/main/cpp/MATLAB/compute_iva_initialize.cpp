/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_iva_initialize.cpp
 *
 * Code generation for function 'compute_iva_initialize'
 *
 */

/* Include files */
#include "compute_iva_initialize.h"
#include "compute_iva.h"
#include "compute_iva_data.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Function Definitions */
void compute_iva_initialize()
{
  rt_InitInfAndNaN();
  isInitialized_compute_iva = true;
}

/* End of code generation (compute_iva_initialize.cpp) */

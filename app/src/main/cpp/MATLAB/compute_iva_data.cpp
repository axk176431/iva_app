/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * compute_iva_data.cpp
 *
 * Code generation for function 'compute_iva_data'
 *
 */

/* Include files */
#include "compute_iva_data.h"
#include "compute_iva.h"
#include "init_iva.h"
#include "rt_nonfinite.h"

/* Variable Definitions */
const float fv[65] = { 1.0F, 0.99879545F, 0.99518472F, 0.989176512F,
  0.980785251F, 0.970031261F, 0.956940353F, 0.941544056F, 0.923879504F,
  0.903989315F, 0.881921232F, 0.857728601F, 0.831469595F, 0.803207517F,
  0.773010433F, 0.740951121F, 0.707106769F, 0.671559F, 0.634393334F, 0.59569931F,
  0.555570245F, 0.514102757F, 0.471396744F, 0.427555084F, 0.382683456F,
  0.336889863F, 0.290284663F, 0.242980197F, 0.195090324F, 0.146730468F,
  0.0980171412F, 0.0490676761F, 0.0F, -0.0490676761F, -0.0980171412F,
  -0.146730468F, -0.195090324F, -0.242980197F, -0.290284663F, -0.336889863F,
  -0.382683456F, -0.427555084F, -0.471396744F, -0.514102757F, -0.555570245F,
  -0.59569931F, -0.634393334F, -0.671559F, -0.707106769F, -0.740951121F,
  -0.773010433F, -0.803207517F, -0.831469595F, -0.857728601F, -0.881921232F,
  -0.903989315F, -0.923879504F, -0.941544056F, -0.956940353F, -0.970031261F,
  -0.980785251F, -0.989176512F, -0.99518472F, -0.99879545F, -1.0F };

boolean_T isInitialized_compute_iva = false;

/* End of code generation (compute_iva_data.cpp) */

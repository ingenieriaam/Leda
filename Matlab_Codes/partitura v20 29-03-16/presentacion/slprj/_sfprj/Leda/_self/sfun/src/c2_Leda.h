#ifndef __c2_Leda_h__
#define __c2_Leda_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  int32_T c2_sfEvent;
  boolean_T c2_isStable;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_Leda;
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  real_T c2_pent[33096708];
  boolean_T c2_pent_not_empty;
} SFc2_LedaInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_Leda_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c2_Leda_get_check_sum(mxArray *plhs[]);
extern void c2_Leda_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif

#ifndef __c1_Leda_h__
#define __c1_Leda_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc1_LedaInstanceStruct
#define typedef_SFc1_LedaInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c1_sfEvent;
  boolean_T c1_isStable;
  boolean_T c1_doneDoubleBufferReInit;
  uint8_T c1_is_active_c1_Leda;
  real_T c1_f_dur;
  boolean_T c1_f_dur_not_empty;
  real_T c1_f_detec;
  boolean_T c1_f_detec_not_empty;
  real_T c1_in_tot[1280];
  boolean_T c1_in_tot_not_empty;
  real_T c1_window[1024];
  boolean_T c1_window_not_empty;
  real_T c1_bloque_ant[1024];
  boolean_T c1_bloque_ant_not_empty;
  real_T c1_bloque_act[1024];
  boolean_T c1_bloque_act_not_empty;
  real_T c1_ruido;
  boolean_T c1_ruido_not_empty;
  real_T c1_ruido_2;
  boolean_T c1_ruido_2_not_empty;
  real_T c1_piso_ruido;
  boolean_T c1_piso_ruido_not_empty;
  real_T c1_nivel_param;
  boolean_T c1_nivel_param_not_empty;
  real_T c1_piso_div_2;
  boolean_T c1_piso_div_2_not_empty;
  real_T c1_piso_suma_2;
  boolean_T c1_piso_suma_2_not_empty;
  real_T c1_flag_nota;
  boolean_T c1_flag_nota_not_empty;
} SFc1_LedaInstanceStruct;

#endif                                 /*typedef_SFc1_LedaInstanceStruct*/

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_Leda_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_Leda_get_check_sum(mxArray *plhs[]);
extern void c1_Leda_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif

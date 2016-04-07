/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Leda_sfun.h"
#include "c2_Leda.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Leda_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c2_debug_family_names[5] = { "pent", "i", "nargin",
  "nargout", "nota" };

/* Function Declarations */
static void initialize_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void initialize_params_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void enable_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void disable_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_Leda(SFc2_LedaInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_Leda(SFc2_LedaInstanceStruct
  *chartInstance);
static void set_sim_state_c2_Leda(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_st);
static void finalize_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void sf_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void c2_chartstep_c2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void initSimStructsc2_Leda(SFc2_LedaInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static void c2_b_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[33096708]);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_c_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_imread, const char_T *c2_identifier, real_T c2_y[435483]);
static void c2_d_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[435483]);
static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_e_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_f_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Leda, const char_T *c2_identifier);
static uint8_T c2_g_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_LedaInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c2_is_active_c2_Leda = 0U;
}

static void initialize_params_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
}

static void enable_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c2_update_debugger_state_c2_Leda(SFc2_LedaInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c2_Leda(SFc2_LedaInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  uint8_T c2_hoistedGlobal;
  uint8_T c2_u;
  const mxArray *c2_b_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellarray(1), FALSE);
  c2_hoistedGlobal = chartInstance->c2_is_active_c2_Leda;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  sf_mex_assign(&c2_st, c2_y, FALSE);
  return c2_st;
}

static void set_sim_state_c2_Leda(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = TRUE;
  c2_u = sf_mex_dup(c2_st);
  chartInstance->c2_is_active_c2_Leda = c2_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 0)), "is_active_c2_Leda");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_Leda(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
}

static void sf_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
  real_T *c2_nota;
  c2_nota = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*c2_nota, 0U);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_Leda(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_LedaMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c2_chartstep_c2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_nota;
  uint32_T c2_debug_family_var_map[5];
  static real_T c2_pent[33096708];
  real_T c2_i;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 0.0;
  int32_T c2_i0;
  int32_T c2_b_i;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  int32_T c2_i1;
  static char_T c2_cv0[4] = { '.', 'j', 'p', 'g' };

  char_T c2_b_u[4];
  const mxArray *c2_b_y = NULL;
  static real_T c2_dv0[435483];
  int32_T c2_c_i;
  int32_T c2_i2;
  int32_T c2_i3;
  int32_T c2_i4;
  int32_T c2_b_nota;
  int32_T c2_i5;
  int32_T c2_i6;
  int32_T c2_i7;
  static real_T c2_c_u[435483];
  const mxArray *c2_c_y = NULL;
  real_T *c2_c_nota;
  c2_c_nota = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *c2_c_nota;
  c2_nota = c2_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 5U, 5U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c2_pent, 0U, c2_b_sf_marshallOut,
    c2_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_i, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_nota, 4U, c2_sf_marshallOut);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 3);
  if (CV_EML_IF(0, 1, 0, c2_nota < 4.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
    c2_nota = 4.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  if (CV_EML_IF(0, 1, 1, c2_nota > 76.0)) {
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 7);
    c2_nota = 76.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 12);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 13);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 14);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 18);
  for (c2_i0 = 0; c2_i0 < 33096708; c2_i0++) {
    c2_pent[c2_i0] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 20);
  c2_i = 4.0;
  c2_b_i = 0;
  while (c2_b_i < 73) {
    c2_i = 4.0 + (real_T)c2_b_i;
    CV_EML_FOR(0, 1, 0, 1);
    _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 22);
    c2_u = c2_i;
    c2_y = NULL;
    sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
    for (c2_i1 = 0; c2_i1 < 4; c2_i1++) {
      c2_b_u[c2_i1] = c2_cv0[c2_i1];
    }

    c2_b_y = NULL;
    sf_mex_assign(&c2_b_y, sf_mex_create("y", c2_b_u, 10, 0U, 1U, 0U, 2, 1, 4),
                  FALSE);
    c2_c_emlrt_marshallIn(chartInstance, sf_mex_call_debug("imread", 1U, 1U, 14,
      sf_mex_call_debug("horzcat", 1U, 2U, 14, sf_mex_call_debug("num2str", 1U,
      1U, 14, c2_y), 14, c2_b_y)), "imread", c2_dv0);
    c2_c_i = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("pent", (int32_T)
      _SFD_INTEGER_CHECK("i", c2_i), 1, 76, 4, 0) - 1;
    for (c2_i2 = 0; c2_i2 < 3; c2_i2++) {
      for (c2_i3 = 0; c2_i3 < 381; c2_i3++) {
        for (c2_i4 = 0; c2_i4 < 381; c2_i4++) {
          c2_pent[((c2_i4 + 381 * c2_i3) + 145161 * c2_i2) + 435483 * c2_c_i] =
            c2_dv0[(c2_i4 + 381 * c2_i3) + 145161 * c2_i2];
        }
      }
    }

    c2_b_i++;
    _SF_MEX_LISTEN_FOR_CTRL_C(chartInstance->S);
  }

  CV_EML_FOR(0, 1, 0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 28);
  c2_b_nota = (int32_T)(real_T)_SFD_EML_ARRAY_BOUNDS_CHECK("pent", (int32_T)
    _SFD_INTEGER_CHECK("nota", c2_nota), 1, 76, 4, 0) - 1;
  for (c2_i5 = 0; c2_i5 < 3; c2_i5++) {
    for (c2_i6 = 0; c2_i6 < 381; c2_i6++) {
      for (c2_i7 = 0; c2_i7 < 381; c2_i7++) {
        c2_c_u[(c2_i7 + 381 * c2_i6) + 145161 * c2_i5] = c2_pent[((c2_i7 + 381 *
          c2_i6) + 145161 * c2_i5) + 435483 * c2_b_nota];
      }
    }
  }

  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", c2_c_u, 0, 0U, 1U, 0U, 3, 381, 381,
    3), FALSE);
  sf_mex_call_debug("imshow", 0U, 1U, 14, c2_c_y);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -28);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 1U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_Leda(SFc2_LedaInstanceStruct *chartInstance)
{
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber)
{
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_nargout;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)chartInstanceVoid;
  c2_nargout = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_nargout), &c2_thisId);
  sf_mex_destroy(&c2_nargout);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_i8;
  int32_T c2_i9;
  int32_T c2_i10;
  int32_T c2_i11;
  int32_T c2_i12;
  int32_T c2_i13;
  int32_T c2_i14;
  static real_T c2_b_inData[33096708];
  int32_T c2_i15;
  int32_T c2_i16;
  int32_T c2_i17;
  int32_T c2_i18;
  int32_T c2_i19;
  int32_T c2_i20;
  int32_T c2_i21;
  static real_T c2_u[33096708];
  const mxArray *c2_y = NULL;
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_i8 = 0;
  for (c2_i9 = 0; c2_i9 < 76; c2_i9++) {
    c2_i10 = 0;
    for (c2_i11 = 0; c2_i11 < 3; c2_i11++) {
      c2_i12 = 0;
      for (c2_i13 = 0; c2_i13 < 381; c2_i13++) {
        for (c2_i14 = 0; c2_i14 < 381; c2_i14++) {
          c2_b_inData[((c2_i14 + c2_i12) + c2_i10) + c2_i8] = (*(real_T (*)
            [33096708])c2_inData)[((c2_i14 + c2_i12) + c2_i10) + c2_i8];
        }

        c2_i12 += 381;
      }

      c2_i10 += 145161;
    }

    c2_i8 += 435483;
  }

  c2_i15 = 0;
  for (c2_i16 = 0; c2_i16 < 76; c2_i16++) {
    c2_i17 = 0;
    for (c2_i18 = 0; c2_i18 < 3; c2_i18++) {
      c2_i19 = 0;
      for (c2_i20 = 0; c2_i20 < 381; c2_i20++) {
        for (c2_i21 = 0; c2_i21 < 381; c2_i21++) {
          c2_u[((c2_i21 + c2_i19) + c2_i17) + c2_i15] = c2_b_inData[((c2_i21 +
            c2_i19) + c2_i17) + c2_i15];
        }

        c2_i19 += 381;
      }

      c2_i17 += 145161;
    }

    c2_i15 += 435483;
  }

  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 0, 0U, 1U, 0U, 4, 381, 381, 3,
    76), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static void c2_b_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[33096708])
{
  static real_T c2_dv1[33096708];
  int32_T c2_i22;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv1, 1, 0, 0U, 1, 0U, 4, 381,
                381, 3, 76);
  for (c2_i22 = 0; c2_i22 < 33096708; c2_i22++) {
    c2_y[c2_i22] = c2_dv1[c2_i22];
  }

  sf_mex_destroy(&c2_u);
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_pent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  static real_T c2_y[33096708];
  int32_T c2_i23;
  int32_T c2_i24;
  int32_T c2_i25;
  int32_T c2_i26;
  int32_T c2_i27;
  int32_T c2_i28;
  int32_T c2_i29;
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)chartInstanceVoid;
  c2_pent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_pent), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_pent);
  c2_i23 = 0;
  for (c2_i24 = 0; c2_i24 < 76; c2_i24++) {
    c2_i25 = 0;
    for (c2_i26 = 0; c2_i26 < 3; c2_i26++) {
      c2_i27 = 0;
      for (c2_i28 = 0; c2_i28 < 381; c2_i28++) {
        for (c2_i29 = 0; c2_i29 < 381; c2_i29++) {
          (*(real_T (*)[33096708])c2_outData)[((c2_i29 + c2_i27) + c2_i25) +
            c2_i23] = c2_y[((c2_i29 + c2_i27) + c2_i25) + c2_i23];
        }

        c2_i27 += 381;
      }

      c2_i25 += 145161;
    }

    c2_i23 += 435483;
  }

  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_Leda_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), FALSE);
  return c2_nameCaptureInfo;
}

static void c2_c_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_imread, const char_T *c2_identifier, real_T c2_y[435483])
{
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_imread), &c2_thisId, c2_y);
  sf_mex_destroy(&c2_imread);
}

static void c2_d_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance, const
  mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId, real_T c2_y[435483])
{
  static real_T c2_dv2[435483];
  int32_T c2_i30;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), c2_dv2, 0, 0, 0U, 1, 0U, 3, 381,
                381, 3);
  for (c2_i30 = 0; c2_i30 < 435483; c2_i30++) {
    c2_y[c2_i30] = c2_dv2[c2_i30];
  }

  sf_mex_destroy(&c2_u);
}

static const mxArray *c2_c_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, FALSE);
  return c2_mxArrayOutData;
}

static int32_T c2_e_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i31;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i31, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i31;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_f_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Leda, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_y = c2_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_is_active_c2_Leda),
    &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_Leda);
  return c2_y;
}

static uint8_T c2_g_emlrt_marshallIn(SFc2_LedaInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_LedaInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_Leda_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2139374234U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2641251111U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3541105668U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1270893992U);
}

mxArray *sf_c2_Leda_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("RNEr3uTozouEmh7bv14pmE");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_Leda_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_Leda_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_Leda(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S'type','srcId','name','auxInfo'{{M[8],M[0],T\"is_active_c2_Leda\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 1, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_Leda_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_LedaInstanceStruct *chartInstance;
    chartInstance = (SFc2_LedaInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _LedaMachineNumber_,
           2,
           1,
           1,
           1,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           ssGetPath(S),
           (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_LedaMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_LedaMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _LedaMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"nota");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,1,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,571);
        _SFD_CV_INIT_EML_IF(0,1,0,27,38,-1,56);
        _SFD_CV_INIT_EML_IF(0,1,1,57,69,-1,87);
        _SFD_CV_INIT_EML_FOR(0,1,0,384,397,458);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);

        {
          real_T *c2_nota;
          c2_nota = (real_T *)ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c2_nota);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _LedaMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "T0ttVZZaZv4SwEqPsOhAqH";
}

static void sf_opaque_initialize_c2_Leda(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_LedaInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
  initialize_c2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_Leda(void *chartInstanceVar)
{
  enable_c2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_Leda(void *chartInstanceVar)
{
  disable_c2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_Leda(void *chartInstanceVar)
{
  sf_c2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c2_Leda(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c2_Leda((SFc2_LedaInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_Leda();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c2_Leda(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c2_Leda();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c2_Leda((SFc2_LedaInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c2_Leda(SimStruct* S)
{
  return sf_internal_get_sim_state_c2_Leda(S);
}

static void sf_opaque_set_sim_state_c2_Leda(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c2_Leda(S, st);
}

static void sf_opaque_terminate_c2_Leda(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_LedaInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Leda_optimization_info();
    }

    finalize_c2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_Leda((SFc2_LedaInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_Leda(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_Leda((SFc2_LedaInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c2_Leda(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Leda_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,2,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,2,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=0; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 1; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(386660348U));
  ssSetChecksum1(S,(326698377U));
  ssSetChecksum2(S,(2614738579U));
  ssSetChecksum3(S,(866903179U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_Leda(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_Leda(SimStruct *S)
{
  SFc2_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc2_LedaInstanceStruct *)utMalloc(sizeof
    (SFc2_LedaInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc2_LedaInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_Leda;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_Leda;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_Leda;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_Leda;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_Leda;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_Leda;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_Leda;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_Leda;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_Leda;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_Leda;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_Leda;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c2_Leda_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_Leda(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_Leda(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_Leda(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_Leda_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}

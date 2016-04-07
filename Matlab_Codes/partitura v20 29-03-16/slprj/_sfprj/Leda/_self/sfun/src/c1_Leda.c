/* Include files */

#include <stddef.h>
#include "blas.h"
#include "Leda_sfun.h"
#include "c1_Leda.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Leda_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static const char * c1_debug_family_names[13] = { "frec_Ffund", "dur_len",
  "detec_len", "salto", "in", "nargin", "nargout", "bloque", "fs", "activar",
  "nota", "f_dur", "f_detec" };

static const char * c1_b_debug_family_names[10] = { "L", "NFFT", "signal_f",
  "Length", "nargin", "nargout", "signal", "Fs", "fft_x", "fft_y" };

static const char * c1_c_debug_family_names[10] = { "L", "NFFT", "signal_f",
  "Length", "nargin", "nargout", "signal", "Fs", "fft_x", "fft_y" };

static const char * c1_d_debug_family_names[32] = { "aux_window", "bloque_ruido",
  "fft_y", "fft_x", "fft_y1", "fft_y2", "fft_anterior", "fft_actual", "diff_fft",
  "abs_diff_fft", "sum_diff_fft", "sum_abs_diff_fft", "div_param", "suma_param",
  "w_len", "salto", "nargin", "nargout", "bloque", "fs", "nota", "in_tot",
  "window", "bloque_ant", "bloque_act", "ruido", "ruido_2", "piso_ruido",
  "nivel_param", "piso_div_2", "piso_suma_2", "flag_nota" };

static const char * c1_e_debug_family_names[9] = { "L", "NFFT", "fft_s",
  "espectro", "s", "nargin", "nargout", "signal", "nivel" };

static const char * c1_f_debug_family_names[10] = { "L", "NFFT", "signal_f",
  "Length", "nargin", "nargout", "signal", "Fs", "fft_x", "fft_y" };

static const char * c1_g_debug_family_names[5] = { "maximos_x", "maximos_y",
  "signal", "nargin", "nargout" };

static const char * c1_h_debug_family_names[12] = { "notas", "chupelupe",
  "fbase", "r", "a", "n", "numero", "nargin", "nargout", "maximo", "nota",
  "notanum" };

static const char * c1_i_debug_family_names[26] = { "piso_de_ruido", "in_hann",
  "in_hann_corr", "f_corr", "fft_in_hann_corr", "Fm_x_corr", "f", "d", "M",
  "Ffund", "i", "piso_corr", "max_x_corr", "max_frec_corr", "frec_Ffundaux",
  "Rangof", "entro", "j", "len", "MIN_FREC", "nargin", "nargout", "in", "fs",
  "frec_Ffund", "numfrec_Ffund" };

/* Function Declarations */
static void initialize_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void initialize_params_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void enable_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void disable_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_Leda(SFc1_LedaInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_Leda(SFc1_LedaInstanceStruct
  *chartInstance);
static void set_sim_state_c1_Leda(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_st);
static void finalize_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void sf_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void c1_chartstep_c1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static void initSimStructsc1_Leda(SFc1_LedaInstanceStruct *chartInstance);
static real_T c1_dur_prueba_simulink(SFc1_LedaInstanceStruct *chartInstance,
  real_T c1_bloque[256], real_T c1_fs);
static void c1_fft_abs(SFc1_LedaInstanceStruct *chartInstance, real_T c1_signal
  [256], real_T c1_Fs, real_T c1_fft_x[513], real_T c1_fft_y[513]);
static void c1_b_fft_abs(SFc1_LedaInstanceStruct *chartInstance, real_T
  c1_signal[1024], real_T c1_Fs, real_T c1_fft_x[513], real_T c1_fft_y[513]);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData);
static real_T c1_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_f_detec, const char_T *c1_identifier);
static real_T c1_b_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_c_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_f_dur, const char_T *c1_identifier);
static real_T c1_d_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_e_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_nota, const char_T *c1_identifier);
static real_T c1_f_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[257], int32_T c1_inData_sizes[1]);
static void c1_g_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[257],
  int32_T c1_y_sizes[1]);
static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[257],
  int32_T c1_outData_sizes[1]);
static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static char_T c1_h_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_i_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[513]);
static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_j_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[513]);
static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_k_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[256]);
static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_l_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[1024]);
static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_m_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024]);
static void c1_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_n_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_flag_nota, const char_T *c1_identifier);
static real_T c1_o_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_p_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_piso_suma_2, const char_T *c1_identifier);
static real_T c1_q_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_r_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_piso_div_2, const char_T *c1_identifier);
static real_T c1_s_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_t_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_nivel_param, const char_T *c1_identifier);
static real_T c1_u_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_p_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_v_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_piso_ruido, const char_T *c1_identifier);
static real_T c1_w_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_q_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_x_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_ruido_2, const char_T *c1_identifier);
static real_T c1_y_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_r_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static real_T c1_ab_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_ruido, const char_T *c1_identifier);
static real_T c1_bb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_s_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_cb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_bloque_act, const char_T *c1_identifier, real_T c1_y[1024]);
static void c1_db_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024]);
static void c1_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_t_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_eb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_bloque_ant, const char_T *c1_identifier, real_T c1_y[1024]);
static void c1_fb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024]);
static void c1_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_u_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_gb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_window, const char_T *c1_identifier, real_T c1_y[1024]);
static void c1_hb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024]);
static void c1_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_v_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_ib_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_in_tot, const char_T *c1_identifier, real_T c1_y[1280]);
static void c1_jb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1280]);
static void c1_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_w_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[257], int32_T c1_inData_sizes[2]);
static void c1_kb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[257],
  int32_T c1_y_sizes[2]);
static void c1_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[257],
  int32_T c1_outData_sizes[2]);
static const mxArray *c1_x_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_lb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[129]);
static void c1_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_y_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_mb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[256]);
static void c1_x_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_ab_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_nb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2049]);
static void c1_y_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_bb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_ob_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4095]);
static void c1_ab_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_cb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_pb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[4096]);
static void c1_bb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_db_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_qb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2049]);
static void c1_cb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_eb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_rb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[4]);
static void c1_db_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_fb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_sb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[73]);
static void c1_eb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_gb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_tb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[348]);
static void c1_fb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static const mxArray *c1_hb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static void c1_ub_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2048]);
static void c1_gb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static void c1_info_helper(const mxArray **c1_info);
static const mxArray *c1_emlrt_marshallOut(char * c1_u);
static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u);
static void c1_b_info_helper(const mxArray **c1_info);
static void c1_c_info_helper(const mxArray **c1_info);
static void c1_d_info_helper(const mxArray **c1_info);
static void c1_hanning(SFc1_LedaInstanceStruct *chartInstance);
static void c1_b_hanning(SFc1_LedaInstanceStruct *chartInstance);
static void c1_eml_scalar_eg(SFc1_LedaInstanceStruct *chartInstance);
static void c1_fft(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[256],
                   creal_T c1_y[1024]);
static void c1_eml_size_ispow2(SFc1_LedaInstanceStruct *chartInstance);
static void c1_b_eml_scalar_eg(SFc1_LedaInstanceStruct *chartInstance);
static void c1_abs(SFc1_LedaInstanceStruct *chartInstance, creal_T c1_x[513],
                   real_T c1_y[513]);
static real_T c1_sum(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[513]);
static void c1_power(SFc1_LedaInstanceStruct *chartInstance, real_T c1_a[513],
                     real_T c1_y[513]);
static void c1_b_fft(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[1024],
                     creal_T c1_y[1024]);
static void c1_c_eml_scalar_eg(SFc1_LedaInstanceStruct *chartInstance);
static void c1_b_abs(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[513],
                     real_T c1_y[513]);
static const mxArray *c1_ib_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData);
static int32_T c1_vb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void c1_hb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData);
static uint8_T c1_wb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_Leda, const char_T *c1_identifier);
static uint8_T c1_xb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId);
static void init_dsm_address_info(SFc1_LedaInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
  chartInstance->c1_sfEvent = CALL_EVENT;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_f_dur_not_empty = FALSE;
  chartInstance->c1_f_detec_not_empty = FALSE;
  chartInstance->c1_in_tot_not_empty = FALSE;
  chartInstance->c1_window_not_empty = FALSE;
  chartInstance->c1_bloque_ant_not_empty = FALSE;
  chartInstance->c1_bloque_act_not_empty = FALSE;
  chartInstance->c1_ruido_not_empty = FALSE;
  chartInstance->c1_ruido_2_not_empty = FALSE;
  chartInstance->c1_piso_ruido_not_empty = FALSE;
  chartInstance->c1_nivel_param_not_empty = FALSE;
  chartInstance->c1_piso_div_2_not_empty = FALSE;
  chartInstance->c1_piso_suma_2_not_empty = FALSE;
  chartInstance->c1_flag_nota_not_empty = FALSE;
  chartInstance->c1_is_active_c1_Leda = 0U;
}

static void initialize_params_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
}

static void enable_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_Leda(SFc1_LedaInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_Leda(SFc1_LedaInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  int32_T c1_i0;
  real_T c1_b_u[1024];
  const mxArray *c1_c_y = NULL;
  int32_T c1_i1;
  real_T c1_c_u[1024];
  const mxArray *c1_d_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_d_u;
  const mxArray *c1_e_y = NULL;
  real_T c1_c_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_f_y = NULL;
  real_T c1_d_hoistedGlobal;
  real_T c1_f_u;
  const mxArray *c1_g_y = NULL;
  int32_T c1_i2;
  real_T c1_g_u[1280];
  const mxArray *c1_h_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_h_u;
  const mxArray *c1_i_y = NULL;
  real_T c1_f_hoistedGlobal;
  real_T c1_i_u;
  const mxArray *c1_j_y = NULL;
  real_T c1_g_hoistedGlobal;
  real_T c1_j_u;
  const mxArray *c1_k_y = NULL;
  real_T c1_h_hoistedGlobal;
  real_T c1_k_u;
  const mxArray *c1_l_y = NULL;
  real_T c1_i_hoistedGlobal;
  real_T c1_l_u;
  const mxArray *c1_m_y = NULL;
  real_T c1_j_hoistedGlobal;
  real_T c1_m_u;
  const mxArray *c1_n_y = NULL;
  int32_T c1_i3;
  real_T c1_n_u[1024];
  const mxArray *c1_o_y = NULL;
  uint8_T c1_k_hoistedGlobal;
  uint8_T c1_o_u;
  const mxArray *c1_p_y = NULL;
  real_T *c1_nota;
  c1_nota = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(15), FALSE);
  c1_hoistedGlobal = *c1_nota;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 0, c1_b_y);
  for (c1_i0 = 0; c1_i0 < 1024; c1_i0++) {
    c1_b_u[c1_i0] = chartInstance->c1_bloque_act[c1_i0];
  }

  c1_c_y = NULL;
  if (!chartInstance->c1_bloque_act_not_empty) {
    sf_mex_assign(&c1_c_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_c_y, sf_mex_create("y", c1_b_u, 0, 0U, 1U, 0U, 1, 1024),
                  FALSE);
  }

  sf_mex_setcell(c1_y, 1, c1_c_y);
  for (c1_i1 = 0; c1_i1 < 1024; c1_i1++) {
    c1_c_u[c1_i1] = chartInstance->c1_bloque_ant[c1_i1];
  }

  c1_d_y = NULL;
  if (!chartInstance->c1_bloque_ant_not_empty) {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", c1_c_u, 0, 0U, 1U, 0U, 1, 1024),
                  FALSE);
  }

  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_b_hoistedGlobal = chartInstance->c1_f_detec;
  c1_d_u = c1_b_hoistedGlobal;
  c1_e_y = NULL;
  if (!chartInstance->c1_f_detec_not_empty) {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_d_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_c_hoistedGlobal = chartInstance->c1_f_dur;
  c1_e_u = c1_c_hoistedGlobal;
  c1_f_y = NULL;
  if (!chartInstance->c1_f_dur_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_d_hoistedGlobal = chartInstance->c1_flag_nota;
  c1_f_u = c1_d_hoistedGlobal;
  c1_g_y = NULL;
  if (!chartInstance->c1_flag_nota_not_empty) {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_f_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 5, c1_g_y);
  for (c1_i2 = 0; c1_i2 < 1280; c1_i2++) {
    c1_g_u[c1_i2] = chartInstance->c1_in_tot[c1_i2];
  }

  c1_h_y = NULL;
  if (!chartInstance->c1_in_tot_not_empty) {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", c1_g_u, 0, 0U, 1U, 0U, 1, 1280),
                  FALSE);
  }

  sf_mex_setcell(c1_y, 6, c1_h_y);
  c1_e_hoistedGlobal = chartInstance->c1_nivel_param;
  c1_h_u = c1_e_hoistedGlobal;
  c1_i_y = NULL;
  if (!chartInstance->c1_nivel_param_not_empty) {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_h_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_f_hoistedGlobal = chartInstance->c1_piso_div_2;
  c1_i_u = c1_f_hoistedGlobal;
  c1_j_y = NULL;
  if (!chartInstance->c1_piso_div_2_not_empty) {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_i_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_g_hoistedGlobal = chartInstance->c1_piso_ruido;
  c1_j_u = c1_g_hoistedGlobal;
  c1_k_y = NULL;
  if (!chartInstance->c1_piso_ruido_not_empty) {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_j_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_h_hoistedGlobal = chartInstance->c1_piso_suma_2;
  c1_k_u = c1_h_hoistedGlobal;
  c1_l_y = NULL;
  if (!chartInstance->c1_piso_suma_2_not_empty) {
    sf_mex_assign(&c1_l_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_k_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_i_hoistedGlobal = chartInstance->c1_ruido;
  c1_l_u = c1_i_hoistedGlobal;
  c1_m_y = NULL;
  if (!chartInstance->c1_ruido_not_empty) {
    sf_mex_assign(&c1_m_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_l_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 11, c1_m_y);
  c1_j_hoistedGlobal = chartInstance->c1_ruido_2;
  c1_m_u = c1_j_hoistedGlobal;
  c1_n_y = NULL;
  if (!chartInstance->c1_ruido_2_not_empty) {
    sf_mex_assign(&c1_n_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_m_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_setcell(c1_y, 12, c1_n_y);
  for (c1_i3 = 0; c1_i3 < 1024; c1_i3++) {
    c1_n_u[c1_i3] = chartInstance->c1_window[c1_i3];
  }

  c1_o_y = NULL;
  if (!chartInstance->c1_window_not_empty) {
    sf_mex_assign(&c1_o_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0),
                  FALSE);
  } else {
    sf_mex_assign(&c1_o_y, sf_mex_create("y", c1_n_u, 0, 0U, 1U, 0U, 1, 1024),
                  FALSE);
  }

  sf_mex_setcell(c1_y, 13, c1_o_y);
  c1_k_hoistedGlobal = chartInstance->c1_is_active_c1_Leda;
  c1_o_u = c1_k_hoistedGlobal;
  c1_p_y = NULL;
  sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_o_u, 3, 0U, 0U, 0U, 0), FALSE);
  sf_mex_setcell(c1_y, 14, c1_p_y);
  sf_mex_assign(&c1_st, c1_y, FALSE);
  return c1_st;
}

static void set_sim_state_c1_Leda(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_st)
{
  const mxArray *c1_u;
  real_T c1_dv0[1024];
  int32_T c1_i4;
  real_T c1_dv1[1024];
  int32_T c1_i5;
  real_T c1_dv2[1280];
  int32_T c1_i6;
  real_T c1_dv3[1024];
  int32_T c1_i7;
  real_T *c1_nota;
  c1_nota = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_nota = c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    0)), "nota");
  c1_cb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 1)),
    "bloque_act", c1_dv0);
  for (c1_i4 = 0; c1_i4 < 1024; c1_i4++) {
    chartInstance->c1_bloque_act[c1_i4] = c1_dv0[c1_i4];
  }

  c1_eb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)),
    "bloque_ant", c1_dv1);
  for (c1_i5 = 0; c1_i5 < 1024; c1_i5++) {
    chartInstance->c1_bloque_ant[c1_i5] = c1_dv1[c1_i5];
  }

  chartInstance->c1_f_detec = c1_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 3)), "f_detec");
  chartInstance->c1_f_dur = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 4)), "f_dur");
  chartInstance->c1_flag_nota = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 5)), "flag_nota");
  c1_ib_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 6)),
    "in_tot", c1_dv2);
  for (c1_i6 = 0; c1_i6 < 1280; c1_i6++) {
    chartInstance->c1_in_tot[c1_i6] = c1_dv2[c1_i6];
  }

  chartInstance->c1_nivel_param = c1_t_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 7)), "nivel_param");
  chartInstance->c1_piso_div_2 = c1_r_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 8)), "piso_div_2");
  chartInstance->c1_piso_ruido = c1_v_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 9)), "piso_ruido");
  chartInstance->c1_piso_suma_2 = c1_p_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 10)), "piso_suma_2");
  chartInstance->c1_ruido = c1_ab_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 11)), "ruido");
  chartInstance->c1_ruido_2 = c1_x_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 12)), "ruido_2");
  c1_gb_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 13)),
    "window", c1_dv3);
  for (c1_i7 = 0; c1_i7 < 1024; c1_i7++) {
    chartInstance->c1_window[c1_i7] = c1_dv3[c1_i7];
  }

  chartInstance->c1_is_active_c1_Leda = c1_wb_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 14)), "is_active_c1_Leda");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_Leda(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
}

static void sf_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
  int32_T c1_i8;
  real_T *c1_fs;
  real_T *c1_activar;
  real_T *c1_nota;
  real_T (*c1_bloque)[256];
  c1_nota = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_activar = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_fs = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_bloque = (real_T (*)[256])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  for (c1_i8 = 0; c1_i8 < 256; c1_i8++) {
    _SFD_DATA_RANGE_CHECK((*c1_bloque)[c1_i8], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_fs, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_activar, 2U);
  _SFD_DATA_RANGE_CHECK(*c1_nota, 3U);
  chartInstance->c1_sfEvent = CALL_EVENT;
  c1_chartstep_c1_Leda(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_LedaMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_chartstep_c1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
  real_T c1_hoistedGlobal;
  real_T c1_b_hoistedGlobal;
  int32_T c1_i9;
  real_T c1_bloque[256];
  real_T c1_fs;
  real_T c1_activar;
  uint32_T c1_debug_family_var_map[13];
  char_T c1_frec_Ffund;
  real_T c1_dur_len;
  real_T c1_detec_len;
  real_T c1_salto;
  real_T c1_in;
  int32_T c1_in_sizes;
  real_T c1_in_data[257];
  real_T c1_nargin = 3.0;
  real_T c1_nargout = 1.0;
  real_T c1_nota;
  int32_T c1_i10;
  real_T c1_b_bloque[256];
  int32_T c1_i11;
  real_T c1_dv4[257];
  int32_T c1_i12;
  int32_T c1_i13;
  int32_T c1_x_sizes;
  int32_T c1_loop_ub;
  int32_T c1_i14;
  real_T c1_x_data[257];
  real_T c1_n;
  real_T *c1_b_nota;
  real_T *c1_b_fs;
  real_T *c1_b_activar;
  real_T (*c1_c_bloque)[256];
  c1_b_nota = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_activar = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
  c1_b_fs = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
  c1_c_bloque = (real_T (*)[256])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
  c1_hoistedGlobal = *c1_b_fs;
  c1_b_hoistedGlobal = *c1_b_activar;
  for (c1_i9 = 0; c1_i9 < 256; c1_i9++) {
    c1_bloque[c1_i9] = (*c1_c_bloque)[c1_i9];
  }

  c1_fs = c1_hoistedGlobal;
  c1_activar = c1_b_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 13U, 14U, c1_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_frec_Ffund, 0U, c1_f_sf_marshallOut,
    c1_e_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_dur_len, 1U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_detec_len, 2U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_salto, 3U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_in, MAX_uint32_T, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_DYN_IMPORTABLE(c1_in_data, (const int32_T *)
    &c1_in_sizes, NULL, 0, -1, (void *)c1_e_sf_marshallOut, (void *)
    c1_d_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 6U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c1_bloque, 7U, c1_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_fs, 8U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_activar, 9U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nota, 10U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_f_dur, 11U,
    c1_b_sf_marshallOut, c1_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_f_detec, 12U,
    c1_sf_marshallOut, c1_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 3);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 4);
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 6);
  c1_frec_Ffund = ' ';
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 7);
  c1_nota = 4.0;
  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 9);
  if (CV_EML_IF(0, 1, 0, c1_activar != 0.0) != 0.0) {
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 24);
    c1_dur_len = 1024.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 25);
    c1_detec_len = 2048.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 26);
    c1_salto = 256.0;
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 32);
    if (CV_EML_IF(0, 1, 1, !chartInstance->c1_f_dur_not_empty)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 33);
      chartInstance->c1_f_dur = 0.0;
      chartInstance->c1_f_dur_not_empty = TRUE;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 34);
      chartInstance->c1_f_detec = 0.0;
      chartInstance->c1_f_detec_not_empty = TRUE;
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 37);
    for (c1_i10 = 0; c1_i10 < 256; c1_i10++) {
      c1_b_bloque[c1_i10] = c1_bloque[c1_i10];
    }

    c1_nota = c1_dur_prueba_simulink(chartInstance, c1_b_bloque, c1_fs);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 39);
    if (CV_EML_IF(0, 1, 2, c1_nota == 2.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 40);
      chartInstance->c1_f_dur++;
    } else {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 41);
      if (CV_EML_IF(0, 1, 3, c1_nota == 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 42);
        chartInstance->c1_f_dur = 0.0;
      }
    }

    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 48);
    c1_in = 0.0;
    _SFD_SYMBOL_SWITCH(4U, 4U);
    _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 50);
    if (CV_EML_IF(0, 1, 4, chartInstance->c1_f_dur == 4.0)) {
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 51);
      if (CV_EML_IF(0, 1, 5, chartInstance->c1_f_detec == 0.0)) {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 52);
        c1_in_sizes = 256;
        for (c1_i11 = 0; c1_i11 < 256; c1_i11++) {
          c1_in_data[c1_i11] = c1_bloque[c1_i11];
        }

        _SFD_SYMBOL_SWITCH(4U, 5U);
      } else {
        _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 54);
        c1_dv4[0] = 0.0;
        for (c1_i12 = 0; c1_i12 < 256; c1_i12++) {
          c1_dv4[c1_i12 + 1] = c1_bloque[c1_i12];
        }

        c1_in_sizes = 257;
        for (c1_i13 = 0; c1_i13 < 257; c1_i13++) {
          c1_in_data[c1_i13] = c1_dv4[c1_i13];
        }

        _SFD_SYMBOL_SWITCH(4U, 5U);
      }

      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 56);
      chartInstance->c1_f_detec++;
      _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, 59);
      c1_x_sizes = c1_in_sizes;
      c1_loop_ub = c1_in_sizes - 1;
      for (c1_i14 = 0; c1_i14 <= c1_loop_ub; c1_i14++) {
        c1_x_data[c1_i14] = c1_in_data[c1_i14];
      }

      c1_n = (real_T)c1_x_sizes;
      CV_EML_IF(0, 1, 6, c1_n == 2048.0);
    }
  }

  _SFD_EML_CALL(0U, chartInstance->c1_sfEvent, -60);
  _SFD_SYMBOL_SCOPE_POP();
  *c1_b_nota = c1_nota;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c1_sfEvent);
}

static void initSimStructsc1_Leda(SFc1_LedaInstanceStruct *chartInstance)
{
}

static real_T c1_dur_prueba_simulink(SFc1_LedaInstanceStruct *chartInstance,
  real_T c1_bloque[256], real_T c1_fs)
{
  real_T c1_nota;
  uint32_T c1_debug_family_var_map[32];
  real_T c1_aux_window[256];
  real_T c1_bloque_ruido[256];
  real_T c1_fft_y[513];
  real_T c1_fft_x[513];
  real_T c1_fft_y1[513];
  real_T c1_fft_y2[513];
  real_T c1_fft_anterior[513];
  real_T c1_fft_actual[513];
  real_T c1_diff_fft[513];
  real_T c1_abs_diff_fft[513];
  real_T c1_sum_diff_fft;
  real_T c1_sum_abs_diff_fft;
  real_T c1_div_param;
  real_T c1_suma_param;
  real_T c1_w_len;
  real_T c1_salto;
  real_T c1_nargin = 4.0;
  real_T c1_nargout = 1.0;
  int32_T c1_i15;
  static real_T c1_dv5[1024] = { 0.0, 9.4123586994454556E-6,
    3.7649080427748505E-5, 8.47091020882984E-5, 0.00015059065189787502,
    0.00023529124945342872, 0.00033880770582522812, 0.00046113612367731927,
    0.0006022718974137975, 0.00076220971335261289, 0.00094094354992541041,
    0.0011384666779041819, 0.0013547716606548965, 0.001589850354417166,
    0.0018436939086109994, 0.0021162927661700914, 0.0024076366639015356,
    0.0027177146328722923, 0.0030465149988219697, 0.00339402538260275,
    0.0037602327006450165, 0.0041451231654502374, 0.0045486822861099951,
    0.0049708948688514387, 0.0054117450176094928, 0.0058712161346252678,
    0.0063492909210707826, 0.0068459513777006653, 0.0073611788055293892,
    0.0078949538065354874, 0.0084472562843918575, 0.0090180654452223785,
    0.0096073597983847847, 0.010215117157279741, 0.010841314640186173,
    0.011485928671122803, 0.012148934980735715, 0.012830308607212071,
    0.013530023897219912, 0.014248054506874108, 0.014984373402728013,
    0.015738952862791367, 0.016511764477573965, 0.0173027791511553,
    0.01811196710228008, 0.01893929786547921, 0.019784740292217107,
    0.0206482625520642, 0.021529832133895588, 0.022429415847114609,
    0.023346979822903069, 0.024282489515495831, 0.025235909703481663,
    0.026207204491129454, 0.02719633730973936, 0.028203270919019807,
    0.029227967408489597, 0.030270388198905041, 0.03133049404371252,
    0.032408245030526195, 0.033503600582630522, 0.034616519460508144,
    0.035746959763392205, 0.03689487893084431, 0.038060233744356631,
    0.039242980328979049, 0.040443074154971115, 0.041660470039478648,
    0.042895122148234655, 0.044146983997285061, 0.04541600845473881,
    0.046702147742542333, 0.048005353438278331, 0.049325576476988986,
    0.050662767153023092, 0.052016875121907391, 0.053387849402242338,
    0.054775638377621061, 0.056180189798573033, 0.057601450784531105,
    0.059039367825822475, 0.060493886785683237, 0.0619649529022967,
    0.063452510790854955, 0.06495650444564427, 0.066476877242153676,
    0.068013571939206652, 0.069566530681116345, 0.071135694999863941,
    0.072721005817299733, 0.0743224034473674, 0.075939827598351384,
    0.077573217375146442, 0.079222511281550778, 0.080887647222580961,
    0.08256856250681, 0.084265193848727382, 0.0859774773711221,
    0.087705348607487355, 0.089448742504447676, 0.091207593424208144,
    0.0929818351470258, 0.094771400873702616, 0.096576223228100333,
    0.098396234259677529, 0.10023136544604749, 0.10208154769555822,
    0.10394671134989381, 0.10582678618669683, 0.10772170142221238,
    0.10963138571395276, 0.11155576716338378, 0.1134947733186315,
    0.11544833117721015, 0.11741636718877052, 0.11939880725786911,
    0.12139557674675772, 0.12340660047819374, 0.12543180273827031,
    0.12747110727926703, 0.12952443732252039, 0.1315917155613151,
    0.13367286416379359, 0.1357678047758874, 0.1378764585242665,
    0.13999874601930917, 0.1421345873580907, 0.14428390212739178,
    0.14644660940672621, 0.14862262777138735, 0.15081187529551354,
    0.153014269555173, 0.15522972763146653, 0.15745816611364982,
    0.15969950110227343, 0.16195364821234198, 0.16422052257649078,
    0.16650003884818126, 0.16879211120491411, 0.17109665335146063,
    0.17341357852311157, 0.17574279948894372, 0.17808422855510425,
    0.18043777756811213, 0.18280335791817726, 0.18518088054253645,
    0.18757025592880677, 0.1899713941183554, 0.19238420470968659,
    0.19480859686184526, 0.19724447929783723, 0.19969176030806551,
    0.20215034775378327, 0.20462014907056286, 0.20710107127178057,
    0.20959302095211774, 0.21209590429107733, 0.21460962705651632,
    0.21713409460819338, 0.21966921190133198, 0.22221488349019886,
    0.22477101353169759, 0.22733750578897677, 0.22991426363505352,
    0.23250119005645137, 0.23509818765685259, 0.23770515866076558,
    0.24032200491720523, 0.24294862790338917, 0.24558492872844645,
    0.24823080813714121, 0.25088616651360907, 0.25355090388510793,
    0.256224919925782, 0.25890811396043856, 0.26160038496833887,
    0.2643016315870011, 0.26701175211601691, 0.26973064452088,
    0.27245820643682805, 0.2751943351726967, 0.27793892771478534,
    0.28069188073073614, 0.283453090573424, 0.2862224532848589,
    0.28899986460010008, 0.29178521995118134, 0.29457841447104804,
    0.29737934299750507, 0.30018790007717661, 0.30300397996947592,
    0.30582747665058685, 0.30865828381745508, 0.31149629489179087,
    0.3143414030240812, 0.317193501097613, 0.32005248173250589,
    0.32291823728975477, 0.32579065987528277, 0.32866964134400278,
    0.33155507330389, 0.33444684712006179, 0.33734485391886848,
    0.34024898459199215, 0.34315912980055419, 0.34607517997923254,
    0.3489970253403859, 0.35192455587818805, 0.35485766137276886,
    0.35779623139436412, 0.3607401553074735, 0.36368932227502548,
    0.36664362126255079, 0.36960294104236224, 0.37256717019774266,
    0.37553619712713987, 0.378509910048368, 0.38148819700281633,
    0.38447094585966435, 0.38745804432010361, 0.39044937992156514,
    0.39344484004195435, 0.39644431190389073, 0.399447682578954,
    0.40245483899193585, 0.40546566792509686, 0.40848005602242948,
    0.41149788979392554, 0.41451905561984931, 0.41754343975501496,
    0.4205709283330693, 0.42360140737077828, 0.42663476277231915,
    0.42967088033357537, 0.43270964574643689, 0.43575094460310337,
    0.43879466240039189, 0.44184068454404757, 0.44488889635305839,
    0.44793918306397262, 0.45099142983521961, 0.45404552175143365,
    0.45710134382778006, 0.46015878101428492, 0.46321771820016627,
    0.46627804021816793, 0.46933963184889566, 0.472402377825155,
    0.47546616283629095, 0.47853087153252954, 0.48159638852932052,
    0.48466259841168169, 0.48772938573854385, 0.49079663504709758,
    0.49386423085714004, 0.49693205767542276, 0.49999999999999994,
    0.50306794232457719, 0.50613576914286, 0.5092033649529023, 0.512270614261456,
    0.5153374015883182, 0.51840361147067948, 0.5214691284674704,
    0.524533837163709, 0.527597622174845, 0.53066036815110429, 0.533721959781832,
    0.53678228179983367, 0.539841218985715, 0.54289865617221988,
    0.54595447824856624, 0.54900857016478033, 0.55206081693602727,
    0.55511110364694149, 0.55815931545595232, 0.56120533759960811,
    0.56424905539689652, 0.567290354253563, 0.57032911966642452,
    0.57336523722768085, 0.57639859262922166, 0.57942907166693058,
    0.58245656024498493, 0.58548094438015064, 0.58850211020607435,
    0.59151994397757046, 0.594534332074903, 0.5975451610080641,
    0.60055231742104587, 0.60355568809610927, 0.60655515995804565,
    0.60955062007843486, 0.61254195567989633, 0.61552905414033554,
    0.61851180299718367, 0.62149008995163191, 0.62446380287286007,
    0.62743282980225723, 0.63039705895763776, 0.63335637873744921,
    0.63631067772497441, 0.6392598446925265, 0.64220376860563588,
    0.645142338627231, 0.648075444121812, 0.651002974659614, 0.65392482002076746,
    0.6568408701994457, 0.65975101540800785, 0.66265514608113141,
    0.6655531528799381, 0.66844492669611, 0.67133035865599711,
    0.67420934012471723, 0.67708176271024523, 0.67994751826749411,
    0.682806498902387, 0.6856585969759188, 0.68850370510820913,
    0.69134171618254481, 0.69417252334941315, 0.696996020030524,
    0.69981209992282334, 0.70262065700249487, 0.70542158552895184,
    0.70821478004881855, 0.71100013539989981, 0.71377754671514093,
    0.716546909426576, 0.71930811926926363, 0.72206107228521454,
    0.72480566482730335, 0.72754179356317183, 0.73026935547912009,
    0.732988247883983, 0.73569836841299885, 0.738399615031661,
    0.74109188603956133, 0.74377508007421789, 0.746449096114892,
    0.74911383348639082, 0.75176919186285873, 0.75441507127155361,
    0.75705137209661078, 0.75967799508279477, 0.76229484133923431,
    0.76490181234314736, 0.76749880994354847, 0.77008573636494648,
    0.77266249421102318, 0.77522898646830241, 0.777785116509801,
    0.780330788098668, 0.78286590539180656, 0.78539037294348357,
    0.78790409570892272, 0.79040697904788226, 0.79289892872821943,
    0.795379850929437, 0.79784965224621662, 0.80030823969193432,
    0.80275552070216272, 0.80519140313815485, 0.80761579529031335,
    0.8100286058816446, 0.81242974407119317, 0.81481911945746355,
    0.81719664208182263, 0.81956222243188792, 0.82191577144489569,
    0.82425720051105622, 0.82658642147688832, 0.82890334664853937,
    0.831207888795086, 0.83349996115181868, 0.83577947742350922,
    0.838046351787658, 0.84030049889772651, 0.84254183388635018,
    0.84477027236853353, 0.846985730444827, 0.84918812470448635,
    0.85137737222861254, 0.85355339059327373, 0.85571609787260827,
    0.8578654126419093, 0.86000125398069083, 0.86212354147573333,
    0.86423219522411254, 0.86632713583620635, 0.8684082844386849,
    0.87047556267747939, 0.872528892720733, 0.87456819726172963,
    0.87659339952180626, 0.87860442325324239, 0.88060119274213089,
    0.88258363281122953, 0.88455166882278968, 0.88650522668136844,
    0.88844423283661622, 0.89036861428604719, 0.89227829857778751,
    0.89417321381330317, 0.896053288650106, 0.89791845230444167,
    0.89976863455395262, 0.90160376574032242, 0.90342377677189967,
    0.90522859912629738, 0.90701816485297426, 0.90879240657579174,
    0.91055125749555232, 0.91229465139251253, 0.91402252262887784,
    0.91573480615127267, 0.91743143749319, 0.919112352777419,
    0.92077748871844922, 0.92242678262485356, 0.92406017240164862,
    0.9256775965526326, 0.92727899418270021, 0.928864305000136,
    0.9304334693188836, 0.93198642806079335, 0.93352312275784632,
    0.93504349555435562, 0.936547489209145, 0.93803504709770325,
    0.93950611321431676, 0.94096063217417747, 0.942398549215469,
    0.94381981020142691, 0.945224361622379, 0.94661215059775761,
    0.94798312487809255, 0.94933723284697691, 0.9506744235230109,
    0.95199464656172172, 0.95329785225745767, 0.95458399154526119,
    0.95585301600271488, 0.95710487785176535, 0.9583395299605213,
    0.95955692584502894, 0.9607570196710209, 0.96193976625564337,
    0.96310512106915569, 0.96425304023660774, 0.96538348053949186,
    0.96649639941736942, 0.96759175496947381, 0.96866950595628742,
    0.969729611801095, 0.97077203259151035, 0.97179672908098014,
    0.97280366269026053, 0.97379279550887055, 0.97476409029651834,
    0.97571751048450417, 0.97665302017709688, 0.97757058415288534,
    0.97847016786610441, 0.97935173744793569, 0.98021525970778289,
    0.98106070213452079, 0.98188803289772, 0.9826972208488447, 0.983488235522426,
    0.98426104713720863, 0.985015626597272, 0.98575194549312584,
    0.98646997610278, 0.98716969139278787, 0.98785106501926423,
    0.98851407132887714, 0.98915868535981377, 0.98978488284272026,
    0.99039264020161522, 0.99098193455477768, 0.9915527437156082,
    0.99210504619346451, 0.99263882119447056, 0.99315404862229928,
    0.99365070907892916, 0.99412878386537473, 0.99458825498239056,
    0.99502910513114851, 0.99545131771389, 0.99585487683454976,
    0.996239767299355, 0.99660597461739719, 0.99695348500117809,
    0.99728228536712771, 0.99759236333609835, 0.99788370723382991,
    0.998156306091389, 0.99841014964558283, 0.9986452283393451,
    0.99886153332209582, 0.99905905645007453, 0.99923779028664739,
    0.9993977281025862, 0.99953886387632274, 0.99966119229417472,
    0.99976470875054657, 0.99984940934810207, 0.99991529089791165,
    0.99996235091957231, 0.99999058764130055, 1.0, 0.99999058764130055,
    0.99996235091957231, 0.99991529089791165, 0.99984940934810207,
    0.99976470875054657, 0.99966119229417472, 0.99953886387632274,
    0.9993977281025862, 0.99923779028664739, 0.99905905645007453,
    0.99886153332209582, 0.9986452283393451, 0.99841014964558283,
    0.998156306091389, 0.99788370723382991, 0.99759236333609835,
    0.99728228536712771, 0.99695348500117809, 0.99660597461739719,
    0.996239767299355, 0.99585487683454976, 0.99545131771389,
    0.99502910513114851, 0.99458825498239056, 0.99412878386537473,
    0.99365070907892916, 0.99315404862229928, 0.99263882119447056,
    0.99210504619346451, 0.9915527437156082, 0.99098193455477768,
    0.99039264020161522, 0.98978488284272026, 0.98915868535981377,
    0.98851407132887714, 0.98785106501926423, 0.98716969139278787,
    0.98646997610278, 0.98575194549312584, 0.985015626597272,
    0.98426104713720863, 0.983488235522426, 0.9826972208488447, 0.98188803289772,
    0.98106070213452079, 0.98021525970778289, 0.97935173744793569,
    0.97847016786610441, 0.97757058415288534, 0.97665302017709688,
    0.97571751048450417, 0.97476409029651834, 0.97379279550887055,
    0.97280366269026053, 0.97179672908098014, 0.97077203259151035,
    0.969729611801095, 0.96866950595628742, 0.96759175496947381,
    0.96649639941736942, 0.96538348053949186, 0.96425304023660774,
    0.96310512106915569, 0.96193976625564337, 0.9607570196710209,
    0.95955692584502894, 0.9583395299605213, 0.95710487785176535,
    0.95585301600271488, 0.95458399154526119, 0.95329785225745767,
    0.95199464656172172, 0.9506744235230109, 0.94933723284697691,
    0.94798312487809255, 0.94661215059775761, 0.945224361622379,
    0.94381981020142691, 0.942398549215469, 0.94096063217417747,
    0.93950611321431676, 0.93803504709770325, 0.936547489209145,
    0.93504349555435562, 0.93352312275784632, 0.93198642806079335,
    0.9304334693188836, 0.928864305000136, 0.92727899418270021,
    0.9256775965526326, 0.92406017240164862, 0.92242678262485356,
    0.92077748871844922, 0.919112352777419, 0.91743143749319,
    0.91573480615127267, 0.91402252262887784, 0.91229465139251253,
    0.91055125749555232, 0.90879240657579174, 0.90701816485297426,
    0.90522859912629738, 0.90342377677189967, 0.90160376574032242,
    0.89976863455395262, 0.89791845230444167, 0.896053288650106,
    0.89417321381330317, 0.89227829857778751, 0.89036861428604719,
    0.88844423283661622, 0.88650522668136844, 0.88455166882278968,
    0.88258363281122953, 0.88060119274213089, 0.87860442325324239,
    0.87659339952180626, 0.87456819726172963, 0.872528892720733,
    0.87047556267747939, 0.8684082844386849, 0.86632713583620635,
    0.86423219522411254, 0.86212354147573333, 0.86000125398069083,
    0.8578654126419093, 0.85571609787260827, 0.85355339059327373,
    0.85137737222861254, 0.84918812470448635, 0.846985730444827,
    0.84477027236853353, 0.84254183388635018, 0.84030049889772651,
    0.838046351787658, 0.83577947742350922, 0.83349996115181868,
    0.831207888795086, 0.82890334664853937, 0.82658642147688832,
    0.82425720051105622, 0.82191577144489569, 0.81956222243188792,
    0.81719664208182263, 0.81481911945746355, 0.81242974407119317,
    0.8100286058816446, 0.80761579529031335, 0.80519140313815485,
    0.80275552070216272, 0.80030823969193432, 0.79784965224621662,
    0.795379850929437, 0.79289892872821943, 0.79040697904788226,
    0.78790409570892272, 0.78539037294348357, 0.78286590539180656,
    0.780330788098668, 0.777785116509801, 0.77522898646830241,
    0.77266249421102318, 0.77008573636494648, 0.76749880994354847,
    0.76490181234314736, 0.76229484133923431, 0.75967799508279477,
    0.75705137209661078, 0.75441507127155361, 0.75176919186285873,
    0.74911383348639082, 0.746449096114892, 0.74377508007421789,
    0.74109188603956133, 0.738399615031661, 0.73569836841299885,
    0.732988247883983, 0.73026935547912009, 0.72754179356317183,
    0.72480566482730335, 0.72206107228521454, 0.71930811926926363,
    0.716546909426576, 0.71377754671514093, 0.71100013539989981,
    0.70821478004881855, 0.70542158552895184, 0.70262065700249487,
    0.69981209992282334, 0.696996020030524, 0.69417252334941315,
    0.69134171618254481, 0.68850370510820913, 0.6856585969759188,
    0.682806498902387, 0.67994751826749411, 0.67708176271024523,
    0.67420934012471723, 0.67133035865599711, 0.66844492669611,
    0.6655531528799381, 0.66265514608113141, 0.65975101540800785,
    0.6568408701994457, 0.65392482002076746, 0.651002974659614,
    0.648075444121812, 0.645142338627231, 0.64220376860563588,
    0.6392598446925265, 0.63631067772497441, 0.63335637873744921,
    0.63039705895763776, 0.62743282980225723, 0.62446380287286007,
    0.62149008995163191, 0.61851180299718367, 0.61552905414033554,
    0.61254195567989633, 0.60955062007843486, 0.60655515995804565,
    0.60355568809610927, 0.60055231742104587, 0.5975451610080641,
    0.594534332074903, 0.59151994397757046, 0.58850211020607435,
    0.58548094438015064, 0.58245656024498493, 0.57942907166693058,
    0.57639859262922166, 0.57336523722768085, 0.57032911966642452,
    0.567290354253563, 0.56424905539689652, 0.56120533759960811,
    0.55815931545595232, 0.55511110364694149, 0.55206081693602727,
    0.54900857016478033, 0.54595447824856624, 0.54289865617221988,
    0.539841218985715, 0.53678228179983367, 0.533721959781832,
    0.53066036815110429, 0.527597622174845, 0.524533837163709,
    0.5214691284674704, 0.51840361147067948, 0.5153374015883182,
    0.512270614261456, 0.5092033649529023, 0.50613576914286, 0.50306794232457719,
    0.49999999999999994, 0.49693205767542276, 0.49386423085714004,
    0.49079663504709758, 0.48772938573854385, 0.48466259841168169,
    0.48159638852932052, 0.47853087153252954, 0.47546616283629095,
    0.472402377825155, 0.46933963184889566, 0.46627804021816793,
    0.46321771820016627, 0.46015878101428492, 0.45710134382778006,
    0.45404552175143365, 0.45099142983521961, 0.44793918306397262,
    0.44488889635305839, 0.44184068454404757, 0.43879466240039189,
    0.43575094460310337, 0.43270964574643689, 0.42967088033357537,
    0.42663476277231915, 0.42360140737077828, 0.4205709283330693,
    0.41754343975501496, 0.41451905561984931, 0.41149788979392554,
    0.40848005602242948, 0.40546566792509686, 0.40245483899193585,
    0.399447682578954, 0.39644431190389073, 0.39344484004195435,
    0.39044937992156514, 0.38745804432010361, 0.38447094585966435,
    0.38148819700281633, 0.378509910048368, 0.37553619712713987,
    0.37256717019774266, 0.36960294104236224, 0.36664362126255079,
    0.36368932227502548, 0.3607401553074735, 0.35779623139436412,
    0.35485766137276886, 0.35192455587818805, 0.3489970253403859,
    0.34607517997923254, 0.34315912980055419, 0.34024898459199215,
    0.33734485391886848, 0.33444684712006179, 0.33155507330389,
    0.32866964134400278, 0.32579065987528277, 0.32291823728975477,
    0.32005248173250589, 0.317193501097613, 0.3143414030240812,
    0.31149629489179087, 0.30865828381745508, 0.30582747665058685,
    0.30300397996947592, 0.30018790007717661, 0.29737934299750507,
    0.29457841447104804, 0.29178521995118134, 0.28899986460010008,
    0.2862224532848589, 0.283453090573424, 0.28069188073073614,
    0.27793892771478534, 0.2751943351726967, 0.27245820643682805,
    0.26973064452088, 0.26701175211601691, 0.2643016315870011,
    0.26160038496833887, 0.25890811396043856, 0.256224919925782,
    0.25355090388510793, 0.25088616651360907, 0.24823080813714121,
    0.24558492872844645, 0.24294862790338917, 0.24032200491720523,
    0.23770515866076558, 0.23509818765685259, 0.23250119005645137,
    0.22991426363505352, 0.22733750578897677, 0.22477101353169759,
    0.22221488349019886, 0.21966921190133198, 0.21713409460819338,
    0.21460962705651632, 0.21209590429107733, 0.20959302095211774,
    0.20710107127178057, 0.20462014907056286, 0.20215034775378327,
    0.19969176030806551, 0.19724447929783723, 0.19480859686184526,
    0.19238420470968659, 0.1899713941183554, 0.18757025592880677,
    0.18518088054253645, 0.18280335791817726, 0.18043777756811213,
    0.17808422855510425, 0.17574279948894372, 0.17341357852311157,
    0.17109665335146063, 0.16879211120491411, 0.16650003884818126,
    0.16422052257649078, 0.16195364821234198, 0.15969950110227343,
    0.15745816611364982, 0.15522972763146653, 0.153014269555173,
    0.15081187529551354, 0.14862262777138735, 0.14644660940672621,
    0.14428390212739178, 0.1421345873580907, 0.13999874601930917,
    0.1378764585242665, 0.1357678047758874, 0.13367286416379359,
    0.1315917155613151, 0.12952443732252039, 0.12747110727926703,
    0.12543180273827031, 0.12340660047819374, 0.12139557674675772,
    0.11939880725786911, 0.11741636718877052, 0.11544833117721015,
    0.1134947733186315, 0.11155576716338378, 0.10963138571395276,
    0.10772170142221238, 0.10582678618669683, 0.10394671134989381,
    0.10208154769555822, 0.10023136544604749, 0.098396234259677529,
    0.096576223228100333, 0.094771400873702616, 0.0929818351470258,
    0.091207593424208144, 0.089448742504447676, 0.087705348607487355,
    0.0859774773711221, 0.084265193848727382, 0.08256856250681,
    0.080887647222580961, 0.079222511281550778, 0.077573217375146442,
    0.075939827598351384, 0.0743224034473674, 0.072721005817299733,
    0.071135694999863941, 0.069566530681116345, 0.068013571939206652,
    0.066476877242153676, 0.06495650444564427, 0.063452510790854955,
    0.0619649529022967, 0.060493886785683237, 0.059039367825822475,
    0.057601450784531105, 0.056180189798573033, 0.054775638377621061,
    0.053387849402242338, 0.052016875121907391, 0.050662767153023092,
    0.049325576476988986, 0.048005353438278331, 0.046702147742542333,
    0.04541600845473881, 0.044146983997285061, 0.042895122148234655,
    0.041660470039478648, 0.040443074154971115, 0.039242980328979049,
    0.038060233744356631, 0.03689487893084431, 0.035746959763392205,
    0.034616519460508144, 0.033503600582630522, 0.032408245030526195,
    0.03133049404371252, 0.030270388198905041, 0.029227967408489597,
    0.028203270919019807, 0.02719633730973936, 0.026207204491129454,
    0.025235909703481663, 0.024282489515495831, 0.023346979822903069,
    0.022429415847114609, 0.021529832133895588, 0.0206482625520642,
    0.019784740292217107, 0.01893929786547921, 0.01811196710228008,
    0.0173027791511553, 0.016511764477573965, 0.015738952862791367,
    0.014984373402728013, 0.014248054506874108, 0.013530023897219912,
    0.012830308607212071, 0.012148934980735715, 0.011485928671122803,
    0.010841314640186173, 0.010215117157279741, 0.0096073597983847847,
    0.0090180654452223785, 0.0084472562843918575, 0.0078949538065354874,
    0.0073611788055293892, 0.0068459513777006653, 0.0063492909210707826,
    0.0058712161346252678, 0.0054117450176094928, 0.0049708948688514387,
    0.0045486822861099951, 0.0041451231654502374, 0.0037602327006450165,
    0.00339402538260275, 0.0030465149988219697, 0.0027177146328722923,
    0.0024076366639015356, 0.0021162927661700914, 0.0018436939086109994,
    0.001589850354417166, 0.0013547716606548965, 0.0011384666779041819,
    0.00094094354992541041, 0.00076220971335261289, 0.0006022718974137975,
    0.00046113612367731927, 0.00033880770582522812, 0.00023529124945342872,
    0.00015059065189787502, 8.47091020882984E-5, 3.7649080427748505E-5,
    9.4123586994454556E-6 };

  int32_T c1_i16;
  static real_T c1_dv6[256] = { 0.0, 0.00015059065189787502,
    0.0006022718974137975, 0.0013547716606548965, 0.0024076366639015356,
    0.0037602327006450165, 0.0054117450176094928, 0.0073611788055293892,
    0.0096073597983847847, 0.012148934980735715, 0.014984373402728013,
    0.01811196710228008, 0.021529832133895588, 0.025235909703481663,
    0.029227967408489597, 0.033503600582630522, 0.038060233744356631,
    0.042895122148234655, 0.048005353438278331, 0.053387849402242338,
    0.059039367825822475, 0.06495650444564427, 0.071135694999863941,
    0.077573217375146442, 0.084265193848727382, 0.091207593424208144,
    0.098396234259677529, 0.10582678618669683, 0.1134947733186315,
    0.12139557674675772, 0.12952443732252039, 0.1378764585242665,
    0.14644660940672621, 0.15522972763146653, 0.16422052257649078,
    0.17341357852311157, 0.18280335791817726, 0.19238420470968659,
    0.20215034775378327, 0.21209590429107733, 0.22221488349019886,
    0.23250119005645137, 0.24294862790338917, 0.25355090388510793,
    0.2643016315870011, 0.2751943351726967, 0.2862224532848589,
    0.29737934299750507, 0.30865828381745508, 0.32005248173250589,
    0.33155507330389, 0.34315912980055419, 0.35485766137276886,
    0.36664362126255079, 0.378509910048368, 0.39044937992156514,
    0.40245483899193585, 0.41451905561984931, 0.42663476277231915,
    0.43879466240039189, 0.45099142983521961, 0.46321771820016627,
    0.47546616283629095, 0.48772938573854385, 0.49999999999999994,
    0.512270614261456, 0.524533837163709, 0.53678228179983367,
    0.54900857016478033, 0.56120533759960811, 0.57336523722768085,
    0.58548094438015064, 0.5975451610080641, 0.60955062007843486,
    0.62149008995163191, 0.63335637873744921, 0.645142338627231,
    0.6568408701994457, 0.66844492669611, 0.67994751826749411,
    0.69134171618254481, 0.70262065700249487, 0.71377754671514093,
    0.72480566482730335, 0.73569836841299885, 0.746449096114892,
    0.75705137209661078, 0.76749880994354847, 0.777785116509801,
    0.78790409570892272, 0.79784965224621662, 0.80761579529031335,
    0.81719664208182263, 0.82658642147688832, 0.83577947742350922,
    0.84477027236853353, 0.85355339059327373, 0.86212354147573333,
    0.87047556267747939, 0.87860442325324239, 0.88650522668136844,
    0.89417321381330317, 0.90160376574032242, 0.90879240657579174,
    0.91573480615127267, 0.92242678262485356, 0.928864305000136,
    0.93504349555435562, 0.94096063217417747, 0.94661215059775761,
    0.95199464656172172, 0.95710487785176535, 0.96193976625564337,
    0.96649639941736942, 0.97077203259151035, 0.97476409029651834,
    0.97847016786610441, 0.98188803289772, 0.985015626597272,
    0.98785106501926423, 0.99039264020161522, 0.99263882119447056,
    0.99458825498239056, 0.996239767299355, 0.99759236333609835,
    0.9986452283393451, 0.9993977281025862, 0.99984940934810207, 1.0,
    0.99984940934810207, 0.9993977281025862, 0.9986452283393451,
    0.99759236333609835, 0.996239767299355, 0.99458825498239056,
    0.99263882119447056, 0.99039264020161522, 0.98785106501926423,
    0.985015626597272, 0.98188803289772, 0.97847016786610441,
    0.97476409029651834, 0.97077203259151035, 0.96649639941736942,
    0.96193976625564337, 0.95710487785176535, 0.95199464656172172,
    0.94661215059775761, 0.94096063217417747, 0.93504349555435562,
    0.928864305000136, 0.92242678262485356, 0.91573480615127267,
    0.90879240657579174, 0.90160376574032242, 0.89417321381330317,
    0.88650522668136844, 0.87860442325324239, 0.87047556267747939,
    0.86212354147573333, 0.85355339059327373, 0.84477027236853353,
    0.83577947742350922, 0.82658642147688832, 0.81719664208182263,
    0.80761579529031335, 0.79784965224621662, 0.78790409570892272,
    0.777785116509801, 0.76749880994354847, 0.75705137209661078,
    0.746449096114892, 0.73569836841299885, 0.72480566482730335,
    0.71377754671514093, 0.70262065700249487, 0.69134171618254481,
    0.67994751826749411, 0.66844492669611, 0.6568408701994457, 0.645142338627231,
    0.63335637873744921, 0.62149008995163191, 0.60955062007843486,
    0.5975451610080641, 0.58548094438015064, 0.57336523722768085,
    0.56120533759960811, 0.54900857016478033, 0.53678228179983367,
    0.524533837163709, 0.512270614261456, 0.49999999999999994,
    0.48772938573854385, 0.47546616283629095, 0.46321771820016627,
    0.45099142983521961, 0.43879466240039189, 0.42663476277231915,
    0.41451905561984931, 0.40245483899193585, 0.39044937992156514,
    0.378509910048368, 0.36664362126255079, 0.35485766137276886,
    0.34315912980055419, 0.33155507330389, 0.32005248173250589,
    0.30865828381745508, 0.29737934299750507, 0.2862224532848589,
    0.2751943351726967, 0.2643016315870011, 0.25355090388510793,
    0.24294862790338917, 0.23250119005645137, 0.22221488349019886,
    0.21209590429107733, 0.20215034775378327, 0.19238420470968659,
    0.18280335791817726, 0.17341357852311157, 0.16422052257649078,
    0.15522972763146653, 0.14644660940672621, 0.1378764585242665,
    0.12952443732252039, 0.12139557674675772, 0.1134947733186315,
    0.10582678618669683, 0.098396234259677529, 0.091207593424208144,
    0.084265193848727382, 0.077573217375146442, 0.071135694999863941,
    0.06495650444564427, 0.059039367825822475, 0.053387849402242338,
    0.048005353438278331, 0.042895122148234655, 0.038060233744356631,
    0.033503600582630522, 0.029227967408489597, 0.025235909703481663,
    0.021529832133895588, 0.01811196710228008, 0.014984373402728013,
    0.012148934980735715, 0.0096073597983847847, 0.0073611788055293892,
    0.0054117450176094928, 0.0037602327006450165, 0.0024076366639015356,
    0.0013547716606548965, 0.0006022718974137975, 0.00015059065189787502 };

  int32_T c1_i17;
  int32_T c1_i18;
  int32_T c1_i19;
  real_T c1_b_bloque_ruido[256];
  real_T c1_b_fft_y[513];
  real_T c1_unusedU0[513];
  int32_T c1_i20;
  int32_T c1_i21;
  real_T c1_c_fft_y[513];
  int32_T c1_i22;
  real_T c1_d_fft_y[513];
  int32_T c1_i23;
  real_T c1_e_fft_y[513];
  int32_T c1_i24;
  int32_T c1_i25;
  int32_T c1_i26;
  int32_T c1_i27;
  real_T c1_dv7[1280];
  int32_T c1_i28;
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_i31;
  int32_T c1_i32;
  int32_T c1_i33;
  int32_T c1_i34;
  real_T c1_dv8[1024];
  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_i37;
  real_T c1_dv9[1024];
  int32_T c1_i38;
  int32_T c1_i39;
  real_T c1_b_fft_y1[513];
  real_T c1_dv10[513];
  int32_T c1_i40;
  int32_T c1_i41;
  real_T c1_b_fft_y2[513];
  real_T c1_dv11[513];
  int32_T c1_i42;
  int32_T c1_i43;
  int32_T c1_i44;
  real_T c1_b_fft_anterior[513];
  int32_T c1_i45;
  real_T c1_b_fft_actual[513];
  real_T c1_B;
  real_T c1_y;
  real_T c1_b_y;
  int32_T c1_i46;
  int32_T c1_i47;
  real_T c1_b_diff_fft[513];
  real_T c1_dv12[513];
  int32_T c1_i48;
  int32_T c1_i49;
  real_T c1_c_diff_fft[513];
  int32_T c1_i50;
  real_T c1_b_abs_diff_fft[513];
  real_T c1_A;
  real_T c1_b_B;
  real_T c1_x;
  real_T c1_c_y;
  real_T c1_b_x;
  real_T c1_d_y;
  real_T c1_hoistedGlobal;
  real_T c1_b;
  real_T c1_e_y;
  int32_T c1_i51;
  real_T c1_c_fft_anterior[513];
  real_T c1_b_hoistedGlobal;
  real_T c1_b_b;
  real_T c1_f_y;
  int32_T c1_i52;
  real_T c1_c_fft_actual[513];
  int32_T c1_i53;
  real_T c1_d_fft_anterior[513];
  int32_T c1_i54;
  real_T c1_d_fft_actual[513];
  int32_T c1_i55;
  real_T c1_e_fft_anterior[513];
  int32_T c1_i56;
  real_T c1_e_fft_actual[513];
  boolean_T guard1 = FALSE;
  boolean_T guard2 = FALSE;
  boolean_T guard3 = FALSE;
  boolean_T guard4 = FALSE;
  boolean_T guard5 = FALSE;
  boolean_T guard6 = FALSE;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 32U, 32U, c1_d_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_aux_window, 0U, c1_i_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_bloque_ruido, 1U, c1_i_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_y, 2U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_x, 3U, c1_h_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_y1, 4U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_y2, 5U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_anterior, 6U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_actual, 7U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_diff_fft, 8U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_abs_diff_fft, 9U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_sum_diff_fft, 10U,
    c1_c_sf_marshallOut, c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_sum_abs_diff_fft, 11U,
    c1_c_sf_marshallOut, c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_div_param, 12U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_suma_param, 13U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_w_len, 14U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_salto, 15U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 16U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 17U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_bloque, 18U, c1_i_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_fs, 19U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nota, 20U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c1_in_tot, 21U,
    c1_v_sf_marshallOut, c1_u_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c1_window, 22U,
    c1_u_sf_marshallOut, c1_t_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c1_bloque_ant, 23U,
    c1_t_sf_marshallOut, c1_s_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(chartInstance->c1_bloque_act, 24U,
    c1_s_sf_marshallOut, c1_r_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_ruido, 25U,
    c1_r_sf_marshallOut, c1_q_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_ruido_2, 26U,
    c1_q_sf_marshallOut, c1_p_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_piso_ruido, 27U,
    c1_p_sf_marshallOut, c1_o_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_nivel_param, 28U,
    c1_o_sf_marshallOut, c1_n_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_piso_div_2, 29U,
    c1_n_sf_marshallOut, c1_m_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_piso_suma_2, 30U,
    c1_m_sf_marshallOut, c1_l_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&chartInstance->c1_flag_nota, 31U,
    c1_l_sf_marshallOut, c1_k_sf_marshallIn);
  c1_salto = 256.0;
  c1_w_len = 1024.0;
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 3);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 4);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 5);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 6);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 7);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 8);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 9);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 10);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 11);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 12);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 13);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 15);
  if (CV_SCRIPT_IF(0, 0, !chartInstance->c1_window_not_empty)) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 16);
    c1_hanning(chartInstance);
    for (c1_i15 = 0; c1_i15 < 1024; c1_i15++) {
      chartInstance->c1_window[c1_i15] = c1_dv5[c1_i15];
    }

    chartInstance->c1_window_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 17);
    c1_b_hanning(chartInstance);
    for (c1_i16 = 0; c1_i16 < 256; c1_i16++) {
      c1_aux_window[c1_i16] = c1_dv6[c1_i16];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 18);
    for (c1_i17 = 0; c1_i17 < 256; c1_i17++) {
      c1_bloque_ruido[c1_i17] = c1_bloque[c1_i17];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 19);
    for (c1_i18 = 0; c1_i18 < 256; c1_i18++) {
      c1_bloque_ruido[c1_i18] *= c1_aux_window[c1_i18];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 20);
    for (c1_i19 = 0; c1_i19 < 256; c1_i19++) {
      c1_b_bloque_ruido[c1_i19] = c1_bloque_ruido[c1_i19];
    }

    c1_fft_abs(chartInstance, c1_b_bloque_ruido, c1_fs, c1_unusedU0, c1_b_fft_y);
    for (c1_i20 = 0; c1_i20 < 513; c1_i20++) {
      c1_fft_y[c1_i20] = c1_b_fft_y[c1_i20];
    }

    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 20);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 21);
    for (c1_i21 = 0; c1_i21 < 513; c1_i21++) {
      c1_c_fft_y[c1_i21] = c1_fft_y[c1_i21];
    }

    chartInstance->c1_ruido = c1_sum(chartInstance, c1_c_fft_y);
    chartInstance->c1_ruido_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 22);
    for (c1_i22 = 0; c1_i22 < 513; c1_i22++) {
      c1_d_fft_y[c1_i22] = c1_fft_y[c1_i22];
    }

    c1_power(chartInstance, c1_d_fft_y, c1_b_fft_y);
    for (c1_i23 = 0; c1_i23 < 513; c1_i23++) {
      c1_e_fft_y[c1_i23] = c1_b_fft_y[c1_i23];
    }

    chartInstance->c1_ruido_2 = c1_sum(chartInstance, c1_e_fft_y);
    chartInstance->c1_ruido_2_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 23);
    chartInstance->c1_flag_nota = 0.0;
    chartInstance->c1_flag_nota_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 25);
    chartInstance->c1_piso_ruido = 10.0;
    chartInstance->c1_piso_ruido_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 26);
    chartInstance->c1_nivel_param = 1.4;
    chartInstance->c1_nivel_param_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 27);
    chartInstance->c1_piso_div_2 = 0.6;
    chartInstance->c1_piso_div_2_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 28);
    chartInstance->c1_piso_suma_2 = 0.6;
    chartInstance->c1_piso_suma_2_not_empty = TRUE;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 32);
  if (CV_SCRIPT_IF(0, 1, !chartInstance->c1_bloque_ant_not_empty)) {
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 33);
    for (c1_i24 = 0; c1_i24 < 1024; c1_i24++) {
      chartInstance->c1_bloque_ant[c1_i24] = 0.0;
    }

    chartInstance->c1_bloque_ant_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 34);
    for (c1_i25 = 0; c1_i25 < 1024; c1_i25++) {
      chartInstance->c1_bloque_act[c1_i25] = 0.0;
    }

    chartInstance->c1_bloque_act_not_empty = TRUE;
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 35);
    for (c1_i26 = 0; c1_i26 < 1280; c1_i26++) {
      chartInstance->c1_in_tot[c1_i26] = 0.0;
    }

    chartInstance->c1_in_tot_not_empty = TRUE;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 38);
  for (c1_i27 = 0; c1_i27 < 1024; c1_i27++) {
    c1_dv7[c1_i27] = chartInstance->c1_in_tot[c1_i27 + 256];
  }

  for (c1_i28 = 0; c1_i28 < 256; c1_i28++) {
    c1_dv7[c1_i28 + 1024] = c1_bloque[c1_i28];
  }

  for (c1_i29 = 0; c1_i29 < 1280; c1_i29++) {
    chartInstance->c1_in_tot[c1_i29] = c1_dv7[c1_i29];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 40);
  for (c1_i30 = 0; c1_i30 < 1024; c1_i30++) {
    chartInstance->c1_bloque_act[c1_i30] = chartInstance->c1_in_tot[c1_i30 + 256];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 41);
  for (c1_i31 = 0; c1_i31 < 1024; c1_i31++) {
    chartInstance->c1_bloque_act[c1_i31] *= chartInstance->c1_window[c1_i31];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 43);
  for (c1_i32 = 0; c1_i32 < 1024; c1_i32++) {
    chartInstance->c1_bloque_ant[c1_i32] = chartInstance->c1_in_tot[c1_i32];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 44);
  for (c1_i33 = 0; c1_i33 < 1024; c1_i33++) {
    chartInstance->c1_bloque_ant[c1_i33] *= chartInstance->c1_window[c1_i33];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 47);
  for (c1_i34 = 0; c1_i34 < 1024; c1_i34++) {
    c1_dv8[c1_i34] = chartInstance->c1_bloque_ant[c1_i34];
  }

  c1_b_fft_abs(chartInstance, c1_dv8, c1_fs, c1_unusedU0, c1_b_fft_y);
  for (c1_i35 = 0; c1_i35 < 513; c1_i35++) {
    c1_fft_x[c1_i35] = c1_unusedU0[c1_i35];
  }

  for (c1_i36 = 0; c1_i36 < 513; c1_i36++) {
    c1_fft_y1[c1_i36] = c1_b_fft_y[c1_i36];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 48);
  for (c1_i37 = 0; c1_i37 < 1024; c1_i37++) {
    c1_dv9[c1_i37] = chartInstance->c1_bloque_act[c1_i37];
  }

  c1_b_fft_abs(chartInstance, c1_dv9, c1_fs, c1_unusedU0, c1_b_fft_y);
  for (c1_i38 = 0; c1_i38 < 513; c1_i38++) {
    c1_fft_y2[c1_i38] = c1_b_fft_y[c1_i38];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 48);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 51);
  for (c1_i39 = 0; c1_i39 < 513; c1_i39++) {
    c1_b_fft_y1[c1_i39] = c1_fft_y1[c1_i39];
  }

  c1_power(chartInstance, c1_b_fft_y1, c1_dv10);
  for (c1_i40 = 0; c1_i40 < 513; c1_i40++) {
    c1_fft_anterior[c1_i40] = c1_dv10[c1_i40];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 52);
  for (c1_i41 = 0; c1_i41 < 513; c1_i41++) {
    c1_b_fft_y2[c1_i41] = c1_fft_y2[c1_i41];
  }

  c1_power(chartInstance, c1_b_fft_y2, c1_dv11);
  for (c1_i42 = 0; c1_i42 < 513; c1_i42++) {
    c1_fft_actual[c1_i42] = c1_dv11[c1_i42];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 53);
  for (c1_i43 = 0; c1_i43 < 513; c1_i43++) {
    c1_b_fft_y[c1_i43] = c1_fft_actual[c1_i43] - c1_fft_anterior[c1_i43];
  }

  for (c1_i44 = 0; c1_i44 < 513; c1_i44++) {
    c1_b_fft_anterior[c1_i44] = c1_fft_anterior[c1_i44];
  }

  for (c1_i45 = 0; c1_i45 < 513; c1_i45++) {
    c1_b_fft_actual[c1_i45] = c1_fft_actual[c1_i45];
  }

  c1_B = c1_sum(chartInstance, c1_b_fft_anterior) + c1_sum(chartInstance,
    c1_b_fft_actual);
  c1_y = c1_B;
  c1_b_y = c1_y;
  for (c1_i46 = 0; c1_i46 < 513; c1_i46++) {
    c1_diff_fft[c1_i46] = c1_b_fft_y[c1_i46] / c1_b_y;
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 54);
  for (c1_i47 = 0; c1_i47 < 513; c1_i47++) {
    c1_b_diff_fft[c1_i47] = c1_diff_fft[c1_i47];
  }

  c1_b_abs(chartInstance, c1_b_diff_fft, c1_dv12);
  for (c1_i48 = 0; c1_i48 < 513; c1_i48++) {
    c1_abs_diff_fft[c1_i48] = c1_dv12[c1_i48];
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 56);
  for (c1_i49 = 0; c1_i49 < 513; c1_i49++) {
    c1_c_diff_fft[c1_i49] = c1_diff_fft[c1_i49];
  }

  c1_sum_diff_fft = c1_sum(chartInstance, c1_c_diff_fft);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 57);
  for (c1_i50 = 0; c1_i50 < 513; c1_i50++) {
    c1_b_abs_diff_fft[c1_i50] = c1_abs_diff_fft[c1_i50];
  }

  c1_sum_abs_diff_fft = c1_sum(chartInstance, c1_b_abs_diff_fft);
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 58);
  c1_A = c1_sum_diff_fft;
  c1_b_B = c1_sum_abs_diff_fft;
  c1_x = c1_A;
  c1_c_y = c1_b_B;
  c1_b_x = c1_x;
  c1_d_y = c1_c_y;
  c1_div_param = c1_b_x / c1_d_y;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 59);
  c1_suma_param = c1_sum_diff_fft + c1_sum_abs_diff_fft;
  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 63);
  c1_hoistedGlobal = chartInstance->c1_ruido_2;
  c1_b = c1_hoistedGlobal;
  c1_e_y = 10.0 * c1_b;
  for (c1_i51 = 0; c1_i51 < 513; c1_i51++) {
    c1_c_fft_anterior[c1_i51] = c1_fft_anterior[c1_i51];
  }

  guard1 = FALSE;
  if (CV_SCRIPT_COND(0, 0, c1_sum(chartInstance, c1_c_fft_anterior) > c1_e_y)) {
    guard1 = TRUE;
  } else {
    c1_b_hoistedGlobal = chartInstance->c1_ruido_2;
    c1_b_b = c1_b_hoistedGlobal;
    c1_f_y = 10.0 * c1_b_b;
    for (c1_i52 = 0; c1_i52 < 513; c1_i52++) {
      c1_c_fft_actual[c1_i52] = c1_fft_actual[c1_i52];
    }

    if (CV_SCRIPT_COND(0, 1, c1_sum(chartInstance, c1_c_fft_actual) > c1_f_y)) {
      guard1 = TRUE;
    } else {
      CV_SCRIPT_MCDC(0, 0, FALSE);
      CV_SCRIPT_IF(0, 2, FALSE);
      _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 88);
      c1_nota = 0.0;
      _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 89);
      chartInstance->c1_flag_nota = 0.0;
    }
  }

  if (guard1 == TRUE) {
    CV_SCRIPT_MCDC(0, 0, TRUE);
    CV_SCRIPT_IF(0, 2, TRUE);
    _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 67);
    for (c1_i53 = 0; c1_i53 < 513; c1_i53++) {
      c1_d_fft_anterior[c1_i53] = c1_fft_anterior[c1_i53];
    }

    guard2 = FALSE;
    guard3 = FALSE;
    if (CV_SCRIPT_COND(0, 2, c1_sum(chartInstance, c1_d_fft_anterior) >
                       chartInstance->c1_ruido)) {
      guard3 = TRUE;
    } else {
      for (c1_i54 = 0; c1_i54 < 513; c1_i54++) {
        c1_d_fft_actual[c1_i54] = c1_fft_actual[c1_i54];
      }

      if (CV_SCRIPT_COND(0, 3, c1_sum(chartInstance, c1_d_fft_actual) >
                         chartInstance->c1_ruido)) {
        guard3 = TRUE;
      } else {
        guard2 = TRUE;
      }
    }

    if (guard3 == TRUE) {
      if (CV_SCRIPT_COND(0, 4, (c1_div_param + c1_sum_abs_diff_fft) +
                         c1_suma_param > 1.4)) {
        CV_SCRIPT_MCDC(0, 1, TRUE);
        CV_SCRIPT_IF(0, 3, TRUE);
        _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 68);
        c1_nota = 2.0;
        _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 69);
        chartInstance->c1_flag_nota = 2.0;
      } else {
        guard2 = TRUE;
      }
    }

    if (guard2 == TRUE) {
      CV_SCRIPT_MCDC(0, 1, FALSE);
      CV_SCRIPT_IF(0, 3, FALSE);
      _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 73);
      for (c1_i55 = 0; c1_i55 < 513; c1_i55++) {
        c1_e_fft_anterior[c1_i55] = c1_fft_anterior[c1_i55];
      }

      guard4 = FALSE;
      guard5 = FALSE;
      guard6 = FALSE;
      if (CV_SCRIPT_COND(0, 5, c1_sum(chartInstance, c1_e_fft_anterior) <
                         chartInstance->c1_ruido)) {
        for (c1_i56 = 0; c1_i56 < 513; c1_i56++) {
          c1_e_fft_actual[c1_i56] = c1_fft_actual[c1_i56];
        }

        if (CV_SCRIPT_COND(0, 6, c1_sum(chartInstance, c1_e_fft_actual) <
                           chartInstance->c1_ruido)) {
          if (CV_SCRIPT_COND(0, 7, c1_div_param > 0.6)) {
            if (CV_SCRIPT_COND(0, 8, c1_suma_param > 0.6)) {
              CV_SCRIPT_MCDC(0, 2, TRUE);
              CV_SCRIPT_IF(0, 4, TRUE);
              _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 74);
              c1_nota = 2.0;
              _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 75);
              chartInstance->c1_flag_nota = 2.0;
            } else {
              guard4 = TRUE;
            }
          } else {
            guard5 = TRUE;
          }
        } else {
          guard6 = TRUE;
        }
      } else {
        guard6 = TRUE;
      }

      if (guard6 == TRUE) {
        guard5 = TRUE;
      }

      if (guard5 == TRUE) {
        guard4 = TRUE;
      }

      if (guard4 == TRUE) {
        CV_SCRIPT_MCDC(0, 2, FALSE);
        CV_SCRIPT_IF(0, 4, FALSE);
        _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 79);
        if (CV_SCRIPT_IF(0, 5, chartInstance->c1_flag_nota > 0.0)) {
          _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 80);
          c1_nota = 1.0;
          _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 81);
          chartInstance->c1_flag_nota = 1.0;
        } else {
          _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 83);
          c1_nota = 0.0;
          _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, 84);
          chartInstance->c1_flag_nota = 0.0;
        }
      }
    }
  }

  _SFD_SCRIPT_CALL(0U, chartInstance->c1_sfEvent, -89);
  _SFD_SYMBOL_SCOPE_POP();
  return c1_nota;
}

static void c1_fft_abs(SFc1_LedaInstanceStruct *chartInstance, real_T c1_signal
  [256], real_T c1_Fs, real_T c1_fft_x[513], real_T c1_fft_y[513])
{
  uint32_T c1_debug_family_var_map[10];
  real_T c1_L;
  real_T c1_NFFT;
  static creal_T c1_signal_f[1024];
  real_T c1_Length;
  real_T c1_nargin = 3.0;
  real_T c1_nargout = 2.0;
  int32_T c1_i57;
  real_T c1_b_signal[256];
  creal_T c1_A[1024];
  int32_T c1_i58;
  real_T c1_ar;
  real_T c1_ai;
  static creal_T c1_dc0 = { 1024.0, 0.0 };

  real_T c1_br;
  real_T c1_bi;
  real_T c1_brm;
  real_T c1_bim;
  real_T c1_s;
  real_T c1_d;
  real_T c1_nr;
  real_T c1_ni;
  real_T c1_sgnbr;
  real_T c1_sgnbi;
  real_T c1_b_A;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_y;
  real_T c1_a;
  int32_T c1_i59;
  int32_T c1_i60;
  creal_T c1_b_signal_f[513];
  real_T c1_dv13[513];
  int32_T c1_i61;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c1_b_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_L, 0U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_NFFT, 1U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_signal_f, 2U, c1_j_sf_marshallOut,
    c1_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Length, 3U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_signal, 6U, c1_i_sf_marshallOut,
    c1_h_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Fs, 7U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_x, 8U, c1_h_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_y, 9U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  c1_Length = 1024.0;
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 17);
  c1_L = 1024.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 18);
  c1_NFFT = 1024.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 21);
  for (c1_i57 = 0; c1_i57 < 256; c1_i57++) {
    c1_b_signal[c1_i57] = c1_signal[c1_i57];
  }

  c1_fft(chartInstance, c1_b_signal, c1_A);
  for (c1_i58 = 0; c1_i58 < 1024; c1_i58++) {
    c1_ar = c1_A[c1_i58].re;
    c1_ai = c1_A[c1_i58].im;
    c1_br = c1_dc0.re;
    c1_bi = c1_dc0.im;
    if (c1_bi == 0.0) {
      if (c1_ai == 0.0) {
        c1_signal_f[c1_i58].re = c1_ar / c1_br;
        c1_signal_f[c1_i58].im = 0.0;
      } else if (c1_ar == 0.0) {
        c1_signal_f[c1_i58].re = 0.0;
        c1_signal_f[c1_i58].im = c1_ai / c1_br;
      } else {
        c1_signal_f[c1_i58].re = c1_ar / c1_br;
        c1_signal_f[c1_i58].im = c1_ai / c1_br;
      }
    } else if (c1_br == 0.0) {
      if (c1_ar == 0.0) {
        c1_signal_f[c1_i58].re = c1_ai / c1_bi;
        c1_signal_f[c1_i58].im = 0.0;
      } else if (c1_ai == 0.0) {
        c1_signal_f[c1_i58].re = 0.0;
        c1_signal_f[c1_i58].im = -(c1_ar / c1_bi);
      } else {
        c1_signal_f[c1_i58].re = c1_ai / c1_bi;
        c1_signal_f[c1_i58].im = -(c1_ar / c1_bi);
      }
    } else {
      c1_brm = muDoubleScalarAbs(c1_br);
      c1_bim = muDoubleScalarAbs(c1_bi);
      if (c1_brm > c1_bim) {
        c1_s = c1_bi / c1_br;
        c1_d = c1_br + c1_s * c1_bi;
        c1_nr = c1_ar + c1_s * c1_ai;
        c1_ni = c1_ai - c1_s * c1_ar;
        c1_signal_f[c1_i58].re = c1_nr / c1_d;
        c1_signal_f[c1_i58].im = c1_ni / c1_d;
      } else if (c1_bim == c1_brm) {
        if (c1_br > 0.0) {
          c1_sgnbr = 0.5;
        } else {
          c1_sgnbr = -0.5;
        }

        if (c1_bi > 0.0) {
          c1_sgnbi = 0.5;
        } else {
          c1_sgnbi = -0.5;
        }

        c1_nr = c1_ar * c1_sgnbr + c1_ai * c1_sgnbi;
        c1_ni = c1_ai * c1_sgnbr - c1_ar * c1_sgnbi;
        c1_signal_f[c1_i58].re = c1_nr / c1_brm;
        c1_signal_f[c1_i58].im = c1_ni / c1_brm;
      } else {
        c1_s = c1_br / c1_bi;
        c1_d = c1_bi + c1_s * c1_br;
        c1_nr = c1_s * c1_ar + c1_ai;
        c1_ni = c1_s * c1_ai - c1_ar;
        c1_signal_f[c1_i58].re = c1_nr / c1_d;
        c1_signal_f[c1_i58].im = c1_ni / c1_d;
      }
    }
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 23);
  c1_b_A = c1_Fs;
  c1_x = c1_b_A;
  c1_b_x = c1_x;
  c1_y = c1_b_x / 2.0;
  c1_a = c1_y;
  for (c1_i59 = 0; c1_i59 < 513; c1_i59++) {
    c1_fft_x[c1_i59] = c1_a * (0.001953125 * (real_T)c1_i59);
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 24);
  for (c1_i60 = 0; c1_i60 < 513; c1_i60++) {
    c1_b_signal_f[c1_i60] = c1_signal_f[c1_i60];
  }

  c1_abs(chartInstance, c1_b_signal_f, c1_dv13);
  for (c1_i61 = 0; c1_i61 < 513; c1_i61++) {
    c1_fft_y[c1_i61] = c1_dv13[c1_i61];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -24);
  _SFD_SYMBOL_SCOPE_POP();
}

static void c1_b_fft_abs(SFc1_LedaInstanceStruct *chartInstance, real_T
  c1_signal[1024], real_T c1_Fs, real_T c1_fft_x[513], real_T c1_fft_y[513])
{
  uint32_T c1_debug_family_var_map[10];
  real_T c1_L;
  real_T c1_NFFT;
  static creal_T c1_signal_f[1024];
  real_T c1_Length;
  real_T c1_nargin = 3.0;
  real_T c1_nargout = 2.0;
  int32_T c1_i62;
  real_T c1_b_signal[1024];
  static creal_T c1_A[1024];
  int32_T c1_i63;
  real_T c1_ar;
  real_T c1_ai;
  static creal_T c1_dc1 = { 1024.0, 0.0 };

  real_T c1_br;
  real_T c1_bi;
  real_T c1_brm;
  real_T c1_bim;
  real_T c1_s;
  real_T c1_d;
  real_T c1_nr;
  real_T c1_ni;
  real_T c1_sgnbr;
  real_T c1_sgnbi;
  real_T c1_b_A;
  real_T c1_x;
  real_T c1_b_x;
  real_T c1_y;
  real_T c1_a;
  int32_T c1_i64;
  int32_T c1_i65;
  creal_T c1_b_signal_f[513];
  real_T c1_dv14[513];
  int32_T c1_i66;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c1_c_debug_family_names,
    c1_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_L, 0U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_NFFT, 1U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_signal_f, 2U, c1_j_sf_marshallOut,
    c1_i_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c1_Length, 3U, c1_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargin, 4U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_nargout, 5U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_signal, 6U, c1_k_sf_marshallOut,
    c1_j_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c1_Fs, 7U, c1_c_sf_marshallOut,
    c1_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_x, 8U, c1_h_sf_marshallOut,
    c1_g_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c1_fft_y, 9U, c1_g_sf_marshallOut,
    c1_f_sf_marshallIn);
  c1_Length = 1024.0;
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 17);
  c1_L = 1024.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 18);
  c1_NFFT = 1024.0;
  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 21);
  for (c1_i62 = 0; c1_i62 < 1024; c1_i62++) {
    c1_b_signal[c1_i62] = c1_signal[c1_i62];
  }

  c1_b_fft(chartInstance, c1_b_signal, c1_A);
  for (c1_i63 = 0; c1_i63 < 1024; c1_i63++) {
    c1_ar = c1_A[c1_i63].re;
    c1_ai = c1_A[c1_i63].im;
    c1_br = c1_dc1.re;
    c1_bi = c1_dc1.im;
    if (c1_bi == 0.0) {
      if (c1_ai == 0.0) {
        c1_signal_f[c1_i63].re = c1_ar / c1_br;
        c1_signal_f[c1_i63].im = 0.0;
      } else if (c1_ar == 0.0) {
        c1_signal_f[c1_i63].re = 0.0;
        c1_signal_f[c1_i63].im = c1_ai / c1_br;
      } else {
        c1_signal_f[c1_i63].re = c1_ar / c1_br;
        c1_signal_f[c1_i63].im = c1_ai / c1_br;
      }
    } else if (c1_br == 0.0) {
      if (c1_ar == 0.0) {
        c1_signal_f[c1_i63].re = c1_ai / c1_bi;
        c1_signal_f[c1_i63].im = 0.0;
      } else if (c1_ai == 0.0) {
        c1_signal_f[c1_i63].re = 0.0;
        c1_signal_f[c1_i63].im = -(c1_ar / c1_bi);
      } else {
        c1_signal_f[c1_i63].re = c1_ai / c1_bi;
        c1_signal_f[c1_i63].im = -(c1_ar / c1_bi);
      }
    } else {
      c1_brm = muDoubleScalarAbs(c1_br);
      c1_bim = muDoubleScalarAbs(c1_bi);
      if (c1_brm > c1_bim) {
        c1_s = c1_bi / c1_br;
        c1_d = c1_br + c1_s * c1_bi;
        c1_nr = c1_ar + c1_s * c1_ai;
        c1_ni = c1_ai - c1_s * c1_ar;
        c1_signal_f[c1_i63].re = c1_nr / c1_d;
        c1_signal_f[c1_i63].im = c1_ni / c1_d;
      } else if (c1_bim == c1_brm) {
        if (c1_br > 0.0) {
          c1_sgnbr = 0.5;
        } else {
          c1_sgnbr = -0.5;
        }

        if (c1_bi > 0.0) {
          c1_sgnbi = 0.5;
        } else {
          c1_sgnbi = -0.5;
        }

        c1_nr = c1_ar * c1_sgnbr + c1_ai * c1_sgnbi;
        c1_ni = c1_ai * c1_sgnbr - c1_ar * c1_sgnbi;
        c1_signal_f[c1_i63].re = c1_nr / c1_brm;
        c1_signal_f[c1_i63].im = c1_ni / c1_brm;
      } else {
        c1_s = c1_br / c1_bi;
        c1_d = c1_bi + c1_s * c1_br;
        c1_nr = c1_s * c1_ar + c1_ai;
        c1_ni = c1_s * c1_ai - c1_ar;
        c1_signal_f[c1_i63].re = c1_nr / c1_d;
        c1_signal_f[c1_i63].im = c1_ni / c1_d;
      }
    }
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 23);
  c1_b_A = c1_Fs;
  c1_x = c1_b_A;
  c1_b_x = c1_x;
  c1_y = c1_b_x / 2.0;
  c1_a = c1_y;
  for (c1_i64 = 0; c1_i64 < 513; c1_i64++) {
    c1_fft_x[c1_i64] = c1_a * (0.001953125 * (real_T)c1_i64);
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, 24);
  for (c1_i65 = 0; c1_i65 < 513; c1_i65++) {
    c1_b_signal_f[c1_i65] = c1_signal_f[c1_i65];
  }

  c1_abs(chartInstance, c1_b_signal_f, c1_dv14);
  for (c1_i66 = 0; c1_i66 < 513; c1_i66++) {
    c1_fft_y[c1_i66] = c1_dv14[c1_i66];
  }

  _SFD_SCRIPT_CALL(1U, chartInstance->c1_sfEvent, -24);
  _SFD_SYMBOL_SCOPE_POP();
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 0U, sf_debug_get_script_id(
    "C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 1U, sf_debug_get_script_id(
    "C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 2U, sf_debug_get_script_id(
    "C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 3U, sf_debug_get_script_id(
    "C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 4U, sf_debug_get_script_id(
    "C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/max_relativos.m"));
  _SFD_SCRIPT_TRANSLATION(c1_chartNumber, 5U, sf_debug_get_script_id(
    "C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"));
}

static const mxArray *c1_sf_marshallOut(void *chartInstanceVoid, void *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_f_detec_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_f_detec, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_f_detec),
    &c1_thisId);
  sf_mex_destroy(&c1_b_f_detec);
  return c1_y;
}

static real_T c1_b_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d0;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_f_detec_not_empty = FALSE;
  } else {
    chartInstance->c1_f_detec_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d0, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d0;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_f_detec;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_f_detec = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_f_detec),
    &c1_thisId);
  sf_mex_destroy(&c1_b_f_detec);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_b_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_f_dur_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_c_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_f_dur, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_f_dur), &c1_thisId);
  sf_mex_destroy(&c1_b_f_dur);
  return c1_y;
}

static real_T c1_d_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d1;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_f_dur_not_empty = FALSE;
  } else {
    chartInstance->c1_f_dur_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d1, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d1;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_f_dur;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_f_dur = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_f_dur), &c1_thisId);
  sf_mex_destroy(&c1_b_f_dur);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_c_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_e_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_nota, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nota), &c1_thisId);
  sf_mex_destroy(&c1_nota);
  return c1_y;
}

static real_T c1_f_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d2;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d2, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d2;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nota;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_nota = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nota), &c1_thisId);
  sf_mex_destroy(&c1_nota);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_d_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i67;
  real_T c1_b_inData[256];
  int32_T c1_i68;
  real_T c1_u[256];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i67 = 0; c1_i67 < 256; c1_i67++) {
    c1_b_inData[c1_i67] = (*(real_T (*)[256])c1_inData)[c1_i67];
  }

  for (c1_i68 = 0; c1_i68 < 256; c1_i68++) {
    c1_u[c1_i68] = c1_b_inData[c1_i68];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 256, 1), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static const mxArray *c1_e_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[257], int32_T c1_inData_sizes[1])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes;
  int32_T c1_loop_ub;
  int32_T c1_i69;
  real_T c1_b_inData_data[257];
  int32_T c1_u_sizes;
  int32_T c1_b_loop_ub;
  int32_T c1_i70;
  real_T c1_u_data[257];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes = c1_inData_sizes[0];
  c1_loop_ub = c1_inData_sizes[0] - 1;
  for (c1_i69 = 0; c1_i69 <= c1_loop_ub; c1_i69++) {
    c1_b_inData_data[c1_i69] = c1_inData_data[c1_i69];
  }

  c1_u_sizes = c1_b_inData_sizes;
  c1_b_loop_ub = c1_b_inData_sizes - 1;
  for (c1_i70 = 0; c1_i70 <= c1_b_loop_ub; c1_i70++) {
    c1_u_data[c1_i70] = c1_b_inData_data[c1_i70];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 1,
    c1_u_sizes), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_g_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[257],
  int32_T c1_y_sizes[1])
{
  static uint32_T c1_uv0[1] = { 257U };

  uint32_T c1_uv1[1];
  static boolean_T c1_bv0[1] = { TRUE };

  boolean_T c1_bv1[1];
  int32_T c1_tmp_sizes;
  real_T c1_tmp_data[257];
  int32_T c1_loop_ub;
  int32_T c1_i71;
  c1_uv1[0] = c1_uv0[0];
  c1_bv1[0] = c1_bv0[0];
  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                   1, c1_bv1, c1_uv1, &c1_tmp_sizes);
  c1_y_sizes[0] = c1_tmp_sizes;
  c1_loop_ub = c1_tmp_sizes - 1;
  for (c1_i71 = 0; c1_i71 <= c1_loop_ub; c1_i71++) {
    c1_y_data[c1_i71] = c1_tmp_data[c1_i71];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[257],
  int32_T c1_outData_sizes[1])
{
  const mxArray *c1_in;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes;
  real_T c1_y_data[257];
  int32_T c1_loop_ub;
  int32_T c1_i72;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_in = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_in), &c1_thisId, c1_y_data,
                        *(int32_T (*)[1])&c1_y_sizes);
  sf_mex_destroy(&c1_in);
  c1_outData_sizes[0] = c1_y_sizes;
  c1_loop_ub = c1_y_sizes - 1;
  for (c1_i72 = 0; c1_i72 <= c1_loop_ub; c1_i72++) {
    c1_outData_data[c1_i72] = c1_y_data[c1_i72];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_f_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  char_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(char_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 10, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static char_T c1_h_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  char_T c1_y;
  char_T c1_c0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_c0, 1, 10, 0U, 0, 0U, 0);
  c1_y = c1_c0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_frec_Ffund;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  char_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_frec_Ffund = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_frec_Ffund),
    &c1_thisId);
  sf_mex_destroy(&c1_frec_Ffund);
  *(char_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_g_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i73;
  real_T c1_b_inData[513];
  int32_T c1_i74;
  real_T c1_u[513];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i73 = 0; c1_i73 < 513; c1_i73++) {
    c1_b_inData[c1_i73] = (*(real_T (*)[513])c1_inData)[c1_i73];
  }

  for (c1_i74 = 0; c1_i74 < 513; c1_i74++) {
    c1_u[c1_i74] = c1_b_inData[c1_i74];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 513), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_i_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[513])
{
  real_T c1_dv15[513];
  int32_T c1_i75;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv15, 1, 0, 0U, 1, 0U, 1, 513);
  for (c1_i75 = 0; c1_i75 < 513; c1_i75++) {
    c1_y[c1_i75] = c1_dv15[c1_i75];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_fft_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[513];
  int32_T c1_i76;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_fft_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_fft_y), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_fft_y);
  for (c1_i76 = 0; c1_i76 < 513; c1_i76++) {
    (*(real_T (*)[513])c1_outData)[c1_i76] = c1_y[c1_i76];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_h_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i77;
  real_T c1_b_inData[513];
  int32_T c1_i78;
  real_T c1_u[513];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i77 = 0; c1_i77 < 513; c1_i77++) {
    c1_b_inData[c1_i77] = (*(real_T (*)[513])c1_inData)[c1_i77];
  }

  for (c1_i78 = 0; c1_i78 < 513; c1_i78++) {
    c1_u[c1_i78] = c1_b_inData[c1_i78];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 513), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_j_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[513])
{
  real_T c1_dv16[513];
  int32_T c1_i79;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv16, 1, 0, 0U, 1, 0U, 2, 1,
                513);
  for (c1_i79 = 0; c1_i79 < 513; c1_i79++) {
    c1_y[c1_i79] = c1_dv16[c1_i79];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_fft_x;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[513];
  int32_T c1_i80;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_fft_x = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_fft_x), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_fft_x);
  for (c1_i80 = 0; c1_i80 < 513; c1_i80++) {
    (*(real_T (*)[513])c1_outData)[c1_i80] = c1_y[c1_i80];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_i_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i81;
  real_T c1_b_inData[256];
  int32_T c1_i82;
  real_T c1_u[256];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i81 = 0; c1_i81 < 256; c1_i81++) {
    c1_b_inData[c1_i81] = (*(real_T (*)[256])c1_inData)[c1_i81];
  }

  for (c1_i82 = 0; c1_i82 < 256; c1_i82++) {
    c1_u[c1_i82] = c1_b_inData[c1_i82];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 256), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_k_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[256])
{
  real_T c1_dv17[256];
  int32_T c1_i83;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv17, 1, 0, 0U, 1, 0U, 1, 256);
  for (c1_i83 = 0; c1_i83 < 256; c1_i83++) {
    c1_y[c1_i83] = c1_dv17[c1_i83];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_signal;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[256];
  int32_T c1_i84;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_signal = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_signal), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_signal);
  for (c1_i84 = 0; c1_i84 < 256; c1_i84++) {
    (*(real_T (*)[256])c1_outData)[c1_i84] = c1_y[c1_i84];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_j_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i85;
  creal_T c1_b_inData[1024];
  int32_T c1_i86;
  creal_T c1_u[1024];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i85 = 0; c1_i85 < 1024; c1_i85++) {
    c1_b_inData[c1_i85] = (*(creal_T (*)[1024])c1_inData)[c1_i85];
  }

  for (c1_i86 = 0; c1_i86 < 1024; c1_i86++) {
    c1_u[c1_i86] = c1_b_inData[c1_i86];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 1U, 1U, 0U, 1, 1024), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_l_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[1024])
{
  creal_T c1_dcv0[1024];
  int32_T c1_i87;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dcv0, 1, 0, 1U, 1, 0U, 1, 1024);
  for (c1_i87 = 0; c1_i87 < 1024; c1_i87++) {
    c1_y[c1_i87] = c1_dcv0[c1_i87];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_signal_f;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  creal_T c1_y[1024];
  int32_T c1_i88;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_signal_f = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_signal_f), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_signal_f);
  for (c1_i88 = 0; c1_i88 < 1024; c1_i88++) {
    (*(creal_T (*)[1024])c1_outData)[c1_i88] = c1_y[c1_i88];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_k_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i89;
  real_T c1_b_inData[1024];
  int32_T c1_i90;
  real_T c1_u[1024];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i89 = 0; c1_i89 < 1024; c1_i89++) {
    c1_b_inData[c1_i89] = (*(real_T (*)[1024])c1_inData)[c1_i89];
  }

  for (c1_i90 = 0; c1_i90 < 1024; c1_i90++) {
    c1_u[c1_i90] = c1_b_inData[c1_i90];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 1024), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_m_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024])
{
  real_T c1_dv18[1024];
  int32_T c1_i91;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv18, 1, 0, 0U, 1, 0U, 1, 1024);
  for (c1_i91 = 0; c1_i91 < 1024; c1_i91++) {
    c1_y[c1_i91] = c1_dv18[c1_i91];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_signal;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[1024];
  int32_T c1_i92;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_signal = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_signal), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_signal);
  for (c1_i92 = 0; c1_i92 < 1024; c1_i92++) {
    (*(real_T (*)[1024])c1_outData)[c1_i92] = c1_y[c1_i92];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_l_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_flag_nota_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_n_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_flag_nota, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_flag_nota),
    &c1_thisId);
  sf_mex_destroy(&c1_b_flag_nota);
  return c1_y;
}

static real_T c1_o_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d3;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_flag_nota_not_empty = FALSE;
  } else {
    chartInstance->c1_flag_nota_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d3, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d3;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_flag_nota;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_flag_nota = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_flag_nota),
    &c1_thisId);
  sf_mex_destroy(&c1_b_flag_nota);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_m_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_piso_suma_2_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_p_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_piso_suma_2, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_piso_suma_2),
    &c1_thisId);
  sf_mex_destroy(&c1_b_piso_suma_2);
  return c1_y;
}

static real_T c1_q_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d4;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_piso_suma_2_not_empty = FALSE;
  } else {
    chartInstance->c1_piso_suma_2_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d4, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d4;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_piso_suma_2;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_piso_suma_2 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_piso_suma_2),
    &c1_thisId);
  sf_mex_destroy(&c1_b_piso_suma_2);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_n_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_piso_div_2_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_r_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_piso_div_2, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_piso_div_2),
    &c1_thisId);
  sf_mex_destroy(&c1_b_piso_div_2);
  return c1_y;
}

static real_T c1_s_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d5;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_piso_div_2_not_empty = FALSE;
  } else {
    chartInstance->c1_piso_div_2_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d5, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d5;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_piso_div_2;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_piso_div_2 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_piso_div_2),
    &c1_thisId);
  sf_mex_destroy(&c1_b_piso_div_2);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_o_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_nivel_param_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_t_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_nivel_param, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_nivel_param),
    &c1_thisId);
  sf_mex_destroy(&c1_b_nivel_param);
  return c1_y;
}

static real_T c1_u_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d6;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_nivel_param_not_empty = FALSE;
  } else {
    chartInstance->c1_nivel_param_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d6, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d6;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_nivel_param;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_nivel_param = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_nivel_param),
    &c1_thisId);
  sf_mex_destroy(&c1_b_nivel_param);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_p_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_piso_ruido_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_v_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_piso_ruido, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_piso_ruido),
    &c1_thisId);
  sf_mex_destroy(&c1_b_piso_ruido);
  return c1_y;
}

static real_T c1_w_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d7;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_piso_ruido_not_empty = FALSE;
  } else {
    chartInstance->c1_piso_ruido_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d7, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d7;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_piso_ruido;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_piso_ruido = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_w_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_piso_ruido),
    &c1_thisId);
  sf_mex_destroy(&c1_b_piso_ruido);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_q_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_ruido_2_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_x_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_ruido_2, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_ruido_2),
    &c1_thisId);
  sf_mex_destroy(&c1_b_ruido_2);
  return c1_y;
}

static real_T c1_y_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d8;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_ruido_2_not_empty = FALSE;
  } else {
    chartInstance->c1_ruido_2_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d8, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d8;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_ruido_2;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_ruido_2 = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_y_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_ruido_2),
    &c1_thisId);
  sf_mex_destroy(&c1_b_ruido_2);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_r_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  real_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(real_T *)c1_inData;
  c1_y = NULL;
  if (!chartInstance->c1_ruido_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static real_T c1_ab_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_ruido, const char_T *c1_identifier)
{
  real_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_ruido),
    &c1_thisId);
  sf_mex_destroy(&c1_b_ruido);
  return c1_y;
}

static real_T c1_bb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  real_T c1_y;
  real_T c1_d9;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_ruido_not_empty = FALSE;
  } else {
    chartInstance->c1_ruido_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_d9, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d9;
  }

  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_ruido;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_ruido = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_bb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_ruido),
    &c1_thisId);
  sf_mex_destroy(&c1_b_ruido);
  *(real_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_s_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i93;
  real_T c1_b_inData[1024];
  int32_T c1_i94;
  real_T c1_u[1024];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i93 = 0; c1_i93 < 1024; c1_i93++) {
    c1_b_inData[c1_i93] = (*(real_T (*)[1024])c1_inData)[c1_i93];
  }

  for (c1_i94 = 0; c1_i94 < 1024; c1_i94++) {
    c1_u[c1_i94] = c1_b_inData[c1_i94];
  }

  c1_y = NULL;
  if (!chartInstance->c1_bloque_act_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 1024), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_cb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_bloque_act, const char_T *c1_identifier, real_T c1_y[1024])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_bloque_act), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_bloque_act);
}

static void c1_db_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024])
{
  real_T c1_dv19[1024];
  int32_T c1_i95;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_bloque_act_not_empty = FALSE;
  } else {
    chartInstance->c1_bloque_act_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv19, 1, 0, 0U, 1, 0U, 1,
                  1024);
    for (c1_i95 = 0; c1_i95 < 1024; c1_i95++) {
      c1_y[c1_i95] = c1_dv19[c1_i95];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_bloque_act;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[1024];
  int32_T c1_i96;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_bloque_act = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_db_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_bloque_act), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_bloque_act);
  for (c1_i96 = 0; c1_i96 < 1024; c1_i96++) {
    (*(real_T (*)[1024])c1_outData)[c1_i96] = c1_y[c1_i96];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_t_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i97;
  real_T c1_b_inData[1024];
  int32_T c1_i98;
  real_T c1_u[1024];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i97 = 0; c1_i97 < 1024; c1_i97++) {
    c1_b_inData[c1_i97] = (*(real_T (*)[1024])c1_inData)[c1_i97];
  }

  for (c1_i98 = 0; c1_i98 < 1024; c1_i98++) {
    c1_u[c1_i98] = c1_b_inData[c1_i98];
  }

  c1_y = NULL;
  if (!chartInstance->c1_bloque_ant_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 1024), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_eb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_bloque_ant, const char_T *c1_identifier, real_T c1_y[1024])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_bloque_ant), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_bloque_ant);
}

static void c1_fb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024])
{
  real_T c1_dv20[1024];
  int32_T c1_i99;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_bloque_ant_not_empty = FALSE;
  } else {
    chartInstance->c1_bloque_ant_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv20, 1, 0, 0U, 1, 0U, 1,
                  1024);
    for (c1_i99 = 0; c1_i99 < 1024; c1_i99++) {
      c1_y[c1_i99] = c1_dv20[c1_i99];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_s_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_bloque_ant;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[1024];
  int32_T c1_i100;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_bloque_ant = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_fb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_bloque_ant), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_bloque_ant);
  for (c1_i100 = 0; c1_i100 < 1024; c1_i100++) {
    (*(real_T (*)[1024])c1_outData)[c1_i100] = c1_y[c1_i100];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_u_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i101;
  real_T c1_b_inData[1024];
  int32_T c1_i102;
  real_T c1_u[1024];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i101 = 0; c1_i101 < 1024; c1_i101++) {
    c1_b_inData[c1_i101] = (*(real_T (*)[1024])c1_inData)[c1_i101];
  }

  for (c1_i102 = 0; c1_i102 < 1024; c1_i102++) {
    c1_u[c1_i102] = c1_b_inData[c1_i102];
  }

  c1_y = NULL;
  if (!chartInstance->c1_window_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 1024), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_gb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_window, const char_T *c1_identifier, real_T c1_y[1024])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_hb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_window), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_window);
}

static void c1_hb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1024])
{
  real_T c1_dv21[1024];
  int32_T c1_i103;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_window_not_empty = FALSE;
  } else {
    chartInstance->c1_window_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv21, 1, 0, 0U, 1, 0U, 1,
                  1024);
    for (c1_i103 = 0; c1_i103 < 1024; c1_i103++) {
      c1_y[c1_i103] = c1_dv21[c1_i103];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_t_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_window;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[1024];
  int32_T c1_i104;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_window = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_hb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_window), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_window);
  for (c1_i104 = 0; c1_i104 < 1024; c1_i104++) {
    (*(real_T (*)[1024])c1_outData)[c1_i104] = c1_y[c1_i104];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_v_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i105;
  real_T c1_b_inData[1280];
  int32_T c1_i106;
  real_T c1_u[1280];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i105 = 0; c1_i105 < 1280; c1_i105++) {
    c1_b_inData[c1_i105] = (*(real_T (*)[1280])c1_inData)[c1_i105];
  }

  for (c1_i106 = 0; c1_i106 < 1280; c1_i106++) {
    c1_u[c1_i106] = c1_b_inData[c1_i106];
  }

  c1_y = NULL;
  if (!chartInstance->c1_in_tot_not_empty) {
    sf_mex_assign(&c1_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0), FALSE);
  } else {
    sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 1280), FALSE);
  }

  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_ib_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_b_in_tot, const char_T *c1_identifier, real_T c1_y[1280])
{
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_jb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_in_tot), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_in_tot);
}

static void c1_jb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[1280])
{
  real_T c1_dv22[1280];
  int32_T c1_i107;
  if (mxIsEmpty(c1_u)) {
    chartInstance->c1_in_tot_not_empty = FALSE;
  } else {
    chartInstance->c1_in_tot_not_empty = TRUE;
    sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv22, 1, 0, 0U, 1, 0U, 1,
                  1280);
    for (c1_i107 = 0; c1_i107 < 1280; c1_i107++) {
      c1_y[c1_i107] = c1_dv22[c1_i107];
    }
  }

  sf_mex_destroy(&c1_u);
}

static void c1_u_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_in_tot;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[1280];
  int32_T c1_i108;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_in_tot = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_jb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_in_tot), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_b_in_tot);
  for (c1_i108 = 0; c1_i108 < 1280; c1_i108++) {
    (*(real_T (*)[1280])c1_outData)[c1_i108] = c1_y[c1_i108];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_w_sf_marshallOut(void *chartInstanceVoid, real_T
  c1_inData_data[257], int32_T c1_inData_sizes[2])
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_b_inData_sizes[2];
  int32_T c1_loop_ub;
  int32_T c1_i109;
  real_T c1_b_inData_data[257];
  int32_T c1_u_sizes[2];
  int32_T c1_b_loop_ub;
  int32_T c1_i110;
  real_T c1_u_data[257];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_b_inData_sizes[0] = 1;
  c1_b_inData_sizes[1] = c1_inData_sizes[1];
  c1_loop_ub = c1_inData_sizes[1] - 1;
  for (c1_i109 = 0; c1_i109 <= c1_loop_ub; c1_i109++) {
    c1_b_inData_data[c1_b_inData_sizes[0] * c1_i109] =
      c1_inData_data[c1_inData_sizes[0] * c1_i109];
  }

  c1_u_sizes[0] = 1;
  c1_u_sizes[1] = c1_b_inData_sizes[1];
  c1_b_loop_ub = c1_b_inData_sizes[1] - 1;
  for (c1_i110 = 0; c1_i110 <= c1_b_loop_ub; c1_i110++) {
    c1_u_data[c1_u_sizes[0] * c1_i110] = c1_b_inData_data[c1_b_inData_sizes[0] *
      c1_i110];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u_data, 0, 0U, 1U, 0U, 2,
    c1_u_sizes[0], c1_u_sizes[1]), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_kb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y_data[257],
  int32_T c1_y_sizes[2])
{
  int32_T c1_i111;
  uint32_T c1_uv2[2];
  int32_T c1_i112;
  static boolean_T c1_bv2[2] = { FALSE, TRUE };

  boolean_T c1_bv3[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[257];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i113;
  for (c1_i111 = 0; c1_i111 < 2; c1_i111++) {
    c1_uv2[c1_i111] = 1U + ((uint32_T)c1_i111 << 8);
  }

  for (c1_i112 = 0; c1_i112 < 2; c1_i112++) {
    c1_bv3[c1_i112] = c1_bv2[c1_i112];
  }

  sf_mex_import_vs(c1_parentId, sf_mex_dup(c1_u), c1_tmp_data, 1, 0, 0U, 1, 0U,
                   2, c1_bv3, c1_uv2, c1_tmp_sizes);
  c1_y_sizes[0] = 1;
  c1_y_sizes[1] = c1_tmp_sizes[1];
  c1_y = c1_y_sizes[0];
  c1_b_y = c1_y_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i113 = 0; c1_i113 <= c1_loop_ub; c1_i113++) {
    c1_y_data[c1_i113] = c1_tmp_data[c1_i113];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_v_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, real_T c1_outData_data[257],
  int32_T c1_outData_sizes[2])
{
  const mxArray *c1_signal;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y_sizes[2];
  real_T c1_y_data[257];
  int32_T c1_loop_ub;
  int32_T c1_i114;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_signal = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_kb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_signal), &c1_thisId,
    c1_y_data, c1_y_sizes);
  sf_mex_destroy(&c1_signal);
  c1_outData_sizes[0] = 1;
  c1_outData_sizes[1] = c1_y_sizes[1];
  c1_loop_ub = c1_y_sizes[1] - 1;
  for (c1_i114 = 0; c1_i114 <= c1_loop_ub; c1_i114++) {
    c1_outData_data[c1_outData_sizes[0] * c1_i114] = c1_y_data[c1_y_sizes[0] *
      c1_i114];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_x_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i115;
  real_T c1_b_inData[129];
  int32_T c1_i116;
  real_T c1_u[129];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i115 = 0; c1_i115 < 129; c1_i115++) {
    c1_b_inData[c1_i115] = (*(real_T (*)[129])c1_inData)[c1_i115];
  }

  for (c1_i116 = 0; c1_i116 < 129; c1_i116++) {
    c1_u[c1_i116] = c1_b_inData[c1_i116];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 129), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_lb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[129])
{
  real_T c1_dv23[129];
  int32_T c1_i117;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv23, 1, 0, 0U, 1, 0U, 2, 1,
                129);
  for (c1_i117 = 0; c1_i117 < 129; c1_i117++) {
    c1_y[c1_i117] = c1_dv23[c1_i117];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_w_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_espectro;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[129];
  int32_T c1_i118;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_espectro = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_lb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_espectro), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_espectro);
  for (c1_i118 = 0; c1_i118 < 129; c1_i118++) {
    (*(real_T (*)[129])c1_outData)[c1_i118] = c1_y[c1_i118];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_y_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i119;
  creal_T c1_b_inData[256];
  int32_T c1_i120;
  creal_T c1_u[256];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i119 = 0; c1_i119 < 256; c1_i119++) {
    c1_b_inData[c1_i119] = (*(creal_T (*)[256])c1_inData)[c1_i119];
  }

  for (c1_i120 = 0; c1_i120 < 256; c1_i120++) {
    c1_u[c1_i120] = c1_b_inData[c1_i120];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 1U, 1U, 0U, 2, 1, 256), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_mb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[256])
{
  creal_T c1_dcv1[256];
  int32_T c1_i121;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dcv1, 1, 0, 1U, 1, 0U, 2, 1,
                256);
  for (c1_i121 = 0; c1_i121 < 256; c1_i121++) {
    c1_y[c1_i121] = c1_dcv1[c1_i121];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_x_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_fft_s;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  creal_T c1_y[256];
  int32_T c1_i122;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_fft_s = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_mb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_fft_s), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_fft_s);
  for (c1_i122 = 0; c1_i122 < 256; c1_i122++) {
    (*(creal_T (*)[256])c1_outData)[c1_i122] = c1_y[c1_i122];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_ab_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i123;
  real_T c1_b_inData[2049];
  int32_T c1_i124;
  real_T c1_u[2049];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i123 = 0; c1_i123 < 2049; c1_i123++) {
    c1_b_inData[c1_i123] = (*(real_T (*)[2049])c1_inData)[c1_i123];
  }

  for (c1_i124 = 0; c1_i124 < 2049; c1_i124++) {
    c1_u[c1_i124] = c1_b_inData[c1_i124];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 2049),
                FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_nb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2049])
{
  real_T c1_dv24[2049];
  int32_T c1_i125;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv24, 1, 0, 0U, 1, 0U, 2, 1,
                2049);
  for (c1_i125 = 0; c1_i125 < 2049; c1_i125++) {
    c1_y[c1_i125] = c1_dv24[c1_i125];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_y_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_fft_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2049];
  int32_T c1_i126;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_fft_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_nb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_fft_y), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_fft_y);
  for (c1_i126 = 0; c1_i126 < 2049; c1_i126++) {
    (*(real_T (*)[2049])c1_outData)[c1_i126] = c1_y[c1_i126];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_bb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i127;
  real_T c1_b_inData[4095];
  int32_T c1_i128;
  real_T c1_u[4095];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i127 = 0; c1_i127 < 4095; c1_i127++) {
    c1_b_inData[c1_i127] = (*(real_T (*)[4095])c1_inData)[c1_i127];
  }

  for (c1_i128 = 0; c1_i128 < 4095; c1_i128++) {
    c1_u[c1_i128] = c1_b_inData[c1_i128];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 4095),
                FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_ob_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[4095])
{
  real_T c1_dv25[4095];
  int32_T c1_i129;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv25, 1, 0, 0U, 1, 0U, 2, 1,
                4095);
  for (c1_i129 = 0; c1_i129 < 4095; c1_i129++) {
    c1_y[c1_i129] = c1_dv25[c1_i129];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_ab_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_signal;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[4095];
  int32_T c1_i130;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_signal = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_ob_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_signal), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_signal);
  for (c1_i130 = 0; c1_i130 < 4095; c1_i130++) {
    (*(real_T (*)[4095])c1_outData)[c1_i130] = c1_y[c1_i130];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_cb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i131;
  creal_T c1_b_inData[4096];
  int32_T c1_i132;
  creal_T c1_u[4096];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i131 = 0; c1_i131 < 4096; c1_i131++) {
    c1_b_inData[c1_i131] = (*(creal_T (*)[4096])c1_inData)[c1_i131];
  }

  for (c1_i132 = 0; c1_i132 < 4096; c1_i132++) {
    c1_u[c1_i132] = c1_b_inData[c1_i132];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 1U, 1U, 0U, 2, 1, 4096),
                FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_pb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, creal_T c1_y[4096])
{
  creal_T c1_dcv2[4096];
  int32_T c1_i133;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dcv2, 1, 0, 1U, 1, 0U, 2, 1,
                4096);
  for (c1_i133 = 0; c1_i133 < 4096; c1_i133++) {
    c1_y[c1_i133] = c1_dcv2[c1_i133];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_bb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_signal_f;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  creal_T c1_y[4096];
  int32_T c1_i134;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_signal_f = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_pb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_signal_f), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_signal_f);
  for (c1_i134 = 0; c1_i134 < 4096; c1_i134++) {
    (*(creal_T (*)[4096])c1_outData)[c1_i134] = c1_y[c1_i134];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_db_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i135;
  real_T c1_b_inData[2049];
  int32_T c1_i136;
  real_T c1_u[2049];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i135 = 0; c1_i135 < 2049; c1_i135++) {
    c1_b_inData[c1_i135] = (*(real_T (*)[2049])c1_inData)[c1_i135];
  }

  for (c1_i136 = 0; c1_i136 < 2049; c1_i136++) {
    c1_u[c1_i136] = c1_b_inData[c1_i136];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 1, 2049), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_qb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2049])
{
  real_T c1_dv26[2049];
  int32_T c1_i137;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv26, 1, 0, 0U, 1, 0U, 1, 2049);
  for (c1_i137 = 0; c1_i137 < 2049; c1_i137++) {
    c1_y[c1_i137] = c1_dv26[c1_i137];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_cb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_maximos_y;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2049];
  int32_T c1_i138;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_maximos_y = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_qb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_maximos_y), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_maximos_y);
  for (c1_i138 = 0; c1_i138 < 2049; c1_i138++) {
    (*(real_T (*)[2049])c1_outData)[c1_i138] = c1_y[c1_i138];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_eb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i139;
  char_T c1_b_inData[4];
  int32_T c1_i140;
  char_T c1_u[4];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i139 = 0; c1_i139 < 4; c1_i139++) {
    c1_b_inData[c1_i139] = (*(char_T (*)[4])c1_inData)[c1_i139];
  }

  for (c1_i140 = 0; c1_i140 < 4; c1_i140++) {
    c1_u[c1_i140] = c1_b_inData[c1_i140];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 4), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_rb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[4])
{
  char_T c1_cv0[4];
  int32_T c1_i141;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv0, 1, 10, 0U, 1, 0U, 2, 1, 4);
  for (c1_i141 = 0; c1_i141 < 4; c1_i141++) {
    c1_y[c1_i141] = c1_cv0[c1_i141];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_db_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_nota;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  char_T c1_y[4];
  int32_T c1_i142;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_nota = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_rb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_nota), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_nota);
  for (c1_i142 = 0; c1_i142 < 4; c1_i142++) {
    (*(char_T (*)[4])c1_outData)[c1_i142] = c1_y[c1_i142];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_fb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i143;
  real_T c1_b_inData[73];
  int32_T c1_i144;
  real_T c1_u[73];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i143 = 0; c1_i143 < 73; c1_i143++) {
    c1_b_inData[c1_i143] = (*(real_T (*)[73])c1_inData)[c1_i143];
  }

  for (c1_i144 = 0; c1_i144 < 73; c1_i144++) {
    c1_u[c1_i144] = c1_b_inData[c1_i144];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 73), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_sb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[73])
{
  real_T c1_dv27[73];
  int32_T c1_i145;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv27, 1, 0, 0U, 1, 0U, 2, 1,
                73);
  for (c1_i145 = 0; c1_i145 < 73; c1_i145++) {
    c1_y[c1_i145] = c1_dv27[c1_i145];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_eb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_chupelupe;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[73];
  int32_T c1_i146;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_chupelupe = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_sb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_chupelupe), &c1_thisId,
    c1_y);
  sf_mex_destroy(&c1_chupelupe);
  for (c1_i146 = 0; c1_i146 < 73; c1_i146++) {
    (*(real_T (*)[73])c1_outData)[c1_i146] = c1_y[c1_i146];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_gb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i147;
  char_T c1_b_inData[348];
  int32_T c1_i148;
  char_T c1_u[348];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i147 = 0; c1_i147 < 348; c1_i147++) {
    c1_b_inData[c1_i147] = (*(char_T (*)[348])c1_inData)[c1_i147];
  }

  for (c1_i148 = 0; c1_i148 < 348; c1_i148++) {
    c1_u[c1_i148] = c1_b_inData[c1_i148];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 10, 0U, 1U, 0U, 2, 1, 348),
                FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_tb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, char_T c1_y[348])
{
  char_T c1_cv1[348];
  int32_T c1_i149;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_cv1, 1, 10, 0U, 1, 0U, 2, 1,
                348);
  for (c1_i149 = 0; c1_i149 < 348; c1_i149++) {
    c1_y[c1_i149] = c1_cv1[c1_i149];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_fb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_notas;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  char_T c1_y[348];
  int32_T c1_i150;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_notas = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_tb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_notas), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_notas);
  for (c1_i150 = 0; c1_i150 < 348; c1_i150++) {
    (*(char_T (*)[348])c1_outData)[c1_i150] = c1_y[c1_i150];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

static const mxArray *c1_hb_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_i151;
  real_T c1_b_inData[2048];
  int32_T c1_i152;
  real_T c1_u[2048];
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  for (c1_i151 = 0; c1_i151 < 2048; c1_i151++) {
    c1_b_inData[c1_i151] = (*(real_T (*)[2048])c1_inData)[c1_i151];
  }

  for (c1_i152 = 0; c1_i152 < 2048; c1_i152++) {
    c1_u[c1_i152] = c1_b_inData[c1_i152];
  }

  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 0, 0U, 1U, 0U, 2, 1, 2048),
                FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static void c1_ub_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance, const
  mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId, real_T c1_y[2048])
{
  real_T c1_dv28[2048];
  int32_T c1_i153;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), c1_dv28, 1, 0, 0U, 1, 0U, 2, 1,
                2048);
  for (c1_i153 = 0; c1_i153 < 2048; c1_i153++) {
    c1_y[c1_i153] = c1_dv28[c1_i153];
  }

  sf_mex_destroy(&c1_u);
}

static void c1_gb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_in_hann;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  real_T c1_y[2048];
  int32_T c1_i154;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_in_hann = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_ub_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_in_hann), &c1_thisId, c1_y);
  sf_mex_destroy(&c1_in_hann);
  for (c1_i154 = 0; c1_i154 < 2048; c1_i154++) {
    (*(real_T (*)[2048])c1_outData)[c1_i154] = c1_y[c1_i154];
  }

  sf_mex_destroy(&c1_mxArrayInData);
}

const mxArray *sf_c1_Leda_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_nameCaptureInfo = NULL;
  sf_mex_assign(&c1_nameCaptureInfo, sf_mex_createstruct("structure", 2, 241, 1),
                FALSE);
  c1_info_helper(&c1_nameCaptureInfo);
  c1_b_info_helper(&c1_nameCaptureInfo);
  c1_c_info_helper(&c1_nameCaptureInfo);
  c1_d_info_helper(&c1_nameCaptureInfo);
  sf_mex_emlrtNameCapturePostProcessR2012a(&c1_nameCaptureInfo);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs0 = NULL;
  const mxArray *c1_lhs0 = NULL;
  const mxArray *c1_rhs1 = NULL;
  const mxArray *c1_lhs1 = NULL;
  const mxArray *c1_rhs2 = NULL;
  const mxArray *c1_lhs2 = NULL;
  const mxArray *c1_rhs3 = NULL;
  const mxArray *c1_lhs3 = NULL;
  const mxArray *c1_rhs4 = NULL;
  const mxArray *c1_lhs4 = NULL;
  const mxArray *c1_rhs5 = NULL;
  const mxArray *c1_lhs5 = NULL;
  const mxArray *c1_rhs6 = NULL;
  const mxArray *c1_lhs6 = NULL;
  const mxArray *c1_rhs7 = NULL;
  const mxArray *c1_lhs7 = NULL;
  const mxArray *c1_rhs8 = NULL;
  const mxArray *c1_lhs8 = NULL;
  const mxArray *c1_rhs9 = NULL;
  const mxArray *c1_lhs9 = NULL;
  const mxArray *c1_rhs10 = NULL;
  const mxArray *c1_lhs10 = NULL;
  const mxArray *c1_rhs11 = NULL;
  const mxArray *c1_lhs11 = NULL;
  const mxArray *c1_rhs12 = NULL;
  const mxArray *c1_lhs12 = NULL;
  const mxArray *c1_rhs13 = NULL;
  const mxArray *c1_lhs13 = NULL;
  const mxArray *c1_rhs14 = NULL;
  const mxArray *c1_lhs14 = NULL;
  const mxArray *c1_rhs15 = NULL;
  const mxArray *c1_lhs15 = NULL;
  const mxArray *c1_rhs16 = NULL;
  const mxArray *c1_lhs16 = NULL;
  const mxArray *c1_rhs17 = NULL;
  const mxArray *c1_lhs17 = NULL;
  const mxArray *c1_rhs18 = NULL;
  const mxArray *c1_lhs18 = NULL;
  const mxArray *c1_rhs19 = NULL;
  const mxArray *c1_lhs19 = NULL;
  const mxArray *c1_rhs20 = NULL;
  const mxArray *c1_lhs20 = NULL;
  const mxArray *c1_rhs21 = NULL;
  const mxArray *c1_lhs21 = NULL;
  const mxArray *c1_rhs22 = NULL;
  const mxArray *c1_lhs22 = NULL;
  const mxArray *c1_rhs23 = NULL;
  const mxArray *c1_lhs23 = NULL;
  const mxArray *c1_rhs24 = NULL;
  const mxArray *c1_lhs24 = NULL;
  const mxArray *c1_rhs25 = NULL;
  const mxArray *c1_lhs25 = NULL;
  const mxArray *c1_rhs26 = NULL;
  const mxArray *c1_lhs26 = NULL;
  const mxArray *c1_rhs27 = NULL;
  const mxArray *c1_lhs27 = NULL;
  const mxArray *c1_rhs28 = NULL;
  const mxArray *c1_lhs28 = NULL;
  const mxArray *c1_rhs29 = NULL;
  const mxArray *c1_lhs29 = NULL;
  const mxArray *c1_rhs30 = NULL;
  const mxArray *c1_lhs30 = NULL;
  const mxArray *c1_rhs31 = NULL;
  const mxArray *c1_lhs31 = NULL;
  const mxArray *c1_rhs32 = NULL;
  const mxArray *c1_lhs32 = NULL;
  const mxArray *c1_rhs33 = NULL;
  const mxArray *c1_lhs33 = NULL;
  const mxArray *c1_rhs34 = NULL;
  const mxArray *c1_lhs34 = NULL;
  const mxArray *c1_rhs35 = NULL;
  const mxArray *c1_lhs35 = NULL;
  const mxArray *c1_rhs36 = NULL;
  const mxArray *c1_lhs36 = NULL;
  const mxArray *c1_rhs37 = NULL;
  const mxArray *c1_lhs37 = NULL;
  const mxArray *c1_rhs38 = NULL;
  const mxArray *c1_lhs38 = NULL;
  const mxArray *c1_rhs39 = NULL;
  const mxArray *c1_lhs39 = NULL;
  const mxArray *c1_rhs40 = NULL;
  const mxArray *c1_lhs40 = NULL;
  const mxArray *c1_rhs41 = NULL;
  const mxArray *c1_lhs41 = NULL;
  const mxArray *c1_rhs42 = NULL;
  const mxArray *c1_lhs42 = NULL;
  const mxArray *c1_rhs43 = NULL;
  const mxArray *c1_lhs43 = NULL;
  const mxArray *c1_rhs44 = NULL;
  const mxArray *c1_lhs44 = NULL;
  const mxArray *c1_rhs45 = NULL;
  const mxArray *c1_lhs45 = NULL;
  const mxArray *c1_rhs46 = NULL;
  const mxArray *c1_lhs46 = NULL;
  const mxArray *c1_rhs47 = NULL;
  const mxArray *c1_lhs47 = NULL;
  const mxArray *c1_rhs48 = NULL;
  const mxArray *c1_lhs48 = NULL;
  const mxArray *c1_rhs49 = NULL;
  const mxArray *c1_lhs49 = NULL;
  const mxArray *c1_rhs50 = NULL;
  const mxArray *c1_lhs50 = NULL;
  const mxArray *c1_rhs51 = NULL;
  const mxArray *c1_lhs51 = NULL;
  const mxArray *c1_rhs52 = NULL;
  const mxArray *c1_lhs52 = NULL;
  const mxArray *c1_rhs53 = NULL;
  const mxArray *c1_lhs53 = NULL;
  const mxArray *c1_rhs54 = NULL;
  const mxArray *c1_lhs54 = NULL;
  const mxArray *c1_rhs55 = NULL;
  const mxArray *c1_lhs55 = NULL;
  const mxArray *c1_rhs56 = NULL;
  const mxArray *c1_lhs56 = NULL;
  const mxArray *c1_rhs57 = NULL;
  const mxArray *c1_lhs57 = NULL;
  const mxArray *c1_rhs58 = NULL;
  const mxArray *c1_lhs58 = NULL;
  const mxArray *c1_rhs59 = NULL;
  const mxArray *c1_lhs59 = NULL;
  const mxArray *c1_rhs60 = NULL;
  const mxArray *c1_lhs60 = NULL;
  const mxArray *c1_rhs61 = NULL;
  const mxArray *c1_lhs61 = NULL;
  const mxArray *c1_rhs62 = NULL;
  const mxArray *c1_lhs62 = NULL;
  const mxArray *c1_rhs63 = NULL;
  const mxArray *c1_lhs63 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("dur_prueba_simulink"), "name",
                  "name", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "resolved", "resolved", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1433587628U), "fileTimeLo",
                  "fileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 0);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 0);
  sf_mex_assign(&c1_rhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs0, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs0), "rhs", "rhs", 0);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs0), "lhs", "lhs", 0);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("hanning"), "name", "name", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/hanning.m"), "resolved", "resolved", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200916U), "fileTimeLo",
                  "fileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 1);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 1);
  sf_mex_assign(&c1_rhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs1, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs1), "rhs", "rhs", 1);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs1), "lhs", "lhs", 1);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/hanning.m"), "context", "context", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_assert_all_constant"),
                  "name", "name", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_all_constant.m"),
                  "resolved", "resolved", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836694U), "fileTimeLo",
                  "fileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 2);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 2);
  sf_mex_assign(&c1_rhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs2, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs2), "rhs", "rhs", 2);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs2), "lhs", "lhs", 2);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("fft_abs"), "name", "name", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "resolved", "resolved", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1414363750U), "fileTimeLo",
                  "fileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 3);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 3);
  sf_mex_assign(&c1_rhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs3, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs3), "rhs", "rhs", 3);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs3), "lhs", "lhs", 3);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("nextpow2"), "name", "name", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/nextpow2.m"), "resolved",
                  "resolved", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 4);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 4);
  sf_mex_assign(&c1_rhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs4, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs4), "rhs", "rhs", 4);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs4), "lhs", "lhs", 4);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/nextpow2.m"), "context",
                  "context", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 5);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 5);
  sf_mex_assign(&c1_rhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs5, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs5), "rhs", "rhs", 5);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs5), "lhs", "lhs", 5);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/nextpow2.m!fnextpow2"),
                  "context", "context", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 6);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 6);
  sf_mex_assign(&c1_rhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs6, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs6), "rhs", "rhs", 6);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs6), "lhs", "lhs", 6);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 7);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 7);
  sf_mex_assign(&c1_rhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs7, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs7), "rhs", "rhs", 7);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs7), "lhs", "lhs", 7);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "context",
                  "context", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_abs"), "name",
                  "name", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "resolved", "resolved", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836712U), "fileTimeLo",
                  "fileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 8);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 8);
  sf_mex_assign(&c1_rhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs8, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs8), "rhs", "rhs", 8);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs8), "lhs", "lhs", 8);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/nextpow2.m!fnextpow2"),
                  "context", "context", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isfinite"), "name", "name", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "resolved",
                  "resolved", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728256U), "fileTimeLo",
                  "fileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 9);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 9);
  sf_mex_assign(&c1_rhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs9, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs9), "rhs", "rhs", 9);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs9), "lhs", "lhs", 9);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "context",
                  "context", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 10);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 10);
  sf_mex_assign(&c1_rhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs10, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs10), "rhs", "rhs",
                  10);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs10), "lhs", "lhs",
                  10);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "context",
                  "context", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isinf"), "name", "name", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "resolved",
                  "resolved", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728256U), "fileTimeLo",
                  "fileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 11);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 11);
  sf_mex_assign(&c1_rhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs11, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs11), "rhs", "rhs",
                  11);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs11), "lhs", "lhs",
                  11);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isinf.m"), "context",
                  "context", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 12);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 12);
  sf_mex_assign(&c1_rhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs12, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs12), "rhs", "rhs",
                  12);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs12), "lhs", "lhs",
                  12);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "context",
                  "context", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isnan"), "name", "name", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728258U), "fileTimeLo",
                  "fileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 13);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 13);
  sf_mex_assign(&c1_rhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs13, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs13), "rhs", "rhs",
                  13);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs13), "lhs", "lhs",
                  13);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "context",
                  "context", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 14);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 14);
  sf_mex_assign(&c1_rhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs14, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs14), "rhs", "rhs",
                  14);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs14), "lhs", "lhs",
                  14);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/nextpow2.m!fnextpow2"),
                  "context", "context", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("log2"), "name", "name", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log2.m"), "resolved",
                  "resolved", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343848382U), "fileTimeLo",
                  "fileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 15);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 15);
  sf_mex_assign(&c1_rhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs15, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs15), "rhs", "rhs",
                  15);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs15), "lhs", "lhs",
                  15);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log2.m!scalar_frexp"),
                  "context", "context", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isfinite"), "name", "name", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "resolved",
                  "resolved", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728256U), "fileTimeLo",
                  "fileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 16);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 16);
  sf_mex_assign(&c1_rhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs16, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs16), "rhs", "rhs",
                  16);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs16), "lhs", "lhs",
                  16);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mpower"), "name", "name", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 17);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 17);
  sf_mex_assign(&c1_rhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs17, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs17), "rhs", "rhs",
                  17);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs17), "lhs", "lhs",
                  17);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 18);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 18);
  sf_mex_assign(&c1_rhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs18, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs18), "rhs", "rhs",
                  18);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs18), "lhs", "lhs",
                  18);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("ismatrix"), "name", "name", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ismatrix.m"), "resolved",
                  "resolved", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1331319258U), "fileTimeLo",
                  "fileTimeLo", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 19);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 19);
  sf_mex_assign(&c1_rhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs19, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs19), "rhs", "rhs",
                  19);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs19), "lhs", "lhs",
                  19);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "context",
                  "context", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("power"), "name", "name", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728280U), "fileTimeLo",
                  "fileTimeLo", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 20);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 20);
  sf_mex_assign(&c1_rhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs20, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs20), "rhs", "rhs",
                  20);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs20), "lhs", "lhs",
                  20);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "context",
                  "context", 21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 21);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 21);
  sf_mex_assign(&c1_rhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs21, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs21), "rhs", "rhs",
                  21);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs21), "lhs", "lhs",
                  21);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 22);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 22);
  sf_mex_assign(&c1_rhs22, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs22, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs22), "rhs", "rhs",
                  22);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs22), "lhs", "lhs",
                  22);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200540U), "fileTimeLo",
                  "fileTimeLo", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 23);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 23);
  sf_mex_assign(&c1_rhs23, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs23, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs23), "rhs", "rhs",
                  23);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs23), "lhs", "lhs",
                  23);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 24);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 24);
  sf_mex_assign(&c1_rhs24, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs24, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs24), "rhs", "rhs",
                  24);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs24), "lhs", "lhs",
                  24);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 25);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 25);
  sf_mex_assign(&c1_rhs25, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs25, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs25), "rhs", "rhs",
                  25);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs25), "lhs", "lhs",
                  25);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "context",
                  "context", 26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836726U), "fileTimeLo",
                  "fileTimeLo", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 26);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 26);
  sf_mex_assign(&c1_rhs26, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs26, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs26), "rhs", "rhs",
                  26);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs26), "lhs", "lhs",
                  26);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!fltpower"), "context",
                  "context", 27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_error"), "name", "name",
                  27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343848358U), "fileTimeLo",
                  "fileTimeLo", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 27);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 27);
  sf_mex_assign(&c1_rhs27, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs27, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs27), "rhs", "rhs",
                  27);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs27), "lhs", "lhs",
                  27);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 28);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 28);
  sf_mex_assign(&c1_rhs28, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs28, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs28), "rhs", "rhs",
                  28);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs28), "lhs", "lhs",
                  28);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("fft"), "name", "name", 29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/fft.m"), "resolved",
                  "resolved", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836688U), "fileTimeLo",
                  "fileTimeLo", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 29);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 29);
  sf_mex_assign(&c1_rhs29, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs29, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs29), "rhs", "rhs",
                  29);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs29), "lhs", "lhs",
                  29);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/fft.m"), "context",
                  "context", 30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_fft"), "name", "name", 30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "resolved",
                  "resolved", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728268U), "fileTimeLo",
                  "fileTimeLo", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 30);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 30);
  sf_mex_assign(&c1_rhs30, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs30, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs30), "rhs", "rhs",
                  30);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs30), "lhs", "lhs",
                  30);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_const_nonsingleton_dim"),
                  "name", "name", 31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m"),
                  "resolved", "resolved", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836696U), "fileTimeLo",
                  "fileTimeLo", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 31);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 31);
  sf_mex_assign(&c1_rhs31, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs31, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs31), "rhs", "rhs",
                  31);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs31), "lhs", "lhs",
                  31);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 32);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 32);
  sf_mex_assign(&c1_rhs32, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs32, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs32), "rhs", "rhs",
                  32);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs32), "lhs", "lhs",
                  32);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_size_ispow2"), "name",
                  "name", 33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "resolved", "resolved", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728270U), "fileTimeLo",
                  "fileTimeLo", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 33);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 33);
  sf_mex_assign(&c1_rhs33, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs33, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs33), "rhs", "rhs",
                  33);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs33), "lhs", "lhs",
                  33);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "context", "context", 34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 34);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 34);
  sf_mex_assign(&c1_rhs34, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs34, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs34), "rhs", "rhs",
                  34);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs34), "lhs", "lhs",
                  34);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "context", "context", 35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 35);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 35);
  sf_mex_assign(&c1_rhs35, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs35, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs35), "rhs", "rhs",
                  35);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs35), "lhs", "lhs",
                  35);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "context", "context", 36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184980U), "fileTimeLo",
                  "fileTimeLo", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 36);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 36);
  sf_mex_assign(&c1_rhs36, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs36, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs36), "rhs", "rhs",
                  36);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs36), "lhs", "lhs",
                  36);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "context", "context", 37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 37);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 37);
  sf_mex_assign(&c1_rhs37, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs37, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs37), "rhs", "rhs",
                  37);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs37), "lhs", "lhs",
                  37);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "context", "context", 38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_size_ispow2"), "name",
                  "name", 38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "resolved", "resolved", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728270U), "fileTimeLo",
                  "fileTimeLo", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 38);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 38);
  sf_mex_assign(&c1_rhs38, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs38, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs38), "rhs", "rhs",
                  38);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs38), "lhs", "lhs",
                  38);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 39);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 39);
  sf_mex_assign(&c1_rhs39, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs39, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs39), "rhs", "rhs",
                  39);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs39), "lhs", "lhs",
                  39);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184980U), "fileTimeLo",
                  "fileTimeLo", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 40);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 40);
  sf_mex_assign(&c1_rhs40, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs40, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs40), "rhs", "rhs",
                  40);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs40), "lhs", "lhs",
                  40);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 41);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 41);
  sf_mex_assign(&c1_rhs41, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs41, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs41), "rhs", "rhs",
                  41);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs41), "lhs", "lhs",
                  41);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 42);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 42);
  sf_mex_assign(&c1_rhs42, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs42, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs42), "rhs", "rhs",
                  42);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs42), "lhs", "lhs",
                  42);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("min"), "name", "name", 43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273318U), "fileTimeLo",
                  "fileTimeLo", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 43);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 43);
  sf_mex_assign(&c1_rhs43, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs43, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs43), "rhs", "rhs",
                  43);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs43), "lhs", "lhs",
                  43);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "context",
                  "context", 44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728270U), "fileTimeLo",
                  "fileTimeLo", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 44);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 44);
  sf_mex_assign(&c1_rhs44, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs44, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs44), "rhs", "rhs",
                  44);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs44), "lhs", "lhs",
                  44);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 45);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 45);
  sf_mex_assign(&c1_rhs45, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs45, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs45), "rhs", "rhs",
                  45);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs45), "lhs", "lhs",
                  45);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200540U), "fileTimeLo",
                  "fileTimeLo", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 46);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 46);
  sf_mex_assign(&c1_rhs46, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs46, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs46), "rhs", "rhs",
                  46);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs46), "lhs", "lhs",
                  46);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 47);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 47);
  sf_mex_assign(&c1_rhs47, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs47, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs47), "rhs", "rhs",
                  47);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs47), "lhs", "lhs",
                  47);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 48);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 48);
  sf_mex_assign(&c1_rhs48, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs48, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs48), "rhs", "rhs",
                  48);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs48), "lhs", "lhs",
                  48);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_relop"), "name", "name",
                  49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("function_handle"),
                  "dominantType", "dominantType", 49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_relop.m"), "resolved",
                  "resolved", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1342469182U), "fileTimeLo",
                  "fileTimeLo", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 49);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 49);
  sf_mex_assign(&c1_rhs49, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs49, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs49), "rhs", "rhs",
                  49);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs49), "lhs", "lhs",
                  49);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_relop.m"), "context",
                  "context", 50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742722U), "fileTimeLo",
                  "fileTimeLo", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 50);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 50);
  sf_mex_assign(&c1_rhs50, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs50, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs50), "rhs", "rhs",
                  50);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs50), "lhs", "lhs",
                  50);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!float_class_contains_indexIntClass"),
                  "context", "context", 51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 51);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 51);
  sf_mex_assign(&c1_rhs51, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs51, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs51), "rhs", "rhs",
                  51);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs51), "lhs", "lhs",
                  51);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m!is_signed_indexIntClass"),
                  "context", "context", 52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 52);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 52);
  sf_mex_assign(&c1_rhs52, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs52, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs52), "rhs", "rhs",
                  52);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs52), "lhs", "lhs",
                  52);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isnan"), "name", "name", 53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728258U), "fileTimeLo",
                  "fileTimeLo", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 53);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 53);
  sf_mex_assign(&c1_rhs53, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs53, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs53), "rhs", "rhs",
                  53);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs53), "lhs", "lhs",
                  53);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 54);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 54);
  sf_mex_assign(&c1_rhs54, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs54, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs54), "rhs", "rhs",
                  54);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs54), "lhs", "lhs",
                  54);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "context", "context", 55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 55);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 55);
  sf_mex_assign(&c1_rhs55, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs55, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs55), "rhs", "rhs",
                  55);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs55), "lhs", "lhs",
                  55);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("max"), "name", "name", 56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273316U), "fileTimeLo",
                  "fileTimeLo", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 56);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 56);
  sf_mex_assign(&c1_rhs56, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs56, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs56), "rhs", "rhs",
                  56);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs56), "lhs", "lhs",
                  56);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "context",
                  "context", 57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_min_or_max"), "name",
                  "name", 57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m"),
                  "resolved", "resolved", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728270U), "fileTimeLo",
                  "fileTimeLo", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 57);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 57);
  sf_mex_assign(&c1_rhs57, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs57, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs57), "rhs", "rhs",
                  57);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs57), "lhs", "lhs",
                  57);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 58);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 58);
  sf_mex_assign(&c1_rhs58, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs58, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs58), "rhs", "rhs",
                  58);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs58), "lhs", "lhs",
                  58);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_bin_extremum"),
                  "context", "context", 59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200540U), "fileTimeLo",
                  "fileTimeLo", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 59);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 59);
  sf_mex_assign(&c1_rhs59, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs59, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs59), "rhs", "rhs",
                  59);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs59), "lhs", "lhs",
                  59);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 60);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 60);
  sf_mex_assign(&c1_rhs60, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs60, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs60), "rhs", "rhs",
                  60);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs60), "lhs", "lhs",
                  60);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 61);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 61);
  sf_mex_assign(&c1_rhs61, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs61, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs61), "rhs", "rhs",
                  61);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs61), "lhs", "lhs",
                  61);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 62);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 62);
  sf_mex_assign(&c1_rhs62, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs62, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs62), "rhs", "rhs",
                  62);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs62), "lhs", "lhs",
                  62);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 63);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_rdivide"), "name",
                  "name", 63);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 63);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m"),
                  "resolved", "resolved", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836780U), "fileTimeLo",
                  "fileTimeLo", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 63);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 63);
  sf_mex_assign(&c1_rhs63, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs63, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs63), "rhs", "rhs",
                  63);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs63), "lhs", "lhs",
                  63);
  sf_mex_destroy(&c1_rhs0);
  sf_mex_destroy(&c1_lhs0);
  sf_mex_destroy(&c1_rhs1);
  sf_mex_destroy(&c1_lhs1);
  sf_mex_destroy(&c1_rhs2);
  sf_mex_destroy(&c1_lhs2);
  sf_mex_destroy(&c1_rhs3);
  sf_mex_destroy(&c1_lhs3);
  sf_mex_destroy(&c1_rhs4);
  sf_mex_destroy(&c1_lhs4);
  sf_mex_destroy(&c1_rhs5);
  sf_mex_destroy(&c1_lhs5);
  sf_mex_destroy(&c1_rhs6);
  sf_mex_destroy(&c1_lhs6);
  sf_mex_destroy(&c1_rhs7);
  sf_mex_destroy(&c1_lhs7);
  sf_mex_destroy(&c1_rhs8);
  sf_mex_destroy(&c1_lhs8);
  sf_mex_destroy(&c1_rhs9);
  sf_mex_destroy(&c1_lhs9);
  sf_mex_destroy(&c1_rhs10);
  sf_mex_destroy(&c1_lhs10);
  sf_mex_destroy(&c1_rhs11);
  sf_mex_destroy(&c1_lhs11);
  sf_mex_destroy(&c1_rhs12);
  sf_mex_destroy(&c1_lhs12);
  sf_mex_destroy(&c1_rhs13);
  sf_mex_destroy(&c1_lhs13);
  sf_mex_destroy(&c1_rhs14);
  sf_mex_destroy(&c1_lhs14);
  sf_mex_destroy(&c1_rhs15);
  sf_mex_destroy(&c1_lhs15);
  sf_mex_destroy(&c1_rhs16);
  sf_mex_destroy(&c1_lhs16);
  sf_mex_destroy(&c1_rhs17);
  sf_mex_destroy(&c1_lhs17);
  sf_mex_destroy(&c1_rhs18);
  sf_mex_destroy(&c1_lhs18);
  sf_mex_destroy(&c1_rhs19);
  sf_mex_destroy(&c1_lhs19);
  sf_mex_destroy(&c1_rhs20);
  sf_mex_destroy(&c1_lhs20);
  sf_mex_destroy(&c1_rhs21);
  sf_mex_destroy(&c1_lhs21);
  sf_mex_destroy(&c1_rhs22);
  sf_mex_destroy(&c1_lhs22);
  sf_mex_destroy(&c1_rhs23);
  sf_mex_destroy(&c1_lhs23);
  sf_mex_destroy(&c1_rhs24);
  sf_mex_destroy(&c1_lhs24);
  sf_mex_destroy(&c1_rhs25);
  sf_mex_destroy(&c1_lhs25);
  sf_mex_destroy(&c1_rhs26);
  sf_mex_destroy(&c1_lhs26);
  sf_mex_destroy(&c1_rhs27);
  sf_mex_destroy(&c1_lhs27);
  sf_mex_destroy(&c1_rhs28);
  sf_mex_destroy(&c1_lhs28);
  sf_mex_destroy(&c1_rhs29);
  sf_mex_destroy(&c1_lhs29);
  sf_mex_destroy(&c1_rhs30);
  sf_mex_destroy(&c1_lhs30);
  sf_mex_destroy(&c1_rhs31);
  sf_mex_destroy(&c1_lhs31);
  sf_mex_destroy(&c1_rhs32);
  sf_mex_destroy(&c1_lhs32);
  sf_mex_destroy(&c1_rhs33);
  sf_mex_destroy(&c1_lhs33);
  sf_mex_destroy(&c1_rhs34);
  sf_mex_destroy(&c1_lhs34);
  sf_mex_destroy(&c1_rhs35);
  sf_mex_destroy(&c1_lhs35);
  sf_mex_destroy(&c1_rhs36);
  sf_mex_destroy(&c1_lhs36);
  sf_mex_destroy(&c1_rhs37);
  sf_mex_destroy(&c1_lhs37);
  sf_mex_destroy(&c1_rhs38);
  sf_mex_destroy(&c1_lhs38);
  sf_mex_destroy(&c1_rhs39);
  sf_mex_destroy(&c1_lhs39);
  sf_mex_destroy(&c1_rhs40);
  sf_mex_destroy(&c1_lhs40);
  sf_mex_destroy(&c1_rhs41);
  sf_mex_destroy(&c1_lhs41);
  sf_mex_destroy(&c1_rhs42);
  sf_mex_destroy(&c1_lhs42);
  sf_mex_destroy(&c1_rhs43);
  sf_mex_destroy(&c1_lhs43);
  sf_mex_destroy(&c1_rhs44);
  sf_mex_destroy(&c1_lhs44);
  sf_mex_destroy(&c1_rhs45);
  sf_mex_destroy(&c1_lhs45);
  sf_mex_destroy(&c1_rhs46);
  sf_mex_destroy(&c1_lhs46);
  sf_mex_destroy(&c1_rhs47);
  sf_mex_destroy(&c1_lhs47);
  sf_mex_destroy(&c1_rhs48);
  sf_mex_destroy(&c1_lhs48);
  sf_mex_destroy(&c1_rhs49);
  sf_mex_destroy(&c1_lhs49);
  sf_mex_destroy(&c1_rhs50);
  sf_mex_destroy(&c1_lhs50);
  sf_mex_destroy(&c1_rhs51);
  sf_mex_destroy(&c1_lhs51);
  sf_mex_destroy(&c1_rhs52);
  sf_mex_destroy(&c1_lhs52);
  sf_mex_destroy(&c1_rhs53);
  sf_mex_destroy(&c1_lhs53);
  sf_mex_destroy(&c1_rhs54);
  sf_mex_destroy(&c1_lhs54);
  sf_mex_destroy(&c1_rhs55);
  sf_mex_destroy(&c1_lhs55);
  sf_mex_destroy(&c1_rhs56);
  sf_mex_destroy(&c1_lhs56);
  sf_mex_destroy(&c1_rhs57);
  sf_mex_destroy(&c1_lhs57);
  sf_mex_destroy(&c1_rhs58);
  sf_mex_destroy(&c1_lhs58);
  sf_mex_destroy(&c1_rhs59);
  sf_mex_destroy(&c1_lhs59);
  sf_mex_destroy(&c1_rhs60);
  sf_mex_destroy(&c1_lhs60);
  sf_mex_destroy(&c1_rhs61);
  sf_mex_destroy(&c1_lhs61);
  sf_mex_destroy(&c1_rhs62);
  sf_mex_destroy(&c1_lhs62);
  sf_mex_destroy(&c1_rhs63);
  sf_mex_destroy(&c1_lhs63);
}

static const mxArray *c1_emlrt_marshallOut(char * c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", c1_u, 15, 0U, 0U, 0U, 2, 1, strlen
    (c1_u)), FALSE);
  return c1_y;
}

static const mxArray *c1_b_emlrt_marshallOut(uint32_T c1_u)
{
  const mxArray *c1_y = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 7, 0U, 0U, 0U, 0), FALSE);
  return c1_y;
}

static void c1_b_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs64 = NULL;
  const mxArray *c1_lhs64 = NULL;
  const mxArray *c1_rhs65 = NULL;
  const mxArray *c1_lhs65 = NULL;
  const mxArray *c1_rhs66 = NULL;
  const mxArray *c1_lhs66 = NULL;
  const mxArray *c1_rhs67 = NULL;
  const mxArray *c1_lhs67 = NULL;
  const mxArray *c1_rhs68 = NULL;
  const mxArray *c1_lhs68 = NULL;
  const mxArray *c1_rhs69 = NULL;
  const mxArray *c1_lhs69 = NULL;
  const mxArray *c1_rhs70 = NULL;
  const mxArray *c1_lhs70 = NULL;
  const mxArray *c1_rhs71 = NULL;
  const mxArray *c1_lhs71 = NULL;
  const mxArray *c1_rhs72 = NULL;
  const mxArray *c1_lhs72 = NULL;
  const mxArray *c1_rhs73 = NULL;
  const mxArray *c1_lhs73 = NULL;
  const mxArray *c1_rhs74 = NULL;
  const mxArray *c1_lhs74 = NULL;
  const mxArray *c1_rhs75 = NULL;
  const mxArray *c1_lhs75 = NULL;
  const mxArray *c1_rhs76 = NULL;
  const mxArray *c1_lhs76 = NULL;
  const mxArray *c1_rhs77 = NULL;
  const mxArray *c1_lhs77 = NULL;
  const mxArray *c1_rhs78 = NULL;
  const mxArray *c1_lhs78 = NULL;
  const mxArray *c1_rhs79 = NULL;
  const mxArray *c1_lhs79 = NULL;
  const mxArray *c1_rhs80 = NULL;
  const mxArray *c1_lhs80 = NULL;
  const mxArray *c1_rhs81 = NULL;
  const mxArray *c1_lhs81 = NULL;
  const mxArray *c1_rhs82 = NULL;
  const mxArray *c1_lhs82 = NULL;
  const mxArray *c1_rhs83 = NULL;
  const mxArray *c1_lhs83 = NULL;
  const mxArray *c1_rhs84 = NULL;
  const mxArray *c1_lhs84 = NULL;
  const mxArray *c1_rhs85 = NULL;
  const mxArray *c1_lhs85 = NULL;
  const mxArray *c1_rhs86 = NULL;
  const mxArray *c1_lhs86 = NULL;
  const mxArray *c1_rhs87 = NULL;
  const mxArray *c1_lhs87 = NULL;
  const mxArray *c1_rhs88 = NULL;
  const mxArray *c1_lhs88 = NULL;
  const mxArray *c1_rhs89 = NULL;
  const mxArray *c1_lhs89 = NULL;
  const mxArray *c1_rhs90 = NULL;
  const mxArray *c1_lhs90 = NULL;
  const mxArray *c1_rhs91 = NULL;
  const mxArray *c1_lhs91 = NULL;
  const mxArray *c1_rhs92 = NULL;
  const mxArray *c1_lhs92 = NULL;
  const mxArray *c1_rhs93 = NULL;
  const mxArray *c1_lhs93 = NULL;
  const mxArray *c1_rhs94 = NULL;
  const mxArray *c1_lhs94 = NULL;
  const mxArray *c1_rhs95 = NULL;
  const mxArray *c1_lhs95 = NULL;
  const mxArray *c1_rhs96 = NULL;
  const mxArray *c1_lhs96 = NULL;
  const mxArray *c1_rhs97 = NULL;
  const mxArray *c1_lhs97 = NULL;
  const mxArray *c1_rhs98 = NULL;
  const mxArray *c1_lhs98 = NULL;
  const mxArray *c1_rhs99 = NULL;
  const mxArray *c1_lhs99 = NULL;
  const mxArray *c1_rhs100 = NULL;
  const mxArray *c1_lhs100 = NULL;
  const mxArray *c1_rhs101 = NULL;
  const mxArray *c1_lhs101 = NULL;
  const mxArray *c1_rhs102 = NULL;
  const mxArray *c1_lhs102 = NULL;
  const mxArray *c1_rhs103 = NULL;
  const mxArray *c1_lhs103 = NULL;
  const mxArray *c1_rhs104 = NULL;
  const mxArray *c1_lhs104 = NULL;
  const mxArray *c1_rhs105 = NULL;
  const mxArray *c1_lhs105 = NULL;
  const mxArray *c1_rhs106 = NULL;
  const mxArray *c1_lhs106 = NULL;
  const mxArray *c1_rhs107 = NULL;
  const mxArray *c1_lhs107 = NULL;
  const mxArray *c1_rhs108 = NULL;
  const mxArray *c1_lhs108 = NULL;
  const mxArray *c1_rhs109 = NULL;
  const mxArray *c1_lhs109 = NULL;
  const mxArray *c1_rhs110 = NULL;
  const mxArray *c1_lhs110 = NULL;
  const mxArray *c1_rhs111 = NULL;
  const mxArray *c1_lhs111 = NULL;
  const mxArray *c1_rhs112 = NULL;
  const mxArray *c1_lhs112 = NULL;
  const mxArray *c1_rhs113 = NULL;
  const mxArray *c1_lhs113 = NULL;
  const mxArray *c1_rhs114 = NULL;
  const mxArray *c1_lhs114 = NULL;
  const mxArray *c1_rhs115 = NULL;
  const mxArray *c1_lhs115 = NULL;
  const mxArray *c1_rhs116 = NULL;
  const mxArray *c1_lhs116 = NULL;
  const mxArray *c1_rhs117 = NULL;
  const mxArray *c1_lhs117 = NULL;
  const mxArray *c1_rhs118 = NULL;
  const mxArray *c1_lhs118 = NULL;
  const mxArray *c1_rhs119 = NULL;
  const mxArray *c1_lhs119 = NULL;
  const mxArray *c1_rhs120 = NULL;
  const mxArray *c1_lhs120 = NULL;
  const mxArray *c1_rhs121 = NULL;
  const mxArray *c1_lhs121 = NULL;
  const mxArray *c1_rhs122 = NULL;
  const mxArray *c1_lhs122 = NULL;
  const mxArray *c1_rhs123 = NULL;
  const mxArray *c1_lhs123 = NULL;
  const mxArray *c1_rhs124 = NULL;
  const mxArray *c1_lhs124 = NULL;
  const mxArray *c1_rhs125 = NULL;
  const mxArray *c1_lhs125 = NULL;
  const mxArray *c1_rhs126 = NULL;
  const mxArray *c1_lhs126 = NULL;
  const mxArray *c1_rhs127 = NULL;
  const mxArray *c1_lhs127 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m"),
                  "context", "context", 64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 64);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 64);
  sf_mex_assign(&c1_rhs64, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs64, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs64), "rhs", "rhs",
                  64);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs64), "lhs", "lhs",
                  64);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_rdivide"), "name",
                  "name", 65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m"),
                  "resolved", "resolved", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836780U), "fileTimeLo",
                  "fileTimeLo", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 65);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 65);
  sf_mex_assign(&c1_rhs65, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs65, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs65), "rhs", "rhs",
                  65);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs65), "lhs", "lhs",
                  65);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836780U), "fileTimeLo",
                  "fileTimeLo", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 66);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 66);
  sf_mex_assign(&c1_rhs66, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs66, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs66), "rhs", "rhs",
                  66);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs66), "lhs", "lhs",
                  66);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "context", "context", 67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 67);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 67);
  sf_mex_assign(&c1_rhs67, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs67, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs67), "rhs", "rhs",
                  67);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs67), "lhs", "lhs",
                  67);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 68);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 68);
  sf_mex_assign(&c1_rhs68, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs68, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs68), "rhs", "rhs",
                  68);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs68), "lhs", "lhs",
                  68);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m!common_checks"),
                  "context", "context", 69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 69);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 69);
  sf_mex_assign(&c1_rhs69, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs69, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs69), "rhs", "rhs",
                  69);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs69), "lhs", "lhs",
                  69);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name", 70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 70);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 70);
  sf_mex_assign(&c1_rhs70, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs70, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs70), "rhs", "rhs",
                  70);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs70), "lhs", "lhs",
                  70);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "context",
                  "context", 71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("rdivide"), "name", "name", 71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "resolved",
                  "resolved", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728280U), "fileTimeLo",
                  "fileTimeLo", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 71);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 71);
  sf_mex_assign(&c1_rhs71, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs71, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs71), "rhs", "rhs",
                  71);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs71), "lhs", "lhs",
                  71);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 72);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 72);
  sf_mex_assign(&c1_rhs72, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs72, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs72), "rhs", "rhs",
                  72);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs72), "lhs", "lhs",
                  72);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_compatible"),
                  "name", "name", 73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_compatible.m"),
                  "resolved", "resolved", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 73);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 73);
  sf_mex_assign(&c1_rhs73, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs73, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs73), "rhs", "rhs",
                  73);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs73), "lhs", "lhs",
                  73);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/rdivide.m"), "context",
                  "context", 74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_div"), "name", "name", 74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m"), "resolved",
                  "resolved", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728266U), "fileTimeLo",
                  "fileTimeLo", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 74);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 74);
  sf_mex_assign(&c1_rhs74, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs74, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs74), "rhs", "rhs",
                  74);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs74), "lhs", "lhs",
                  74);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 75);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 75);
  sf_mex_assign(&c1_rhs75, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs75, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs75), "rhs", "rhs",
                  75);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs75), "lhs", "lhs",
                  75);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"), "context",
                  "context", 76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 76);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 76);
  sf_mex_assign(&c1_rhs76, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs76, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs76), "rhs", "rhs",
                  76);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs76), "lhs", "lhs",
                  76);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_rdivide"), "name",
                  "name", 77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_rdivide.m"),
                  "resolved", "resolved", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836780U), "fileTimeLo",
                  "fileTimeLo", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 77);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 77);
  sf_mex_assign(&c1_rhs77, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs77, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs77), "rhs", "rhs",
                  77);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs77), "lhs", "lhs",
                  77);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1346528340U), "fileTimeLo",
                  "fileTimeLo", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 78);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 78);
  sf_mex_assign(&c1_rhs78, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs78, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs78), "rhs", "rhs",
                  78);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs78), "lhs", "lhs",
                  78);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m!eml_int_forloop_overflow_check_helper"),
                  "context", "context", 79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 79);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 79);
  sf_mex_assign(&c1_rhs79, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs79, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs79), "rhs", "rhs",
                  79);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs79), "lhs", "lhs",
                  79);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 80);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 80);
  sf_mex_assign(&c1_rhs80, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs80, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs80), "rhs", "rhs",
                  80);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs80), "lhs", "lhs",
                  80);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("cos"), "name", "name", 81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "resolved",
                  "resolved", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343848372U), "fileTimeLo",
                  "fileTimeLo", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 81);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 81);
  sf_mex_assign(&c1_rhs81, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs81, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs81), "rhs", "rhs",
                  81);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs81), "lhs", "lhs",
                  81);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/cos.m"), "context",
                  "context", 82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_cos"), "name",
                  "name", 82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_cos.m"),
                  "resolved", "resolved", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836722U), "fileTimeLo",
                  "fileTimeLo", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 82);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 82);
  sf_mex_assign(&c1_rhs82, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs82, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs82), "rhs", "rhs",
                  82);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs82), "lhs", "lhs",
                  82);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 83);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 83);
  sf_mex_assign(&c1_rhs83, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs83, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs83), "rhs", "rhs",
                  83);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs83), "lhs", "lhs",
                  83);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 84);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 84);
  sf_mex_assign(&c1_rhs84, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs84, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs84), "rhs", "rhs",
                  84);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs84), "lhs", "lhs",
                  84);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_1q_cosine_table"),
                  "context", "context", 85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("sin"), "name", "name", 85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "resolved",
                  "resolved", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343848386U), "fileTimeLo",
                  "fileTimeLo", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 85);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 85);
  sf_mex_assign(&c1_rhs85, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs85, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs85), "rhs", "rhs",
                  85);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs85), "lhs", "lhs",
                  85);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/sin.m"), "context",
                  "context", 86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_sin"), "name",
                  "name", 86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_sin.m"),
                  "resolved", "resolved", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836736U), "fileTimeLo",
                  "fileTimeLo", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 86);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 86);
  sf_mex_assign(&c1_rhs86, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs86, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs86), "rhs", "rhs",
                  86);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs86), "lhs", "lhs",
                  86);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_twiddle_table"),
                  "context", "context", 87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 87);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 87);
  sf_mex_assign(&c1_rhs87, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs87, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs87), "rhs", "rhs",
                  87);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs87), "lhs", "lhs",
                  87);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_twiddle_table"),
                  "context", "context", 88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836780U), "fileTimeLo",
                  "fileTimeLo", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 88);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 88);
  sf_mex_assign(&c1_rhs88, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs88, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs88), "rhs", "rhs",
                  88);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs88), "lhs", "lhs",
                  88);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_twiddle_table"),
                  "context", "context", 89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 89);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 89);
  sf_mex_assign(&c1_rhs89, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs89, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs89), "rhs", "rhs",
                  89);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs89), "lhs", "lhs",
                  89);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_twiddle_table"),
                  "context", "context", 90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1346528340U), "fileTimeLo",
                  "fileTimeLo", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 90);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 90);
  sf_mex_assign(&c1_rhs90, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs90, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs90), "rhs", "rhs",
                  90);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs90), "lhs", "lhs",
                  90);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!make_twiddle_table"),
                  "context", "context", 91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 91);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 91);
  sf_mex_assign(&c1_rhs91, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs91, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs91), "rhs", "rhs",
                  91);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs91), "lhs", "lhs",
                  91);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!ucls"), "context",
                  "context", 92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 92);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 92);
  sf_mex_assign(&c1_rhs92, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs92, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs92), "rhs", "rhs",
                  92);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs92), "lhs", "lhs",
                  92);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!ucls"), "context",
                  "context", 93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184980U), "fileTimeLo",
                  "fileTimeLo", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 93);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 93);
  sf_mex_assign(&c1_rhs93, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs93, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs93), "rhs", "rhs",
                  93);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs93), "lhs", "lhs",
                  93);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1346528340U), "fileTimeLo",
                  "fileTimeLo", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 94);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 94);
  sf_mex_assign(&c1_rhs94, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs94, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs94), "rhs", "rhs",
                  94);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs94), "lhs", "lhs",
                  94);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 95);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 95);
  sf_mex_assign(&c1_rhs95, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs95, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs95), "rhs", "rhs",
                  95);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs95), "lhs", "lhs",
                  95);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!eml_fft_bitrevidx"),
                  "context", "context", 96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 96);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 96);
  sf_mex_assign(&c1_rhs96, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs96, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs96), "rhs", "rhs",
                  96);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs96), "lhs", "lhs",
                  96);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 97);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 97);
  sf_mex_assign(&c1_rhs97, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs97, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs97), "rhs", "rhs",
                  97);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs97), "lhs", "lhs",
                  97);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_times"), "name",
                  "name", 98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_times.m"),
                  "resolved", "resolved", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836780U), "fileTimeLo",
                  "fileTimeLo", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 98);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 98);
  sf_mex_assign(&c1_rhs98, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs98, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs98), "rhs", "rhs",
                  98);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs98), "lhs", "lhs",
                  98);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name", 99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 99);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 99);
  sf_mex_assign(&c1_rhs99, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs99, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs99), "rhs", "rhs",
                  99);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs99), "lhs", "lhs",
                  99);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m!eml_fldiv"),
                  "context", "context", 100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 100);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 100);
  sf_mex_assign(&c1_rhs100, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs100, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs100), "rhs", "rhs",
                  100);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs100), "lhs", "lhs",
                  100);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m!eml_fldiv"),
                  "context", "context", 101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalexp_alloc"), "name",
                  "name", 101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalexp_alloc.m"),
                  "resolved", "resolved", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200540U), "fileTimeLo",
                  "fileTimeLo", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 101);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 101);
  sf_mex_assign(&c1_rhs101, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs101, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs101), "rhs", "rhs",
                  101);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs101), "lhs", "lhs",
                  101);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m!eml_fldiv"),
                  "context", "context", 102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 102);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 102);
  sf_mex_assign(&c1_rhs102, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs102, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs102), "rhs", "rhs",
                  102);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs102), "lhs", "lhs",
                  102);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_div.m!eml_fldiv"),
                  "context", "context", 103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 103);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 103);
  sf_mex_assign(&c1_rhs103, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs103, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs103), "rhs", "rhs",
                  103);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs103), "lhs", "lhs",
                  103);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("linspace"), "name", "name",
                  104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "resolved",
                  "resolved", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728258U), "fileTimeLo",
                  "fileTimeLo", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 104);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 104);
  sf_mex_assign(&c1_rhs104, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs104, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs104), "rhs", "rhs",
                  104);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs104), "lhs", "lhs",
                  104);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 105);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 105);
  sf_mex_assign(&c1_rhs105, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs105, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs105), "rhs", "rhs",
                  105);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs105), "lhs", "lhs",
                  105);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 106);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 106);
  sf_mex_assign(&c1_rhs106, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs106, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs106), "rhs", "rhs",
                  106);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs106), "lhs", "lhs",
                  106);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836726U), "fileTimeLo",
                  "fileTimeLo", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 107);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 107);
  sf_mex_assign(&c1_rhs107, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs107, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs107), "rhs", "rhs",
                  107);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs107), "lhs", "lhs",
                  107);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 108);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 108);
  sf_mex_assign(&c1_rhs108, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs108, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs108), "rhs", "rhs",
                  108);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs108), "lhs", "lhs",
                  108);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("realmax"), "name", "name", 109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "resolved",
                  "resolved", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307669242U), "fileTimeLo",
                  "fileTimeLo", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 109);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 109);
  sf_mex_assign(&c1_rhs109, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs109, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs109), "rhs", "rhs",
                  109);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs109), "lhs", "lhs",
                  109);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "context",
                  "context", 110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_realmax"), "name", "name",
                  110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "resolved",
                  "resolved", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 110);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 110);
  sf_mex_assign(&c1_rhs110, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs110, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs110), "rhs", "rhs",
                  110);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs110), "lhs", "lhs",
                  110);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "context",
                  "context", 111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 111);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 111);
  sf_mex_assign(&c1_rhs111, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs111, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs111), "rhs", "rhs",
                  111);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs111), "lhs", "lhs",
                  111);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmax.m"), "context",
                  "context", 112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 112);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 112);
  sf_mex_assign(&c1_rhs112, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs112, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs112), "rhs", "rhs",
                  112);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs112), "lhs", "lhs",
                  112);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 113);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 113);
  sf_mex_assign(&c1_rhs113, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs113, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs113), "rhs", "rhs",
                  113);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs113), "lhs", "lhs",
                  113);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/linspace.m"), "context",
                  "context", 114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 114);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 114);
  sf_mex_assign(&c1_rhs114, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs114, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs114), "rhs", "rhs",
                  114);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs114), "lhs", "lhs",
                  114);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 115);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 115);
  sf_mex_assign(&c1_rhs115, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs115, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs115), "rhs", "rhs",
                  115);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs115), "lhs", "lhs",
                  115);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "context", "context", 116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 116);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 116);
  sf_mex_assign(&c1_rhs116, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs116, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs116), "rhs", "rhs",
                  116);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs116), "lhs", "lhs",
                  116);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_abs.m"),
                  "context", "context", 117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_dlapy2"), "name", "name",
                  117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dlapy2.m"), "resolved",
                  "resolved", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1350428654U), "fileTimeLo",
                  "fileTimeLo", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 117);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 117);
  sf_mex_assign(&c1_rhs117, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs117, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs117), "rhs", "rhs",
                  117);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs117), "lhs", "lhs",
                  117);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("sum"), "name", "name", 118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "resolved",
                  "resolved", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728258U), "fileTimeLo",
                  "fileTimeLo", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 118);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 118);
  sf_mex_assign(&c1_rhs118, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs118, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs118), "rhs", "rhs",
                  118);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs118), "lhs", "lhs",
                  118);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 119);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 119);
  sf_mex_assign(&c1_rhs119, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs119, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs119), "rhs", "rhs",
                  119);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs119), "lhs", "lhs",
                  119);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isequal"), "name", "name", 120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836758U), "fileTimeLo",
                  "fileTimeLo", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 120);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 120);
  sf_mex_assign(&c1_rhs120, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs120, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs120), "rhs", "rhs",
                  120);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs120), "lhs", "lhs",
                  120);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "context",
                  "context", 121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_isequal_core"), "name",
                  "name", 121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m"),
                  "resolved", "resolved", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836786U), "fileTimeLo",
                  "fileTimeLo", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 121);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 121);
  sf_mex_assign(&c1_rhs121, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs121, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs121), "rhs", "rhs",
                  121);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs121), "lhs", "lhs",
                  121);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_const_nonsingleton_dim"),
                  "name", "name", 122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m"),
                  "resolved", "resolved", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836696U), "fileTimeLo",
                  "fileTimeLo", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 122);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 122);
  sf_mex_assign(&c1_rhs122, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs122, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs122), "rhs", "rhs",
                  122);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs122), "lhs", "lhs",
                  122);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 123);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 123);
  sf_mex_assign(&c1_rhs123, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs123, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs123), "rhs", "rhs",
                  123);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs123), "lhs", "lhs",
                  123);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 124);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 124);
  sf_mex_assign(&c1_rhs124, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs124, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs124), "rhs", "rhs",
                  124);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs124), "lhs", "lhs",
                  124);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "context",
                  "context", 125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1346528340U), "fileTimeLo",
                  "fileTimeLo", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 125);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 125);
  sf_mex_assign(&c1_rhs125, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs125, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs125), "rhs", "rhs",
                  125);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs125), "lhs", "lhs",
                  125);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("power"), "name", "name", 126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m"), "resolved",
                  "resolved", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728280U), "fileTimeLo",
                  "fileTimeLo", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 126);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 126);
  sf_mex_assign(&c1_rhs126, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs126, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs126), "rhs", "rhs",
                  126);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs126), "lhs", "lhs",
                  126);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/power.m!scalar_float_power"),
                  "context", "context", 127);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 127);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 127);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 127);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 127);
  sf_mex_assign(&c1_rhs127, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs127, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs127), "rhs", "rhs",
                  127);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs127), "lhs", "lhs",
                  127);
  sf_mex_destroy(&c1_rhs64);
  sf_mex_destroy(&c1_lhs64);
  sf_mex_destroy(&c1_rhs65);
  sf_mex_destroy(&c1_lhs65);
  sf_mex_destroy(&c1_rhs66);
  sf_mex_destroy(&c1_lhs66);
  sf_mex_destroy(&c1_rhs67);
  sf_mex_destroy(&c1_lhs67);
  sf_mex_destroy(&c1_rhs68);
  sf_mex_destroy(&c1_lhs68);
  sf_mex_destroy(&c1_rhs69);
  sf_mex_destroy(&c1_lhs69);
  sf_mex_destroy(&c1_rhs70);
  sf_mex_destroy(&c1_lhs70);
  sf_mex_destroy(&c1_rhs71);
  sf_mex_destroy(&c1_lhs71);
  sf_mex_destroy(&c1_rhs72);
  sf_mex_destroy(&c1_lhs72);
  sf_mex_destroy(&c1_rhs73);
  sf_mex_destroy(&c1_lhs73);
  sf_mex_destroy(&c1_rhs74);
  sf_mex_destroy(&c1_lhs74);
  sf_mex_destroy(&c1_rhs75);
  sf_mex_destroy(&c1_lhs75);
  sf_mex_destroy(&c1_rhs76);
  sf_mex_destroy(&c1_lhs76);
  sf_mex_destroy(&c1_rhs77);
  sf_mex_destroy(&c1_lhs77);
  sf_mex_destroy(&c1_rhs78);
  sf_mex_destroy(&c1_lhs78);
  sf_mex_destroy(&c1_rhs79);
  sf_mex_destroy(&c1_lhs79);
  sf_mex_destroy(&c1_rhs80);
  sf_mex_destroy(&c1_lhs80);
  sf_mex_destroy(&c1_rhs81);
  sf_mex_destroy(&c1_lhs81);
  sf_mex_destroy(&c1_rhs82);
  sf_mex_destroy(&c1_lhs82);
  sf_mex_destroy(&c1_rhs83);
  sf_mex_destroy(&c1_lhs83);
  sf_mex_destroy(&c1_rhs84);
  sf_mex_destroy(&c1_lhs84);
  sf_mex_destroy(&c1_rhs85);
  sf_mex_destroy(&c1_lhs85);
  sf_mex_destroy(&c1_rhs86);
  sf_mex_destroy(&c1_lhs86);
  sf_mex_destroy(&c1_rhs87);
  sf_mex_destroy(&c1_lhs87);
  sf_mex_destroy(&c1_rhs88);
  sf_mex_destroy(&c1_lhs88);
  sf_mex_destroy(&c1_rhs89);
  sf_mex_destroy(&c1_lhs89);
  sf_mex_destroy(&c1_rhs90);
  sf_mex_destroy(&c1_lhs90);
  sf_mex_destroy(&c1_rhs91);
  sf_mex_destroy(&c1_lhs91);
  sf_mex_destroy(&c1_rhs92);
  sf_mex_destroy(&c1_lhs92);
  sf_mex_destroy(&c1_rhs93);
  sf_mex_destroy(&c1_lhs93);
  sf_mex_destroy(&c1_rhs94);
  sf_mex_destroy(&c1_lhs94);
  sf_mex_destroy(&c1_rhs95);
  sf_mex_destroy(&c1_lhs95);
  sf_mex_destroy(&c1_rhs96);
  sf_mex_destroy(&c1_lhs96);
  sf_mex_destroy(&c1_rhs97);
  sf_mex_destroy(&c1_lhs97);
  sf_mex_destroy(&c1_rhs98);
  sf_mex_destroy(&c1_lhs98);
  sf_mex_destroy(&c1_rhs99);
  sf_mex_destroy(&c1_lhs99);
  sf_mex_destroy(&c1_rhs100);
  sf_mex_destroy(&c1_lhs100);
  sf_mex_destroy(&c1_rhs101);
  sf_mex_destroy(&c1_lhs101);
  sf_mex_destroy(&c1_rhs102);
  sf_mex_destroy(&c1_lhs102);
  sf_mex_destroy(&c1_rhs103);
  sf_mex_destroy(&c1_lhs103);
  sf_mex_destroy(&c1_rhs104);
  sf_mex_destroy(&c1_lhs104);
  sf_mex_destroy(&c1_rhs105);
  sf_mex_destroy(&c1_lhs105);
  sf_mex_destroy(&c1_rhs106);
  sf_mex_destroy(&c1_lhs106);
  sf_mex_destroy(&c1_rhs107);
  sf_mex_destroy(&c1_lhs107);
  sf_mex_destroy(&c1_rhs108);
  sf_mex_destroy(&c1_lhs108);
  sf_mex_destroy(&c1_rhs109);
  sf_mex_destroy(&c1_lhs109);
  sf_mex_destroy(&c1_rhs110);
  sf_mex_destroy(&c1_lhs110);
  sf_mex_destroy(&c1_rhs111);
  sf_mex_destroy(&c1_lhs111);
  sf_mex_destroy(&c1_rhs112);
  sf_mex_destroy(&c1_lhs112);
  sf_mex_destroy(&c1_rhs113);
  sf_mex_destroy(&c1_lhs113);
  sf_mex_destroy(&c1_rhs114);
  sf_mex_destroy(&c1_lhs114);
  sf_mex_destroy(&c1_rhs115);
  sf_mex_destroy(&c1_lhs115);
  sf_mex_destroy(&c1_rhs116);
  sf_mex_destroy(&c1_lhs116);
  sf_mex_destroy(&c1_rhs117);
  sf_mex_destroy(&c1_lhs117);
  sf_mex_destroy(&c1_rhs118);
  sf_mex_destroy(&c1_lhs118);
  sf_mex_destroy(&c1_rhs119);
  sf_mex_destroy(&c1_lhs119);
  sf_mex_destroy(&c1_rhs120);
  sf_mex_destroy(&c1_lhs120);
  sf_mex_destroy(&c1_rhs121);
  sf_mex_destroy(&c1_lhs121);
  sf_mex_destroy(&c1_rhs122);
  sf_mex_destroy(&c1_lhs122);
  sf_mex_destroy(&c1_rhs123);
  sf_mex_destroy(&c1_lhs123);
  sf_mex_destroy(&c1_rhs124);
  sf_mex_destroy(&c1_lhs124);
  sf_mex_destroy(&c1_rhs125);
  sf_mex_destroy(&c1_lhs125);
  sf_mex_destroy(&c1_rhs126);
  sf_mex_destroy(&c1_lhs126);
  sf_mex_destroy(&c1_rhs127);
  sf_mex_destroy(&c1_lhs127);
}

static void c1_c_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs128 = NULL;
  const mxArray *c1_lhs128 = NULL;
  const mxArray *c1_rhs129 = NULL;
  const mxArray *c1_lhs129 = NULL;
  const mxArray *c1_rhs130 = NULL;
  const mxArray *c1_lhs130 = NULL;
  const mxArray *c1_rhs131 = NULL;
  const mxArray *c1_lhs131 = NULL;
  const mxArray *c1_rhs132 = NULL;
  const mxArray *c1_lhs132 = NULL;
  const mxArray *c1_rhs133 = NULL;
  const mxArray *c1_lhs133 = NULL;
  const mxArray *c1_rhs134 = NULL;
  const mxArray *c1_lhs134 = NULL;
  const mxArray *c1_rhs135 = NULL;
  const mxArray *c1_lhs135 = NULL;
  const mxArray *c1_rhs136 = NULL;
  const mxArray *c1_lhs136 = NULL;
  const mxArray *c1_rhs137 = NULL;
  const mxArray *c1_lhs137 = NULL;
  const mxArray *c1_rhs138 = NULL;
  const mxArray *c1_lhs138 = NULL;
  const mxArray *c1_rhs139 = NULL;
  const mxArray *c1_lhs139 = NULL;
  const mxArray *c1_rhs140 = NULL;
  const mxArray *c1_lhs140 = NULL;
  const mxArray *c1_rhs141 = NULL;
  const mxArray *c1_lhs141 = NULL;
  const mxArray *c1_rhs142 = NULL;
  const mxArray *c1_lhs142 = NULL;
  const mxArray *c1_rhs143 = NULL;
  const mxArray *c1_lhs143 = NULL;
  const mxArray *c1_rhs144 = NULL;
  const mxArray *c1_lhs144 = NULL;
  const mxArray *c1_rhs145 = NULL;
  const mxArray *c1_lhs145 = NULL;
  const mxArray *c1_rhs146 = NULL;
  const mxArray *c1_lhs146 = NULL;
  const mxArray *c1_rhs147 = NULL;
  const mxArray *c1_lhs147 = NULL;
  const mxArray *c1_rhs148 = NULL;
  const mxArray *c1_lhs148 = NULL;
  const mxArray *c1_rhs149 = NULL;
  const mxArray *c1_lhs149 = NULL;
  const mxArray *c1_rhs150 = NULL;
  const mxArray *c1_lhs150 = NULL;
  const mxArray *c1_rhs151 = NULL;
  const mxArray *c1_lhs151 = NULL;
  const mxArray *c1_rhs152 = NULL;
  const mxArray *c1_lhs152 = NULL;
  const mxArray *c1_rhs153 = NULL;
  const mxArray *c1_lhs153 = NULL;
  const mxArray *c1_rhs154 = NULL;
  const mxArray *c1_lhs154 = NULL;
  const mxArray *c1_rhs155 = NULL;
  const mxArray *c1_lhs155 = NULL;
  const mxArray *c1_rhs156 = NULL;
  const mxArray *c1_lhs156 = NULL;
  const mxArray *c1_rhs157 = NULL;
  const mxArray *c1_lhs157 = NULL;
  const mxArray *c1_rhs158 = NULL;
  const mxArray *c1_lhs158 = NULL;
  const mxArray *c1_rhs159 = NULL;
  const mxArray *c1_lhs159 = NULL;
  const mxArray *c1_rhs160 = NULL;
  const mxArray *c1_lhs160 = NULL;
  const mxArray *c1_rhs161 = NULL;
  const mxArray *c1_lhs161 = NULL;
  const mxArray *c1_rhs162 = NULL;
  const mxArray *c1_lhs162 = NULL;
  const mxArray *c1_rhs163 = NULL;
  const mxArray *c1_lhs163 = NULL;
  const mxArray *c1_rhs164 = NULL;
  const mxArray *c1_lhs164 = NULL;
  const mxArray *c1_rhs165 = NULL;
  const mxArray *c1_lhs165 = NULL;
  const mxArray *c1_rhs166 = NULL;
  const mxArray *c1_lhs166 = NULL;
  const mxArray *c1_rhs167 = NULL;
  const mxArray *c1_lhs167 = NULL;
  const mxArray *c1_rhs168 = NULL;
  const mxArray *c1_lhs168 = NULL;
  const mxArray *c1_rhs169 = NULL;
  const mxArray *c1_lhs169 = NULL;
  const mxArray *c1_rhs170 = NULL;
  const mxArray *c1_lhs170 = NULL;
  const mxArray *c1_rhs171 = NULL;
  const mxArray *c1_lhs171 = NULL;
  const mxArray *c1_rhs172 = NULL;
  const mxArray *c1_lhs172 = NULL;
  const mxArray *c1_rhs173 = NULL;
  const mxArray *c1_lhs173 = NULL;
  const mxArray *c1_rhs174 = NULL;
  const mxArray *c1_lhs174 = NULL;
  const mxArray *c1_rhs175 = NULL;
  const mxArray *c1_lhs175 = NULL;
  const mxArray *c1_rhs176 = NULL;
  const mxArray *c1_lhs176 = NULL;
  const mxArray *c1_rhs177 = NULL;
  const mxArray *c1_lhs177 = NULL;
  const mxArray *c1_rhs178 = NULL;
  const mxArray *c1_lhs178 = NULL;
  const mxArray *c1_rhs179 = NULL;
  const mxArray *c1_lhs179 = NULL;
  const mxArray *c1_rhs180 = NULL;
  const mxArray *c1_lhs180 = NULL;
  const mxArray *c1_rhs181 = NULL;
  const mxArray *c1_lhs181 = NULL;
  const mxArray *c1_rhs182 = NULL;
  const mxArray *c1_lhs182 = NULL;
  const mxArray *c1_rhs183 = NULL;
  const mxArray *c1_lhs183 = NULL;
  const mxArray *c1_rhs184 = NULL;
  const mxArray *c1_lhs184 = NULL;
  const mxArray *c1_rhs185 = NULL;
  const mxArray *c1_lhs185 = NULL;
  const mxArray *c1_rhs186 = NULL;
  const mxArray *c1_lhs186 = NULL;
  const mxArray *c1_rhs187 = NULL;
  const mxArray *c1_lhs187 = NULL;
  const mxArray *c1_rhs188 = NULL;
  const mxArray *c1_lhs188 = NULL;
  const mxArray *c1_rhs189 = NULL;
  const mxArray *c1_lhs189 = NULL;
  const mxArray *c1_rhs190 = NULL;
  const mxArray *c1_lhs190 = NULL;
  const mxArray *c1_rhs191 = NULL;
  const mxArray *c1_lhs191 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303164206U), "fileTimeLo",
                  "fileTimeLo", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 128);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 128);
  sf_mex_assign(&c1_rhs128, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs128, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs128), "rhs", "rhs",
                  128);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs128), "lhs", "lhs",
                  128);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 129);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 129);
  sf_mex_assign(&c1_rhs129, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs129, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs129), "rhs", "rhs",
                  129);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs129), "lhs", "lhs",
                  129);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 130);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 130);
  sf_mex_assign(&c1_rhs130, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs130, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs130), "rhs", "rhs",
                  130);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs130), "lhs", "lhs",
                  130);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m"),
                  "context", "context", 131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 131);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 131);
  sf_mex_assign(&c1_rhs131, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs131, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs131), "rhs", "rhs",
                  131);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs131), "lhs", "lhs",
                  131);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303164206U), "fileTimeLo",
                  "fileTimeLo", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 132);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 132);
  sf_mex_assign(&c1_rhs132, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs132, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs132), "rhs", "rhs",
                  132);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs132), "lhs", "lhs",
                  132);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "context", "context", 133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("FindPitch_simulink"), "name",
                  "name", 133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "resolved", "resolved", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1433593308U), "fileTimeLo",
                  "fileTimeLo", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 133);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 133);
  sf_mex_assign(&c1_rhs133, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs133, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs133), "rhs", "rhs",
                  133);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs133), "lhs", "lhs",
                  133);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("piso_ruido"), "name", "name",
                  134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "resolved", "resolved", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1433590554U), "fileTimeLo",
                  "fileTimeLo", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 134);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 134);
  sf_mex_assign(&c1_rhs134, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs134, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs134), "rhs", "rhs",
                  134);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs134), "lhs", "lhs",
                  134);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "context", "context", 135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303164206U), "fileTimeLo",
                  "fileTimeLo", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 135);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 135);
  sf_mex_assign(&c1_rhs135, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs135, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs135), "rhs", "rhs",
                  135);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs135), "lhs", "lhs",
                  135);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "context", "context", 136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("fft"), "name", "name", 136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/fft.m"), "resolved",
                  "resolved", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836688U), "fileTimeLo",
                  "fileTimeLo", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 136);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 136);
  sf_mex_assign(&c1_rhs136, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs136, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs136), "rhs", "rhs",
                  136);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs136), "lhs", "lhs",
                  136);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("max"), "name", "name", 137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273316U), "fileTimeLo",
                  "fileTimeLo", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 137);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 137);
  sf_mex_assign(&c1_rhs137, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs137, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs137), "rhs", "rhs",
                  137);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs137), "lhs", "lhs",
                  137);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_scalar_bin_extremum"),
                  "context", "context", 138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 138);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 138);
  sf_mex_assign(&c1_rhs138, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs138, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs138), "rhs", "rhs",
                  138);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs138), "lhs", "lhs",
                  138);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_dim_to_fore_permutation"),
                  "name", "name", 139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "resolved", "resolved", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836696U), "fileTimeLo",
                  "fileTimeLo", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 139);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 139);
  sf_mex_assign(&c1_rhs139, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs139, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs139), "rhs", "rhs",
                  139);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs139), "lhs", "lhs",
                  139);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 140);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 140);
  sf_mex_assign(&c1_rhs140, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs140, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs140), "rhs", "rhs",
                  140);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs140), "lhs", "lhs",
                  140);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 141);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 141);
  sf_mex_assign(&c1_rhs141, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs141, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs141), "rhs", "rhs",
                  141);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs141), "lhs", "lhs",
                  141);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("min"), "name", "name", 142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273318U), "fileTimeLo",
                  "fileTimeLo", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 142);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 142);
  sf_mex_assign(&c1_rhs142, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs142, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs142), "rhs", "rhs",
                  142);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs142), "lhs", "lhs",
                  142);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("max"), "name", "name", 143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273316U), "fileTimeLo",
                  "fileTimeLo", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 143);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 143);
  sf_mex_assign(&c1_rhs143, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs143, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs143), "rhs", "rhs",
                  143);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs143), "lhs", "lhs",
                  143);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1366180242U), "fileTimeLo",
                  "fileTimeLo", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 144);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 144);
  sf_mex_assign(&c1_rhs144, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs144, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs144), "rhs", "rhs",
                  144);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs144), "lhs", "lhs",
                  144);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1366180242U), "fileTimeLo",
                  "fileTimeLo", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 145);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 145);
  sf_mex_assign(&c1_rhs145, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs145, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs145), "rhs", "rhs",
                  145);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs145), "lhs", "lhs",
                  145);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 146);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 146);
  sf_mex_assign(&c1_rhs146, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs146, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs146), "rhs", "rhs",
                  146);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs146), "lhs", "lhs",
                  146);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 147);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 147);
  sf_mex_assign(&c1_rhs147, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs147, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs147), "rhs", "rhs",
                  147);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs147), "lhs", "lhs",
                  147);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "context",
                  "context", 148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 148);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 148);
  sf_mex_assign(&c1_rhs148, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs148, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs148), "rhs", "rhs",
                  148);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs148), "lhs", "lhs",
                  148);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 149);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 149);
  sf_mex_assign(&c1_rhs149, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs149, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs149), "rhs", "rhs",
                  149);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs149), "lhs", "lhs",
                  149);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 150);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 150);
  sf_mex_assign(&c1_rhs150, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs150, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs150), "rhs", "rhs",
                  150);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs150), "lhs", "lhs",
                  150);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmin"), "name", "name", 151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmin.m"), "resolved",
                  "resolved", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 151);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 151);
  sf_mex_assign(&c1_rhs151, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs151, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs151), "rhs", "rhs",
                  151);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs151), "lhs", "lhs",
                  151);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 152);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 152);
  sf_mex_assign(&c1_rhs152, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs152, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs152), "rhs", "rhs",
                  152);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs152), "lhs", "lhs",
                  152);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_integer_colon_dispatcher"),
                  "context", "context", 153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836784U), "fileTimeLo",
                  "fileTimeLo", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 153);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 153);
  sf_mex_assign(&c1_rhs153, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs153, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs153), "rhs", "rhs",
                  153);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs153), "lhs", "lhs",
                  153);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_unsigned_class"), "name",
                  "name", 154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_unsigned_class.m"),
                  "resolved", "resolved", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184980U), "fileTimeLo",
                  "fileTimeLo", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 154);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 154);
  sf_mex_assign(&c1_rhs154, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs154, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs154), "rhs", "rhs",
                  154);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs154), "lhs", "lhs",
                  154);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 155);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 155);
  sf_mex_assign(&c1_rhs155, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs155, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs155), "rhs", "rhs",
                  155);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs155), "lhs", "lhs",
                  155);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 156);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 156);
  sf_mex_assign(&c1_rhs156, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs156, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs156), "rhs", "rhs",
                  156);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs156), "lhs", "lhs",
                  156);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_isa_uint"), "name", "name",
                  157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isa_uint.m"), "resolved",
                  "resolved", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836784U), "fileTimeLo",
                  "fileTimeLo", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 157);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 157);
  sf_mex_assign(&c1_rhs157, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs157, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs157), "rhs", "rhs",
                  157);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs157), "lhs", "lhs",
                  157);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!integer_colon_length_nonnegd"),
                  "context", "context", 158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 158);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 158);
  sf_mex_assign(&c1_rhs158, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs158, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs158), "rhs", "rhs",
                  158);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs158), "lhs", "lhs",
                  158);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_minus"), "name",
                  "name", 159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m"),
                  "resolved", "resolved", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 159);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 159);
  sf_mex_assign(&c1_rhs159, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs159, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs159), "rhs", "rhs",
                  159);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs159), "lhs", "lhs",
                  159);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_dim_to_fore_permutation.m"),
                  "context", "context", 160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 160);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 160);
  sf_mex_assign(&c1_rhs160, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs160, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs160), "rhs", "rhs",
                  160);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs160), "lhs", "lhs",
                  160);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("permute"), "name", "name", 161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/permute.m"), "resolved",
                  "resolved", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372349104U), "fileTimeLo",
                  "fileTimeLo", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 161);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 161);
  sf_mex_assign(&c1_rhs161, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs161, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs161), "rhs", "rhs",
                  161);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs161), "lhs", "lhs",
                  161);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/permute.m"), "context",
                  "context", 162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 162);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 162);
  sf_mex_assign(&c1_rhs162, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs162, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs162), "rhs", "rhs",
                  162);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs162), "lhs", "lhs",
                  162);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/permute.m"), "context",
                  "context", 163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_is_permutation"), "name",
                  "name", 163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_permutation.m"),
                  "resolved", "resolved", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 163);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 163);
  sf_mex_assign(&c1_rhs163, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs163, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs163), "rhs", "rhs",
                  163);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs163), "lhs", "lhs",
                  163);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_permutation.m"),
                  "context", "context", 164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836726U), "fileTimeLo",
                  "fileTimeLo", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 164);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 164);
  sf_mex_assign(&c1_rhs164, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs164, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs164), "rhs", "rhs",
                  164);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs164), "lhs", "lhs",
                  164);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_permutation.m"),
                  "context", "context", 165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("all"), "name", "name", 165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "resolved",
                  "resolved", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728276U), "fileTimeLo",
                  "fileTimeLo", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 165);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 165);
  sf_mex_assign(&c1_rhs165, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs165, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs165), "rhs", "rhs",
                  165);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs165), "lhs", "lhs",
                  165);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 166);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 166);
  sf_mex_assign(&c1_rhs166, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs166, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs166), "rhs", "rhs",
                  166);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs166), "lhs", "lhs",
                  166);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/all.m"), "context", "context",
                  167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_all_or_any"), "name",
                  "name", 167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"),
                  "resolved", "resolved", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836694U), "fileTimeLo",
                  "fileTimeLo", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 167);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 167);
  sf_mex_assign(&c1_rhs167, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs167, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs167), "rhs", "rhs",
                  167);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs167), "lhs", "lhs",
                  167);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"), "context",
                  "context", 168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isequal"), "name", "name", 168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m"), "resolved",
                  "resolved", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836758U), "fileTimeLo",
                  "fileTimeLo", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 168);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 168);
  sf_mex_assign(&c1_rhs168, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs168, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs168), "rhs", "rhs",
                  168);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs168), "lhs", "lhs",
                  168);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_all_or_any.m"), "context",
                  "context", 169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_const_nonsingleton_dim"),
                  "name", "name", 169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("logical"), "dominantType",
                  "dominantType", 169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m"),
                  "resolved", "resolved", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836696U), "fileTimeLo",
                  "fileTimeLo", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 169);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 169);
  sf_mex_assign(&c1_rhs169, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs169, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs169), "rhs", "rhs",
                  169);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs169), "lhs", "lhs",
                  169);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_fft"), "name", "name", 170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "resolved",
                  "resolved", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728268U), "fileTimeLo",
                  "fileTimeLo", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 170);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 170);
  sf_mex_assign(&c1_rhs170, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs170, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs170), "rhs", "rhs",
                  170);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs170), "lhs", "lhs",
                  170);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_assert_valid_dim"), "name",
                  "name", 171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "resolved", "resolved", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728266U), "fileTimeLo",
                  "fileTimeLo", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 171);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 171);
  sf_mex_assign(&c1_rhs171, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs171, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs171), "rhs", "rhs",
                  171);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs171), "lhs", "lhs",
                  171);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "context", "context", 172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 172);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 172);
  sf_mex_assign(&c1_rhs172, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs172, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs172), "rhs", "rhs",
                  172);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs172), "lhs", "lhs",
                  172);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "context", "context", 173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_floor"), "name",
                  "name", 173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_floor.m"),
                  "resolved", "resolved", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836726U), "fileTimeLo",
                  "fileTimeLo", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 173);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 173);
  sf_mex_assign(&c1_rhs173, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs173, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs173), "rhs", "rhs",
                  173);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs173), "lhs", "lhs",
                  173);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "context", "context", 174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 174);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 174);
  sf_mex_assign(&c1_rhs174, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs174, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs174), "rhs", "rhs",
                  174);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs174), "lhs", "lhs",
                  174);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_valid_dim.m"),
                  "context", "context", 175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 175);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 175);
  sf_mex_assign(&c1_rhs175, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs175, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs175), "rhs", "rhs",
                  175);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs175), "lhs", "lhs",
                  175);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 176);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 176);
  sf_mex_assign(&c1_rhs176, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs176, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs176), "rhs", "rhs",
                  176);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs176), "lhs", "lhs",
                  176);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_size_ispow2"), "name",
                  "name", 177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_size_ispow2.m"),
                  "resolved", "resolved", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728270U), "fileTimeLo",
                  "fileTimeLo", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 177);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 177);
  sf_mex_assign(&c1_rhs177, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs177, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs177), "rhs", "rhs",
                  177);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs177), "lhs", "lhs",
                  177);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m!r2br_r2dit_trig"),
                  "context", "context", 178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexIntRelop"),
                  "name", "name", 178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/indexIntRelop.m"),
                  "resolved", "resolved", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742722U), "fileTimeLo",
                  "fileTimeLo", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 178);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 178);
  sf_mex_assign(&c1_rhs178, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs178, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs178), "rhs", "rhs",
                  178);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs178), "lhs", "lhs",
                  178);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_fft.m"), "context",
                  "context", 179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("ipermute"), "name", "name",
                  179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ipermute.m"), "resolved",
                  "resolved", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836756U), "fileTimeLo",
                  "fileTimeLo", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 179);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 179);
  sf_mex_assign(&c1_rhs179, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs179, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs179), "rhs", "rhs",
                  179);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs179), "lhs", "lhs",
                  179);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ipermute.m"), "context",
                  "context", 180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_is_permutation"), "name",
                  "name", 180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_is_permutation.m"),
                  "resolved", "resolved", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 180);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 180);
  sf_mex_assign(&c1_rhs180, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs180, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs180), "rhs", "rhs",
                  180);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs180), "lhs", "lhs",
                  180);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ipermute.m!invperm"),
                  "context", "context", 181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 181);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 181);
  sf_mex_assign(&c1_rhs181, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs181, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs181), "rhs", "rhs",
                  181);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs181), "lhs", "lhs",
                  181);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/ipermute.m"), "context",
                  "context", 182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("permute"), "name", "name", 182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/permute.m"), "resolved",
                  "resolved", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1372349104U), "fileTimeLo",
                  "fileTimeLo", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 182);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 182);
  sf_mex_assign(&c1_rhs182, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs182, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs182), "rhs", "rhs",
                  182);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs182), "lhs", "lhs",
                  182);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "context", "context", 183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 183);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 183);
  sf_mex_assign(&c1_rhs183, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs183, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs183), "rhs", "rhs",
                  183);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs183), "lhs", "lhs",
                  183);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "context", "context", 184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 184);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 184);
  sf_mex_assign(&c1_rhs184, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs184, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs184), "rhs", "rhs",
                  184);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs184), "lhs", "lhs",
                  184);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "context", "context", 185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("sum"), "name", "name", 185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/sum.m"), "resolved",
                  "resolved", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728258U), "fileTimeLo",
                  "fileTimeLo", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 185);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 185);
  sf_mex_assign(&c1_rhs185, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs185, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs185), "rhs", "rhs",
                  185);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs185), "lhs", "lhs",
                  185);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/piso_ruido.m"),
                  "context", "context", 186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 186);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 186);
  sf_mex_assign(&c1_rhs186, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs186, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs186), "rhs", "rhs",
                  186);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs186), "lhs", "lhs",
                  186);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("hann"), "name", "name", 187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/hann.m"), "resolved", "resolved", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200916U), "fileTimeLo",
                  "fileTimeLo", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 187);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 187);
  sf_mex_assign(&c1_rhs187, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs187, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs187), "rhs", "rhs",
                  187);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs187), "lhs", "lhs",
                  187);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/hann.m"), "context", "context", 188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_assert_all_constant"),
                  "name", "name", 188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_assert_all_constant.m"),
                  "resolved", "resolved", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836694U), "fileTimeLo",
                  "fileTimeLo", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 188);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 188);
  sf_mex_assign(&c1_rhs188, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs188, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs188), "rhs", "rhs",
                  188);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs188), "lhs", "lhs",
                  188);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("xcorr"), "name", "name", 189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/xcorr.m"), "resolved", "resolved", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1358200922U), "fileTimeLo",
                  "fileTimeLo", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 189);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 189);
  sf_mex_assign(&c1_rhs189, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs189, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs189), "rhs", "rhs",
                  189);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs189), "lhs", "lhs",
                  189);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/xcorr.m!crosscorr"), "context",
                  "context", 190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 190);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 190);
  sf_mex_assign(&c1_rhs190, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs190, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs190), "rhs", "rhs",
                  190);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs190), "lhs", "lhs",
                  190);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/xcorr.m!crosscorr"), "context",
                  "context", 191);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 191);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 191);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 191);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 191);
  sf_mex_assign(&c1_rhs191, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs191, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs191), "rhs", "rhs",
                  191);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs191), "lhs", "lhs",
                  191);
  sf_mex_destroy(&c1_rhs128);
  sf_mex_destroy(&c1_lhs128);
  sf_mex_destroy(&c1_rhs129);
  sf_mex_destroy(&c1_lhs129);
  sf_mex_destroy(&c1_rhs130);
  sf_mex_destroy(&c1_lhs130);
  sf_mex_destroy(&c1_rhs131);
  sf_mex_destroy(&c1_lhs131);
  sf_mex_destroy(&c1_rhs132);
  sf_mex_destroy(&c1_lhs132);
  sf_mex_destroy(&c1_rhs133);
  sf_mex_destroy(&c1_lhs133);
  sf_mex_destroy(&c1_rhs134);
  sf_mex_destroy(&c1_lhs134);
  sf_mex_destroy(&c1_rhs135);
  sf_mex_destroy(&c1_lhs135);
  sf_mex_destroy(&c1_rhs136);
  sf_mex_destroy(&c1_lhs136);
  sf_mex_destroy(&c1_rhs137);
  sf_mex_destroy(&c1_lhs137);
  sf_mex_destroy(&c1_rhs138);
  sf_mex_destroy(&c1_lhs138);
  sf_mex_destroy(&c1_rhs139);
  sf_mex_destroy(&c1_lhs139);
  sf_mex_destroy(&c1_rhs140);
  sf_mex_destroy(&c1_lhs140);
  sf_mex_destroy(&c1_rhs141);
  sf_mex_destroy(&c1_lhs141);
  sf_mex_destroy(&c1_rhs142);
  sf_mex_destroy(&c1_lhs142);
  sf_mex_destroy(&c1_rhs143);
  sf_mex_destroy(&c1_lhs143);
  sf_mex_destroy(&c1_rhs144);
  sf_mex_destroy(&c1_lhs144);
  sf_mex_destroy(&c1_rhs145);
  sf_mex_destroy(&c1_lhs145);
  sf_mex_destroy(&c1_rhs146);
  sf_mex_destroy(&c1_lhs146);
  sf_mex_destroy(&c1_rhs147);
  sf_mex_destroy(&c1_lhs147);
  sf_mex_destroy(&c1_rhs148);
  sf_mex_destroy(&c1_lhs148);
  sf_mex_destroy(&c1_rhs149);
  sf_mex_destroy(&c1_lhs149);
  sf_mex_destroy(&c1_rhs150);
  sf_mex_destroy(&c1_lhs150);
  sf_mex_destroy(&c1_rhs151);
  sf_mex_destroy(&c1_lhs151);
  sf_mex_destroy(&c1_rhs152);
  sf_mex_destroy(&c1_lhs152);
  sf_mex_destroy(&c1_rhs153);
  sf_mex_destroy(&c1_lhs153);
  sf_mex_destroy(&c1_rhs154);
  sf_mex_destroy(&c1_lhs154);
  sf_mex_destroy(&c1_rhs155);
  sf_mex_destroy(&c1_lhs155);
  sf_mex_destroy(&c1_rhs156);
  sf_mex_destroy(&c1_lhs156);
  sf_mex_destroy(&c1_rhs157);
  sf_mex_destroy(&c1_lhs157);
  sf_mex_destroy(&c1_rhs158);
  sf_mex_destroy(&c1_lhs158);
  sf_mex_destroy(&c1_rhs159);
  sf_mex_destroy(&c1_lhs159);
  sf_mex_destroy(&c1_rhs160);
  sf_mex_destroy(&c1_lhs160);
  sf_mex_destroy(&c1_rhs161);
  sf_mex_destroy(&c1_lhs161);
  sf_mex_destroy(&c1_rhs162);
  sf_mex_destroy(&c1_lhs162);
  sf_mex_destroy(&c1_rhs163);
  sf_mex_destroy(&c1_lhs163);
  sf_mex_destroy(&c1_rhs164);
  sf_mex_destroy(&c1_lhs164);
  sf_mex_destroy(&c1_rhs165);
  sf_mex_destroy(&c1_lhs165);
  sf_mex_destroy(&c1_rhs166);
  sf_mex_destroy(&c1_lhs166);
  sf_mex_destroy(&c1_rhs167);
  sf_mex_destroy(&c1_lhs167);
  sf_mex_destroy(&c1_rhs168);
  sf_mex_destroy(&c1_lhs168);
  sf_mex_destroy(&c1_rhs169);
  sf_mex_destroy(&c1_lhs169);
  sf_mex_destroy(&c1_rhs170);
  sf_mex_destroy(&c1_lhs170);
  sf_mex_destroy(&c1_rhs171);
  sf_mex_destroy(&c1_lhs171);
  sf_mex_destroy(&c1_rhs172);
  sf_mex_destroy(&c1_lhs172);
  sf_mex_destroy(&c1_rhs173);
  sf_mex_destroy(&c1_lhs173);
  sf_mex_destroy(&c1_rhs174);
  sf_mex_destroy(&c1_lhs174);
  sf_mex_destroy(&c1_rhs175);
  sf_mex_destroy(&c1_lhs175);
  sf_mex_destroy(&c1_rhs176);
  sf_mex_destroy(&c1_lhs176);
  sf_mex_destroy(&c1_rhs177);
  sf_mex_destroy(&c1_lhs177);
  sf_mex_destroy(&c1_rhs178);
  sf_mex_destroy(&c1_lhs178);
  sf_mex_destroy(&c1_rhs179);
  sf_mex_destroy(&c1_lhs179);
  sf_mex_destroy(&c1_rhs180);
  sf_mex_destroy(&c1_lhs180);
  sf_mex_destroy(&c1_rhs181);
  sf_mex_destroy(&c1_lhs181);
  sf_mex_destroy(&c1_rhs182);
  sf_mex_destroy(&c1_lhs182);
  sf_mex_destroy(&c1_rhs183);
  sf_mex_destroy(&c1_lhs183);
  sf_mex_destroy(&c1_rhs184);
  sf_mex_destroy(&c1_lhs184);
  sf_mex_destroy(&c1_rhs185);
  sf_mex_destroy(&c1_lhs185);
  sf_mex_destroy(&c1_rhs186);
  sf_mex_destroy(&c1_lhs186);
  sf_mex_destroy(&c1_rhs187);
  sf_mex_destroy(&c1_lhs187);
  sf_mex_destroy(&c1_rhs188);
  sf_mex_destroy(&c1_lhs188);
  sf_mex_destroy(&c1_rhs189);
  sf_mex_destroy(&c1_lhs189);
  sf_mex_destroy(&c1_rhs190);
  sf_mex_destroy(&c1_lhs190);
  sf_mex_destroy(&c1_rhs191);
  sf_mex_destroy(&c1_lhs191);
}

static void c1_d_info_helper(const mxArray **c1_info)
{
  const mxArray *c1_rhs192 = NULL;
  const mxArray *c1_lhs192 = NULL;
  const mxArray *c1_rhs193 = NULL;
  const mxArray *c1_lhs193 = NULL;
  const mxArray *c1_rhs194 = NULL;
  const mxArray *c1_lhs194 = NULL;
  const mxArray *c1_rhs195 = NULL;
  const mxArray *c1_lhs195 = NULL;
  const mxArray *c1_rhs196 = NULL;
  const mxArray *c1_lhs196 = NULL;
  const mxArray *c1_rhs197 = NULL;
  const mxArray *c1_lhs197 = NULL;
  const mxArray *c1_rhs198 = NULL;
  const mxArray *c1_lhs198 = NULL;
  const mxArray *c1_rhs199 = NULL;
  const mxArray *c1_lhs199 = NULL;
  const mxArray *c1_rhs200 = NULL;
  const mxArray *c1_lhs200 = NULL;
  const mxArray *c1_rhs201 = NULL;
  const mxArray *c1_lhs201 = NULL;
  const mxArray *c1_rhs202 = NULL;
  const mxArray *c1_lhs202 = NULL;
  const mxArray *c1_rhs203 = NULL;
  const mxArray *c1_lhs203 = NULL;
  const mxArray *c1_rhs204 = NULL;
  const mxArray *c1_lhs204 = NULL;
  const mxArray *c1_rhs205 = NULL;
  const mxArray *c1_lhs205 = NULL;
  const mxArray *c1_rhs206 = NULL;
  const mxArray *c1_lhs206 = NULL;
  const mxArray *c1_rhs207 = NULL;
  const mxArray *c1_lhs207 = NULL;
  const mxArray *c1_rhs208 = NULL;
  const mxArray *c1_lhs208 = NULL;
  const mxArray *c1_rhs209 = NULL;
  const mxArray *c1_lhs209 = NULL;
  const mxArray *c1_rhs210 = NULL;
  const mxArray *c1_lhs210 = NULL;
  const mxArray *c1_rhs211 = NULL;
  const mxArray *c1_lhs211 = NULL;
  const mxArray *c1_rhs212 = NULL;
  const mxArray *c1_lhs212 = NULL;
  const mxArray *c1_rhs213 = NULL;
  const mxArray *c1_lhs213 = NULL;
  const mxArray *c1_rhs214 = NULL;
  const mxArray *c1_lhs214 = NULL;
  const mxArray *c1_rhs215 = NULL;
  const mxArray *c1_lhs215 = NULL;
  const mxArray *c1_rhs216 = NULL;
  const mxArray *c1_lhs216 = NULL;
  const mxArray *c1_rhs217 = NULL;
  const mxArray *c1_lhs217 = NULL;
  const mxArray *c1_rhs218 = NULL;
  const mxArray *c1_lhs218 = NULL;
  const mxArray *c1_rhs219 = NULL;
  const mxArray *c1_lhs219 = NULL;
  const mxArray *c1_rhs220 = NULL;
  const mxArray *c1_lhs220 = NULL;
  const mxArray *c1_rhs221 = NULL;
  const mxArray *c1_lhs221 = NULL;
  const mxArray *c1_rhs222 = NULL;
  const mxArray *c1_lhs222 = NULL;
  const mxArray *c1_rhs223 = NULL;
  const mxArray *c1_lhs223 = NULL;
  const mxArray *c1_rhs224 = NULL;
  const mxArray *c1_lhs224 = NULL;
  const mxArray *c1_rhs225 = NULL;
  const mxArray *c1_lhs225 = NULL;
  const mxArray *c1_rhs226 = NULL;
  const mxArray *c1_lhs226 = NULL;
  const mxArray *c1_rhs227 = NULL;
  const mxArray *c1_lhs227 = NULL;
  const mxArray *c1_rhs228 = NULL;
  const mxArray *c1_lhs228 = NULL;
  const mxArray *c1_rhs229 = NULL;
  const mxArray *c1_lhs229 = NULL;
  const mxArray *c1_rhs230 = NULL;
  const mxArray *c1_lhs230 = NULL;
  const mxArray *c1_rhs231 = NULL;
  const mxArray *c1_lhs231 = NULL;
  const mxArray *c1_rhs232 = NULL;
  const mxArray *c1_lhs232 = NULL;
  const mxArray *c1_rhs233 = NULL;
  const mxArray *c1_lhs233 = NULL;
  const mxArray *c1_rhs234 = NULL;
  const mxArray *c1_lhs234 = NULL;
  const mxArray *c1_rhs235 = NULL;
  const mxArray *c1_lhs235 = NULL;
  const mxArray *c1_rhs236 = NULL;
  const mxArray *c1_lhs236 = NULL;
  const mxArray *c1_rhs237 = NULL;
  const mxArray *c1_lhs237 = NULL;
  const mxArray *c1_rhs238 = NULL;
  const mxArray *c1_lhs238 = NULL;
  const mxArray *c1_rhs239 = NULL;
  const mxArray *c1_lhs239 = NULL;
  const mxArray *c1_rhs240 = NULL;
  const mxArray *c1_lhs240 = NULL;
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/xcorr.m!crosscorr"), "context",
                  "context", 192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("min"), "name", "name", 192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/min.m"), "resolved",
                  "resolved", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273318U), "fileTimeLo",
                  "fileTimeLo", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 192);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 192);
  sf_mex_assign(&c1_rhs192, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs192, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs192), "rhs", "rhs",
                  192);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs192), "lhs", "lhs",
                  192);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/xcorr.m!crosscorr"), "context",
                  "context", 193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_conjtimes"), "name",
                  "name", 193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_conjtimes.m"), "resolved",
                  "resolved", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836696U), "fileTimeLo",
                  "fileTimeLo", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 193);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 193);
  sf_mex_assign(&c1_rhs193, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs193, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs193), "rhs", "rhs",
                  193);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs193), "lhs", "lhs",
                  193);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/signal/eml/xcorr.m!local_xcorr"), "context",
                  "context", 194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1366180242U), "fileTimeLo",
                  "fileTimeLo", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 194);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 194);
  sf_mex_assign(&c1_rhs194, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs194, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs194), "rhs", "rhs",
                  194);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs194), "lhs", "lhs",
                  194);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon"),
                  "context", "context", 195);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isfinite"), "name", "name",
                  195);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 195);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "resolved",
                  "resolved", 195);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728256U), "fileTimeLo",
                  "fileTimeLo", 195);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 195);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 195);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 195);
  sf_mex_assign(&c1_rhs195, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs195, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs195), "rhs", "rhs",
                  195);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs195), "lhs", "lhs",
                  195);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon"),
                  "context", "context", 196);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 196);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 196);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 196);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 196);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 196);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 196);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 196);
  sf_mex_assign(&c1_rhs196, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs196, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs196), "rhs", "rhs",
                  196);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs196), "lhs", "lhs",
                  196);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!maxabs"), "context",
                  "context", 197);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 197);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 197);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 197);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 197);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 197);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 197);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 197);
  sf_mex_assign(&c1_rhs197, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs197, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs197), "rhs", "rhs",
                  197);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs197), "lhs", "lhs",
                  197);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!is_flint_colon"),
                  "context", "context", 198);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eps"), "name", "name", 198);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 198);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "resolved",
                  "resolved", 198);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 198);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 198);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 198);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 198);
  sf_mex_assign(&c1_rhs198, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs198, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs198), "rhs", "rhs",
                  198);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs198), "lhs", "lhs",
                  198);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 199);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_mantissa_nbits"), "name",
                  "name", 199);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 199);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m"),
                  "resolved", "resolved", 199);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307669242U), "fileTimeLo",
                  "fileTimeLo", 199);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 199);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 199);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 199);
  sf_mex_assign(&c1_rhs199, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs199, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs199), "rhs", "rhs",
                  199);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs199), "lhs", "lhs",
                  199);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_mantissa_nbits.m"),
                  "context", "context", 200);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 200);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 200);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 200);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 200);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 200);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 200);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 200);
  sf_mex_assign(&c1_rhs200, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs200, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs200), "rhs", "rhs",
                  200);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs200), "lhs", "lhs",
                  200);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 201);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_realmin"), "name", "name",
                  201);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 201);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "resolved",
                  "resolved", 201);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307669244U), "fileTimeLo",
                  "fileTimeLo", 201);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 201);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 201);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 201);
  sf_mex_assign(&c1_rhs201, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs201, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs201), "rhs", "rhs",
                  201);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs201), "lhs", "lhs",
                  201);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin.m"), "context",
                  "context", 202);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 202);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 202);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 202);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 202);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 202);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 202);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 202);
  sf_mex_assign(&c1_rhs202, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs202, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs202), "rhs", "rhs",
                  202);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs202), "lhs", "lhs",
                  202);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 203);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_realmin_denormal"), "name",
                  "name", 203);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 203);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m"),
                  "resolved", "resolved", 203);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742398U), "fileTimeLo",
                  "fileTimeLo", 203);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 203);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 203);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 203);
  sf_mex_assign(&c1_rhs203, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs203, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs203), "rhs", "rhs",
                  203);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs203), "lhs", "lhs",
                  203);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_realmin_denormal.m"),
                  "context", "context", 204);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_float_model"), "name",
                  "name", 204);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 204);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_float_model.m"),
                  "resolved", "resolved", 204);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1326742396U), "fileTimeLo",
                  "fileTimeLo", 204);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 204);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 204);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 204);
  sf_mex_assign(&c1_rhs204, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs204, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs204), "rhs", "rhs",
                  204);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs204), "lhs", "lhs",
                  204);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 205);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("abs"), "name", "name", 205);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 205);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/abs.m"), "resolved",
                  "resolved", 205);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728252U), "fileTimeLo",
                  "fileTimeLo", 205);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 205);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 205);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 205);
  sf_mex_assign(&c1_rhs205, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs205, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs205), "rhs", "rhs",
                  205);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs205), "lhs", "lhs",
                  205);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/eps.m"), "context",
                  "context", 206);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isfinite"), "name", "name",
                  206);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 206);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isfinite.m"), "resolved",
                  "resolved", 206);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728256U), "fileTimeLo",
                  "fileTimeLo", 206);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 206);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 206);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 206);
  sf_mex_assign(&c1_rhs206, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs206, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs206), "rhs", "rhs",
                  206);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs206), "lhs", "lhs",
                  206);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!checkrange"),
                  "context", "context", 207);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("realmax"), "name", "name", 207);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 207);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "resolved",
                  "resolved", 207);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307669242U), "fileTimeLo",
                  "fileTimeLo", 207);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 207);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 207);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 207);
  sf_mex_assign(&c1_rhs207, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs207, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs207), "rhs", "rhs",
                  207);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs207), "lhs", "lhs",
                  207);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon"),
                  "context", "context", 208);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  208);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 208);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 208);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 208);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 208);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 208);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 208);
  sf_mex_assign(&c1_rhs208, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs208, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs208), "rhs", "rhs",
                  208);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs208), "lhs", "lhs",
                  208);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon"),
                  "context", "context", 209);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 209);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 209);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 209);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 209);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 209);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 209);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 209);
  sf_mex_assign(&c1_rhs209, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs209, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs209), "rhs", "rhs",
                  209);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs209), "lhs", "lhs",
                  209);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon"),
                  "context", "context", 210);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 210);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 210);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 210);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 210);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 210);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 210);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 210);
  sf_mex_assign(&c1_rhs210, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs210, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs210), "rhs", "rhs",
                  210);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs210), "lhs", "lhs",
                  210);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m!eml_flint_colon"),
                  "context", "context", 211);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("intmax"), "name", "name", 211);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 211);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/intmax.m"), "resolved",
                  "resolved", 211);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1362276282U), "fileTimeLo",
                  "fileTimeLo", 211);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 211);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 211);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 211);
  sf_mex_assign(&c1_rhs211, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs211, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs211), "rhs", "rhs",
                  211);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs211), "lhs", "lhs",
                  211);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 212);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 212);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 212);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 212);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303164206U), "fileTimeLo",
                  "fileTimeLo", 212);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 212);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 212);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 212);
  sf_mex_assign(&c1_rhs212, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs212, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs212), "rhs", "rhs",
                  212);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs212), "lhs", "lhs",
                  212);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 213);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("fft_abs"), "name", "name", 213);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 213);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/fft_abs.m"),
                  "resolved", "resolved", 213);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1414363750U), "fileTimeLo",
                  "fileTimeLo", 213);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 213);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 213);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 213);
  sf_mex_assign(&c1_rhs213, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs213, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs213), "rhs", "rhs",
                  213);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs213), "lhs", "lhs",
                  213);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 214);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("max"), "name", "name", 214);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 214);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/datafun/max.m"), "resolved",
                  "resolved", 214);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1311273316U), "fileTimeLo",
                  "fileTimeLo", 214);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 214);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 214);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 214);
  sf_mex_assign(&c1_rhs214, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs214, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs214), "rhs", "rhs",
                  214);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs214), "lhs", "lhs",
                  214);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum"),
                  "context", "context", 215);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_const_nonsingleton_dim"),
                  "name", "name", 215);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 215);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_const_nonsingleton_dim.m"),
                  "resolved", "resolved", 215);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836696U), "fileTimeLo",
                  "fileTimeLo", 215);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 215);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 215);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 215);
  sf_mex_assign(&c1_rhs215, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs215, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs215), "rhs", "rhs",
                  215);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs215), "lhs", "lhs",
                  215);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum"),
                  "context", "context", 216);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_eg"), "name",
                  "name", 216);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 216);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m"), "resolved",
                  "resolved", 216);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836796U), "fileTimeLo",
                  "fileTimeLo", 216);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 216);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 216);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 216);
  sf_mex_assign(&c1_rhs216, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs216, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs216), "rhs", "rhs",
                  216);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs216), "lhs", "lhs",
                  216);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum"),
                  "context", "context", 217);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 217);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 217);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 217);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 217);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 217);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 217);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 217);
  sf_mex_assign(&c1_rhs217, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs217, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs217), "rhs", "rhs",
                  217);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs217), "lhs", "lhs",
                  217);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 218);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_class"), "name",
                  "name", 218);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 218);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m"),
                  "resolved", "resolved", 218);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1323184978U), "fileTimeLo",
                  "fileTimeLo", 218);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 218);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 218);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 218);
  sf_mex_assign(&c1_rhs218, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs218, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs218), "rhs", "rhs",
                  218);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs218), "lhs", "lhs",
                  218);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 219);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("isnan"), "name", "name", 219);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 219);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/isnan.m"), "resolved",
                  "resolved", 219);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728258U), "fileTimeLo",
                  "fileTimeLo", 219);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 219);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 219);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 219);
  sf_mex_assign(&c1_rhs219, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs219, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs219), "rhs", "rhs",
                  219);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs219), "lhs", "lhs",
                  219);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 220);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_index_plus"), "name",
                  "name", 220);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("coder.internal.indexInt"),
                  "dominantType", "dominantType", 220);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m"),
                  "resolved", "resolved", 220);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836778U), "fileTimeLo",
                  "fileTimeLo", 220);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 220);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 220);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 220);
  sf_mex_assign(&c1_rhs220, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs220, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs220), "rhs", "rhs",
                  220);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs220), "lhs", "lhs",
                  220);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 221);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "eml_int_forloop_overflow_check"), "name", "name", 221);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(""), "dominantType",
                  "dominantType", 221);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"),
                  "resolved", "resolved", 221);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1346528340U), "fileTimeLo",
                  "fileTimeLo", 221);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 221);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 221);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 221);
  sf_mex_assign(&c1_rhs221, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs221, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs221), "rhs", "rhs",
                  221);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs221), "lhs", "lhs",
                  221);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_min_or_max.m!eml_extremum_sub"),
                  "context", "context", 222);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_relop"), "name", "name",
                  222);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("function_handle"),
                  "dominantType", "dominantType", 222);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_relop.m"), "resolved",
                  "resolved", 222);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1342469182U), "fileTimeLo",
                  "fileTimeLo", 222);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 222);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 222);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 222);
  sf_mex_assign(&c1_rhs222, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs222, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs222), "rhs", "rhs",
                  222);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs222), "lhs", "lhs",
                  222);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 223);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  223);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 223);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 223);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 223);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 223);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 223);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 223);
  sf_mex_assign(&c1_rhs223, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs223, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs223), "rhs", "rhs",
                  223);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs223), "lhs", "lhs",
                  223);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 224);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("floor"), "name", "name", 224);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 224);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/floor.m"), "resolved",
                  "resolved", 224);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 224);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 224);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 224);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 224);
  sf_mex_assign(&c1_rhs224, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs224, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs224), "rhs", "rhs",
                  224);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs224), "lhs", "lhs",
                  224);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 225);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("max_relativos"), "name",
                  "name", 225);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 225);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/max_relativos.m"),
                  "resolved", "resolved", 225);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1433592086U), "fileTimeLo",
                  "fileTimeLo", 225);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 225);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 225);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 225);
  sf_mex_assign(&c1_rhs225, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs225, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs225), "rhs", "rhs",
                  225);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs225), "lhs", "lhs",
                  225);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/funciones auxiliares/max_relativos.m"),
                  "context", "context", 226);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("length"), "name", "name", 226);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 226);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/length.m"), "resolved",
                  "resolved", 226);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1303164206U), "fileTimeLo",
                  "fileTimeLo", 226);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 226);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 226);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 226);
  sf_mex_assign(&c1_rhs226, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs226, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs226), "rhs", "rhs",
                  226);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs226), "lhs", "lhs",
                  226);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 227);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 227);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 227);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 227);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 227);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 227);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 227);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 227);
  sf_mex_assign(&c1_rhs227, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs227, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs227), "rhs", "rhs",
                  227);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs227), "lhs", "lhs",
                  227);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/FindPitch_simulink.m"),
                  "context", "context", 228);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("deteccion"), "name", "name",
                  228);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 228);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "resolved", "resolved", 228);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1433593360U), "fileTimeLo",
                  "fileTimeLo", 228);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 228);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 228);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 228);
  sf_mex_assign(&c1_rhs228, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs228, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs228), "rhs", "rhs",
                  228);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs228), "lhs", "lhs",
                  228);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "context", "context", 229);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("colon"), "name", "name", 229);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 229);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/colon.m"), "resolved",
                  "resolved", 229);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1366180242U), "fileTimeLo",
                  "fileTimeLo", 229);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 229);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 229);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 229);
  sf_mex_assign(&c1_rhs229, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs229, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs229), "rhs", "rhs",
                  229);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs229), "lhs", "lhs",
                  229);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "context", "context", 230);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  230);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 230);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 230);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 230);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 230);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 230);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 230);
  sf_mex_assign(&c1_rhs230, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs230, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs230), "rhs", "rhs",
                  230);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs230), "lhs", "lhs",
                  230);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "context", "context", 231);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mpower"), "name", "name", 231);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 231);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mpower.m"), "resolved",
                  "resolved", 231);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 231);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 231);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 231);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 231);
  sf_mex_assign(&c1_rhs231, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs231, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs231), "rhs", "rhs",
                  231);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs231), "lhs", "lhs",
                  231);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "context", "context", 232);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("log10"), "name", "name", 232);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 232);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log10.m"), "resolved",
                  "resolved", 232);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343848382U), "fileTimeLo",
                  "fileTimeLo", 232);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 232);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 232);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 232);
  sf_mex_assign(&c1_rhs232, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs232, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs232), "rhs", "rhs",
                  232);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs232), "lhs", "lhs",
                  232);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log10.m"), "context",
                  "context", 233);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_error"), "name", "name",
                  233);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 233);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_error.m"), "resolved",
                  "resolved", 233);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1343848358U), "fileTimeLo",
                  "fileTimeLo", 233);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 233);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 233);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 233);
  sf_mex_assign(&c1_rhs233, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs233, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs233), "rhs", "rhs",
                  233);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs233), "lhs", "lhs",
                  233);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/log10.m"), "context",
                  "context", 234);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_log10"), "name",
                  "name", 234);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 234);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log10.m"),
                  "resolved", "resolved", 234);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1286836728U), "fileTimeLo",
                  "fileTimeLo", 234);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 234);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 234);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 234);
  sf_mex_assign(&c1_rhs234, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs234, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs234), "rhs", "rhs",
                  234);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs234), "lhs", "lhs",
                  234);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log10.m"),
                  "context", "context", 235);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("realmax"), "name", "name", 235);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("char"), "dominantType",
                  "dominantType", 235);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elmat/realmax.m"), "resolved",
                  "resolved", 235);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307669242U), "fileTimeLo",
                  "fileTimeLo", 235);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 235);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 235);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 235);
  sf_mex_assign(&c1_rhs235, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs235, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs235), "rhs", "rhs",
                  235);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs235), "lhs", "lhs",
                  235);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_log10.m"),
                  "context", "context", 236);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mrdivide"), "name", "name",
                  236);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 236);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mrdivide.p"), "resolved",
                  "resolved", 236);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1373324508U), "fileTimeLo",
                  "fileTimeLo", 236);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 236);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1319747966U), "mFileTimeLo",
                  "mFileTimeLo", 236);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 236);
  sf_mex_assign(&c1_rhs236, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs236, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs236), "rhs", "rhs",
                  236);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs236), "lhs", "lhs",
                  236);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "context", "context", 237);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("round"), "name", "name", 237);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 237);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m"), "resolved",
                  "resolved", 237);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728254U), "fileTimeLo",
                  "fileTimeLo", 237);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 237);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 237);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 237);
  sf_mex_assign(&c1_rhs237, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs237, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs237), "rhs", "rhs",
                  237);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs237), "lhs", "lhs",
                  237);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m"), "context",
                  "context", 238);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "coder.internal.isBuiltInNumeric"), "name", "name", 238);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 238);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[IXE]$matlabroot$/toolbox/shared/coder/coder/+coder/+internal/isBuiltInNumeric.m"),
                  "resolved", "resolved", 238);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728956U), "fileTimeLo",
                  "fileTimeLo", 238);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 238);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 238);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 238);
  sf_mex_assign(&c1_rhs238, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs238, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs238), "rhs", "rhs",
                  238);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs238), "lhs", "lhs",
                  238);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/round.m"), "context",
                  "context", 239);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("eml_scalar_round"), "name",
                  "name", 239);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 239);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_round.m"),
                  "resolved", "resolved", 239);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1307669238U), "fileTimeLo",
                  "fileTimeLo", 239);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 239);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 239);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 239);
  sf_mex_assign(&c1_rhs239, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs239, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs239), "rhs", "rhs",
                  239);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs239), "lhs", "lhs",
                  239);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[E]C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/Pitch Detection/deteccion.m"),
                  "context", "context", 240);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("mtimes"), "name", "name", 240);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut("double"), "dominantType",
                  "dominantType", 240);
  sf_mex_addfield(*c1_info, c1_emlrt_marshallOut(
    "[ILXE]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m"), "resolved",
                  "resolved", 240);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(1363728278U), "fileTimeLo",
                  "fileTimeLo", 240);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "fileTimeHi",
                  "fileTimeHi", 240);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeLo",
                  "mFileTimeLo", 240);
  sf_mex_addfield(*c1_info, c1_b_emlrt_marshallOut(0U), "mFileTimeHi",
                  "mFileTimeHi", 240);
  sf_mex_assign(&c1_rhs240, sf_mex_createcellarray(0), FALSE);
  sf_mex_assign(&c1_lhs240, sf_mex_createcellarray(0), FALSE);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_rhs240), "rhs", "rhs",
                  240);
  sf_mex_addfield(*c1_info, sf_mex_duplicatearraysafe(&c1_lhs240), "lhs", "lhs",
                  240);
  sf_mex_destroy(&c1_rhs192);
  sf_mex_destroy(&c1_lhs192);
  sf_mex_destroy(&c1_rhs193);
  sf_mex_destroy(&c1_lhs193);
  sf_mex_destroy(&c1_rhs194);
  sf_mex_destroy(&c1_lhs194);
  sf_mex_destroy(&c1_rhs195);
  sf_mex_destroy(&c1_lhs195);
  sf_mex_destroy(&c1_rhs196);
  sf_mex_destroy(&c1_lhs196);
  sf_mex_destroy(&c1_rhs197);
  sf_mex_destroy(&c1_lhs197);
  sf_mex_destroy(&c1_rhs198);
  sf_mex_destroy(&c1_lhs198);
  sf_mex_destroy(&c1_rhs199);
  sf_mex_destroy(&c1_lhs199);
  sf_mex_destroy(&c1_rhs200);
  sf_mex_destroy(&c1_lhs200);
  sf_mex_destroy(&c1_rhs201);
  sf_mex_destroy(&c1_lhs201);
  sf_mex_destroy(&c1_rhs202);
  sf_mex_destroy(&c1_lhs202);
  sf_mex_destroy(&c1_rhs203);
  sf_mex_destroy(&c1_lhs203);
  sf_mex_destroy(&c1_rhs204);
  sf_mex_destroy(&c1_lhs204);
  sf_mex_destroy(&c1_rhs205);
  sf_mex_destroy(&c1_lhs205);
  sf_mex_destroy(&c1_rhs206);
  sf_mex_destroy(&c1_lhs206);
  sf_mex_destroy(&c1_rhs207);
  sf_mex_destroy(&c1_lhs207);
  sf_mex_destroy(&c1_rhs208);
  sf_mex_destroy(&c1_lhs208);
  sf_mex_destroy(&c1_rhs209);
  sf_mex_destroy(&c1_lhs209);
  sf_mex_destroy(&c1_rhs210);
  sf_mex_destroy(&c1_lhs210);
  sf_mex_destroy(&c1_rhs211);
  sf_mex_destroy(&c1_lhs211);
  sf_mex_destroy(&c1_rhs212);
  sf_mex_destroy(&c1_lhs212);
  sf_mex_destroy(&c1_rhs213);
  sf_mex_destroy(&c1_lhs213);
  sf_mex_destroy(&c1_rhs214);
  sf_mex_destroy(&c1_lhs214);
  sf_mex_destroy(&c1_rhs215);
  sf_mex_destroy(&c1_lhs215);
  sf_mex_destroy(&c1_rhs216);
  sf_mex_destroy(&c1_lhs216);
  sf_mex_destroy(&c1_rhs217);
  sf_mex_destroy(&c1_lhs217);
  sf_mex_destroy(&c1_rhs218);
  sf_mex_destroy(&c1_lhs218);
  sf_mex_destroy(&c1_rhs219);
  sf_mex_destroy(&c1_lhs219);
  sf_mex_destroy(&c1_rhs220);
  sf_mex_destroy(&c1_lhs220);
  sf_mex_destroy(&c1_rhs221);
  sf_mex_destroy(&c1_lhs221);
  sf_mex_destroy(&c1_rhs222);
  sf_mex_destroy(&c1_lhs222);
  sf_mex_destroy(&c1_rhs223);
  sf_mex_destroy(&c1_lhs223);
  sf_mex_destroy(&c1_rhs224);
  sf_mex_destroy(&c1_lhs224);
  sf_mex_destroy(&c1_rhs225);
  sf_mex_destroy(&c1_lhs225);
  sf_mex_destroy(&c1_rhs226);
  sf_mex_destroy(&c1_lhs226);
  sf_mex_destroy(&c1_rhs227);
  sf_mex_destroy(&c1_lhs227);
  sf_mex_destroy(&c1_rhs228);
  sf_mex_destroy(&c1_lhs228);
  sf_mex_destroy(&c1_rhs229);
  sf_mex_destroy(&c1_lhs229);
  sf_mex_destroy(&c1_rhs230);
  sf_mex_destroy(&c1_lhs230);
  sf_mex_destroy(&c1_rhs231);
  sf_mex_destroy(&c1_lhs231);
  sf_mex_destroy(&c1_rhs232);
  sf_mex_destroy(&c1_lhs232);
  sf_mex_destroy(&c1_rhs233);
  sf_mex_destroy(&c1_lhs233);
  sf_mex_destroy(&c1_rhs234);
  sf_mex_destroy(&c1_lhs234);
  sf_mex_destroy(&c1_rhs235);
  sf_mex_destroy(&c1_lhs235);
  sf_mex_destroy(&c1_rhs236);
  sf_mex_destroy(&c1_lhs236);
  sf_mex_destroy(&c1_rhs237);
  sf_mex_destroy(&c1_lhs237);
  sf_mex_destroy(&c1_rhs238);
  sf_mex_destroy(&c1_lhs238);
  sf_mex_destroy(&c1_rhs239);
  sf_mex_destroy(&c1_lhs239);
  sf_mex_destroy(&c1_rhs240);
  sf_mex_destroy(&c1_lhs240);
}

static void c1_hanning(SFc1_LedaInstanceStruct *chartInstance)
{
  const mxArray *c1_errid = NULL;
  const mxArray *c1_errmsg = NULL;
  const mxArray *c1_w = NULL;
  sf_mex_destroy(&c1_errid);
  sf_mex_destroy(&c1_errmsg);
  sf_mex_destroy(&c1_w);
}

static void c1_b_hanning(SFc1_LedaInstanceStruct *chartInstance)
{
  const mxArray *c1_errid = NULL;
  const mxArray *c1_errmsg = NULL;
  const mxArray *c1_w = NULL;
  sf_mex_destroy(&c1_errid);
  sf_mex_destroy(&c1_errmsg);
  sf_mex_destroy(&c1_w);
}

static void c1_eml_scalar_eg(SFc1_LedaInstanceStruct *chartInstance)
{
}

static void c1_fft(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[256],
                   creal_T c1_y[1024])
{
  int32_T c1_i155;
  static creal_T c1_dc2 = { 0.0, 0.0 };

  int32_T c1_ix;
  int32_T c1_ju;
  int32_T c1_iy;
  int32_T c1_i;
  int32_T c1_a;
  int32_T c1_c;
  int32_T c1_b_a;
  int32_T c1_b_c;
  int32_T c1_n;
  boolean_T c1_tst;
  int32_T c1_b;
  int32_T c1_c_a;
  int32_T c1_d_a;
  int32_T c1_c_c;
  int32_T c1_e_a;
  int32_T c1_d_c;
  int32_T c1_b_i;
  int32_T c1_c_i;
  int32_T c1_f_a;
  int32_T c1_e_c;
  creal_T c1_temp;
  int32_T c1_g_a;
  int32_T c1_f_c;
  int32_T c1_h_a;
  int32_T c1_g_c;
  int32_T c1_i_a;
  int32_T c1_h_c;
  int32_T c1_j_a;
  int32_T c1_i_c;
  int32_T c1_iDelta;
  int32_T c1_iDelta2;
  int32_T c1_k;
  int32_T c1_iheight;
  int32_T c1_b_b;
  int32_T c1_ihi;
  int32_T c1_k_a;
  int32_T c1_c_b;
  int32_T c1_j_c;
  int32_T c1_l_a;
  int32_T c1_k_c;
  int32_T c1_m_a;
  int32_T c1_d_b;
  int32_T c1_l_c;
  int32_T c1_n_a;
  int32_T c1_m_c;
  int32_T c1_o_a;
  int32_T c1_n_c;
  int32_T c1_p_a;
  int32_T c1_o_c;
  int32_T c1_q_a;
  int32_T c1_p_c;
  int32_T c1_r_a;
  int32_T c1_e_b;
  int32_T c1_istart;
  int32_T c1_f_b;
  int32_T c1_j;
  int32_T c1_s_a;
  int32_T c1_q_c;
  int32_T c1_t_a;
  int32_T c1_r_c;
  static real_T c1_dv29[513] = { 1.0, 0.99998117528260111, 0.9999247018391445,
    0.9998305817958234, 0.99969881869620425, 0.99952941750109314,
    0.99932238458834954, 0.99907772775264536, 0.99879545620517241,
    0.99847558057329477, 0.99811811290014918, 0.99772306664419164,
    0.99729045667869021, 0.99682029929116567, 0.996312612182778,
    0.99576741446765982, 0.99518472667219693, 0.99456457073425542,
    0.99390697000235606, 0.9932119492347945, 0.99247953459871,
    0.99170975366909953, 0.99090263542778, 0.99005821026229712,
    0.989176509964781, 0.98825756773074946, 0.98730141815785843,
    0.98630809724459867, 0.98527764238894122, 0.984210092386929,
    0.98310548743121629, 0.98196386910955524, 0.98078528040323043,
    0.97956976568544052, 0.97831737071962765, 0.97702814265775439,
    0.97570213003852857, 0.97433938278557586, 0.97293995220556018,
    0.97150389098625178, 0.970031253194544, 0.96852209427441727,
    0.96697647104485207, 0.9653944416976894, 0.96377606579543984,
    0.96212140426904158, 0.96043051941556579, 0.9587034748958716,
    0.95694033573220882, 0.95514116830577078, 0.95330604035419386,
    0.95143502096900834, 0.94952818059303667, 0.94758559101774109,
    0.94560732538052128, 0.94359345816196039, 0.94154406518302081,
    0.93945922360218992, 0.937339011912575, 0.93518350993894761,
    0.932992798834739, 0.93076696107898371, 0.92850608047321559,
    0.92621024213831138, 0.92387953251128674, 0.9215140393420419,
    0.91911385169005777, 0.9166790599210427, 0.91420975570353069,
    0.91170603200542988, 0.90916798309052238, 0.90659570451491533,
    0.90398929312344334, 0.901348847046022, 0.89867446569395382,
    0.89596624975618522, 0.89322430119551532, 0.89044872324475788,
    0.88763962040285393, 0.88479709843093779, 0.881921264348355,
    0.87901222642863353, 0.8760700941954066, 0.87309497841829009,
    0.87008699110871146, 0.86704624551569265, 0.8639728561215867,
    0.86086693863776731, 0.85772861000027212, 0.85455798836540053,
    0.8513551931052652, 0.84812034480329723, 0.84485356524970712,
    0.84155497743689844, 0.83822470555483808, 0.83486287498638,
    0.83146961230254524, 0.8280450452577558, 0.82458930278502529,
    0.82110251499110465, 0.81758481315158371, 0.81403632970594841,
    0.81045719825259477, 0.80684755354379933, 0.80320753148064494,
    0.799537269107905, 0.79583690460888357, 0.79210657730021239,
    0.78834642762660634, 0.78455659715557524, 0.78073722857209449,
    0.77688846567323244, 0.773010453362737, 0.7691033376455797,
    0.765167265622459, 0.76120238548426178, 0.75720884650648457,
    0.75318679904361252, 0.74913639452345937, 0.745057785441466,
    0.74095112535495922, 0.73681656887736979, 0.73265427167241282,
    0.7284643904482252, 0.724247082951467, 0.72000250796138165,
    0.71573082528381859, 0.71143219574521643, 0.70710678118654757,
    0.7027547444572253, 0.69837624940897292, 0.69397146088965389,
    0.68954054473706683, 0.68508366777270036, 0.680600997795453,
    0.67609270357531592, 0.67155895484701833, 0.66699992230363747,
    0.66241577759017178, 0.65780669329707864, 0.65317284295377676,
    0.64851440102211244, 0.64383154288979139, 0.63912444486377573,
    0.63439328416364549, 0.629638238914927, 0.62485948814238634,
    0.6200572117632891, 0.61523159058062682, 0.61038280627630948,
    0.60551104140432555, 0.600616479383869, 0.59569930449243336,
    0.59075970185887416, 0.58579785745643886, 0.58081395809576453,
    0.57580819141784534, 0.57078074588696726, 0.56573181078361312,
    0.560661576197336, 0.55557023301960218, 0.55045797293660481,
    0.54532498842204646, 0.54017147272989285, 0.53499761988709715,
    0.52980362468629461, 0.524589682678469, 0.51935599016558964,
    0.51410274419322166, 0.508830142543107, 0.50353838372571758,
    0.49822766697278181, 0.49289819222978404, 0.487550160148436,
    0.48218377207912272, 0.47679923006332209, 0.47139673682599764,
    0.46597649576796618, 0.46053871095824, 0.45508358712634384,
    0.44961132965460654, 0.4441221445704292, 0.43861623853852766,
    0.43309381885315196, 0.42755509343028208, 0.42200027079979968,
    0.41642956009763715, 0.41084317105790391, 0.40524131400498986,
    0.39962419984564679, 0.3939920400610481, 0.38834504669882625,
    0.38268343236508978, 0.37700741021641826, 0.37131719395183749,
    0.36561299780477385, 0.35989503653498811, 0.35416352542049034,
    0.34841868024943456, 0.34266071731199438, 0.33688985339222005,
    0.33110630575987643, 0.32531029216226293, 0.31950203081601569,
    0.31368174039889152, 0.30784964004153487, 0.30200594931922808,
    0.29615088824362379, 0.29028467725446233, 0.28440753721127188,
    0.27851968938505306, 0.272621355449949, 0.26671275747489837,
    0.26079411791527551, 0.25486565960451457, 0.24892760574572015,
    0.24298017990326387, 0.2370236059943672, 0.23105810828067111,
    0.22508391135979283, 0.2191012401568698, 0.21311031991609136,
    0.20711137619221856, 0.2011046348420919, 0.19509032201612825,
    0.18906866414980619, 0.18303988795514095, 0.17700422041214875,
    0.17096188876030122, 0.16491312048996992, 0.15885814333386145,
    0.15279718525844344, 0.14673047445536175, 0.14065823933284921,
    0.13458070850712617, 0.12849811079379317, 0.1224106751992162,
    0.11631863091190475, 0.11022220729388306, 0.10412163387205459,
    0.0980171403295606, 0.091908956497132724, 0.0857973123444399,
    0.079682437971430126, 0.073564563599667426, 0.067443919563664051,
    0.061320736302208578, 0.055195244349689941, 0.049067674327418015,
    0.04293825693494082, 0.036807222941358832, 0.030674803176636626,
    0.024541228522912288, 0.01840672990580482, 0.012271538285719925,
    0.0061358846491544753, 0.0, -0.0061358846491544753, -0.012271538285719925,
    -0.01840672990580482, -0.024541228522912288, -0.030674803176636626,
    -0.036807222941358832, -0.04293825693494082, -0.049067674327418015,
    -0.055195244349689941, -0.061320736302208578, -0.067443919563664051,
    -0.073564563599667426, -0.079682437971430126, -0.0857973123444399,
    -0.091908956497132724, -0.0980171403295606, -0.10412163387205459,
    -0.11022220729388306, -0.11631863091190475, -0.1224106751992162,
    -0.12849811079379317, -0.13458070850712617, -0.14065823933284921,
    -0.14673047445536175, -0.15279718525844344, -0.15885814333386145,
    -0.16491312048996992, -0.17096188876030122, -0.17700422041214875,
    -0.18303988795514095, -0.18906866414980619, -0.19509032201612825,
    -0.2011046348420919, -0.20711137619221856, -0.21311031991609136,
    -0.2191012401568698, -0.22508391135979283, -0.23105810828067111,
    -0.2370236059943672, -0.24298017990326387, -0.24892760574572015,
    -0.25486565960451457, -0.26079411791527551, -0.26671275747489837,
    -0.272621355449949, -0.27851968938505306, -0.28440753721127188,
    -0.29028467725446233, -0.29615088824362379, -0.30200594931922808,
    -0.30784964004153487, -0.31368174039889152, -0.31950203081601569,
    -0.32531029216226293, -0.33110630575987643, -0.33688985339222005,
    -0.34266071731199438, -0.34841868024943456, -0.35416352542049034,
    -0.35989503653498811, -0.36561299780477385, -0.37131719395183749,
    -0.37700741021641826, -0.38268343236508978, -0.38834504669882625,
    -0.3939920400610481, -0.39962419984564679, -0.40524131400498986,
    -0.41084317105790391, -0.41642956009763715, -0.42200027079979968,
    -0.42755509343028208, -0.43309381885315196, -0.43861623853852766,
    -0.4441221445704292, -0.44961132965460654, -0.45508358712634384,
    -0.46053871095824, -0.46597649576796618, -0.47139673682599764,
    -0.47679923006332209, -0.48218377207912272, -0.487550160148436,
    -0.49289819222978404, -0.49822766697278181, -0.50353838372571758,
    -0.508830142543107, -0.51410274419322166, -0.51935599016558964,
    -0.524589682678469, -0.52980362468629461, -0.53499761988709715,
    -0.54017147272989285, -0.54532498842204646, -0.55045797293660481,
    -0.55557023301960218, -0.560661576197336, -0.56573181078361312,
    -0.57078074588696726, -0.57580819141784534, -0.58081395809576453,
    -0.58579785745643886, -0.59075970185887416, -0.59569930449243336,
    -0.600616479383869, -0.60551104140432555, -0.61038280627630948,
    -0.61523159058062682, -0.6200572117632891, -0.62485948814238634,
    -0.629638238914927, -0.63439328416364549, -0.63912444486377573,
    -0.64383154288979139, -0.64851440102211244, -0.65317284295377676,
    -0.65780669329707864, -0.66241577759017178, -0.66699992230363747,
    -0.67155895484701833, -0.67609270357531592, -0.680600997795453,
    -0.68508366777270036, -0.68954054473706683, -0.69397146088965389,
    -0.69837624940897292, -0.7027547444572253, -0.70710678118654757,
    -0.71143219574521643, -0.71573082528381859, -0.72000250796138165,
    -0.724247082951467, -0.7284643904482252, -0.73265427167241282,
    -0.73681656887736979, -0.74095112535495922, -0.745057785441466,
    -0.74913639452345937, -0.75318679904361252, -0.75720884650648457,
    -0.76120238548426178, -0.765167265622459, -0.7691033376455797,
    -0.773010453362737, -0.77688846567323244, -0.78073722857209449,
    -0.78455659715557524, -0.78834642762660634, -0.79210657730021239,
    -0.79583690460888357, -0.799537269107905, -0.80320753148064494,
    -0.80684755354379933, -0.81045719825259477, -0.81403632970594841,
    -0.81758481315158371, -0.82110251499110465, -0.82458930278502529,
    -0.8280450452577558, -0.83146961230254524, -0.83486287498638,
    -0.83822470555483808, -0.84155497743689844, -0.84485356524970712,
    -0.84812034480329723, -0.8513551931052652, -0.85455798836540053,
    -0.85772861000027212, -0.86086693863776731, -0.8639728561215867,
    -0.86704624551569265, -0.87008699110871146, -0.87309497841829009,
    -0.8760700941954066, -0.87901222642863353, -0.881921264348355,
    -0.88479709843093779, -0.88763962040285393, -0.89044872324475788,
    -0.89322430119551532, -0.89596624975618522, -0.89867446569395382,
    -0.901348847046022, -0.90398929312344334, -0.90659570451491533,
    -0.90916798309052238, -0.91170603200542988, -0.91420975570353069,
    -0.9166790599210427, -0.91911385169005777, -0.9215140393420419,
    -0.92387953251128674, -0.92621024213831138, -0.92850608047321559,
    -0.93076696107898371, -0.932992798834739, -0.93518350993894761,
    -0.937339011912575, -0.93945922360218992, -0.94154406518302081,
    -0.94359345816196039, -0.94560732538052128, -0.94758559101774109,
    -0.94952818059303667, -0.95143502096900834, -0.95330604035419386,
    -0.95514116830577078, -0.95694033573220882, -0.9587034748958716,
    -0.96043051941556579, -0.96212140426904158, -0.96377606579543984,
    -0.9653944416976894, -0.96697647104485207, -0.96852209427441727,
    -0.970031253194544, -0.97150389098625178, -0.97293995220556018,
    -0.97433938278557586, -0.97570213003852857, -0.97702814265775439,
    -0.97831737071962765, -0.97956976568544052, -0.98078528040323043,
    -0.98196386910955524, -0.98310548743121629, -0.984210092386929,
    -0.98527764238894122, -0.98630809724459867, -0.98730141815785843,
    -0.98825756773074946, -0.989176509964781, -0.99005821026229712,
    -0.99090263542778, -0.99170975366909953, -0.99247953459871,
    -0.9932119492347945, -0.99390697000235606, -0.99456457073425542,
    -0.99518472667219693, -0.99576741446765982, -0.996312612182778,
    -0.99682029929116567, -0.99729045667869021, -0.99772306664419164,
    -0.99811811290014918, -0.99847558057329477, -0.99879545620517241,
    -0.99907772775264536, -0.99932238458834954, -0.99952941750109314,
    -0.99969881869620425, -0.9998305817958234, -0.9999247018391445,
    -0.99998117528260111, -1.0 };

  creal_T c1_twid;
  static real_T c1_dv30[513] = { 0.0, -0.0061358846491544753,
    -0.012271538285719925, -0.01840672990580482, -0.024541228522912288,
    -0.030674803176636626, -0.036807222941358832, -0.04293825693494082,
    -0.049067674327418015, -0.055195244349689941, -0.061320736302208578,
    -0.067443919563664051, -0.073564563599667426, -0.079682437971430126,
    -0.0857973123444399, -0.091908956497132724, -0.0980171403295606,
    -0.10412163387205459, -0.11022220729388306, -0.11631863091190475,
    -0.1224106751992162, -0.12849811079379317, -0.13458070850712617,
    -0.14065823933284921, -0.14673047445536175, -0.15279718525844344,
    -0.15885814333386145, -0.16491312048996992, -0.17096188876030122,
    -0.17700422041214875, -0.18303988795514095, -0.18906866414980619,
    -0.19509032201612825, -0.2011046348420919, -0.20711137619221856,
    -0.21311031991609136, -0.2191012401568698, -0.22508391135979283,
    -0.23105810828067111, -0.2370236059943672, -0.24298017990326387,
    -0.24892760574572015, -0.25486565960451457, -0.26079411791527551,
    -0.26671275747489837, -0.272621355449949, -0.27851968938505306,
    -0.28440753721127188, -0.29028467725446233, -0.29615088824362379,
    -0.30200594931922808, -0.30784964004153487, -0.31368174039889152,
    -0.31950203081601569, -0.32531029216226293, -0.33110630575987643,
    -0.33688985339222005, -0.34266071731199438, -0.34841868024943456,
    -0.35416352542049034, -0.35989503653498811, -0.36561299780477385,
    -0.37131719395183749, -0.37700741021641826, -0.38268343236508978,
    -0.38834504669882625, -0.3939920400610481, -0.39962419984564679,
    -0.40524131400498986, -0.41084317105790391, -0.41642956009763715,
    -0.42200027079979968, -0.42755509343028208, -0.43309381885315196,
    -0.43861623853852766, -0.4441221445704292, -0.44961132965460654,
    -0.45508358712634384, -0.46053871095824, -0.46597649576796618,
    -0.47139673682599764, -0.47679923006332209, -0.48218377207912272,
    -0.487550160148436, -0.49289819222978404, -0.49822766697278181,
    -0.50353838372571758, -0.508830142543107, -0.51410274419322166,
    -0.51935599016558964, -0.524589682678469, -0.52980362468629461,
    -0.53499761988709715, -0.54017147272989285, -0.54532498842204646,
    -0.55045797293660481, -0.55557023301960218, -0.560661576197336,
    -0.56573181078361312, -0.57078074588696726, -0.57580819141784534,
    -0.58081395809576453, -0.58579785745643886, -0.59075970185887416,
    -0.59569930449243336, -0.600616479383869, -0.60551104140432555,
    -0.61038280627630948, -0.61523159058062682, -0.6200572117632891,
    -0.62485948814238634, -0.629638238914927, -0.63439328416364549,
    -0.63912444486377573, -0.64383154288979139, -0.64851440102211244,
    -0.65317284295377676, -0.65780669329707864, -0.66241577759017178,
    -0.66699992230363747, -0.67155895484701833, -0.67609270357531592,
    -0.680600997795453, -0.68508366777270036, -0.68954054473706683,
    -0.69397146088965389, -0.69837624940897292, -0.7027547444572253,
    -0.70710678118654757, -0.71143219574521643, -0.71573082528381859,
    -0.72000250796138165, -0.724247082951467, -0.7284643904482252,
    -0.73265427167241282, -0.73681656887736979, -0.74095112535495922,
    -0.745057785441466, -0.74913639452345937, -0.75318679904361252,
    -0.75720884650648457, -0.76120238548426178, -0.765167265622459,
    -0.7691033376455797, -0.773010453362737, -0.77688846567323244,
    -0.78073722857209449, -0.78455659715557524, -0.78834642762660634,
    -0.79210657730021239, -0.79583690460888357, -0.799537269107905,
    -0.80320753148064494, -0.80684755354379933, -0.81045719825259477,
    -0.81403632970594841, -0.81758481315158371, -0.82110251499110465,
    -0.82458930278502529, -0.8280450452577558, -0.83146961230254524,
    -0.83486287498638, -0.83822470555483808, -0.84155497743689844,
    -0.84485356524970712, -0.84812034480329723, -0.8513551931052652,
    -0.85455798836540053, -0.85772861000027212, -0.86086693863776731,
    -0.8639728561215867, -0.86704624551569265, -0.87008699110871146,
    -0.87309497841829009, -0.8760700941954066, -0.87901222642863353,
    -0.881921264348355, -0.88479709843093779, -0.88763962040285393,
    -0.89044872324475788, -0.89322430119551532, -0.89596624975618522,
    -0.89867446569395382, -0.901348847046022, -0.90398929312344334,
    -0.90659570451491533, -0.90916798309052238, -0.91170603200542988,
    -0.91420975570353069, -0.9166790599210427, -0.91911385169005777,
    -0.9215140393420419, -0.92387953251128674, -0.92621024213831138,
    -0.92850608047321559, -0.93076696107898371, -0.932992798834739,
    -0.93518350993894761, -0.937339011912575, -0.93945922360218992,
    -0.94154406518302081, -0.94359345816196039, -0.94560732538052128,
    -0.94758559101774109, -0.94952818059303667, -0.95143502096900834,
    -0.95330604035419386, -0.95514116830577078, -0.95694033573220882,
    -0.9587034748958716, -0.96043051941556579, -0.96212140426904158,
    -0.96377606579543984, -0.9653944416976894, -0.96697647104485207,
    -0.96852209427441727, -0.970031253194544, -0.97150389098625178,
    -0.97293995220556018, -0.97433938278557586, -0.97570213003852857,
    -0.97702814265775439, -0.97831737071962765, -0.97956976568544052,
    -0.98078528040323043, -0.98196386910955524, -0.98310548743121629,
    -0.984210092386929, -0.98527764238894122, -0.98630809724459867,
    -0.98730141815785843, -0.98825756773074946, -0.989176509964781,
    -0.99005821026229712, -0.99090263542778, -0.99170975366909953,
    -0.99247953459871, -0.9932119492347945, -0.99390697000235606,
    -0.99456457073425542, -0.99518472667219693, -0.99576741446765982,
    -0.996312612182778, -0.99682029929116567, -0.99729045667869021,
    -0.99772306664419164, -0.99811811290014918, -0.99847558057329477,
    -0.99879545620517241, -0.99907772775264536, -0.99932238458834954,
    -0.99952941750109314, -0.99969881869620425, -0.9998305817958234,
    -0.9999247018391445, -0.99998117528260111, -1.0, -0.99998117528260111,
    -0.9999247018391445, -0.9998305817958234, -0.99969881869620425,
    -0.99952941750109314, -0.99932238458834954, -0.99907772775264536,
    -0.99879545620517241, -0.99847558057329477, -0.99811811290014918,
    -0.99772306664419164, -0.99729045667869021, -0.99682029929116567,
    -0.996312612182778, -0.99576741446765982, -0.99518472667219693,
    -0.99456457073425542, -0.99390697000235606, -0.9932119492347945,
    -0.99247953459871, -0.99170975366909953, -0.99090263542778,
    -0.99005821026229712, -0.989176509964781, -0.98825756773074946,
    -0.98730141815785843, -0.98630809724459867, -0.98527764238894122,
    -0.984210092386929, -0.98310548743121629, -0.98196386910955524,
    -0.98078528040323043, -0.97956976568544052, -0.97831737071962765,
    -0.97702814265775439, -0.97570213003852857, -0.97433938278557586,
    -0.97293995220556018, -0.97150389098625178, -0.970031253194544,
    -0.96852209427441727, -0.96697647104485207, -0.9653944416976894,
    -0.96377606579543984, -0.96212140426904158, -0.96043051941556579,
    -0.9587034748958716, -0.95694033573220882, -0.95514116830577078,
    -0.95330604035419386, -0.95143502096900834, -0.94952818059303667,
    -0.94758559101774109, -0.94560732538052128, -0.94359345816196039,
    -0.94154406518302081, -0.93945922360218992, -0.937339011912575,
    -0.93518350993894761, -0.932992798834739, -0.93076696107898371,
    -0.92850608047321559, -0.92621024213831138, -0.92387953251128674,
    -0.9215140393420419, -0.91911385169005777, -0.9166790599210427,
    -0.91420975570353069, -0.91170603200542988, -0.90916798309052238,
    -0.90659570451491533, -0.90398929312344334, -0.901348847046022,
    -0.89867446569395382, -0.89596624975618522, -0.89322430119551532,
    -0.89044872324475788, -0.88763962040285393, -0.88479709843093779,
    -0.881921264348355, -0.87901222642863353, -0.8760700941954066,
    -0.87309497841829009, -0.87008699110871146, -0.86704624551569265,
    -0.8639728561215867, -0.86086693863776731, -0.85772861000027212,
    -0.85455798836540053, -0.8513551931052652, -0.84812034480329723,
    -0.84485356524970712, -0.84155497743689844, -0.83822470555483808,
    -0.83486287498638, -0.83146961230254524, -0.8280450452577558,
    -0.82458930278502529, -0.82110251499110465, -0.81758481315158371,
    -0.81403632970594841, -0.81045719825259477, -0.80684755354379933,
    -0.80320753148064494, -0.799537269107905, -0.79583690460888357,
    -0.79210657730021239, -0.78834642762660634, -0.78455659715557524,
    -0.78073722857209449, -0.77688846567323244, -0.773010453362737,
    -0.7691033376455797, -0.765167265622459, -0.76120238548426178,
    -0.75720884650648457, -0.75318679904361252, -0.74913639452345937,
    -0.745057785441466, -0.74095112535495922, -0.73681656887736979,
    -0.73265427167241282, -0.7284643904482252, -0.724247082951467,
    -0.72000250796138165, -0.71573082528381859, -0.71143219574521643,
    -0.70710678118654757, -0.7027547444572253, -0.69837624940897292,
    -0.69397146088965389, -0.68954054473706683, -0.68508366777270036,
    -0.680600997795453, -0.67609270357531592, -0.67155895484701833,
    -0.66699992230363747, -0.66241577759017178, -0.65780669329707864,
    -0.65317284295377676, -0.64851440102211244, -0.64383154288979139,
    -0.63912444486377573, -0.63439328416364549, -0.629638238914927,
    -0.62485948814238634, -0.6200572117632891, -0.61523159058062682,
    -0.61038280627630948, -0.60551104140432555, -0.600616479383869,
    -0.59569930449243336, -0.59075970185887416, -0.58579785745643886,
    -0.58081395809576453, -0.57580819141784534, -0.57078074588696726,
    -0.56573181078361312, -0.560661576197336, -0.55557023301960218,
    -0.55045797293660481, -0.54532498842204646, -0.54017147272989285,
    -0.53499761988709715, -0.52980362468629461, -0.524589682678469,
    -0.51935599016558964, -0.51410274419322166, -0.508830142543107,
    -0.50353838372571758, -0.49822766697278181, -0.49289819222978404,
    -0.487550160148436, -0.48218377207912272, -0.47679923006332209,
    -0.47139673682599764, -0.46597649576796618, -0.46053871095824,
    -0.45508358712634384, -0.44961132965460654, -0.4441221445704292,
    -0.43861623853852766, -0.43309381885315196, -0.42755509343028208,
    -0.42200027079979968, -0.41642956009763715, -0.41084317105790391,
    -0.40524131400498986, -0.39962419984564679, -0.3939920400610481,
    -0.38834504669882625, -0.38268343236508978, -0.37700741021641826,
    -0.37131719395183749, -0.36561299780477385, -0.35989503653498811,
    -0.35416352542049034, -0.34841868024943456, -0.34266071731199438,
    -0.33688985339222005, -0.33110630575987643, -0.32531029216226293,
    -0.31950203081601569, -0.31368174039889152, -0.30784964004153487,
    -0.30200594931922808, -0.29615088824362379, -0.29028467725446233,
    -0.28440753721127188, -0.27851968938505306, -0.272621355449949,
    -0.26671275747489837, -0.26079411791527551, -0.25486565960451457,
    -0.24892760574572015, -0.24298017990326387, -0.2370236059943672,
    -0.23105810828067111, -0.22508391135979283, -0.2191012401568698,
    -0.21311031991609136, -0.20711137619221856, -0.2011046348420919,
    -0.19509032201612825, -0.18906866414980619, -0.18303988795514095,
    -0.17700422041214875, -0.17096188876030122, -0.16491312048996992,
    -0.15885814333386145, -0.15279718525844344, -0.14673047445536175,
    -0.14065823933284921, -0.13458070850712617, -0.12849811079379317,
    -0.1224106751992162, -0.11631863091190475, -0.11022220729388306,
    -0.10412163387205459, -0.0980171403295606, -0.091908956497132724,
    -0.0857973123444399, -0.079682437971430126, -0.073564563599667426,
    -0.067443919563664051, -0.061320736302208578, -0.055195244349689941,
    -0.049067674327418015, -0.04293825693494082, -0.036807222941358832,
    -0.030674803176636626, -0.024541228522912288, -0.01840672990580482,
    -0.012271538285719925, -0.0061358846491544753, -0.0 };

  int32_T c1_u_a;
  int32_T c1_g_b;
  int32_T c1_v_a;
  int32_T c1_h_b;
  int32_T c1_s_c;
  int32_T c1_w_a;
  int32_T c1_t_c;
  creal_T c1_b_temp;
  int32_T c1_x_a;
  int32_T c1_i_b;
  int32_T c1_u_c;
  int32_T c1_y_a;
  int32_T c1_v_c;
  int32_T c1_ab_a;
  int32_T c1_w_c;
  int32_T c1_bb_a;
  int32_T c1_x_c;
  int32_T c1_cb_a;
  int32_T c1_y_c;
  int32_T c1_db_a;
  int32_T c1_j_b;
  int32_T c1_eb_a;
  int32_T c1_fb_a;
  int32_T c1_k_b;
  int32_T c1_gb_a;
  int32_T c1_i156;
  int32_T c1_hb_a;
  int32_T c1_ib_a;
  int32_T c1_l_b;
  c1_eml_size_ispow2(chartInstance);
  c1_b_eml_scalar_eg(chartInstance);
  for (c1_i155 = 0; c1_i155 < 1024; c1_i155++) {
    c1_y[c1_i155] = c1_dc2;
  }

  c1_ix = 0;
  c1_ju = 0;
  c1_iy = 0;
  for (c1_i = 1; c1_i < 256; c1_i++) {
    c1_a = c1_iy;
    c1_c = c1_a;
    c1_b_a = c1_ix;
    c1_b_c = c1_b_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c + 1, 1, 1024, 1, 0) - 1].re =
      c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_b_c + 1, 1, 256, 1, 0) - 1];
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c + 1, 1, 1024, 1, 0) - 1].im = 0.0;
    c1_n = 1024;
    c1_tst = TRUE;
    while (c1_tst) {
      c1_n >>= 1;
      c1_ju ^= c1_n;
      c1_tst = ((c1_ju & c1_n) == 0);
    }

    c1_b = c1_ju;
    c1_iy = c1_b;
    c1_c_a = c1_ix + 1;
    c1_ix = c1_c_a;
  }

  c1_d_a = c1_iy;
  c1_c_c = c1_d_a;
  c1_e_a = c1_ix;
  c1_d_c = c1_e_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c_c + 1, 1, 1024, 1, 0) - 1].re =
    c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_d_c + 1, 1, 256, 1, 0) - 1];
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c_c + 1, 1, 1024, 1, 0) - 1].im = 0.0;
  for (c1_b_i = 0; c1_b_i < 1023; c1_b_i += 2) {
    c1_c_i = c1_b_i;
    c1_f_a = c1_c_i;
    c1_e_c = c1_f_a;
    c1_temp.re = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_e_c + 2, 1, 1024, 1, 0)
      - 1].re;
    c1_temp.im = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_e_c + 2, 1, 1024, 1, 0)
      - 1].im;
    c1_g_a = c1_c_i;
    c1_f_c = c1_g_a;
    c1_h_a = c1_c_i;
    c1_g_c = c1_h_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_f_c + 2, 1, 1024, 1, 0) - 1].re =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_g_c + 1, 1, 1024, 1, 0) - 1].re -
      c1_temp.re;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_f_c + 2, 1, 1024, 1, 0) - 1].im =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_g_c + 1, 1, 1024, 1, 0) - 1].im -
      c1_temp.im;
    c1_i_a = c1_c_i;
    c1_h_c = c1_i_a;
    c1_j_a = c1_c_i;
    c1_i_c = c1_j_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_h_c + 1, 1, 1024, 1, 0) - 1].re =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_i_c + 1, 1, 1024, 1, 0) - 1].re +
      c1_temp.re;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_h_c + 1, 1, 1024, 1, 0) - 1].im =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_i_c + 1, 1, 1024, 1, 0) - 1].im +
      c1_temp.im;
  }

  c1_iDelta = 2;
  c1_iDelta2 = 4;
  c1_k = 256;
  c1_iheight = 1021;
  while (c1_k > 0) {
    c1_c_i = 0;
    c1_b_b = c1_iheight;
    c1_ihi = c1_b_b;
    while (c1_c_i < c1_ihi) {
      c1_k_a = c1_c_i;
      c1_c_b = c1_iDelta;
      c1_j_c = c1_k_a + c1_c_b;
      c1_l_a = c1_j_c;
      c1_k_c = c1_l_a;
      c1_temp.re = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_k_c + 1, 1, 1024, 1,
        0) - 1].re;
      c1_temp.im = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_k_c + 1, 1, 1024, 1,
        0) - 1].im;
      c1_m_a = c1_c_i;
      c1_d_b = c1_iDelta;
      c1_l_c = c1_m_a + c1_d_b;
      c1_n_a = c1_l_c;
      c1_m_c = c1_n_a;
      c1_o_a = c1_c_i;
      c1_n_c = c1_o_a;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_m_c + 1, 1, 1024, 1, 0) - 1].re =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_n_c + 1, 1, 1024, 1, 0) - 1].re
        - c1_temp.re;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_m_c + 1, 1, 1024, 1, 0) - 1].im =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_n_c + 1, 1, 1024, 1, 0) - 1].im
        - c1_temp.im;
      c1_p_a = c1_c_i;
      c1_o_c = c1_p_a;
      c1_q_a = c1_c_i;
      c1_p_c = c1_q_a;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_o_c + 1, 1, 1024, 1, 0) - 1].re =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_p_c + 1, 1, 1024, 1, 0) - 1].re
        + c1_temp.re;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_o_c + 1, 1, 1024, 1, 0) - 1].im =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_p_c + 1, 1, 1024, 1, 0) - 1].im
        + c1_temp.im;
      c1_r_a = c1_c_i;
      c1_e_b = c1_iDelta2;
      c1_c_i = c1_r_a + c1_e_b;
    }

    c1_istart = 1;
    c1_f_b = c1_k;
    for (c1_j = c1_f_b; c1_j < 512; c1_j = c1_fb_a + c1_k_b) {
      c1_s_a = c1_j;
      c1_q_c = c1_s_a;
      c1_t_a = c1_j;
      c1_r_c = c1_t_a;
      c1_twid.re = c1_dv29[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_q_c + 1, 1, 513, 1,
        0) - 1];
      c1_twid.im = c1_dv30[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_r_c + 1, 1, 513, 1,
        0) - 1];
      c1_c_i = c1_istart;
      c1_u_a = c1_c_i;
      c1_g_b = c1_iheight;
      c1_ihi = c1_u_a + c1_g_b;
      while (c1_c_i < c1_ihi) {
        c1_v_a = c1_c_i;
        c1_h_b = c1_iDelta;
        c1_s_c = c1_v_a + c1_h_b;
        c1_w_a = c1_s_c;
        c1_t_c = c1_w_a;
        c1_temp.re = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_t_c + 1, 1, 1024, 1,
          0) - 1].re;
        c1_temp.im = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_t_c + 1, 1, 1024, 1,
          0) - 1].im;
        c1_b_temp = c1_temp;
        c1_temp.re = c1_twid.re * c1_b_temp.re - c1_twid.im * c1_b_temp.im;
        c1_temp.im = c1_twid.re * c1_b_temp.im + c1_twid.im * c1_b_temp.re;
        c1_x_a = c1_c_i;
        c1_i_b = c1_iDelta;
        c1_u_c = c1_x_a + c1_i_b;
        c1_y_a = c1_u_c;
        c1_v_c = c1_y_a;
        c1_ab_a = c1_c_i;
        c1_w_c = c1_ab_a;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_v_c + 1, 1, 1024, 1, 0) - 1].re =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_w_c + 1, 1, 1024, 1, 0) - 1].
          re - c1_temp.re;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_v_c + 1, 1, 1024, 1, 0) - 1].im =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_w_c + 1, 1, 1024, 1, 0) - 1].
          im - c1_temp.im;
        c1_bb_a = c1_c_i;
        c1_x_c = c1_bb_a;
        c1_cb_a = c1_c_i;
        c1_y_c = c1_cb_a;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_x_c + 1, 1, 1024, 1, 0) - 1].re =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_y_c + 1, 1, 1024, 1, 0) - 1].
          re + c1_temp.re;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_x_c + 1, 1, 1024, 1, 0) - 1].im =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_y_c + 1, 1, 1024, 1, 0) - 1].
          im + c1_temp.im;
        c1_db_a = c1_c_i;
        c1_j_b = c1_iDelta2;
        c1_c_i = c1_db_a + c1_j_b;
      }

      c1_eb_a = c1_istart + 1;
      c1_istart = c1_eb_a;
      c1_fb_a = c1_j;
      c1_k_b = c1_k;
    }

    c1_gb_a = c1_k;
    c1_i156 = c1_gb_a;
    c1_k = (c1_i156 + (c1_i156 < 0)) >> 1;
    c1_iDelta = c1_iDelta2;
    c1_hb_a = c1_iDelta;
    c1_iDelta2 = c1_hb_a << 1;
    c1_ib_a = c1_iheight;
    c1_l_b = c1_iDelta;
    c1_iheight = c1_ib_a - c1_l_b;
  }
}

static void c1_eml_size_ispow2(SFc1_LedaInstanceStruct *chartInstance)
{
}

static void c1_b_eml_scalar_eg(SFc1_LedaInstanceStruct *chartInstance)
{
}

static void c1_abs(SFc1_LedaInstanceStruct *chartInstance, creal_T c1_x[513],
                   real_T c1_y[513])
{
  int32_T c1_k;
  real_T c1_b_k;
  creal_T c1_b_x;
  real_T c1_x1;
  real_T c1_x2;
  real_T c1_a;
  real_T c1_b;
  real_T c1_b_y;
  for (c1_k = 0; c1_k < 513; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_b_x = c1_x[(int32_T)c1_b_k - 1];
    c1_x1 = c1_b_x.re;
    c1_x2 = c1_b_x.im;
    c1_a = c1_x1;
    c1_b = c1_x2;
    c1_b_y = muDoubleScalarHypot(c1_a, c1_b);
    c1_y[(int32_T)c1_b_k - 1] = c1_b_y;
  }
}

static real_T c1_sum(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[513])
{
  real_T c1_y;
  int32_T c1_k;
  int32_T c1_b_k;
  c1_y = c1_x[0];
  for (c1_k = 2; c1_k < 514; c1_k++) {
    c1_b_k = c1_k - 1;
    c1_y += c1_x[c1_b_k];
  }

  return c1_y;
}

static void c1_power(SFc1_LedaInstanceStruct *chartInstance, real_T c1_a[513],
                     real_T c1_y[513])
{
  int32_T c1_k;
  real_T c1_b_k;
  real_T c1_ak;
  real_T c1_b_a;
  real_T c1_c_a;
  real_T c1_b;
  real_T c1_b_y;
  for (c1_k = 0; c1_k < 513; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_ak = c1_a[(int32_T)c1_b_k - 1];
    c1_b_a = c1_ak;
    c1_eml_scalar_eg(chartInstance);
    c1_c_a = c1_b_a;
    c1_b = c1_b_a;
    c1_b_y = c1_c_a * c1_b;
    c1_y[(int32_T)c1_b_k - 1] = c1_b_y;
  }
}

static void c1_b_fft(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[1024],
                     creal_T c1_y[1024])
{
  int32_T c1_ix;
  int32_T c1_ju;
  int32_T c1_iy;
  int32_T c1_i;
  int32_T c1_a;
  int32_T c1_c;
  int32_T c1_b_a;
  int32_T c1_b_c;
  int32_T c1_n;
  boolean_T c1_tst;
  int32_T c1_b;
  int32_T c1_c_a;
  int32_T c1_d_a;
  int32_T c1_c_c;
  int32_T c1_e_a;
  int32_T c1_d_c;
  int32_T c1_b_i;
  int32_T c1_c_i;
  int32_T c1_f_a;
  int32_T c1_e_c;
  creal_T c1_temp;
  int32_T c1_g_a;
  int32_T c1_f_c;
  int32_T c1_h_a;
  int32_T c1_g_c;
  int32_T c1_i_a;
  int32_T c1_h_c;
  int32_T c1_j_a;
  int32_T c1_i_c;
  int32_T c1_iDelta;
  int32_T c1_iDelta2;
  int32_T c1_k;
  int32_T c1_iheight;
  int32_T c1_b_b;
  int32_T c1_ihi;
  int32_T c1_k_a;
  int32_T c1_c_b;
  int32_T c1_j_c;
  int32_T c1_l_a;
  int32_T c1_k_c;
  int32_T c1_m_a;
  int32_T c1_d_b;
  int32_T c1_l_c;
  int32_T c1_n_a;
  int32_T c1_m_c;
  int32_T c1_o_a;
  int32_T c1_n_c;
  int32_T c1_p_a;
  int32_T c1_o_c;
  int32_T c1_q_a;
  int32_T c1_p_c;
  int32_T c1_r_a;
  int32_T c1_e_b;
  int32_T c1_istart;
  int32_T c1_f_b;
  int32_T c1_j;
  int32_T c1_s_a;
  int32_T c1_q_c;
  int32_T c1_t_a;
  int32_T c1_r_c;
  static real_T c1_dv31[513] = { 1.0, 0.99998117528260111, 0.9999247018391445,
    0.9998305817958234, 0.99969881869620425, 0.99952941750109314,
    0.99932238458834954, 0.99907772775264536, 0.99879545620517241,
    0.99847558057329477, 0.99811811290014918, 0.99772306664419164,
    0.99729045667869021, 0.99682029929116567, 0.996312612182778,
    0.99576741446765982, 0.99518472667219693, 0.99456457073425542,
    0.99390697000235606, 0.9932119492347945, 0.99247953459871,
    0.99170975366909953, 0.99090263542778, 0.99005821026229712,
    0.989176509964781, 0.98825756773074946, 0.98730141815785843,
    0.98630809724459867, 0.98527764238894122, 0.984210092386929,
    0.98310548743121629, 0.98196386910955524, 0.98078528040323043,
    0.97956976568544052, 0.97831737071962765, 0.97702814265775439,
    0.97570213003852857, 0.97433938278557586, 0.97293995220556018,
    0.97150389098625178, 0.970031253194544, 0.96852209427441727,
    0.96697647104485207, 0.9653944416976894, 0.96377606579543984,
    0.96212140426904158, 0.96043051941556579, 0.9587034748958716,
    0.95694033573220882, 0.95514116830577078, 0.95330604035419386,
    0.95143502096900834, 0.94952818059303667, 0.94758559101774109,
    0.94560732538052128, 0.94359345816196039, 0.94154406518302081,
    0.93945922360218992, 0.937339011912575, 0.93518350993894761,
    0.932992798834739, 0.93076696107898371, 0.92850608047321559,
    0.92621024213831138, 0.92387953251128674, 0.9215140393420419,
    0.91911385169005777, 0.9166790599210427, 0.91420975570353069,
    0.91170603200542988, 0.90916798309052238, 0.90659570451491533,
    0.90398929312344334, 0.901348847046022, 0.89867446569395382,
    0.89596624975618522, 0.89322430119551532, 0.89044872324475788,
    0.88763962040285393, 0.88479709843093779, 0.881921264348355,
    0.87901222642863353, 0.8760700941954066, 0.87309497841829009,
    0.87008699110871146, 0.86704624551569265, 0.8639728561215867,
    0.86086693863776731, 0.85772861000027212, 0.85455798836540053,
    0.8513551931052652, 0.84812034480329723, 0.84485356524970712,
    0.84155497743689844, 0.83822470555483808, 0.83486287498638,
    0.83146961230254524, 0.8280450452577558, 0.82458930278502529,
    0.82110251499110465, 0.81758481315158371, 0.81403632970594841,
    0.81045719825259477, 0.80684755354379933, 0.80320753148064494,
    0.799537269107905, 0.79583690460888357, 0.79210657730021239,
    0.78834642762660634, 0.78455659715557524, 0.78073722857209449,
    0.77688846567323244, 0.773010453362737, 0.7691033376455797,
    0.765167265622459, 0.76120238548426178, 0.75720884650648457,
    0.75318679904361252, 0.74913639452345937, 0.745057785441466,
    0.74095112535495922, 0.73681656887736979, 0.73265427167241282,
    0.7284643904482252, 0.724247082951467, 0.72000250796138165,
    0.71573082528381859, 0.71143219574521643, 0.70710678118654757,
    0.7027547444572253, 0.69837624940897292, 0.69397146088965389,
    0.68954054473706683, 0.68508366777270036, 0.680600997795453,
    0.67609270357531592, 0.67155895484701833, 0.66699992230363747,
    0.66241577759017178, 0.65780669329707864, 0.65317284295377676,
    0.64851440102211244, 0.64383154288979139, 0.63912444486377573,
    0.63439328416364549, 0.629638238914927, 0.62485948814238634,
    0.6200572117632891, 0.61523159058062682, 0.61038280627630948,
    0.60551104140432555, 0.600616479383869, 0.59569930449243336,
    0.59075970185887416, 0.58579785745643886, 0.58081395809576453,
    0.57580819141784534, 0.57078074588696726, 0.56573181078361312,
    0.560661576197336, 0.55557023301960218, 0.55045797293660481,
    0.54532498842204646, 0.54017147272989285, 0.53499761988709715,
    0.52980362468629461, 0.524589682678469, 0.51935599016558964,
    0.51410274419322166, 0.508830142543107, 0.50353838372571758,
    0.49822766697278181, 0.49289819222978404, 0.487550160148436,
    0.48218377207912272, 0.47679923006332209, 0.47139673682599764,
    0.46597649576796618, 0.46053871095824, 0.45508358712634384,
    0.44961132965460654, 0.4441221445704292, 0.43861623853852766,
    0.43309381885315196, 0.42755509343028208, 0.42200027079979968,
    0.41642956009763715, 0.41084317105790391, 0.40524131400498986,
    0.39962419984564679, 0.3939920400610481, 0.38834504669882625,
    0.38268343236508978, 0.37700741021641826, 0.37131719395183749,
    0.36561299780477385, 0.35989503653498811, 0.35416352542049034,
    0.34841868024943456, 0.34266071731199438, 0.33688985339222005,
    0.33110630575987643, 0.32531029216226293, 0.31950203081601569,
    0.31368174039889152, 0.30784964004153487, 0.30200594931922808,
    0.29615088824362379, 0.29028467725446233, 0.28440753721127188,
    0.27851968938505306, 0.272621355449949, 0.26671275747489837,
    0.26079411791527551, 0.25486565960451457, 0.24892760574572015,
    0.24298017990326387, 0.2370236059943672, 0.23105810828067111,
    0.22508391135979283, 0.2191012401568698, 0.21311031991609136,
    0.20711137619221856, 0.2011046348420919, 0.19509032201612825,
    0.18906866414980619, 0.18303988795514095, 0.17700422041214875,
    0.17096188876030122, 0.16491312048996992, 0.15885814333386145,
    0.15279718525844344, 0.14673047445536175, 0.14065823933284921,
    0.13458070850712617, 0.12849811079379317, 0.1224106751992162,
    0.11631863091190475, 0.11022220729388306, 0.10412163387205459,
    0.0980171403295606, 0.091908956497132724, 0.0857973123444399,
    0.079682437971430126, 0.073564563599667426, 0.067443919563664051,
    0.061320736302208578, 0.055195244349689941, 0.049067674327418015,
    0.04293825693494082, 0.036807222941358832, 0.030674803176636626,
    0.024541228522912288, 0.01840672990580482, 0.012271538285719925,
    0.0061358846491544753, 0.0, -0.0061358846491544753, -0.012271538285719925,
    -0.01840672990580482, -0.024541228522912288, -0.030674803176636626,
    -0.036807222941358832, -0.04293825693494082, -0.049067674327418015,
    -0.055195244349689941, -0.061320736302208578, -0.067443919563664051,
    -0.073564563599667426, -0.079682437971430126, -0.0857973123444399,
    -0.091908956497132724, -0.0980171403295606, -0.10412163387205459,
    -0.11022220729388306, -0.11631863091190475, -0.1224106751992162,
    -0.12849811079379317, -0.13458070850712617, -0.14065823933284921,
    -0.14673047445536175, -0.15279718525844344, -0.15885814333386145,
    -0.16491312048996992, -0.17096188876030122, -0.17700422041214875,
    -0.18303988795514095, -0.18906866414980619, -0.19509032201612825,
    -0.2011046348420919, -0.20711137619221856, -0.21311031991609136,
    -0.2191012401568698, -0.22508391135979283, -0.23105810828067111,
    -0.2370236059943672, -0.24298017990326387, -0.24892760574572015,
    -0.25486565960451457, -0.26079411791527551, -0.26671275747489837,
    -0.272621355449949, -0.27851968938505306, -0.28440753721127188,
    -0.29028467725446233, -0.29615088824362379, -0.30200594931922808,
    -0.30784964004153487, -0.31368174039889152, -0.31950203081601569,
    -0.32531029216226293, -0.33110630575987643, -0.33688985339222005,
    -0.34266071731199438, -0.34841868024943456, -0.35416352542049034,
    -0.35989503653498811, -0.36561299780477385, -0.37131719395183749,
    -0.37700741021641826, -0.38268343236508978, -0.38834504669882625,
    -0.3939920400610481, -0.39962419984564679, -0.40524131400498986,
    -0.41084317105790391, -0.41642956009763715, -0.42200027079979968,
    -0.42755509343028208, -0.43309381885315196, -0.43861623853852766,
    -0.4441221445704292, -0.44961132965460654, -0.45508358712634384,
    -0.46053871095824, -0.46597649576796618, -0.47139673682599764,
    -0.47679923006332209, -0.48218377207912272, -0.487550160148436,
    -0.49289819222978404, -0.49822766697278181, -0.50353838372571758,
    -0.508830142543107, -0.51410274419322166, -0.51935599016558964,
    -0.524589682678469, -0.52980362468629461, -0.53499761988709715,
    -0.54017147272989285, -0.54532498842204646, -0.55045797293660481,
    -0.55557023301960218, -0.560661576197336, -0.56573181078361312,
    -0.57078074588696726, -0.57580819141784534, -0.58081395809576453,
    -0.58579785745643886, -0.59075970185887416, -0.59569930449243336,
    -0.600616479383869, -0.60551104140432555, -0.61038280627630948,
    -0.61523159058062682, -0.6200572117632891, -0.62485948814238634,
    -0.629638238914927, -0.63439328416364549, -0.63912444486377573,
    -0.64383154288979139, -0.64851440102211244, -0.65317284295377676,
    -0.65780669329707864, -0.66241577759017178, -0.66699992230363747,
    -0.67155895484701833, -0.67609270357531592, -0.680600997795453,
    -0.68508366777270036, -0.68954054473706683, -0.69397146088965389,
    -0.69837624940897292, -0.7027547444572253, -0.70710678118654757,
    -0.71143219574521643, -0.71573082528381859, -0.72000250796138165,
    -0.724247082951467, -0.7284643904482252, -0.73265427167241282,
    -0.73681656887736979, -0.74095112535495922, -0.745057785441466,
    -0.74913639452345937, -0.75318679904361252, -0.75720884650648457,
    -0.76120238548426178, -0.765167265622459, -0.7691033376455797,
    -0.773010453362737, -0.77688846567323244, -0.78073722857209449,
    -0.78455659715557524, -0.78834642762660634, -0.79210657730021239,
    -0.79583690460888357, -0.799537269107905, -0.80320753148064494,
    -0.80684755354379933, -0.81045719825259477, -0.81403632970594841,
    -0.81758481315158371, -0.82110251499110465, -0.82458930278502529,
    -0.8280450452577558, -0.83146961230254524, -0.83486287498638,
    -0.83822470555483808, -0.84155497743689844, -0.84485356524970712,
    -0.84812034480329723, -0.8513551931052652, -0.85455798836540053,
    -0.85772861000027212, -0.86086693863776731, -0.8639728561215867,
    -0.86704624551569265, -0.87008699110871146, -0.87309497841829009,
    -0.8760700941954066, -0.87901222642863353, -0.881921264348355,
    -0.88479709843093779, -0.88763962040285393, -0.89044872324475788,
    -0.89322430119551532, -0.89596624975618522, -0.89867446569395382,
    -0.901348847046022, -0.90398929312344334, -0.90659570451491533,
    -0.90916798309052238, -0.91170603200542988, -0.91420975570353069,
    -0.9166790599210427, -0.91911385169005777, -0.9215140393420419,
    -0.92387953251128674, -0.92621024213831138, -0.92850608047321559,
    -0.93076696107898371, -0.932992798834739, -0.93518350993894761,
    -0.937339011912575, -0.93945922360218992, -0.94154406518302081,
    -0.94359345816196039, -0.94560732538052128, -0.94758559101774109,
    -0.94952818059303667, -0.95143502096900834, -0.95330604035419386,
    -0.95514116830577078, -0.95694033573220882, -0.9587034748958716,
    -0.96043051941556579, -0.96212140426904158, -0.96377606579543984,
    -0.9653944416976894, -0.96697647104485207, -0.96852209427441727,
    -0.970031253194544, -0.97150389098625178, -0.97293995220556018,
    -0.97433938278557586, -0.97570213003852857, -0.97702814265775439,
    -0.97831737071962765, -0.97956976568544052, -0.98078528040323043,
    -0.98196386910955524, -0.98310548743121629, -0.984210092386929,
    -0.98527764238894122, -0.98630809724459867, -0.98730141815785843,
    -0.98825756773074946, -0.989176509964781, -0.99005821026229712,
    -0.99090263542778, -0.99170975366909953, -0.99247953459871,
    -0.9932119492347945, -0.99390697000235606, -0.99456457073425542,
    -0.99518472667219693, -0.99576741446765982, -0.996312612182778,
    -0.99682029929116567, -0.99729045667869021, -0.99772306664419164,
    -0.99811811290014918, -0.99847558057329477, -0.99879545620517241,
    -0.99907772775264536, -0.99932238458834954, -0.99952941750109314,
    -0.99969881869620425, -0.9998305817958234, -0.9999247018391445,
    -0.99998117528260111, -1.0 };

  creal_T c1_twid;
  static real_T c1_dv32[513] = { 0.0, -0.0061358846491544753,
    -0.012271538285719925, -0.01840672990580482, -0.024541228522912288,
    -0.030674803176636626, -0.036807222941358832, -0.04293825693494082,
    -0.049067674327418015, -0.055195244349689941, -0.061320736302208578,
    -0.067443919563664051, -0.073564563599667426, -0.079682437971430126,
    -0.0857973123444399, -0.091908956497132724, -0.0980171403295606,
    -0.10412163387205459, -0.11022220729388306, -0.11631863091190475,
    -0.1224106751992162, -0.12849811079379317, -0.13458070850712617,
    -0.14065823933284921, -0.14673047445536175, -0.15279718525844344,
    -0.15885814333386145, -0.16491312048996992, -0.17096188876030122,
    -0.17700422041214875, -0.18303988795514095, -0.18906866414980619,
    -0.19509032201612825, -0.2011046348420919, -0.20711137619221856,
    -0.21311031991609136, -0.2191012401568698, -0.22508391135979283,
    -0.23105810828067111, -0.2370236059943672, -0.24298017990326387,
    -0.24892760574572015, -0.25486565960451457, -0.26079411791527551,
    -0.26671275747489837, -0.272621355449949, -0.27851968938505306,
    -0.28440753721127188, -0.29028467725446233, -0.29615088824362379,
    -0.30200594931922808, -0.30784964004153487, -0.31368174039889152,
    -0.31950203081601569, -0.32531029216226293, -0.33110630575987643,
    -0.33688985339222005, -0.34266071731199438, -0.34841868024943456,
    -0.35416352542049034, -0.35989503653498811, -0.36561299780477385,
    -0.37131719395183749, -0.37700741021641826, -0.38268343236508978,
    -0.38834504669882625, -0.3939920400610481, -0.39962419984564679,
    -0.40524131400498986, -0.41084317105790391, -0.41642956009763715,
    -0.42200027079979968, -0.42755509343028208, -0.43309381885315196,
    -0.43861623853852766, -0.4441221445704292, -0.44961132965460654,
    -0.45508358712634384, -0.46053871095824, -0.46597649576796618,
    -0.47139673682599764, -0.47679923006332209, -0.48218377207912272,
    -0.487550160148436, -0.49289819222978404, -0.49822766697278181,
    -0.50353838372571758, -0.508830142543107, -0.51410274419322166,
    -0.51935599016558964, -0.524589682678469, -0.52980362468629461,
    -0.53499761988709715, -0.54017147272989285, -0.54532498842204646,
    -0.55045797293660481, -0.55557023301960218, -0.560661576197336,
    -0.56573181078361312, -0.57078074588696726, -0.57580819141784534,
    -0.58081395809576453, -0.58579785745643886, -0.59075970185887416,
    -0.59569930449243336, -0.600616479383869, -0.60551104140432555,
    -0.61038280627630948, -0.61523159058062682, -0.6200572117632891,
    -0.62485948814238634, -0.629638238914927, -0.63439328416364549,
    -0.63912444486377573, -0.64383154288979139, -0.64851440102211244,
    -0.65317284295377676, -0.65780669329707864, -0.66241577759017178,
    -0.66699992230363747, -0.67155895484701833, -0.67609270357531592,
    -0.680600997795453, -0.68508366777270036, -0.68954054473706683,
    -0.69397146088965389, -0.69837624940897292, -0.7027547444572253,
    -0.70710678118654757, -0.71143219574521643, -0.71573082528381859,
    -0.72000250796138165, -0.724247082951467, -0.7284643904482252,
    -0.73265427167241282, -0.73681656887736979, -0.74095112535495922,
    -0.745057785441466, -0.74913639452345937, -0.75318679904361252,
    -0.75720884650648457, -0.76120238548426178, -0.765167265622459,
    -0.7691033376455797, -0.773010453362737, -0.77688846567323244,
    -0.78073722857209449, -0.78455659715557524, -0.78834642762660634,
    -0.79210657730021239, -0.79583690460888357, -0.799537269107905,
    -0.80320753148064494, -0.80684755354379933, -0.81045719825259477,
    -0.81403632970594841, -0.81758481315158371, -0.82110251499110465,
    -0.82458930278502529, -0.8280450452577558, -0.83146961230254524,
    -0.83486287498638, -0.83822470555483808, -0.84155497743689844,
    -0.84485356524970712, -0.84812034480329723, -0.8513551931052652,
    -0.85455798836540053, -0.85772861000027212, -0.86086693863776731,
    -0.8639728561215867, -0.86704624551569265, -0.87008699110871146,
    -0.87309497841829009, -0.8760700941954066, -0.87901222642863353,
    -0.881921264348355, -0.88479709843093779, -0.88763962040285393,
    -0.89044872324475788, -0.89322430119551532, -0.89596624975618522,
    -0.89867446569395382, -0.901348847046022, -0.90398929312344334,
    -0.90659570451491533, -0.90916798309052238, -0.91170603200542988,
    -0.91420975570353069, -0.9166790599210427, -0.91911385169005777,
    -0.9215140393420419, -0.92387953251128674, -0.92621024213831138,
    -0.92850608047321559, -0.93076696107898371, -0.932992798834739,
    -0.93518350993894761, -0.937339011912575, -0.93945922360218992,
    -0.94154406518302081, -0.94359345816196039, -0.94560732538052128,
    -0.94758559101774109, -0.94952818059303667, -0.95143502096900834,
    -0.95330604035419386, -0.95514116830577078, -0.95694033573220882,
    -0.9587034748958716, -0.96043051941556579, -0.96212140426904158,
    -0.96377606579543984, -0.9653944416976894, -0.96697647104485207,
    -0.96852209427441727, -0.970031253194544, -0.97150389098625178,
    -0.97293995220556018, -0.97433938278557586, -0.97570213003852857,
    -0.97702814265775439, -0.97831737071962765, -0.97956976568544052,
    -0.98078528040323043, -0.98196386910955524, -0.98310548743121629,
    -0.984210092386929, -0.98527764238894122, -0.98630809724459867,
    -0.98730141815785843, -0.98825756773074946, -0.989176509964781,
    -0.99005821026229712, -0.99090263542778, -0.99170975366909953,
    -0.99247953459871, -0.9932119492347945, -0.99390697000235606,
    -0.99456457073425542, -0.99518472667219693, -0.99576741446765982,
    -0.996312612182778, -0.99682029929116567, -0.99729045667869021,
    -0.99772306664419164, -0.99811811290014918, -0.99847558057329477,
    -0.99879545620517241, -0.99907772775264536, -0.99932238458834954,
    -0.99952941750109314, -0.99969881869620425, -0.9998305817958234,
    -0.9999247018391445, -0.99998117528260111, -1.0, -0.99998117528260111,
    -0.9999247018391445, -0.9998305817958234, -0.99969881869620425,
    -0.99952941750109314, -0.99932238458834954, -0.99907772775264536,
    -0.99879545620517241, -0.99847558057329477, -0.99811811290014918,
    -0.99772306664419164, -0.99729045667869021, -0.99682029929116567,
    -0.996312612182778, -0.99576741446765982, -0.99518472667219693,
    -0.99456457073425542, -0.99390697000235606, -0.9932119492347945,
    -0.99247953459871, -0.99170975366909953, -0.99090263542778,
    -0.99005821026229712, -0.989176509964781, -0.98825756773074946,
    -0.98730141815785843, -0.98630809724459867, -0.98527764238894122,
    -0.984210092386929, -0.98310548743121629, -0.98196386910955524,
    -0.98078528040323043, -0.97956976568544052, -0.97831737071962765,
    -0.97702814265775439, -0.97570213003852857, -0.97433938278557586,
    -0.97293995220556018, -0.97150389098625178, -0.970031253194544,
    -0.96852209427441727, -0.96697647104485207, -0.9653944416976894,
    -0.96377606579543984, -0.96212140426904158, -0.96043051941556579,
    -0.9587034748958716, -0.95694033573220882, -0.95514116830577078,
    -0.95330604035419386, -0.95143502096900834, -0.94952818059303667,
    -0.94758559101774109, -0.94560732538052128, -0.94359345816196039,
    -0.94154406518302081, -0.93945922360218992, -0.937339011912575,
    -0.93518350993894761, -0.932992798834739, -0.93076696107898371,
    -0.92850608047321559, -0.92621024213831138, -0.92387953251128674,
    -0.9215140393420419, -0.91911385169005777, -0.9166790599210427,
    -0.91420975570353069, -0.91170603200542988, -0.90916798309052238,
    -0.90659570451491533, -0.90398929312344334, -0.901348847046022,
    -0.89867446569395382, -0.89596624975618522, -0.89322430119551532,
    -0.89044872324475788, -0.88763962040285393, -0.88479709843093779,
    -0.881921264348355, -0.87901222642863353, -0.8760700941954066,
    -0.87309497841829009, -0.87008699110871146, -0.86704624551569265,
    -0.8639728561215867, -0.86086693863776731, -0.85772861000027212,
    -0.85455798836540053, -0.8513551931052652, -0.84812034480329723,
    -0.84485356524970712, -0.84155497743689844, -0.83822470555483808,
    -0.83486287498638, -0.83146961230254524, -0.8280450452577558,
    -0.82458930278502529, -0.82110251499110465, -0.81758481315158371,
    -0.81403632970594841, -0.81045719825259477, -0.80684755354379933,
    -0.80320753148064494, -0.799537269107905, -0.79583690460888357,
    -0.79210657730021239, -0.78834642762660634, -0.78455659715557524,
    -0.78073722857209449, -0.77688846567323244, -0.773010453362737,
    -0.7691033376455797, -0.765167265622459, -0.76120238548426178,
    -0.75720884650648457, -0.75318679904361252, -0.74913639452345937,
    -0.745057785441466, -0.74095112535495922, -0.73681656887736979,
    -0.73265427167241282, -0.7284643904482252, -0.724247082951467,
    -0.72000250796138165, -0.71573082528381859, -0.71143219574521643,
    -0.70710678118654757, -0.7027547444572253, -0.69837624940897292,
    -0.69397146088965389, -0.68954054473706683, -0.68508366777270036,
    -0.680600997795453, -0.67609270357531592, -0.67155895484701833,
    -0.66699992230363747, -0.66241577759017178, -0.65780669329707864,
    -0.65317284295377676, -0.64851440102211244, -0.64383154288979139,
    -0.63912444486377573, -0.63439328416364549, -0.629638238914927,
    -0.62485948814238634, -0.6200572117632891, -0.61523159058062682,
    -0.61038280627630948, -0.60551104140432555, -0.600616479383869,
    -0.59569930449243336, -0.59075970185887416, -0.58579785745643886,
    -0.58081395809576453, -0.57580819141784534, -0.57078074588696726,
    -0.56573181078361312, -0.560661576197336, -0.55557023301960218,
    -0.55045797293660481, -0.54532498842204646, -0.54017147272989285,
    -0.53499761988709715, -0.52980362468629461, -0.524589682678469,
    -0.51935599016558964, -0.51410274419322166, -0.508830142543107,
    -0.50353838372571758, -0.49822766697278181, -0.49289819222978404,
    -0.487550160148436, -0.48218377207912272, -0.47679923006332209,
    -0.47139673682599764, -0.46597649576796618, -0.46053871095824,
    -0.45508358712634384, -0.44961132965460654, -0.4441221445704292,
    -0.43861623853852766, -0.43309381885315196, -0.42755509343028208,
    -0.42200027079979968, -0.41642956009763715, -0.41084317105790391,
    -0.40524131400498986, -0.39962419984564679, -0.3939920400610481,
    -0.38834504669882625, -0.38268343236508978, -0.37700741021641826,
    -0.37131719395183749, -0.36561299780477385, -0.35989503653498811,
    -0.35416352542049034, -0.34841868024943456, -0.34266071731199438,
    -0.33688985339222005, -0.33110630575987643, -0.32531029216226293,
    -0.31950203081601569, -0.31368174039889152, -0.30784964004153487,
    -0.30200594931922808, -0.29615088824362379, -0.29028467725446233,
    -0.28440753721127188, -0.27851968938505306, -0.272621355449949,
    -0.26671275747489837, -0.26079411791527551, -0.25486565960451457,
    -0.24892760574572015, -0.24298017990326387, -0.2370236059943672,
    -0.23105810828067111, -0.22508391135979283, -0.2191012401568698,
    -0.21311031991609136, -0.20711137619221856, -0.2011046348420919,
    -0.19509032201612825, -0.18906866414980619, -0.18303988795514095,
    -0.17700422041214875, -0.17096188876030122, -0.16491312048996992,
    -0.15885814333386145, -0.15279718525844344, -0.14673047445536175,
    -0.14065823933284921, -0.13458070850712617, -0.12849811079379317,
    -0.1224106751992162, -0.11631863091190475, -0.11022220729388306,
    -0.10412163387205459, -0.0980171403295606, -0.091908956497132724,
    -0.0857973123444399, -0.079682437971430126, -0.073564563599667426,
    -0.067443919563664051, -0.061320736302208578, -0.055195244349689941,
    -0.049067674327418015, -0.04293825693494082, -0.036807222941358832,
    -0.030674803176636626, -0.024541228522912288, -0.01840672990580482,
    -0.012271538285719925, -0.0061358846491544753, -0.0 };

  int32_T c1_u_a;
  int32_T c1_g_b;
  int32_T c1_v_a;
  int32_T c1_h_b;
  int32_T c1_s_c;
  int32_T c1_w_a;
  int32_T c1_t_c;
  creal_T c1_b_temp;
  int32_T c1_x_a;
  int32_T c1_i_b;
  int32_T c1_u_c;
  int32_T c1_y_a;
  int32_T c1_v_c;
  int32_T c1_ab_a;
  int32_T c1_w_c;
  int32_T c1_bb_a;
  int32_T c1_x_c;
  int32_T c1_cb_a;
  int32_T c1_y_c;
  int32_T c1_db_a;
  int32_T c1_j_b;
  int32_T c1_eb_a;
  int32_T c1_fb_a;
  int32_T c1_k_b;
  int32_T c1_gb_a;
  int32_T c1_i157;
  int32_T c1_hb_a;
  int32_T c1_ib_a;
  int32_T c1_l_b;
  c1_eml_size_ispow2(chartInstance);
  c1_c_eml_scalar_eg(chartInstance);
  c1_ix = 0;
  c1_ju = 0;
  c1_iy = 0;
  for (c1_i = 1; c1_i < 1024; c1_i++) {
    c1_a = c1_iy;
    c1_c = c1_a;
    c1_b_a = c1_ix;
    c1_b_c = c1_b_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c + 1, 1, 1024, 1, 0) - 1].re =
      c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_b_c + 1, 1, 1024, 1, 0) - 1];
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c + 1, 1, 1024, 1, 0) - 1].im = 0.0;
    c1_n = 1024;
    c1_tst = TRUE;
    while (c1_tst) {
      c1_n >>= 1;
      c1_ju ^= c1_n;
      c1_tst = ((c1_ju & c1_n) == 0);
    }

    c1_b = c1_ju;
    c1_iy = c1_b;
    c1_c_a = c1_ix + 1;
    c1_ix = c1_c_a;
  }

  c1_d_a = c1_iy;
  c1_c_c = c1_d_a;
  c1_e_a = c1_ix;
  c1_d_c = c1_e_a;
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c_c + 1, 1, 1024, 1, 0) - 1].re =
    c1_x[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_d_c + 1, 1, 1024, 1, 0) - 1];
  c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_c_c + 1, 1, 1024, 1, 0) - 1].im = 0.0;
  for (c1_b_i = 0; c1_b_i < 1023; c1_b_i += 2) {
    c1_c_i = c1_b_i;
    c1_f_a = c1_c_i;
    c1_e_c = c1_f_a;
    c1_temp.re = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_e_c + 2, 1, 1024, 1, 0)
      - 1].re;
    c1_temp.im = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_e_c + 2, 1, 1024, 1, 0)
      - 1].im;
    c1_g_a = c1_c_i;
    c1_f_c = c1_g_a;
    c1_h_a = c1_c_i;
    c1_g_c = c1_h_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_f_c + 2, 1, 1024, 1, 0) - 1].re =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_g_c + 1, 1, 1024, 1, 0) - 1].re -
      c1_temp.re;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_f_c + 2, 1, 1024, 1, 0) - 1].im =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_g_c + 1, 1, 1024, 1, 0) - 1].im -
      c1_temp.im;
    c1_i_a = c1_c_i;
    c1_h_c = c1_i_a;
    c1_j_a = c1_c_i;
    c1_i_c = c1_j_a;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_h_c + 1, 1, 1024, 1, 0) - 1].re =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_i_c + 1, 1, 1024, 1, 0) - 1].re +
      c1_temp.re;
    c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_h_c + 1, 1, 1024, 1, 0) - 1].im =
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_i_c + 1, 1, 1024, 1, 0) - 1].im +
      c1_temp.im;
  }

  c1_iDelta = 2;
  c1_iDelta2 = 4;
  c1_k = 256;
  c1_iheight = 1021;
  while (c1_k > 0) {
    c1_c_i = 0;
    c1_b_b = c1_iheight;
    c1_ihi = c1_b_b;
    while (c1_c_i < c1_ihi) {
      c1_k_a = c1_c_i;
      c1_c_b = c1_iDelta;
      c1_j_c = c1_k_a + c1_c_b;
      c1_l_a = c1_j_c;
      c1_k_c = c1_l_a;
      c1_temp.re = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_k_c + 1, 1, 1024, 1,
        0) - 1].re;
      c1_temp.im = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_k_c + 1, 1, 1024, 1,
        0) - 1].im;
      c1_m_a = c1_c_i;
      c1_d_b = c1_iDelta;
      c1_l_c = c1_m_a + c1_d_b;
      c1_n_a = c1_l_c;
      c1_m_c = c1_n_a;
      c1_o_a = c1_c_i;
      c1_n_c = c1_o_a;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_m_c + 1, 1, 1024, 1, 0) - 1].re =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_n_c + 1, 1, 1024, 1, 0) - 1].re
        - c1_temp.re;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_m_c + 1, 1, 1024, 1, 0) - 1].im =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_n_c + 1, 1, 1024, 1, 0) - 1].im
        - c1_temp.im;
      c1_p_a = c1_c_i;
      c1_o_c = c1_p_a;
      c1_q_a = c1_c_i;
      c1_p_c = c1_q_a;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_o_c + 1, 1, 1024, 1, 0) - 1].re =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_p_c + 1, 1, 1024, 1, 0) - 1].re
        + c1_temp.re;
      c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_o_c + 1, 1, 1024, 1, 0) - 1].im =
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_p_c + 1, 1, 1024, 1, 0) - 1].im
        + c1_temp.im;
      c1_r_a = c1_c_i;
      c1_e_b = c1_iDelta2;
      c1_c_i = c1_r_a + c1_e_b;
    }

    c1_istart = 1;
    c1_f_b = c1_k;
    for (c1_j = c1_f_b; c1_j < 512; c1_j = c1_fb_a + c1_k_b) {
      c1_s_a = c1_j;
      c1_q_c = c1_s_a;
      c1_t_a = c1_j;
      c1_r_c = c1_t_a;
      c1_twid.re = c1_dv31[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_q_c + 1, 1, 513, 1,
        0) - 1];
      c1_twid.im = c1_dv32[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_r_c + 1, 1, 513, 1,
        0) - 1];
      c1_c_i = c1_istart;
      c1_u_a = c1_c_i;
      c1_g_b = c1_iheight;
      c1_ihi = c1_u_a + c1_g_b;
      while (c1_c_i < c1_ihi) {
        c1_v_a = c1_c_i;
        c1_h_b = c1_iDelta;
        c1_s_c = c1_v_a + c1_h_b;
        c1_w_a = c1_s_c;
        c1_t_c = c1_w_a;
        c1_temp.re = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_t_c + 1, 1, 1024, 1,
          0) - 1].re;
        c1_temp.im = c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_t_c + 1, 1, 1024, 1,
          0) - 1].im;
        c1_b_temp = c1_temp;
        c1_temp.re = c1_twid.re * c1_b_temp.re - c1_twid.im * c1_b_temp.im;
        c1_temp.im = c1_twid.re * c1_b_temp.im + c1_twid.im * c1_b_temp.re;
        c1_x_a = c1_c_i;
        c1_i_b = c1_iDelta;
        c1_u_c = c1_x_a + c1_i_b;
        c1_y_a = c1_u_c;
        c1_v_c = c1_y_a;
        c1_ab_a = c1_c_i;
        c1_w_c = c1_ab_a;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_v_c + 1, 1, 1024, 1, 0) - 1].re =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_w_c + 1, 1, 1024, 1, 0) - 1].
          re - c1_temp.re;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_v_c + 1, 1, 1024, 1, 0) - 1].im =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_w_c + 1, 1, 1024, 1, 0) - 1].
          im - c1_temp.im;
        c1_bb_a = c1_c_i;
        c1_x_c = c1_bb_a;
        c1_cb_a = c1_c_i;
        c1_y_c = c1_cb_a;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_x_c + 1, 1, 1024, 1, 0) - 1].re =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_y_c + 1, 1, 1024, 1, 0) - 1].
          re + c1_temp.re;
        c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_x_c + 1, 1, 1024, 1, 0) - 1].im =
          c1_y[_SFD_EML_ARRAY_BOUNDS_CHECK("", c1_y_c + 1, 1, 1024, 1, 0) - 1].
          im + c1_temp.im;
        c1_db_a = c1_c_i;
        c1_j_b = c1_iDelta2;
        c1_c_i = c1_db_a + c1_j_b;
      }

      c1_eb_a = c1_istart + 1;
      c1_istart = c1_eb_a;
      c1_fb_a = c1_j;
      c1_k_b = c1_k;
    }

    c1_gb_a = c1_k;
    c1_i157 = c1_gb_a;
    c1_k = (c1_i157 + (c1_i157 < 0)) >> 1;
    c1_iDelta = c1_iDelta2;
    c1_hb_a = c1_iDelta;
    c1_iDelta2 = c1_hb_a << 1;
    c1_ib_a = c1_iheight;
    c1_l_b = c1_iDelta;
    c1_iheight = c1_ib_a - c1_l_b;
  }
}

static void c1_c_eml_scalar_eg(SFc1_LedaInstanceStruct *chartInstance)
{
}

static void c1_b_abs(SFc1_LedaInstanceStruct *chartInstance, real_T c1_x[513],
                     real_T c1_y[513])
{
  int32_T c1_k;
  real_T c1_b_k;
  real_T c1_b_x;
  real_T c1_b_y;
  for (c1_k = 0; c1_k < 513; c1_k++) {
    c1_b_k = 1.0 + (real_T)c1_k;
    c1_b_x = c1_x[(int32_T)c1_b_k - 1];
    c1_b_y = muDoubleScalarAbs(c1_b_x);
    c1_y[(int32_T)c1_b_k - 1] = c1_b_y;
  }
}

static const mxArray *c1_ib_sf_marshallOut(void *chartInstanceVoid, void
  *c1_inData)
{
  const mxArray *c1_mxArrayOutData = NULL;
  int32_T c1_u;
  const mxArray *c1_y = NULL;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_mxArrayOutData = NULL;
  c1_u = *(int32_T *)c1_inData;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_create("y", &c1_u, 6, 0U, 0U, 0U, 0), FALSE);
  sf_mex_assign(&c1_mxArrayOutData, c1_y, FALSE);
  return c1_mxArrayOutData;
}

static int32_T c1_vb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  int32_T c1_y;
  int32_T c1_i158;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_i158, 1, 6, 0U, 0, 0U, 0);
  c1_y = c1_i158;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void c1_hb_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c1_mxArrayInData, const char_T *c1_varName, void *c1_outData)
{
  const mxArray *c1_b_sfEvent;
  const char_T *c1_identifier;
  emlrtMsgIdentifier c1_thisId;
  int32_T c1_y;
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)chartInstanceVoid;
  c1_b_sfEvent = sf_mex_dup(c1_mxArrayInData);
  c1_identifier = c1_varName;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_vb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_sfEvent),
    &c1_thisId);
  sf_mex_destroy(&c1_b_sfEvent);
  *(int32_T *)c1_outData = c1_y;
  sf_mex_destroy(&c1_mxArrayInData);
}

static uint8_T c1_wb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_Leda, const char_T *c1_identifier)
{
  uint8_T c1_y;
  emlrtMsgIdentifier c1_thisId;
  c1_thisId.fIdentifier = c1_identifier;
  c1_thisId.fParent = NULL;
  c1_y = c1_xb_emlrt_marshallIn(chartInstance, sf_mex_dup(c1_b_is_active_c1_Leda),
    &c1_thisId);
  sf_mex_destroy(&c1_b_is_active_c1_Leda);
  return c1_y;
}

static uint8_T c1_xb_emlrt_marshallIn(SFc1_LedaInstanceStruct *chartInstance,
  const mxArray *c1_u, const emlrtMsgIdentifier *c1_parentId)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_parentId, sf_mex_dup(c1_u), &c1_u0, 1, 3, 0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_u);
  return c1_y;
}

static void init_dsm_address_info(SFc1_LedaInstanceStruct *chartInstance)
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

void sf_c1_Leda_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(1083002641U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(4002547205U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4175860372U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1799732814U);
}

mxArray *sf_c1_Leda_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("BzaCLece7dyoTB2thjuysB");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,3,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(256);
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

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
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
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c1_Leda_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c1_Leda_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c1_Leda(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[8],T\"nota\",},{M[4],M[0],T\"bloque_act\",S'l','i','p'{{M1x2[151 161],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"bloque_ant\",S'l','i','p'{{M1x2[124 134],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"f_detec\",S'l','i','p'{{M1x2[90 97],M[0],}}},{M[4],M[0],T\"f_dur\",S'l','i','p'{{M1x2[68 73],M[0],}}},{M[4],M[0],T\"flag_nota\",S'l','i','p'{{M1x2[383 392],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"in_tot\",S'l','i','p'{{M1x2[78 84],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"nivel_param\",S'l','i','p'{{M1x2[300 311],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"piso_div_2\",S'l','i','p'{{M1x2[328 338],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"piso_ruido\",S'l','i','p'{{M1x2[273 283],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}}}",
    "100 S1x5'type','srcId','name','auxInfo'{{M[4],M[0],T\"piso_suma_2\",S'l','i','p'{{M1x2[355 366],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"ruido\",S'l','i','p'{{M1x2[178 183],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"ruido_2\",S'l','i','p'{{M1x2[223 230],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[4],M[0],T\"window\",S'l','i','p'{{M1x2[101 107],M[1],T\"C:/Users/Agus/Dropbox/DPLabUTN/partitura v14 05-06-15/funciones/dur_prueba_simulink.m\"}}},{M[8],M[0],T\"is_active_c1_Leda\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 15, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_Leda_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_LedaInstanceStruct *chartInstance;
    chartInstance = (SFc1_LedaInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _LedaMachineNumber_,
           1,
           1,
           1,
           4,
           0,
           0,
           0,
           0,
           6,
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
          _SFD_SET_DATA_PROPS(0,1,1,0,"bloque");
          _SFD_SET_DATA_PROPS(1,1,1,0,"fs");
          _SFD_SET_DATA_PROPS(2,1,1,0,"activar");
          _SFD_SET_DATA_PROPS(3,2,0,1,"nota");
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
        _SFD_CV_INIT_EML(0,1,1,7,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,1793);
        _SFD_CV_INIT_EML_IF(0,1,0,153,163,-1,1787);
        _SFD_CV_INIT_EML_IF(0,1,1,861,878,-1,950);
        _SFD_CV_INIT_EML_IF(0,1,2,1057,1069,1115,1131);
        _SFD_CV_INIT_EML_IF(0,1,3,1115,1131,-1,1131);
        _SFD_CV_INIT_EML_IF(0,1,4,1292,1305,-1,1777);
        _SFD_CV_INIT_EML_IF(0,1,5,1322,1337,1387,1451);
        _SFD_CV_INIT_EML_IF(0,1,6,1569,1590,-1,1744);
        _SFD_CV_INIT_SCRIPT(0,1,6,0,0,0,0,0,9,3);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"dur_prueba_simulink",0,-1,3051);
        _SFD_CV_INIT_SCRIPT_IF(0,0,449,467,-1,894);
        _SFD_CV_INIT_SCRIPT_IF(0,1,909,931,-1,1052);
        _SFD_CV_INIT_SCRIPT_IF(0,2,1968,2057,2985,3038);
        _SFD_CV_INIT_SCRIPT_IF(0,3,2201,2319,2483,2926);
        _SFD_CV_INIT_SCRIPT_IF(0,4,2483,2604,2780,2926);
        _SFD_CV_INIT_SCRIPT_IF(0,5,2780,2803,2861,2926);

        {
          static int condStart[] = { 1972, 2018 };

          static int condEnd[] = { 2012, 2056 };

          static int pfixExpr[] = { 0, 1, -2 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,0,1971,2057,2,0,&(condStart[0]),&(condEnd[0]),
            3,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2206, 2237, 2267 };

          static int condEnd[] = { 2231, 2260, 2318 };

          static int pfixExpr[] = { 0, 1, -2, 2, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,1,2204,2319,3,2,&(condStart[0]),&(condEnd[0]),
            5,&(pfixExpr[0]));
        }

        {
          static int condStart[] = { 2491, 2522, 2551, 2579 };

          static int condEnd[] = { 2516, 2545, 2573, 2603 };

          static int pfixExpr[] = { 0, 1, -3, 2, -3, 3, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(0,2,2490,2604,4,5,&(condStart[0]),&(condEnd[0]),
            7,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"fft_abs",0,-1,867);
        _SFD_CV_INIT_SCRIPT(2,1,4,0,0,0,4,0,2,1);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"FindPitch_simulink",0,-1,2514);
        _SFD_CV_INIT_SCRIPT_IF(2,0,1476,1494,-1,1550);
        _SFD_CV_INIT_SCRIPT_IF(2,1,1838,1846,-1,2450);
        _SFD_CV_INIT_SCRIPT_IF(2,2,1855,1883,-1,2442);
        _SFD_CV_INIT_SCRIPT_IF(2,3,1934,2035,-1,2414);
        _SFD_CV_INIT_SCRIPT_FOR(2,0,1026,1036,1135);
        _SFD_CV_INIT_SCRIPT_FOR(2,1,1445,1472,1554);
        _SFD_CV_INIT_SCRIPT_FOR(2,2,1804,1834,2454);
        _SFD_CV_INIT_SCRIPT_FOR(2,3,1896,1918,2430);

        {
          static int condStart[] = { 1939, 1989 };

          static int condEnd[] = { 1983, 2033 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(2,0,1938,2034,2,0,&(condStart[0]),&(condEnd[0]),
            3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(3,1,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"piso_ruido",0,-1,815);
        _SFD_CV_INIT_SCRIPT(4,1,9,0,0,0,1,0,2,1);
        _SFD_CV_INIT_SCRIPT_FCN(4,0,"max_relativos",0,-1,1980);
        _SFD_CV_INIT_SCRIPT_IF(4,0,738,759,-1,-2);
        _SFD_CV_INIT_SCRIPT_IF(4,1,871,892,935,1968);
        _SFD_CV_INIT_SCRIPT_IF(4,2,935,944,1103,1968);
        _SFD_CV_INIT_SCRIPT_IF(4,3,957,981,-1,1094);
        _SFD_CV_INIT_SCRIPT_IF(4,4,1120,1142,1532,1956);
        _SFD_CV_INIT_SCRIPT_IF(4,5,1159,1185,-1,1519);
        _SFD_CV_INIT_SCRIPT_IF(4,6,1206,1219,1350,1499);
        _SFD_CV_INIT_SCRIPT_IF(4,7,1553,1606,-1,1940);
        _SFD_CV_INIT_SCRIPT_IF(4,8,1627,1640,1771,1920);
        _SFD_CV_INIT_SCRIPT_FOR(4,0,838,863,1976);

        {
          static int condStart[] = { 1556, 1583 };

          static int condEnd[] = { 1579, 1606 };

          static int pfixExpr[] = { 0, 1, -3 };

          _SFD_CV_INIT_SCRIPT_MCDC(4,0,1556,1606,2,0,&(condStart[0]),&(condEnd[0]),
            3,&(pfixExpr[0]));
        }

        _SFD_CV_INIT_SCRIPT(5,1,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(5,0,"deteccion",0,-1,1469);
        _SFD_CV_INIT_SCRIPT_IF(5,0,831,848,1292,1465);

        {
          unsigned int dimVector[2];
          dimVector[0]= 256;
          dimVector[1]= 1;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c1_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c1_c_sf_marshallOut,(MexInFcnForType)c1_c_sf_marshallIn);

        {
          real_T *c1_fs;
          real_T *c1_activar;
          real_T *c1_nota;
          real_T (*c1_bloque)[256];
          c1_nota = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_activar = (real_T *)ssGetInputPortSignal(chartInstance->S, 2);
          c1_fs = (real_T *)ssGetInputPortSignal(chartInstance->S, 1);
          c1_bloque = (real_T (*)[256])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c1_bloque);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_fs);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_activar);
          _SFD_SET_DATA_VALUE_PTR(3U, c1_nota);
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
  return "wPqfUpjxt14VhNhuGdghYC";
}

static void sf_opaque_initialize_c1_Leda(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_LedaInstanceStruct*) chartInstanceVar)->S,0);
  initialize_params_c1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
  initialize_c1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_Leda(void *chartInstanceVar)
{
  enable_c1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_Leda(void *chartInstanceVar)
{
  disable_c1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_Leda(void *chartInstanceVar)
{
  sf_c1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c1_Leda(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_Leda((SFc1_LedaInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_Leda();/* state var info */
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

extern void sf_internal_set_sim_state_c1_Leda(SimStruct* S, const mxArray *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_Leda();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_Leda((SFc1_LedaInstanceStruct*)chartInfo->chartInstance,
                        mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c1_Leda(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_Leda(S);
}

static void sf_opaque_set_sim_state_c1_Leda(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_Leda(S, st);
}

static void sf_opaque_terminate_c1_Leda(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_LedaInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Leda_optimization_info();
    }

    finalize_c1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc1_Leda((SFc1_LedaInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_Leda(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_Leda((SFc1_LedaInstanceStruct*)(((ChartInfoStruct *)
      ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_Leda(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Leda_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(S,sf_get_instance_specialization(),infoStruct,
      1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(S,sf_get_instance_specialization(),
                infoStruct,1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop(S,
      sf_get_instance_specialization(),infoStruct,1,
      "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(S,sf_get_instance_specialization(),infoStruct,1);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,1,3);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,1,1);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=1; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 3; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(2223447356U));
  ssSetChecksum1(S,(2836995743U));
  ssSetChecksum2(S,(635924725U));
  ssSetChecksum3(S,(1192119566U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c1_Leda(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_Leda(SimStruct *S)
{
  SFc1_LedaInstanceStruct *chartInstance;
  chartInstance = (SFc1_LedaInstanceStruct *)utMalloc(sizeof
    (SFc1_LedaInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_LedaInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_Leda;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_Leda;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_Leda;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_Leda;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_Leda;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_Leda;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_Leda;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_Leda;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_Leda;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_Leda;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_Leda;
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

void c1_Leda_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_Leda(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_Leda(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_Leda(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_Leda_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}

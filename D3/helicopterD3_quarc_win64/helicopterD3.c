/*
 * helicopterD3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD3".
 *
 * Model version              : 11.5
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar  4 14:54:02 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterD3.h"
#include "helicopterD3_private.h"

/* Block signals (default storage) */
B_helicopterD3_T helicopterD3_B;

/* Continuous states */
X_helicopterD3_T helicopterD3_X;

/* Block states (default storage) */
DW_helicopterD3_T helicopterD3_DW;

/* Real-time model */
static RT_MODEL_helicopterD3_T helicopterD3_M_;
RT_MODEL_helicopterD3_T *const helicopterD3_M = &helicopterD3_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  helicopterD3_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopterD3_output(void)
{
  /* local block i/o variables */
  real_T rtb_Sum[4];
  real_T rtb_Clock;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Gain1_idx_2;
  real_T rtb_Gain1_idx_3;
  real_T rtb_Sum_b;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    /* set solver stop time */
    if (!(helicopterD3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopterD3_M->solverInfo,
                            ((helicopterD3_M->Timing.clockTickH0 + 1) *
        helicopterD3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopterD3_M->solverInfo,
                            ((helicopterD3_M->Timing.clockTick0 + 1) *
        helicopterD3_M->Timing.stepSize0 + helicopterD3_M->Timing.clockTickH0 *
        helicopterD3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopterD3_M)) {
    helicopterD3_M->Timing.t[0] = rtsiGetT(&helicopterD3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopterD3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopterD3_DW.HILReadEncoderTimebase_Task,
        1, &helicopterD3_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopterD3_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopterD3_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopterD3_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopterD3_B.TravelCounttorad = helicopterD3_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopterD3_P.TravelCounttorad_Gain;

    /* Sum: '<Root>/Sum4' incorporates:
     *  Constant: '<Root>/Pi'
     *  Gain: '<S13>/Gain'
     */
    helicopterD3_B.Sum4 = helicopterD3_P.Gain_Gain *
      helicopterD3_B.TravelCounttorad + helicopterD3_P.Pi_Value;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopterD3_B.PitchCounttorad = helicopterD3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopterD3_B.Gain = helicopterD3_P.Gain_Gain_a *
      helicopterD3_B.PitchCounttorad;

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopterD3_B.ElevationCounttorad = helicopterD3_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterD3_P.ElevationCounttorad_Gain;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     *  Gain: '<S8>/Gain'
     */
    helicopterD3_B.Sum = helicopterD3_P.Gain_Gain_lv *
      helicopterD3_B.ElevationCounttorad +
      helicopterD3_P.elavation_offsetdeg_Value;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S11>/Gain'
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopterD3_P.PitchTransferFcn_C *
    helicopterD3_X.PitchTransferFcn_CSTATE;
  rtb_Clock += helicopterD3_P.PitchTransferFcn_D *
    helicopterD3_B.PitchCounttorad;
  rtb_Clock *= helicopterD3_P.Gain_Gain_ae;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1_idx_2 = helicopterD3_P.Gain1_Gain * helicopterD3_B.Gain;
  rtb_Gain1_idx_3 = helicopterD3_P.Gain1_Gain * rtb_Clock;

  /* FromWorkspace: '<S6>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopterD3_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopterD3_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopterD3_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopterD3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopterD3_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 141;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 4; ++elIdx) {
              (&rtb_Sum[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 141;
            }
          }
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;

        {
          int_T elIdx;
          for (elIdx = 0; elIdx < 4; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 141;
          }
        }
      }
    }
  }

  /* Sum: '<S6>/Sum' incorporates:
   *  Gain: '<S14>/Gain'
   *  Gain: '<S2>/Gain1'
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  rtb_Sum[0] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Sum4 - rtb_Sum[0];
  rtb_Sum[1] = (helicopterD3_P.TravelTransferFcn_C *
                helicopterD3_X.TravelTransferFcn_CSTATE +
                helicopterD3_P.TravelTransferFcn_D *
                helicopterD3_B.TravelCounttorad) * helicopterD3_P.Gain_Gain_l *
    helicopterD3_P.Gain1_Gain - rtb_Sum[1];
  rtb_Sum[2] = rtb_Gain1_idx_2 - rtb_Sum[2];
  rtb_Sum[3] = rtb_Gain1_idx_3 - rtb_Sum[3];

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopterD3_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopterD3_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopterD3_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopterD3_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[140]) {
      currTimeIndex = 139;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    helicopterD3_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          rtb_Clock = pDataValues[currTimeIndex];
        } else {
          rtb_Clock = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Clock = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Gain: '<S6>/Gain'
   *  Sum: '<Root>/Sum3'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Gain1_idx_2 = (((rtb_Clock - (((helicopterD3_P.K[0] * rtb_Sum[0] +
    helicopterD3_P.K[1] * rtb_Sum[1]) + helicopterD3_P.K[2] * rtb_Sum[2]) +
    helicopterD3_P.K[3] * rtb_Sum[3])) - rtb_Gain1_idx_2) * helicopterD3_P.K_pp
                     - helicopterD3_P.K_pd * rtb_Gain1_idx_3) +
    helicopterD3_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopterD3_X.Integrator_CSTATE >= helicopterD3_P.Integrator_UpperSat) {
    helicopterD3_X.Integrator_CSTATE = helicopterD3_P.Integrator_UpperSat;
  } else {
    if (helicopterD3_X.Integrator_CSTATE <= helicopterD3_P.Integrator_LowerSat)
    {
      helicopterD3_X.Integrator_CSTATE = helicopterD3_P.Integrator_LowerSat;
    }
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  Integrator: '<S3>/Integrator'
   */
  rtb_Clock = helicopterD3_X.Integrator_CSTATE;

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Sum_b = helicopterD3_P.elevation_ref_Value - helicopterD3_P.Gain1_Gain *
    helicopterD3_B.Sum;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Gain: '<S9>/Gain'
   *  Sum: '<S3>/Sum1'
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  rtb_Gain1_idx_3 = ((helicopterD3_P.K_ep * rtb_Sum_b + rtb_Clock) -
                     (helicopterD3_P.ElevationTransferFcn_C *
                      helicopterD3_X.ElevationTransferFcn_CSTATE +
                      helicopterD3_P.ElevationTransferFcn_D *
                      helicopterD3_B.ElevationCounttorad) *
                     helicopterD3_P.Gain_Gain_n * helicopterD3_P.Gain1_Gain *
                     helicopterD3_P.K_ed) + helicopterD3_P.Vs_ff;

  /* Clock: '<S3>/Clock' */
  rtb_Clock = helicopterD3_M->Timing.t[0];

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopterD3_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterD3_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopterD3_B.In1 = helicopterD3_P.K_ei * rtb_Sum_b;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Sum_b = (rtb_Gain1_idx_2 + rtb_Gain1_idx_3) *
    helicopterD3_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Sum_b > helicopterD3_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD3_B.FrontmotorSaturation =
      helicopterD3_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum_b < helicopterD3_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD3_B.FrontmotorSaturation =
      helicopterD3_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD3_B.FrontmotorSaturation = rtb_Sum_b;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Sum_b = (rtb_Gain1_idx_3 - rtb_Gain1_idx_2) * helicopterD3_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Sum_b > helicopterD3_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD3_B.BackmotorSaturation =
      helicopterD3_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Sum_b < helicopterD3_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD3_B.BackmotorSaturation =
      helicopterD3_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD3_B.BackmotorSaturation = rtb_Sum_b;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopterD3/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopterD3_DW.HILWriteAnalog_Buffer[0] =
        helicopterD3_B.FrontmotorSaturation;
      helicopterD3_DW.HILWriteAnalog_Buffer[1] =
        helicopterD3_B.BackmotorSaturation;
      result = hil_write_analog(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILWriteAnalog_channels, 2,
        &helicopterD3_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopterD3_update(void)
{
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    rt_ertODEUpdateContinuousStates(&helicopterD3_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++helicopterD3_M->Timing.clockTick0)) {
    ++helicopterD3_M->Timing.clockTickH0;
  }

  helicopterD3_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopterD3_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++helicopterD3_M->Timing.clockTick1)) {
      ++helicopterD3_M->Timing.clockTickH1;
    }

    helicopterD3_M->Timing.t[1] = helicopterD3_M->Timing.clockTick1 *
      helicopterD3_M->Timing.stepSize1 + helicopterD3_M->Timing.clockTickH1 *
      helicopterD3_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopterD3_derivatives(void)
{
  XDot_helicopterD3_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopterD3_T *) helicopterD3_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD3_P.TravelTransferFcn_A *
    helicopterD3_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD3_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD3_P.PitchTransferFcn_A *
    helicopterD3_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD3_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD3_P.ElevationTransferFcn_A *
    helicopterD3_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD3_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopterD3_X.Integrator_CSTATE <= helicopterD3_P.Integrator_LowerSat);
  usat = (helicopterD3_X.Integrator_CSTATE >= helicopterD3_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopterD3_B.In1 > 0.0)) || (usat &&
       (helicopterD3_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopterD3_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopterD3_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterD3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopterD3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopterD3_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopterD3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
      return;
    }

    if ((helicopterD3_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopterD3_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopterD3_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopterD3_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopterD3_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_AIChannels, 8U,
        &helicopterD3_DW.HILInitialize_AIMinimums[0],
        &helicopterD3_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD3_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopterD3_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopterD3_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopterD3_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopterD3_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_AOChannels, 8U,
        &helicopterD3_DW.HILInitialize_AOMinimums[0],
        &helicopterD3_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD3_P.HILInitialize_AOStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD3_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_AOChannels, 8U,
        &helicopterD3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if (helicopterD3_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD3_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopterD3_DW.HILInitialize_Card,
         helicopterD3_P.HILInitialize_AOChannels, 8U,
         &helicopterD3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD3_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopterD3_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopterD3_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopterD3_DW.HILInitialize_Card,
         helicopterD3_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode
          *) &helicopterD3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD3_P.HILInitialize_EIStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopterD3_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopterD3_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_EIChannels, 8U,
        &helicopterD3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD3_P.HILInitialize_POPStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopterD3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterD3_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopterD3_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopterD3_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &helicopterD3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopterD3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            helicopterD3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopterD3_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopterD3_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopterD3_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopterD3_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopterD3_DW.HILInitialize_Card,
          &helicopterD3_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopterD3_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopterD3_DW.HILInitialize_Card,
          &helicopterD3_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopterD3_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopterD3_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterD3_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopterD3_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopterD3_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopterD3_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopterD3_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopterD3_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopterD3_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopterD3_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopterD3_DW.HILInitialize_POSortedFreqs
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopterD3_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopterD3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD3_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_POChannels, 8U,
        &helicopterD3_DW.HILInitialize_POSortedFreqs[0],
        &helicopterD3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD3_P.HILInitialize_POStart && !is_switching) ||
        (helicopterD3_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD3_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopterD3_DW.HILInitialize_Card,
        helicopterD3_P.HILInitialize_POChannels, 8U,
        &helicopterD3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }

    if (helicopterD3_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD3_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopterD3_DW.HILInitialize_Card,
         helicopterD3_P.HILInitialize_POChannels, 8U,
         &helicopterD3_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopterD3/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopterD3_DW.HILInitialize_Card,
      helicopterD3_P.HILReadEncoderTimebase_SamplesI,
      helicopterD3_P.HILReadEncoderTimebase_Channels, 3,
      &helicopterD3_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopterD3_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopterD3_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
    }
  }

  /* Start for FromWorkspace: '<S6>/From Workspace1' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931, 1.0, 1.0, 1.0,
      1.0, 0.99624948777273281, 0.98462289986820439, 0.96171664644017,
      0.92503476160138376, 0.87286126880436465, 0.80406362352777727,
      0.71991899095499279, 0.62478969055999412, 0.52424581577580931,
      0.42384006967950483, 0.32837688219139288, 0.24154455420988497,
      0.1658029081058528, 0.10244015389467137, 0.051731543770989666,
      0.013148888060868365, -0.014415867551388418, -0.032438023848012476,
      -0.042573966030402595, -0.04650953273805418, -0.04584546025205008,
      -0.042018559226891496, -0.036254772285998618, -0.029548861500353282,
      -0.022664929607310466, -0.016152055523552613, -0.010369821202292785,
      -0.0055192549212799511, -0.0016755818895558376, 0.0011799442263644364,
      0.0031310267149872338, 0.0043012971051926314, 0.0048338363566169228,
      0.00487533711072955, 0.0045646532839406541, 0.0040252542599969682,
      0.0033609707859389173, 0.002654369243940326, 0.00196710095888788,
      0.0013416255864570417, 0.00080378658254888166, 0.00036580914190381615,
      2.9386511414215067E-5, -0.00021138832070891991, -0.00036740695195385778,
      -0.00045233812499441119, -0.00048086521583428883, -0.0004673633995810179,
      -0.00042498186183700812, -0.00036507801595665621, -0.00029694135362292294,
      -0.0002277423158682107, -0.00016264452019823473, -0.00010502510246540784,
      -5.6756369497791905E-5, -1.8511232918462915E-5, 9.9358880248545789E-6,
      2.943247692326238E-5, 4.1207983054172205E-5, 4.6676726166025442E-5,
      4.7285033020050417E-5, 4.4400490694121344E-5, 3.9238861933794228E-5,
      3.2822859310655989E-5, 2.5966424636413416E-5, 1.9278214997059527E-5,
      1.3178477467050045E-5, 7.9242437888486486E-6, 3.6386635976600292E-6,
      3.4121784137624212E-7, -2.0235622311464239E-6, -3.5604513304173288E-6,
      -4.4018681428506693E-6, -4.6905594216691506E-6, -4.5665840898878665E-6,
      -4.1582632529193829E-6, -3.5765810122651725E-6, -2.9124286228253397E-6,
      -2.2360615759506671E-6, -1.5981670679323468E-6, -1.0320012898711727E-6,
      -5.561377709978107E-7, -1.7745809431377523E-7, 1.0589408415323507E-7,
      3.0179182808680634E-7, 4.2176025980397336E-7, 4.79032388164643E-7,
      4.8704268879905426E-7, 4.5834154486276436E-7, 4.0389067888795276E-7,
      3.3268610111072255E-7, 2.516488483496856E-7, 1.6572284731265946E-7,
      7.8121676197768143E-8, -9.3299109695644829E-9, -9.5809568112605636E-8,
      -1.8111268635489991E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, -0.015002048909069103, -0.046506351618113825,
      -0.091625013712137715, -0.14672753935514468, -0.20869397118807662,
      -0.27519058110634942, -0.336578530291138, -0.38051720157999441,
      -0.4021754991367395, -0.40162298438521793, -0.38185274995244778,
      -0.34732931192603156, -0.30296658441612867, -0.25345101684472565,
      -0.20283444049472682, -0.15433062284048521, -0.11025902244902713,
      -0.072088625186496225, -0.040543768729560482, -0.015742266830606335,
      0.0026562899440163903, 0.015307604100634331, 0.02305514776357151,
      0.026823643142581358, 0.027535727572171258, 0.026051496335031409,
      0.023128937285039314, 0.019402265124051334, 0.015374692126896454,
      0.011422104463681096, 0.0078043299544911906, 0.0046810815608215872,
      0.0021301570056971668, 0.00016600301645050807, -0.001242735307155584,
      -0.0021575960957747396, -0.0026571338962322042, -0.0028264061679943667,
      -0.0027490731402097829, -0.0025019014897233538, -0.0021513560156326402,
      -0.0017519097625802618, -0.0013456905219584043, -0.00096309932849254,
      -0.00062407452497975147, -0.00033972469216221357, -0.0001141083633595106,
      5.4007265013083784E-5, 0.00016952615097603902, 0.00023961538352140744,
      0.00027254664933493307, 0.00027679615101884906, 0.00026039118267990376,
      0.00023047767093130756, 0.00019307493187046372, 0.00015298054631731595,
      0.00011378848377326998, 7.79863555936312E-5, 4.7102024523639322E-5,
      2.1874972447412943E-5, 2.4332274160999048E-6, -1.1538169303716288E-5,
      -2.0646515041308463E-5, -2.5664010492552946E-5, -2.7425738696970291E-5,
      -2.6752838557415553E-5, -2.4398950120037933E-5, -2.1016934712805589E-5,
      -1.7142320764754476E-5, -1.3189783025135148E-5, -9.459120290090665E-6,
      -6.14755639708362E-6, -3.365667249733361E-6, -1.1547651152739268E-6,
      4.9590132712513655E-7, 1.6332833478739342E-6, 2.3267289626168415E-6,
      2.6566095577593324E-6, 2.7054681874986903E-6, 2.55157803207328E-6,
      2.2646631122446965E-6, 1.9034540754934482E-6, 1.5147187067361421E-6,
      1.133408713868041E-6, 7.8359097573428522E-7, 4.798737268686679E-7,
      2.2908851344267866E-7, 3.20412025376448E-8, -1.1480457574515942E-7,
      -2.178034638992463E-7, -2.84818311108921E-7, -3.2414901104414774E-7,
      -3.4370400414810456E-7, -3.5040468445956525E-7, -3.4980634866933048E-7,
      -3.4591862857216463E-7, -3.412124729691771E-7, -3.3680863093985967E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.10602875205866502,
      0.22266037932318383, 0.3188814718164108, 0.38944360631143271,
      0.43795507377675658, 0.469972642303804, 0.43386657935563477,
      0.31054174747137364, 0.1530725753246156, -0.0039049632455309125,
      -0.13972846625945107, -0.24399847466850133, -0.31353881488478452,
      -0.34995712045026289, -0.35773862999657391, -0.34280645844654012,
      -0.31148123959982038, -0.26977378969099153, -0.22294699772484211,
      -0.17528754315263168, -0.13003397244719789, -0.0894146566284762,
      -0.054756679642897488, -0.026634286062983348, -0.0050327407867571949,
      0.010489979521763892, 0.020655531172231512, 0.026338695531291423,
      0.0284653477203064, 0.027935380018660916, 0.025569048518922832,
      0.022073926805425526, 0.018028960498344349, 0.013881890240016959,
      0.0099564244414018788, 0.0064658866474065491, 0.0035305423885676479,
      0.0011963517678194036, -0.00054656030509014908, -0.0017469148250351951,
      -0.0024775215294078334, -0.0028231335587665107, -0.0028710024481464202,
      -0.0027040084349473359, -0.0023960978297744573, -0.0020096760185405182,
      -0.001594570043851995, -0.0011881770540639325, -0.000816443366629116,
      -0.00049536392691251763, -0.00023274560954167356, -3.0033854904965018E-5,
      0.00011594405079518033, 0.00021141727638829266, 0.00026434827472165967,
      0.00028337180412696394, 0.0002769945297166343, 0.00025303576832380603,
      0.00021827865657353396, 0.00017829516929179778, 0.00013740682864127329,
      9.8744496028535522E-5, 6.43743089983051E-5, 3.546174156499049E-5,
      1.245122211745997E-5, -4.7558011765369557E-6, -1.6636384457147102E-5,
      -2.3902793214625184E-5, -2.7384291566345809E-5, -2.7935027164138759E-5,
      -2.63668993710775E-5, -2.3404868819132396E-5, -1.9661330011966349E-5,
      -1.5625811878083873E-5, -1.166627997362113E-5, -8.0385817166073181E-6,
      -4.9010087486145437E-6, -2.3314700440257852E-6, -3.4531412129723549E-7,
      1.0876368577994455E-6, 2.0278050875122133E-6, 2.5528875311486843E-6,
      2.7474331329990775E-6, 2.6949534122078234E-6, 2.4723781836266667E-6,
      2.1465575325008146E-6, 1.7724541221397772E-6, 1.3926551509779728E-6,
      1.0378498918051093E-6, 7.2795681882453778E-7, 4.7363536082034585E-7,
      2.77974381512891E-7, 1.3820723865354267E-7, 4.735786551801624E-8,
      -4.2287922052963722E-9, -2.7476904085332876E-8, -3.3261293386210866E-8,
      -3.1124656296732667E-8, -2.98985329827417E-8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823464127, 0.46652650905809445,
      0.38488436997290759, 0.28224853798008503, 0.1940458698612835,
      0.12807027410817604, -0.14442425179269028, -0.49329932753705591,
      -0.6298766885870416, -0.62791015428059371, -0.54329401205568573,
      -0.41708003363620427, -0.27816136086513454, -0.14567322226191373,
      -0.031126038185243236, 0.05972868620013632, 0.12530087538688089,
      0.16682979963531785, 0.18730716786460017, 0.19063781828884438,
      0.18101428282173757, 0.16247726327488896, 0.13863190794231703,
      0.11248957431965854, 0.086406181104906485, 0.062090881234085807,
      0.040662206601871288, 0.02273265743624089, 0.008506608756060817,
      -0.0021198708065813983, -0.0094653259989522457, -0.013980486853988838,
      -0.016179865228324403, -0.016588281033309511, -0.015701863194459754,
      -0.013962151175981702, -0.011741377035355804, -0.0093367624829929566,
      -0.0069716482916380162, -0.0048014180797802926, -0.0029224268174906859,
      -0.0013824481174348625, -0.0001914755575200034, 0.0006679760527962624,
      0.0012316424206915632, 0.0015456872449356232, 0.0016604238987541398,
      0.0016255719591519353, 0.0014869347497390229, 0.0012843177588667556,
      0.0010504732694829257, 0.00081084701854721808, 0.00058391162280028281,
      0.00038189290237259266, 0.00021172399333338707, 7.6094117621178443E-5,
      -2.5509097640979767E-5, -9.5835045571574759E-5, -0.00013902844700114912,
      -0.00015993394912683397, -0.00016355336260187117, -0.0001546493304508702,
      -0.00013748074812100226, -0.000115650269733334, -9.2042077789910822E-5,
      -6.8828093176364559E-5, -4.75223331221675E-5, -2.9065635029621597E-5,
      -1.3925993406984626E-5, -2.2029423910914078E-6, 6.2725111725702471E-6,
      1.1848122208000441E-5, 1.4974155228969372E-5, 1.6142072535482628E-5,
      1.5838127618128406E-5, 1.4510793028250691E-5, 1.2550291871817871E-5,
      1.0278154818492582E-5, 7.94462369097057E-6, 5.7318039162250974E-6,
      3.7606729186546252E-6, 2.1003297743130217E-6, 7.7818240679068052E-7,
      -2.0991888365347323E-7, -8.9030091497312482E-7, -1.3032826048036215E-6,
      -1.4964136420683572E-6, -1.5191958853688407E-6, -1.4192210373943394E-6,
      -1.2395722931780655E-6, -1.0172858334984447E-6, -7.8264391865911074E-7,
      -5.5906857283358841E-7, -3.6339749363734692E-7, -2.0634663223946686E-7,
      -9.2992448615903385E-8, -2.3137557824161654E-8, 8.5465474975329421E-9,
      4.9044925866440088E-9, 2.5701434847483247E-8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopterD3_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD3_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD3_DW.FromWorkspace1_IWORK.PrevIndex = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.25, 0.5, 0.75, 1.0, 1.25, 1.5, 1.75,
      2.0, 2.25, 2.5, 2.75, 3.0, 3.25, 3.5, 3.75, 4.0, 4.25, 4.5, 4.75, 5.0,
      5.25, 5.5, 5.75, 6.0, 6.25, 6.5, 6.75, 7.0, 7.25, 7.5, 7.75, 8.0, 8.25,
      8.5, 8.75, 9.0, 9.25, 9.5, 9.75, 10.0, 10.25, 10.5, 10.75, 11.0, 11.25,
      11.5, 11.75, 12.0, 12.25, 12.5, 12.75, 13.0, 13.25, 13.5, 13.75, 14.0,
      14.25, 14.5, 14.75, 15.0, 15.25, 15.5, 15.75, 16.0, 16.25, 16.5, 16.75,
      17.0, 17.25, 17.5, 17.75, 18.0, 18.25, 18.5, 18.75, 19.0, 19.25, 19.5,
      19.75, 20.0, 20.25, 20.5, 20.75, 21.0, 21.25, 21.5, 21.75, 22.0, 22.25,
      22.5, 22.75, 23.0, 23.25, 23.5, 23.75, 24.0, 24.25, 24.5, 24.75, 25.0,
      25.25, 25.5, 25.75, 26.0, 26.25, 26.5, 26.75, 27.0, 27.25, 27.5, 27.75,
      28.0, 28.25, 28.5, 28.75, 29.0, 29.25, 29.5, 29.75, 30.0, 30.25, 30.5,
      30.75, 31.0, 31.25, 31.5, 31.75, 32.0, 32.25, 32.5, 32.75, 33.0, 33.25,
      33.5, 33.75, 34.0, 34.25, 34.5, 34.75, 35.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559832246,
      0.52359877559830881, 0.52359877559829038, 0.52359877559824708,
      0.52359877559824464, 0.52359877559792645, 0.2438423834020701,
      -0.12120871863172261, -0.28285781056205361, -0.38689341971613644,
      -0.44014100075886825, -0.45174525019692952, -0.43164619156996065,
      -0.38950105019368658, -0.33398167409349139, -0.27237528092105395,
      -0.21042010312390041, -0.15231298672230842, -0.10083409404294863,
      -0.05754280018187774, -0.023008107610211215, 0.0029542284433105026,
      0.021057609793328491, 0.032346310686863555, 0.03803001624961988,
      0.039353693101947362, 0.037501973384183152, 0.033534963195903322,
      0.028351016372769822, 0.022671372466861794, 0.017041472512535516,
      0.011844078470396813, 0.0073198922930886035, 0.0035920817307624198,
      0.0006918801389259599, -0.0014168318050888917, -0.0028153803953357981,
      -0.0036114278951333567, -0.003923744084689873, -0.0038706275539291957,
      -0.0035617269835006571, -0.003092847461684145, -0.0025432384995021096,
      -0.0019748328074721266, -0.0014329224291192988, -0.00094780719684051107,
      -0.00053701736772426845, -0.00020778766140894245, 4.0463973214666105E-5,
      0.00021382823469273671, 0.00032187946497119757, 0.00037599371703689322,
      0.000388028366934301, 0.00036935100940682641, 0.00033018442498788936,
      0.0002792218668671298, 0.00022346122607574959, 0.00016820620436452938,
      0.00011718595879817162, 7.27504542167301E-5, 3.6105856957124871E-5,
      7.5618431303325906E-6, -1.3229980094342508E-5, -2.7060682886492771E-5,
      -3.4980074725909915E-5, -3.8147993493553578E-5, -3.7721029493065217E-5,
      -3.4772346506728447E-5, -3.0240618906662853E-5, -2.4903216733762612E-5,
      -1.9368482416237676E-5, -1.4082099891621347E-5, -9.3430191141496977E-6,
      -5.3250453468933756E-6, -2.10093450014881E-6, 3.3342301863914514E-7,
      2.0364515931348137E-6, 3.101079556699915E-6, 3.6382606454221644E-6,
      3.7640133476735116E-6, 3.589861838237951E-6, 3.2163559722242496E-6,
      2.729224136355235E-6, 2.1976565139913973E-6, 1.6742121130564058E-6,
      1.195876236037563E-6, 7.8585302198952434E-7, 4.5574948270843407E-7,
      2.0788443333419337E-7, 3.7531461605233574E-8, -6.5024926776402481E-8,
      -1.1267939625803081E-7, -1.1995004634002271E-7, -1.0164368668963419E-7,
      -7.167780069483598E-8, -4.19727325118302E-8, -2.1313128262256953E-8,
      -1.4069121312410005E-8, -2.8261492590608839E-8, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

    helicopterD3_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD3_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD3_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopterD3_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopterD3_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopterD3_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopterD3_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopterD3_X.Integrator_CSTATE = helicopterD3_P.Integrator_IC;
}

/* Model terminate function */
void helicopterD3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterD3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopterD3_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopterD3_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopterD3_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopterD3_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD3_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD3_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopterD3_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopterD3_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD3_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD3_P.HILInitialize_POFinal;
        }
      }

      num_final_pwm_outputs = 8U;
    } else {
      num_final_pwm_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_pwm_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(helicopterD3_DW.HILInitialize_Card
                         , helicopterD3_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopterD3_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopterD3_DW.HILInitialize_AOVoltages[0]
                         , &helicopterD3_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopterD3_DW.HILInitialize_Card,
            helicopterD3_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopterD3_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopterD3_DW.HILInitialize_Card,
            helicopterD3_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopterD3_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD3_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopterD3_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopterD3_DW.HILInitialize_Card);
    hil_close(helicopterD3_DW.HILInitialize_Card);
    helicopterD3_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  helicopterD3_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopterD3_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  helicopterD3_initialize();
}

void MdlTerminate(void)
{
  helicopterD3_terminate();
}

/* Registration function */
RT_MODEL_helicopterD3_T *helicopterD3(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopterD3_P.Integrator_UpperSat = rtInf;
  helicopterD3_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopterD3_M, 0,
                sizeof(RT_MODEL_helicopterD3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopterD3_M->solverInfo,
                          &helicopterD3_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopterD3_M->solverInfo, &rtmGetTPtr(helicopterD3_M));
    rtsiSetStepSizePtr(&helicopterD3_M->solverInfo,
                       &helicopterD3_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopterD3_M->solverInfo, &helicopterD3_M->derivs);
    rtsiSetContStatesPtr(&helicopterD3_M->solverInfo, (real_T **)
                         &helicopterD3_M->contStates);
    rtsiSetNumContStatesPtr(&helicopterD3_M->solverInfo,
      &helicopterD3_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopterD3_M->solverInfo,
      &helicopterD3_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopterD3_M->solverInfo,
      &helicopterD3_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopterD3_M->solverInfo,
      &helicopterD3_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopterD3_M->solverInfo, (&rtmGetErrorStatus
      (helicopterD3_M)));
    rtsiSetRTModelPtr(&helicopterD3_M->solverInfo, helicopterD3_M);
  }

  rtsiSetSimTimeStep(&helicopterD3_M->solverInfo, MAJOR_TIME_STEP);
  helicopterD3_M->intgData.f[0] = helicopterD3_M->odeF[0];
  helicopterD3_M->contStates = ((real_T *) &helicopterD3_X);
  rtsiSetSolverData(&helicopterD3_M->solverInfo, (void *)
                    &helicopterD3_M->intgData);
  rtsiSetSolverName(&helicopterD3_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopterD3_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopterD3_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopterD3_M->Timing.sampleTimes =
      (&helicopterD3_M->Timing.sampleTimesArray[0]);
    helicopterD3_M->Timing.offsetTimes =
      (&helicopterD3_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopterD3_M->Timing.sampleTimes[0] = (0.0);
    helicopterD3_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopterD3_M->Timing.offsetTimes[0] = (0.0);
    helicopterD3_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopterD3_M, &helicopterD3_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopterD3_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopterD3_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopterD3_M, -1);
  helicopterD3_M->Timing.stepSize0 = 0.002;
  helicopterD3_M->Timing.stepSize1 = 0.002;
  helicopterD3_M->solverInfoPtr = (&helicopterD3_M->solverInfo);
  helicopterD3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterD3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterD3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterD3_M->blockIO = ((void *) &helicopterD3_B);

  {
    helicopterD3_B.TravelCounttorad = 0.0;
    helicopterD3_B.Sum4 = 0.0;
    helicopterD3_B.PitchCounttorad = 0.0;
    helicopterD3_B.Gain = 0.0;
    helicopterD3_B.ElevationCounttorad = 0.0;
    helicopterD3_B.Sum = 0.0;
    helicopterD3_B.FrontmotorSaturation = 0.0;
    helicopterD3_B.BackmotorSaturation = 0.0;
    helicopterD3_B.In1 = 0.0;
  }

  /* parameters */
  helicopterD3_M->defaultParam = ((real_T *)&helicopterD3_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopterD3_X;
    helicopterD3_M->contStates = (x);
    (void) memset((void *)&helicopterD3_X, 0,
                  sizeof(X_helicopterD3_T));
  }

  /* states (dwork) */
  helicopterD3_M->dwork = ((void *) &helicopterD3_DW);
  (void) memset((void *)&helicopterD3_DW, 0,
                sizeof(DW_helicopterD3_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD3_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopterD3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterD3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* Initialize Sizes */
  helicopterD3_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterD3_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterD3_M->Sizes.numY = (0);    /* Number of model outputs */
  helicopterD3_M->Sizes.numU = (0);    /* Number of model inputs */
  helicopterD3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterD3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterD3_M->Sizes.numBlocks = (52);/* Number of blocks */
  helicopterD3_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  helicopterD3_M->Sizes.numBlockPrms = (148);/* Sum of parameter "widths" */
  return helicopterD3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

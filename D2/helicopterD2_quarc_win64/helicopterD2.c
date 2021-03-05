/*
 * helicopterD2.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD2".
 *
 * Model version              : 11.6
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar  4 14:02:09 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterD2.h"
#include "helicopterD2_private.h"

/* Block signals (default storage) */
B_helicopterD2_T helicopterD2_B;

/* Continuous states */
X_helicopterD2_T helicopterD2_X;

/* Block states (default storage) */
DW_helicopterD2_T helicopterD2_DW;

/* Real-time model */
static RT_MODEL_helicopterD2_T helicopterD2_M_;
RT_MODEL_helicopterD2_T *const helicopterD2_M = &helicopterD2_M_;

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
  helicopterD2_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopterD2_output(void)
{
  /* local block i/o variables */
  real_T rtb_Clock;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Backgain;
  real_T rtb_Frontgain;
  real_T rtb_Sum;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* set solver stop time */
    if (!(helicopterD2_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopterD2_M->solverInfo,
                            ((helicopterD2_M->Timing.clockTickH0 + 1) *
        helicopterD2_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopterD2_M->solverInfo,
                            ((helicopterD2_M->Timing.clockTick0 + 1) *
        helicopterD2_M->Timing.stepSize0 + helicopterD2_M->Timing.clockTickH0 *
        helicopterD2_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopterD2_M)) {
    helicopterD2_M->Timing.t[0] = rtsiGetT(&helicopterD2_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopterD2/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopterD2_DW.HILReadEncoderTimebase_Task,
        1, &helicopterD2_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopterD2_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopterD2_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopterD2_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopterD2_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopterD2_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopterD2_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopterD2_M->Timing.t[0];

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

    helicopterD2_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

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

  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopterD2_B.TravelCounttorad = helicopterD2_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopterD2_P.TravelCounttorad_Gain;

    /* Gain: '<S13>/Gain' */
    helicopterD2_B.Gain = helicopterD2_P.Gain_Gain *
      helicopterD2_B.TravelCounttorad;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopterD2_B.PitchCounttorad = helicopterD2_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopterD2_B.Gain_i = helicopterD2_P.Gain_Gain_a *
      helicopterD2_B.PitchCounttorad;

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopterD2_B.ElevationCounttorad = helicopterD2_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterD2_P.ElevationCounttorad_Gain;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     *  Gain: '<S8>/Gain'
     */
    helicopterD2_B.Sum = helicopterD2_P.Gain_Gain_lv *
      helicopterD2_B.ElevationCounttorad +
      helicopterD2_P.elavation_offsetdeg_Value;
  }

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Sum: '<S5>/Sum2'
   */
  rtb_Clock -= helicopterD2_P.Gain1_Gain * helicopterD2_B.Gain_i;

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S11>/Gain'
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum3'
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  rtb_Backgain = (helicopterD2_P.K_pp * rtb_Clock -
                  (helicopterD2_P.PitchTransferFcn_C *
                   helicopterD2_X.PitchTransferFcn_CSTATE +
                   helicopterD2_P.PitchTransferFcn_D *
                   helicopterD2_B.PitchCounttorad) * helicopterD2_P.Gain_Gain_ae
                  * helicopterD2_P.Gain1_Gain * helicopterD2_P.K_pd) +
    helicopterD2_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopterD2_X.Integrator_CSTATE >= helicopterD2_P.Integrator_UpperSat) {
    helicopterD2_X.Integrator_CSTATE = helicopterD2_P.Integrator_UpperSat;
  } else {
    if (helicopterD2_X.Integrator_CSTATE <= helicopterD2_P.Integrator_LowerSat)
    {
      helicopterD2_X.Integrator_CSTATE = helicopterD2_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   *  Gain: '<S2>/Gain1'
   */
  rtb_Sum = helicopterD2_P.elevation_ref_Value - helicopterD2_P.Gain1_Gain *
    helicopterD2_B.Sum;

  /* Clock: '<S3>/Clock' incorporates:
   *  Gain: '<S2>/Gain1'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S9>/Gain'
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  rtb_Clock = (helicopterD2_P.ElevationTransferFcn_C *
               helicopterD2_X.ElevationTransferFcn_CSTATE +
               helicopterD2_P.ElevationTransferFcn_D *
               helicopterD2_B.ElevationCounttorad) * helicopterD2_P.Gain_Gain_n *
    helicopterD2_P.Gain1_Gain * helicopterD2_P.K_ed;

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Frontgain = ((helicopterD2_P.K_ep * rtb_Sum +
                    helicopterD2_X.Integrator_CSTATE) - rtb_Clock) +
    helicopterD2_P.Vs_ff;

  /* Clock: '<S3>/Clock' */
  rtb_Clock = helicopterD2_M->Timing.t[0];

  /* If: '<S3>/If' incorporates:
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopterD2_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterD2_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopterD2_B.In1 = helicopterD2_P.K_ei * rtb_Sum;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Sum = (rtb_Backgain + rtb_Frontgain) * helicopterD2_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Sum > helicopterD2_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD2_B.FrontmotorSaturation =
      helicopterD2_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum < helicopterD2_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD2_B.FrontmotorSaturation =
      helicopterD2_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD2_B.FrontmotorSaturation = rtb_Sum;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Sum = (rtb_Frontgain - rtb_Backgain) * helicopterD2_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Sum > helicopterD2_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD2_B.BackmotorSaturation =
      helicopterD2_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Sum < helicopterD2_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD2_B.BackmotorSaturation =
      helicopterD2_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD2_B.BackmotorSaturation = rtb_Sum;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopterD2/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopterD2_DW.HILWriteAnalog_Buffer[0] =
        helicopterD2_B.FrontmotorSaturation;
      helicopterD2_DW.HILWriteAnalog_Buffer[1] =
        helicopterD2_B.BackmotorSaturation;
      result = hil_write_analog(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILWriteAnalog_channels, 2,
        &helicopterD2_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopterD2_update(void)
{
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    rt_ertODEUpdateContinuousStates(&helicopterD2_M->solverInfo);
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
  if (!(++helicopterD2_M->Timing.clockTick0)) {
    ++helicopterD2_M->Timing.clockTickH0;
  }

  helicopterD2_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopterD2_M->solverInfo);

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
    if (!(++helicopterD2_M->Timing.clockTick1)) {
      ++helicopterD2_M->Timing.clockTickH1;
    }

    helicopterD2_M->Timing.t[1] = helicopterD2_M->Timing.clockTick1 *
      helicopterD2_M->Timing.stepSize1 + helicopterD2_M->Timing.clockTickH1 *
      helicopterD2_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopterD2_derivatives(void)
{
  XDot_helicopterD2_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopterD2_T *) helicopterD2_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD2_P.TravelTransferFcn_A *
    helicopterD2_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD2_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD2_P.PitchTransferFcn_A *
    helicopterD2_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD2_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD2_P.ElevationTransferFcn_A *
    helicopterD2_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD2_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopterD2_X.Integrator_CSTATE <= helicopterD2_P.Integrator_LowerSat);
  usat = (helicopterD2_X.Integrator_CSTATE >= helicopterD2_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopterD2_B.In1 > 0.0)) || (usat &&
       (helicopterD2_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopterD2_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopterD2_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterD2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopterD2_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopterD2_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopterD2_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
      return;
    }

    if ((helicopterD2_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopterD2_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopterD2_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopterD2_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopterD2_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_AIChannels, 8U,
        &helicopterD2_DW.HILInitialize_AIMinimums[0],
        &helicopterD2_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD2_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopterD2_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopterD2_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopterD2_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopterD2_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_AOChannels, 8U,
        &helicopterD2_DW.HILInitialize_AOMinimums[0],
        &helicopterD2_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD2_P.HILInitialize_AOStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD2_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_AOChannels, 8U,
        &helicopterD2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if (helicopterD2_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD2_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopterD2_DW.HILInitialize_Card,
         helicopterD2_P.HILInitialize_AOChannels, 8U,
         &helicopterD2_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD2_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopterD2_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopterD2_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopterD2_DW.HILInitialize_Card,
         helicopterD2_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode
          *) &helicopterD2_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD2_P.HILInitialize_EIStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopterD2_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopterD2_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_EIChannels, 8U,
        &helicopterD2_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD2_P.HILInitialize_POPStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopterD2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterD2_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopterD2_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopterD2_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &helicopterD2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopterD2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            helicopterD2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopterD2_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopterD2_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopterD2_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopterD2_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopterD2_DW.HILInitialize_Card,
          &helicopterD2_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopterD2_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopterD2_DW.HILInitialize_Card,
          &helicopterD2_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopterD2_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopterD2_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterD2_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopterD2_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopterD2_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopterD2_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopterD2_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopterD2_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopterD2_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopterD2_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopterD2_DW.HILInitialize_POSortedFreqs
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopterD2_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopterD2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD2_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_POChannels, 8U,
        &helicopterD2_DW.HILInitialize_POSortedFreqs[0],
        &helicopterD2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD2_P.HILInitialize_POStart && !is_switching) ||
        (helicopterD2_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD2_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopterD2_DW.HILInitialize_Card,
        helicopterD2_P.HILInitialize_POChannels, 8U,
        &helicopterD2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }

    if (helicopterD2_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD2_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopterD2_DW.HILInitialize_Card,
         helicopterD2_P.HILInitialize_POChannels, 8U,
         &helicopterD2_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopterD2/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopterD2_DW.HILInitialize_Card,
      helicopterD2_P.HILReadEncoderTimebase_SamplesI,
      helicopterD2_P.HILReadEncoderTimebase_Channels, 3,
      &helicopterD2_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopterD2_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopterD2_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
    }
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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829959,
      0.52359877559828794, 0.5235987755982846, 0.52359877559828039,
      0.52359877559827506, 0.52359877559827239, 0.523598775598274,
      0.52359877559827017, 0.52359877559826107, 0.52359877559824886,
      0.52359877559716328, 0.52359877559713175, 0.52359877559540713,
      -0.028435096217164613, -0.52359877559688273, -0.52359877559794488,
      -0.52359877559810408, -0.5235987755981597, -0.52359877559817547,
      -0.52359877559818269, -0.52359877559818213, -0.52359877559816825,
      -0.5235987755981194, -0.523598775597961, -0.5235987755979582,
      -0.52359877559802881, -0.5235987755946323, -0.439842800420693,
      -0.23673384022876715, -0.12713565573492291, -0.037925189210826826,
      0.029992099383180482, 0.077573047751628765, 0.10700768811589878,
      0.12119321707082287, 0.12331509683773245, 0.11653176250631259,
      0.10375392416238483, 0.087505934431737153, 0.069854888063047627,
      0.052392713987774675, 0.036257175834919608, 0.022179090902337273,
      0.01054492076647684, 0.0014659358041366755, -0.005152781189335931,
      -0.00954829155217407, -0.012043802769820977, -0.013002362336044349,
      -0.012790746233050099, -0.011753191157194642, -0.010194032468530123,
      -0.0083679541779215771, -0.0064763921354561438, -0.0046686144707102084,
      -0.0030460935916336584, -0.0016689450894257218, -0.000563409579157903,
      0.00027043126278025742, 0.00085130244317277448, 0.0012101522156332534,
      0.0013845757299945083, 0.0014143476219344864, 0.0013380602508443751,
      0.001190788900546691, 0.0010026564711578256, 0.0007981439089397302,
      0.00059598433887742, 0.00040948409818875042, 0.00024712845997643118,
      0.00011335014846003411, 9.3617707027648933E-6, -6.6023327002118215E-5,
      -0.00011563524265278957, -0.00014329067520213457, -0.00015325259966425531,
      -0.00014981100996247498, -0.00013697961945413617, -0.00011829681649944135,
      -9.6715241222122827E-5, -7.45626049701853E-5, -5.3556324057901783E-5,
      -3.4855714082127065E-5, -1.9137468425078907E-5, -6.6825661111380441E-6,
      2.5346680257998244E-6, 8.7621116334757332E-6, 1.2394460037312705E-5,
      1.3909373773546285E-5, 1.3815988235021948E-5, 1.2615348062405829E-5,
      1.0771414402643842E-5, 8.6906972741607191E-6, 6.7082430900144985E-6,
      5.0776087171522377E-6, 3.9625263805742605E-6, 3.4281564402771636E-6,
      3.4300856743829655E-6, 5.3789465609410669E-6, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0 } ;

    helicopterD2_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD2_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD2_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopterD2_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopterD2_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopterD2_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopterD2_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopterD2_X.Integrator_CSTATE = helicopterD2_P.Integrator_IC;
}

/* Model terminate function */
void helicopterD2_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterD2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopterD2_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopterD2_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopterD2_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopterD2_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD2_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD2_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopterD2_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopterD2_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD2_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD2_P.HILInitialize_POFinal;
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
      result = hil_write(helicopterD2_DW.HILInitialize_Card
                         , helicopterD2_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopterD2_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopterD2_DW.HILInitialize_AOVoltages[0]
                         , &helicopterD2_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopterD2_DW.HILInitialize_Card,
            helicopterD2_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopterD2_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopterD2_DW.HILInitialize_Card,
            helicopterD2_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopterD2_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD2_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopterD2_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopterD2_DW.HILInitialize_Card);
    hil_close(helicopterD2_DW.HILInitialize_Card);
    helicopterD2_DW.HILInitialize_Card = NULL;
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
  helicopterD2_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopterD2_update();
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
  helicopterD2_initialize();
}

void MdlTerminate(void)
{
  helicopterD2_terminate();
}

/* Registration function */
RT_MODEL_helicopterD2_T *helicopterD2(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopterD2_P.Integrator_UpperSat = rtInf;
  helicopterD2_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopterD2_M, 0,
                sizeof(RT_MODEL_helicopterD2_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopterD2_M->solverInfo,
                          &helicopterD2_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopterD2_M->solverInfo, &rtmGetTPtr(helicopterD2_M));
    rtsiSetStepSizePtr(&helicopterD2_M->solverInfo,
                       &helicopterD2_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopterD2_M->solverInfo, &helicopterD2_M->derivs);
    rtsiSetContStatesPtr(&helicopterD2_M->solverInfo, (real_T **)
                         &helicopterD2_M->contStates);
    rtsiSetNumContStatesPtr(&helicopterD2_M->solverInfo,
      &helicopterD2_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopterD2_M->solverInfo,
      &helicopterD2_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopterD2_M->solverInfo,
      &helicopterD2_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopterD2_M->solverInfo,
      &helicopterD2_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopterD2_M->solverInfo, (&rtmGetErrorStatus
      (helicopterD2_M)));
    rtsiSetRTModelPtr(&helicopterD2_M->solverInfo, helicopterD2_M);
  }

  rtsiSetSimTimeStep(&helicopterD2_M->solverInfo, MAJOR_TIME_STEP);
  helicopterD2_M->intgData.f[0] = helicopterD2_M->odeF[0];
  helicopterD2_M->contStates = ((real_T *) &helicopterD2_X);
  rtsiSetSolverData(&helicopterD2_M->solverInfo, (void *)
                    &helicopterD2_M->intgData);
  rtsiSetSolverName(&helicopterD2_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopterD2_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopterD2_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopterD2_M->Timing.sampleTimes =
      (&helicopterD2_M->Timing.sampleTimesArray[0]);
    helicopterD2_M->Timing.offsetTimes =
      (&helicopterD2_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopterD2_M->Timing.sampleTimes[0] = (0.0);
    helicopterD2_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopterD2_M->Timing.offsetTimes[0] = (0.0);
    helicopterD2_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopterD2_M, &helicopterD2_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopterD2_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopterD2_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopterD2_M, 20.0);
  helicopterD2_M->Timing.stepSize0 = 0.002;
  helicopterD2_M->Timing.stepSize1 = 0.002;
  helicopterD2_M->solverInfoPtr = (&helicopterD2_M->solverInfo);
  helicopterD2_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterD2_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterD2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterD2_M->blockIO = ((void *) &helicopterD2_B);

  {
    helicopterD2_B.TravelCounttorad = 0.0;
    helicopterD2_B.Gain = 0.0;
    helicopterD2_B.PitchCounttorad = 0.0;
    helicopterD2_B.Gain_i = 0.0;
    helicopterD2_B.ElevationCounttorad = 0.0;
    helicopterD2_B.Sum = 0.0;
    helicopterD2_B.FrontmotorSaturation = 0.0;
    helicopterD2_B.BackmotorSaturation = 0.0;
    helicopterD2_B.In1 = 0.0;
  }

  /* parameters */
  helicopterD2_M->defaultParam = ((real_T *)&helicopterD2_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopterD2_X;
    helicopterD2_M->contStates = (x);
    (void) memset((void *)&helicopterD2_X, 0,
                  sizeof(X_helicopterD2_T));
  }

  /* states (dwork) */
  helicopterD2_M->dwork = ((void *) &helicopterD2_DW);
  (void) memset((void *)&helicopterD2_DW, 0,
                sizeof(DW_helicopterD2_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD2_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopterD2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterD2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* Initialize Sizes */
  helicopterD2_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterD2_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterD2_M->Sizes.numY = (0);    /* Number of model outputs */
  helicopterD2_M->Sizes.numU = (0);    /* Number of model inputs */
  helicopterD2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterD2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterD2_M->Sizes.numBlocks = (46);/* Number of blocks */
  helicopterD2_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  helicopterD2_M->Sizes.numBlockPrms = (143);/* Sum of parameter "widths" */
  return helicopterD2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

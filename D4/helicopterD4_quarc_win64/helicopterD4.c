/*
 * helicopterD4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD4".
 *
 * Model version              : 11.8
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Mar  4 17:13:47 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterD4.h"
#include "helicopterD4_private.h"

/* Block signals (default storage) */
B_helicopterD4_T helicopterD4_B;

/* Continuous states */
X_helicopterD4_T helicopterD4_X;

/* Block states (default storage) */
DW_helicopterD4_T helicopterD4_DW;

/* Real-time model */
static RT_MODEL_helicopterD4_T helicopterD4_M_;
RT_MODEL_helicopterD4_T *const helicopterD4_M = &helicopterD4_M_;

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
  helicopterD4_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void helicopterD4_output(void)
{
  /* local block i/o variables */
  real_T rtb_u[2];
  real_T rtb_Sum[6];
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Gain1[6];
  real_T rtb_u_b[2];
  real_T rtb_Clock;
  real_T rtb_Frontgain;
  real_T rtb_Sum_b;
  int32_T i;
  int32_T i_0;
  int8_T rtAction;
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    /* set solver stop time */
    if (!(helicopterD4_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&helicopterD4_M->solverInfo,
                            ((helicopterD4_M->Timing.clockTickH0 + 1) *
        helicopterD4_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&helicopterD4_M->solverInfo,
                            ((helicopterD4_M->Timing.clockTick0 + 1) *
        helicopterD4_M->Timing.stepSize0 + helicopterD4_M->Timing.clockTickH0 *
        helicopterD4_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(helicopterD4_M)) {
    helicopterD4_M->Timing.t[0] = rtsiGetT(&helicopterD4_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

    /* S-Function Block: helicopterD4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(helicopterD4_DW.HILReadEncoderTimebase_Task,
        1, &helicopterD4_DW.HILReadEncoderTimebase_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase_o1 =
          helicopterD4_DW.HILReadEncoderTimebase_Buffer[0];
        rtb_HILReadEncoderTimebase_o2 =
          helicopterD4_DW.HILReadEncoderTimebase_Buffer[1];
        rtb_HILReadEncoderTimebase_o3 =
          helicopterD4_DW.HILReadEncoderTimebase_Buffer[2];
      }
    }

    /* Gain: '<S4>/Travel: Count to rad' incorporates:
     *  Gain: '<S4>/Travel_gain'
     */
    helicopterD4_B.TravelCounttorad = helicopterD4_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopterD4_P.TravelCounttorad_Gain;

    /* Sum: '<Root>/Sum4' incorporates:
     *  Constant: '<Root>/Pi'
     *  Gain: '<S13>/Gain'
     */
    helicopterD4_B.Sum4 = helicopterD4_P.Gain_Gain *
      helicopterD4_B.TravelCounttorad + helicopterD4_P.Pi_Value;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopterD4_B.PitchCounttorad = helicopterD4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopterD4_B.Gain = helicopterD4_P.Gain_Gain_a *
      helicopterD4_B.PitchCounttorad;

    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopterD4_B.ElevationCounttorad = helicopterD4_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterD4_P.ElevationCounttorad_Gain;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     *  Gain: '<S8>/Gain'
     */
    helicopterD4_B.Sum = helicopterD4_P.Gain_Gain_lv *
      helicopterD4_B.ElevationCounttorad +
      helicopterD4_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S2>/Gain1' incorporates:
   *  Gain: '<S11>/Gain'
   *  Gain: '<S14>/Gain'
   *  Gain: '<S9>/Gain'
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  rtb_Gain1[0] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Sum4;
  rtb_Gain1[1] = (helicopterD4_P.TravelTransferFcn_C *
                  helicopterD4_X.TravelTransferFcn_CSTATE +
                  helicopterD4_P.TravelTransferFcn_D *
                  helicopterD4_B.TravelCounttorad) * helicopterD4_P.Gain_Gain_l *
    helicopterD4_P.Gain1_Gain;
  rtb_Gain1[2] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Gain;
  rtb_Gain1[3] = (helicopterD4_P.PitchTransferFcn_C *
                  helicopterD4_X.PitchTransferFcn_CSTATE +
                  helicopterD4_P.PitchTransferFcn_D *
                  helicopterD4_B.PitchCounttorad) * helicopterD4_P.Gain_Gain_ae *
    helicopterD4_P.Gain1_Gain;
  rtb_Gain1[4] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Sum;
  rtb_Gain1[5] = (helicopterD4_P.ElevationTransferFcn_C *
                  helicopterD4_X.ElevationTransferFcn_CSTATE +
                  helicopterD4_P.ElevationTransferFcn_D *
                  helicopterD4_B.ElevationCounttorad) *
    helicopterD4_P.Gain_Gain_n * helicopterD4_P.Gain1_Gain;

  /* FromWorkspace: '<S6>/From Workspace1' */
  {
    real_T *pDataValues = (real_T *)
      helicopterD4_DW.FromWorkspace1_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      helicopterD4_DW.FromWorkspace1_PWORK.TimePtr;
    int_T currTimeIndex = helicopterD4_DW.FromWorkspace1_IWORK.PrevIndex;
    real_T t = helicopterD4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
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

    helicopterD4_DW.FromWorkspace1_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&rtb_Sum[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
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
          for (elIdx = 0; elIdx < 6; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_Sum[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  for (i = 0; i < 6; i++) {
    /* Sum: '<S6>/Sum' */
    rtb_Sum[i] = rtb_Gain1[i] - rtb_Sum[i];
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *) helicopterD4_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *) helicopterD4_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = helicopterD4_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = helicopterD4_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[80]) {
      currTimeIndex = 79;
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

    helicopterD4_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_u[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 2; ++elIdx) {
              (&rtb_u[0])[elIdx] = pDataValues[currTimeIndex + 1];
              pDataValues += 81;
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
          for (elIdx = 0; elIdx < 2; ++elIdx) {
            d1 = pDataValues[TimeIndex];
            d2 = pDataValues[TimeIndex + 1];
            (&rtb_u[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1, f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<S6>/Gain'
   */
  for (i = 0; i < 2; i++) {
    rtb_Frontgain = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Frontgain += helicopterD4_P.K[(i_0 << 1) + i] * rtb_Sum[i_0];
    }

    rtb_u_b[i] = rtb_u[i] - rtb_Frontgain;
  }

  /* End of Sum: '<Root>/Sum3' */

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Frontgain = ((rtb_u_b[0] - rtb_Gain1[2]) * helicopterD4_P.K_pp -
                   helicopterD4_P.K_pd * rtb_Gain1[3]) + helicopterD4_P.Vd_ff;

  /* Integrator: '<S3>/Integrator' */
  /* Limited  Integrator  */
  if (helicopterD4_X.Integrator_CSTATE >= helicopterD4_P.Integrator_UpperSat) {
    helicopterD4_X.Integrator_CSTATE = helicopterD4_P.Integrator_UpperSat;
  } else {
    if (helicopterD4_X.Integrator_CSTATE <= helicopterD4_P.Integrator_LowerSat)
    {
      helicopterD4_X.Integrator_CSTATE = helicopterD4_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S3>/Sum' */
  rtb_Sum_b = rtb_u_b[1] - rtb_Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Clock = ((helicopterD4_P.K_ep * rtb_Sum_b +
                helicopterD4_X.Integrator_CSTATE) - helicopterD4_P.K_ed *
               rtb_Gain1[5]) + helicopterD4_P.Vs_ff;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    rtAction = (int8_T)!(helicopterD4_M->Timing.t[0] >= 2.0);
    helicopterD4_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterD4_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopterD4_B.In1 = helicopterD4_P.K_ei * rtb_Sum_b;

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Sum_b = (rtb_Frontgain + rtb_Clock) * helicopterD4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Sum_b > helicopterD4_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD4_B.FrontmotorSaturation =
      helicopterD4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Sum_b < helicopterD4_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD4_B.FrontmotorSaturation =
      helicopterD4_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD4_B.FrontmotorSaturation = rtb_Sum_b;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Sum_b = (rtb_Clock - rtb_Frontgain) * helicopterD4_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Sum_b > helicopterD4_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD4_B.BackmotorSaturation =
      helicopterD4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Sum_b < helicopterD4_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD4_B.BackmotorSaturation =
      helicopterD4_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD4_B.BackmotorSaturation = rtb_Sum_b;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    /* S-Function (hil_write_analog_block): '<S4>/HIL Write Analog' */

    /* S-Function Block: helicopterD4/Helicopter_interface/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      helicopterD4_DW.HILWriteAnalog_Buffer[0] =
        helicopterD4_B.FrontmotorSaturation;
      helicopterD4_DW.HILWriteAnalog_Buffer[1] =
        helicopterD4_B.BackmotorSaturation;
      result = hil_write_analog(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILWriteAnalog_channels, 2,
        &helicopterD4_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
      }
    }
  }
}

/* Model update function */
void helicopterD4_update(void)
{
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    rt_ertODEUpdateContinuousStates(&helicopterD4_M->solverInfo);
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
  if (!(++helicopterD4_M->Timing.clockTick0)) {
    ++helicopterD4_M->Timing.clockTickH0;
  }

  helicopterD4_M->Timing.t[0] = rtsiGetSolverStopTime
    (&helicopterD4_M->solverInfo);

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
    if (!(++helicopterD4_M->Timing.clockTick1)) {
      ++helicopterD4_M->Timing.clockTickH1;
    }

    helicopterD4_M->Timing.t[1] = helicopterD4_M->Timing.clockTick1 *
      helicopterD4_M->Timing.stepSize1 + helicopterD4_M->Timing.clockTickH1 *
      helicopterD4_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void helicopterD4_derivatives(void)
{
  XDot_helicopterD4_T *_rtXdot;
  boolean_T lsat;
  boolean_T usat;
  _rtXdot = ((XDot_helicopterD4_T *) helicopterD4_M->derivs);

  /* Derivatives for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD4_P.TravelTransferFcn_A *
    helicopterD4_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD4_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD4_P.PitchTransferFcn_A *
    helicopterD4_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD4_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD4_P.ElevationTransferFcn_A *
    helicopterD4_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD4_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S3>/Integrator' */
  lsat = (helicopterD4_X.Integrator_CSTATE <= helicopterD4_P.Integrator_LowerSat);
  usat = (helicopterD4_X.Integrator_CSTATE >= helicopterD4_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopterD4_B.In1 > 0.0)) || (usat &&
       (helicopterD4_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopterD4_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S3>/Integrator' */
}

/* Model initialize function */
void helicopterD4_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterD4/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q8_usb", "0", &helicopterD4_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(helicopterD4_DW.HILInitialize_Card,
      "update_rate=normal;decimation=1", 32);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(helicopterD4_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
      return;
    }

    if ((helicopterD4_P.HILInitialize_AIPStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_AIPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AIMinimums = &helicopterD4_DW.HILInitialize_AIMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMinimums[i1] = (helicopterD4_P.HILInitialize_AILow);
        }
      }

      {
        int_T i1;
        real_T *dw_AIMaximums = &helicopterD4_DW.HILInitialize_AIMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AIMaximums[i1] = helicopterD4_P.HILInitialize_AIHigh;
        }
      }

      result = hil_set_analog_input_ranges(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_AIChannels, 8U,
        &helicopterD4_DW.HILInitialize_AIMinimums[0],
        &helicopterD4_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD4_P.HILInitialize_AOPStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_AOPEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOMinimums = &helicopterD4_DW.HILInitialize_AOMinimums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMinimums[i1] = (helicopterD4_P.HILInitialize_AOLow);
        }
      }

      {
        int_T i1;
        real_T *dw_AOMaximums = &helicopterD4_DW.HILInitialize_AOMaximums[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOMaximums[i1] = helicopterD4_P.HILInitialize_AOHigh;
        }
      }

      result = hil_set_analog_output_ranges(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_AOChannels, 8U,
        &helicopterD4_DW.HILInitialize_AOMinimums[0],
        &helicopterD4_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD4_P.HILInitialize_AOStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_AOEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD4_P.HILInitialize_AOInitial;
        }
      }

      result = hil_write_analog(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_AOChannels, 8U,
        &helicopterD4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if (helicopterD4_P.HILInitialize_AOReset) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD4_P.HILInitialize_AOWatchdog;
        }
      }

      result = hil_watchdog_set_analog_expiration_state
        (helicopterD4_DW.HILInitialize_Card,
         helicopterD4_P.HILInitialize_AOChannels, 8U,
         &helicopterD4_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD4_P.HILInitialize_EIPStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_EIPEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_QuadratureModes =
          &helicopterD4_DW.HILInitialize_QuadratureModes[0];
        for (i1=0; i1 < 8; i1++) {
          dw_QuadratureModes[i1] = helicopterD4_P.HILInitialize_EIQuadrature;
        }
      }

      result = hil_set_encoder_quadrature_mode
        (helicopterD4_DW.HILInitialize_Card,
         helicopterD4_P.HILInitialize_EIChannels, 8U, (t_encoder_quadrature_mode
          *) &helicopterD4_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD4_P.HILInitialize_EIStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_EIEnter && is_switching)) {
      {
        int_T i1;
        int32_T *dw_InitialEICounts =
          &helicopterD4_DW.HILInitialize_InitialEICounts[0];
        for (i1=0; i1 < 8; i1++) {
          dw_InitialEICounts[i1] = helicopterD4_P.HILInitialize_EIInitial;
        }
      }

      result = hil_set_encoder_counts(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_EIChannels, 8U,
        &helicopterD4_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD4_P.HILInitialize_POPStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_POPEnter && is_switching)) {
      uint32_T num_duty_cycle_modes = 0;
      uint32_T num_frequency_modes = 0;

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopterD4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterD4_P.HILInitialize_POModes;
        }
      }

      result = hil_set_pwm_mode(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_POChannels, 8U, (t_pwm_mode *)
        &helicopterD4_DW.HILInitialize_POModeValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        const uint32_T *p_HILInitialize_POChannels =
          helicopterD4_P.HILInitialize_POChannels;
        int32_T *dw_POModeValues = &helicopterD4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          if (dw_POModeValues[i1] == PWM_DUTY_CYCLE_MODE || dw_POModeValues[i1] ==
              PWM_ONE_SHOT_MODE || dw_POModeValues[i1] == PWM_TIME_MODE ||
              dw_POModeValues[i1] == PWM_RAW_MODE) {
            helicopterD4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes] =
              (p_HILInitialize_POChannels[i1]);
            helicopterD4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes] =
              helicopterD4_P.HILInitialize_POFrequency;
            num_duty_cycle_modes++;
          } else {
            helicopterD4_DW.HILInitialize_POSortedChans[7U - num_frequency_modes]
              = (p_HILInitialize_POChannels[i1]);
            helicopterD4_DW.HILInitialize_POSortedFreqs[7U - num_frequency_modes]
              = helicopterD4_P.HILInitialize_POFrequency;
            num_frequency_modes++;
          }
        }
      }

      if (num_duty_cycle_modes > 0) {
        result = hil_set_pwm_frequency(helicopterD4_DW.HILInitialize_Card,
          &helicopterD4_DW.HILInitialize_POSortedChans[0], num_duty_cycle_modes,
          &helicopterD4_DW.HILInitialize_POSortedFreqs[0]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
          return;
        }
      }

      if (num_frequency_modes > 0) {
        result = hil_set_pwm_duty_cycle(helicopterD4_DW.HILInitialize_Card,
          &helicopterD4_DW.HILInitialize_POSortedChans[num_duty_cycle_modes],
          num_frequency_modes,
          &helicopterD4_DW.HILInitialize_POSortedFreqs[num_duty_cycle_modes]);
        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
          return;
        }
      }

      {
        int_T i1;
        int32_T *dw_POModeValues = &helicopterD4_DW.HILInitialize_POModeValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POModeValues[i1] = helicopterD4_P.HILInitialize_POConfiguration;
        }
      }

      {
        int_T i1;
        int32_T *dw_POAlignValues =
          &helicopterD4_DW.HILInitialize_POAlignValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POAlignValues[i1] = helicopterD4_P.HILInitialize_POAlignment;
        }
      }

      {
        int_T i1;
        int32_T *dw_POPolarityVals =
          &helicopterD4_DW.HILInitialize_POPolarityVals[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POPolarityVals[i1] = helicopterD4_P.HILInitialize_POPolarity;
        }
      }

      result = hil_set_pwm_configuration(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_POChannels, 8U,
        (t_pwm_configuration *) &helicopterD4_DW.HILInitialize_POModeValues[0],
        (t_pwm_alignment *) &helicopterD4_DW.HILInitialize_POAlignValues[0],
        (t_pwm_polarity *) &helicopterD4_DW.HILInitialize_POPolarityVals[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }

      {
        int_T i1;
        real_T *dw_POSortedFreqs = &helicopterD4_DW.HILInitialize_POSortedFreqs
          [0];
        for (i1=0; i1 < 8; i1++) {
          dw_POSortedFreqs[i1] = helicopterD4_P.HILInitialize_POLeading;
        }
      }

      {
        int_T i1;
        real_T *dw_POValues = &helicopterD4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD4_P.HILInitialize_POTrailing;
        }
      }

      result = hil_set_pwm_deadband(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_POChannels, 8U,
        &helicopterD4_DW.HILInitialize_POSortedFreqs[0],
        &helicopterD4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if ((helicopterD4_P.HILInitialize_POStart && !is_switching) ||
        (helicopterD4_P.HILInitialize_POEnter && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD4_P.HILInitialize_POInitial;
        }
      }

      result = hil_write_pwm(helicopterD4_DW.HILInitialize_Card,
        helicopterD4_P.HILInitialize_POChannels, 8U,
        &helicopterD4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }

    if (helicopterD4_P.HILInitialize_POReset) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD4_P.HILInitialize_POWatchdog;
        }
      }

      result = hil_watchdog_set_pwm_expiration_state
        (helicopterD4_DW.HILInitialize_Card,
         helicopterD4_P.HILInitialize_POChannels, 8U,
         &helicopterD4_DW.HILInitialize_POValues[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S4>/HIL Read Encoder Timebase' */

  /* S-Function Block: helicopterD4/Helicopter_interface/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(helicopterD4_DW.HILInitialize_Card,
      helicopterD4_P.HILReadEncoderTimebase_SamplesI,
      helicopterD4_P.HILReadEncoderTimebase_Channels, 3,
      &helicopterD4_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (helicopterD4_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (helicopterD4_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
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
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, -1.9795904404546385E-16, -1.4566701796728242E-18,
      -2.292861843145929E-11, -0.20843121089757738, -0.13097701940556955,
      -0.11322642519015726, -0.12303802272039226, -0.12008524516858664,
      -0.12144115635781001, -0.12101533497284854, -0.12111965620597215,
      -0.12112687317616318, -0.12108110016326475, -0.1211943722549341,
      -0.12088242185761305, -0.1216740160086224, -0.1198978643597856,
      -0.12342197210114542, -0.11727400975956773, -0.12608711064777037,
      -0.11748805630618271, -0.11290222652754912, -0.1654626335944813,
      0.013485705494639918, 0.028141775709940357, -0.14500407838053603,
      -0.20284371193365172, -0.19796868449878421, -0.19745304101134697,
      -0.19746869160249297, -0.19746220539605783, -0.19746552428085154,
      -0.1974675213875747, -0.19746576567526555, -0.19746243723892057,
      -0.1974712980510909, -0.19749155580645561, -0.19733147975737481,
      -0.19919037658502975, -0.21006576774295632, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, -8.546297219230822E-19, -2.2928420165805217E-11,
      -0.20843121091063824, -0.1309770194063028, -0.11322642519580767,
      -0.12303802272376857, -0.12008524517232941, -0.12144115636202249,
      -0.12101533497651568, -0.12111965621006804, -0.12112687318005448,
      -0.12108110016713314, -0.12119437225910007, -0.12088242186109736,
      -0.12167401601333679, -0.11989786436255459, -0.12342197210660169,
      -0.11727400976185368, -0.12608711065288264, -0.11748805631011305,
      -0.11290222653010945, -0.16546263360080934, 0.013485705493538539,
      0.02814177571152655, -0.14500407838267956, -0.20284371193932837,
      -0.19796868450618188, -0.1974530410197943, -0.19746869161116634,
      -0.19746220540466758, -0.19746552428941749, -0.19746752139613286,
      -0.1974657656838297, -0.1974624372475321, -0.19747129805973698,
      -0.19749155581490122, -0.1973314797652784, -0.19919037659253322,
      -0.21006576775115893, 0.014621809939376094, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 4.0511979374524061E-11, 0.3682780485460932,
      0.23142388750268433, 0.20006028239108423, 0.21739643839575609,
      0.21217916239722542, 0.21457492800758751, 0.21382254227523498,
      0.21400686793576429, 0.21401961963192315, 0.21393874308845548,
      0.21413888406070097, 0.21358769749029666, 0.21498636877960614,
      0.21184807839418476, 0.21807484030277594, 0.20721197784077908,
      0.22278388564327278, 0.2075901776600298, 0.19948745429262424,
      0.2923566750900522, -0.02382795397721468, -0.049723830688560726,
      0.25620836140408659, 0.35840547133657652, 0.34979176333981693,
      0.3488806705371329, 0.34890832363855417, 0.34889686313075652,
      0.34890272728306365, 0.34890625597991681, 0.34890315380393527,
      0.34889727277496652, 0.348912928984217, 0.34894872250265768,
      0.34866588340524685, 0.35195037660863354, 0.37116615439732575,
      -0.025835342054457523, -0.0041991051390272965, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.36827804856890756, 0.23142388751771792,
      0.20006028235947584, 0.21739643843239795, 0.2121791623695117,
      0.21457492802827785, 0.21382254226491143, 0.2140068679428524,
      0.21401961963049299, 0.21393874309088098, 0.21413888406068582,
      0.21358769749395287, 0.21498636877581645, 0.21184807840435357,
      0.21807484028978411, 0.20721197786176387, 0.22278388562085996,
      0.20759017768359789, 0.1994874542797338, 0.292356675092177,
      -0.023827953965369544, -0.04972383069076175, 0.25620836139659764,
      0.35840547132808376, 0.34979176333506318, 0.34888067053509719,
      0.34890832363746788, 0.34889686312960339, 0.34890272728175903,
      0.34890625597860575, 0.34890315380260617, 0.34889727277358534,
      0.34891292898299753, 0.34894872250180231, 0.34866588340424409,
      0.35195037660646872, 0.37116615439314865, -0.025835342050184777,
      -0.0041991051342856051, 0.00064997124505583983, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.2010659729211185E-6, 0.0088865766534252637,
      0.0085971902684450641, 0.0086247733607704487, 0.00854172391679641,
      0.00856972800684799, 0.008576960066104965, 0.0085555302559222682,
      0.0085767578508994368, 0.0085656588804670659, 0.0085672492610401347,
      0.0085700596776940516, 0.0085672348629101079, 0.0085685396482515757,
      0.0085682563846069121, 0.0085690629739935027, 0.008567251196905849,
      0.0085647299708305688, 0.0085677983906570568, 0.0085967775337243077,
      0.0088630491170667344, 3.5254105731818735E-6, 4.2568664717412155E-7,
      2.0002278917112768E-6, 0.00887132376821229, 0.0086234750294851212,
      0.0086179878154549472, 0.008582537645210055, 0.0086079270488449225,
      0.0086034921032571918, 0.0085968571352672881, 0.0086052570426431232,
      0.0086036283349965135, 0.0085934804897761369, 0.0086129808264852,
      0.008594297562102067, 0.0085840122825159241, 0.0086282502716861515,
      0.0085754220576795149, 0.00900267719152593, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.00888657665138386, 0.0085971902662605234,
      0.0086247733616985275, 0.00854172392149928, 0.0085697280100080434,
      0.0085769600679378322, 0.008555530258526416, 0.0085767578532831255,
      0.0085656588827730754, 0.0085672492636339071, 0.0085700596801179616,
      0.0085672348653197047, 0.0085685396507999938, 0.0085682563871029467,
      0.0085690629762221748, 0.0085672511991706762, 0.00856472997316588,
      0.00856779839427155, 0.0085967775393894982, 0.0088630491234196074,
      3.5254157381147178E-6, -1.1640060818629687E-6, 1.0066675834669143E-6,
      0.0088713237683577546, 0.0086234750307906, 0.00861798781388599,
      0.0085825376439212977, 0.0086079270475035424, 0.0086034921012516884,
      0.00859685713362968, 0.0086052570408093731, 0.0086036283333808024,
      0.0085934804880615917, 0.0086129808239832784, 0.00859429756174507,
      0.0085840122803508313, 0.00862825027108604, 0.00857542206156204,
      0.0090026771912091828, -0.0040363574828763066, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0
    } ;

    helicopterD4_DW.FromWorkspace1_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD4_DW.FromWorkspace1_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD4_DW.FromWorkspace1_IWORK.PrevIndex = 0;
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
      19.75, 20.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.11366606437339058,
      0.48062495756467521, 0.68716270207211871, 0.52081075630521789,
      0.5070992764465565, 0.51937789288615277, 0.5165903609087078,
      0.51820703297442439, 0.51766338925975552, 0.51783692156562711,
      0.51782158234501008, 0.51779296534578745, 0.51781236546699783,
      0.51784664995878438, 0.51768017203561612, 0.5181077706481787,
      0.517070829787569, 0.51882067102376928, 0.51500984056635146,
      0.51947644633104584, 0.51697389761718848, 0.25053430936052029, 0.0,
      0.34557109905075378, 0.762397083662333, 0.85474220545493484,
      0.84512470703327347, 0.84424080270614965, 0.84425753183342089,
      0.84425367615419356, 0.84426250361904831, 0.84426077032126479,
      0.84425596583199525, 0.84427852797362757, 0.84424665874155891,
      0.8449819190657748, 0.85427931247276312, 0.75638334382078531,
      0.34116419868354914, -0.030300406016317047, -0.030300406016317047, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.013885276015632744,
      0.035650752484945036, 0.043855760694400073, 0.043505567302319012,
      0.043369283182543426, 0.043367544049240966, 0.043380144206239556,
      0.04336696985975539, 0.043381266894417236, 0.0433772320334237,
      0.043374500291065578, 0.043378702939482344, 0.043376490046568489,
      0.04337648459603332, 0.043378341517523122, 0.043377243824848574,
      0.0433695815561204, 0.0433662611219766, 0.043416690864314565,
      0.043908256497949417, 0.030759908808160753, 0.0088700438993651945, 0.0,
      0.013864385742324683, 0.035654489385356015, 0.043895617304795437,
      0.043578659631194623, 0.04352421793644605, 0.043545311671107811,
      0.043549246571854106, 0.043541349062689666, 0.043553169006850745,
      0.043541641137818193, 0.043545112091276796, 0.043554522488332192,
      0.043511243919353591, 0.043535969308926462, 0.043553734932895175,
      0.044133488539162873, 0.024775306468143566, 0.024775306468143566, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0 } ;

    helicopterD4_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD4_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD4_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S3>/If' */
  helicopterD4_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S4>/Travel: Transfer Fcn' */
  helicopterD4_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Pitch: Transfer Fcn' */
  helicopterD4_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S4>/Elevation: Transfer Fcn' */
  helicopterD4_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S3>/Integrator' */
  helicopterD4_X.Integrator_CSTATE = helicopterD4_P.Integrator_IC;
}

/* Model terminate function */
void helicopterD4_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: helicopterD4/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_pwm_outputs = 0;
    hil_task_stop_all(helicopterD4_DW.HILInitialize_Card);
    hil_monitor_stop_all(helicopterD4_DW.HILInitialize_Card);
    is_switching = false;
    if ((helicopterD4_P.HILInitialize_AOTerminate && !is_switching) ||
        (helicopterD4_P.HILInitialize_AOExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_AOVoltages = &helicopterD4_DW.HILInitialize_AOVoltages[0];
        for (i1=0; i1 < 8; i1++) {
          dw_AOVoltages[i1] = helicopterD4_P.HILInitialize_AOFinal;
        }
      }

      num_final_analog_outputs = 8U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((helicopterD4_P.HILInitialize_POTerminate && !is_switching) ||
        (helicopterD4_P.HILInitialize_POExit && is_switching)) {
      {
        int_T i1;
        real_T *dw_POValues = &helicopterD4_DW.HILInitialize_POValues[0];
        for (i1=0; i1 < 8; i1++) {
          dw_POValues[i1] = helicopterD4_P.HILInitialize_POFinal;
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
      result = hil_write(helicopterD4_DW.HILInitialize_Card
                         , helicopterD4_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , helicopterD4_P.HILInitialize_POChannels,
                         num_final_pwm_outputs
                         , NULL, 0
                         , NULL, 0
                         , &helicopterD4_DW.HILInitialize_AOVoltages[0]
                         , &helicopterD4_DW.HILInitialize_POValues[0]
                         , (t_boolean *) NULL
                         , NULL
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(helicopterD4_DW.HILInitialize_Card,
            helicopterD4_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &helicopterD4_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_pwm_outputs > 0) {
          local_result = hil_write_pwm(helicopterD4_DW.HILInitialize_Card,
            helicopterD4_P.HILInitialize_POChannels, num_final_pwm_outputs,
            &helicopterD4_DW.HILInitialize_POValues[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(helicopterD4_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(helicopterD4_DW.HILInitialize_Card);
    hil_monitor_delete_all(helicopterD4_DW.HILInitialize_Card);
    hil_close(helicopterD4_DW.HILInitialize_Card);
    helicopterD4_DW.HILInitialize_Card = NULL;
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
  helicopterD4_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  helicopterD4_update();
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
  helicopterD4_initialize();
}

void MdlTerminate(void)
{
  helicopterD4_terminate();
}

/* Registration function */
RT_MODEL_helicopterD4_T *helicopterD4(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* non-finite (run-time) assignments */
  helicopterD4_P.Integrator_UpperSat = rtInf;
  helicopterD4_P.Integrator_LowerSat = rtMinusInf;

  /* initialize real-time model */
  (void) memset((void *)helicopterD4_M, 0,
                sizeof(RT_MODEL_helicopterD4_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&helicopterD4_M->solverInfo,
                          &helicopterD4_M->Timing.simTimeStep);
    rtsiSetTPtr(&helicopterD4_M->solverInfo, &rtmGetTPtr(helicopterD4_M));
    rtsiSetStepSizePtr(&helicopterD4_M->solverInfo,
                       &helicopterD4_M->Timing.stepSize0);
    rtsiSetdXPtr(&helicopterD4_M->solverInfo, &helicopterD4_M->derivs);
    rtsiSetContStatesPtr(&helicopterD4_M->solverInfo, (real_T **)
                         &helicopterD4_M->contStates);
    rtsiSetNumContStatesPtr(&helicopterD4_M->solverInfo,
      &helicopterD4_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&helicopterD4_M->solverInfo,
      &helicopterD4_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&helicopterD4_M->solverInfo,
      &helicopterD4_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&helicopterD4_M->solverInfo,
      &helicopterD4_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&helicopterD4_M->solverInfo, (&rtmGetErrorStatus
      (helicopterD4_M)));
    rtsiSetRTModelPtr(&helicopterD4_M->solverInfo, helicopterD4_M);
  }

  rtsiSetSimTimeStep(&helicopterD4_M->solverInfo, MAJOR_TIME_STEP);
  helicopterD4_M->intgData.f[0] = helicopterD4_M->odeF[0];
  helicopterD4_M->contStates = ((real_T *) &helicopterD4_X);
  rtsiSetSolverData(&helicopterD4_M->solverInfo, (void *)
                    &helicopterD4_M->intgData);
  rtsiSetSolverName(&helicopterD4_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = helicopterD4_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    helicopterD4_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    helicopterD4_M->Timing.sampleTimes =
      (&helicopterD4_M->Timing.sampleTimesArray[0]);
    helicopterD4_M->Timing.offsetTimes =
      (&helicopterD4_M->Timing.offsetTimesArray[0]);

    /* task periods */
    helicopterD4_M->Timing.sampleTimes[0] = (0.0);
    helicopterD4_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    helicopterD4_M->Timing.offsetTimes[0] = (0.0);
    helicopterD4_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(helicopterD4_M, &helicopterD4_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = helicopterD4_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    helicopterD4_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(helicopterD4_M, 20.0);
  helicopterD4_M->Timing.stepSize0 = 0.002;
  helicopterD4_M->Timing.stepSize1 = 0.002;
  helicopterD4_M->solverInfoPtr = (&helicopterD4_M->solverInfo);
  helicopterD4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterD4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterD4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterD4_M->blockIO = ((void *) &helicopterD4_B);

  {
    helicopterD4_B.TravelCounttorad = 0.0;
    helicopterD4_B.Sum4 = 0.0;
    helicopterD4_B.PitchCounttorad = 0.0;
    helicopterD4_B.Gain = 0.0;
    helicopterD4_B.ElevationCounttorad = 0.0;
    helicopterD4_B.Sum = 0.0;
    helicopterD4_B.FrontmotorSaturation = 0.0;
    helicopterD4_B.BackmotorSaturation = 0.0;
    helicopterD4_B.In1 = 0.0;
  }

  /* parameters */
  helicopterD4_M->defaultParam = ((real_T *)&helicopterD4_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &helicopterD4_X;
    helicopterD4_M->contStates = (x);
    (void) memset((void *)&helicopterD4_X, 0,
                  sizeof(X_helicopterD4_T));
  }

  /* states (dwork) */
  helicopterD4_M->dwork = ((void *) &helicopterD4_DW);
  (void) memset((void *)&helicopterD4_DW, 0,
                sizeof(DW_helicopterD4_T));

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_AIMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_AIMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_AOMinimums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_AOMaximums[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_AOVoltages[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_FilterFrequency[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_POSortedFreqs[i] = 0.0;
    }
  }

  {
    int32_T i;
    for (i = 0; i < 8; i++) {
      helicopterD4_DW.HILInitialize_POValues[i] = 0.0;
    }
  }

  helicopterD4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterD4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* Initialize Sizes */
  helicopterD4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterD4_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterD4_M->Sizes.numY = (0);    /* Number of model outputs */
  helicopterD4_M->Sizes.numU = (0);    /* Number of model inputs */
  helicopterD4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterD4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterD4_M->Sizes.numBlocks = (51);/* Number of blocks */
  helicopterD4_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  helicopterD4_M->Sizes.numBlockPrms = (155);/* Sum of parameter "widths" */
  return helicopterD4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

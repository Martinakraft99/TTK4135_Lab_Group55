/*
 * helicopterD2.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD2".
 *
 * Model version              : 11.8
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Apr  8 17:49:59 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterD2.h"
#include "helicopterD2_private.h"
#include "helicopterD2_dt.h"

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
 * Writes out MAT-file header.  Returns success or failure.
 * Returns:
 *      0 - success
 *      1 - failure
 */
int_T rt_WriteMat4FileHeader(FILE *fp, int32_T m, int32_T n, const char *name)
{
  typedef enum { ELITTLE_ENDIAN, EBIG_ENDIAN } ByteOrder;

  int16_T one = 1;
  ByteOrder byteOrder = (*((int8_T *)&one)==1) ? ELITTLE_ENDIAN : EBIG_ENDIAN;
  int32_T type = (byteOrder == ELITTLE_ENDIAN) ? 0: 1000;
  int32_T imagf = 0;
  int32_T name_len = (int32_T)strlen(name) + 1;
  if ((fwrite(&type, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&m, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&n, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&imagf, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(&name_len, sizeof(int32_T), 1, fp) == 0) ||
      (fwrite(name, sizeof(char), name_len, fp) == 0)) {
    return(1);
  } else {
    return(0);
  }
}                                      /* end rt_WriteMat4FileHeader */

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
  real_T rtb_Clock_tmp;
  real_T rtb_Derivative;
  real_T rtb_K_pp;
  real_T *lastU;
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

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopterD2_DW.IfActionSubsystem_SubsysRanBC);
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* S-Function (hil_read_encoder_timebase_block): '<S6>/HIL Read Encoder Timebase' */

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

    /* Gain: '<S6>/Travel: Count to rad' incorporates:
     *  Gain: '<S6>/Travel_gain'
     */
    helicopterD2_B.TravelCounttorad = helicopterD2_P.travel_gain *
      rtb_HILReadEncoderTimebase_o1 * helicopterD2_P.TravelCounttorad_Gain;

    /* Gain: '<S14>/Gain' */
    helicopterD2_B.Gain = helicopterD2_P.Gain_Gain *
      helicopterD2_B.TravelCounttorad;

    /* Sum: '<Root>/Sum3' incorporates:
     *  Constant: '<Root>/travel_offset [deg]'
     */
    helicopterD2_B.Sum3 = helicopterD2_P.travel_offsetdeg_Value +
      helicopterD2_B.Gain;

    /* Gain: '<S6>/Pitch: Count to rad' */
    helicopterD2_B.PitchCounttorad = helicopterD2_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S11>/Gain' */
    helicopterD2_B.Gain_i = helicopterD2_P.Gain_Gain_a *
      helicopterD2_B.PitchCounttorad;
  }

  /* Clock: '<S5>/Clock' incorporates:
   *  TransferFcn: '<S6>/Travel: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopterD2_P.TravelTransferFcn_C *
    helicopterD2_X.TravelTransferFcn_CSTATE;
  rtb_Clock += helicopterD2_P.TravelTransferFcn_D *
    helicopterD2_B.TravelCounttorad;

  /* Gain: '<S15>/Gain' */
  helicopterD2_B.Gain_d = helicopterD2_P.Gain_Gain_l * rtb_Clock;

  /* Clock: '<S5>/Clock' incorporates:
   *  TransferFcn: '<S6>/Pitch: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopterD2_P.PitchTransferFcn_C *
    helicopterD2_X.PitchTransferFcn_CSTATE;
  rtb_Clock += helicopterD2_P.PitchTransferFcn_D *
    helicopterD2_B.PitchCounttorad;

  /* Gain: '<S12>/Gain' */
  helicopterD2_B.Gain_b = helicopterD2_P.Gain_Gain_ae * rtb_Clock;
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* Gain: '<S6>/Elevation: Count to rad' incorporates:
     *  Gain: '<S6>/Elevation_gain'
     */
    helicopterD2_B.ElevationCounttorad = helicopterD2_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterD2_P.ElevationCounttorad_Gain;

    /* Gain: '<S9>/Gain' */
    helicopterD2_B.Gain_e = helicopterD2_P.Gain_Gain_lv *
      helicopterD2_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopterD2_B.Sum = helicopterD2_B.Gain_e +
      helicopterD2_P.elavation_offsetdeg_Value;
  }

  /* Clock: '<S5>/Clock' incorporates:
   *  TransferFcn: '<S6>/Elevation: Transfer Fcn'
   */
  rtb_Clock = 0.0;
  rtb_Clock += helicopterD2_P.ElevationTransferFcn_C *
    helicopterD2_X.ElevationTransferFcn_CSTATE;
  rtb_Clock += helicopterD2_P.ElevationTransferFcn_D *
    helicopterD2_B.ElevationCounttorad;

  /* Gain: '<S10>/Gain' */
  helicopterD2_B.Gain_dg = helicopterD2_P.Gain_Gain_n * rtb_Clock;

  /* Gain: '<S2>/Gain1' */
  helicopterD2_B.Gain1[0] = helicopterD2_P.Gain1_Gain * helicopterD2_B.Sum3;
  helicopterD2_B.Gain1[1] = helicopterD2_P.Gain1_Gain * helicopterD2_B.Gain_d;
  helicopterD2_B.Gain1[2] = helicopterD2_P.Gain1_Gain * helicopterD2_B.Gain_i;
  helicopterD2_B.Gain1[3] = helicopterD2_P.Gain1_Gain * helicopterD2_B.Gain_b;
  helicopterD2_B.Gain1[4] = helicopterD2_P.Gain1_Gain * helicopterD2_B.Sum;
  helicopterD2_B.Gain1[5] = helicopterD2_P.Gain1_Gain * helicopterD2_B.Gain_dg;
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* ToFile: '<Root>/       ' */
    {
      if (!(++helicopterD2_DW._IWORK.Decimation % 1) &&
          (helicopterD2_DW._IWORK.Count * (6 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterD2_DW._PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          helicopterD2_DW._IWORK.Decimation = 0;
          u[0] = helicopterD2_M->Timing.t[1];
          u[1] = helicopterD2_B.Gain1[0];
          u[2] = helicopterD2_B.Gain1[1];
          u[3] = helicopterD2_B.Gain1[2];
          u[4] = helicopterD2_B.Gain1[3];
          u[5] = helicopterD2_B.Gain1[4];
          u[6] = helicopterD2_B.Gain1[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(helicopterD2_M,
                              "Error writing to MAT-file x_enc.mat");
            return;
          }

          if (((++helicopterD2_DW._IWORK.Count) * (6 + 1))+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file x_enc.mat.\n");
          }
        }
      }
    }

    /* Gain: '<S3>/Gain1' */
    helicopterD2_B.Gain1_k = helicopterD2_P.Gain1_Gain_i * helicopterD2_B.Gain_i;

    /* Gain: '<S4>/Gain1' */
    helicopterD2_B.Gain1_g = helicopterD2_P.Gain1_Gain_n * helicopterD2_B.Sum3;
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

  /* Clock: '<S5>/Clock' incorporates:
   *  Sum: '<S7>/Sum2'
   */
  rtb_Clock -= helicopterD2_B.Gain1[2];

  /* Gain: '<S7>/K_pp' */
  rtb_K_pp = helicopterD2_P.K_pp * rtb_Clock;

  /* Clock: '<S5>/Clock' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S7>/K_pd'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S7>/Sum3'
   */
  rtb_Clock = helicopterD2_P.K_pd * helicopterD2_B.Gain1[3];
  rtb_Clock = (rtb_K_pp - rtb_Clock) + helicopterD2_P.Vd_ff;

  /* Integrator: '<S5>/Integrator' */
  /* Limited  Integrator  */
  if (helicopterD2_X.Integrator_CSTATE >= helicopterD2_P.Integrator_UpperSat) {
    helicopterD2_X.Integrator_CSTATE = helicopterD2_P.Integrator_UpperSat;
  } else {
    if (helicopterD2_X.Integrator_CSTATE <= helicopterD2_P.Integrator_LowerSat)
    {
      helicopterD2_X.Integrator_CSTATE = helicopterD2_P.Integrator_LowerSat;
    }
  }

  /* Sum: '<S5>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   */
  rtb_Derivative = helicopterD2_P.elevation_ref_Value - helicopterD2_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S5>/K_ed'
   *  Gain: '<S5>/K_ep'
   *  Integrator: '<S5>/Integrator'
   *  Sum: '<S5>/Sum1'
   */
  rtb_Backgain = ((helicopterD2_P.K_ep * rtb_Derivative +
                   helicopterD2_X.Integrator_CSTATE) - helicopterD2_P.K_ed *
                  helicopterD2_B.Gain1[5]) + helicopterD2_P.Vs_ff;

  /* Sum: '<S1>/Add' */
  rtb_K_pp = rtb_Clock + rtb_Backgain;

  /* Sum: '<S1>/Subtract' */
  rtb_Backgain -= rtb_Clock;

  /* Clock: '<S5>/Clock' incorporates:
   *  Derivative: '<S6>/Derivative'
   */
  rtb_Clock_tmp = helicopterD2_M->Timing.t[0];

  /* Clock: '<S5>/Clock' */
  rtb_Clock = rtb_Clock_tmp;

  /* If: '<S5>/If' incorporates:
   *  Gain: '<S5>/K_ei'
   *  Inport: '<S8>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    rtAction = (int8_T)!(rtb_Clock >= 2.0);
    helicopterD2_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterD2_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S5>/If Action Subsystem' incorporates:
     *  ActionPort: '<S8>/Action Port'
     */
    helicopterD2_B.In1 = helicopterD2_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopterD2_M)) {
      srUpdateBC(helicopterD2_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S5>/If Action Subsystem' */
  }

  /* End of If: '<S5>/If' */
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
  }

  /* Derivative: '<S6>/Derivative' */
  if ((helicopterD2_DW.TimeStampA >= rtb_Clock_tmp) &&
      (helicopterD2_DW.TimeStampB >= rtb_Clock_tmp)) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Derivative = helicopterD2_DW.TimeStampA;
    lastU = &helicopterD2_DW.LastUAtTimeA;
    if (helicopterD2_DW.TimeStampA < helicopterD2_DW.TimeStampB) {
      if (helicopterD2_DW.TimeStampB < rtb_Clock_tmp) {
        rtb_Derivative = helicopterD2_DW.TimeStampB;
        lastU = &helicopterD2_DW.LastUAtTimeB;
      }
    } else {
      if (helicopterD2_DW.TimeStampA >= rtb_Clock_tmp) {
        rtb_Derivative = helicopterD2_DW.TimeStampB;
        lastU = &helicopterD2_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopterD2_B.PitchCounttorad - *lastU) / (rtb_Clock_tmp
      - rtb_Derivative);
  }

  /* Gain: '<S13>/Gain' */
  helicopterD2_B.Gain_l = helicopterD2_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
  }

  /* Gain: '<S1>/Back gain' */
  rtb_Derivative = helicopterD2_P.Backgain_Gain * rtb_Backgain;

  /* Saturate: '<S6>/Back motor: Saturation' */
  if (rtb_Derivative > helicopterD2_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S6>/Back motor: Saturation' */
    helicopterD2_B.BackmotorSaturation =
      helicopterD2_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterD2_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S6>/Back motor: Saturation' */
    helicopterD2_B.BackmotorSaturation =
      helicopterD2_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S6>/Back motor: Saturation' */
    helicopterD2_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S6>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
  }

  /* Gain: '<S1>/Front gain' */
  rtb_Derivative = helicopterD2_P.Frontgain_Gain * rtb_K_pp;

  /* Saturate: '<S6>/Front motor: Saturation' */
  if (rtb_Derivative > helicopterD2_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S6>/Front motor: Saturation' */
    helicopterD2_B.FrontmotorSaturation =
      helicopterD2_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterD2_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S6>/Front motor: Saturation' */
    helicopterD2_B.FrontmotorSaturation =
      helicopterD2_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S6>/Front motor: Saturation' */
    helicopterD2_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S6>/Front motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD2_M)) {
    /* S-Function (hil_write_analog_block): '<S6>/HIL Write Analog' */

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
  real_T *lastU;

  /* Update for Derivative: '<S6>/Derivative' */
  if (helicopterD2_DW.TimeStampA == (rtInf)) {
    helicopterD2_DW.TimeStampA = helicopterD2_M->Timing.t[0];
    lastU = &helicopterD2_DW.LastUAtTimeA;
  } else if (helicopterD2_DW.TimeStampB == (rtInf)) {
    helicopterD2_DW.TimeStampB = helicopterD2_M->Timing.t[0];
    lastU = &helicopterD2_DW.LastUAtTimeB;
  } else if (helicopterD2_DW.TimeStampA < helicopterD2_DW.TimeStampB) {
    helicopterD2_DW.TimeStampA = helicopterD2_M->Timing.t[0];
    lastU = &helicopterD2_DW.LastUAtTimeA;
  } else {
    helicopterD2_DW.TimeStampB = helicopterD2_M->Timing.t[0];
    lastU = &helicopterD2_DW.LastUAtTimeB;
  }

  *lastU = helicopterD2_B.PitchCounttorad;

  /* End of Update for Derivative: '<S6>/Derivative' */
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

  /* Derivatives for TransferFcn: '<S6>/Travel: Transfer Fcn' */
  _rtXdot->TravelTransferFcn_CSTATE = 0.0;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD2_P.TravelTransferFcn_A *
    helicopterD2_X.TravelTransferFcn_CSTATE;
  _rtXdot->TravelTransferFcn_CSTATE += helicopterD2_B.TravelCounttorad;

  /* Derivatives for TransferFcn: '<S6>/Pitch: Transfer Fcn' */
  _rtXdot->PitchTransferFcn_CSTATE = 0.0;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD2_P.PitchTransferFcn_A *
    helicopterD2_X.PitchTransferFcn_CSTATE;
  _rtXdot->PitchTransferFcn_CSTATE += helicopterD2_B.PitchCounttorad;

  /* Derivatives for TransferFcn: '<S6>/Elevation: Transfer Fcn' */
  _rtXdot->ElevationTransferFcn_CSTATE = 0.0;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD2_P.ElevationTransferFcn_A *
    helicopterD2_X.ElevationTransferFcn_CSTATE;
  _rtXdot->ElevationTransferFcn_CSTATE += helicopterD2_B.ElevationCounttorad;

  /* Derivatives for Integrator: '<S5>/Integrator' */
  lsat = (helicopterD2_X.Integrator_CSTATE <= helicopterD2_P.Integrator_LowerSat);
  usat = (helicopterD2_X.Integrator_CSTATE >= helicopterD2_P.Integrator_UpperSat);
  if (((!lsat) && (!usat)) || (lsat && (helicopterD2_B.In1 > 0.0)) || (usat &&
       (helicopterD2_B.In1 < 0.0))) {
    _rtXdot->Integrator_CSTATE = helicopterD2_B.In1;
  } else {
    /* in saturation */
    _rtXdot->Integrator_CSTATE = 0.0;
  }

  /* End of Derivatives for Integrator: '<S5>/Integrator' */
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

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S6>/HIL Read Encoder Timebase' */

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

  /* Start for ToFile: '<Root>/       ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "x_enc.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterD2_M, "Error creating .mat file x_enc.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterD2_M,
                        "Error writing mat file header to file x_enc.mat");
      return;
    }

    helicopterD2_DW._IWORK.Count = 0;
    helicopterD2_DW._IWORK.Decimation = -1;
    helicopterD2_DW._PWORK.FilePtr = fp;
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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829682,
      0.5235987755982966, 0.52359877559829615, 0.52359877559829571,
      0.523598775598295, 0.52359877559829415, 0.523598775598293,
      0.52359877559829127, 0.5235987755982886, 0.5235987755982846,
      0.523598775598274, 0.523598775598212, 0.52359877559807944,
      -0.011120274942176711, -0.52359877559808565, -0.52359877559821277,
      -0.52359877559823553, -0.5235987755982433, -0.52359877559824541,
      -0.52359877559824408, -0.52359877559823909, -0.523598775598231,
      -0.52359877559821333, -0.52359877559809387, -0.52359877559743373,
      -0.52359877559672463, -0.52359877542821587, -0.52359875495089969,
      -0.32089753062788384, -0.13965645376143493, -0.008066579812406216,
      0.0800000163537905, 0.13193086443848046, 0.15549391886790787,
      0.15815710065874844, 0.1466185908913108, 0.12653199590038755,
      0.10239460749005325, 0.077560424390479943, 0.054339534477009233,
      0.034149418125002606, 0.017689801892250889, 0.0051194808958072713,
      -0.0037798916995264165, -0.009462240879248407, -0.012502170259689582,
      -0.013507548880510867, -0.013057876144358382, -0.011665140270852858,
      -0.0097530894877980723, -0.0076506347956697418, -0.0055953229163406837,
      -0.003743303717656965, -0.002182841361340726, -0.00094908541969895843,
      -3.84580600675255E-5, 0.00057841833936411735, 0.00094585612586217671,
      0.0011145340385927405, 0.0011351917222386376, 0.0010543753974335823,
      0.000911920845941272, 0.00073981722341043277, 0.00056209622629610489,
      0.00039542148951032807, 0.0002501006776762793, 0.00013129796315680675,
      4.028035625858184E-5, -2.4417164063983421E-5, -6.5978474807604215E-5,
      -8.8480088803688517E-5, -9.6259873146098407E-5, -9.3469816656033267E-5,
      -8.37901473511593E-5, -7.0276036896688154E-5, -5.5306443084046641E-5,
      -4.0606046671443075E-5, -2.7314610250850357E-5, -1.608250192730587E-5,
      -7.1758768620533431E-6, -5.7958966503957043E-7, 3.9100062926289425E-6,
      6.6068089518145356E-6, 7.8730353533229547E-6, 8.0734288669948029E-6,
      7.544130182224329E-6, 6.5739857872948448E-6, 5.3957498203915932E-6,
      4.184637832915783E-6, 3.061912633217645E-6, 2.1015373082855504E-6,
      1.3383509179787367E-6, 7.7665776387902952E-7, 3.98535851986459E-7,
      1.7153813991477307E-7, 5.5755969174953179E-8, 1.0396086880248845E-8, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopterD2_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD2_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD2_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for If: '<S5>/If' */
  helicopterD2_DW.If_ActiveSubsystem = -1;

  /* InitializeConditions for TransferFcn: '<S6>/Travel: Transfer Fcn' */
  helicopterD2_X.TravelTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S6>/Pitch: Transfer Fcn' */
  helicopterD2_X.PitchTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S6>/Elevation: Transfer Fcn' */
  helicopterD2_X.ElevationTransferFcn_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S5>/Integrator' */
  helicopterD2_X.Integrator_CSTATE = helicopterD2_P.Integrator_IC;

  /* InitializeConditions for Derivative: '<S6>/Derivative' */
  helicopterD2_DW.TimeStampA = (rtInf);
  helicopterD2_DW.TimeStampB = (rtInf);
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

  /* Terminate for ToFile: '<Root>/       ' */
  {
    FILE *fp = (FILE *) helicopterD2_DW._PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "x_enc.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD2_M, "Error closing MAT-file x_enc.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterD2_M, "Error reopening MAT-file x_enc.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1, helicopterD2_DW._IWORK.Count, "ans"))
      {
        rtmSetErrorStatus(helicopterD2_M,
                          "Error writing header for ans to MAT-file x_enc.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD2_M, "Error closing MAT-file x_enc.mat");
        return;
      }

      helicopterD2_DW._PWORK.FilePtr = (NULL);
    }
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

  rtmSetTFinal(helicopterD2_M, 25.0);
  helicopterD2_M->Timing.stepSize0 = 0.002;
  helicopterD2_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopterD2_M->Sizes.checksums[0] = (3897251790U);
  helicopterD2_M->Sizes.checksums[1] = (1252532254U);
  helicopterD2_M->Sizes.checksums[2] = (285317196U);
  helicopterD2_M->Sizes.checksums[3] = (1761704310U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopterD2_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&helicopterD2_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopterD2_M->extModeInfo,
      &helicopterD2_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopterD2_M->extModeInfo,
                        helicopterD2_M->Sizes.checksums);
    rteiSetTPtr(helicopterD2_M->extModeInfo, rtmGetTPtr(helicopterD2_M));
  }

  helicopterD2_M->solverInfoPtr = (&helicopterD2_M->solverInfo);
  helicopterD2_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterD2_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterD2_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterD2_M->blockIO = ((void *) &helicopterD2_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopterD2_B.Gain1[i] = 0.0;
    }

    helicopterD2_B.TravelCounttorad = 0.0;
    helicopterD2_B.Gain = 0.0;
    helicopterD2_B.Sum3 = 0.0;
    helicopterD2_B.Gain_d = 0.0;
    helicopterD2_B.PitchCounttorad = 0.0;
    helicopterD2_B.Gain_i = 0.0;
    helicopterD2_B.Gain_b = 0.0;
    helicopterD2_B.ElevationCounttorad = 0.0;
    helicopterD2_B.Gain_e = 0.0;
    helicopterD2_B.Sum = 0.0;
    helicopterD2_B.Gain_dg = 0.0;
    helicopterD2_B.Gain1_k = 0.0;
    helicopterD2_B.Gain1_g = 0.0;
    helicopterD2_B.Gain_l = 0.0;
    helicopterD2_B.BackmotorSaturation = 0.0;
    helicopterD2_B.FrontmotorSaturation = 0.0;
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

  helicopterD2_DW.TimeStampA = 0.0;
  helicopterD2_DW.LastUAtTimeA = 0.0;
  helicopterD2_DW.TimeStampB = 0.0;
  helicopterD2_DW.LastUAtTimeB = 0.0;
  helicopterD2_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterD2_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopterD2_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopterD2_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterD2_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterD2_M->Sizes.numY = (0);    /* Number of model outputs */
  helicopterD2_M->Sizes.numU = (0);    /* Number of model inputs */
  helicopterD2_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterD2_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterD2_M->Sizes.numBlocks = (63);/* Number of blocks */
  helicopterD2_M->Sizes.numBlockIO = (18);/* Number of block outputs */
  helicopterD2_M->Sizes.numBlockPrms = (147);/* Sum of parameter "widths" */
  return helicopterD2_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

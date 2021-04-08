/*
 * helicopterD3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD3".
 *
 * Model version              : 11.7
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Thu Apr  8 17:57:03 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterD3.h"
#include "helicopterD3_private.h"
#include "helicopterD3_dt.h"

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
  real_T rtb_Frontgain;
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T rtb_HILReadEncoderTimebase_o3;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
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

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopterD3_DW.IfActionSubsystem_SubsysRanBC);
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

    /* Gain: '<S13>/Gain' */
    helicopterD3_B.Gain = helicopterD3_P.Gain_Gain *
      helicopterD3_B.TravelCounttorad;

    /* Sum: '<Root>/Sum4' incorporates:
     *  Constant: '<Root>/Pi'
     */
    helicopterD3_B.Sum4 = helicopterD3_P.Pi_Value + helicopterD3_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopterD3_B.PitchCounttorad = helicopterD3_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopterD3_B.Gain_i = helicopterD3_P.Gain_Gain_a *
      helicopterD3_B.PitchCounttorad;
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopterD3_B.Gain_d = (helicopterD3_P.TravelTransferFcn_C *
    helicopterD3_X.TravelTransferFcn_CSTATE + helicopterD3_P.TravelTransferFcn_D
    * helicopterD3_B.TravelCounttorad) * helicopterD3_P.Gain_Gain_l;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopterD3_B.Gain_b = (helicopterD3_P.PitchTransferFcn_C *
    helicopterD3_X.PitchTransferFcn_CSTATE + helicopterD3_P.PitchTransferFcn_D *
    helicopterD3_B.PitchCounttorad) * helicopterD3_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopterD3_B.ElevationCounttorad = helicopterD3_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterD3_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopterD3_B.Gain_e = helicopterD3_P.Gain_Gain_lv *
      helicopterD3_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopterD3_B.Sum = helicopterD3_B.Gain_e +
      helicopterD3_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopterD3_B.Gain_dg = (helicopterD3_P.ElevationTransferFcn_C *
    helicopterD3_X.ElevationTransferFcn_CSTATE +
    helicopterD3_P.ElevationTransferFcn_D * helicopterD3_B.ElevationCounttorad) *
    helicopterD3_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopterD3_B.Gain1[0] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Sum4;
  helicopterD3_B.Gain1[1] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Gain_d;
  helicopterD3_B.Gain1[2] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Gain_i;
  helicopterD3_B.Gain1[3] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Gain_b;
  helicopterD3_B.Gain1[4] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Sum;
  helicopterD3_B.Gain1[5] = helicopterD3_P.Gain1_Gain * helicopterD3_B.Gain_dg;
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    /* ToFile: '<Root>/       ' */
    {
      if (!(++helicopterD3_DW._IWORK.Decimation % 1) &&
          (helicopterD3_DW._IWORK.Count * (6 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterD3_DW._PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          helicopterD3_DW._IWORK.Decimation = 0;
          u[0] = helicopterD3_M->Timing.t[1];
          u[1] = helicopterD3_B.Gain1[0];
          u[2] = helicopterD3_B.Gain1[1];
          u[3] = helicopterD3_B.Gain1[2];
          u[4] = helicopterD3_B.Gain1[3];
          u[5] = helicopterD3_B.Gain1[4];
          u[6] = helicopterD3_B.Gain1[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(helicopterD3_M,
                              "Error writing to MAT-file x_enc.mat");
            return;
          }

          if (((++helicopterD3_DW._IWORK.Count) * (6 + 1))+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file x_enc.mat.\n");
          }
        }
      }
    }
  }

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

  /* Sum: '<S6>/Sum' */
  rtb_Sum[0] = helicopterD3_B.Gain1[0] - rtb_Sum[0];
  rtb_Sum[1] = helicopterD3_B.Gain1[1] - rtb_Sum[1];
  rtb_Sum[2] = helicopterD3_B.Gain1[2] - rtb_Sum[2];
  rtb_Sum[3] = helicopterD3_B.Gain1[3] - rtb_Sum[3];

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
          rtb_Frontgain = pDataValues[currTimeIndex];
        } else {
          rtb_Frontgain = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex= currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        rtb_Frontgain = (real_T) rtInterpolate(d1, d2, f1, f2);
        pDataValues += 141;
      }
    }
  }

  /* Sum: '<Root>/Sum3' incorporates:
   *  Gain: '<S6>/Gain'
   */
  helicopterD3_B.u = rtb_Frontgain - (((helicopterD3_P.K[0] * rtb_Sum[0] +
    helicopterD3_P.K[1] * rtb_Sum[1]) + helicopterD3_P.K[2] * rtb_Sum[2]) +
    helicopterD3_P.K[3] * rtb_Sum[3]);
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    /* ToFile: '<Root>/            ' */
    {
      if (!(++helicopterD3_DW._IWORK_f.Decimation % 1) &&
          (helicopterD3_DW._IWORK_f.Count * (1 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterD3_DW._PWORK_f.FilePtr;
        if (fp != (NULL)) {
          real_T u[1 + 1];
          helicopterD3_DW._IWORK_f.Decimation = 0;
          u[0] = helicopterD3_M->Timing.t[1];
          u[1] = helicopterD3_B.u;
          if (fwrite(u, sizeof(real_T), 1 + 1, fp) != 1 + 1) {
            rtmSetErrorStatus(helicopterD3_M,
                              "Error writing to MAT-file u_vec.mat");
            return;
          }

          if (((++helicopterD3_DW._IWORK_f.Count) * (1 + 1))+1 >= 100000000) {
            (void)fprintf(stdout,
                          "*** The ToFile block will stop logging data before\n"
                          "    the simulation has ended, because it has reached\n"
                          "    the maximum number of elements (100000000)\n"
                          "    allowed in MAT-file u_vec.mat.\n");
          }
        }
      }
    }
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S5>/Sum2'
   */
  rtb_Frontgain = helicopterD3_B.u - helicopterD3_B.Gain1[2];

  /* Gain: '<S5>/K_pp' */
  rtb_Clock = helicopterD3_P.K_pp * rtb_Frontgain;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Sum: '<Root>/Sum1'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Frontgain = helicopterD3_P.K_pd * helicopterD3_B.Gain1[3];
  rtb_Frontgain = (rtb_Clock - rtb_Frontgain) + helicopterD3_P.Vd_ff;

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

  /* Sum: '<S3>/Sum' incorporates:
   *  Constant: '<Root>/elevation_ref'
   */
  rtb_Derivative = helicopterD3_P.elevation_ref_Value - helicopterD3_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopterD3_P.K_ep * rtb_Derivative +
                   helicopterD3_X.Integrator_CSTATE) - helicopterD3_P.K_ed *
                  helicopterD3_B.Gain1[5]) + helicopterD3_P.Vs_ff;

  /* Sum: '<S1>/Subtract' */
  rtb_Clock = rtb_Backgain - rtb_Frontgain;

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Frontgain = (rtb_Frontgain + rtb_Backgain) * helicopterD3_P.Frontgain_Gain;

  /* If: '<S3>/If' incorporates:
   *  Clock: '<S3>/Clock'
   *  Gain: '<S3>/K_ei'
   *  Inport: '<S7>/In1'
   */
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
    rtAction = (int8_T)!(helicopterD3_M->Timing.t[0] >= 2.0);
    helicopterD3_DW.If_ActiveSubsystem = rtAction;
  } else {
    rtAction = helicopterD3_DW.If_ActiveSubsystem;
  }

  if (rtAction == 0) {
    /* Outputs for IfAction SubSystem: '<S3>/If Action Subsystem' incorporates:
     *  ActionPort: '<S7>/Action Port'
     */
    helicopterD3_B.In1 = helicopterD3_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopterD3_M)) {
      srUpdateBC(helicopterD3_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Derivative = helicopterD3_M->Timing.t[0];
  if ((helicopterD3_DW.TimeStampA >= rtb_Derivative) &&
      (helicopterD3_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    rtb_Backgain = helicopterD3_DW.TimeStampA;
    lastU = &helicopterD3_DW.LastUAtTimeA;
    if (helicopterD3_DW.TimeStampA < helicopterD3_DW.TimeStampB) {
      if (helicopterD3_DW.TimeStampB < rtb_Derivative) {
        rtb_Backgain = helicopterD3_DW.TimeStampB;
        lastU = &helicopterD3_DW.LastUAtTimeB;
      }
    } else {
      if (helicopterD3_DW.TimeStampA >= rtb_Derivative) {
        rtb_Backgain = helicopterD3_DW.TimeStampB;
        lastU = &helicopterD3_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopterD3_B.PitchCounttorad - *lastU) / (rtb_Derivative
      - rtb_Backgain);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopterD3_B.Gain_l = helicopterD3_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
  }

  /* Gain: '<S1>/Back gain' */
  rtb_Clock *= helicopterD3_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Clock > helicopterD3_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD3_B.BackmotorSaturation =
      helicopterD3_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Clock < helicopterD3_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD3_B.BackmotorSaturation =
      helicopterD3_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD3_B.BackmotorSaturation = rtb_Clock;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD3_M)) {
  }

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Frontgain > helicopterD3_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD3_B.FrontmotorSaturation =
      helicopterD3_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Frontgain < helicopterD3_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD3_B.FrontmotorSaturation =
      helicopterD3_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD3_B.FrontmotorSaturation = rtb_Frontgain;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
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
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopterD3_DW.TimeStampA == (rtInf)) {
    helicopterD3_DW.TimeStampA = helicopterD3_M->Timing.t[0];
    lastU = &helicopterD3_DW.LastUAtTimeA;
  } else if (helicopterD3_DW.TimeStampB == (rtInf)) {
    helicopterD3_DW.TimeStampB = helicopterD3_M->Timing.t[0];
    lastU = &helicopterD3_DW.LastUAtTimeB;
  } else if (helicopterD3_DW.TimeStampA < helicopterD3_DW.TimeStampB) {
    helicopterD3_DW.TimeStampA = helicopterD3_M->Timing.t[0];
    lastU = &helicopterD3_DW.LastUAtTimeA;
  } else {
    helicopterD3_DW.TimeStampB = helicopterD3_M->Timing.t[0];
    lastU = &helicopterD3_DW.LastUAtTimeB;
  }

  *lastU = helicopterD3_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
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

  /* Start for ToFile: '<Root>/       ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "x_enc.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterD3_M, "Error creating .mat file x_enc.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterD3_M,
                        "Error writing mat file header to file x_enc.mat");
      return;
    }

    helicopterD3_DW._IWORK.Count = 0;
    helicopterD3_DW._IWORK.Decimation = -1;
    helicopterD3_DW._PWORK.FilePtr = fp;
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
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1415926535897931, 3.1415926535897931,
      3.1415926535897931, 3.1378421413581004, 3.1262155534495779,
      3.1033093000177243, 3.0666274151656396, 3.0144539223448756,
      2.9456562770496388, 2.8595077632063375, 2.7555515878588226,
      2.6335051103643985, 2.4931956058870255, 2.3345185758741969,
      2.1583782669637146, 1.9678000581135191, 1.7674109954733876,
      1.5625809549354213, 1.358683804011916, 1.1605918369355772,
      0.97235388516989174, 0.79694979436636826, 0.63643262323373173,
      0.49215933302296, 0.36485709412521788, 0.25463979460451081,
      0.16109616184129089, 0.083400574655896842, 0.020423656619654978,
      -0.029167441704377982, -0.066822904066107081, -0.0940390640924539,
      -0.11230155622235478, -0.12304153586926976, -0.12760344283844177,
      -0.12722271685743988, -0.12301190962844068, -0.1159537270863043,
      -0.10689965405874764, -0.09657294712217078, -0.085574921725740466,
      -0.074393600546095173, -0.063413927293962655, -0.052928880639357516,
      -0.04315094432883871, -0.034223500296097206, -0.026231810811581779,
      -0.019213342941689721, -0.013167263929779859, -0.0080629998942333535,
      -0.0038478030631035214, -0.00045331552211483371, 0.0021988489692087295,
      0.0041924581240611568, 0.00561288393830298, 0.0065441176597979041,
      0.0070664922888435556, 0.007255025067771201, 0.0071782928370169967,
      0.0068977561523728857, 0.006467452980336511, 0.0059339890631594141,
      0.0053367591566571126, 0.0047083409035912939, 0.0040750107676803642,
      0.0034573389690635364, 0.0028708275270749174, 0.002326562189651357,
      0.0018318551162871115, 0.0013908606225582934, 0.0010051510695038123,
      0.00067424408815765127, 0.00039607579327794986, 0.00016741749599207475,
      -1.5764280438531193E-5, -0.00015800288881626451, -0.00026407881788686468,
      -0.00033881524306625383, -0.00038691737198464282, -0.00041285075169586092,
      -0.00042075359470661653, -0.00041437825154655157, -0.00039705716704153537,
      -0.0003716889678354599, -0.00034074070924942419, -0.00030626273216083767,
      -0.00026991302312797245, -0.00023298841454796724, -0.00019646039109629898,
      -0.0001610136718334827, -0.00012708610399008116, -9.4908725824856252E-5,
      -6.45451236989734E-5, -3.5929413389653984E-5, -8.90230658706063E-6,
      1.6755233440410426E-5, 4.12913043120547E-5, 6.4956082763148527E-5,
      8.7979585578187793E-5, 0.00011055557878012771, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048917201064,
      -0.046506351656542169, -0.091625013734441721, -0.14672753940815955,
      -0.20869397123343644, -0.27519058115644818, -0.34459405538014581,
      -0.41582470141326755, -0.48818591000878953, -0.56123801786711214,
      -0.634708120007655, -0.70456123559370043, -0.76231283539710615,
      -0.80155625054534674, -0.81932016215214043, -0.8155886037057043,
      -0.79236786827609684, -0.7529518070689889, -0.70161636319697884,
      -0.642068684516413, -0.57709316084518891, -0.50920895555766155,
      -0.44086919811311776, -0.37417453105548781, -0.31078234873521415,
      -0.25190767215982685, -0.19836439330924963, -0.15062184943913481,
      -0.10886464012460555, -0.073049968505004712, -0.04295991857744879,
      -0.018247627868953214, 0.0015229039264128149, 0.016843228913179669,
      0.028232730172138093, 0.0362162921126615, 0.041306827744810752,
      0.043992101587239915, 0.044725284716789881, 0.043918693005298617,
      0.041940186619619735, 0.039111745242053561, 0.035709776133060346,
      0.0319667579361035, 0.028073871477010411, 0.024184316045238938,
      0.020417056141757588, 0.016860787326075918, 0.013577950164258485,
      0.010608657963113763, 0.0079744366195490766, 0.0056817032563070934,
      0.0037249348865819464, 0.0020894985170541217, 0.00075413111531568518,
      -0.00030692892261997211, -0.0011221467385628579, -0.0017212126883052951,
      -0.0021338556687659819, -0.0023889196259528457, -0.0025136730122892223,
      -0.0025333205436405622, -0.0024706871944557042, -0.0023460457678644948,
      -0.0021770613495687673, -0.00197882829326785, -0.0017639779749067145,
      -0.0015428382122697874, -0.0013236279255590079, -0.0011126731796560368,
      -0.0009146331891584196, -0.00073272710577309782, -0.00056895443348615972,
      -0.00042430371625123427, -0.00029894570070579558, -0.00019240851570384782,
      -0.00010373351886705226, -3.1611372026824223E-5, 2.5501372652184395E-5,
      6.92843380156535E-5, 0.0001014727968107909, 0.00012379303433933424,
      0.00013791190835017104, 0.000145398836133918, 0.00014769843432559134,
      0.00014611209381003282, 0.00014178687705066566, 0.00013571027137004494,
      0.00012870951266184767, 0.00012145440850193107, 0.00011446284123800034,
      0.00010810842721089078, 0.00010263016011142474, 9.8144283487780208E-5,
      9.4659113806076721E-5, 9.2094011258328948E-5, 9.0303972807803936E-5,
      8.9110874030441114E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875207092044, 0.22266037931927207, 0.318881471795075,
      0.38944360629700792, 0.4379550737651976, 0.46997264229395097,
      0.49051724877025504, 0.5034310014141935, 0.51142138586090657,
      0.51630439857945609, 0.51925862127590838, 0.49369514239354884,
      0.40816625060380507, 0.277357470521581, 0.12554854193153475,
      -0.02637323009949627, -0.16411528900531824, -0.27857766734823486,
      -0.36281931122682104, -0.42086025003955768, -0.45922218544653465,
      -0.47977963631801318, -0.48299930537316677, -0.47137243451387273,
      -0.44803173399684482, -0.41610372876821405, -0.37842344550402218,
      -0.337426066033261, -0.29512400750638945, -0.2531244203618182,
      -0.21266498095142705, -0.17465703254524534, -0.1397305678273757,
      -0.10827820591003506, -0.080496644965468878, -0.056424766695017725,
      -0.035977961675399017, -0.018978489925194575, -0.0051818583455516265,
      0.0057006821314992129, 0.013983327531272294, 0.019990343367292773,
      0.024043818396113359, 0.026454223061642246, 0.027513434697979511,
      0.027489892302258512, 0.026625554213773772, 0.02513434976632456,
      0.023201839262909751, 0.020985823210890042, 0.018617670412215959,
      0.016204163756477374, 0.013829691509682052, 0.011558639648636793,
      0.0094378667872960786, 0.0074991671101900526, 0.0057616481707635225,
      0.0042339693309828563, 0.0029164029897612576, 0.0018026946352195372,
      0.00088170928819442107, 0.00013886124814010969, -0.00044266859164976413,
      -0.00088091799773204471, -0.0011943173284855169, -0.0014010355307811917,
      -0.0015184799956825534, -0.0015629313846351467, -0.0015492945849636675,
      -0.0014909475751101464, -0.0013996710157151426, -0.0012856427224940958,
      -0.0011574826974948271, -0.0010223360237535672, -0.0008859825772195018,
      -0.00075296413505132609, -0.00062672101031446825, -0.00050973178860880264,
      -0.0004036510666022286, -0.00030944127760901274, -0.00022749573327041084,
      -0.00015775091413194886, -9.978680917677174E-5, -5.2914746092369569E-5,
      -1.6252681744322039E-5, 1.1211648898834525E-5, 3.0568980189160655E-5,
      4.2947128153225655E-5, 4.9478688828541451E-5, 5.1276305315650639E-5,
      4.9413727200464663E-5, 4.4910571448286696E-5, 3.8718299579909576E-5,
      3.1704462711390491E-5, 2.463184824719189E-5, 1.8129165111235857E-5,
      1.2651308120337212E-5, 8.4323664862884229E-6, 5.4485824284578044E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500823768633,
      0.46652650906667492, 0.38488436997799264, 0.28224853798573468,
      0.19404586987333083, 0.12807027412071126, 0.082178425907496341,
      0.051655010570862289, 0.031961537799632941, 0.019532050874564232,
      0.011816890786057547, -0.10225391552643, -0.34211556717377783,
      -0.523235120354195, -0.60723571429086065, -0.6076870878643299,
      -0.55096823591222, -0.45784951343436592, -0.33696657548035713,
      -0.23216375521594909, -0.15344774162650784, -0.082229803500705342,
      -0.012878676221653087, 0.04650748343472505, 0.093362802075616411,
      0.12771202090697811, 0.15072113306349455, 0.16398951789391145,
      0.16920823411496094, 0.16799834857389684, 0.16183775763381375,
      0.15203179362882352, 0.13970585886917028, 0.12580944768596944,
      0.11112624377464499, 0.096287513077991216, 0.081787220077290071,
      0.067997886993126949, 0.055186526311956564, 0.043530161911689159,
      0.033130581600747812, 0.024028063342310037, 0.016213900112101561,
      0.0096416186616122019, 0.0042368465363723596, -9.4169577269645062E-5,
      -0.003457352350333343, -0.0059648177880621059, -0.0077300420164466655,
      -0.0088640642063435721, -0.0094726111916343947, -0.0096540266233755036,
      -0.0094978889872281615, -0.0090842074440680015, -0.0084830914450825783,
      -0.0077547987086612124, -0.00695007575780448, -0.0061107153590699084,
      -0.0052702653650396848, -0.004454833418240745, -0.0036839413876824513,
      -0.0029713921608743657, -0.0023261193588959422, -0.0017529976244401086,
      -0.0012535973231821002, -0.00082687280895566415, -0.00046977785959699937,
      -0.00017780555564062244, 5.4547198593454322E-5, 0.00023338803955145796,
      0.00036510623765451491, 0.00045611317316823205, 0.00051264009997659284,
      0.00054058669488550939, 0.00054541378633238594, 0.000532073768688989,
      0.00050497249894296443, 0.00046795688685129184, 0.00042432288799156709,
      0.0003768391559677369, 0.00032778217734989843, 0.00027897927654613441,
      0.00023185641982610548, 0.00018748825235836785, 0.00014664825737522403,
      0.00010985732259602777, 7.7429325161243979E-5, 4.9512591888764234E-5,
      2.6126242707011752E-5, 7.1904659392062875E-6, -7.4503124488415915E-6,
      -1.8012623003939951E-5, -2.4769087471981145E-5, -2.8055347473103545E-5,
      -2.8290457854873571E-5, -2.6010732545924694E-5, -2.1911427963403032E-5,
      -1.687576653635415E-5, -1.1935136231069677E-5, -8.02373047700059E-6, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359877559829882,
      0.52359877559829882, 0.52359877559829859, 0.52359877559829859,
      0.52359877559829859, 0.52359877559829859, 0.52359877559829859,
      0.52359877559829837, 0.52359877559829815, 0.52359877559829771,
      0.52359877559829548, 0.388606121277404, 0.10951766372501204,
      -0.11003765221488804, -0.27691054231834039, -0.39790613003678332,
      -0.47963605946625437, -0.52359877303297353, -0.523598775598013,
      -0.523598775598036, -0.52359877556252854, -0.5034343603283038,
      -0.46496995813135161, -0.4207730300695291, -0.37347825138717894,
      -0.32522954476034893, -0.27772317724492029, -0.23225508112910864,
      -0.18977001053991005, -0.15091060287218283, -0.11606484358328473,
      -0.085410818060040916, -0.058957969215634676, -0.036584363657828467,
      -0.018069704858730162, -0.003124022327003706, 0.0085878843803844918,
      0.017426054273942615, 0.02375875142724182, 0.027949299309182662,
      0.030346000184618194, 0.031274762603571982, 0.03103406059176439,
      0.029891860220957467, 0.028084169840618012, 0.025814896851072189,
      0.023256724335176227, 0.020552753346721908, 0.017818689723081649,
      0.015145386797597138, 0.012601586458064529, 0.010236729995111715,
      0.0080837366777457564, 0.0061616717252570563, 0.0044782461999463008,
      0.003032109322807508, 0.0018149089022696518, 0.00081310811851054154,
      9.5570236664510588E-6, -0.00061517496743790367, -0.0010816933631545567,
      -0.0014108831698587121, -0.0016232044682481517, -0.0017381581204108931,
      -0.0017739001480926442, -0.0017469835244707799, -0.0016722069318741983,
      -0.0015625512957277987, -0.0014291864719969682, -0.0012815322244001948,
      -0.0011273594817051702, -0.00097291973629753947, -0.00082309227167365329,
      -0.00068154064237391232, -0.00055087144216192652, -0.00043278986322770052,
      -0.0003282478585878712, -0.00023758186718814134, -0.00016063804821619954,
      -9.688380444772271E-5, -4.55050644339039E-5, -5.4893531510336047E-6,
      2.4304874346237071E-5, 4.5091814721787138E-5, 5.811372432551476E-5,
      6.4606854966342553E-5, 6.577644529104365E-5, 6.2779129604839667E-5,
      5.671093514758585E-5, 4.8598784535114348E-5, 3.939306037981094E-5,
      2.9958290796217035E-5, 2.1058387479122587E-5, 1.3332252033482206E-5,
      7.2554315453388085E-6, 3.0850963405049114E-6, 7.9190416280017217E-7, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopterD3_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD3_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD3_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/            ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "u_vec.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterD3_M, "Error creating .mat file u_vec.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 1 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterD3_M,
                        "Error writing mat file header to file u_vec.mat");
      return;
    }

    helicopterD3_DW._IWORK_f.Count = 0;
    helicopterD3_DW._IWORK_f.Decimation = -1;
    helicopterD3_DW._PWORK_f.FilePtr = fp;
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

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopterD3_DW.TimeStampA = (rtInf);
  helicopterD3_DW.TimeStampB = (rtInf);
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

  /* Terminate for ToFile: '<Root>/       ' */
  {
    FILE *fp = (FILE *) helicopterD3_DW._PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "x_enc.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD3_M, "Error closing MAT-file x_enc.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterD3_M, "Error reopening MAT-file x_enc.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1, helicopterD3_DW._IWORK.Count, "ans"))
      {
        rtmSetErrorStatus(helicopterD3_M,
                          "Error writing header for ans to MAT-file x_enc.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD3_M, "Error closing MAT-file x_enc.mat");
        return;
      }

      helicopterD3_DW._PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/            ' */
  {
    FILE *fp = (FILE *) helicopterD3_DW._PWORK_f.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "u_vec.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD3_M, "Error closing MAT-file u_vec.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterD3_M, "Error reopening MAT-file u_vec.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 1 + 1, helicopterD3_DW._IWORK_f.Count,
           "ans")) {
        rtmSetErrorStatus(helicopterD3_M,
                          "Error writing header for ans to MAT-file u_vec.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD3_M, "Error closing MAT-file u_vec.mat");
        return;
      }

      helicopterD3_DW._PWORK_f.FilePtr = (NULL);
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

  rtmSetTFinal(helicopterD3_M, 25.0);
  helicopterD3_M->Timing.stepSize0 = 0.002;
  helicopterD3_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopterD3_M->Sizes.checksums[0] = (3993181117U);
  helicopterD3_M->Sizes.checksums[1] = (2093805055U);
  helicopterD3_M->Sizes.checksums[2] = (241788468U);
  helicopterD3_M->Sizes.checksums[3] = (1017237816U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopterD3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&helicopterD3_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopterD3_M->extModeInfo,
      &helicopterD3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopterD3_M->extModeInfo,
                        helicopterD3_M->Sizes.checksums);
    rteiSetTPtr(helicopterD3_M->extModeInfo, rtmGetTPtr(helicopterD3_M));
  }

  helicopterD3_M->solverInfoPtr = (&helicopterD3_M->solverInfo);
  helicopterD3_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterD3_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterD3_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterD3_M->blockIO = ((void *) &helicopterD3_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopterD3_B.Gain1[i] = 0.0;
    }

    helicopterD3_B.TravelCounttorad = 0.0;
    helicopterD3_B.Gain = 0.0;
    helicopterD3_B.Sum4 = 0.0;
    helicopterD3_B.Gain_d = 0.0;
    helicopterD3_B.PitchCounttorad = 0.0;
    helicopterD3_B.Gain_i = 0.0;
    helicopterD3_B.Gain_b = 0.0;
    helicopterD3_B.ElevationCounttorad = 0.0;
    helicopterD3_B.Gain_e = 0.0;
    helicopterD3_B.Sum = 0.0;
    helicopterD3_B.Gain_dg = 0.0;
    helicopterD3_B.u = 0.0;
    helicopterD3_B.Gain_l = 0.0;
    helicopterD3_B.BackmotorSaturation = 0.0;
    helicopterD3_B.FrontmotorSaturation = 0.0;
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

  helicopterD3_DW.TimeStampA = 0.0;
  helicopterD3_DW.LastUAtTimeA = 0.0;
  helicopterD3_DW.TimeStampB = 0.0;
  helicopterD3_DW.LastUAtTimeB = 0.0;
  helicopterD3_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterD3_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopterD3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopterD3_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterD3_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterD3_M->Sizes.numY = (0);    /* Number of model outputs */
  helicopterD3_M->Sizes.numU = (0);    /* Number of model inputs */
  helicopterD3_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterD3_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterD3_M->Sizes.numBlocks = (65);/* Number of blocks */
  helicopterD3_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  helicopterD3_M->Sizes.numBlockPrms = (149);/* Sum of parameter "widths" */
  return helicopterD3_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

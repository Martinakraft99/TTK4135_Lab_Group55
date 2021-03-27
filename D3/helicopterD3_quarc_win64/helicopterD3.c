/*
 * helicopterD3.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD3".
 *
 * Model version              : 11.6
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Sat Mar 27 15:01:32 2021
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
      3.1415926535897931, 3.1378421413626678, 3.1262155534585028,
      3.1033093000313436, 3.0666274151941342, 3.014453922399591,
      2.9456562771266168, 2.8595077633076316, 2.7555515879860746,
      2.633505110520368, 2.4931956060744582, 2.3345185761233522,
      2.1574113215536808, 1.961836484148447, 1.7511937945163805,
      1.5333134234609245, 1.3157801403603693, 1.104568564863847,
      0.90395638584884663, 0.71684173863678669, 0.54511857119567664,
      0.38999354035523631, 0.25222104936729306, 0.13226592811700444,
      0.030411282493045439, -0.053172082069362504, -0.11838191912621635,
      -0.16515742623854598, -0.19346265029411641, -0.20327643561504646,
      -0.19458638682461735, -0.16738526920269345, -0.12783115851139037,
      -0.084038865368926907, -0.043071863568099146, -0.010245243815160699,
      0.01073109574127471, 0.017384085624029041, 0.0128514945645418,
      0.004098001486342622, -0.0021647118775279129, -0.0021173977919048078,
      0.00037271033536781154, 0.00023582456581670727, -4.9577270425100854E-5,
      -1.2049043602948408E-6, 1.6523869218854808E-6, -4.2121232705397079E-7,
      -7.8062622063483E-8, 1.8240026045824262E-8, 3.2050121149272856E-8,
      -6.2110995108397706E-9, -7.4806830501935834E-9, 5.7103469477556136E-10,
      3.0209932370333447E-9, -1.8028117641198509E-9, 5.7547837785127923E-10,
      1.5564431726301007E-9, -3.8621304082060762E-9, 4.0069162961624491E-9,
      -2.2107063736839852E-9, 5.9836617848070508E-10, -5.1324116683677793E-11,
      7.082784036921579E-13, -5.71989451748791E-12, -3.0799430251715507E-11,
      4.1537797825116358E-11, 1.629870463732711E-10, -6.0295678406247277E-10,
      8.1089595760637284E-10, -4.1079989114019738E-10, -1.9135612015943444E-10,
      4.0070448664030272E-10, -2.3920033970745215E-10, 5.7076126941088241E-11,
      8.35085555106497E-12, -9.1955746657951342E-12, -3.376449034802859E-13,
      1.6275339245042879E-12, 4.2410672706714967E-13, -3.6917062738054713E-13,
      -2.365536540759749E-13, -2.8061449323371904E-14, 3.1102652151361812E-14,
      7.1932508434148973E-14, 9.8998034791107841E-14, 8.4743101588812839E-14,
      5.3574726567190347E-14, 3.3605286624913279E-14, 2.6892180257729174E-14,
      2.4761791819208128E-14, 2.3326016984052386E-14, 2.2599812641934282E-14,
      1.3802268164529944E-14, -3.3958789236954168E-14, 7.8251603351949917E-14,
      -8.3236800246551057E-14, -3.6083977585485106E-15, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.015002048908273845,
      -0.04650635161641635, -0.091625013708524813, -0.14672753934887803,
      -0.20869397117813243, -0.27519058109172745, -0.34459405527602055,
      -0.41582470128606025, -0.488185909862881, -0.56123801778352811,
      -0.63470811980436292, -0.70842901827868265, -0.78229934962091974,
      -0.84257075852826113, -0.87152148422180387, -0.8701331324021786,
      -0.84484630198607447, -0.80244871605998647, -0.74845858884828043,
      -0.68689266976439367, -0.62050012336171945, -0.55108996395172616,
      -0.47982048500115815, -0.407418582495855, -0.33433345824977095,
      -0.26083934822738652, -0.18710202844938403, -0.11322089622226482,
      -0.039255141283677242, 0.034760195161663968, 0.10880447048774894,
      0.15821644276518326, 0.17516917256978687, 0.16386800720325673,
      0.13130647901172149, 0.0839053582257576, 0.026611959530994808,
      -0.018130364237960592, -0.03501397231276026, -0.025050853455406797,
      0.00018925634245236289, 0.0099604325089778165, -0.00054754307818317613,
      -0.0011416073449708616, 0.0001934894642531651, 1.1429165131699137E-5,
      -8.2943969921524E-6, 1.3725988179081653E-6, 3.8521059108745061E-7,
      5.5240380401835228E-8, -1.5304488201768409E-7, -5.0783341787281753E-9,
      3.220687088416753E-8, 9.7998342489019932E-9, -1.9295220013141682E-8,
      9.5131605760556132E-9, 3.9238591307846819E-9, -2.16742943327547E-8,
      3.1476186828797357E-8, -2.4870490677150697E-8, 1.1236290203662807E-8,
      -2.5987611826348586E-9, 2.081295797611858E-10, -2.571269109746866E-11,
      -1.0031814269347347E-10, 2.8934891171503538E-10, 4.8579699040857733E-10,
      -3.063775323644656E-9, 5.6554109735811105E-9, -4.8867834015608946E-9,
      8.77775083967084E-10, 2.3682424319571651E-9, -2.5596193053516254E-9,
      1.1851058662903616E-9, -1.9490108532908558E-10, -7.01857211421512E-11,
      3.5431719218015565E-11, 7.8607152872232263E-12, -4.8137090064724091E-12,
      -3.1731093375291589E-12, 5.3046801905702439E-13, 8.3396855638142075E-13,
      2.366565105474255E-13, 1.6331958573875592E-13, 1.0826214171895873E-13,
      -5.7019696202483426E-14, -1.2467350509198568E-13, -7.987774374322773E-14,
      -2.6852422590638938E-14, -8.5215434898364685E-15, -5.7431021367222271E-15,
      -2.9047971323620912E-15, -3.5190153149438336E-14, -1.9104424778129737E-13,
      4.488415734684511E-13, -6.4595361982639418E-13, 3.1851360727127375E-13,
      2.2477601811329641E-10, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.10602875205458229, 0.22266037931401239, 0.31888147180196358,
      0.38944360629167818, 0.43795507375131382, 0.46997264227186109,
      0.49051724873530078, 0.5034310013639135, 0.51142138579451413,
      0.51630439848889764, 0.51925862114583576, 0.52103115469381589,
      0.52208728913294078, 0.42597529910737031, 0.20461267224783186,
      -0.0098123404172798523, -0.17871765975380366, -0.29964994470350642,
      -0.38158159905070854, -0.43512440263111196, -0.46923716111974778,
      -0.4905644973580669, -0.50370545775289211, -0.51170899494020516,
      -0.5165377452667016, -0.5194283005308864, -0.52114721419888643,
      -0.52216362566322272, -0.52276170666844513, -0.52311212981969613,
      -0.52331665877778788, -0.34922494847887847, -0.11981541961786601,
      0.079872320633225025, 0.23013244525417464, 0.33501301812755979,
      0.4049278602950328, 0.31622165626721677, 0.11932689363089088,
      -0.070415518936986332, -0.17838745626799951, -0.069058941306169075,
      0.07426635821004457, 0.004198619350851307, -0.00943595434296185,
      0.0012867326611433194, 0.00013939860420597583, -6.8322634343309652E-5,
      6.9784828938823651E-6, 2.3321034228196424E-6, 1.4720806922330354E-6,
      -1.0457710495348493E-6, -2.6351758952714022E-7, 1.5836437805560877E-7,
      2.056327315091977E-7, -2.0360663077756413E-7, 3.9503048054889689E-8,
      1.8091797271413412E-7, -3.7564730115402512E-7, 3.9823679698347547E-7,
      -2.5518893709275403E-7, 9.7780859631413364E-8, -1.9838031550811763E-8,
      1.6527081925232778E-9, 5.2728321708883641E-10, -2.7540176805729288E-9,
      -1.3884196015112593E-9, 2.5087021793268605E-8, -6.1623878333527671E-8,
      7.4508203828926867E-8, -4.0741697349133688E-8, -1.0534053629385198E-8,
      3.482824495470993E-8, -2.6466286939808015E-8, 9.75336245101488E-9,
      -8.8144014309676777E-10, -7.4646333558803235E-10, 1.9486168234550405E-10,
      8.9578344741880755E-11, -1.1594725179975285E-11, -2.6175173140075003E-11,
      -2.1446178166684149E-12, 4.2219561180445453E-12, 5.1869619710487314E-13,
      3.8946623703850491E-13, 1.1685097334179773E-12, 4.7850612361344247E-13,
      -3.1619151741324458E-13, -3.7436720390360279E-13, -1.2911893776390571E-13,
      -1.9317880628477724E-14, -1.9761969838327786E-14, 2.2859492077031973E-13,
      1.1018963519404679E-12, -4.5221604239031876E-12, 7.7379214147299535E-12,
      -6.8161032373836861E-12, -1.5863799163184922E-9, -2.4411657140177567E-9,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.42411500821839504,
      0.46652650903756443, 0.38488436995186237, 0.28224853795882826,
      0.19404586983848868, 0.1280702740821559, 0.082178425853774689,
      0.0516550105144487, 0.031961537722395246, 0.019532050777538505,
      0.01181689062775166, 0.0070901341919200793, 0.0042245377565002388,
      -0.38444796010228077, -0.88545050743813669, -0.85770005066039745,
      -0.675621277346057, -0.48372913979883131, -0.32772661738883724,
      -0.21417121432164551, -0.13645103395453598, -0.0853093449532918,
      -0.052563841579299719, -0.032014148749251944, -0.019315001306008352,
      -0.011562221056731837, -0.0068756546719773905, -0.0040656458573454816,
      -0.0023923240208495382, -0.0014016926049905888, -0.00081811583239960433,
      0.69636684119564507, 0.91763811544401419, 0.798750961004429,
      0.60104049848379815, 0.419522291493583, 0.27965936866990015,
      -0.3548248161112561, -0.78757905054536947, -0.7589696502714951,
      -0.43188774932407864, 0.43731405984734628, 0.5733011980648367,
      -0.28027095543675529, -0.054538294775258747, 0.042890748016425589,
      -0.0045893362277597619, -0.00083088495419720654, 0.00030120446894854082,
      -1.8585517884009296E-5, -3.4400909225794254E-6, -1.0071406967075683E-5,
      3.1290138399060982E-6, 1.6875278700128427E-6, 1.8907341360973058E-7,
      -1.636957448960735E-6, 9.7243871538434622E-7, 5.6565969881500087E-7,
      -2.2262610957500555E-6, 3.0955363922757509E-6, -2.6137029358947004E-6,
      1.4118791863514271E-6, -4.7047556444937053E-7, 8.5962959240286767E-8,
      -4.5016996706861946E-9, -1.3125203517066561E-8, 5.4623921478423081E-9,
      1.0590176561456482E-7, -3.4684360016340529E-7, 5.44528328404413E-7,
      -4.6099960451344184E-7, 1.2083057494408105E-7, 1.8144919444691712E-7,
      -2.4517812789495845E-7, 1.4487859735612426E-7, -4.2539210093492144E-8,
      5.3990713234110734E-10, 3.7653002044713983E-9, -4.2113359075071665E-10,
      -4.0469210459556539E-10, -5.83214383084874E-11, 9.6121769611558635E-11,
      2.5466550891503233E-11, -1.4813280236653661E-11, -5.1679279085871665E-13,
      3.1158959727386023E-12, -2.760026378137109E-12, -3.1790921563326282E-12,
      -2.3259163135615645E-13, 9.8077045822643713E-13, 4.39659844856015E-13,
      -1.6398331044724212E-15, 9.9296492546319515E-13, 3.4936769209178871E-12,
      -2.2496255980164752E-11, 4.9040553857787648E-11, -5.8216154529481318E-11,
      -6.3182552831180256E-9, -3.4191435644938257E-9, 9.4305337576859617E-10,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0 } ;

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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5235987755782654,
      0.523598775574922, 0.52359877557069889, 0.52359877556531986,
      0.52359877555827794, 0.52359877554887369, 0.5235987755359558,
      0.52359877551763889, 0.52359877548955736, 0.52359877544453071,
      0.5235987753624135, 0.52359877519154907, 0.52359877464868954,
      0.045882495585259253, -0.52359877435830138, -0.52359877486371076,
      -0.52359877501144925, -0.52359877506447006, -0.5235987750735035,
      -0.52359877505261809, -0.5235987750042489, -0.52359877492473228,
      -0.52359877480367034, -0.52359877463129989, -0.52359877433447211,
      -0.5235987738613862, -0.52359877312638547, -0.523598770148235,
      -0.52359876905701974, -0.52359876171631914, -0.52359867774483237,
      0.33670102175917105, 0.52359868853635028, 0.52359869282980342,
      0.52359865739860745, 0.5235985448865369, 0.52359804960052136,
      -0.13756815838879227, -0.52358642233982955, -0.523545930420378,
      -0.32016790179741889, 0.52279785733432227, 0.4754024104975596,
      -0.48585039222374776, 0.041536482615493253, 0.063883282923630325,
      -0.020396955613830037, 0.00082753348655140169, 0.00061383436268502845,
      -0.00012845345505785311, 5.0259654443829405E-6, -9.6770297558501639E-6,
      6.5784443177285823E-6, 6.512986862050596E-7, -2.3843039620441431E-7,
      -1.8859131408754948E-6, 1.6082678676587747E-6, 3.7468451397071334E-7,
      -2.7788019713037571E-6, 4.2774148886204344E-6, -3.9846060359005619E-6,
      2.4639768956280506E-6, -1.010329039652369E-6, 2.6199137270754846E-7,
      -3.6008396486764127E-8, -1.3995481440431945E-8, 8.89137274917573E-9,
      1.2731453347125665E-7, -4.4266468712805818E-7, 7.4016441486968176E-7,
      -6.9798491197925472E-7, 2.805952845630344E-7, 1.6835229887934844E-7,
      -3.3562423562560895E-7, 2.4395961550904843E-7, -9.6870076959909568E-8,
      1.5671668740502298E-8, 3.7004234121340573E-9, -1.731233267854293E-9,
      -2.5276636339555125E-10, 6.7538530323929535E-11, 1.142742567239452E-10,
      -6.6018301936310309E-12, -2.3576696150939824E-11, 5.4127813342574882E-12,
      4.429234756742062E-12, -3.4026115258711798E-12, -2.4155122346769531E-12,
      5.8386628865036982E-13, 9.2337248958074269E-13, 4.7406523151494184E-14,
      -1.8551826741486366E-13, 1.2068124277675452E-12, 4.1708858589117881E-12,
      -2.7975954886017007E-11, 6.4423133494528884E-11, -8.2448381455435538E-11,
      -7.7853898883262218E-9, -3.4479494814831924E-9, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0 } ;

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
  helicopterD3_M->Sizes.checksums[0] = (1983878486U);
  helicopterD3_M->Sizes.checksums[1] = (264031718U);
  helicopterD3_M->Sizes.checksums[2] = (576712663U);
  helicopterD3_M->Sizes.checksums[3] = (2894294489U);

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

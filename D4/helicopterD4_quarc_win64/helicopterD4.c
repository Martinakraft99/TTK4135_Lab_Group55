/*
 * helicopterD4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD4".
 *
 * Model version              : 11.12
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Sat Mar 27 15:43:06 2021
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "helicopterD4.h"
#include "helicopterD4_private.h"
#include "helicopterD4_dt.h"

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
  real_T lastTime;
  real_T rtb_Backgain;
  real_T rtb_Clock;
  real_T rtb_Derivative;
  real_T *lastU;
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

  /* Reset subsysRan breadcrumbs */
  srClearBC(helicopterD4_DW.IfActionSubsystem_SubsysRanBC);
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

    /* Gain: '<S13>/Gain' */
    helicopterD4_B.Gain = helicopterD4_P.Gain_Gain *
      helicopterD4_B.TravelCounttorad;

    /* Sum: '<Root>/Sum4' incorporates:
     *  Constant: '<Root>/Pi'
     */
    helicopterD4_B.Sum4 = helicopterD4_P.Pi_Value + helicopterD4_B.Gain;

    /* Gain: '<S4>/Pitch: Count to rad' */
    helicopterD4_B.PitchCounttorad = helicopterD4_P.PitchCounttorad_Gain *
      rtb_HILReadEncoderTimebase_o2;

    /* Gain: '<S10>/Gain' */
    helicopterD4_B.Gain_i = helicopterD4_P.Gain_Gain_a *
      helicopterD4_B.PitchCounttorad;
  }

  /* Gain: '<S14>/Gain' incorporates:
   *  TransferFcn: '<S4>/Travel: Transfer Fcn'
   */
  helicopterD4_B.Gain_d = (helicopterD4_P.TravelTransferFcn_C *
    helicopterD4_X.TravelTransferFcn_CSTATE + helicopterD4_P.TravelTransferFcn_D
    * helicopterD4_B.TravelCounttorad) * helicopterD4_P.Gain_Gain_l;

  /* Gain: '<S11>/Gain' incorporates:
   *  TransferFcn: '<S4>/Pitch: Transfer Fcn'
   */
  helicopterD4_B.Gain_b = (helicopterD4_P.PitchTransferFcn_C *
    helicopterD4_X.PitchTransferFcn_CSTATE + helicopterD4_P.PitchTransferFcn_D *
    helicopterD4_B.PitchCounttorad) * helicopterD4_P.Gain_Gain_ae;
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    /* Gain: '<S4>/Elevation: Count to rad' incorporates:
     *  Gain: '<S4>/Elevation_gain'
     */
    helicopterD4_B.ElevationCounttorad = helicopterD4_P.elevation_gain *
      rtb_HILReadEncoderTimebase_o3 * helicopterD4_P.ElevationCounttorad_Gain;

    /* Gain: '<S8>/Gain' */
    helicopterD4_B.Gain_e = helicopterD4_P.Gain_Gain_lv *
      helicopterD4_B.ElevationCounttorad;

    /* Sum: '<Root>/Sum' incorporates:
     *  Constant: '<Root>/elavation_offset [deg]'
     */
    helicopterD4_B.Sum = helicopterD4_B.Gain_e +
      helicopterD4_P.elavation_offsetdeg_Value;
  }

  /* Gain: '<S9>/Gain' incorporates:
   *  TransferFcn: '<S4>/Elevation: Transfer Fcn'
   */
  helicopterD4_B.Gain_dg = (helicopterD4_P.ElevationTransferFcn_C *
    helicopterD4_X.ElevationTransferFcn_CSTATE +
    helicopterD4_P.ElevationTransferFcn_D * helicopterD4_B.ElevationCounttorad) *
    helicopterD4_P.Gain_Gain_n;

  /* Gain: '<S2>/Gain1' */
  helicopterD4_B.Gain1[0] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Sum4;
  helicopterD4_B.Gain1[1] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Gain_d;
  helicopterD4_B.Gain1[2] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Gain_i;
  helicopterD4_B.Gain1[3] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Gain_b;
  helicopterD4_B.Gain1[4] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Sum;
  helicopterD4_B.Gain1[5] = helicopterD4_P.Gain1_Gain * helicopterD4_B.Gain_dg;
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    /* ToFile: '<Root>/       ' */
    {
      if (!(++helicopterD4_DW._IWORK.Decimation % 1) &&
          (helicopterD4_DW._IWORK.Count * (6 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterD4_DW._PWORK.FilePtr;
        if (fp != (NULL)) {
          real_T u[6 + 1];
          helicopterD4_DW._IWORK.Decimation = 0;
          u[0] = helicopterD4_M->Timing.t[1];
          u[1] = helicopterD4_B.Gain1[0];
          u[2] = helicopterD4_B.Gain1[1];
          u[3] = helicopterD4_B.Gain1[2];
          u[4] = helicopterD4_B.Gain1[3];
          u[5] = helicopterD4_B.Gain1[4];
          u[6] = helicopterD4_B.Gain1[5];
          if (fwrite(u, sizeof(real_T), 6 + 1, fp) != 6 + 1) {
            rtmSetErrorStatus(helicopterD4_M,
                              "Error writing to MAT-file x_enc.mat");
            return;
          }

          if (((++helicopterD4_DW._IWORK.Count) * (6 + 1))+1 >= 100000000) {
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
    rtb_Sum[i] = helicopterD4_B.Gain1[i] - rtb_Sum[i];
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

  for (i = 0; i < 2; i++) {
    /* Sum: '<Root>/Sum3' incorporates:
     *  Gain: '<S6>/Gain'
     */
    rtb_Clock = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      rtb_Clock += helicopterD4_P.K[(i_0 << 1) + i] * rtb_Sum[i_0];
    }

    helicopterD4_B.u[i] = rtb_u[i] - rtb_Clock;

    /* End of Sum: '<Root>/Sum3' */
  }

  if (rtmIsMajorTimeStep(helicopterD4_M)) {
    /* ToFile: '<Root>/            ' */
    {
      if (!(++helicopterD4_DW._IWORK_b.Decimation % 1) &&
          (helicopterD4_DW._IWORK_b.Count * (2 + 1)) + 1 < 100000000 ) {
        FILE *fp = (FILE *) helicopterD4_DW._PWORK_l.FilePtr;
        if (fp != (NULL)) {
          real_T u[2 + 1];
          helicopterD4_DW._IWORK_b.Decimation = 0;
          u[0] = helicopterD4_M->Timing.t[1];
          u[1] = helicopterD4_B.u[0];
          u[2] = helicopterD4_B.u[1];
          if (fwrite(u, sizeof(real_T), 2 + 1, fp) != 2 + 1) {
            rtmSetErrorStatus(helicopterD4_M,
                              "Error writing to MAT-file u_vec.mat");
            return;
          }

          if (((++helicopterD4_DW._IWORK_b.Count) * (2 + 1))+1 >= 100000000) {
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

  /* Sum: '<Root>/Sum1' incorporates:
   *  Constant: '<Root>/Vd_bias'
   *  Gain: '<S5>/K_pd'
   *  Gain: '<S5>/K_pp'
   *  Sum: '<S5>/Sum2'
   *  Sum: '<S5>/Sum3'
   */
  rtb_Clock = ((helicopterD4_B.u[0] - helicopterD4_B.Gain1[2]) *
               helicopterD4_P.K_pp - helicopterD4_P.K_pd * helicopterD4_B.Gain1
               [3]) + helicopterD4_P.Vd_ff;

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
  rtb_Derivative = helicopterD4_B.u[1] - helicopterD4_B.Gain1[4];

  /* Sum: '<Root>/Sum2' incorporates:
   *  Constant: '<Root>/Vs_bias'
   *  Gain: '<S3>/K_ed'
   *  Gain: '<S3>/K_ep'
   *  Integrator: '<S3>/Integrator'
   *  Sum: '<S3>/Sum1'
   */
  rtb_Backgain = ((helicopterD4_P.K_ep * rtb_Derivative +
                   helicopterD4_X.Integrator_CSTATE) - helicopterD4_P.K_ed *
                  helicopterD4_B.Gain1[5]) + helicopterD4_P.Vs_ff;

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
    helicopterD4_B.In1 = helicopterD4_P.K_ei * rtb_Derivative;
    if (rtmIsMajorTimeStep(helicopterD4_M)) {
      srUpdateBC(helicopterD4_DW.IfActionSubsystem_SubsysRanBC);
    }

    /* End of Outputs for SubSystem: '<S3>/If Action Subsystem' */
  }

  /* End of If: '<S3>/If' */
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
  }

  /* Derivative: '<S4>/Derivative' */
  rtb_Derivative = helicopterD4_M->Timing.t[0];
  if ((helicopterD4_DW.TimeStampA >= rtb_Derivative) &&
      (helicopterD4_DW.TimeStampB >= rtb_Derivative)) {
    rtb_Derivative = 0.0;
  } else {
    lastTime = helicopterD4_DW.TimeStampA;
    lastU = &helicopterD4_DW.LastUAtTimeA;
    if (helicopterD4_DW.TimeStampA < helicopterD4_DW.TimeStampB) {
      if (helicopterD4_DW.TimeStampB < rtb_Derivative) {
        lastTime = helicopterD4_DW.TimeStampB;
        lastU = &helicopterD4_DW.LastUAtTimeB;
      }
    } else {
      if (helicopterD4_DW.TimeStampA >= rtb_Derivative) {
        lastTime = helicopterD4_DW.TimeStampB;
        lastU = &helicopterD4_DW.LastUAtTimeB;
      }
    }

    rtb_Derivative = (helicopterD4_B.PitchCounttorad - *lastU) / (rtb_Derivative
      - lastTime);
  }

  /* End of Derivative: '<S4>/Derivative' */

  /* Gain: '<S12>/Gain' */
  helicopterD4_B.Gain_l = helicopterD4_P.Gain_Gain_a1 * rtb_Derivative;
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
  }

  /* Gain: '<S1>/Back gain' incorporates:
   *  Sum: '<S1>/Subtract'
   */
  rtb_Derivative = (rtb_Backgain - rtb_Clock) * helicopterD4_P.Backgain_Gain;

  /* Saturate: '<S4>/Back motor: Saturation' */
  if (rtb_Derivative > helicopterD4_P.BackmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD4_B.BackmotorSaturation =
      helicopterD4_P.BackmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterD4_P.BackmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD4_B.BackmotorSaturation =
      helicopterD4_P.BackmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Back motor: Saturation' */
    helicopterD4_B.BackmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Back motor: Saturation' */
  if (rtmIsMajorTimeStep(helicopterD4_M)) {
  }

  /* Gain: '<S1>/Front gain' incorporates:
   *  Sum: '<S1>/Add'
   */
  rtb_Derivative = (rtb_Clock + rtb_Backgain) * helicopterD4_P.Frontgain_Gain;

  /* Saturate: '<S4>/Front motor: Saturation' */
  if (rtb_Derivative > helicopterD4_P.FrontmotorSaturation_UpperSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD4_B.FrontmotorSaturation =
      helicopterD4_P.FrontmotorSaturation_UpperSat;
  } else if (rtb_Derivative < helicopterD4_P.FrontmotorSaturation_LowerSat) {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD4_B.FrontmotorSaturation =
      helicopterD4_P.FrontmotorSaturation_LowerSat;
  } else {
    /* Saturate: '<S4>/Front motor: Saturation' */
    helicopterD4_B.FrontmotorSaturation = rtb_Derivative;
  }

  /* End of Saturate: '<S4>/Front motor: Saturation' */
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
  real_T *lastU;

  /* Update for Derivative: '<S4>/Derivative' */
  if (helicopterD4_DW.TimeStampA == (rtInf)) {
    helicopterD4_DW.TimeStampA = helicopterD4_M->Timing.t[0];
    lastU = &helicopterD4_DW.LastUAtTimeA;
  } else if (helicopterD4_DW.TimeStampB == (rtInf)) {
    helicopterD4_DW.TimeStampB = helicopterD4_M->Timing.t[0];
    lastU = &helicopterD4_DW.LastUAtTimeB;
  } else if (helicopterD4_DW.TimeStampA < helicopterD4_DW.TimeStampB) {
    helicopterD4_DW.TimeStampA = helicopterD4_M->Timing.t[0];
    lastU = &helicopterD4_DW.LastUAtTimeA;
  } else {
    helicopterD4_DW.TimeStampB = helicopterD4_M->Timing.t[0];
    lastU = &helicopterD4_DW.LastUAtTimeB;
  }

  *lastU = helicopterD4_B.PitchCounttorad;

  /* End of Update for Derivative: '<S4>/Derivative' */
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

  /* Start for ToFile: '<Root>/       ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "x_enc.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterD4_M, "Error creating .mat file x_enc.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 6 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterD4_M,
                        "Error writing mat file header to file x_enc.mat");
      return;
    }

    helicopterD4_DW._IWORK.Count = 0;
    helicopterD4_DW._IWORK.Decimation = -1;
    helicopterD4_DW._PWORK.FilePtr = fp;
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
      3.1415926535897931, 3.1415926535640963, 3.1415926535318985,
      3.1415926535117955, 3.13784288444811, 3.126218768727326, 3.103317786670158,
      3.06664513396749, 3.0144861941610088, 2.9457101995644259,
      2.8595930779021534, 2.7556827012275225, 2.6337074787964974,
      2.4935569225614178, 2.336641135044327, 2.1659168202322565,
      1.9852462285376919, 1.7989313219433458, 1.6112000833494744,
      1.4259198521531427, 1.2464294072966642, 1.0754559255380665,
      0.91509482639887219, 0.766834031043732, 0.63160524836202248,
      0.50984913172832, 0.40158672096214215, 0.30649258083533193,
      0.22396634670676713, 0.15320036967705603, 0.093241874452232629,
      0.043048641585853024, 0.0015377631442520178, -0.03237266736183389,
      -0.059728669064694706, -0.081511896816962526, -0.098616998517262716,
      -0.1118342723790198, -0.12183704202983996, -0.12917328552612523,
      -0.1342611700832593, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      -2.5959701874695323E-11, -4.6764758653357805E-11, -0.014999076221853726,
      -0.046496462851555037, -0.091603928205415408, -0.14669061080299869,
      -0.20863575923265298, -0.27510397839511763, -0.34446848667434615,
      -0.41564150672637651, -0.48790088973998386, -0.56060222473737975,
      -0.62766314994541739, -0.68289725921697708, -0.72268236672605513,
      -0.74525962639355992, -0.75092495437551077, -0.74112092478126224,
      -0.71796177942197859, -0.6838939270311063, -0.64144439655431218,
      -0.59304318141911672, -0.54091513072645014, -0.48702446653560705,
      -0.43304964306663624, -0.38037656051042529, -0.33010493651862172,
      -0.28306390812429866, -0.23983398090562705, -0.20077293147264569,
      -0.16604351377402404, -0.13564172203229014, -0.10942400681952537,
      -0.087132911016939082, -0.06842040680860996, -0.052869095453702532,
      -0.040011078608838978, -0.029344973989239086, -0.020351538230757842,
      -0.012508287223992208, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 8.9899010802823638E-12, 0.10600774178705509, 0.22261149900693453,
      0.31880233743798159, 0.3893316336318946, 0.43780465072889191,
      0.46977198719952068, 0.49024185251245167, 0.50302372299822062,
      0.51070172149036885, 0.51382526931226435, 0.47396100721350776,
      0.39037358916385351, 0.28118594505260813, 0.15956744860808428,
      0.040040374507559706, -0.069291136732848646, -0.16367999432800917,
      -0.24077856933565792, -0.30001706888673546, -0.34208130296386197,
      -0.36842115331766573, -0.38087863233907687, -0.38147343797455796,
      -0.37227323036906584, -0.35530063841029619, -0.33246802256933888,
      -0.30553261501119705, -0.27606857901726256, -0.24545426027428802,
      -0.21486825283685843, -0.18529679793135398, -0.15754495161284365,
      -0.13225283297726564, -0.10991072922742316, -0.0908755522672504,
      -0.07538395380606748, -0.063562169131280752, -0.055433102592609494,
      -0.0508946309599458, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.42403096707865351, 0.46641502884633135, 0.3847633536921784,
      0.28211718474581721, 0.19389206836043149, 0.12786934585613488,
      0.0818794612244458, 0.051127481914751818, 0.030711993942849864,
      0.012494191271590949, -0.15945704839172103, -0.33434967219594047,
      -0.43675057644414461, -0.48647398577228707, -0.47810829638889124,
      -0.4373260449406095, -0.37755543035501338, -0.30839430000392043,
      -0.23695399817825255, -0.1682569362824731, -0.1053594013879605,
      -0.049829916056878053, -0.0023792225123672218, 0.03680083045108419,
      0.067890367862554549, 0.091330463388712813, 0.10774163025403576,
      0.11785614399351953, 0.1224572749861403, 0.12234402976067861,
      0.11828581963017586, 0.11100738528001484, 0.10116847454691576,
      0.089368415003115459, 0.076140707844182087, 0.061966393848419253,
      0.047287138703117945, 0.032516266158365642, 0.018153886533150403,
      0.0066434025317080973, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 7.882965302556181E-8, 0.003695920366126251, 0.0064788445774856783,
      0.0077058920000249763, 0.0080244423160218976, 0.0079869716364909891,
      0.0079584691252937677, 0.0084185103020476826, 0.010393141478638158,
      0.015949600921329236, 0.02830284913465159, 0.051557017140346252,
      0.089079635569021792, 0.13857055814153549, 0.18066539196608281,
      0.1580291570767883, 0.10869150825221527, 0.065732746760732985,
      0.036784465258053151, 0.020197845160730855, 0.012064932123063478,
      0.0088239053439565941, 0.0079779784327571115, 0.0080631601296022662,
      0.0083596952471164856, 0.00859219778819091, 0.0087100209799860252,
      0.0087500975768163014, 0.008762758893517528, 0.0087789692635587679,
      0.0088051370504869, 0.0088314068146646135, 0.0088436271913206552,
      0.0088340823807448818, 0.0088058989587559561, 0.008770256291399308,
      0.0087365478256720957, 0.0086992311884209524, 0.0086281826681312047,
      0.0084729831684324779, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.014783365918818457, 0.01113169706860913, 0.0049081901341828729,
      0.0012742016495267358, -0.00014988266867142831, -0.00011401035416883304,
      0.0018401643115378678, 0.0078985245161049943, 0.022225837844287125,
      0.049412993080715124, 0.093016672250887819, 0.1500904737877862,
      0.1979636901730383, 0.16837933504376371, -0.090544939754565693,
      -0.19735059536646068, -0.17183504626786397, -0.11579312654329521,
      -0.066346481037971, -0.032531652777847649, -0.012964107617791624,
      -0.0033837079890331177, 0.0003407265645892849, 0.0011861403455808053,
      0.00093001015562408263, 0.00047129290565677689, 0.000160306688019333,
      5.0645713450936113E-5, 6.4842025852961807E-5, 0.00010467172707267765,
      0.0001050796020875106, 4.8881961535872362E-5, -3.817891349111735E-5,
      -0.00011273349628168025, -0.00014257060090031861, -0.00013483388388540673,
      -0.00014926661579380408, -0.000284194152564612, -0.00062079804460522759,
      -0.0017529880539438045, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.523495021082877,
      0.523471521164274, 0.523442125496794, 0.52340267107410132,
      0.5233459792702575, 0.52325773118579244, 0.52310406633035766,
      0.52278375977984093, 0.521845859610058, 0.51465704630158127,
      0.31229867517096377, 0.12073395158810662, -0.023959498003617668,
      -0.15629175420415561, -0.24901269421883998, -0.32131553324238488,
      -0.37208657099605735, -0.40341305891302087, -0.41814242417496938,
      -0.41924960200605516, -0.4093179426618061, -0.390592384341448,
      -0.36520662356993111, -0.33515177714834554, -0.30220148140747582,
      -0.26790109875915258, -0.23356164592090078, -0.2002680460643573,
      -0.16890093527356509, -0.1401447490634439, -0.11452658539215789,
      -0.092425285778369989, -0.074102062105032493, -0.059703510194450207,
      -0.049285096749598425, -0.042809095814278365, -0.040146540762274606,
      -0.0410783336963942, -0.045164317380787196, -0.049472591631144244,
      -0.049472591631144244, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.092396037038936188, 0.014135563527384702, -0.0073717550346657718,
      -0.0039631079988248618, 0.0019908689929127154, 0.00787393731697277,
      0.019915537195641177, 0.050423631179030169, 0.11771053005736581,
      0.23587745652135103, 0.4120050785487217, 0.61755578928772525,
      0.72599080380736147, 0.39908664120957837, -1.0587578219565918,
      -0.71323230520869552, -0.17587514991810807, 0.029365890289899669,
      0.085291464265132788, 0.082260938866714511, 0.061165870191586577,
      0.039532160605809975, 0.023642351271695058, 0.014113631007308804,
      0.0094276974489946163, 0.0078177380889498833, 0.0078267665675821833,
      0.0084254070581859311, 0.00896543928397848, 0.0091738000299257348,
      0.0090431981637263265, 0.0087166010639982174, 0.0084094814026317074,
      0.0082822138213822644, 0.0083657667222375044, 0.00849782688722827,
      0.0083429669515242885, 0.0075200841416996726, 0.0058849714651941125, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    helicopterD4_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    helicopterD4_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    helicopterD4_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* Start for ToFile: '<Root>/            ' */
  {
    FILE *fp = (NULL);
    char fileName[509] = "u_vec.mat";
    if ((fp = fopen(fileName, "wb")) == (NULL)) {
      rtmSetErrorStatus(helicopterD4_M, "Error creating .mat file u_vec.mat");
      return;
    }

    if (rt_WriteMat4FileHeader(fp, 2 + 1, 0, "ans")) {
      rtmSetErrorStatus(helicopterD4_M,
                        "Error writing mat file header to file u_vec.mat");
      return;
    }

    helicopterD4_DW._IWORK_b.Count = 0;
    helicopterD4_DW._IWORK_b.Decimation = -1;
    helicopterD4_DW._PWORK_l.FilePtr = fp;
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

  /* InitializeConditions for Derivative: '<S4>/Derivative' */
  helicopterD4_DW.TimeStampA = (rtInf);
  helicopterD4_DW.TimeStampB = (rtInf);
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

  /* Terminate for ToFile: '<Root>/       ' */
  {
    FILE *fp = (FILE *) helicopterD4_DW._PWORK.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "x_enc.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD4_M, "Error closing MAT-file x_enc.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterD4_M, "Error reopening MAT-file x_enc.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 6 + 1, helicopterD4_DW._IWORK.Count, "ans"))
      {
        rtmSetErrorStatus(helicopterD4_M,
                          "Error writing header for ans to MAT-file x_enc.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD4_M, "Error closing MAT-file x_enc.mat");
        return;
      }

      helicopterD4_DW._PWORK.FilePtr = (NULL);
    }
  }

  /* Terminate for ToFile: '<Root>/            ' */
  {
    FILE *fp = (FILE *) helicopterD4_DW._PWORK_l.FilePtr;
    if (fp != (NULL)) {
      char fileName[509] = "u_vec.mat";
      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD4_M, "Error closing MAT-file u_vec.mat");
        return;
      }

      if ((fp = fopen(fileName, "r+b")) == (NULL)) {
        rtmSetErrorStatus(helicopterD4_M, "Error reopening MAT-file u_vec.mat");
        return;
      }

      if (rt_WriteMat4FileHeader(fp, 2 + 1, helicopterD4_DW._IWORK_b.Count,
           "ans")) {
        rtmSetErrorStatus(helicopterD4_M,
                          "Error writing header for ans to MAT-file u_vec.mat");
      }

      if (fclose(fp) == EOF) {
        rtmSetErrorStatus(helicopterD4_M, "Error closing MAT-file u_vec.mat");
        return;
      }

      helicopterD4_DW._PWORK_l.FilePtr = (NULL);
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

  /* External mode info */
  helicopterD4_M->Sizes.checksums[0] = (2815837564U);
  helicopterD4_M->Sizes.checksums[1] = (4241144707U);
  helicopterD4_M->Sizes.checksums[2] = (2895534585U);
  helicopterD4_M->Sizes.checksums[3] = (2497324469U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[2];
    helicopterD4_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = (sysRanDType *)&helicopterD4_DW.IfActionSubsystem_SubsysRanBC;
    rteiSetModelMappingInfoPtr(helicopterD4_M->extModeInfo,
      &helicopterD4_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(helicopterD4_M->extModeInfo,
                        helicopterD4_M->Sizes.checksums);
    rteiSetTPtr(helicopterD4_M->extModeInfo, rtmGetTPtr(helicopterD4_M));
  }

  helicopterD4_M->solverInfoPtr = (&helicopterD4_M->solverInfo);
  helicopterD4_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&helicopterD4_M->solverInfo, 0.002);
  rtsiSetSolverMode(&helicopterD4_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  helicopterD4_M->blockIO = ((void *) &helicopterD4_B);

  {
    int32_T i;
    for (i = 0; i < 6; i++) {
      helicopterD4_B.Gain1[i] = 0.0;
    }

    helicopterD4_B.TravelCounttorad = 0.0;
    helicopterD4_B.Gain = 0.0;
    helicopterD4_B.Sum4 = 0.0;
    helicopterD4_B.Gain_d = 0.0;
    helicopterD4_B.PitchCounttorad = 0.0;
    helicopterD4_B.Gain_i = 0.0;
    helicopterD4_B.Gain_b = 0.0;
    helicopterD4_B.ElevationCounttorad = 0.0;
    helicopterD4_B.Gain_e = 0.0;
    helicopterD4_B.Sum = 0.0;
    helicopterD4_B.Gain_dg = 0.0;
    helicopterD4_B.u[0] = 0.0;
    helicopterD4_B.u[1] = 0.0;
    helicopterD4_B.Gain_l = 0.0;
    helicopterD4_B.BackmotorSaturation = 0.0;
    helicopterD4_B.FrontmotorSaturation = 0.0;
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

  helicopterD4_DW.TimeStampA = 0.0;
  helicopterD4_DW.LastUAtTimeA = 0.0;
  helicopterD4_DW.TimeStampB = 0.0;
  helicopterD4_DW.LastUAtTimeB = 0.0;
  helicopterD4_DW.HILWriteAnalog_Buffer[0] = 0.0;
  helicopterD4_DW.HILWriteAnalog_Buffer[1] = 0.0;

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    helicopterD4_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 16;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  helicopterD4_M->Sizes.numContStates = (4);/* Number of continuous states */
  helicopterD4_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  helicopterD4_M->Sizes.numY = (0);    /* Number of model outputs */
  helicopterD4_M->Sizes.numU = (0);    /* Number of model inputs */
  helicopterD4_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  helicopterD4_M->Sizes.numSampTimes = (2);/* Number of sample times */
  helicopterD4_M->Sizes.numBlocks = (68);/* Number of blocks */
  helicopterD4_M->Sizes.numBlockIO = (17);/* Number of block outputs */
  helicopterD4_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return helicopterD4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

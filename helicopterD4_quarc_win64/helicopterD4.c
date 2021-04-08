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
 * C source code generated on : Thu Apr  8 19:37:48 2021
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
              (&helicopterD4_B.x[0])[elIdx] = pDataValues[currTimeIndex];
              pDataValues += 81;
            }
          }
        } else {
          {
            int_T elIdx;
            for (elIdx = 0; elIdx < 6; ++elIdx) {
              (&helicopterD4_B.x[0])[elIdx] = pDataValues[currTimeIndex + 1];
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
            (&helicopterD4_B.x[0])[elIdx] = (real_T) rtInterpolate(d1, d2, f1,
              f2);
            pDataValues += 81;
          }
        }
      }
    }
  }

  for (i = 0; i < 6; i++) {
    /* Sum: '<S6>/Sum' */
    helicopterD4_B.Sum_n[i] = helicopterD4_B.Gain1[i] - helicopterD4_B.x[i];
  }

  for (i = 0; i < 2; i++) {
    /* Gain: '<S6>/Gain' */
    helicopterD4_B.Kxx[i] = 0.0;
    for (i_0 = 0; i_0 < 6; i_0++) {
      helicopterD4_B.Kxx[i] += helicopterD4_P.K[(i_0 << 1) + i] *
        helicopterD4_B.Sum_n[i_0];
    }

    /* End of Gain: '<S6>/Gain' */
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

  /* Sum: '<Root>/Sum3' */
  helicopterD4_B.u[0] = rtb_u[0] - helicopterD4_B.Kxx[0];
  helicopterD4_B.u[1] = rtb_u[1] - helicopterD4_B.Kxx[1];
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
      3.1415926535897931, 3.1415926535898016, 3.1415926535897807,
      3.1415926535897007, 3.1378421415069249, 3.1262155540768823,
      3.103309301647736, 3.0666274185352513, 3.0144539284183036,
      2.9456562870510843, 2.8595077787320755, 2.7555516110379927,
      2.633505144197728, 2.4931956551073111, 2.3345186515385996,
      2.1584795154211363, 1.968119722633964, 1.7680411183810341,
      1.563568425858628, 1.3600205789578412, 1.1622098739746487,
      0.97415620203845088, 0.79885022306074183, 0.63836563570285754,
      0.49404476253114049, 0.36651072283502378, 0.25575302067252081,
      0.16124121789077264, 0.082043411805926128, 0.016938162569321673,
      -0.035485300102423241, -0.076740510855824645, -0.10837102204154581,
      -0.13189082318366371, -0.14873682115591136, -0.1602322032311769,
      -0.1675595438389727, -0.17174278318729239, -0.173637511127814,
      -0.17392950186163172, -0.17314186493814729, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, -7.7153700626625849E-14, -1.5915999217585507E-13,
      -0.01500204833096482, -0.046506349720000749, -0.09162500971644226,
      -0.1467275324498353, -0.20869396046772171, -0.27519056546901927,
      -0.34459403327622706, -0.41582467077665114, -0.48818586736101893,
      -0.56123795636147211, -0.63470801427458334, -0.70415654446972309,
      -0.76143917114892345, -0.80031441701192552, -0.81789077008978206,
      -0.81419138760331033, -0.7912428199329532, -0.75221468774494193,
      -0.70122391591098754, -0.6419383494317733, -0.57728349268703227,
      -0.51013615878466856, -0.44303080865019356, -0.37804721112713974,
      -0.31679122433943657, -0.2604209969463202, -0.20969385068682997,
      -0.16502084301337203, -0.12652204474260398, -0.094079204568113,
      -0.067383991888706946, -0.045981528300724592, -0.029309362430762237,
      -0.01673295739293645, -0.0075789117617936722, -0.0011679629350445924,
      0.0031505476940637805, 0.0059615829176523066, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 3.7387303531794397E-14, 0.10602874797124383,
      0.22266036999345548, 0.31888145699116366, 0.38944358574711985,
      0.43795504681324149, 0.46997260755229747, 0.49051720366604074,
      0.50343094121909771, 0.51142130103751671, 0.51630426476657443,
      0.51925830940929518, 0.49083568741354749, 0.40485172780383594,
      0.27475539040074859, 0.12422295073666551, -0.026145822534957695,
      -0.16219171170425356, -0.27583593255631106, -0.36038330076419106,
      -0.41900774134231844, -0.4569558342825103, -0.47457171089768729,
      -0.47427498566079657, -0.45927924854979718, -0.43293391953334576,
      -0.39840323811723732, -0.35852009588829042, -0.31573175657810837,
      -0.27209480259360491, -0.22929360367991503, -0.18867156769683421,
      -0.15126443854227756, -0.11783250088171086, -0.088885227586191259,
      -0.064697298378194712, -0.045310137817063091, -0.030521583786877918,
      -0.019867323360591081, -0.012621495081439331, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.42411499188469237, 0.46652648808872493,
      0.3848843479907178, 0.282248515023711, 0.19404584426436861,
      0.12807024295609767, 0.082178384454834552, 0.051654950212081815,
      0.031961439273532066, 0.019531854916112396, 0.011816178570849422,
      -0.11369048798266465, -0.34393583843838138, -0.52038534961188709,
      -0.602129758656124, -0.601475093087181, -0.54418355667881013,
      -0.45457688340990282, -0.33818947283276651, -0.23449776231325581,
      -0.1517923717615054, -0.070463506461160383, 0.0011869009473926371,
      0.059982948443918487, 0.1053813160656992, 0.1381227256644427,
      0.15953256891601825, 0.17115335724119057, 0.17454781593863219,
      0.17120479565548952, 0.16248814393301741, 0.14962851661879903,
      0.13372775064270059, 0.11578909318245592, 0.096751716832267839,
      0.077548642244740479, 0.059154216120800768, 0.042617041705136451,
      0.028983313116611203, 0.018990582276157172, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 1.0083683522688197E-10, 0.00421869761666947,
      0.011646552269773998, 0.021584417528436321, 0.033555063936874296,
      0.0472306464878424, 0.062369919947273145, 0.078759982156217739,
      0.096156969136969833, 0.11422102222371022, 0.132438373112736,
      0.1500251752683455, 0.16580334129335522, 0.17803895389941865,
      0.1842293373628491, 0.18082217521703797, 0.17140883471815754,
      0.15852806927345378, 0.14394343977812732, 0.12885171944257104,
      0.11403915181871846, 0.099997836074679131, 0.087011802555645987,
      0.075220532233848864, 0.06466557644341063, 0.055324189437934129,
      0.047133130476123414, 0.04000592779514462, 0.033844656461151916,
      0.028548126275194232, 0.024016870395565774, 0.020156594850656434,
      0.016880228913323504, 0.01410867744377638, 0.011770932296584723,
      0.00980434138899194, 0.0081538161367904188, 0.0067715479167627423,
      0.0056161576103076448, 0.004652141691833098, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.016874790063343983, 0.029711418612427751,
      0.039751461034665793, 0.047882585633791358, 0.054702330203953112,
      0.060557093837869912, 0.065560248836008236, 0.069587947923325372,
      0.072256212347359461, 0.072869403556573634, 0.070347208622976859,
      0.0631126641006388, 0.048942450424900717, 0.024761533854389006,
      -0.013628648583246365, -0.037653361995523417, -0.05152306177882103,
      -0.058338517981320059, -0.060366881342245542, -0.0592502704954304,
      -0.056165262976171221, -0.051944134076133262, -0.047165081287167621,
      -0.042219823161707137, -0.037365548021837919, -0.03276423584715564,
      -0.02850881072380957, -0.0246450853358465, -0.021186120743691361,
      -0.018125023518367374, -0.015441102179486323, -0.013105463749173606,
      -0.011086205878028417, -0.0093509805886124089, -0.0078663636302278243,
      -0.0066021010086795024, -0.0055290728800036467, -0.0046215612257386679,
      -0.0038560636738527452, -0.003212223421960547, 0.0, 0.0, 0.0, 0.0, 0.0,
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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.52359875541318934,
      0.52359875172873771, 0.52359874696116637, 0.52359874064114842,
      0.52359873200596552, 0.52359871973434557, 0.523598701330793,
      0.52359867146166794, 0.52359861632322069, 0.52359848564965672,
      0.52359783570323959, 0.37448685014962, 0.10868202590310676,
      -0.10915414686795387, -0.27427323972076023, -0.39346944567534531,
      -0.47335241638723474, -0.52016869629088891, -0.523588976508981,
      -0.52358755605006779, -0.51883094956680276, -0.48725992564487913,
      -0.44679132614230543, -0.40066521910852282, -0.35157989773324982,
      -0.30176740403392388, -0.25303231910173124, -0.20679817595717412,
      -0.16415900920361653, -0.12591692440318614, -0.09262855028801506,
      -0.064627304636066155, -0.042048235621744735, -0.024824539630944636,
      -0.012680886666851843, -0.0050908194855644705, -0.0012413083827262663,
      5.042730932210631E-7, -1.0789151579127273E-6, -3.4686119931420907E-7,
      -3.4686119931420907E-7, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.10546743789589076, 0.12241590369094635, 0.14124750928669985,
      0.1618447336010243, 0.18391428517653283, 0.20690316215897725,
      0.22989309982125908, 0.25144366133349738, 0.26940650461526472,
      0.28062994506347239, 0.28063081278068519, 0.26309049140607432,
      0.21924300004702521, 0.13702873879022892, 4.1483002292724249E-6,
      3.2570780068570768E-6, 3.1465826090552312E-6, 4.5790054512237726E-6,
      4.5033143177680606E-6, 5.0542150770076243E-6, 7.3401993587603053E-6,
      8.0500035490873944E-6, 6.5808154497719047E-6, 6.9626219744767622E-6,
      1.0193953899258857E-5, 9.9074807210420868E-6, 1.0006841107458399E-5,
      9.3873415381772226E-6, 1.1743156682477857E-5, 1.1212260364745032E-5,
      1.0075847420969472E-5, 1.1855136463397214E-5, 1.3297172544646114E-5,
      9.8722772240267864E-6, 1.0081962254015432E-5, 6.664605765435215E-6,
      5.5146715707508912E-6, 3.0817759905266896E-6, 2.0045517205593615E-6, 0.0,
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

  rtmSetTFinal(helicopterD4_M, 25.0);
  helicopterD4_M->Timing.stepSize0 = 0.002;
  helicopterD4_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  helicopterD4_M->Sizes.checksums[0] = (2752760392U);
  helicopterD4_M->Sizes.checksums[1] = (865314332U);
  helicopterD4_M->Sizes.checksums[2] = (442949977U);
  helicopterD4_M->Sizes.checksums[3] = (2655801359U);

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

    for (i = 0; i < 6; i++) {
      helicopterD4_B.x[i] = 0.0;
    }

    for (i = 0; i < 6; i++) {
      helicopterD4_B.Sum_n[i] = 0.0;
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
    helicopterD4_B.Kxx[0] = 0.0;
    helicopterD4_B.Kxx[1] = 0.0;
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
  helicopterD4_M->Sizes.numBlocks = (71);/* Number of blocks */
  helicopterD4_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  helicopterD4_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return helicopterD4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

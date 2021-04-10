/*
 * helicopterD4.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "helicopterD4".
 *
 * Model version              : 11.13
 * Simulink Coder version : 9.4 (R2020b) 29-Jul-2020
 * C source code generated on : Sat Apr 10 18:17:56 2021
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
      3.1415926535897931, 3.1415926535651613, 3.1415926533405751,
      3.141592652903495, 3.1378421402891572, 3.1262155525686213,
      3.1033093013961368, 3.06935599991589, 3.0300897997183864,
      2.9908198925737728, 2.9515499891269457, 2.9122800837760368,
      2.873010178547037, 2.8337402734500707, 2.7944703684953534,
      2.7552004636942944, 2.7159305590596809, 2.6766606546059082,
      2.6373907503492631, 2.5981208463082881, 2.5588509425041437,
      2.5195810389611517, 2.4803111357075172, 2.4410412327761977,
      2.4017713302058543, 2.3625014280421945, 2.323231526340241,
      2.2839616251684145, 2.2446917246103348, 2.205421824767559,
      2.166151925774491, 2.1268820277984473, 2.0876121310142555,
      2.0483422359175387, 2.0090723428447275, 1.9698024524792006,
      1.930532565904356, 1.8912626850204459, 1.8519928137485817,
      1.8127229600819532, 1.773453173333301, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, -7.9972344176123661E-10, -1.6498364671251261E-9,
      -0.015002050359065306, -0.046506350784136, -0.091625004592268744,
      -0.13581320582377202, -0.15706480069331005, -0.15707962848230017,
      -0.15707961369174581, -0.15707962130869843, -0.15707962082171162,
      -0.15707962029425024, -0.15707961972597165, -0.15707961911207391,
      -0.1570796184470496, -0.15707961772445017, -0.15707961693673239,
      -0.15707961607496068, -0.15707961512851176, -0.1570796140846355,
      -0.15707961292790171, -0.15707961163945708, -0.15707961019603886,
      -0.1570796085685465, -0.15707960672016397, -0.1570796046036313,
      -0.15707960215708702, -0.15707959929830423, -0.15707959591490203,
      -0.15707959185107553, -0.15707958709554573, -0.15707958034857145,
      -0.15707957225210448, -0.15707956143951629, -0.157079546284321,
      -0.15707952353380217, -0.15707948508988, -0.15707941466985645,
      -0.15707914699723668, -0.15706643822841374, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 4.0837409344510616E-10, 0.10602874510599351,
      0.22266035770698372, 0.31888140785953217, 0.31230532454523646,
      0.15019815128891442, 0.00010480667182699123, -1.0613179498763244E-7,
      5.3977628832958941E-8, -3.4612145891970387E-9, -3.72794758383042E-9,
      -4.0163435965999077E-9, -4.3388268079933004E-9, -4.700035717883877E-9,
      -5.1071029328770664E-9, -5.5672418027232461E-9, -6.0906641293602508E-9,
      -6.68913385242031E-9, -7.3777248087353159E-9, -8.1753911367332342E-9,
      -9.1062701400667849E-9, -1.0201421331334176E-8, -1.1502487651541258E-8,
      -1.3063733676614117E-8, -1.4958734597832535E-8, -1.7291325426980577E-8,
      -2.020474612367269E-8, -2.3912951431914889E-8, -2.8721701868026336E-8,
      -3.3606328271586379E-8, -4.7690271336959318E-8, -5.7218638672094016E-8,
      -7.6421842899497391E-8, -1.0711830214248433E-7, -1.6078410928626007E-7,
      -2.7171170307806772E-7, -4.9770215920011684E-7, -1.8918021626324988E-6,
      -8.9820725269233E-5, -9.817350505118586E-5, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.42411497735911319, 0.46652644926282438,
      0.38488419986984229, -0.026304333492837728, -0.648428692733213,
      -0.60037337782573208, -0.00041965133194698742, 6.4044766734439942E-7,
      -2.2975692618324569E-7, -1.0669313749675443E-9, -1.1535780699797994E-9,
      -1.2899278489418905E-9, -1.4448279003591083E-9, -1.6282684840963012E-9,
      -1.8405514181726031E-9, -2.0936891834576056E-9, -2.3938797151346494E-9,
      -2.7543648699003855E-9, -3.1906646314421588E-9, -3.723510610597098E-9,
      -4.3805965355429187E-9, -5.204265446277258E-9, -6.2449836115519937E-9,
      -7.5799976597453249E-9, -9.330364925918474E-9, -1.1653677095001163E-8,
      -1.4832818641211754E-8, -1.9234991340432577E-8, -1.9538567579215362E-8,
      -5.6336170340760094E-8, -3.81135302602014E-8, -7.6813216059882732E-8,
      -1.2278593471055039E-7, -2.1466276249678014E-7, -4.4371046080706545E-7,
      -9.039614563106092E-7, -5.5763996476670526E-6, -0.00035171569253402275,
      -3.3411119148687121E-5, 6.9480485699765907E-5, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 2.1997722216666752E-9,
      0.00022669114745792716, 0.00063432627473564206, 0.001196904320475793,
      0.001903197574850474, 0.0027535360858639371, 0.0037582478989928846,
      0.0049364236648192479, 0.0063153305276375353, 0.0079299320457264563,
      0.0098230269802987817, 0.012045549875158521, 0.014656857556641159,
      0.017724970714282893, 0.021327281099137948, 0.025550268383763897,
      0.03048917810802863, 0.036246927494200325, 0.0429319967563199,
      0.050655001109832905, 0.0595232665057353, 0.069631823603586371,
      0.081051018782441545, 0.093808195702444169, 0.10786193146405854,
      0.12306577471831738, 0.13911861260809238, 0.15549660285037864,
      0.17136082369166564, 0.18543198432833435, 0.19582325436513282,
      0.19981611167643787, 0.19437904804313383, 0.18312426695483786,
      0.16859624797624262, 0.15255444249151973, 0.1361855244073239,
      0.12026192311728789, 0.10526027312614612, 0.09144884281655645, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00090675578935606649,
      0.001630540524261355, 0.0022503121592805909, 0.0028251730398174248,
      0.00340135399732795, 0.0040188472148472024, 0.0047127030484857228,
      0.0055156274374193832, 0.0064584060564820489, 0.007572379730893709,
      0.008890091584519557, 0.010445230736371706, 0.012272452636530524,
      0.014409241541365202, 0.016891949144817894, 0.019755638903217177,
      0.023030997549834693, 0.026740277048892189, 0.030892017414623569,
      0.035473061588422963, 0.040434228399724458, 0.045676780725787243,
      0.051028707693989574, 0.056214943066760011, 0.06081537304344669,
      0.064211351581214229, 0.06551196098085188, 0.063456883373391809,
      0.056284642531767168, 0.041565080122740246, 0.015971429176351051,
      -0.0217482545668685, -0.045019124392589281, -0.058112075927618474,
      -0.0641672219429226, -0.065475672324672843, -0.0636944051435049,
      -0.060006599948430828, -0.05524572122666422, -0.049989076436096708, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0 } ;

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
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.5235987373605504,
      0.52359870590325186, 0.52359856596540122, 0.14266930401369976,
      -0.47840039382165395, -0.34884345139776751, 0.22380023331784818,
      0.00015740615510021042, -4.6885005427502011E-7, 8.10254823133731E-8,
      -4.75366460860494E-9, -5.1780335976785789E-9, -5.6408307787642E-9,
      -6.170660928223772E-9, -6.7713003025077193E-9, -7.46467582179596E-9,
      -8.2641687847411709E-9, -9.1955739538642759E-9, -1.0288180847351146E-8,
      -1.158074179542204E-8, -1.3123841707003538E-8, -1.4990474826777778E-8,
      -1.726877564992512E-8, -2.0089523360799319E-8, -2.3646900623912711E-8,
      -2.8194092911520272E-8, -3.416472144218583E-8, -4.212043682629536E-8,
      -4.565995742231633E-8, -9.5860392102284607E-8, -7.3704994412103487E-8,
      -1.3781605938927058E-7, -1.9932310313506241E-7, -3.2627880615897378E-7,
      -6.2840742277653463E-7, -1.2220068080617487E-6, -7.0445555046371846E-6,
      -0.00043402616213254926, 2.8159302129204666E-7, 8.24816638904252E-8,
      8.24816638904252E-8, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0056672236810133628, 0.0067905462631186481, 0.0081766151617762867,
      0.00985298716637187, 0.011860967873387047, 0.014265915156305389,
      0.01713725307214356, 0.020558282942211206, 0.024617858621791479,
      0.029423681134712845, 0.035096580464246241, 0.04176787564754867,
      0.04957876359669481, 0.058692919807028149, 0.069264997094488912,
      0.08145521495576552, 0.09541035718684085, 0.11124966885451279,
      0.12904599740684689, 0.14879356638675856, 0.17034494766151595,
      0.19337478955477583, 0.21727331898326607, 0.2410367591126702,
      0.26309824073751709, 0.28112522994069944, 0.29172296241732076,
      0.29005428000353989, 0.26931230600086276, 0.22007516493457008,
      0.12938436618328653, 3.803890859392937E-6, 2.5388338579542263E-6,
      2.8996645119882874E-7, -5.8545488374582667E-7, 3.7824369837362311E-7,
      -1.8184274477832096E-6, -1.7059745797033262E-6, 9.1526084542607748E-7, 0.0,
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
  helicopterD4_M->Sizes.checksums[0] = (1899614748U);
  helicopterD4_M->Sizes.checksums[1] = (2151363402U);
  helicopterD4_M->Sizes.checksums[2] = (2246188042U);
  helicopterD4_M->Sizes.checksums[3] = (3898633219U);

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
  helicopterD4_M->Sizes.numBlocks = (70);/* Number of blocks */
  helicopterD4_M->Sizes.numBlockIO = (20);/* Number of block outputs */
  helicopterD4_M->Sizes.numBlockPrms = (156);/* Sum of parameter "widths" */
  return helicopterD4_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/

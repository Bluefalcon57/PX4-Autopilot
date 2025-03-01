/****************************************************************************
 *
 *   Copyright (c) 2014-2022 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file vtol_att_control_params.c
 * Parameters for vtol attitude controller.
 *
 * @author Roman Bapst <roman@px4.io>
 * @author Sander Smeets <sander@droneslab.com>
 */

/**
 * VTOL Type (Tailsitter=0, Tiltrotor=1, Standard=2)
 *
 * @value 0 Tailsitter
 * @value 1 Tiltrotor
 * @value 2 Standard
 * @min 0
 * @max 2
 * @reboot_required true
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_INT32(VT_TYPE, 0);

/**
 * Lock control surfaces in hover
 *
 * If set to 1 the control surfaces are locked at the disarmed value in multicopter mode.
 *
 * @boolean
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_INT32(VT_ELEV_MC_LOCK, 1);

/**
 * Duration of a front transition
 *
 * Time in seconds used for a transition
 *
 * @unit s
 * @min 0.1
 * @max 20.00
 * @increment 1
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_F_TRANS_DUR, 5.0f);

/**
 * Duration of a back transition
 *
 * Time in seconds used for a back transition
 *
 * @unit s
 * @min 0.1
 * @max 20.00
 * @increment 1
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_B_TRANS_DUR, 4.0f);

/**
 * Target throttle value for the transition to fixed wing flight.
 *
 * standard vtol: pusher
 *
 * tailsitter, tiltrotor: main throttle
 *
 * @min 0.0
 * @max 1.0
 * @increment 0.01
 * @decimal 3
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_F_TRANS_THR, 1.0f);

/**
 * Target throttle value for the transition to hover flight.
 *
 * standard vtol: pusher
 *
 * tailsitter, tiltrotor: main throttle
 *
 * Note for standard vtol:
 * For ESCs and mixers that support reverse thrust on low PWM values set this to a negative value to apply active breaking
 * For ESCs that support thrust reversal with a control channel please set VT_B_REV_OUT and set this to a positive value to apply active breaking
 *
 * @min -1
 * @max 1
 * @increment 0.01
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_B_TRANS_THR, 0.0f);

/**
 * Approximate deceleration during back transition
 *
 * The approximate deceleration during a back transition in m/s/s
 * Used to calculate back transition distance in mission mode. A lower value will make the VTOL transition further from the destination waypoint.
 * For standard vtol and tiltrotors a controller is used to track this value during the transition.
 *
 * @unit m/s^2
 * @min 0.5
 * @max 10
 * @increment 0.1
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_B_DEC_MSS, 2.0f);

/**
 * Transition blending airspeed
 *
 * Airspeed at which we can start blending both fw and mc controls. Set to 0 to disable.
 *
 * @unit m/s
 * @min 0.00
 * @max 30.00
 * @increment 1
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_ARSP_BLEND, 8.0f);

/**
 * Transition airspeed
 *
 * Airspeed at which we can switch to fw mode
 *
 * @unit m/s
 * @min 0.00
 * @max 30.00
 * @increment 1
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_ARSP_TRANS, 10.0f);

/**
 * Front transition timeout
 *
 * Time in seconds after which transition will be cancelled. Disabled if set to 0.
 *
 * @unit s
 * @min 0.1
 * @max 30.00
 * @increment 1
 * @decimal 2
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_TRANS_TIMEOUT, 15.0f);

/**
 * Front transition minimum time
 *
 * Minimum time in seconds for front transition.
 *
 * @unit s
 * @min 0.0
 * @max 20.0
 * @increment 0.1
 * @decimal 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_TRANS_MIN_TM, 2.0f);

/**
 * QuadChute Altitude
 *
 * Minimum altitude for fixed wing flight, when in fixed wing the altitude drops below this altitude
 * the vehicle will transition back to MC mode and enter failsafe RTL
 *
 * @unit m
 * @min 0.0
 * @max 200.0
 * @increment 1
 * @decimal 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_FW_MIN_ALT, 0.0f);

/**
 * Adaptive QuadChute
 *
 * Maximum negative altitude error for fixed wing flight. If the altitude drops below this value below the altitude setpoint
 * the vehicle will transition back to MC mode and enter failsafe RTL.
 *
 * @unit m
 * @min 0.0
 * @max 200.0
 * @increment 1
 * @decimal 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_FW_ALT_ERR, 0.0f);

/**
 * Quad-chute max pitch threshold
 *
 * Absolute pitch threshold for quad-chute triggering in FW mode.
 * Above this the vehicle will transition back to MC mode and execute behavior defined in COM_QC_ACT.
 * Set to 0 do disable this threshold.
 *
 * @unit deg
 * @min 0
 * @max 180
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_INT32(VT_FW_QC_P, 0);

/**
 * Quad-chute max roll threshold
 *
 * Absolute roll threshold for quad-chute triggering in FW mode.
 * Above this the vehicle will transition back to MC mode and execute behavior defined in COM_QC_ACT.
 * Set to 0 do disable this threshold.
 *
 * @unit deg
 * @min 0
 * @max 180
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_INT32(VT_FW_QC_R, 0);

/**
 * Quad-chute maximum height
 *
 * Maximum height above the ground (if available, otherwhise above home if available, otherwise above the local origin) where triggering a quadchute is possible.
 * Triggering a quadchute always means transitioning the vehicle to hover flight in which generally a lot of energy is consumed.
 * At high altitudes there is therefore a big risk to deplete the battery and therefore crash. Currently, there is no automated
 * re-transition to fixed wing mode implemented and therefore this parameter serves and an intermediate measure to increase safety.
 * Setting this value to 0 deactivates the behavior (always enable quad-chute independently of altitude).
 *
 * @unit m
 * @min 0
 * @increment 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_INT32(VT_FW_QC_HMAX, 0);

/**
 * Airspeed less front transition time (open loop)
 *
 * The duration of the front transition when there is no airspeed feedback available.
 *
 * @unit s
 * @min 1.0
 * @max 30.0
 * @increment 0.5
 * @decimal 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_F_TR_OL_TM, 6.0f);

/**
 * Differential thrust in forwards flight.
 *
 * Enable differential thrust seperately for roll, pitch, yaw in forward (fixed-wing) mode.
 * The effectiveness of differential thrust around the corresponding axis can be
 * tuned by setting VT_FW_DIFTHR_S_R / VT_FW_DIFTHR_S_P / VT_FW_DIFTHR_S_Y.
 *
 * @min 0
 * @max 7
 * @bit 0 Yaw
 * @bit 1 Roll
 * @bit 2 Pitch
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_INT32(VT_FW_DIFTHR_EN, 0);

/**
 * Roll differential thrust factor in forward flight
 *
 * Maps the roll control output in forward flight to the actuator differential thrust output.
 *
 * Differential thrust in forward flight is enabled via VT_FW_DIFTHR_EN.
 *
 * @min 0.0
 * @max 2.0
 * @decimal 2
 * @increment 0.1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_FW_DIFTHR_S_R, 1.f);

/**
 * Pitch differential thrust factor in forward flight
 *
 * Maps the pitch control output in forward flight to the actuator differential thrust output.
 *
 * Differential thrust in forward flight is enabled via VT_FW_DIFTHR_EN.
 *
 * @min 0.0
 * @max 2.0
 * @decimal 2
 * @increment 0.1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_FW_DIFTHR_S_P, 1.f);

/**
 * Yaw differential thrust factor in forward flight
 *
 * Maps the yaw control output in forward flight to the actuator differential thrust output.
 *
 * Differential thrust in forward flight is enabled via VT_FW_DIFTHR_EN.
 *
 * @min 0.0
 * @max 2.0
 * @decimal 2
 * @increment 0.1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_FW_DIFTHR_S_Y, 0.1f);

/**
 * Backtransition deceleration setpoint to pitch feedforward gain.
 *
 *
 * @unit rad s^2/m
 * @min 0
 * @max 0.2
 * @decimal 2
 * @increment 0.01
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_B_DEC_FF, 0.f);

/**
 * Backtransition deceleration setpoint to pitch I gain.
 *
 *
 * @unit rad s/m
 * @min 0
 * @max 0.3
 * @decimal 2
 * @increment 0.05
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_B_DEC_I, 0.1f);

/**
 * Minimum pitch angle during hover.
 *
 * Minimum pitch angle during hover flight. If the desired pitch angle is is lower than this value
 * then the fixed-wing forward actuation can be used to compensate for the missing thrust in forward direction
 * (see VT_FW_TRHUST_EN)
 *
 * @unit deg
 * @min -10.0
 * @max 45.0
 * @increment 0.1
 * @decimal 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_PITCH_MIN, -5.0f);

/**
 * Minimum pitch angle during hover landing.
 *
 * Overrides  VT_PITCH_MIN when the vehicle is in LAND mode (hovering).
 * During landing it can be beneficial to allow lower minimum pitch angles as it can avoid the wings
 * generating too much lift and preventing the vehicle from sinking at the desired rate.
 *
 * @unit deg
 * @min -10.0
 * @max 45.0
 * @increment 0.1
 * @decimal 1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_LND_PITCH_MIN, -5.0f);

/**
 * Spoiler setting while landing (hover)
 *
 * @unit norm
 * @min -1
 * @max 1
 * @decimal 1
 * @increment 0.1
 * @group VTOL Attitude Control
 */
PARAM_DEFINE_FLOAT(VT_SPOILER_MC_LD, 0.f);

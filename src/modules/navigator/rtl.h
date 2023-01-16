/***************************************************************************
 *
 *   Copyright (c) 2013-2020 PX4 Development Team. All rights reserved.
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
 * @file rtl.h
 *
 * Helper class for RTL
 *
 * @author Julian Oes <julian@oes.ch>
 * @author Anton Babushkin <anton.babushkin@me.com>
 */

#pragma once

#include <drivers/drv_hrt.h>
#include <px4_platform_common/module_params.h>

#include "navigator_mode.h"
#include "lib/mission/planned_mission_interface.h"
#include "rtl_direct.h"

#include <uORB/uORB.h>
#include <uORB/Publication.hpp>
#include <uORB/topics/rtl_time_estimate.h>

class Navigator;

class RTL : public NavigatorMode, protected PlannedMissionInterface, public ModuleParams
{
public:
	RTL(Navigator *navigator);

	~RTL() = default;

	enum RtlType {
		RTL_DIRECT,
		RTL_MISSION_FAST,
		RTL_MISSION_FAST_REVERSE,
	};

	void on_inactivation() override;
	void on_inactive() override;
	void on_activation() override;
	void on_active() override;

	void initialize() override {};

	void set_return_alt_min(bool min) { _enforce_rtl_alt = min; }

private:
	void onMissionUpdate(bool has_mission_items_changed) override {};

	void setRtlType();

	hrt_abstime _destination_check_time{0};

	RtlType _rtl_type{RTL_DIRECT};

	RtlDirect _rtl_direct;

	bool _enforce_rtl_alt{false};

	DEFINE_PARAMETERS(
		(ParamInt<px4::params::RTL_TYPE>)          _param_rtl_type
	)

	uORB::Publication<rtl_time_estimate_s> _rtl_time_estimate_pub{ORB_ID(rtl_time_estimate)};


};

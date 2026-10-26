//
// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include "discipline.h"

/// Discipline() - algorithm to keep a system clock in time with a reference clock.

Discipline::Discipline(SystemClock& clock) : system_clock(clock){
  return;
}

// called on an interval to calculate offsets and discipline clock
bool Discipline::clock_adjust(const TimeVal& reference_timestamp, const TimeVal& measured_timestamp){
  bool status = false;
  
  if (--loop_tc <= 0){  
    status = true;
    
    // generate clock statistics
    stats.update(reference_timestamp, measured_timestamp);

    // fll uses frequency offset
    int32_t freq_offset = stats.frequency_offset.toMicros();

    loop_tc = get_filter_tc(freq_offset);

    const int32_t max_error = one_million / 2;
    if (safe_abs(freq_offset) > max_error){
      Serial.print("ignoring: "); // hide the rollover
    }
    else{
      int32_t phase_error = 0;
      int32_t freq_error = 0;
      
      if (fll_enabled){
	freq_error = get_frequency_error(freq_offset);
      }
      
      if (pll_enabled){
	int32_t offset = stats.phase_offset.toMicros();
	phase_error = get_phase_error(offset);
      }

      if (info_enabled){
	Serial.print("adjust time: tc=");
	Serial.print(loop_tc);
	Serial.print(", ");
	Serial.print(freq_error);
	Serial.print("/");
	Serial.print(phase_error);
	Serial.print(", ");
      }
      
      int32_t loop_error = freq_error + phase_error;
      system_clock.adjust_time(loop_error);
    }
  }
  
  return status;
}

// adjust loop filter. often overridden by clock specific discipline
int32_t Discipline::get_filter_tc(int32_t freq_offset){
  int8_t filter_tc = 1;
  
  return filter_tc;
}

// scale frequency offset. often overridden by clock specific discipline
int32_t Discipline::get_frequency_error(int32_t freq_offset){
  return freq_offset;
}

// scale phase offset. often overridden by clock specific discipline
int32_t Discipline::get_phase_error(int32_t phase_offset){
  int32_t phase_limit = 2048; // microseconds
  
  phase_offset = phase_offset / 16;
  phase_offset = constrain(phase_offset, -phase_limit, phase_limit);

  return phase_offset;
}


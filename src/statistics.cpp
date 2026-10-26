//
// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include "statistics.h"

/// Statistics() - Maintains statistics for clock pair.

void Statistics::update(const TimeVal& reference_timestamp, const TimeVal& measured_timestamp){
  // find clock deltas
  TimeVal reference_delta = reference_timestamp.subtract(prev_reference_ts);
  prev_reference_ts = reference_timestamp;

  TimeVal measured_delta = measured_timestamp.subtract(prev_measured_ts);
  prev_measured_ts = measured_timestamp;

  // take snapshots of previous frequency/phase offset for wander/jitter calculations
  TimeVal prev_freq_offset = frequency_offset;
  TimeVal prev_phase_offset = phase_offset;
  
  // calculate period difference in microseconds.
  frequency_offset = reference_delta.subtract(measured_delta);

  // find phase difference in microseconds
  phase_offset = reference_timestamp.subtract(measured_timestamp);

  // fixup phase so it passes linearly thru zero
  phase_offset.seconds = 0;
  if (phase_offset.useconds >= (one_million/2)){
    phase_offset.useconds -= one_million;
  }

  if (reference_delta.toMicros() != 0){ // avoid divide by zero
    // find frequency delta and normalize to one second
    TimeVal freq_delta = frequency_offset.subtract(prev_freq_offset);
    freq_delta = freq_delta.divide(reference_delta);

    // wander is the rms value of the change in frequency offset.
    int32_t freq_wander = safe_abs(freq_delta.toMicros());
    if (freq_wander > precision){
      freq_wander = precision; // clamp 'outliers'
    }
    wander.update(freq_wander); // update mean

    // find phase delta and normalize to one second
    TimeVal phase_delta = phase_offset.subtract(prev_phase_offset);
    phase_delta = phase_delta.divide(reference_delta);
    
    // jitter is the rms value of the change in phase offset.
    int32_t phase_jitter = safe_abs(phase_delta.toMicros());
    if (phase_jitter > precision ){
      phase_jitter = precision;  // clamp 'outliers'
    }
    jitter.update(phase_jitter); // update mean
  }
  
  return;
}

int32_t Statistics::get_wander(){
  return wander.value();
}

int32_t Statistics::get_jitter(){
  return jitter.value();
}

void Statistics::print_info(){
  Serial.print("wander/jitter = ");
  Serial.print(wander.value());
  Serial.print("ppm/");
  Serial.print(jitter.value());
  Serial.print("us, offset freq/phase = ");
  Serial.print(frequency_offset.toMicros());
  Serial.print("ppm/");
  Serial.print(phase_offset.toMicros());
  Serial.print("us");

  return;
}


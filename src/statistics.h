#ifndef PPS_STATISTICS_H
#define PPS_STATISTICS_H

// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include <ppskit.h>
#include <utils/ewma.h>

/// Statistics() - Maintains statistics for a clock pair.

class Statistics {
 public:
  void update(const TimeVal& reference_timestamp, const TimeVal& measured_timestamp);
  int32_t get_wander(); /// ppm. filtered rms value of frequency offset delta
  int32_t get_jitter(); /// usecs. filtered rms value of phase offset delta

  TimeVal frequency_offset; /// ref_clock_delta - local_clock_delta
  TimeVal phase_offset;     /// ref_clock - local_clock
  int32_t delay = 0;        /// propagation delay in microseconds
  int32_t precision = 10000;

  void print_info();
  
 private:
  TimeVal prev_reference_ts;
  TimeVal prev_measured_ts;
  EWMA<int32_t> wander{4, precision}; // filtered abs(freq_offset)
  EWMA<int32_t> jitter{4, precision}; // filtered abs(phase_offset_delta)
};

#endif

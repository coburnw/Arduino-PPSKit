#ifndef DISCIPLINE_H
#define DISCIPLINE_H

// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include <ppskit.h>
#include <statistics.h>

/// Discipline() - keeps a system clock in time with a reference clock.
///
/// Implements a simple frequency-locked-loop (fll) and phase-locked-loop
/// (pll) control algorithm.  Exposes filter time constant and error
/// scaling functions to be overriden by clock specific objects.

class Discipline{
 public:
  Discipline(SystemClock&); /// the system clock to be disciplined

  /// called periodically to implement the control algorithm
  virtual bool clock_adjust(const TimeVal& ref, const TimeVal& sys);
  
  /// scales the frequency offset to clock specific error values
  virtual int32_t get_frequency_error(int32_t offset);

  // scales the phase offset to clock specific error values
  virtual int32_t get_phase_error(int32_t offset);

  /// derives a time-constant from clock statistics and current offst
  virtual int32_t get_filter_tc(int32_t offset);

  /// prints current statistics as part of a larger print string
  void print_info();

  /// the system clock being disciplined
  SystemClock& system_clock;

  /// clock and algorithm statistics
  Statistics stats;

  /// enabled control algorithms
  bool fll_enabled = false;
  bool pll_enabled = false;

  /// enabled printing of statistics
  bool info_enabled = false;
  
 private:
  
  int8_t loop_tc = 1;
  bool locked = false;
  
};

#endif

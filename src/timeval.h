#ifndef TIMEVAL_H
#define TIMEVAL_H

// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include <Arduino.h>
constexpr int32_t one_million = 1000000;

/// TimeVal() - a container for a microsecond resolution time instant.
///
/// with helper routines for conversion to simple values and
/// helper routines for simple time math.

class TimeVal {
 public:
  TimeVal();
  TimeVal(int32_t);
  TimeVal(int32_t, int32_t);
  //TimeVal(float);
    
  /// convert to milliseconds.  Max range +/- 24 days.
  int32_t toMillis() const;

  /// convert to microseconds.  Max range +/- 35 minutes.
  int32_t toMicros() const;

  void fromMicros(int32_t);
  
  /// returns (this + val) as a timeval
  TimeVal add(const TimeVal&) const;
  TimeVal subtract(const TimeVal&) const;

  TimeVal multiply(const TimeVal&) const;
  TimeVal divide(const TimeVal&) const;

  // String toString();
  
  int32_t seconds = 0;
  int32_t useconds = 0; // microseconds
};

#endif

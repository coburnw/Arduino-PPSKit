#ifndef PPSKIT
#define PPSKIT

// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include <Arduino.h>

#include "timeval.h"
#include "utils/pps-utils.h"

/// what all clocks have in common
class Clock { 
 public:
  virtual ~Clock() = default;

  /// Gets this clocks understanding of the current time as a TimeVal
  virtual TimeVal get_time() = 0;

  /// called periodically for clock internal maintenance such as slewing.
  virtual bool update() = 0;
  
  int32_t offset = 0;     // the path delay or offset in microseconds

private:
};
  
/// An immutable clock, typically remote, that can be queried
/// for its time with specifications we hope to transfer to
/// our own system clocks.
class ReferenceClock : Clock {
 public:
  /// Gets this clocks understanding of the current time as a TimeVal
  virtual TimeVal get_time();

 private:
};

/// A local clock in hardware or software, walltime or not, that
/// can be nudged, set, or reset at will.
class SystemClock : Clock {
 public:
  virtual ~SystemClock() = default;
  
  /// Gets this clocks understanding of the current time as a TimeVal
  virtual TimeVal get_time();

  /// Sets this clocks time to the instant contained in the TimeVal.
  /// returns true for success, false on error or not supported.
  virtual bool set_time(const TimeVal&);

  /// initiate a slew of the clock by offset in microseconds
  virtual bool adjust_time(const int32_t offset);  // slews clock by offset
  virtual bool step_time(const int32_t offset);  // steps clock by offset

 private:
};

/// An input that is aligned to a seconds boundary of some clock,
/// reference or system.  Its important to recognize that aligned
/// does not mean 'on' the boundary.  offsets often need to be
/// applied.
class PPSClock : Clock {
 public:

  virtual ~PPSClock() = default;
  
  /// called periodically for clock internal maintenance such as polling.
  virtual bool update();

  /// returns immediately with TimeVal containing the
  /// timestamp of the most recent assert pps arrival.
  virtual TimeVal fetch();

  /// Sets the active edge of the pps pulse.
  /// true = rising, false = falling
  bool assert_polarity = true;
  
 private:
};

#endif

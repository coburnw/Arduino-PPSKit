#ifndef PPS_PIN_CLOCK_H
#define PPS_PIN_CLOCK_H

// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright (C) 2026 Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include <ppskit.h>

/// PPSPinClock() - A PPS Pin Clock records the digital-io-pin arrival
/// timestamp of a reference clocks pulse-per-second signal.

class PPSPinClock : public PPSClock{
 public:
  PPSPinClock(const uint8_t pin_number);

  /// returns the reference-clock timestamp of last pps assertion.
  TimeVal get_time();

  /// returns the system-clock timestamp of last pps assertion.
  TimeVal fetch();

  /// returns true if pps asserted.  does any processing such as polling.
  bool update();

 private:
  uint8_t pin_number = NOT_A_PIN;
  bool last_state = false;
  unsigned long timestamp = 0;

};

#endif

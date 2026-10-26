//
// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include "pps-pin-clock.h"

/// PPSPinClock() - A PPS Pin Clock records the arrival timestamp of
/// a reference clocks pulse-per-second signal on a Digital IO pin.

PPSPinClock::PPSPinClock(const uint8_t pps_pin_number){
  pin_number = pps_pin_number;
}

TimeVal PPSPinClock::get_time(){
  // fabricate and return a reference timestamp of the most recent pps assertion
  TimeVal tv = fetch();
  if (tv.useconds >= one_million / 2){
    ++tv.seconds;
  }
  tv.useconds = 0;

  return tv;
}

TimeVal PPSPinClock::fetch(){
  // return a local timestamp of the most recent pps assertion
  TimeVal tv;
  tv.seconds = timestamp / one_million;
  tv.useconds = timestamp % one_million;
  
  return tv;
}

bool PPSPinClock::update(){
  // polls digital io pin for pps edges and returns true on assertion.
  bool got_assert = false;
  
  bool pin_state = digitalRead(pin_number);
  if (pin_state != last_state){
    last_state = pin_state;
    
    if (pin_state == assert_polarity){
      got_assert = true;
      timestamp = micros();
    }
  }

  return got_assert;
}

#ifndef EWMA_H
#define EWMA_H

// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright 2026 (C) Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include <Arduino.h>

/// EWMA() - Exponentialy Weighted Moving Average Filter

// (free form, highly suspect, reasoning of ewma use...)
//
// Oversampling Ratio is defined as F(sampling) / F(nyquist)
// where: F(sampling) is the ADC sample rate for the
// channel of interest.
//
// F(nyquist) is the maximum frequency of interest or 1/2
// the sample rate.
//
// So OSR will typically range from 2 to some number larger.
//
// The corner frequency (fc) of a filter is defined as the
// frequency at which the the output drops by 3db or 1/2 the
// power.
//
// A time constant is defined as the time for a process to
// reach 63% of its final value in response to a step change.
//
// in each iteration, a sample/filter_fraction is accumulated.
//
// In a single pole filter: tc = 1/(2 * pi * fc)
// or fc = 1/(2 * pi * tc)
// or fc = 1/(2 * pi * filter_fraction * sample_interval)
//
// or tc = filter_fraction * sample_interval
//
// By defining filter_fraction = 2^filter_constant, a right
// shift can be used  to effect that division.
//

template <typename T>
class EWMA{
 public:
  EWMA(uint8_t alpha_exponent, T initial_value=0){
    alpha_n = alpha_exponent;
    filter_value = initial_value;

    return;
  };

  T update(T new_value){
    filter_value += (new_value - filter_value) >> alpha_n;
    return filter_value;
  };
  
  T value(){
    return filter_value;
  };
  
  void set_alpha_exponent(uint8_t alpha_exponent){
    alpha_n = alpha_exponent;
    return;
  };
  
 private:
  uint8_t alpha_n;
  T filter_value;

};

#endif

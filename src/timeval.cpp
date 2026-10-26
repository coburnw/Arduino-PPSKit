//
// Arduino PPSKit - A framework for building clocks on small systems.
//
// Copyright (C) 2026 Coburn Wightman
// SPDX-License-Identifier: AGPL-3.0-or-later
//
// SPDX-AI-Disclosure: human-only

#include "timeval.h"

/// TimeVal() - a container for a microsecond resolution time instant.

TimeVal::TimeVal(){
  seconds = 0;
  useconds = 0;
}

TimeVal::TimeVal(int32_t secs){
  seconds = secs;
  useconds = 0;
}

TimeVal::TimeVal(int32_t secs, int32_t usecs){
  seconds = secs;
  useconds = usecs;

  // fix up sign
  if (secs < 0 and usecs > 0){
    useconds = -usecs;
  }
  else if (secs > 0 and usecs < 0){
    useconds = -usecs;
  }

  return;
}

// DateTime TimeVal::toDateTime(){
//   unsigned long days = seconds / (24UL * 60 * 60);
//   unsigned long hours = (seconds / (60 * 60)) % 24;
//   unsigned long minutes = (seconds / 60) % 60;
//   unsigned long _seconds = seconds % 60;

//   DateTime dt;
//   while (days >= dt.daysInYear()) { // 365 or 366
//     days -= dt.daysInYear();
//     dt.year++;
//   }

//   while (days >= dt.daysInMonth()) { // 28 to 31
//     days -= dt.daysInMonth();
//     dt.month++;
//   }

//   dt.day = days + 1;
//   dt.hour = hours;
//   dt.minute = minutes;
//   dt.second = _seconds;

//   return dt;
// }

// usable for timedeltas under approx 24 days.
int32_t TimeVal::toMillis() const{
  int32_t result = 0;
  result += seconds * 1000;
  result += useconds / 1000;

  return result;
}

// usable for timedeltas under approx 35 minutes.
int32_t TimeVal::toMicros() const{
  int32_t result = 0;
  result += seconds * one_million;
  result += useconds;

  return result;
}

void TimeVal::fromMicros(int32_t micros){
  seconds = micros / one_million;
  useconds = micros % one_million;
  
  return;
}

TimeVal TimeVal::add(const TimeVal& tv) const {
  
  TimeVal result;
  int32_t micros = toMicros() + tv.toMicros();
  result.fromMicros(micros);
  
  return result;
}

TimeVal TimeVal::subtract(const TimeVal& tv) const {

  TimeVal result;
  int32_t micros = toMicros() - tv.toMicros();
  result.fromMicros(micros);

  return result;
}

TimeVal TimeVal::multiply(const TimeVal& tv) const {
  // laziness has a cost...
  
  TimeVal result;
  float a = (float)toMicros() / one_million;
  float b = (float)tv.toMicros() / one_million;
  result.fromMicros((a * b) * one_million);
  
  return result;
}

TimeVal TimeVal::divide(const TimeVal& tv) const {
  // what should we do on divide by zero attempt?
  // dxcore returns "most negative number" which gets really weird.
  TimeVal result;
  float a = (float)toMicros() / one_million;
  float b = (float)tv.toMicros() / one_million;
  result.fromMicros((a / b) * one_million);

  return result;
}


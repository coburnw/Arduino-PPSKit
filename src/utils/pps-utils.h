#ifndef PPS_UTILS
#define PPS_UTILS

/// safe_abs() - returns the absolute value.
///
/// because arduino abs() macro acts weird at times.
///
/// original code found here: https://forum.arduino.cc/t/function-abs-on-every-malfunctioning/1150330/16
/// and here: https://electricalflux.com/mcu-general/arduino-absolute-value-macro-error-diagnosis

template <class T> T safe_abs(T const value) {
  return value >= 0 ? value : -value;
}

#endif

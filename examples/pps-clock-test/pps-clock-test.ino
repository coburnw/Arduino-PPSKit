// pps-clock-test.ino
//
// a reference clock built on a pps input
//
// With an arbitry epoch based on the most recent reset event,
// this reference clock has no understanding of wall time.
//

#include <Arduino.h>

#include <ppskit.h>
#include <statistics.h>
#include <clocks/pps-pin-clock.h>

#include "pps-clock-test.h"

const static char* version_string = VERSION;

#define PIN_PPS PIN_PF1

PPSPinClock ppsclock = PPSPinClock{PIN_PPS};
Statistics stats;

void setup(){  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.pins(SER_TX_PIN, SER_RX_PIN);
  Serial.begin(115200);
  Serial.flush();
  Serial.println(version_string);

  // force DX HF Clock in range of pps source
  CLKCTRL.OSCHFTUNE = 2;
  
  pinMode(PIN_PPS, INPUT);
  
  return;
}
  
void loop(){
  constexpr uint32_t loop_interval = 2000;
  static uint32_t loop_timestamp = millis();
  
  if (millis() - loop_timestamp > loop_interval){
    loop_timestamp += loop_interval;  
  }

  if (ppsclock.update()){
    TimeVal ref_tv = ppsclock.get_time();
    TimeVal pps_tv = ppsclock.fetch();
    stats.update(ref_tv, pps_tv);
    stats.print_info();
    Serial.println("");
  }
  
  return;
}

void print_tv(TimeVal tv){
  Serial.print(tv.seconds);
  Serial.print(":");
  Serial.println(tv.useconds);

  return;
}

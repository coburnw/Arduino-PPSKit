// timeval-test.ino
//
// exercise timeval math routines for test and grounding
//

#include <Arduino.h>

#include <timeval.h>
#include <utils/pps-utils.h>

#include "timeval-test.h"

const static char* version_string = VERSION;

void setup(){  
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.pins(SER_TX_PIN, SER_RX_PIN);
  Serial.begin(115200);
  Serial.flush();
  Serial.println(version_string);

  return;
}
  
void loop(){
  constexpr uint32_t interval = 2000;
  static uint32_t timestamp = millis();
  
  if (millis() - timestamp > interval){
    timestamp += interval;

    MyTimeVal a;
    MyTimeVal b;
    
    a = MyTimeVal{6, 500000};
    b = MyTimeVal{3L};

    /* String s = tv_str(a) + " = " + String(a.toMicros()); */
    /* Serial.println(s); */
    /* s = tv_str(b) + " = " + String(b.toMicros()); */
    /* Serial.println(s); */

    test(a, b);
    Serial.println();

    a = MyTimeVal{0L, 500000};
    b = MyTimeVal{3L};
    test(a, b);
    Serial.println();

    a = MyTimeVal{-3L, -500000};
    b = MyTimeVal{3L};
    test(a, b);
    Serial.println();

    a = MyTimeVal{-3L, -500000};
    b = MyTimeVal{-3L};
    test(a, b);
    Serial.println();

    a = MyTimeVal{-3L, -500000};
    b = MyTimeVal{-4L, -250000};
    test(a, b);
    Serial.println();


    a = MyTimeVal{1L,0L};
    b = MyTimeVal{0, 0};
    MyTimeVal c;
    c = a.divide(b);
    String str = a.toString() + " / " + b.toString() + " = " + c.toString();
    Serial.println(str);
    Serial.printHexln(c.toMicros());
    Serial.println(sabs(c.toMicros()));

    int32_t val = ~0; //2147483648;
    Serial.println(safe_abs(val));
  
  }

  return;
}

void test(MyTimeVal a, MyTimeVal b){
  Serial.println(add(a, b));
  Serial.println(sub(a, b));
  Serial.println(mul(a, b));
  Serial.println(div(a, b));
  
  return;
}

String sabs(MyTimeVal a){
  String str = String("abs(" + a.toString() + ") = " + safe_abs(a.toMicros()));

  return str;
}

String add(MyTimeVal a, MyTimeVal b){
  MyTimeVal result = a.add(b);
  String s = tv_str(a) + " + " + tv_str(b) + " = " + tv_str(result);
  return s;
}

String sub(MyTimeVal a, MyTimeVal b){
  MyTimeVal result = a.subtract(b);
  String s = tv_str(a) + " - " + tv_str(b) + " = " + tv_str(result);
  return s;
}

String mul(MyTimeVal a, MyTimeVal b){
  MyTimeVal result = a.multiply(b);
  String s = tv_str(a) + " * " + tv_str(b) + " = " + tv_str(result);
  return s;
}

String div(MyTimeVal a, MyTimeVal b){
  MyTimeVal result = a.divide(b);
  String s = tv_str(a) + " / " + tv_str(b) + " = " + tv_str(result);
  return s;
}

String tv_str(MyTimeVal tv){
  String s = String(tv.seconds) + ":" + String(tv.useconds);
  
  return s;
}
void print_tv(MyTimeVal tv){
  Serial.print(tv.seconds);
  Serial.print(":");
  Serial.println(tv.useconds);

  return;
}

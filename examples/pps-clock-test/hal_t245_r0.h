#ifndef T245_R0_H
#define T245_R0_H

// Core 
#ifdef LED_BUILTIN
#undef LED_BUILTIN
#endif

#define LED_BUILTIN PIN_PC3
#define RST_SW_PIN PIN_PF6

#define SER_TX_PIN PIN_PA0
#define SER_RX_PIN PIN_PA1

// UI
#define BEEP_POS_PIN PIN_PA3
#define BEEP_NEG_PIN PIN_PA2

#define ENC_B_PIN PIN_PF4
#define ENC_A_PIN PIN_PF5
#define ENC_PB_PIN PIN_PF1

//#define I2C_SDA_PIN PIN_PF2
//#define I2C_SCL_PIN PIN_PF3
#define I2C_PIN_SET 0  // Wire1: PIN_PF2/PIN_PF3, swap0

// Application
#define DAC_OUT_PIN PIN_PD6 

#define PWM_PIN  PIN_PA4   // mosi, hdr pin4
#define PARK_PIN PIN_PA6   // sck,  hdr pin6

// beware: the actual op-amp to use is defined in channels.cpp
#define AMPS_IN_PIN PIN_PD4      // op-amp1 in+
#define TEMP_IN_PIN PIN_PD1      // op-amp0 in+

#define TEMP_ADC_PIN  PIN_PD2    // AIN2, op-amp0 output
#define AMPS_ADC_PIN  PIN_PD5    // AIN5, op-amp1 output

#define VOLTS_IN_PIN PIN_PD7     // AIN7
#define VOLTS_ADC_PIN VOLTS_IN_PIN    // AIN3

#endif

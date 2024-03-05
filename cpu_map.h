/*
  cpu_map.h - CPU and pin mapping configuration file
  Part of Grbl v0.9

  Copyright (c) 2012-2014 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

/* The cpu_map.h file serves as a central pin mapping settings file for different processor
   types, i.e. AVR 328p or AVR Mega 2560. Grbl officially supports the Arduino Uno, but the 
   other supplied pin mappings are supplied by users, so your results may vary. */

// NOTE: This is still a work in progress. We are still centralizing the configurations to
// this file, so your success may vary for other CPUs.

#ifndef cpu_map_h
#define cpu_map_h
//----------------------------------------------------------------------------------------


#ifdef CPU_MAP_ATMEGA2560_RAMBO // (Arduino Mega 2560)+Ramps1.4 Working Arsi

// Serial port pins
#define SERIAL_RX USART0_RX_vect
#define SERIAL_UDRE USART0_UDRE_vect

// Increase Buffers to make use of extra SRAM
//#define RX_BUFFER_SIZE		256
//#define TX_BUFFER_SIZE		128
//#define BLOCK_BUFFER_SIZE	36
//#define LINE_BUFFER_SIZE	100

// Define step pulse output pins. Changed for Ramps
#define STEP_DDR      DDRC
#define STEP_PORT     PORTC
#define STEP_PIN      PINC
#define X_STEP_BIT        0 // Not realy used
#define Y_STEP_BIT        1 // Not realy used
#define Z_STEP_BIT        2 // Not realy used
#define STEP_MASK ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits

// Define step direction output pins. Changed for Ramps
#define DIRECTION_DDR      DDRL
#define DIRECTION_PORT     PORTL
#define DIRECTION_PIN      PINL
#define X_DIRECTION_BIT   1 // Not realy used
#define Y_DIRECTION_BIT   0 // Not realy used
#define Z_DIRECTION_BIT   2 // Not realy used
#define DIRECTION_MASK ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits

// Define stepper driver enable/disable output pin. Changed for Ramps
#define STEPPERS_DISABLE_DDR   DDRA
#define STEPPERS_DISABLE_PORT  PORTA
#define STEPPERS_DISABLE_BIT   6 // Not realy used
#define STEPPERS_DISABLE_MASK (1<<STEPPERS_DISABLE_BIT)

// NOTE: All limit bit pins must be on the same port
#define LIMIT_DDR       DDRB
#define LIMIT_PORT      PORTB
#define LIMIT_PIN       PINB
#define X_LIMIT_BIT     6 // Ramps PB3 ( MISO/PCINT3 ) Digital pin 50 (MISO) ->Ramps AUX-3 pin 3
#define Y_LIMIT_BIT     5 // Ramps PB2 ( MOSI/PCINT2 ) Digital pin 51 (MOSI) ->Ramps AUX-3 pin 4
#define Z_LIMIT_BIT     4 // Ramps PB1 ( SCK/PCINT1 ) Digital pin 52 (SCK) -> Ramps AUX-3 pin 5
#define LIMIT_INT       PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect  PCINT0_vect 
#define LIMIT_PCMSK     PCMSK0 // Pin change interrupt register
#define LIMIT_MASK ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits

// Define spindle enable and spindle direction output pins.
#define SPINDLE_ENABLE_DDR   DDRE
#define SPINDLE_ENABLE_PORT  PORTE
#define SPINDLE_ENABLE_BIT   5 // MEGA2560 Digital Pin 6
#define SPINDLE_DIRECTION_DDR   DDRH
#define SPINDLE_DIRECTION_PORT  PORTH
#define SPINDLE_DIRECTION_BIT   5 // MEGA2560 Digital Pin 5

// Define flood and mist coolant enable output pins.
// NOTE: Uno analog pins 4 and 5 are reserved for an i2c interface, and may be installed at
// a later date if flash and memory space allows.
#define COOLANT_FLOOD_DDR   DDRH
#define COOLANT_FLOOD_PORT  PORTH
#define COOLANT_FLOOD_BIT   3 // MEGA2560 Digital Pin 8
#ifdef ENABLE_M7 // Mist coolant disabled by default. See config.h to enable/disable.
#define COOLANT_MIST_DDR   DDRG
#define COOLANT_MIST_PORT  PORTG
#define COOLANT_MIST_BIT   5 // MEGA2560 Digital Pin 9
#endif  

// Define user-control pinouts (cycle start, reset, feed hold) input pins.
// NOTE: All pinouts pins must be on the same port and not on a port with other input pins (limits).
#define PINOUT_DDR       DDRK
#define PINOUT_PIN       PINK
#define PINOUT_PORT      PORTK
#define PIN_RESET        0  // MEGA2560 Analog Pin 8
#define PIN_FEED_HOLD    1  // MEGA2560 Analog Pin 9
#define PIN_CYCLE_START  2  // MEGA2560 Analog Pin 10
#define PINOUT_INT       PCIE2  // Pin change interrupt enable pin
#define PINOUT_INT_vect  PCINT2_vect
#define PINOUT_PCMSK     PCMSK2 // Pin change interrupt register
#define PINOUT_MASK ((1<<PIN_RESET)|(1<<PIN_FEED_HOLD)|(1<<PIN_CYCLE_START))

// Define probe switch input pin.
#define PROBE_DDR       DDRA
#define PROBE_PIN       PINA
#define PROBE_PORT      PORTA
#define PROBE_BIT       1  // MEGA2560 Analog Pin 11
#define PROBE_MASK      (1<<PROBE_BIT)

// Start of PWM & Stepper Enabled Spindle
#ifdef VARIABLE_SPINDLE
// Advanced Configuration Below You should not need to touch these variables
// Set Timer up to use TIMER2B which is attached to Digital Pin 9
#define TCCRA_REGISTER		TCCR2A
#define TCCRB_REGISTER		TCCR2B
#define OCR_REGISTER		OCR2B

#define COMB_BIT			COM2B1
#define WAVE0_REGISTER		WGM20
#define WAVE1_REGISTER		WGM21
#define WAVE2_REGISTER		WGM22
#define WAVE3_REGISTER		WGM23

#define SPINDLE_PWM_DDR		DDRG
#define SPINDLE_PWM_PORT    PORTG
#define SPINDLE_PWM_BIT		5 // MEGA2560 Digital Pin 9
#endif // End of VARIABLE_SPINDLE



// MOD GRBL for Cyclone

#define PROBE_PIN 23 // Z endstop
#define XLIM_PIN 12
#define YLIM_PIN 11

#define X_STEP_PIN         37 //PF0 ( ADC0 )
#define X_DIR_PIN          48 //PF1 ( ADC1 )
#define X_ENABLE_PIN       29 //PD7 ( T0 )

#define Y_STEP_PIN         36 //PF6 ( ADC6 )
#define Y_DIR_PIN          49 //PF7 ( ADC7 )
#define Y_ENABLE_PIN       28 //PF2 ( ADC2 )

#define Z_STEP_PIN         35 //PL3 ( OC5A )
#define Z_DIR_PIN          47 //PL1 ( ICP5 )
#define Z_ENABLE_PIN       27 //PK0 ( ADC8/PCINT16 )

#define SPINDLE_ENABLE_PIN 3
#define SPINDLE_DIRECTION_PIN 4
#define COOLANT_FLOOD_PIN 8

#define X_CURRENT   46
#define Y_CURRENT   46
#define Z_CURRENT   45

#define MICROSTEP_X_1 40
#define MICROSTEP_X_2 41
//#define MICROSTEP_Y_1 A15
#define MICROSTEP_Y_2 39



#endif









//----------------------------------------------------------------------------------------

/* 
#ifdef CPU_MAP_CUSTOM_PROC
  // For a custom pin map or different processor, copy and paste one of the default cpu map
  // settings above and modify it to your needs. Then, make sure the defined name is also
  // changed in the config.h file.
#endif
*/

#endif

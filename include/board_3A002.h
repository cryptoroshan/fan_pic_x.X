/* 
 * File:   board.h
 * Author: jstahlba
 *
 * Created on May 3, 2022, 8:15 PM
 */

#ifndef BOARD_3A002_H
#define	BOARD_3A002_H

#define BOARD_3A002

#ifdef	__cplusplus
extern "C" {
#endif
    
#include <xc.h>
    
#define ASCII_PROTOCOL
//BASE64 uses 32 bit floats and ascii uses 24 floats
//#define BASE64_PROTOCOL

#define NUM_TACH 4
#define NUM_TEMP 2
#define NUM_VOLTAGE 4
#define NUM_FAN 2

#define VERSION_MAJOR 1
#define VERSION_MINOR 9
#define VERSION_BUILD 2
    
#define PROTOCOL_VERSION 0x10

#define GENERIC_BUFFER_SIZE 180
uint8_t genericBuffer[GENERIC_BUFFER_SIZE]; //Started to run out of memory so I created a very basic heap
    
#define _XTAL_FREQ 20e6
#define VCC_VOLTAGE 3.3f

    /************************************************************************************************
    Define the i/o pins
     ************************************************************************************************/
    //hww TRISA changed for Pixus board I/O differences #define     TRISA_INIT			0b11001111  	// this MUST agree with the #defines below

#define TRISA_INIT 0b00101111 //  4 right most bits inputs RA0-RA3, relay output, -12V input, OSC2 setting??, unused

#define     TEMP_A              PORTAbits.RA0   // input analog - Temperature A
#define     TEMP_B              PORTAbits.RA1   // input analog - Temperature B
#define     VSENSE3				PORTAbits.RA2   // 3.3V sense analog input
#define     VSENSE5				PORTAbits.RA3   // 5V sense analog input
#define     FAN_ERR				PORTAbits.RA4	// output - fan error  relay and front panel alarm output
#define     VSENSENEG12			PORTAbits.RA5   // -12 sense analog input

#define     TRISB_INIT          0b11111111  	// this MUST agree with the #defines below

#define     TACHO_2A			PORTBbits.RB2	// input - Tachometer for fan 2A
#define     TACHO_2B			PORTBbits.RB3	// input - Tachometer for fan 2B
#define     VSENSENE12_2		PORTAbits.RB4
#define     PSU_FAULT			PORTBbits.RB5	// input  power good signal from PSU

#define     TRISC_INIT          0b00000000  	// this MUST agree with the #defines below

#define     FAN_1_PWM           PORTCbits.RC1   // output - Fan 1 PWM control (CCP2)
#define     FAN_2_PWM           PORTCbits.RC2   // output - Fan 2 PWM control (CCP1)
#define     USB_DN              PORTCbits.RC4   // output - USB D-
#define     USB_DP              PORTCbits.RC5   // output - USB D+
#define     TEMP_ERR			PORTCbits.RC6   // output - temperature relay and front panel alarm output
#define     POW_ERR				PORTCbits.RC7   // output - power supplies out of range relay and front panel alarm output

#define     USB_BUS_SENSE		PORTEbits.RE3   // input - USB connected to host - no TRIS required for this pin

    // define debugging signals - not used in production code
#define Mark1               { UNASSIGNED1 = 1; UNASSIGNED1 = 0; }
#define Mark1double         { UNASSIGNED1 = 1; UNASSIGNED1 = 0; UNASSIGNED1 = 1; UNASSIGNED1 = 0; }
#define Mark2               { UNASSIGNED2 = 1; UNASSIGNED2 = 0; }
#define Mark2double         { UNASSIGNED2 = 1; UNASSIGNED2 = 0; UNASSIGNED2 = 1; UNASSIGNED2 = 0; }
#define Mark3               { UNASSIGNED3 = 1; UNASSIGNED3 = 0; }
#define Mark3double         { UNASSIGNED2 = 1; UNASSIGNED2 = 0; UNASSIGNED2 = 1; UNASSIGNED2 = 0; }

#define self_power          1
    
#define TACH_PORT PORTB
static char TACH_FIELD[NUM_TACH] = {1<<3, 1<<2, 1<<1, 1<<0};

#define DIV_3 2.475f
#define DIV_5 2.5f
#define DIV_12 2.551181f
#define DIV_M12 2.503f

#define AN0  0b00000011
#define AN1  0b00000111
#define AN2  0b00001011
#define AN3  0b00001111
#define AN4  0b00010011
#define AN11 0b00101111

#define VS2_12
#ifdef VS2_12
const float VOLTAGE_LEVELS[NUM_VOLTAGE] = {12.0f, 5, 3.3f, -12};
const float VOLTAGE_DIV[NUM_VOLTAGE] = {DIV_12, DIV_5, DIV_3, DIV_M12};
#else
const float VOLTAGE_LEVELS[6] = {12, 3.3f, 5, 3.3f, 12, -12};
const float VOLTAGE_DIV[6] = {DIV_12, DIV_3, DIV_5, DIV_3, DIV_12, DIV_M12};
#endif
const uint8_t VOLTAGE_PORT[NUM_VOLTAGE] = {AN11, AN3, AN2, AN4};
const uint8_t TEMP_PORT[NUM_TEMP] = {AN0, AN1};
const uint8_t TACH_DIVS_MAP[6] = {0,0,1,2,4,2}; // x4 settings

const uint8_t TACH_INDEX_TO_FAN[NUM_TACH] = {0,0,1,1};

#define HAS_BEEPER_BUTTON
#ifdef HAS_BEEPER_BUTTON
    #define     ALARM_RESET_BUTTON	PORTBbits.RB7	// input  alarm reset button - low if pressed
    #define     BEEPER              PORTCbits.RC0   // output - USB connected to host
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* BOARD_3A002_H */


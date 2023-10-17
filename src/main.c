/*******************************************************************************************************************************
    Main.c
    Pixus Technologies Version Released 1.4 PN: 25A000004-A04 24-Oct-2018 HWW remove latching behaviour of EFor conditions, add 6 sec startup dela7
    Pixus Technologies Version Released 1.3 PN: 25A000004-A03 12-Jul-2018 HWW JS fix rratic fan detection fail
    Pixus Technologies Version Released 1.2 PN: 25A000004-A02 12-Feb-2018 HWW JS
    Pixus Technologies Version Released 1.0 PN: 25A000004-A01 09-Feb-2018 HWW initial release for first unit shipped
	
    Original version Copyright by Geoff Graham under GPL General License 2.0
	
    (original)Version 1.0   Mar 2010
	
    Go to http://geoffg.net/fancontroller.html for updates, errata and helpful notes
    
    Copyright 2010 Geoff Graham - http://geoffg.net
    This program is free software: you can redistribute it and/or modify it under the terms of the GNU General
    Public License as published by the Free Software Foundation, either version 2 of the License, or (at your
    option) any later version.
	
    This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.  You should have received a copy of the GNU General Public License along with this program.
    If not, see <http://www.gnu.org/licenses/>.
	
	
    This is the main source file for the Fan Controller project.
	
    Development Environment
    To compile this you need the following software which is available free of charge from Microchip (www.microchip.com)
    - Microchip MPLAB IDE Version 8.14 or higher
    - Microchip C18 Compiler Lite Version
    You should unzip all the source code files while retaining the directory structure.  Then use the MPLAB
    "Project -> Open.." menu selection to open the file "Fan Controller.mcp".  This will load the complete project
    and its dependent files.
	
    Program summary:
    The program consists of two main sections:
    
    Timer 1 interrupt:
    This occurs every 400uS.  Within this interrupt a fast loop counts down the pulse width
    of the pulses used to drive the buck converters.  The length of this loop is about 170uS which is the 
    maximum width of the output pulse.  Other functions within the timer include:
    - setting a new second flag every second
    - counts pulses on the various tachometer inputs
    Overall the interrupt lasts for about 200uS leaving about 200uS before the next interrupt.
    
    Main function:
    After initialising everything main() enters a high speed loop which runs forever.  Functions
    within the loop include:
    - reading the temperatures and calculating the pulse widths
    - checking the USB stack for data to be sent/received
    Every second the main function will also:
    - format the status string and send it off to the USB interface
    - check for alarms (failed sensors or fans)
    - count down timers (for example the startup timer and the alarm timer)
    
 ********************************************************************************************************************************/
// PIC18F2550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = ON         // Brown-out Reset Enable bits (Brown-out Reset enabled in hardware only (SBOREN is disabled))
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = ON      // USB Voltage Regulator Enable bit (USB voltage regulator enabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = ON      // CCP2 MUX bit (CCP2 input/output is multiplexed with RC1)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = ON      // Stack Full/Underflow Reset Enable bit (Stack full/underflow will cause Reset)
#pragma config LVP = ON         // Single-Supply ICSP Enable bit (Single-Supply ICSP enabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

/** INCLUDES *******************************************************/
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "usb.h"
#include "usb_device.h"
#include "usb_device_cdc.h"

#include "board.h"
#include "eeprom.h"
#include "fan_config.h"
#include "fan_data.h"
#include "sensors.h"
#include "utils.h"

#define BC_PERIOD				400									// period of the buck waveform
#define	BC_MAX_PULSE			45									// max pulsewidth of the buck pulse is (BC_MAX_PULSE * 3.8) uSec
#define BC_MAX_PULSE_ONE_FAN	36									// max pulsewidth when only one fan in the pair is connected
// this should be approx 80% of BC_MAX_PULSE

#define	FAN_START_TIME			3									// run fans at high speed for 3 seconds after startup
#define	FAN_START_PWR			85									// power to use after startup

#define ALARM_DELAY				5									// an alarm must stay on for more than this seconds before we beep

#ifdef ASCII_PROTOCOL
#define COMMAND_START_CHR 'F'
#define COMMAND_CD "FCD,"
#define COMMAND_CR "FCR,"
#define COMMAND_GVV "FVV,"
#else
#define COMMAND_START_CHR 'G'
#define COMMAND_CD "GCD,"
#define COMMAND_CR "GCR,"
#define COMMAND_GVV "GVV,"
#endif


/* ****************************************************************************
 * Re-direct interrupts
 * ****************************************************************************/
#define REMAPPED_RESET_VECTOR_ADDRESS			0x1000
#define REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS	(REMAPPED_RESET_VECTOR_ADDRESS + 0x0008)
#define REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS	(REMAPPED_RESET_VECTOR_ADDRESS + 0x0018)

#pragma code HIGH_INTERRUPT_VECTOR = 0x08
void High_ISR (void) __at(0x08)
{
	asm("goto" ___mkstr(REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS));
}
#pragma code LOW_INTERRUPT_VECTOR = 0x18
void Low_ISR (void) __at(0x18)
{
	asm("goto" ___mkstr(REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS));
}
extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code REMAPPED_RESET_VECTOR = REMAPPED_RESET_VECTOR_ADDRESS
void _reset (void) __at(REMAPPED_RESET_VECTOR_ADDRESS)
{
	asm("goto" ___mkstr(_startup));
}
#pragma code REMAPPED_HIGH_INTERRUPT_VECTOR = REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS
void Remapped_High_ISR (void) __at(REMAPPED_HIGH_INTERRUPT_VECTOR_ADDRESS)
{
	asm("goto" ___mkstr(HighISRCode));
}
#pragma code REMAPPED_LOW_INTERRUPT_VECTOR __at(REMAPPED_LOW_INTERRUPT_VECTOR_ADDRESS)
void Remapped_Low_ISR (void)
{
	asm("goto" ___mkstr(LowISRCode));
}



/** V A R I A B L E S ********************************************************/
#define COMMAND_FCQ 0 
#define COMMAND_FCS 1
#define COMMAND_FCV 2
#define COMMAND_FCR 3
#define COMMAND_ERR 99

#define USB_BUFF_SIZE  200											// buffer size for USB communications
#define FAULTY_SENSOR  127                                          // magic number indicating a faulty sensor

/** P R I V A T E  P R O T O T Y P E S ***************************************/
void InitializeSystem(void);
uint8_t CheckHeader(uint8_t * buffer);

int8_t ReadFanData(uint8_t fan, uint8_t idx);
void DelayWait();
void Beep();
void rebootToBoot();

void Init_PWM();
void Init_TIM1();
void TIM1_ISR();
void highISR(void);

void pvrMainTask();
//the variables need to be split due to compiler limits


uint8_t USB_Out_Buffer[USB_BUFF_SIZE];
uint8_t USB_Out_len;

uint8_t cmdBuffer[USB_BUFF_SIZE];
uint8_t cmdBufferOffset = 0;

uint16_t TachoCapture[NUM_TACH];

uint8_t StartupCount[4];
bool NewSecond;
uint8_t AlarmTempCount[4];
uint8_t AlarmFanCount[4];

bool lastTach[NUM_TACH];



#if defined(USB_CDC_SET_LINE_CODING_HANDLER)

void USART_mySetLineCodingHandler(void) {
    //Update the baudrate info in the CDC driver
    CDCSetBaudRate(cdc_notice.GetLineCoding.dwDTERate);
}
#endif

#pragma code

void DelayWait() {
    uint16_t bc; // beeper cycle counter
    uint8_t bt; // beeper delay
    uint8_t junk;
    for (bc = 0; bc < 50000; bc++) {
        junk = 1;
        for (bt = 0; bt < 100; bt++)
            junk = 0;
    }
}

void ProcessUSBIO() {
    /* If the USB device isn't configured yet, we can't really do anything
     * else since we don't have a host to talk to.  So jump back to the
     * top of the while loop. */
    if (USBGetDeviceState() < CONFIGURED_STATE) {
        return;
    }

    /* If we are currently suspended, then we need to see if we need to
     * issue a remote wakeup.  In either case, we shouldn't process any
     * keyboard commands since we aren't currently communicating to the host
     * thus just continue back to the start of the while loop. */
    if (USBIsDeviceSuspended() == true) {
        return;
    }

    uint8_t n = getsUSBUSART(genericBuffer, GENERIC_BUFFER_SIZE);
    if (n) {
        if (n + cmdBufferOffset >= USB_BUFF_SIZE)
            cmdBufferOffset = 0;
        memcpy(cmdBuffer + cmdBufferOffset, genericBuffer, n);
        cmdBufferOffset += n;

        // check if we have a line terminated in CR or LF
        if (cmdBuffer[cmdBufferOffset - 1] == '\r' || cmdBuffer[cmdBufferOffset - 1] == '\n') {
            uint8_t cmd = CheckHeader(cmdBuffer);
            if (cmd == COMMAND_FCQ) {
                size_t outlen = 0;
                strncpy(USB_Out_Buffer, COMMAND_CR, USB_BUFF_SIZE);
                USB_Out_len = 4;
                fan_config_to_data(&lastFanConfig, &USB_Out_Buffer[USB_Out_len], USB_BUFF_SIZE - 6, &outlen);
                USB_Out_len += outlen;
                strncpy(&USB_Out_Buffer[USB_Out_len], "\r\n", (USB_BUFF_SIZE - USB_Out_len));
                USB_Out_len += 2;

            } else if (cmd == COMMAND_FCS) {
                FanConfig newConfig;
                if (fan_config_from_data(&cmdBuffer[4], cmdBufferOffset - 4, &newConfig) == 0) {
                    setConfig(&newConfig, true);
                }
            } else if (cmd == COMMAND_FCV) {                
                uint8_t p = 0;
                strncpy(USB_Out_Buffer, COMMAND_GVV, USB_BUFF_SIZE);
                p += 4;
                p += uitoac(&USB_Out_Buffer[p], VERSION_MAJOR);
                p += uitoac(&USB_Out_Buffer[p], VERSION_MINOR);
                p += uitoac(&USB_Out_Buffer[p], VERSION_BUILD);
                USB_Out_Buffer[p++] = '\r';
                USB_Out_Buffer[p++] = '\n';
                USB_Out_len = strlen(USB_Out_Buffer);
            } else if (cmd == COMMAND_FCR) {
                rebootToBoot();
            }

            cmdBuffer[0] = 0;
            cmdBufferOffset = 0;
        }
    }

    if (mUSBUSARTIsTxTrfReady() && USB_Out_len > 0) {
        putUSBUSART(USB_Out_Buffer, USB_Out_len);
        USB_Out_len = 0;
    }

    CDCTxService();
}

void main(void) {
    uint8_t i;
    PORTC = PORTB = PORTA = 0; // start out with all outputs low
    TRISA = TRISA_INIT;
    TRISB = TRISB_INIT;
    TRISC = TRISC_INIT;

    Init_PWM();
    Init_TIM1();
    
	INTCON = 0b11000000;											// enable peripheral interrupts
    INTCON2 = 0b10000000;
	INTCON3= 0;														// disable external interrupts
	PIE1   = 0b00000001;											// enable timer 1 overflow interrupt
    
    ADCON1 = 0b00001111; // Make A0 to A12 into analog inputs, reference is Vdd/Vss //need to toggle the bits because the pin assignment is flawed
    ADCON0 = 0b00000001; // Enable the ADC
    ADCON2 = 0b10010110; // ADC result right justified, setup 4 Tad, clock Fosc/64

    // check if temp A is shorted to ground and, if so, reset the eeprom to the defaults
    ADCON0 = 0b00000011; // select temperature A input and start the conversion
    while ((ADCON0 & 0b00000010) != 0); // wait for the conversion

    if (ADRESH == 0 && ADRESL < 100) { // get the reading and if the input is shorted to ground
        loadDefault();
    } else {
        loadConfig();
    }

    Beep();
    DelayWait(); // 6 sec startup delay so fans and power supplies come up

    //TODO: not bootleader issues with attach and interrupts
    USBDeviceInit();

    while (1) {
        if (NewSecond) {
            NewSecond = false;
            pvrMainTask();

            for (i = 0; i < NUM_TACH; i++) {
                int fanIndex = TACH_INDEX_TO_FAN[i];
                lastFanData.tach[i] = (TachoCapture[i] / (TACH_DIVS_MAP[lastFanConfig.fanConfig[fanIndex].fanType]*2.0f)*60);
                //lastFanData.tach[i] =  TachoCapture[i];
                TachoCapture[i] = 0;
            }
        }


        for (i = 0; i < NUM_TACH; i++) {
            bool current = (TACH_PORT & TACH_FIELD[i]) == TACH_FIELD[i];
            if (current != lastTach[i]) {
                TachoCapture[i]++; // count up if the input is low->high
            }
            lastTach[i] = current;
        }


#if defined(USB_POLLING)
        USBDeviceTasks();
#endif
#if defined(USB_INTERRUPT)
        USBDeviceAttach();
#endif
        if (USBGetDeviceState() < CONFIGURED_STATE) {
            /* Jump back to the top of the while loop. */
            continue;
        }
        if (USBIsDeviceSuspended() == true) {
            /* Jump back to the top of the while loop. */
            continue;
        }

        //Application specific tasks
        ProcessUSBIO();

        CLRWDT();
    }//end while
}

// Check the data in the command sent to the fan controller
// the data is assumed to be in DATA_In_Buffer[]
// Return 	COMMAND_FCQ for query (FCQ)
//        	COMMAND_FCS for setting (FCS) the parameters
// 			COMMAND_FCV for version
// 			COMMAND_FCR reboot into bootloader
//		  99 for error (ie, invalid command or invalid characters)

uint8_t CheckHeader(uint8_t * buffer) {
    // then check the command header
    if (toupper(buffer[0]) != COMMAND_START_CHR) return COMMAND_ERR;
    if (toupper(buffer[1]) != 'C') return COMMAND_ERR;
    if (toupper(buffer[2]) == 'Q') return COMMAND_FCQ;
    if (toupper(buffer[2]) == 'V') return COMMAND_FCV;
    if (toupper(buffer[2]) == 'R') return COMMAND_FCR;
    if (toupper(buffer[2]) == 'S') return COMMAND_FCS;

    return COMMAND_ERR;
}

void rebootToBoot() {
    asm("goto 0x001C");
}

void Init_PWM() {
    T2CON = 0b00000110;

    PR2 = 119;

    FAN_1_PWM = 0;
    FAN_2_PWM = 0;

    CCP1CONbits.CCP1M = 0b00001111;
    CCP2CONbits.CCP2M = 0b00001111;
}

void Init_TIM1() {
    T1CON = 0b10000001;
    PIE1 = 0b00000001;
}

void highISR(void)  {
    if (((PIE1bits.TMR1IE)&&(PIR1bits.TMR1IF))) {
        TIM1_ISR();
    } else {
#if defined(USB_INTERRUPT)
        USBDeviceTasks();
#endif
    }
}

void TIM1_ISR() {
    static uint16_t SecCnt = (uint16_t) ((uint32_t) 1000000 / (uint32_t) BC_PERIOD);
    uint8_t i;

    if (!((PIE1bits.TMR1IE)&&(PIR1bits.TMR1IF))) return; // abort if not the timer 1 interrupt

    // reset the timer for the next interrupt
    TMR1H = ((uint16_t) 0 - (uint16_t) BC_PERIOD * 12) >> 8;
    TMR1L = ((uint16_t) 0 - (uint16_t) BC_PERIOD * 12) & 0x0f;

    // Time the buck converter pulse width for each fan pair
    // each loop through here takes 3.8uS and the total (for BC_MAX_PULSE = 45) is 170uS

    // count down to each second and raise a flag indicating that a new second has occurred
    if (--SecCnt == 0) {
        NewSecond = true;
        SecCnt = (uint16_t) ((uint32_t) 1000000 / (uint32_t) BC_PERIOD);


    }

    PIR1bits.TMR1IF = false;
}

void sendFanData() {
    uint8_t outlen = 0;
    strncpy(USB_Out_Buffer, COMMAND_CD, USB_BUFF_SIZE);
    USB_Out_len = 4;
    fan_data_to_data(&lastFanData, &USB_Out_Buffer[USB_Out_len], USB_BUFF_SIZE - 6, &outlen);
    USB_Out_len += outlen;
    strncpy(&USB_Out_Buffer[USB_Out_len], "\r\n", (USB_BUFF_SIZE - USB_Out_len));
    USB_Out_len += 2;
}

void pvrMainTask() {
    processAnalog(&lastFanData, &lastFanConfig);
    computePWM(&lastFanData, &lastFanConfig);
    checkError(&lastFanData, &lastFanConfig);

    sendFanData();
}

void __interrupt() HighISRCode()
{
    highISR();
	
}	//This return will be a "retfie fast", since this is in a #pragma interrupt section 
#pragma interruptlow LowISRCode
void LowISRCode()
{
	
}


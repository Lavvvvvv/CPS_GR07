#include "lab02.h"

#include <xc.h>
#include <p33Fxxxx.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL
#include <libpic30.h>

#include "types.h"
#include "lcd.h"
#include "led.h"

#define FCY_EXT 32768

void initialize_timer()
{
    // Enable RTC Oscillator -> this effectively does OSCCONbits.LPOSCEN = 1
    // but the OSCCON register is lock protected. That means you would have to 
    // write a specific sequence of numbers to the register OSCCONL. After that 
    // the write access to OSCCONL will be enabled for one instruction cycle.
    // The function __builtin_write_OSCCONL(val) does the unlocking sequence and
    // afterwards writes the value val to that register. (OSCCONL represents the
    // lower 8 bits of the register OSCCON)
    __builtin_write_OSCCONL(OSCCONL | 2);
    // Disable the Timers
    CLEARBIT(T2CONbits.TON);
	CLEARBIT(T1CONbits.TON);
	CLEARBIT(T3CONbits.TON);
    // Set Prescaler
	T2CONbits.TCKPS = 0b11;
	T1CONbits.TCKPS = 0b11;
	T3CONbits.TCKPS = 0b00;
	// Set Clock Source
    CLEARBIT(T2CONbits.TCS)
	SETBIT(T1CONbits.TCS);
	CLEARBIT(T3CONbits.TCS)
    // Set Gated Timer Mode -> don't use gating
	CLEARBIT(T2CONbits.TGATE);
	CLEARBIT(T1CONbits.TGATE);
	CLEARBIT(T3CONbits.TGATE);
    // T1: Set External Clock Input Synchronization -> no sync
	CLEARBIT(T1CONbits.TSYNC);
    // Load Timer Periods
    PR2 = 100;
	PR1 = 125;
	PR3 = 65535;  // I am not sure on this!
    // Reset Timer Values
	TMR2 = 0x00;
	TMR1 = 0x00;
	TMR3 = 0X00;
    // Set Interrupt Priority
	IPC0bits.T2IP = 0x01;
	IPC0bits.T1IP = 0x01;
    // Clear Interrupt Flags
	CLEARBIT(IFS0bits.T2IF);
	CLEARBIT(IFS0bits.T1IF);
    // Enable Interrupts
	SETBIT(IEC0bits.T2IE);
	SETBIT(IEC0bits.T1IE);
    // Enable the Timers
	SETBIT(T2CONbits.TON);
	SETBIT(T1CONbits.TON);

}

void timer_loop()
{
    // print assignment information
    lcd_printf("Lab02: Int & Timer");
    lcd_locate(0, 1);
    lcd_printf("Group: CPS7");
    
    while(TRUE)
    {
        count = TMR3;
		
    }
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T1Interrupt(void)
{ // invoked every ??
	TOGGLELED(LED2_PORT);		
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T2Interrupt(void)
{ // invoked every ??
    TOGGLELED(LED1_PORT);
}

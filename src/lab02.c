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
    T1CONbits.TON = 0; 
    T3CONbits.TON = 0; 
    
    
    // Set Prescaler
    //1
    T3CONbits.TCKPS = 0b00;

    //256
    T2CONbits.TCKPS = 0b11;

    //256
    T1CONbits.TCKPS = 0b11;

    // Set Clock Source
    CLEARBIT(T2CONbits.TCS); //internal 12 mhz
    T1CONbits.TCS = 1; //external 32k
    CLEARBIT(T3CONbits.TCS); //internal 12 mhz
    
    // Set Gated Timer Mode -> don't use gating
    CLEARBIT(T2CONbits.TGATE);
    CLEARBIT(T1CONbits.TGATE);
    CLEARBIT(T3CONbits.TGATE);
    

    // T1: Set External Clock Input Synchronization -> no sync
    T1CONbits.TSYNC = 0;

    // Load Timer Periods
    PR2 = 936; // 2ms
    PR1 = 127; //1s
    PR3 = 65535; // highest period possible, 5ms
    
    // Reset Timer Values
    TMR1 = 0x00;
    TMR2 = 0x00;
    TMR3 = 0x00;

    // Set Interrupt Priority
    IPC0bits.T2IP = 0x01; 
    IPC0bits.T1IP = 0x01;
    IPC0bits.T3IP = 0x01;

    // Clear Interrupt Flags
    CLEARBIT(IFS0bits.T2IF);
    IFS0bits.T1IF = 0;
    CLEARBIT(IFS0bits.T3IF);

    // Enable Interrupts
    SETBIT(IEC0bits.T2IE);
    IEC0bits.T1IE = 1;
    SETBIT(IEC0bits.T3IE);

    // Enable the Timers
    SETBIT(T2CONbits.TON);
    T1CONbits.TON = 1;
    SETBIT(T3CONbits.TON);

    //machine is Fcy = 12,8 MHz
    //Timer1 with 1:256 prescaler
    //T =  (PR1 + 1) x tick period
    // tick period = prescaler / Fcy = 256 / 12,800,000 = 20 µs
    

}

void timer_loop()
{
    // print assignment information
    lcd_printf("Lab02: Int & Timer");
    lcd_locate(0, 1);
    lcd_printf("Group: Aylin /r Ahmet /r Lavinda /r");
    
    while(TRUE)
    {
        
    }
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T1Interrupt(void)
{ // invoked every ??
    
}

void __attribute__((__interrupt__, __shadow__, __auto_psv__)) _T2Interrupt(void)
{ // invoked every ??
    
}

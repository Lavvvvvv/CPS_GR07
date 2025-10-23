#include <xc.h>
#include <p33Fxxxx.h>

//do not change the order of the following 2 definitions
#define FCY 12800000UL 
#include <libpic30.h>

#include "lcd.h"
#include "led.h"

/* Configuration of the Chip */
#pragma config FNOSC = PRIPLL   // Initial Oscillator Source Selection = Primary Oscillator with PLL
#pragma config POSCMD = XT      // Primary Oscillator Mode = XT
#pragma config FWDTEN = OFF     // Watchdog Timer Enable = OFF

void timer1_init(void);
void __attribute__((__interrupt__)) _T1Interrupt(void);

volatile int counter = 0;

int main() {
    // Init LCD and LEDs
    lcd_initialize();
    led_init();

    lcd_clear();
    lcd_locate(0, 0);
    lcd_printf("Group members#");

    lcd_locate(0, 1);
    lcd_printf("AYLIN");

    lcd_locate(0, 2);
    lcd_printf("LAVINDA");

    lcd_locate(0, 3);
    lcd_printf("AHMET");


    CLEARLED(LED1_TRIS);
    CLEARLED(LED2_TRIS);
    CLEARLED(LED3_TRIS);
    CLEARLED(LED4_TRIS);
    CLEARLED(LED5_TRIS);

    timer1_init();

    while (1) ;

    return 0;
}


void timer1_init(void) {
    CLEARBIT(T1CONbits.TON);
    CLEARBIT(T1CONbits.TCS);
    CLEARBIT(T1CONbits.TGATE);
    TMR1 = 0x00;
    T1CONbits.TCKPS = 0b11;    // 1:256 prescaler
    PR1 = 100000;               // Period
    IPC0bits.T1IP = 0x01;      // Priority
    IFS0bits.T1IF = 0;         // Clear flag
    IEC0bits.T1IE = 1;         // Enable interrupt
    SETBIT(T1CONbits.TON);     // Start Timer
}

void __attribute__((__interrupt__)) _T1Interrupt(void) {
    counter++; 
    lcd_locate(0, 6);
    lcd_printf("Counter value=%3u", counter);

    LATAbits.LATA4  = (counter >> 0) & 1;
    LATAbits.LATA5  = (counter >> 1) & 1;
    LATAbits.LATA9  = (counter >> 2) & 1;
    LATAbits.LATA10 = (counter >> 3) & 1;
    LATAbits.LATA0  = (counter >> 4) & 1;
    if (counter > 32) {
        counter = 0;
    }
    IFS0bits.T1IF = 0; // Clear interrupt flag
}

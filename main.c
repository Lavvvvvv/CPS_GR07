#include <xc.h>
#include <p33Fxxxx.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL 
#include <libpic30.h>

#include "lcd.h"
#include "led.h"

/* Configuration of the Chip */
// Initial Oscillator Source Selection = Primary (XT, HS, EC) Oscillator with PLL
#pragma config FNOSC = PRIPLL
// Primary Oscillator Mode Select = XT Crystal Oscillator mode
#pragma config POSCMD = XT
// Watchdog Timer Enable = Watchdog Timer enabled/disabled by user software
// (LPRC can be disabled by clearing the SWDTEN bit in the RCON register)
#pragma config FWDTEN = OFF

volatile uint8_t counter = 0;

int main(){
    //Init LCD and LEDs
    lcd_initialize();
    led_init();
	
    // Clear the Screen and reset the cursor
    lcd_clear();
    lcd_locate(0, 0);
    
    // Print Team members
    lcd_printf("Our Team Members are: \r Aylin \r Ahmet \r lavinda \r");
    
    
    //LED ON
    CLEARLED(LED1_TRIS); // Set Pin to Output
    CLEARLED(LED2_TRIS); // Set Pin to Output
    CLEARLED(LED3_TRIS); // Set Pin to Output
    CLEARLED(LED4_TRIS); // Set Pin to Output
    CLEARLED(LED5_TRIS); // Set Pin to Output
    //LED

    
    //machine is Fcy = 12,8 MHz
    //Timer1 with 1:256 prescaler
    //T =  (PR1 + 1) x tick period
    // tick period = prescaler / Fcy = 256 / 12,800,000 = 20 µs
    


    CLEARBIT(T1CONbits.TON);    // Disable Timer
    CLEARBIT(T1CONbits.TCS);    // Select internal instruction cycle clock
    CLEARBIT(T1CONbits.TGATE);  // Disable Gated Timer mode
    TMR1 = 0x00;                // Clear timer register
    T1CONbits.TCKPS = 0b11;     // Select 1:256 Prescaler PR1=(T.FCY/Prescaler)-1
    PR1 = 9999;                 // Load the period value
    IPC0bits.T1IP = 0x01;       // Set Timer1 Interrupt Priority Level
    CLEARBIT(IFS0bits.T1IF);    // Clear Timer1 Interrupt Flag
    SETBIT(IEC0bits.T1IE);      // Enable Timer1 interrupt
    SETBIT(T1CONbits.TON);      // Start Timer
    
    // Stop
    while(1)
        ;
}

//define interrupt function
void __attribute__ (( __interrupt__ )) _T1Interrupt(void){
    counter++;
    uint8_t bit1=counter & BV(0);
    uint8_t bit2=counter & BV(1);
    uint8_t bit3=counter & BV(2);
    uint8_t bit4=counter & BV(3);
    uint8_t bit5=counter & BV(4);

    if(bit5) {SETLED(LED1_PORT);}
        else {CLEARLED(LED1_PORT);}

    if(bit4) {SETLED(LED2_PORT);}
        else {CLEARLED(LED2_PORT);}

    if(bit3) {SETLED(LED3_PORT);}
        else {CLEARLED(LED3_PORT);}
        
    if(bit2) {SETLED(LED4_PORT);}
        else {CLEARLED(LED4_PORT);}

    if(bit1) {SETLED(LED5_PORT);}
        else {CLEARLED(LED5_PORT);}



    lcd_locate(0,5);
    lcd_printf(" counter : %u",counter);

    IFS0bits.T1IF = 0;


}

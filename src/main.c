#include <xc.h>
#include <p33Fxxxx.h>
//do not change the order of the following 2 definitions
#define FCY 12800000UL 
#include <libpic30.h>

#include "lcd.h"
#include "led.h"
#include "lab02.h"

/* Configuration of the Chip */
// Initial Oscillator Source Selection = Primary (XT, HS, EC) Oscillator with PLL
#pragma config FNOSC = PRIPLL
// Primary Oscillator Mode Select = XT Crystal Oscillator mode
#pragma config POSCMD = XT
// OSC2 Pin Function: OSC2 is Clock Output
#pragma config OSCIOFNC = ON
// Watchdog Timer Enable = Watchdog Timer enabled/disabled by user software
// (LPRC can be disabled by clearing the SWDTEN bit in the RCON register)
#pragma config FWDTEN = OFF


volatile uint16_t counterInter1=0;
volatile uint16_t counterInter2=0;
volatile uint16_t counterInter3=0;

int main(){
    //Init LCD and LEDs
    lcd_initialize();
    led_init();
	
    // Clear the Screen and reset the cursor
    lcd_clear();
    lcd_locate(0, 0);
    
    // Initialize Lab 02 Timers
    initialize_timer();
    
    // Start Lab02 Main Program
    timer_loop();
    uint16_t counter1;
    uint16_t counter2;
    uint16_t counter3;

    //LED ON
    CLEARLED(LED1_TRIS); // Set Pin to Output
    CLEARLED(LED2_TRIS); // Set Pin to Output
    CLEARLED(LED3_TRIS); // Set Pin to Output
    CLEARLED(LED4_TRIS); // Set Pin to Output
    CLEARLED(LED5_TRIS); // Set Pin to Output
    //LED
    
    // Stop
    while(1)

    if (counterInter1 ==1){
            counterInter1=0;
            counter1++;
            if (counter1%2==0){
                SETLED(LED1_PORT);} 
            else{
            CLEARLED(LED1_PORT);}

            



    }
    
    if (counterInter2 ==1){
        counterInter2=0;
        counter2++;
        if (counter2%2==0){
            SETLED(LED2_PORT);} 
        else{
            CLEARLED(LED2_PORT);}

    }

    if (counterInter2 ==1){

        counterInter2=0;
        counter2++;

    if (counter3%2==0){

        if(counter3%2000==0){

            SETLED(LED3_PORT);} 
        else{
            CLEARLED(LED3_PORT);}}

    }

    lcd_locate(0,5);
    lcd_printf("%02d : %02d .  %03d",TMR1,TMR2,TMR3);
}


void __attribute__ (( interrupt )) _T1Interrupt(void){

    counterInter1=1;

    IFS0bits.T1IF = 0;


}

void __attribute__ (( interrupt )) _T2Interrupt(void){

    counterInter2=1;
    

    IFS0bits.T2IF = 0;


}

void __attribute__ (( interrupt )) _T3Interrupt(void){

    counterInter3=1;


    

    IFS0bits.T3IF = 0;


}


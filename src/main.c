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


volatile int counter=0;
int main(){
    //Init LCD and LEDs
    lcd_initialize();
    led_init();
	
    // Clear the Screen and reset the cursor
    lcd_clear();
    lcd_locate(0, 0);
    lcd_printf("Group members#");
    
    lcd_locate(0, 1);
    lcd_printf("AYLIN");
    
    lcd_locate(0, 2);
    lcd_printf("LAVINDA");
    
    lcd_locate(0, 3);
    lcd_printf("AHMET ");
    
    __delay_ms(2000);
    
    CLEARLED(LED1_TRIS);
    CLEARLED(LED2_TRIS);
    CLEARLED(LED3_TRIS);
    CLEARLED(LED4_TRIS);
    CLEARLED(LED5_TRIS);
    while(1){
        lcd_locate(0, 6);
        
        lcd_printf("Counter value=%3u",counter);
        
        
        LATAbits.LATA4=(counter>>0)&1;
        LATAbits.LATA5=(counter>>1)&1;
        LATAbits.LATA9=(counter>>2)&1;
        LATAbits.LATA10=(counter>>3)&1;
        LATAbits.LATA0=(counter>>4)&1;
        
        counter++ ; 
        if(counter>32){
            counter=0x00;
            
        }
        
        __delay_ms(300);
    }
    return 0;
}

    
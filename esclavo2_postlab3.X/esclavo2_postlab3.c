//*****************************************************************************
/*
 * File:   main.c
 * Author: Julian Salazar
 * Created on 03 de agosto de 2023, 03:32 PM
 */
//*****************************************************************************
//*****************************************************************************
// Palabra de configuraci?n
//*****************************************************************************
// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//*****************************************************************************
// Definici?n e importaci?n de librer?as
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "ADC.h"
//*****************************************************************************
// Definici?n de variables
int ADC_voltaje, ADC_voltaje_nc;
//*****************************************************************************
#define _XTAL_FREQ 8000000

uint8_t temporal = 0;
//*****************************************************************************
// Definici?n de funciones para que se puedan colocar despu?s del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************
void setup(void);
//*****************************************************************************
// C?digo de Interrupci?n 
//*****************************************************************************
void __interrupt() isr(void){
   if(SSPIF == 1){ //SI EL PIC ESCLAVO ESTÁ EN COMUNICACIÓN
        PORTD = spiRead(); //EL PUERTO D RECIBE EL VALOR DEL ADC
        spiWrite(PORTB); //ENVÍA EL VALOR DEL PUERTO B
        SSPIF = 0; //BAJA LA COMUNICACIÓN
    }
   
    if (PIR1bits.ADIF == 1) //SI LA BANDERA DEL ADC EST? ACTIVADA   
    {
        if (ADCON0bits.CHS == 0b0000)
        {
            ADC_voltaje_nc = adc_read();
            PORTB = adc_read();
        }
        else 
        {
            PORTB = adc_read();
        }
        ADIF = 0;
        return;
    }

}
//*****************************************************************************
// C?digo Principal
//*****************************************************************************
void main(void) {
    setup();
    ADCON0bits.GO = 1; //REALIZA CONVERSI?N DEL ADC
    //*************************************************************************
    // Loop infinito
    //*************************************************************************
    while(1){
       //PORTB--;
       //__delay_ms(250);
        if (ADCON0bits.GO == 0)
        {
            __delay_ms(10);
            ADCON0bits.GO = 1; //REALIZA CONVERSI?N DEL ADC
        }
    }
    return;
}
//*****************************************************************************
// Funci?n de Inicializaci?n
//*****************************************************************************
void setup(void){
    ANSEL = 0b00000001;
    ANSELH = 0;
    
    TRISAbits.TRISA0 = 1;
    PORTA = 0x00;
    
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    
    //CONFIGURACI?N DEL OSCILADOR
    OSCCONbits.IRCF = 0b111; //8 Mhz
    OSCCONbits.SCS = 1; //RELOJ INTERNO
    
    adc_init(0); //CANAL ANAL?GICO 0, inicializa el ADC
    
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupci?n MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupci?n MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
   
}

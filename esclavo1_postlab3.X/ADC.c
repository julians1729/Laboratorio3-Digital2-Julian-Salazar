//INCLUYE LAS LIBRERIAS NECESARIAS
#include "ADC.h"



void adc_init (int channel)
{
    //CONFIGURACI?N DEL ADC
    ADCON0bits.ADCS = 0b10; //FOSC/32
    ADCON1bits.ADFM = 0; //JUSTIFICACI?N A LA IZQUIERDA
    ADCON1bits.VCFG1 = 0; //VSS 
    ADCON1bits.VCFG1 = 0; //VDD VOLTAJES DE REFERENCIA
    
    switch (channel){
        case 0:
            //CONFIGURACI?N DEL ADC
            ADCON0bits.CHS = 0b0000; //CANAL ANAL?GICO 0
            //FIN DE LA CONFIGURACI?N DEL ADC
            break;
        case 1:
            //CONFIGURACI?N DEL ADC
            ADCON0bits.CHS = 0b0001; //CANAL ANAL?GICO 1
            //FIN DE LA CONFIGURACI?N DEL ADC
            break;
        case 2:
            //CONFIGURACI?N DEL ADC
            ADCON0bits.CHS = 0b0010; //CANAL ANAL?GICO 2
            //FIN DE LA CONFIGURACI?N DEL ADC
            break;
        case 3:
            //CONFIGURACI?N DEL ADC
            ADCON0bits.CHS = 0b0011; //CANAL ANAL?GICO 3
            //FIN DE LA CONFIGURACI?N DEL ADC
            break;
        case 4:
            //CONFIGURACI?N DEL ADC
            ADCON0bits.CHS = 0b0100; //CANAL ANAL?GICO 4
            //FIN DE LA CONFIGURACI?N DEL ADC
            break;
        case 5:
            //CONFIGURACI?N DEL ADC
            ADCON0bits.CHS = 0b0101; //CANAL ANAL?GICO 5
            //FIN DE LA CONFIGURACI?N DEL ADC
            break;
        default:
            ADCON0bits.CHS = 0b0000;
            break;
    }
        
        //BANDERAS DEL ADC
    PIR1bits.ADIF = 0; //COLOCA LA BANDERA DEL ADC EN 0
    PIE1bits.ADIE = 1; //HABILITA LA BANDERA DEL ADC
    
    
        //FIN DE LAS BANDERAS DEL ADC
    
     __delay_us(50);
    ADCON0bits.ADON = 1; //HABILITA EL M?DULO ADC
    
    ADCON0bits.GO = 1; //REALIZA CONVERSI?N DEL ADC
    //FIN DE LA CONFIGURACI?N DEL ADC
    return;
};

int adc_read()
{
    return ADRESH; 
}

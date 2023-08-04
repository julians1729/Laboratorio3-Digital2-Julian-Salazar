
/* 
 * File: ADC.h   
 * Author: Julian Salazar
 */

#ifndef ADC_H
#define	ADC_H

#include <xc.h> 
#define _XTAL_FREQ 8000000 //FRECUENCIA DEL OSCILADOR 

//LIBRER?AS PARA EL ADC
void adc_init (int channel); //LIBRER?A DE INICIALIZACI?N DEL ADC
int adc_read(); //PROTOTIPO PARA OBTENER EL VALOR DEL ADC


#endif	/* XC_HEADER_TEMPLATE_H */
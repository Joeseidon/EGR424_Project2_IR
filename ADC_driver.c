/*
 * ADC_driver.c
 *
 *  Created on: April 2018
 *      Author: Lourens Willekes
 */

#include "ADC_driver.h"


void ADC_init(void)
{
    // initializing adc clk = 3MHz
    MAP_ADC14_enableModule();
    MAP_ADC14_initModule(ADC_CLOCKSOURCE_SMCLK, ADC_PREDIVIDER_1,
                ADC_DIVIDER_1, 0);

    // configure gpio 5.5 for analog input
    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5,
                GPIO_PIN5, GPIO_TERTIARY_MODULE_FUNCTION);

    // configure adc mem 0 for 3.3V
    ADC14->MCTL[0] = ADC14_MCTLN_INCH_0;    // ref+=AVcc, channel = A0

    MAP_ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);

    ADC14->IER0 = ADC14_IER0_IE0;           // Enable ADC14IFG.0

    MAP_Interrupt_enableInterrupt(INT_ADC14);

    // enable conversion
    MAP_ADC14_enableConversion();

}

void ADC_read(uint16_t *mem0)
{
    // start next conversion
    MAP_ADC14_toggleConversionTrigger();
}

/* ADC Interrupt Handler. This handler is called whenever there is a conversion
 * that is finished for ADC_MEM0.
 */
void ADC14_IRQHandler(void)
{
    uint64_t status = MAP_ADC14_getEnabledInterruptStatus();
    MAP_ADC14_clearInterruptFlag(status);

    if(ADC_INT0 & status){
        // and get the result
        raw_adc = MAP_ADC14_getResult(ADC_MEM0);
        ADC_Ready = 1;
    }
}

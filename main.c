/*
 * -------------------------------------------
 *    MSP432 DriverLib - v3_21_00_05 
 * -------------------------------------------
 *
 * --COPYRIGHT--,BSD,BSD
 * Copyright (c) 2016, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
/******************************************************************************
 * MSP432 Empty Project
 *
 * Description: An empty project that uses DriverLib
 *
 *                MSP432P401
 *             ------------------
 *         /|\|                  |
 *          | |                  |
 *          --|RST               |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 *            |                  |
 * Author: 
*******************************************************************************/
/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>

/* User Libraries */
#include "clockConfig.h"
#include "ADC_driver.h"
#include "systick_init.h"
#include "servo.h"

int IR_Flag, ADC_Ready;
uint16_t raw_adc,duty_cycle=0,period=50;
float distance;


int main(void)
{
    /* Stop Watchdog  */
    MAP_WDT_A_holdTimer();

    /* Setup 48MHz External Clock to Source MCLK and SMCLK (3MHz) */
    clockStartUp();

    /* Initialize ADC */
    ADC_init();

    /* Setup Systick */
    SysTick_Init();
    SysTick_Load(100);
    SysTick_Start(&IR_Flag);

    /* Enabling the FPU for floating point operation */
    MAP_FPU_enableModule();
    MAP_FPU_enableLazyStacking();

    /* Enable Motor Driver */
    P3->DIR |= BIT5;
    P3->OUT |= BIT5;

    /* Set Initial Direction */
    P3->DIR |= BIT6;
    P3->OUT |= BIT6;

    /* Initialize Servo Driver */
    //PWM_Init(period,duty_cycle);

    //configure timerA for pwm
    //SMCLK=3MHz
    //Period = 3MHz*2/(50Hz*4*8) = 3750 (up-down mode)
    //left-duty cycle = 188
    //right-duty cycle = 375
    //center-duty cycle = 281
    PWM_Init((3750-1),0); //initialize at stop

    /*PWM_Duty1(188);

    int i =0;
    for(i=0; i<10000000; i++);

    PWM_Duty1(280);
    for(i=0; i<10000000; i++);

    PWM_Duty1(375);
    for(i=0; i<10000000; i++);

    PWM_Duty1(280);
    for(i=0; i<10000000; i++);*/

    while(1)
    {
        if(IR_Flag){
            // start next conversion
            MAP_ADC14_toggleConversionTrigger();
            IR_Flag = 0;
        }

        if(ADC_Ready){
            ADC_Ready = 0;
            //Convert to usable form
            distance = ((raw_adc * 3.3 ) / 16384.0);
        }


    }

}

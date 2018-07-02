/*
 * servo.c
 *
 *  Created on: Jun 14, 2018
 *      Author: joe
 */


#include <servo.h>
#include <stdio.h>
#include <stdint.h>
#include "msp.h"

//calculated for 3MHz clock and 50Hz Period
const uint16_t right_count = 375;
const uint16_t left_count = 188;
const uint16_t center_count = 281;
const uint16_t stop_count = 0;

void servo_setup(void){
    P2DIR |= 0x10;          // make P2.4 output
    P2SEL0 |= 0x10;
    P2SEL1 &= ~0x10;        // configure P2.4 as Timer A0.1 function
}

void PWM_Init(uint16_t period, uint16_t duty){
    if(duty >= period) return;  // bad input
    TA0CCTL0 = 0x0080;          // CCI0 toggle
    TA0CCR0 = period;           // Squarewave 4*period*8 is
    TA0CCTL1 = 0x0040;          // CCR1 toggle/reset
    TA0CCR1 = duty;             // CCR1 duty cycle is duty/period

    // bit  mode
    // 9-8  20    TASSEL, SMCLK=3MHz
    // 7-6  00    ID, divide by 1
    // 5-4  11    MC, up-down mode
    // 2    0     TACLR, no clear
    // 1    0     TAIE, no interrupt
    // 0          TAIFG
    TA0CTL = 0x02f0;            // SMCLK=3MHz, divide by 1, up-down mode
}

//left-duty cycle = 188 (1ms)
//right-duty cycle = 375 (2ms)
//center-duty cycle = 281 (1.5ms)
void PWM_Duty(uint16_t duty){
  if(duty >= TA0CCR0) return; // bad input
  TA0CCR1 = duty;        // CCR1 duty cycle is duty1/period
}

void servo_move(move x){
    switch(x){
        case LEFT:
            PWM_Duty(left_count);
            break;
        case CENTER:
            PWM_Duty(center_count);
            break;
        case RIGHT:
            PWM_Duty(right_count);
            break;
        case STOP:
            PWM_Duty(stop_count);
            break;
    }
}

void servo_pattern(move* x, int num){
    int count;
    for(count=0; count<num; count++){
        move temp = x[count];
        servo_move(temp);

        //simply delay
        int d;
        for(d=0; d<1000000; d++);
    }

}

/*
 * servo.c
 *
 *  Created on: Jun 14, 2018
 *      Author: joe
 */


#include <servo.h>

int servo_setup(void){
    int successful = 1;

    return successful;
}

void PWM_Init(uint16_t period, uint16_t duty1){
  if(duty1 >= period) return; // bad input
  P2DIR |= 0x10;          // make P2.4 output
  P2SEL0 |= 0x10;
  P2SEL1 &= ~0x10;        // configure P2.4 as Timer A0.1 function
  TA0CCTL0 = 0x0080;      // CCI0 toggle (P7.3 free for other use)
  TA0CCR0 = period;       // Squarewave 4*period*8 is
  TA0CCTL1 = 0x0040;      // CCR1 toggle/reset
  TA0CCR1 = duty1;        // CCR1 duty cycle is duty1/period
  TA0CTL = 0x0230;        // SMCLK=12MHz, divide by 1, up-down mode
// bit  mode
// 9-8  20    TASSEL, SMCLK=12MHz
// 7-6  00    ID, divide by 1
// 5-4  11    MC, up-down mode
// 2    0     TACLR, no clear
// 1    0     TAIE, no interrupt
// 0          TAIFG
}
//***************************PWM_Duty1*******************************
// change duty cycle of PWM output on P2.4
// Inputs:  duty1
// Outputs: none
// period of P2.4 is period*0.1667us, duty cycle is duty1/period
void PWM_Duty1(uint16_t duty1){
  if(duty1 >= TA0CCR0) return; // bad input
  TA0CCR1 = duty1;        // CCR1 duty cycle is duty1/period
}

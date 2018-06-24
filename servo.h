/*
 * servo.h
 *
 *  Created on: Jun 14, 2018
 *      Author: joe
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>
//Movement enum
typedef enum move{
    STOP,
    LEFT,
    CENTER,
    RIGHT
}move;
void servo_setup(void);
void PWM_Duty(uint16_t duty);
void PWM_Init(uint16_t period, uint16_t duty);
void servo_move(move x);
void servo_pattern(move* x,int num);

#endif /* SERVO_H_ */

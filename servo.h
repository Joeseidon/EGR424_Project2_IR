/*
 * servo.h
 *
 *  Created on: Jun 14, 2018
 *      Author: joe
 */

#ifndef SERVO_H_
#define SERVO_H_

#include <stdint.h>

int servo_setup(void);

void PWM_Duty1(uint16_t duty1);
void PWM_Init(uint16_t period, uint16_t duty1);

#endif /* SERVO_H_ */

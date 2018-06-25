/*
 * systick_init.h
 *
 *  Created on: Jun 12, 2018
 *      Author: joe
 */

#ifndef SYSTICK_INIT_H_
#define SYSTICK_INIT_H_


void SysTick_Init(void);
// ---- Configurable Systick delay fromm 1 ms to 5592 ms
void SysTick_Load(uint8_t delay);

void SysTick_Start(int *flag_address);

void SysTickISR(void);

#endif /* SYSTICK_INIT_H_ */

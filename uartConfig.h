/*
 * uartConfig.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua
 */

#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_

extern void UART0_init(void);

extern void EUSCIA0_Interrupt_Enable(void);

extern void Master_Interrupt_Enable(void);

extern void EUSCIA0_IRQHandler(void);

#endif /* UARTCONFIG_H_ */

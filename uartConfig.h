/*
 * uartConfig.h
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua
 */

#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_

/* Initializes EUSCI_A0 */
extern void UART0_init(void);

/* Enables EUSCI_A0 interrupts */
extern void EUSCIA0_Interrupt_Enable(void);

/* Enables master interrupt */
extern void Master_Interrupt_Enable(void);

/* EUSCI_A0 ISR */
extern void EUSCIA0_IRQHandler(void);

/* Sends a single character to terminal */
void UART_Send(char c);

/* Sends a string to terminal */
void UART_Send_String(char *string);

#endif /* UARTCONFIG_H_ */

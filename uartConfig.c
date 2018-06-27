/*
 * uartConfig.c
 *
 *  Created on: Jun 27, 2018
 *      Author: Joshua
 */

#include "uartConfig.h"
#include "driverlib.h"

extern int IR_Flag, ADC_Ready, servo_triggered;

void UART0_init(void)
{
	EUSCI_A0->CTLW0 |= BIT0;  	// Enables software reset mode
	EUSCI_A0->MCTLW &= ~BIT0; 	// Disables over sampling mode
	EUSCI_A0->BRW = 0x138;		// Sets baud rate to 9600

	// Configures the control register for one stop bit, no parity,
	//	SMCLK clock source, and 8-bit data size
	EUSCI_A0->CTLW0 &= ~(0x9800);
	EUSCI_A0->CTLW0 |= BIT7;

	MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1,GPIO_PIN2, GPIO_PRIMARY_MODULE_FUNCTION);
	MAP_GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P1,GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);

	EUSCI_A0->CTLW0 &= ~BIT0;	// Disables software reset mode

	EUSCI_A0->IE |= BIT0;		// Enables receive interrupts
}

void EUSCIA0_Interrupt_Enable(void)
{
	MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
}

void Master_Interrupt_Enable(void)
{
	MAP_Interrupt_enableMaster();
}

void EUSCIA0_IRQHandler(void)
{
	if(EUSCI_A0->IV & 0x02)
	{
		int value = (int)(EUSCI_A0->RXBUF);

		char buffer[50];
		sprintf(buffer,"Value: %d\n\r", value);
		UART_Send_String(buffer);

		if(value == 49)
		{
			IR_Flag = 1;
		}
		else if(value == 50)
		{
		    servo_triggered = 1;
		}
	}
	else
	{
		char* string = "Invalid input.\n\r"
	}
}

void UART_Send(char c)
{
	while((EUSCI_A0->IFG & 0x02) == 0);
	EUSCI_A0->TXBUF = c;
}

void UART_Send_String(char *string)
{
	int i , len = strlen(string);
	for(i=0; i<len; i++)
	{
		while((EUSCI_A0->IFG & 0x02) == 0);
		EUSCI_A0->TXBUF = *string++;
	}
}

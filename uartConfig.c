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
	MAP_Interrupt_enableInterrupt(INT_EUSCIA0);  // Enables EUSCI_A0 interrupts
}

void Master_Interrupt_Enable(void)
{
	MAP_Interrupt_enableMaster();	// Enables master interrupts
}

void EUSCIA0_IRQHandler(void)
{
	if(EUSCI_A0->IV & 0x02)	// Clears the EUSCI_A0->IFG register based on the received interrupt
	{
		int value = (int)(EUSCI_A0->RXBUF);	// Reads in the character from the terminal window

		char buffer[50];
		sprintf(buffer,"Value entered: %c\n\r", value);	// Prints out the value entered
		UART_Send_String(buffer);

		if(value == 49)
		{
			IR_Flag = 1;  // Sets the IR_Flag to get IR readings
		}
		else if(value == 50)
		{
		    servo_triggered = 1;	// Sets the servo_triggered flag to start servo motor movement
		}
	}
	else
	{
		char* string = "Invalid input.\n\r";	// Prints out invalid input if input is not a 1 or a 2
		UART_Send_String(string);
	}
}

void UART_Send(char c)
{
	while((EUSCI_A0->IFG & 0x02) == 0);	// Waits while the buffer is empty
	EUSCI_A0->TXBUF = c;	// Sends the character across the buffer
}

void UART_Send_String(char *string)
{
	int i , len = strlen(string);
	for(i=0; i<len; i++)	// Goes through the entire string
	{
		while((EUSCI_A0->IFG & 0x02) == 0);	// Waits while the buffer is empty
		EUSCI_A0->TXBUF = *string++;	// Sends the character across the buffer
	}
}

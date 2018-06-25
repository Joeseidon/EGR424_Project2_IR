/*
 * systick_init.c
 *
 *  Created on: Jun 12, 2018
 *      Author: joe
 */

#include "driverlib.h"
#include "msp.h"

int *flag;

// ----- Initialize SysTick ------
void SysTick_Init(void)
{
    SysTick -> CTRL = 0; // disable SysTick during setup
    SysTick -> LOAD = 0x00FFFFFF; // maximum reload value
    SysTick -> VAL = 0; // any write to current clears it
    SysTick -> CTRL = 0x00000005; // enable SysTick, 3MHz, no interrupts
}
// ---- Configurable Systick delay
void SysTick_Load(uint8_t delay)
{
    SysTick -> LOAD = ((delay*48000) - 1); // 1ms count down to zero
}

void SysTick_Start(int *flag_address){
    //SysTick -> VAL = 0; // any write to CVR clears it
    MAP_SysTick_enableInterrupt();
    flag = flag_address;
}

void SysTickISR(void){
    tick_count++;
    *flag=1;
}
void reset_tick_count(void){
    tick_count = 0;
}

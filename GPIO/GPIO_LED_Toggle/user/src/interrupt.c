/*
 * Example_Multi_Timer_Blinky_ISR.c
 *
 *  Created on: Apr 8, 2016
 *      Author:
 */

#include "LPC8xx.h"
#include "lpc8xx_wkt.h"
#include "lpc8xx_mrt.h"
#include "lpc8xx_swm.h"
#include "user_gpio.h"

void SysTick_Handler(void) 
{
	// Clear the interrupt flag by reading the SysTick_CTRL register
	uint32_t temp = SysTick->CTRL;
	LEDs_Toggle(RED);
    LEDs_Toggle(BLUE);
    LEDs_Toggle(GREEN);
	return;
}



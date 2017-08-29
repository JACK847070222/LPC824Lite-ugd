#include "LPC8xx.h"			/* LPC8xx Peripheral Registers */
#include "lpc8xx_syscon.h"


#define SYSTICK_TIME        12000000 - 1        // default set to .4 second @ 30 MHz (clocked by PLL)

void SysTickInit(void) 
{
    // Configure the SYSTICK
    // clock = system_clock, tick interrupt enabled
    SysTick->CTRL = (1<<SysTick_CTRL_CLKSOURCE_Pos) | (1<<SysTick_CTRL_TICKINT_Pos);
    // Reload value
    SysTick->LOAD = SYSTICK_TIME;
    // Clear the counter and the countflag bit by writing any value to SysTick_VAL
    SysTick->VAL = 0;
    // Start the SYSTICK
    SysTick->CTRL |= 1<<SysTick_CTRL_ENABLE_Pos;
    // Enable the SYSTICK interrupt in the NVIC
    NVIC_EnableIRQ(SysTick_IRQn);

	return;
}





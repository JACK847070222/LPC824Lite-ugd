
/*
===============================================================================
 Name        : Main.c
 Author      : $(Jack)
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "main.h"
#include "user_systick.h"
#include "user_gpio.h"


// Program flow:
// 1. Configure clocking (IRC_Only_SystemInit function)
//   A. SYSPLLCLKSEL = IRC (which is not used, see clocking diagram in SYSCON chapter of user manual)
//   B. MAINCLKSEL = IRC oscillator
//   C. SYSAHBCLKDIV = 1
// 2. Turn on clocks to peripherals
// 3. Configure the WKT
//    A. Run from IRC/16 (this is the default clock)
//    B. Enable the WKT interrupt
// 4. Configure the SYSTICK
//    A. SYST_CSR(2) = 1 (clksource = system clock div-by-1) SYST_CSR(1) = 1 int enabled
//    B. SYST_RVR = value from header file
//    C. Clear the SYST_CVR register by writing to it
//    D. Enable the interrupt in the NVIC
// 5. Configure the MRT channels 0 and 1
//    A. Write to CTRL registers 1<<0 | 0<<1 (enable interrupt and Repeat mode)
//    B. Enable the MRT0 interrupt in the NVIC
// 6. Enter the main while(1) loop
//    A. Light an LED, start a timer, and wait for two interrupts
//       First one turns off the LED, 2nd one stops the timer and switches to the next LED.
//    B. Proceed to the next timer


int main(void) 
{
//    uint32_t i;
    SysTickInit();
    GPIOInit();     
    Init_LEDs();

//	SystemCoreClockUpdate ();
//    i = SystemCoreClock;
    while(1) 
    {
        
    } // end of while(1)
	
} // end of main

/*****************************************************************************
** Function name:		Setup_LPC8xx_Low_Power
**
** Description:		    Sets PDAWAKECFG = PDRUNCFG and turns off some clocks.
**
** Parameters:			None
** Returned value:		void
**
*****************************************************************************/
void Setup_LPC8xx_Low_Power() 
{
	// Configure PDAWAKECFG
	LPC_SYSCON->PDAWAKECFG = LPC_SYSCON->PDRUNCFG;

	// Turn clocks off to unused peripherals
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(SWM | GPIO | IOCON);

	return;
}

/*****************************************************************************
** Function name:		IRC_Only_SystemInit
**
** Description:		    Configures the clocking to run directly from the 12 MHz IRC
**
** Parameters:			None
** Returned value:		void
**
*****************************************************************************/
void IRC_Only_SystemInit(void) 
{
	LPC_SYSCON->SYSPLLCLKSEL  = 0;                  // Selects IRC as input to the PLL which we won't be using
	LPC_SYSCON->SYSPLLCLKUEN  = 0;
	LPC_SYSCON->SYSPLLCLKUEN  = 1;                  // Update Clock Source
	while (!(LPC_SYSCON->SYSPLLCLKUEN & 0x01));     // Wait Until Updated

	LPC_SYSCON->MAINCLKSEL    = 0;                  // Select IRC as input to main clock select mux
	LPC_SYSCON->MAINCLKUEN    = 0;
	LPC_SYSCON->MAINCLKUEN    = 1;                  // Update MCLK Clock Source
	while (!(LPC_SYSCON->MAINCLKUEN & 0x01));       // Wait Until Updated

	LPC_SYSCON->SYSAHBCLKDIV  = 1;                  // System clock = main clock div-by-1

	LPC_FLASHCTRL->FLASHCFG = 0;                    // FLASH access time is always 1 system clock
}

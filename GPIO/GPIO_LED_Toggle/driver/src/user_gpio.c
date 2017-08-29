#include "LPC8xx.h"			/* LPC8xx Peripheral Registers */
#include "lpc8xx_gpio.h"
#include "lpc8xx_syscon.h"
#include "lpc8xx_swm.h"
#include "user_gpio.h"

/*该文件将lpc8xx_gpio.c内容进行整合，工程中删除lpc8xx_gpio.c*/
/*****************************************************************************
** Function name:	GPIOInit
**
** Description:		Enable clock, then reset the GPIO module.
** 					See lpc8xx_syscon.h for register bit definitions.
**
** Parameters:		None
**
** Returned value:	None
*****************************************************************************/
void GPIOInit( void )
{
    /* Enable AHB clock to the GPIO domain. */
    LPC_SYSCON->SYSAHBCLKCTRL |= GPIO;

    /* Peripheral reset to the GPIO module. '0' asserts, '1' deasserts reset. */
    LPC_SYSCON->PRESETCTRL &= GPIO_RST_N;
    LPC_SYSCON->PRESETCTRL |= ~GPIO_RST_N;
    return;
}


/*****************************************************************************
** Function name:		GPIOGetPinValue
**
** Descriptions:		Read Current state of port pin, PIN register value
**
** parameters:			port num, bit position
** Returned value:		None
**
*****************************************************************************/
uint32_t GPIOGetPinValue( uint32_t portNum, uint32_t bitPosi )
{
    uint32_t regVal = 0;	

    if( bitPosi < 0x20 )
    {	
        if ( LPC_GPIO_PORT->PIN0 & (0x1<<bitPosi) )
        {
            regVal = 1;
        }
    }
    else if( bitPosi == 0xFF )
    {
        regVal = LPC_GPIO_PORT->PIN0;
    }
    return ( regVal );		
}

/*****************************************************************************
** Function name:		GPIOSetBitValue
**
** Descriptions:		Set/clear a bit in a specific position
**
** parameters:			port num, bit position, bit value
** 						
** Returned value:		None
**
*****************************************************************************/
void GPIOSetBitValue( uint32_t portNum, uint32_t bitPosi, uint32_t bitVal )
{
    if ( bitVal )
    {
        LPC_GPIO_PORT->SET0 = 1<<bitPosi;
    }
    else
    {
        LPC_GPIO_PORT->CLR0 = 1<<bitPosi;
    }
    return;
}

/*****************************************************************************
** Function name:		GPIOSetDir
**
** Descriptions:		Set the direction in GPIO port
**
** parameters:			portNum, bit position, direction (1 out, 0 input)
** 						
** Returned value:		None
**
*****************************************************************************/
void GPIOSetDir( uint32_t portNum, uint32_t bitPosi, uint32_t dir )
{
  if( dir )
  {
		LPC_GPIO_PORT->DIR0 |= (1<<bitPosi);
  }
  else
  {
		LPC_GPIO_PORT->DIR0 &= ~(1<<bitPosi);
  }
  return;
}


/*****************************************************************************
** Function name:		Config_LEDs
**
** Description:			Makes port bit(s) an output driving '1' (for LED off).
** 						Typically called with '1' in any port bit positions
** 						which have a board LED attached.
**
** parameters:			bits ('1' in a bit position corresponding to an LED)
**
** Returned value:		None
**
*****************************************************************************/
void Init_LEDs(void) 
{  
    GPIOSetBitValue( PORT0, RED, 1);
    GPIOSetBitValue( PORT0, BLUE, 1);
    GPIOSetBitValue( PORT0, GREEN, 1);
    GPIOSetDir( PORT0, RED, OUTPUT );
    GPIOSetDir( PORT0, BLUE, OUTPUT );
    GPIOSetDir( PORT0, GREEN, OUTPUT );
}



/*****************************************************************************
** Function name:		LEDs_Off
**
** Description:			Makes port bit(s) drive '1' (for LED off).
** 						Typically called with '1' in any port bit positions
** 						which have a board LED attached.
**
** parameters:			bits ('1' in a bit position corresponding to an LED)
**
** Returned value:		None
**
*****************************************************************************/
void LEDs_Off(uint32_t bits) 
{
    GPIOSetBitValue( PORT0, bits, 1);
	//LPC_GPIO_PORT->SET0  = bits;           // Write '1's to bits corresponding to requested LEDs
}



/*****************************************************************************
** Function name:		LEDs_On
**
** Description:			Makes port bit(s) drive '0' (for LED on).
** 						Typically called with '1' in any port bit positions
** 						which have a board LED attached.
**
** parameters:			bits ('1' in a bit position corresponding to an LED)
**
** Returned value:		None
**
*****************************************************************************/
void LEDs_On(uint32_t bits) 
{
    GPIOSetBitValue( PORT0, bits, 0);
	//LPC_GPIO_PORT->CLR0  = bits;           // Write '1's to bits corresponding to requested LEDs
}

void LEDs_Toggle(uint32_t bits) 
{
	LPC_GPIO_PORT->NOT0  = 1<<bits;           // Write '1's to bits corresponding to requested LEDs
}






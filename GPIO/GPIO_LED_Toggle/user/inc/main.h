
#ifndef MAIN_H_
#define MAIN_H_
#include "LPC8xx.h"
#include "core_cm0plus.h"
#include "lpc8xx_syscon.h"
#include "lpc8xx_swm.h"
#include "lpc8xx_gpio.h"


#define WKT_TIME            2400000/16 - 1      // default set to .2 second @ 12 MHz (clocked by IRC)

#define MRT0_TIME           18000000            // default set to .6 second @ 30 MHz (clocked by PLL)
#define MRT1_TIME           24000000            // default set to .8 second @ 30 MHz (clocked by PLL)


#endif /* MAIN_H_ */


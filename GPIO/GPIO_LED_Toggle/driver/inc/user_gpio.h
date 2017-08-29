/*
 * utilities.h
 *
 *  Created on: Feb 16, 2016
 *      Author:
 */

#ifndef USER_GPIO_H_
#define USER_GPIO_H_

#include "stdint.h"
#include "board.h"

void Init_LEDs(void);
void LEDs_Off(uint32_t bits);
void LEDs_On(uint32_t bits);
void LEDs_Toggle(uint32_t bits);

#endif /* USER_GPIO_H_ */

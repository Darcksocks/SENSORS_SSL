/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "serial.h"

int main(void)
{
	serial_init(9600);
	serial_puts("<3");
	for(;;);
}

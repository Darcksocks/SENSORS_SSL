/*
 * Spi.h
 *
 *  Created on: 10 janv. 2019
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "stm32f4xx_tim.h"
#include "math.h"

void init_clock_spi(void);

void init_spi_Optical(void);

void SPI_ENABLE_Optical(void);

uint8_t SPI_SENDATA_Comm(uint8_t data_comme);



#endif /* SPI_H_ */

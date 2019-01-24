/*
 * Optical_flow.h
 *
 *  Created on: 9 janv. 2019
 */

#ifndef OPTICAL_FLOW_H_
#define OPTICAL_FLOW_H_

/*fonction definition clock*/
void init_clock_spi(void);

/*fonction initialisant la spi du capteur optique*/
void init_spi_Optical(void);

/*fonction activant le port spi2*/
void SPI_ENABLE_Optical(void);

/*fonction gerant la reception des donn�es*/
uint16_t SPI_RECEIVEDATA_Optical(uint8_t data_optical);

/*fonction signalant si la spi est libre*/
uint8_t SPI_BUSY_Optical(uint8_t SPI_BUSY);

/*fonction signalant si la recpetion de la spi est libre*/
uint8_t SPI_RX_BUSY_Optical(uint8_t SPI_RX_BUSY);

/*fonction raz flag spi2*/
void SPI_CLEAR_BUSY(void);

#endif /* OPTICAL_FLOW_H_ */
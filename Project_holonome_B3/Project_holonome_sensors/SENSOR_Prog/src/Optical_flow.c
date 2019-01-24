/*
 * Optical_flow.c
 *
 *  Created on: 9 janv. 2019
 */

#include "Optical_flow.h"
#include <stm32f4xx.h>
#include <stm32f4_discovery.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_rcc.h>
#include <stdint.h>


void init_clock_spi(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
	/* APB2 correspond a la configuration de la clock en haute vitesse
	 * on active donc la clock en haute vitesse pour le port spi1
	 */
}

void init_spi_Optical(void)
{
	SPI_I2S_DeInit(SPI4);
	SPI_InitTypeDef SPI_Optical;
	SPI_Optical.SPI_Direction = SPI_Direction_2Lines_RxOnly;
	SPI_Optical.SPI_Mode = SPI_Mode_Master;
	SPI_Optical.SPI_DataSize = SPI_DataSize_8b;
	SPI_Optical.SPI_CPOL = SPI_CPOL_High;
	SPI_Optical.SPI_CPHA = SPI_CPHA_2Edge;
	SPI_Optical.SPI_NSS = SPI_NSS_Hard;
	SPI_Optical.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_Optical.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Optical.SPI_CRCPolynomial = 0;
	SPI_Init(SPI4, &SPI_Optical);

	/* Configure le port 2 de la spi, avec comme paramètres
	 * --> reception seule 2 lignes
	 * --> spi en mode maitre
	 * --> trame en format 8 bits
	 * --> etat de repos a l'etat haut
	 * --> capture sur deuxieme front
	 * --> desactive le slave select logiciel
	 * --> divise la frequence par 4
	 * --> configure le msb comme premier bit transmis
	 * --> desactive la CRC
	 */
}

void SPI_ENABLE_Optical(void)
{
	SPI_Cmd(SPI4, ENABLE);
	/*active la communication SPI sur le port 4*/
}

uint16_t SPI_RECEIVEDATA_Optical(uint16_t data_optical)
{
	SPI_I2S_ReceiveData(SPI4);
	data_optical = SPI4;
	return data_optical;
	/*fonction permettant la reception de la donnée du capteur optique de
	 * souris
	 */
}

uint8_t SPI_BUSY_Optical(uint8_t SPI_BUSY)
{
	SPI_BUSY = SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_BSY);
	return SPI_BUSY;
	/*fonction permettant de savoir si la spi est libre*/
}

uint8_t SPI_RX_BUSY_Optical(uint8_t SPI_RX_BUSY)
{
	SPI_RX_BUSY = SPI_I2S_GetFlagStatus(SPI4, SPI_I2S_FLAG_RXNE);
	return SPI_RX_BUSY;
	/*fonction permettant de savoir si la reception de la spi est libre*/
}

void SPI_CLEAR_BUSY(void)
{
	SPI_I2S_ClearFlag(SPI4, SPI_I2S_FLAG_BSY);
	SPI_I2S_ClearFlag(SPI4, SPI_I2S_FLAG_RXNE);
	/*remet à zero les flags de status*/
}

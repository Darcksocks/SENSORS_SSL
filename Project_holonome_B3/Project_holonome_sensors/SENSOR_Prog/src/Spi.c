/*
 * Spi.c
 *
 *  Created on: 10 janv. 2019
 */

#include <stm32f4_discovery.h>
#include <stm32f4xx.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_gpio.h>
#include "Spi.h"
#include <stm32f4xx_rcc.h>
#include <stdint.h>


void init_clock_spi(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
	/* APB2 correspond a la configuration de la clock en haute vitesse
	 * on active donc la clock en haute vitesse pour le port spi1
	 * */
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
	SPI_Init(SPI2, &SPI_Optical);

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
	/*active la communication SPI sur le port 2*/
}

uint8_t SPI_SENDDATA_Comm(uint8_t data_comm)
{
	SPI_I2S_SendData(SPI4, data_comm);
	return data_comm;
	/*fonction ayant pour but d'envoyer une donnée sur le port de la
	 * communication
	 */
}

uint8_t SPI_RECEIVEDATA_Optical(uint8_t data_optical)
{
	SPI_I2S_ReceiveData(SPI4);
	return SPI4;
	/*fonction permettant la reception de la donnée du capteur optique de
	 * souris
	 */
}



/* cette fonction sert a configurer le port de spi utilisé,
 * ainsi qu'a configuré la communication spi
 *
 * SPIx peut valoir SPI1 pour le port un, SPI2 pour le port deux etc
 *
 * SPI_InitStruct correspond a la configuration de la spi (structure)
 * --> SPI_Direction : IS_SPI_DIRECTION_MODE(MODE)
 * avec MODE = SPI_Direction_2Lines_FullDuplex ( configure spi classique)
 * 			 = SPI_Direction_2Lines_RxOnly ( configure spi classique mais reception seul)
 * 			 = SPI_Direction_1Lines_Rx ( configure spi 1 line reception seule)
 * 			 = SPI_Direction_1Line_TX ( configure spi 1 line emission seule)
 *
 * --> SPI_Mode : IS_SPI_MODE(MODE)
 * avec MODE = SPI_Mode_Master (configure en maitre)
 * 			 = SPI_Mode_Slave ( configure en esclave)
 *
 * --> SPI_DataSize : IS_SPI_DATASIZE(DATASIZE)
 * avec DATASIZE = SPI_DataSize_16b (configure le format de la spi en 16 bits)
 * 				 = SPI_Datasize_8b (configure le format de la spi en 8 bits)
 *
 * --> SPI_CPOL : IS_SPI_CPOL(CPOL)
 * avec CPOL = SPI_CPOL_Low (configure la polarité inactive à l'état bas)
 * 			 = SPI_CPOL_High (configure la polarité inactive à l'état haut)
 *
 * --> SPI_CPHA : IS_SPI_CPHA(CPHA)
 * avec CPHA = SPI_CPHA_1Edge (configure la capture sur le premier front)
 * 			 = SPI_CPHA_2Edge (configure la capture sur le deuxime front d'horloge)
 *
 * --> SPI_NSS : IS_SPI_NSS(NSS)
 * avec NSS = SPI_NSS_Soft (configure la selection de l'esclave par le sofware)
 * 			= SPI_NSS_Hard (configure la selection de l'esclave de facon materiel)
 *
 * --> SPI_BaudRatePrescaler : IS_SPI_BAUDRATE_PRESCALER(PRESCALER)
 * avec PRESCALER = SPI_BaudRatePrescaler_2 (division par 2 de fclock)
 * 				  = SPI_BaudRatePrescaler_4 (division par 4)
 * 				  = SPI_BaudRatePrescaler_8 (division par 8)
 * 				  = SPI_BaudRatePrescaler_16 (division par 16)
 * 				  = SPI_BaudRatePrescaler_32 (division par 32)
 * 				  = SPI_BaudRatePrescaler_64 (division par 64)
 * 				  = SPI_BaudRatePrescaler_128 (division par 128)
 * 				  = SPI_BaudRatePrescaler_256 (division par 256)
 *
 * --> SPI_FirstBit : IS_SPI_FIRST_BIT(BIT)
 * avec BIT = SPI_FisrtBit_MSB (configure la trame avec comme premier bit transmis le MSB)
 * 			= SPI_FirstBit_LSB (configure le premier comme étant le LSB)
 *
 * --> SPI_CRCPolynomial : IS_SPI_CRC_POLYNOMIAL(POLYNOMIAL)
 * si POLYNOMIAL >= 1, utilise la CRC
 *
 *Configuration de la forme :
 *struct SPI_InitTypdeDef SPI_SENSOR = {SPI_Direction_2Lines_RxOnly, SPI_Mode_Master, SPI_Datasize_8b, SPI_CPOL_High, SPI_CPHA_2Edge, SPI_NSS_Hard, SPI_BaudRatePrescaler_2,SPI_FisrtBit_MSB};
 */

/*Pour un envoi de données, la fonction a utilisé esrt la suivante : */



/*SPIx peut valoir SPI1 pour le port un, SPI2 pour le port deux etc, il sert à sélectionner le port souhaité
 *
 * uint16_t data correspond à la valeur que l'on veut envoyé
 */

/*Pour une reception de données, on utilise la fonction suivante : */

uint16_t SPI_I2S_ReceiveData(SPI_TypeDef* SPIx);
/*SPIx peut valoir SPI1 pour le port un, SPI2 pour le port deux etc, il sert à sélectionner le port souhaité*/

FlagStatus SPI_I2S_GetFlagStatus(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
/*SPIx peut valoir SPI1 pour le port un, SPI2 pour le port deux etc, il sert à sélectionner le port souhaité
 *
 * SPI_I2S_FLAG
 */

void SPI_I2S_ClearFlag(SPI_TypeDef* SPIx, uint16_t SPI_I2S_FLAG);
/* fonction permettant de remettre à zero les flags,
 * le x de SPIx permet de selectionner le port spi souhaité
 *
 * SPI_I2S_FLAG = SPI_I2S_FLAG_BSY (flag qui indique que le port spi n'est pas libre)
 * 				   = SPI_I2S_FLAG_TXE (flag indiquant que la transmission n'est pas libre)
 * 				   = SPI_I2S_FLAG_RXNE (flag indiquant que la reception n'est pas libre)
 */

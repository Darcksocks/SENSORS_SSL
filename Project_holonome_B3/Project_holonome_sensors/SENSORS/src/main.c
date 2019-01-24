/**
 ******************************************************************************
 * @file    main.c
 * @author  Ac6
 * @version V1.0
 * @date    01-December-2013
 * @brief   Default main function.
 ******************************************************************************
 */

#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
#include "Optical_flow.h"
#include "serial.h"
#include "VAR_GLOBALE.h"

/*pensez a envoyer en premier les valeur dans les registres et se servir des ces valeurs pour savoir si la communication est bonne*/
int main(void)
{
	/*initialisation variables */
	uint8_t BUSY_OPTIC;
	int delay;
	uint16_t data_optical;
	uint8_t id;
	uint8_t boucle;

	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);

	/*Initialisation de la spi et des broches en sortie et mets le CS � 1*/
	init_clock_spi();
	init_spi_Optical();
	GPIO_SetBits(GPIOB, GPIO_Pin_1);

	/*initialisation liaison serie */
	serial_init(9600);
	for(delay=0;delay<100;delay++);
	serial_putchar("0x31");

	/*active la communication spi*/
	SPI_ENABLE_Optical();

	/*raz les flags de la spi*/
	SPI_CLEAR_BUSY();

	STM_EVAL_LEDOn(LED3);

	for(boucle=0;boucle<10;boucle++)
	{
		SPI_BUSY_Optical(BUSY_OPTIC);
		if(BUSY_OPTIC == 0)
		{
			STM_EVAL_LEDOn(LED4);
			STM_EVAL_LEDOn(LED5);
			GPIO_ResetBits(GPIOB, GPIO_Pin_1);
			for(delay=0 ; delay<10000; delay++);
			STM_EVAL_LEDOn(LED3);
			id = SPI_RECEIVEDATA_Optical(data_optical);
			serial_puts("test\r\n");
			/*if(id == 0x17)
			{
				STM_EVAL_LEDOn(LED3);
				serial_puts("found\r\n");
			}
			else
			{
				STM_EVAL_LEDOff(LED4);
				serial_puts(id);
				serial_puts("not found\r\n");
			}
			/*SPI_RECEIVEDATA_Optical(data_optical);
			serial_putchar(data_optical+10);
			SPI_CLEAR_BUSY_OPTIC();*/
			/*test si la liaison est bonne puis configure le CS � 0 pour
			 * selectionner l'esclave. realiser une attente pour etre sur que
			 * l'esclave est bien selectionn� puis lance la proc�dure de
			 * reception
			 * une fois fini, remet les flags � leur etat par d�faut (reset)
			 */
		}
		else
		{
			for(delay=0;delay<10000;delay++);
			/*si la liaion n'est pas prete, alors attend*/
		}
	}
}
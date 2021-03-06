#ifndef SERIAL_H_
#define SERIAL_H_

#include <stdint.h>

void serial_init(uint32_t baudrate);
void serial_putchar(volatile char c);
void serial_puts(volatile char *s);

/* for interruptions */
int32_t serial_input_not_empty(void);
char serial_input_character(void);
#define serial_it_handler USART2_IRQHandler
void serial_it_handler(void);

#endif /* SERIAL_H_ */

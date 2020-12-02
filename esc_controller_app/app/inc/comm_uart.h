/*
 * comm_uart.h
 *
 *  Created on: 17 aug 2015
 *      Author: benjamin
 */

#ifndef COMM_UART_H_
#define COMM_UART_H_

// Functions
void comm_uart_init(const char* szName, int baudrate);
void process_receiving(void);
void process_timing(void);

#endif /* COMM_UART_H_ */

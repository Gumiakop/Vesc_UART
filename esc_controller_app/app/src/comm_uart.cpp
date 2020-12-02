/*
	Copyright 2015 Benjamin Vedder	benjamin@vedder.se

	This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    */

/*
 * comm_uart.c
 *
 *  Created on: 17 aug 2015
 *      Author: benjamin
 */

#include "comm_uart.h"
#include "bldc_interface_uart.h"
#include "log.h"

#include <string.h>
#include <thread>

#include "serial/serial.h"

serial::Serial oSerial;

static uint8_t pRxBuffer[1024];
static uint16_t uwIdx = 0;
static void send_packet(unsigned char *data, unsigned int len) {
	printbuf((char*)"BUFFER:",data,len);
    oSerial.write(data, len);
}

void comm_uart_init(const char* szName, int baudrate) {

	bldc_interface_uart_init(send_packet);

    std::string cppszComPort(szName);
    oSerial.setBaudrate(baudrate);
    oSerial.setPort(cppszComPort);
    oSerial.open();

}

void process_receiving(void)
{
    uint8_t ubDummy=0;
    size_t receivedSize = oSerial.read(&ubDummy,1);
    if(receivedSize>0)
    {
        bldc_interface_uart_process_byte(ubDummy);
    }
}

void process_timing(void)
{
	bldc_interface_uart_run_timer();
	// std::this_thread::sleep_for(std::chrono::milliseconds(1));
}
#include "log.h"
#include <vector>
#include "serial/serial.h"
#include "comm_uart.h"
#include "datatypes.h"

#include "bldc_interface.h"

#include "argparse.h"

using namespace std;

void enumerate_ports()
{
	vector<serial::PortInfo> devices_found = serial::list_ports();

	vector<serial::PortInfo>::iterator iter = devices_found.begin();

	while( iter != devices_found.end() )
	{
		serial::PortInfo device = *iter++;

		printf( "(%s, %s, %s)\n", device.port.c_str(), device.description.c_str(),
     device.hardware_id.c_str() );
	}
}

void bldc_val_received(mc_values *val) {
	log_info("Input voltage: %.2f V\r\n", val->v_in);
	log_info("Current motor: %.2f A\r\n", val->current_motor);
	log_info("Current in:    %.2f A\r\n", val->current_in);
	log_info("RPM:           %.1f RPM\r\n", val->rpm);
	log_info("Duty cycle:    %.1f %%\r\n", val->duty_now * 100.0);
	log_info("Ah Drawn:      %.4f Ah\r\n", val->amp_hours);
	log_info("Ah Regen:      %.4f Ah\r\n", val->amp_hours_charged);
	log_info("Wh Drawn:      %.4f Wh\r\n", val->watt_hours);
	log_info("Wh Regen:      %.4f Wh\r\n", val->watt_hours_charged);
	log_info("Tacho:         %i counts\r\n", val->tachometer);
	log_info("Tacho ABS:     %i counts\r\n", val->tachometer_abs);
	log_info("Fault Code:    %s\r\n", bldc_interface_fault_to_string(val->fault_code));
}

static const char *const usage[] =
{
    "esc_controller_app [options] [[--] args]",
    "esc_controller_app [options]",
    NULL,
};

const char* szComPort = NULL;
int iGivenBaudrate = 0;

struct argparse_option options[] =
{
    OPT_STRING('c', "comport", &szComPort, "Given VESC serial port"),
    OPT_INTEGER('b', "baudrate", &iGivenBaudrate, "Selected baud for VESC communication"),
    OPT_END(),
};

struct argparse argparse;

void my_print(char* szStr)
{
    std::printf("%s\r\n", szStr);
}

void firmware_data(int maj, int min)
{
    std::printf("FW version : %d, %d\r\n",maj,min);
}

int main (int argc, char** argv)
{
    enumerate_ports();
    argparse_init(&argparse, options, usage, 0);
    argc = argparse_parse(&argparse, argc, argv);
    log_info("Given port COM: %s, at: %d",szComPort, iGivenBaudrate);

    comm_uart_init(szComPort,iGivenBaudrate);
    bldc_interface_set_rx_value_func(bldc_val_received);
    bldc_interface_set_rx_printf_func(my_print);

    bldc_interface_set_rx_fw_func(firmware_data);

    //bldc_interface_get_values();

    bldc_interface_terminal_cmd("help");


    while(true)
    {
        process_receiving();
        // process_timing();
    }

    return 0;
}
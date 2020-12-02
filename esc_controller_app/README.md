# VEST 4.12 Linux UART Communication

### This poject based on [Benjamin's robotics](http://vedder.se/2015/10/communicating-with-the-vesc-using-uart/) and https://github.com/vedderb/bldc_uart_comm_stm32f4_discovery
 [![LinkedIn][linkedin-shield]][linkedin-url]
## Setup
To run this project use cmake:

```
$ cd ../git clone
$ cd ../esc_controller_app/build
$ cmake
$ make
``` 
 ## To run script 
 ```
$ cd ../esc_controller_app/build
$ ./esc_controller_app -c /dev/ttyACM0 -b 115200
 
 ```

#include "include/mini_uart.h"

void main() {
	mini_uart_init();
	
	
	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}

#include "include/mini_uart.h"

void main() {
	mini_uart_init();
	
	mini_uart_send('h');
	mini_uart_send_string("ello world!\n");

	for(;;) {
		mini_uart_send(mini_uart_recv());
	}

	/*
	for(;;) {
		asm volatile("wfe");
	}
	*/
}

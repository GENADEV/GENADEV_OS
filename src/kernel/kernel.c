#include "hardware/uart/mini_uart.h"
#include "../lib/debug/debug.h"
#include "int/irq.h"


void main() {
	mini_uart_init();
	
	debug("Genadev OS\n");

	irq_init();

	debug("Kernel code end\n");

	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}

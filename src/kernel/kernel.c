#include "include/mini_uart.h"
#include "../lib/debug/debug.h"

void main() {
	mini_uart_init();
	
	debug("hello, world! %d\n", 1234);

	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}

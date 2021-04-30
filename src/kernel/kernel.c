#include "hardware/uart/mini_uart.h"
#include "../lib/debug/debug.h"
#include "int/irq.h"

extern void svc_test();
extern void switch_el();

void main() {
	mini_uart_init();
	
	debug("Genadev OS\n");
	
	/* Get Current Exception Level */
	int el = 0;
	asm volatile(
		"mrs %0, currentEL\n"
		"lsr %0, %0, 2\n"
		: "=r"(el)
	);
	debug("Current EL: %d\n", el);

	irq_init();
	
	svc_test();

	debug("Kernel code end\n");

	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}

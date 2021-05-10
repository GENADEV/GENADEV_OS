#include "hardware/uart/mini_uart.h"
#include "../lib/debug/debug.h"
#include "int/irq.h"
#include "arm-v-8/mb/mailbox.h"

extern void svc_test();

void main() {
	mini_uart_init();
	
	debug("GENADEV_OS\n");


	/* START OF TEST */
	debug("START OF - interrupts and service test\n");
	
	// get current exception level
	int el = 0;
	asm volatile(
		"mrs %0, currentEL\n"
		"lsr %0, %0, 2\n"
		: "=r"(el)
	);
	debug("Current EL: %d\n", el);

	irq_init();
	
	svc_test();

	debug("END OF - interrutps and service test\n");
	/* END OF TEST */


	/* START OF TEST */
	debug("START OF - Mailbox test start\n");

	volatile unsigned int  __attribute__((aligned(16))) mb_buffer[36];
	
	mb_buffer[0] = 8 * 4;					// total buffer size
	mb_buffer[1] = MB_REQUEST;				// buffer request
	mb_buffer[2] = MB_TAG_GET_BOARD_MODEL;	// tag identifier 
 	mb_buffer[3] = 4;						// value buffer size
	mb_buffer[4] = 0;						// value buffer request/response code 
	mb_buffer[5] = 0;						// value buffer 
	mb_buffer[6] = 0;						// end tag 
	mb_buffer[7] = 0;						// padding

	debug("BEFORE WRITE AND READ\n");
	for (int i = 0; i < 8; i++) {
		debug("mailbox[%x] = %x\n", i, mb_buffer[i]);
	}
	
	// write the mailbox buffer to channel 8 - property tags
	mailbox_write(8, (unsigned int*) mb_buffer);

	// now read from channel 8 - property tags
	mailbox_read(8);

	debug("AFTER WRITE AND READ\n");
	for (int i = 0; i < 8; i++) {
		debug("mailbox[%x] = %x\n", i, mb_buffer[i]);
	}

	// check if the the request was successful
	if(mb_buffer[1] != MB_SUCCESSFUL_RESPONSE)
		debug("request not successful (0x%x)\n", mb_buffer[1]);
		
	debug("END OF - mailbox test\n");	
	/* END OF TEST */


	// print everything we receive from the mini uart to the mini uart
	for(;;) {
		mini_uart_send(mini_uart_recv());
	}
}

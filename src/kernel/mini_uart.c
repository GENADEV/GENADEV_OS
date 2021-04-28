// mini uart is the same as uart1

#include "include/gpio.h"
#include "include/mini_uart.h"
#include "include/utils.h"

void mini_uart_init(void) {
	unsigned int selector;

	// ?
	selector = get32(GPFSEL1);
	// clean gpio14
	selector &= ~(7<<12);
	// set alt5 for gpio14
	selector |= 2<<12;
	// clean gpio15
	selector &= ~(7<<15);
	// set alt5 for gpio15
	selector |= 2<<15;
	// ?
	put32(GPFSEL1,selector);

	// ?
	put32(GPPUD,0);
	// delay execution
	delay(150);
	// ?
	put32(GPPUDCLK0,(1<<14)|(1<<15));
	// delay execution
	delay(150);
	// ?
	put32(GPPUDCLK0,0);

	// enable mini uart itself -> access to it's registers
	put32(AUX_ENABLES,1);
	// disable auto flow control and disable receiver and transmitter
	put32(AUX_MU_CNTL_REG,0);
	// diable receive and transmit interrupts
	put32(AUX_MU_IER_REG,0);
	// enable 8 bit mode
	put32(AUX_MU_LCR_REG,3);
	// set rts line to be always high
	put32(AUX_MU_MCR_REG,0);
	// set baud rate to 115200
	put32(AUX_MU_BAUD_REG,270);
	
	// enable transmitter and receiver
	put32(AUX_MU_CNTL_REG,3);
}

char mini_uart_recv(void) {
	while(!(get32(AUX_MU_LSR_REG)&0x01));
	
	return get32(AUX_MU_IO_REG)&0xFF;
}

void mini_uart_send(char c) {
	while(!(get32(AUX_MU_LSR_REG)&0x20));
	
	put32(AUX_MU_IO_REG, c);
}

void mini_uart_send_string(char* str) {
	for(int i = 0; str[i] != '\0'; i++) {
		mini_uart_send(str[i]);
	}
}

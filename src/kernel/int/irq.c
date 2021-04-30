#include "irq.h"
#include "../../lib/debug/debug.h"

void irq_unknown()
{
    int esr;
	int elr;
	asm volatile(
		"mrs %0, esr_el2\n"
		"mrs %1, elr_el2\n"
		: "=r"(esr), "=r"(elr)
	);
    
    debug(
        "************************************\n"
        "Unhandled IRQ:\n"
        "\tesr_el2: 0x%lx\n"
        "\telr_el2: 0x%lx\n"
        "************************************\n",
        esr, elr
    );
    
}
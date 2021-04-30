ENTRY(_start)

SECTIONS
{
	kernel_start = .;
	.text.boot	: { *(.text.boot) }
	.text.interrupts : { *(.text.interrupts) }
	.text		: { *(.text*) }
	.rodata		: { *(.rodata) }
	.data		: { *(.data) }
	.			= ALIGN(0x8);
	bss_begin	= .;
	.bss		: { *(.bss*) } 
	bss_end		= .;
	kernel_end	= .;
}

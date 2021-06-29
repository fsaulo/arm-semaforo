FLASH_INIT = 0x08000000;
FLASH_SIZE = 64K;
RAM_INIT   = 0x20000000;
RAM_SIZE   = 20K;

_estack	   = RAM_INIT + RAM_SIZE;

MEMORY {
	FLASH : ORIGIN = FLASH_INIT,  LENGTH = FLASH_SIZE
	RAM   : ORIGIN = RAM_INIT,    LENGTH = RAM_SIZE
}

SECTIONS {
	.text   : { *(.text.vector_table) *(.text.start) *(.text*) } > FLASH
	.rodata : { *(.rodata*)                                    } > FLASH
	.data   : { *(.data*)                                      } > RAM AT > FLASH
	.bss	: { *(.bss*)                                       } > RAM
}

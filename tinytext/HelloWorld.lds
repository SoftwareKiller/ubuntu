ENTRY(start)

SECTIONS
{
    . = 0x8048000 + SIZEOF_HEADERS;

    HelloWorld : { *(.text) *(.data) *(.rodata) }

    /DISCARD/  : { *(.comment) }
}

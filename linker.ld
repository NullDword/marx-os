ENTRY(kernel_start)

SECTIONS
{
  . = 0x10000;

  .text :
  {
    *(.text)
  }

  .rodata :
  {
    *(.rodata)
  }

  .data :
  {
    *(.data)
  }

  .bss :
  {
    *(.bss)
  }

  . = ALIGN(4096);
  _kernel_end = .;
}

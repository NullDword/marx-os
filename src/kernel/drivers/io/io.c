#include <drivers/io/io.h>

uint8 port_inb(uint16 Port)
{
  uint8 Value;

  __asm__ volatile("inb %1, %0" : "=a"(Value) : "Nd"(Port));

  return Value;
}

uint16 port_inw(uint16 Port)
{
  uint16 Value;

  __asm__ volatile("inw %1, %0" : "=a"(Value) : "Nd"(Port));

  return Value;
}

void port_outb(uint16 Port, uint8 Value)
{
}

void port_outw(uint16 Port, uint16 Value)
{
}

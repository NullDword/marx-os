#pragma once

#include <types.h>

uint8  port_inb(uint16 Port);
uint16 port_inw(uint16 Port);

void port_outb(uint16 Port, uint8 Value);
void port_outw(uint16 Port, uint16 Value);

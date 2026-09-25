#include <graphics/graphics.h>
#include <types.h>

int kmain(framebuffer Buffer)
{
  clear_screen(&Buffer, COLOR_BLACK);

  string String;

  String.Position = (uVector){ 10, 10 };
  String.String   = "char with 8bit on to overflow\nyour\tarray";

  String.Scale = 2.f;
  String.Color = COLOR_WHITE;

  draw_string(&Buffer, &String);

  for (;;)
    __asm__ volatile("hlt");
}

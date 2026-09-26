#include <drivers/io/io.h>
#include <drivers/keyboard/keyboard.h>
#include <graphics/graphics.h>
#include <types.h>

int int_to_string(int value, char *buffer, int size)
{
  unsigned int magnitude;
  int          digits = 1;
  int          required;
  int          i;
  int          left;
  int          right;
  char         temp;

  if (buffer == 0 || size <= 0)
    return 0;

  if (value < 0)
    magnitude = 0u - (unsigned int)value;
  else
    magnitude = (unsigned int)value;

  {
    unsigned int copy = magnitude;

    while (copy >= 10)
    {
      copy /= 10;
      digits++;
    }
  }

  required = digits + (value < 0 ? 1 : 0) + 1; /* sign + '\0' */

  if (size < required)
  {
    buffer[0] = '\0';
    return 0;
  }

  i = 0;

  if (value < 0)
    buffer[i++] = '-';

  left = i;

  do
  {
    buffer[i++] = (char)('0' + magnitude % 10);
    magnitude /= 10;
  } while (magnitude != 0);

  buffer[i] = '\0';

  right = i - 1;

  while (left < right)
  {
    temp          = buffer[left];
    buffer[left]  = buffer[right];
    buffer[right] = temp;

    left++;
    right--;
  }

  return 1;
}

int kmain(framebuffer Buffer)
{
  clear_screen(&Buffer, COLOR_BLACK);

  char Str[1024];
  size i = 0;

  kb_input Input;
  while (1)
  {
    keyboard_read(&Input);

    if (Input.State != KB_PRESS)
      continue;

    if (Input.Key == KEY_BACKSPACE)
    {
      if (i == 0)
        continue;

      Str[--i] = '\0';
    }
    else if (Input.Key == KEY_LEFT)
    {
      if (i == 0)
        continue;

      i--;
    }
    else if (Input.Ascii != '\0')
    {
      Str[i++] = Input.Ascii;
      Str[i]   = '\0';
    }

    clear_screen(&Buffer, COLOR_BLACK);

    string String;

    String.String   = Str;
    String.Position = (uVector){ 10, 10 };
    String.Color    = COLOR_LIGHT_GRAY;
    String.Scale    = 2.f;

    draw_string(&Buffer, &String);
  }
}

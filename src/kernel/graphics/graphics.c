#include <graphics/font.h>
#include <graphics/graphics.h>

uint32 color_to_pixel(color Color)
{
  return (uint32)(Color.r << 16 | Color.g << 8 | Color.b);
}

void put_pixel(framebuffer *Buffer, uVector Position, color Color)
{
  if (Position.x >= Buffer->Width || Position.y >= Buffer->Height)
    return;

  uint32 *Pixel =
      (uint32 *)(Buffer->Address + Position.y * Buffer->Pitch + Position.x * 4);
  *Pixel = color_to_pixel(Color);
}

void put_pixel_raw(framebuffer *Buffer, uint x, uint y, uint32 Color)
{
  if (x >= Buffer->Width || y >= Buffer->Height)
    return;

  uint32 *Pixel = (uint32 *)(Buffer->Address + y * Buffer->Pitch + x * 4);
  *Pixel        = Color;
}

void clear_screen(framebuffer *Buffer, color Color)
{
  uint32 Pixel = color_to_pixel(Color);

  for (uint y = 0; y < Buffer->Height; y++)
  {
    uint32 *Row = (uint32 *)(Buffer->Address + y * Buffer->Pitch);

    for (uint x = 0; x < Buffer->Width; x++)
      Row[x] = Pixel;
  }
}

void draw_rectangle(framebuffer *Buffer, rectangle *Rectangle)
{
  uVector Position = Rectangle->Position;
  uVector Size     = Rectangle->Size;
  uint32  Color    = color_to_pixel(Rectangle->Color);

  for (uint y = Position.y; y < Position.y + Size.y; y++)
  {
    uint32 *Row = (uint32 *)(Buffer->Address + y * Buffer->Pitch);

    for (uint x = Position.x; x < Position.x + Size.x; x++)
      Row[x] = Color;
  }
}

void draw_character(framebuffer *Buffer, character *Character)
{
  if (Character->Color.a == 0)
    return;

  char  Char  = Character->Character;
  float Scale = Character->Scale;

  if (Scale <= 0.0f)
    Scale = 1.0f;

  const uint8 *Glyph = Font[(unsigned char)Char];

  int PosX = Character->Position.x;
  int PosY = Character->Position.y;

  for (int y = 0; y < FONT_HEIGHT; y++)
  {
    uint8 Row = Glyph[y];

    for (int x = 0; x < FONT_WIDTH; x++)
    {
      if (!(Row & (1 << x)))
        continue;

      int StartX = (int)(x * Scale);
      int EndX   = (int)((x + 1) * Scale);

      int StartY = (int)(y * Scale);
      int EndY   = (int)((y + 1) * Scale);

      for (int py = StartY; py < EndY; py++)
      {
        int DstY = PosY + py;

        if (DstY < 0 || (unsigned int)DstY >= Buffer->Height)
          continue;

        for (int px = StartX; px < EndX; px++)
        {
          int DstX = PosX + px;

          if (DstX < 0 || (unsigned int)DstX >= Buffer->Width)
            continue;

          unsigned int *Dst = (unsigned int *)(Buffer->Address +
                                               DstY * Buffer->Pitch + DstX * 4);

          *Dst = color_to_pixel(Character->Color);
        }
      }
    }
  }
}

void draw_string(framebuffer *Buffer, string *String)
{
  uVector     Position = String->Position;
  const char *cString  = String->String;
  float       Scale    = String->Scale;
  color       Color    = String->Color;

  uint x = 0;
  uint y = 0;
  while (*cString != '\0')
  {
    character Character;

    Character.Position  = (uVector){ Position.x + x * FONT_WIDTH * Scale,
                                     Position.y + y * FONT_HEIGHT * Scale };
    Character.Character = *cString;
    Character.Scale     = Scale;
    Character.Color     = Color;

    draw_character(Buffer, &Character);

    if (*cString == '\n' || *cString == '\r')
    {
      x = 0;
      y++;
    }
    else if (*cString == '\t')
      x += 8;
    else
      x++;

    cString++;
  }
}

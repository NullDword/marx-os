#pragma once

#include <types.h>
#include <vector.h>

#define COLOR_GREEN (color){ 0, 255, 0, 255 }
#define COLOR_BLUE (color){ 0, 0, 255, 255 }
#define COLOR_BLACK (color){ 0, 0, 0, 255 }
#define COLOR_WHITE (color){ 255, 255, 255, 255 }

#define COLOR_RED (color){ 255, 0, 0, 255 }
#define COLOR_GREEN (color){ 0, 255, 0, 255 }
#define COLOR_BLUE (color){ 0, 0, 255, 255 }

#define COLOR_YELLOW (color){ 255, 255, 0, 255 }
#define COLOR_CYAN (color){ 0, 255, 255, 255 }
#define COLOR_MAGENTA (color){ 255, 0, 255, 255 }

#define COLOR_ORANGE (color){ 255, 165, 0, 255 }
#define COLOR_PURPLE (color){ 128, 0, 128, 255 }
#define COLOR_PINK (color){ 255, 192, 203, 255 }
#define COLOR_BROWN (color){ 165, 42, 42, 255 }

#define COLOR_GRAY (color){ 128, 128, 128, 255 }
#define COLOR_DARK_GRAY (color){ 64, 64, 64, 255 }
#define COLOR_LIGHT_GRAY (color){ 192, 192, 192, 255 }

#define COLOR_DARK_RED (color){ 128, 0, 0, 255 }
#define COLOR_DARK_GREEN (color){ 0, 128, 0, 255 }
#define COLOR_DARK_BLUE (color){ 0, 0, 128, 255 }

#define COLOR_LIGHT_RED (color){ 255, 128, 128, 255 }
#define COLOR_LIGHT_GREEN (color){ 128, 255, 128, 255 }
#define COLOR_LIGHT_BLUE (color){ 128, 128, 255, 255 }

typedef struct
{
  uint32 Address;
  uint32 Pitch;
  uint32 Width;
  uint32 Height;
} framebuffer;

typedef struct
{
  uint8 r, g, b, a;
} color;

typedef struct
{
  uVector Position, Size;
  color   Color;
} rectangle;

typedef struct
{
  uVector Position;
  char    Character;
  float   Scale;
  color   Color;
} character;

typedef struct
{
  uVector     Position;
  const char *String;
  float       Scale;
  color       Color;
} string;

uint32 color_to_pixel(color Color);

void put_pixel(framebuffer *Buffer, uVector Position, color Color);
void clear_screen(framebuffer *Buffer, color Color);
void draw_rectangle(framebuffer *Buffer, rectangle *Rectangle);
void draw_character(framebuffer *Buffer, character *Character);
void draw_string(framebuffer *Buffer, string *String);

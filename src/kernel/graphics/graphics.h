#pragma once

#include <types.h>
#include <vector.h>

#define COLOR_WHITE (color){ 255, 255, 255, 255 }
#define COLOR_BLACK (color){ 0, 0, 0, 255 }

#define COLOR_RED (color){ 255, 0, 0, 255 }
#define COLOR_GREEN (color){ 0, 255, 0, 255 }
#define COLOR_BLUE (color){ 0, 0, 255, 255 }

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

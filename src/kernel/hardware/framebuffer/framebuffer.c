/*
    This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
    Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
    Copyright (C) 2021  GENADEV_OS and it's affiliates
     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
     
    Author: Yves Vollmeier <https://github.com/Tix3Dev>
*/


/*
 	Short definition:

	"A framebuffer is simply an area of memory that contains a bitmap which drives a video display."


	Procedure to write to the framebuffer:

	1. Send all the frame buffer specification to property tags channel with a mailbox
	2. Read from the mailbox and see if the GPU modified the structure and wait if necessary
	3. Once we have the pointer to the framebuffer we can write to it (note that this is for 32 bit mode):
		3.1. The address or actually offset of a subpixel is defined as: y * pitch + x * bytes_per_pixel
		3.2. So now we can add this offset we got in 3.1. plus the framebuffer address
		3.3. We can now write a ARGB color to this memory address we got in 3.2.
*/

#include "../../arm-v-8/mb/mailbox.h"
#include "../../arm-v-8/genadev_os.h"
#include "framebuffer.h"
#include "font.h"
#include "font_properties.h"

struct GFX_Struct
{
	unsigned int width;
	unsigned int height;
	unsigned int pitch;
	unsigned int bytes_per_pixel;

	unsigned char *address;

	int cursor_x_pos;
	int cursor_y_pos;

	uint32_t global_background_color;
} framebuffer;

void framebuffer_init(void)
{
	framebuffer.cursor_x_pos = 0;
	framebuffer.cursor_y_pos = 0;
	framebuffer.global_background_color = 0x00FFFFFF;

	// save all of the needed buffer content which we will pass later into channel 8
	// specific for the following tags
	// SET PHYSICAL (DISPLAY) WIDTH/HEIGHT
	// SET VIRTUAL (BUFFER) WIDTH/HEIGHT
	// SET VIRTUAL OFFSET
	// SET DEPTH
	// SET PIXEL ORDER
	// ALLOCATE BUFFER
	// GET PITCH

	uint32_t __section_align *mb_buffer;

	mb_buffer[0] = 35 * 4;										// total buffer size
	mb_buffer[1] = MB_REQUEST;									// buffer request

	mb_buffer[2] = MB_TAG_SET_PHYSICAL_DISPLAY_WIDTH_HEIGHT;	// tag identifier
	mb_buffer[3] = 8;											// value buffer size
	mb_buffer[4] = 8;											// value buffer size
	mb_buffer[5] = 1920;										// value buffer | width in pixels
	mb_buffer[6] = 1080;										// value buffer | height in pixels

	mb_buffer[7] = MB_TAG_SET_VIRTUAL_BUFFER_WIDHT_HEIGHT;		// tag identifier
	mb_buffer[8] = 8;											// value buffer size
	mb_buffer[9] = 8;											// value buffer size
	mb_buffer[10] = 1920;										// value buffer | width in pixels
	mb_buffer[11] = 1080;										// value buffer | height in pixels

	mb_buffer[12] = MB_TAG_SET_VIRTUAL_OFFSET;					// tag identifier
	mb_buffer[13] = 8;											// value buffer size
	mb_buffer[14] = 8;											// value buffer size
	mb_buffer[15] = 0;											// value buffer | x-axis-offset
	mb_buffer[16] = 0;											// value buffer | y-axis-offset

	mb_buffer[17] = MB_TAG_SET_DEPTH;							// tag identifier
	mb_buffer[18] = 4;											// value buffer size
	mb_buffer[19] = 4;											// value buffer size
	mb_buffer[20] = 32;											// value buffer | 32 bits per pixel

	mb_buffer[21] = MB_TAG_SET_PIXEL_ORDER;						// tag identifier
	mb_buffer[22] = 4;											// value buffer size
	mb_buffer[23] = 4;											// value buffer size
	mb_buffer[24] = 1;											// value buffer | state which can be either 0x0 (BGR) or 0x1 (RGB)

	mb_buffer[25] = MB_TAG_ALLOCATE_BUFFER;						// tag identifier
	mb_buffer[26] = 8;											// value buffer size
	mb_buffer[27] = 8;											// value buffer size
	mb_buffer[28] = 4096;										// value buffer | framebuffer base address in bytes - pointer
	mb_buffer[29] = 0;											// value buffer | framebuffer size in bytes

	mb_buffer[30] = MB_TAG_GET_PITCH;							// tag identifier
	mb_buffer[31] = 4;											// value buffer size
	mb_buffer[32] = 4;											// value buffer size
	mb_buffer[33] = 0;											// value buffer | bytes per line

	mb_buffer[34] = 0;											// end tag

	// write the mailbox buffer to channel 8 - property tags
	mailbox_write(MB_CHANNEL_PROP, mb_buffer);

	// check the number of bytes per line or pitch and pointer to the framebuffer
	mailbox_read(MB_CHANNEL_PROP);

	if (mb_buffer[20] == 32	&& mb_buffer[28] != 0)
	{
		framebuffer.width = mb_buffer[10];									// get actual physical width
		framebuffer.height = mb_buffer[11];									// get actual physical height
		framebuffer.pitch = mb_buffer[33];									// get number of bytes per line or pitch
		framebuffer.bytes_per_pixel = mb_buffer[20] >> 3;					// get bytes per pixel by converting bits per pixel

		mb_buffer[28] &= 0x3FFFFFFF;							// convert GPU address to ARM address
		framebuffer.address = (unsigned char *)((long)mb_buffer[28]);	// get framebuffer address
	}
}

// color must be in hexadecimal with 8 digits (4 binary bits = 1 hexadecimal digit -> ARGB (32 bits) = 8 hexadecimal degits)
void framebuffer_draw_pixel(int x, int y, uint32_t color)
{
	int offset = (y * framebuffer.pitch) + (x * framebuffer.bytes_per_pixel);
	*((uint32_t*)(framebuffer.address + offset)) = color;
}

// set a global background color + apply it
void framebuffer_set_background_color(uint32_t background_color)
{
	framebuffer.global_background_color = background_color;

	for (int y = 0; y < framebuffer.height; y++)
	{
		for (int x = 0; x < framebuffer.width; x++)
			framebuffer_draw_pixel(x, y, framebuffer.global_background_color);
	}
}

// set cursor position to standard and also background color to standard
void framebuffer_reset_screen(void)
{
	framebuffer.cursor_x_pos = 0;
	framebuffer.cursor_y_pos = 0;

	framebuffer_set_background_color(framebuffer.global_background_color);
}


// draw a line to the framebuffer with start coordinates and end coordinates
void framebuffer_draw_line(int x_start_pos, int y_start_pos, int x_end_pos, int y_end_pos, uint32_t color)
{
	int dx = x_end_pos - x_start_pos;
	int dy = y_end_pos - y_start_pos;

	int x = x_start_pos;
	int y = y_start_pos;

	int p = 2 * dy - dx;

	while (x < x_end_pos)
	{
		if (p >= 0)
		{
			framebuffer_draw_pixel(x, y, color);
			y += 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			framebuffer_draw_pixel(x, y, color);
			p = p + 2 * dy;
		}

		x += 1;
	}
}

// we divide the circle in 8 parts
void draw_circle_helper(int xc, int yc, int x, int y, uint32_t color)
{
	framebuffer_draw_pixel(xc + x, yc + y, color);
	framebuffer_draw_pixel(xc - x, yc + y, color);
	framebuffer_draw_pixel(xc + x, yc - y, color);
	framebuffer_draw_pixel(xc - x, yc - y, color);
	framebuffer_draw_pixel(xc + y, yc + x, color);
	framebuffer_draw_pixel(xc - y, yc + x, color);
	framebuffer_draw_pixel(xc + y, yc - x, color);
	framebuffer_draw_pixel(xc - y, yc - x, color);
}

// draw a circle to the framebuffer with the center of the circle and the radius
void framebuffer_draw_circle(int x_center, int y_center, int radius, uint32_t color)
{
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;

	draw_circle_helper(x_center, y_center, x, y, color);

	while (y >= x)
	{
		x += 1;

		if (d > 0)
		{
			y -= 1;
			d = d + 4 * (x - y) + 10;
		}
		else
			d = d + 4 * x + 6;

		draw_circle_helper(x_center, y_center, x, y, color);
	}
}

// memmove the screen one row up
void framebuffer_move_one_row_up(void)
{
	for (int column = FONT_HEIGHT; column < framebuffer.height; column++)
	{
		for (int row = 0; row < framebuffer.width; row++)
		{
			int offset = (column * framebuffer.pitch) + (row * framebuffer.bytes_per_pixel);
			uint32_t current_color = *((uint32_t*)(framebuffer.address + offset));
			*((uint32_t*)(framebuffer.address + offset)) = framebuffer.global_background_color;

			int new_offset = ((column - FONT_HEIGHT) * framebuffer.pitch) + (row * framebuffer.bytes_per_pixel);
			*((uint32_t*)(framebuffer.address + new_offset)) = current_color;
		}
	}
}

// print one character/glyph to the screen where x/y are the top left corner of the character
void framebuffer_print_char(char character, int x, int y, uint32_t foreground_color, uint32_t background_color)
{
	if (x + FONT_WIDTH >= framebuffer.width || framebuffer.cursor_x_pos + FONT_WIDTH >= framebuffer.width)
	{
		x = 0;
		y += FONT_HEIGHT;
		framebuffer.cursor_x_pos = x;
		framebuffer.cursor_y_pos = y;
	}

	if (y >= framebuffer.height || framebuffer.cursor_y_pos >= framebuffer.height)
	{
		x = 0;
		y = framebuffer.height - FONT_HEIGHT;
		framebuffer.cursor_x_pos = x;
		framebuffer.cursor_y_pos = y;
		framebuffer_move_one_row_up();
	}

	switch (character)
	{
		case '\n':
		{
			framebuffer.cursor_x_pos = 0;
			framebuffer.cursor_y_pos = y + FONT_HEIGHT;
			return;
		}

		case '\t':
		{
			framebuffer.cursor_x_pos += 4;
			return;
		}
	}

	int offset = character * FONT_HEIGHT;
	int line_data;
	int x_pos;
	int y_pos;
	int pixel_color;

	for (int column = 0; column < FONT_HEIGHT; column++)
	{
		line_data = font[offset + column];

		for (int row = 0; row < FONT_WIDTH; row++)
		{
			x_pos = x + FONT_WIDTH - row;
			y_pos = y + column;

			pixel_color = ((line_data >> row) & 0x01) ? foreground_color : background_color;

			framebuffer_draw_pixel(x_pos, y_pos, pixel_color);
		}
	}

	framebuffer.cursor_x_pos += FONT_WIDTH;
}

void framebuffer_print_string(char *string, uint32_t foreground_color, uint32_t background_color)
{
	while (*string)
		framebuffer_print_char(*string++, framebuffer.cursor_x_pos, framebuffer.cursor_y_pos, foreground_color, background_color);
}

// test - change the color of all pixels on the screen to 0xFF00FF00
void framebuffer_test(void)
{
	framebuffer_set_background_color(0xFF27DFF8);

	framebuffer_draw_line(0, 540, 1919, 540, 0xFFF9AC37);
	framebuffer_draw_circle(960, 540, 250, 0xFFF9AC37);
	framebuffer_draw_circle(960, 540, 50, 0xFFF9AC37);

	framebuffer_print_char('!', 0, 0, 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("Hello World!\nGENADEV_OS is the coolest OS out there!\n", 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("1\n", 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("2\n", 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("3\n", 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("4\n", 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("5\n", 0xFF27DFF8, 0xFFF9AC37);
	framebuffer_print_string("6\n", 0xFF27DFF8, 0xFFF9AC37);

	framebuffer_print_string("123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890", 0xFF27DFF8, 0xFFF9AC37);

	framebuffer.cursor_x_pos = 0;
	framebuffer.cursor_y_pos = 1073;

	while (1 == 1)
	{
		framebuffer_print_string("!", 0xFF27DFF8, 0xFFF9AC37);

		for (int i = 0; i <= 5000000; i++) {}
	}

	// framebuffer_reset_screen();
}

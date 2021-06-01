/*
     This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS
     Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
     Copyright (C) 2021  Yves Vollmeier and Tim Thompson

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
#include "../../../lib/debug/debug.h"

unsigned int width, height, pitch, bytes_per_pixel;
unsigned char *framebuffer;

void framebuffer_init(void)
{
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
		mb_buffer[28] &= 0x3FFFFFFF;							// convert GPU address to ARM address
		width = mb_buffer[10];									// get actual physical width
		height = mb_buffer[11];									// get actual physical height
		pitch = mb_buffer[33];									// get number of bytes per line or pitch
		bytes_per_pixel = mb_buffer[20] >> 3;					// get bytes per pixel by converting bits per pixel


		debug(DBG_BOTH, "width: '%x'\n", width);
		debug(DBG_BOTH, "height: '%x'\n", height);
		debug(DBG_BOTH, "pitch: '%x'\n", pitch);
		debug(DBG_BOTH, "bytes_per_pixel: '%x'\n", bytes_per_pixel);

		framebuffer = (unsigned char *)((long)mb_buffer[28]);	// get framebuffer address
	}
}

// color must be in hexadecimal with 8 digits (4 binary bits = 1 hexadecimal digit -> ARGB (32 bits) = 8 hexadecimal degits)
void framebuffer_draw_pixel(int x, int y, uint32_t color)
{
	int offset = (y * pitch) + (x * bytes_per_pixel);
	*((uint32_t*)(framebuffer + offset)) = color;
}

// test - change the color of all pixels on the screen to 0xFF00FF00
void framebuffer_test(void)
{
	for (int y = 0; y <= height; y++)
	{
		for (int x = 0; x <= width; x++)
			framebuffer_draw_pixel(x, y, 0xFF11AA11);
	}
}

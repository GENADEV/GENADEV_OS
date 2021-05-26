/*
 *   This file is part of an AArch64 hobbyist OS for the Raspberry Pi 3 B+ called GENADEV_OS 
 *   Everything is openly developed on github: https://github.com/GENADEV/GENADEV_OS
 *   Copyright (C) 2021  Yves Vollmeier and Tim Thompson
 *
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#ifndef MAILBOX_H
#define MAILBOX_H

#include "../../hardware/gpio/mmio_base.h"

/* buffer contents:
u32: buffer size in bytes (including the header values, the end tag and padding)
u32: buffer request/response code
	Request codes:
		0x00000000: process request
		All other values reserved
	Response codes:
		0x80000000: request successful
		0x80000001: error parsing request buffer (partial response)
		All other values reserved
u8...: sequence of concatenated tags
u32: 0x0 (end tag)
u8...: padding
*/

/* tag format ("sequence of concatenated tags")
u32: tag identifier
u32: value buffer size in bytes
u32:
	Request codes:
		b31 clear: request
		b30-b0: reserved
	Response codes:
		b31 set: response
		b30-b0: value length in bytes
u8...: value buffer
u8...: padding to align the tag to 32 bits.
*/

#define MB_BASE	MMIO_BASE + 0x0000B880

// codes
#define MB_REQUEST				0x00000000
#define MB_SUCCESSFUL_RESPONSE	0x80000000
#define MB_FULL					0x80000000
#define MB_EMPTY				0x40000000

// channels
#define MB_CHANNEL_POWER   0
#define MB_CHANNEL_FB      1
#define MB_CHANNEL_VUART   2
#define MB_CHANNEL_VCHIQ   3
#define MB_CHANNEL_LEDS    4
#define MB_CHANNEL_BTNS    5
#define MB_CHANNEL_TOUCH   6
#define MB_CHANNEL_COUNT   7
#define MB_CHANNEL_PROP    8

// tags
#define MB_TAG_SET_CLOCK_RATE	0x38002
#define MB_TAG_SET_PHYSICAL_DISPLAY_WIDTH_HEIGHT	0x40003
#define MB_TAG_SET_VIRTUAL_BUFFER_WIDHT_HEIGHT		0x48004
#define MB_TAG_SET_VIRTUAL_OFFSET					0x40009
#define MB_TAG_SET_DEPTH							0x48009
#define MB_TAG_SET_PIXEL_ORDER						0x48005
#define MB_TAG_ALLOCATE_BUFFER						0x40001
#define MB_TAG_GET_PITCH							0x40008

typedef struct {
	int status_code;
}mb_status_t;

unsigned int mailbox_read(unsigned int channel);
void mailbox_write(unsigned int channel, unsigned int *data);

#endif

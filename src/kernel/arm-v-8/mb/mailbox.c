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

#include "mailbox.h"
#include "../../../lib/debug/debug.h"

unsigned int *MB_READ	= (unsigned int *)(MB_BASE + 0x0);
unsigned int *MB_STATUS	= (unsigned int *)(MB_BASE + 0x18);
unsigned int *MB_WRITE	= (unsigned int *)(MB_BASE + 0x20);

unsigned int mailbox_read(unsigned int channel) {
	unsigned int *read_data;
	unsigned int read_channel;
	unsigned int clean_data;

	for(;;) {
		// wait until that there is something written in a mailbox 
		while(*MB_STATUS & MB_EMPTY);

		// assign read content to read_data
		read_data = &MB_READ;
		// get the lower 4 bits that contain the channel
		read_channel = *read_data & 0b1111;
		// shift bits to the right to get the upper 28 bits of the returned data
		clean_data = *read_data >>= 4;

		debug("mb: MB_READ = 0x%x\n", MB_READ);
		debug("mb: read_data = 0x%x\n", read_data);
		debug("mb: read_channel = 0x%x\n", read_channel);
		debug("mb: clean_data = 0x%x\n", clean_data);

		// check if the read channel equals the desired channel
		if(read_channel == channel) {
			return clean_data;
		}
	}
}

void mailbox_write(unsigned int channel, unsigned int data) {
	// wait until that there is enough space in the mailbox 
	while(*MB_STATUS & MB_FULL);

	// combine data (28 bits) and channel (4 bits)
	*MB_WRITE = (data | channel);
}

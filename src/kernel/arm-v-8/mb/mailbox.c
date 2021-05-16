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
#include <stdint.h>
#include "../genadev_os.h"

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
		read_data = (unsigned int*)&MB_READ;
		// get the lower 4 bits that contain the channel
		read_channel = *read_data & 0b1111;
		// shift bits to the right to get the upper 28 bits of the returned data
		clean_data = *read_data >>= 4;

		// check if the read channel equals the desired channel
		if(read_channel == channel) {
			return clean_data;
		}
	}
}

void mailbox_write(unsigned int channel, unsigned int *data) {
	// wait until that there is enough space in the mailbox 
	while(*MB_STATUS & MB_FULL);

	// combine data (28 bits) and channel (4 bits)
	*MB_WRITE = (data[4] | channel); //NOTE: This method of writing to the mailbox aims to satifsy compiler warnings, though it is untested and may cause UB. If "data[4]" causes any issues, try higher indexes or revert it back to "(unsigned int)data" which is guaranteed to work
}

mb_status_t mailbox_send(int channel, int buffer_size, int buffer_request, int tag_id, int value_buff_size, int value_buff_response, int value_buff, int end_tag, int padding)
{
	mb_status_t local_mb_status;

	//Setup mailbox buffer
	uint32_t __section_align *mb_buffer;
	
	mb_buffer[0] = buffer_size;				// total buffer size
	mb_buffer[1] = buffer_request;			// buffer request
	mb_buffer[2] = tag_id;					// tag identifier 
 	mb_buffer[3] = value_buff_size;			// value buffer size
	mb_buffer[4] = value_buff_response;		// value buffer request/response code 
	mb_buffer[5] = value_buff;				// value buffer 
	mb_buffer[6] = end_tag;					// end tag 
	mb_buffer[7] = padding;					// padding

	// Initiate a write request to the target mailbox and parse it's response
	mailbox_write(8, mb_buffer);
	mailbox_read(8);

	local_mb_status.status_code = mb_buffer[1];
	return local_mb_status;
}
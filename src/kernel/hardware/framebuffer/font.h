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
     
    Author: Yves Vollmeier <https://github.com/Tix3Dev> (see original source: https://github.com/spacerace/romfont/blob/master/font-headers/wang_3050_BIOS_ROM__8x14.h)
*/


#ifndef FONT_H 
#define FONT_H

#include "font_properties.h"

uint8_t font[3584] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7e, 0x81, 0xa5, 0x81, 0x81, 0xbd, 0x99, 0x81, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7e, 0xff, 0xdb, 0xff, 0xff, 0xc3, 0xe7, 0xff, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x36, 0x7f, 0x7f, 0x7f, 0x3e, 0x1c, 0x08, 0x08, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x08, 0x1c, 0x3e, 0x7f, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x3c, 0x18, 0x66, 0xff, 0x66, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x18, 0x18, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x3e, 0x3e, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe3, 0xc1, 0xc1, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x3c, 0x76, 0x62, 0x62, 0x76, 0x3c, 0x00, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xff, 0xc3, 0x89, 0x9d, 0x9d, 0x89, 0xc3, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x3f, 0x0f, 0x1d, 0x38, 0x7e, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x3e, 0x1c, 0x7f, 0x1c, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x0e, 0x0d, 0x0d, 0x0e, 0x0d, 0x0d, 0x1c, 0x7f, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x07, 0x1f, 0x3b, 0x33, 0x37, 0x3b, 0x33, 0x37, 0x75, 0x57, 0x70, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0xdb, 0x3c, 0xe7, 0x3c, 0xdb, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x60, 0x70, 0x78, 0x7c, 0x7e, 0x7e, 0x7c, 0x78, 0x70, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x3e, 0x7f, 0x1c, 0x1c, 0x1c, 0x7f, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3f, 0x6d, 0x6d, 0x6d, 0x3d, 0x0d, 0x0d, 0x0d, 0x0d, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x60, 0x3e, 0x63, 0x3e, 0x03, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x3e, 0x7f, 0x1c, 0x1c, 0x7f, 0x3e, 0x1c, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x3e, 0x7f, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x7f, 0x3e, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x38, 0x1c, 0x0e, 0x7f, 0x7f, 0x0e, 0x1c, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x0e, 0x1c, 0x38, 0x7f, 0x7f, 0x38, 0x1c, 0x0e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x60, 0x7f, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x36, 0x7f, 0x36, 0x14, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x1c, 0x3e, 0x3e, 0x7f, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x3e, 0x3e, 0x1c, 0x1c, 0x08, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x33, 0x77, 0xee, 0xdc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x66, 0x66, 0xff, 0x66, 0x66, 0x66, 0xff, 0x66, 0x66, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x18, 0x3c, 0x66, 0x30, 0x18, 0x0c, 0x66, 0x3c, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x70, 0x51, 0x73, 0x06, 0x0c, 0x18, 0x37, 0x65, 0x47, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3c, 0x66, 0x66, 0x3c, 0x38, 0x6f, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x0e, 0x1c, 0x38, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x30, 0x60, 0x60, 0x60, 0x60, 0x60, 0x30, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x38, 0x0c, 0x06, 0x06, 0x06, 0x06, 0x06, 0x0c, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x63, 0x36, 0x1c, 0x7f, 0x1c, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x18, 0x30, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x40, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x36, 0x63, 0x63, 0x6b, 0x63, 0x63, 0x36, 0x1c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0e, 0x1e, 0x36, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7e, 0x03, 0x03, 0x03, 0x3e, 0x03, 0x03, 0x03, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x07, 0x0f, 0x1b, 0x33, 0x63, 0x63, 0x7f, 0x03, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x60, 0x60, 0x60, 0x7e, 0x03, 0x03, 0x03, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0x30, 0x60, 0x60, 0x7e, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x63, 0x03, 0x06, 0x0c, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x36, 0x1c, 0x36, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x3f, 0x03, 0x03, 0x06, 0x7c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x0c, 0x0c, 0x18, 0x30, 0x00, 
	0x00, 0x00, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x06, 0x0c, 0x0c, 0x00, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x6f, 0x6b, 0x6b, 0x6f, 0x60, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1c, 0x36, 0x63, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7e, 0x63, 0x63, 0x63, 0x7e, 0x63, 0x63, 0x63, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1e, 0x33, 0x61, 0x60, 0x60, 0x60, 0x61, 0x33, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7c, 0x66, 0x63, 0x63, 0x63, 0x63, 0x63, 0x66, 0x7c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x60, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x60, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1e, 0x33, 0x63, 0x60, 0x60, 0x67, 0x63, 0x33, 0x1e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x66, 0x66, 0x6c, 0x78, 0x70, 0x78, 0x6c, 0x66, 0x66, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x77, 0x7f, 0x6b, 0x6b, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x73, 0x6b, 0x67, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7e, 0x63, 0x63, 0x63, 0x63, 0x7e, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x7b, 0x6f, 0x3e, 0x06, 0x03, 0x00, 
	0x00, 0x00, 0x7e, 0x63, 0x63, 0x63, 0x7e, 0x78, 0x6c, 0x66, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x60, 0x30, 0x1c, 0x06, 0x03, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x36, 0x1c, 0x08, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x6b, 0x6b, 0x7f, 0x77, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x36, 0x3e, 0x1c, 0x3e, 0x36, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x03, 0x06, 0x0c, 0x18, 0x30, 0x60, 0x60, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x40, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x03, 0x01, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x08, 0x1c, 0x36, 0x63, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 
	0x00, 0x70, 0x38, 0x1c, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x60, 0x60, 0x60, 0x6e, 0x73, 0x63, 0x63, 0x73, 0x6e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x60, 0x60, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x03, 0x03, 0x03, 0x3b, 0x67, 0x63, 0x63, 0x67, 0x3b, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x7e, 0x60, 0x60, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1e, 0x33, 0x30, 0x7c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x67, 0x63, 0x63, 0x67, 0x3b, 0x03, 0x7e, 0x00, 
	0x00, 0x00, 0x60, 0x60, 0x60, 0x6e, 0x73, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x06, 0x06, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x66, 0x3c, 0x00, 
	0x00, 0x00, 0x60, 0x60, 0x60, 0x66, 0x7c, 0x70, 0x78, 0x6c, 0x66, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x7f, 0x6b, 0x6b, 0x6b, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x6c, 0x76, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x6e, 0x73, 0x63, 0x63, 0x73, 0x6e, 0x60, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3b, 0x67, 0x63, 0x63, 0x67, 0x3b, 0x03, 0x03, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x3b, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x38, 0x0e, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x6b, 0x6b, 0x7f, 0x36, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x36, 0x1c, 0x1c, 0x36, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x63, 0x63, 0x63, 0x63, 0x67, 0x3b, 0x03, 0x7e, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x06, 0x0c, 0x18, 0x30, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0e, 0x18, 0x18, 0x18, 0x70, 0x18, 0x18, 0x18, 0x0e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x70, 0x18, 0x18, 0x18, 0x0e, 0x18, 0x18, 0x18, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3b, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x08, 0x1c, 0x36, 0x63, 0x63, 0x63, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1e, 0x33, 0x61, 0x60, 0x60, 0x60, 0x61, 0x33, 0x1e, 0x06, 0x7c, 0x00, 
	0x00, 0x00, 0x66, 0x66, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x0c, 0x18, 0x00, 0x3e, 0x63, 0x7e, 0x60, 0x60, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x3c, 0x66, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x36, 0x36, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x0c, 0x06, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x1c, 0x36, 0x1c, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x63, 0x60, 0x60, 0x63, 0x3e, 0x06, 0x3c, 0x00, 
	0x00, 0x08, 0x1c, 0x36, 0x00, 0x3e, 0x63, 0x7e, 0x60, 0x60, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x36, 0x36, 0x00, 0x3e, 0x63, 0x7e, 0x60, 0x60, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x0c, 0x06, 0x00, 0x3e, 0x63, 0x7e, 0x60, 0x60, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x6c, 0x6c, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x3c, 0x66, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x0c, 0x06, 0x00, 0x1c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x63, 0x00, 0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x1c, 0x36, 0x1c, 0x36, 0x63, 0x63, 0x7f, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x0e, 0x18, 0x7f, 0x60, 0x60, 0x7e, 0x60, 0x60, 0x60, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x1b, 0x3f, 0x6c, 0x6c, 0x37, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1f, 0x3c, 0x6c, 0x6c, 0x7f, 0x6c, 0x6c, 0x6c, 0x6f, 0x00, 0x00, 0x00, 
	0x00, 0x08, 0x1c, 0x36, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x36, 0x36, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x0c, 0x06, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x3c, 0x66, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 
	0x00, 0x30, 0x18, 0x0c, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x36, 0x36, 0x00, 0x63, 0x63, 0x63, 0x63, 0x67, 0x3b, 0x03, 0x7e, 0x00, 
	0x00, 0x63, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x63, 0x00, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x18, 0x18, 0x3c, 0x66, 0x60, 0x60, 0x66, 0x3c, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x1e, 0x33, 0x30, 0x30, 0x7e, 0x30, 0x30, 0x33, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x6c, 0x76, 0x66, 0x66, 0x78, 0x64, 0x6e, 0x64, 0x64, 0x66, 0x00, 0x00, 0x00, 
	0x00, 0x0e, 0x19, 0x18, 0x18, 0x7f, 0x0c, 0x0c, 0x0c, 0x4c, 0x38, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x0c, 0x18, 0x00, 0x3c, 0x06, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x18, 0x30, 0x00, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x06, 0x0c, 0x18, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x0c, 0x18, 0x30, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3b, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3b, 0x6e, 0x00, 0x6c, 0x76, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 
	0x00, 0x73, 0x8c, 0x63, 0x63, 0x73, 0x6b, 0x67, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x3e, 0x66, 0x66, 0x3f, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3c, 0x66, 0x66, 0x3c, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x30, 0x73, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x70, 0x70, 0x70, 0x70, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x7f, 0x07, 0x07, 0x07, 0x07, 0x00, 0x00, 0x00, 
	0x00, 0x61, 0x63, 0x66, 0x6c, 0x18, 0x30, 0x6e, 0x43, 0x0e, 0x1f, 0x00, 0x00, 0x00, 
	0x00, 0x61, 0x63, 0x66, 0x6c, 0x18, 0x33, 0x67, 0x49, 0x1f, 0x03, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x33, 0x66, 0xcc, 0x66, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0xcc, 0x66, 0x33, 0x66, 0xcc, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 0x11, 0x44, 
	0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 
	0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x18, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x06, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x06, 0xf6, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0xf6, 0x06, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x30, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0xf7, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xf7, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x37, 0x30, 0x37, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0xf7, 0x00, 0xf7, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x3f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x1f, 0x18, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x18, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0xff, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0xff, 0x18, 0xff, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 0xf0, 
	0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7b, 0xce, 0xcc, 0xcc, 0xce, 0x7b, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x2c, 0x76, 0x66, 0x66, 0x6e, 0x63, 0x63, 0x63, 0x6e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x63, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xb6, 0x36, 0x36, 0x36, 0x36, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x63, 0x30, 0x18, 0x1c, 0x18, 0x30, 0x63, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7b, 0x60, 0x60, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0x4c, 0x0c, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x7e, 0xdb, 0xdb, 0xdb, 0x7e, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3c, 0x66, 0xc3, 0xc3, 0xbd, 0xc3, 0xc3, 0x66, 0x3c, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0x66, 0x66, 0xe7, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x30, 0x18, 0x3e, 0x63, 0x63, 0x63, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7e, 0xdb, 0xdb, 0x7e, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0xdb, 0xdb, 0x7e, 0x18, 0x18, 0x18, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x60, 0x3c, 0x60, 0x60, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x3e, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x18, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x18, 0x00, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x70, 0x38, 0x1c, 0x0e, 0x1c, 0x38, 0x70, 0x00, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0e, 0x1c, 0x38, 0x70, 0x38, 0x1c, 0x0e, 0x00, 0x7e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x0e, 0x1b, 0x1b, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0xd8, 0xd8, 0xd8, 0x70, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x7e, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3b, 0x6f, 0x00, 0x3b, 0x6e, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3c, 0x66, 0x66, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x0c, 0xcc, 0xcc, 0x6c, 0x6c, 0x3c, 0x1c, 0x00, 
	0x00, 0x6c, 0x76, 0x66, 0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x3c, 0x26, 0x0c, 0x18, 0x30, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

#endif

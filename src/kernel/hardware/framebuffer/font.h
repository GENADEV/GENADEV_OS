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

#ifndef FONT_H 
#define FONT_H

#include "font_properties.h"

// see original source: https://github.com/spacerace/romfont/blob/master/font-headers/VTech-LaserXT3-BIOS-V1__8x8.h

uint8_t font[1024] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x7e, 0x81, 0xa5, 0x81, 0xa5, 0x99, 0x42, 0x3c, 
	0x3c, 0x7e, 0xdb, 0xff, 0xdb, 0xc3, 0x66, 0x3c, 
	0x00, 0x6c, 0xfe, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 
	0x08, 0x1c, 0x3e, 0x7f, 0x3e, 0x1c, 0x08, 0x00, 
	0x38, 0x7c, 0x38, 0xee, 0xee, 0xee, 0x10, 0x38, 
	0x10, 0x38, 0x7c, 0xfe, 0xfe, 0x7c, 0x10, 0x38, 
	0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 
	0xff, 0xff, 0xff, 0xe7, 0xe7, 0xff, 0xff, 0xff, 
	0x00, 0x00, 0x18, 0x24, 0x24, 0x18, 0x00, 0x00, 
	0xff, 0xff, 0xc3, 0xdb, 0xdb, 0xc3, 0xff, 0xff, 
	0x00, 0x0e, 0x06, 0x3a, 0x48, 0x48, 0x48, 0x30, 
	0x38, 0x44, 0x44, 0x44, 0x38, 0x10, 0x7c, 0x10, 
	0x3e, 0x30, 0x3e, 0x30, 0x30, 0x70, 0xf0, 0x60, 
	0x7f, 0x63, 0x7f, 0x63, 0x67, 0x66, 0xe0, 0xc0, 
	0x18, 0x5a, 0x3c, 0xe7, 0x3c, 0x5a, 0x18, 0x00, 
	0xc0, 0xf0, 0xfc, 0xff, 0xfc, 0xf0, 0xc0, 0x00, 
	0x03, 0x0f, 0x3f, 0xff, 0x3f, 0x0f, 0x03, 0x00, 
	0x30, 0x78, 0xfc, 0x30, 0x30, 0xfc, 0x78, 0x30, 
	0x6c, 0x6c, 0x6c, 0x6c, 0x6c, 0x00, 0x6c, 0x00, 
	0x7e, 0x92, 0x92, 0x7e, 0x12, 0x12, 0x12, 0x00, 
	0x3e, 0x62, 0x38, 0x6c, 0x6c, 0x38, 0x8c, 0xf8, 
	0x00, 0x00, 0x00, 0x00, 0x7e, 0x7e, 0x7e, 0x7e, 
	0x18, 0x3c, 0x7e, 0x18, 0x7e, 0x3c, 0x18, 0x7e, 
	0x18, 0x3c, 0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x7e, 0x3c, 0x18, 
	0x00, 0x0c, 0x06, 0xff, 0x06, 0x0c, 0x00, 0x00, 
	0x00, 0x30, 0x60, 0xff, 0x60, 0x30, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xc0, 0xc0, 0xfe, 0x00, 0x00, 
	0x00, 0x00, 0x24, 0x66, 0xff, 0x66, 0x24, 0x00, 
	0x00, 0x00, 0x10, 0x38, 0x7c, 0xfe, 0xfe, 0x00, 
	0x00, 0x00, 0xfe, 0xfe, 0x7c, 0x38, 0x10, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x18, 0x18, 0x18, 0x18, 0x18, 0x00, 0x18, 0x00, 
	0x6c, 0x6c, 0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x28, 0x28, 0xfe, 0x28, 0xfe, 0x28, 0x28, 0x00, 
	0x18, 0x3e, 0x60, 0x3c, 0x06, 0x7c, 0x18, 0x00, 
	0x00, 0xc6, 0xec, 0x18, 0x30, 0x66, 0xc6, 0x00, 
	0x38, 0x6c, 0x38, 0x70, 0xd8, 0xcc, 0x76, 0x00, 
	0x18, 0x18, 0x30, 0x20, 0x00, 0x00, 0x00, 0x00, 
	0x0c, 0x18, 0x30, 0x30, 0x30, 0x18, 0x0c, 0x00, 
	0x30, 0x18, 0x0c, 0x0c, 0x0c, 0x18, 0x30, 0x00, 
	0x00, 0x24, 0x18, 0xff, 0x18, 0x24, 0x00, 0x00, 
	0x00, 0x18, 0x18, 0x7e, 0x18, 0x18, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x30, 
	0x00, 0x00, 0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 
	0x04, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0x80, 0x00, 
	0x78, 0x8c, 0x9c, 0xb4, 0xe4, 0xc4, 0x78, 0x00, 
	0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 
	0x78, 0x84, 0x04, 0x38, 0x40, 0x80, 0xfc, 0x00, 
	0xfc, 0x04, 0x08, 0x38, 0x04, 0x84, 0x78, 0x00, 
	0x18, 0x28, 0x48, 0x88, 0xf8, 0x08, 0x1c, 0x00, 
	0xfc, 0x80, 0xf8, 0x04, 0x04, 0x84, 0x78, 0x00, 
	0x38, 0x40, 0x80, 0xf8, 0x84, 0x84, 0x78, 0x00, 
	0xfc, 0x84, 0x04, 0x08, 0x10, 0x10, 0x10, 0x00, 
	0x3c, 0x42, 0x42, 0x3c, 0x42, 0x42, 0x3c, 0x00, 
	0x3c, 0x42, 0x42, 0x3e, 0x02, 0x04, 0x38, 0x00, 
	0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x00, 
	0x00, 0x18, 0x18, 0x00, 0x00, 0x18, 0x18, 0x30, 
	0x0c, 0x18, 0x30, 0x60, 0x30, 0x18, 0x0c, 0x00, 
	0x00, 0x00, 0x7e, 0x00, 0x00, 0x7e, 0x00, 0x00, 
	0x60, 0x30, 0x18, 0x0c, 0x18, 0x30, 0x60, 0x00, 
	0x3c, 0x46, 0x06, 0x0c, 0x18, 0x00, 0x18, 0x00, 
	0x7c, 0x82, 0xba, 0xaa, 0xbe, 0x80, 0x78, 0x00, 
	0x30, 0x48, 0x84, 0x84, 0xfc, 0x84, 0x84, 0x00, 
	0xf8, 0x44, 0x44, 0x78, 0x44, 0x44, 0xf8, 0x00, 
	0x38, 0x44, 0x80, 0x80, 0x80, 0x44, 0x38, 0x00, 
	0xf0, 0x48, 0x44, 0x44, 0x44, 0x48, 0xf0, 0x00, 
	0xfc, 0x44, 0x40, 0x70, 0x40, 0x44, 0xfc, 0x00, 
	0xfc, 0x44, 0x40, 0x70, 0x40, 0x40, 0xe0, 0x00, 
	0x78, 0x84, 0x80, 0x9c, 0x84, 0x84, 0x78, 0x00, 
	0x44, 0x44, 0x44, 0x7c, 0x44, 0x44, 0x44, 0x00, 
	0x38, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 
	0x1c, 0x08, 0x08, 0x08, 0x88, 0x88, 0x70, 0x00, 
	0xc4, 0x48, 0x50, 0x60, 0x50, 0x48, 0xc4, 0x00, 
	0xe0, 0x40, 0x40, 0x40, 0x40, 0x44, 0xfc, 0x00, 
	0x84, 0xcc, 0xb4, 0x84, 0x84, 0x84, 0x84, 0x00, 
	0x84, 0xc4, 0xa4, 0x94, 0x8c, 0x84, 0x84, 0x00, 
	0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, 
	0xf8, 0x44, 0x44, 0x78, 0x40, 0x40, 0xe0, 0x00, 
	0x78, 0x84, 0x84, 0x84, 0x94, 0x8c, 0x7c, 0x02, 
	0xf8, 0x44, 0x44, 0x78, 0x50, 0x48, 0xc4, 0x00, 
	0x70, 0x88, 0x40, 0x20, 0x10, 0x88, 0x70, 0x00, 
	0xf8, 0xa8, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 
	0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, 
	0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00, 
	0x84, 0x84, 0x84, 0x84, 0xb4, 0xcc, 0x84, 0x00, 
	0xc6, 0x28, 0x10, 0x10, 0x28, 0x44, 0x82, 0x00, 
	0x82, 0x82, 0x44, 0x28, 0x10, 0x10, 0x10, 0x00, 
	0xfe, 0x84, 0x08, 0x10, 0x20, 0x42, 0xfe, 0x00, 
	0x3c, 0x30, 0x30, 0x30, 0x30, 0x30, 0x3c, 0x00, 
	0x40, 0x60, 0x30, 0x18, 0x0c, 0x06, 0x02, 0x00, 
	0x3c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x3c, 0x00, 
	0x10, 0x38, 0x6c, 0xc6, 0x82, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 
	0x30, 0x30, 0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x78, 0x08, 0x78, 0x88, 0x74, 0x00, 
	0x40, 0x40, 0x40, 0x78, 0x44, 0x44, 0xf8, 0x00, 
	0x00, 0x00, 0x78, 0x80, 0x80, 0x80, 0x78, 0x00, 
	0x08, 0x08, 0x08, 0x78, 0x88, 0x88, 0x74, 0x00, 
	0x00, 0x00, 0x78, 0x84, 0xf8, 0x80, 0x78, 0x00, 
	0x70, 0x48, 0x40, 0xf0, 0x40, 0x40, 0x40, 0x00, 
	0x00, 0x00, 0x6c, 0x98, 0x88, 0x78, 0x08, 0xf8, 
	0x40, 0x40, 0x58, 0x64, 0x44, 0x44, 0xc4, 0x00, 
	0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 
	0x08, 0x00, 0x08, 0x08, 0x08, 0x88, 0x88, 0x70, 
	0xc0, 0x40, 0x48, 0x50, 0x60, 0x50, 0xc8, 0x00, 
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 
	0x00, 0x00, 0xac, 0xd2, 0x92, 0x92, 0x92, 0x00, 
	0x00, 0x00, 0xb8, 0xc4, 0x84, 0x84, 0x84, 0x00, 
	0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x78, 0x00, 
	0x00, 0x00, 0xb8, 0x44, 0x44, 0x78, 0x40, 0x40, 
	0x00, 0x00, 0x74, 0x88, 0x88, 0x78, 0x08, 0x0c, 
	0x00, 0x00, 0xb8, 0x44, 0x40, 0x40, 0xe0, 0x00, 
	0x00, 0x00, 0x78, 0x80, 0x70, 0x08, 0xf0, 0x00, 
	0x20, 0x20, 0xf8, 0x20, 0x20, 0x2c, 0x38, 0x00, 
	0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x6c, 0x00, 
	0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00, 
	0x00, 0x00, 0x84, 0x84, 0xb4, 0xcc, 0x84, 0x00, 
	0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 
	0x00, 0x00, 0x88, 0x88, 0x88, 0x78, 0x08, 0x70, 
	0x00, 0x00, 0xfc, 0x08, 0x30, 0x40, 0xfc, 0x00, 
	0x1c, 0x30, 0x30, 0x60, 0x30, 0x30, 0x1c, 0x00, 
	0x08, 0x08, 0x08, 0x00, 0x08, 0x08, 0x08, 0x00, 
	0x70, 0x18, 0x18, 0x0c, 0x18, 0x18, 0x70, 0x00, 
	0x00, 0x62, 0x92, 0x8c, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x10, 0x28, 0x44, 0x82, 0xfe, 0x00
};

#endif
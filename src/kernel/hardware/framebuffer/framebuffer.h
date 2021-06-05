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

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

void framebuffer_init(void);
void framebuffer_draw_pixel(int x, int y, uint32_t color);
void framebuffer_set_background_color(uint32_t background_color);
void reset_screen(void);
void framebuffer_draw_line(int x_start_pos, int y_start_pos, int x_end_pos, int y_end_pos, uint32_t color);
void framebuffer_draw_circle(int x_center, int y_center, int radius, uint32_t color);
void framebuffer_move_one_row_up(void);
void framebuffer_print_char(char character, int x, int y, uint32_t foreground_color, uint32_t background_color);
void framebuffer_print_string(char *string, uint32_t foreground_color, uint32_t background_color);
void framebuffer_test(void);
	
#endif

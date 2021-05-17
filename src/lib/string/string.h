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

#ifndef LIB_STRING_H
#define LIB_STRING_H

#include "../../kernel/arm-v-8/genadev_os.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

int strlen(const char *);
void *memset(void *src, uint32_t val, size_t n);
void *memcpy(void *src, void *dst, int n);
void *memzero(void *src, size_t n);

#endif // LIB_STRING_H

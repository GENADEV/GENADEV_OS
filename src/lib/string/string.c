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

    Author: Tim Thompson <https://github.com/V01D-NULL>
*/


#include "string.h"

int strlen(const char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return len;
}

/*
    Set n bytes in memory equal to val
*/
void *memset(void *src, uint32_t val, size_t n)
{
	uint8_t *src_ptr = (uint8_t*)src;

	do
	{
		*src_ptr++ = val;
		n--;
	}
	while (n != 0x0);

	return (void *)src;
}

/*
    Copy n bytes from src to dst
*/
void *memcpy(void *src, void *dst, int n)
{
	//Cast src and dst to uint8_t* to be able to perform arithemtic operations
	uint8_t *src_ptr = (uint8_t*)src;
	uint8_t *dst_ptr = (uint8_t*)dst;

	do
	{
		*dst_ptr++ = *src_ptr++;
		n--;
	}
	while (n != 0x0);

	return (void *)dst_ptr;
}

bool memcmp(void *src, int cmp, int n)
{

}

/*
    Zero out n bytes of memory
*/
void *memzero(void *src, size_t n)
{
	memset(src, 0x0, n);
}
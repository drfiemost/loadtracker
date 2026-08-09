/*
 * LoadTracker
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef SDL_IO_H
#define SDL_IO_H

bool io_openlinkeddatafile(unsigned char *ptr);
void io_closelinkeddatafile();
int io_open(const char *name);
void io_close(int handle);

int io_lseek(int handle, int bytes, int whence);
int io_read(int handle, void *buffer, int size);
unsigned io_read8(int handle);
unsigned io_readle16(int handle);
unsigned io_readle32(int handle);
unsigned io_readhe16(int handle);
unsigned io_readhe32(int handle);

#endif

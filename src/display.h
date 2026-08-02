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

#ifndef DISPLAY_H
#define DISPLAY_H

#include "file.h"
#include "table.h"

#ifndef DISPLAY_C
extern const char *programname;

extern char textbuffer[MAX_PATHNAME];
extern const char *notename[];

extern Tables tables;

extern bool menu;
extern int editmode;
extern bool recordmode;
extern bool followplay;
extern int hexnybble;
extern bool exitprogram;
extern int eacolumn;
extern EditHdr ehmode;
#endif

void printmainscreen();
void displayupdate();
void printstatus();
void settooltip(const char *msg);

#endif

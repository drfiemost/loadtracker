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

// =============================================================================
// instrument editor
// =============================================================================

#define INSTR_C

#include "instr.h"

#include "globals.h"
#include "console.h"
#include "display.h"
#include "pattern.h"
#include "play.h"
#include "settings.h"
#include "song.h"
#include "table.h"

#include "bme_main.h"

#include <cstring>

int einum;
int eipos;
int eirow;
int eicolumn;

void showinstrtable();

void clearinstr(int num)
{
  std::memset(&song.instr[num], 0, sizeof(Instr));
  if (num)
  {
    if (config.multiplier)
      song.instr[num].gatetimer = 2 * config.multiplier;
    else
      song.instr[num].gatetimer = 1;

    song.instr[num].firstwave = 0x9;
  }
}

void clearinstr()
{
    for (int c = 0; c < MAX_INSTR; c++)
      clearinstr(c);
    eipos = 0;
    eicolumn = 0;
    eirow = 1;
    einum = 1;
}

void gotoinstr(int i)
{
  if ((i < 0) || (i >= MAX_INSTR)) return;

  einum = i;
  showinstrtable();

  editmode = EDIT_INSTRUMENT;
}

void nextinstr(int n)
{
  einum+=n;
  if (einum >= MAX_INSTR) einum = MAX_INSTR - 1;
  while ((einum - eirow) >= 5) eirow++;
  showinstrtable();
}

void previnstr(int n)
{
  einum-=n;
  if (einum < 1) einum = 1;
  while ((einum - eirow) < 0) eirow--;
  showinstrtable();
}

void showinstrtable()
{
  if (!tables.islocked())
  {
    for (int c = MAX_TABLES-1; c >= 0; c--)
    {
      if (song.instr[einum].ptr[c])
        tables.settableviewfirst(c, song.instr[einum].ptr[c] - 1);
    }
  }
}

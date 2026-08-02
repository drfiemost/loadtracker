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
// table editor
// =============================================================================

#define TABLE_C

#include "console.h"
#include "display.h"
#include "instr.h"
#include "pattern.h"
#include "play.h"
#include "reloc.h"
#include "settings.h"
#include "song.h"
#include "table.h"

#include "bme_main.h"

#include <utility>

#include <cmath>
#include <cstring>

#ifdef OVERFLOW
// might be defined in math.h
#  undef OVERFLOW
#endif

Tables tables;

int makespeedtable(unsigned data, int mode, bool makenew)
{
  if (!data) return -1;

  unsigned char l = 0, r = 0;

  switch (mode)
  {
    case MST_NOFINEVIB:
    l = (data & 0xf0) >> 4;
    r = (data & 0x0f) << 4;
    break;

    case MST_FINEVIB:
    l = (data & 0x70) >> 4;
    r = ((data & 0x0f) << 4) | ((data & 0x80) >> 4);
    break;

    case MST_FUNKTEMPO:
    l = (data & 0xf0) >> 4;
    r = data & 0x0f;
    break;

    case MST_PORTAMENTO:
    l = (data << 2) >> 8;
    r = (data << 2) & 0xff;
    break;

    case MST_RAW:
    r = data & 0xff;
    l = data >> 8;
    break;
  }

  if (!makenew)
  {
    for (int c = 0; c < MAX_TABLELEN; c++)
    {
      if ((song.ltable[STBL][c] == l) && (song.rtable[STBL][c] == r))
        return c;
    }
  }

  for (int c = 0; c < MAX_TABLELEN; c++)
  {
    if ((!song.ltable[STBL][c]) && (!song.rtable[STBL][c]))
    {
      song.ltable[STBL][c] = l;
      song.rtable[STBL][c] = r;

      tables.settableview(STBL, c);
      return c;
    }
  }
  return -1;
}

void gototable(int num, int pos)
{
  editmode = EDIT_TABLES;
  tables.settableview(num, pos);
}

void Tables::settableview(int num, int pos)
{
  m_num = num;
  m_column = 0;
  m_pos = pos;

  validatetableview();
}

void Tables::settableviewfirst(int num, int pos)
{
  m_view[num] = pos;
  settableview(num, pos);
}

void Tables::validatetableview()
{
  if (m_pos - m_view[m_num] < 0)
    m_view[m_num] = m_pos;
  if (m_pos - m_view[m_num] >= VISIBLETABLEROWS)
    m_view[m_num] = m_pos - VISIBLETABLEROWS + 1;

  // Table view is locked?
  if (m_lock)
  {
    for (int c = 0; c < MAX_TABLES; c++) m_view[c] = m_view[m_num];
  }
}

void Tables::tableup(bool shiftpressed, int n)
{
  if (shiftpressed)
  {
    if ((m_mark.chn != m_num) || (m_pos != m_mark.end))
    {
      m_mark.chn = m_num;
      m_mark.start = m_pos;
      m_mark.end = m_pos;
    }
  }
  m_pos-=n;
  if (m_pos < 0) m_pos = 0;
  if (shiftpressed) m_mark.end = m_pos;

  validatetableview();
}

void Tables::tabledown(bool shiftpressed, int n)
{
  if (shiftpressed)
  {
    if ((m_mark.chn != m_num) || (m_pos != m_mark.end))
    {
      m_mark.chn = m_num;
      m_mark.start = m_pos;
      m_mark.end = m_pos;
    }
  }
  m_pos+=n;
  if (m_pos >= MAX_TABLELEN) m_pos = MAX_TABLELEN-1;
  if (shiftpressed) m_mark.end = m_pos;

  validatetableview();
}

void Tables::setrow(int num, int pos, int column)
{
    m_num = num;
    m_pos = pos;
    if (m_pos < 0) m_pos = 0;
    if (m_pos > MAX_TABLELEN-1) m_pos = MAX_TABLELEN-1;
    m_column = column;
    if (m_column >= 2) m_column--;

    validatetableview();
}

void Tables::resetmarknum()
{
    m_mark.chn = -1;
}

void Tables::setmarkstart(int num, int markstart)
{
    if ((m_mark.chn != m_num) || (markstart != m_mark.end))
    {
        m_mark.chn = num;
        m_mark.start = markstart;
        m_mark.end = markstart;
    }
}

void Tables::setmarkend(int markend)
{
    m_mark.end = markend;
}

void Tables::fliplock()
{
    m_lock = !m_lock;
}

void Tables::clear()
{
  m_mark.chn = -1;
}

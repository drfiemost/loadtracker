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

#include "table.h"

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

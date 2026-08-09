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

#include <cstdint>
#include <cstdio>

void fwrite8(FILE *file, unsigned data)
{
    uint8_t bytes[1];

    bytes[0] = data;
    std::fwrite(bytes, 1, 1, file);
}

void fwritele16(FILE *file, unsigned data)
{
    uint8_t bytes[2];

    bytes[0] = data;
    bytes[1] = data >> 8;
    std::fwrite(bytes, 2, 1, file);
}

void fwritele32(FILE *file, unsigned data)
{
    uint8_t bytes[4];

    bytes[0] = data;
    bytes[1] = data >> 8;
    bytes[2] = data >> 16;
    bytes[3] = data >> 24;
    std::fwrite(bytes, 4, 1, file);
}

unsigned fread8(FILE *file)
{
    uint8_t bytes[1];

    std::fread(bytes, 1, 1, file);
    return bytes[0];
}

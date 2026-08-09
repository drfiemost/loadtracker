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

#ifndef SDL_SOUND_H
#define SDL_SOUND_H

#include <SDL3/SDL.h>

using CustomMixer = void (*)(Sint32 *dest, unsigned samples);
using Player = void (*)();

bool snd_init(unsigned mixrate, unsigned numsids);
void snd_uninit();
void snd_setcustommixer(CustomMixer custommixer);
void snd_setplayer(Player player);
unsigned getmixrate();

extern int snd_bpmtempo;

#endif

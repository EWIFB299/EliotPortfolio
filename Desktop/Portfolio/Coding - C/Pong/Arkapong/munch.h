#ifndef __MUNCH_H__
#define __MUNCH_H__

#include "cab202_simple_sprite.h"

/*
 *	Basic h file template was adjusted from ZDK Library
  */
sprite_id munch_id;
timer_id munch_timer;

void create_munch();

void setup_munch();

void move_munch();

void reset_munch();

void change_sprite();

int m_cycle;

#endif

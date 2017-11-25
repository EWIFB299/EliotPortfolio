#ifndef __BALL_H__
#define __BALL_H__

#include "cab202_simple_sprite.h"

/*
 *	Basic h file template was adjusted from ZDK Library
  */
sprite_id ball_id;
timer_id ball_timer;

void create_ball();

void setup_ball();

void reset_ball();

bool update_ball();

int angle;
#endif

#ifndef __SPLIT_BALL_H__
#define __SPLIT_BALL_H__

#include "cab202_simple_sprite.h"

/*
 *	Basic h file template was adjusted from ZDK Library
  */
sprite_id split_ball_id[9];

void create_split_ball();

void setup_split_ball();

void reset_split_ball();

bool update_split_ball();

int s_angle;
#endif

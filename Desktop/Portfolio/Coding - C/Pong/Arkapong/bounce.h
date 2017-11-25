#ifndef __BOUNCE_H__
#define __BOUNCE_H__

#include "curses.h"

#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "cab202_simple_sprite.h"
#include "cab202_timer.h"
#include "cab202_screen.h"

// INSERT INCLUDES HERE

#define TURN_SCREEN_CHANGED 1
#define TURN_OK 0
#define TURN_GAME_OVER -1

sprite_id bumper_id[10];
sprite_id munch_id;
sprite_id plus_id;
sprite_id splitter_id;
sprite_id minus_id;
sprite_id wind_id;


void setup_options();

void reset_plus();
void move_plus();

void reset_minus();
void move_minus();

void reset_bounce();
void move_bounce();

void reset_splitter();
void move_splitter();

void reset_wind();
void move_wind();

void reset_size();
#endif

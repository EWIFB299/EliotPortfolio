#ifndef __STAGE_H__
#define __STAGE_H__

#include "curses.h"
#include "cab202_simple_sprite.h"


void setup_stage();

void reset_stage();

bool update_stage_paddle();
sprite_id stage_paddle_id;
sprite_id ai_paddle_id;

int ai_collumn;
int stage_collumn;

#endif

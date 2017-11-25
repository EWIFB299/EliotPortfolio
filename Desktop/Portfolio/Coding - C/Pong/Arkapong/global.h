#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include "curses.h"
#include "cab202_simple_sprite.h"
#include "ball.h"

void setup_global();
void score_increase();
void lives_decrease();
void lives_depleted();
void end_game();


int score;
int lives;
int split_number;

#endif

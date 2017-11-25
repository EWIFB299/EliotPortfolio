#ifndef __TOGGLE_H__
#define __TOGGLE_H__

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

/* 
 *	setup_game:
 *
 *	Initialises the game environment. 
 */

void setup_toggle();
void move_paddle();

/* 
 *	reset_game:
 *
 *	restores the game to its initial appearance and behaviour, as if starting over. 
 */
 
int wind_count;

bool update_toggle(int key_code);
bool active_1;
bool active_2;
bool active_3;
bool active_4;
bool active_5;
bool active_6;
bool active_7;
bool active_8;
#endif

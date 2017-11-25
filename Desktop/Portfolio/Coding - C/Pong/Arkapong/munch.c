#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "munch.h"
#include "split.h"
#include "toggle.h"
#include "global.h"
#include "bounce.h"
#include "right_paddle.h"
#include "stage.h"
#include "cab202_simple_sprite.h"
#include "cab202_timer.h"
#include "cab202_screen.h"


#define munch_UPDATE_TIME (10)
/*
 *	Use of timers was adjusted from the ZDK library
 */

sprite_id munch_id;
timer_id munch_timer;

char munch_char[]= 
	
	"[||]"	
	"|()|"
	"[||]"
	;
	
char munch_char_1[]= 
	
	"[||]"	
	"(||)"
	"[||]"
	;

void create_munch() {
srand (time(NULL));
	
	munch_id = create_big_sprite(-10,-10,4,3, munch_char);
	set_sprite_angle( munch_id, 0);
	set_sprite_timer( munch_id, munch_timer );
	show_sprite( munch_id );
}

void setup_munch() {
	create_munch();
	munch_timer = create_timer(munch_UPDATE_TIME );
}
void reset_munch() {
	set_sprite_angle( munch_id, 0);
	move_sprite_to( munch_id, -10, -10);
	show_sprite( munch_id );
	
}

void move_munch() {
	m_cycle= 110;
	set_sprite_angle( munch_id, 0);
	move_sprite_to( munch_id, 10, (rand() %19) +3);
	show_sprite( munch_id );
	
}

void change_sprite(){

	if (m_cycle >= 110 && m_cycle <120) {
	set_sprite_image(munch_id, 4, 3, munch_char);
	}
	if (m_cycle >= 120 && m_cycle <130) {
	set_sprite_image(munch_id, 4, 3, munch_char_1);
	}
	if (m_cycle >= 130 && m_cycle <140) {
	set_sprite_image(munch_id, 4, 3, munch_char);
	}
	if (m_cycle >= 140 && m_cycle <150) {
	set_sprite_image(munch_id, 4, 3, munch_char_1);
	}
	if (m_cycle >= 150 && m_cycle < 160) {
	set_sprite_image(munch_id, 4, 3, munch_char);
	}
	if (m_cycle >= 160 && m_cycle < 170) {
	set_sprite_image(munch_id, 4, 3, munch_char_1);
	}
}


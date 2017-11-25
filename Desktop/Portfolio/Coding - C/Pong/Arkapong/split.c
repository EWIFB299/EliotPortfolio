#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "split.h"
#include "toggle.h"
#include "global.h"
#include "bounce.h"
#include "right_paddle.h"
#include "stage.h"
#include "cab202_simple_sprite.h"
#include "cab202_timer.h"
#include "cab202_screen.h"


#define S_UPDATE_TIME (60)
/*
 *	Use of timers was adjusted from the ZDK library
 */

sprite_id split_ball_id[9];
timer_id split_ball_timer;

void create_split_ball() {
for ( int n = 0; n < 9; n++ ) {
srand (time(NULL));
s_angle = ((rand() %140 )+ 110 );
	split_ball_id[n] = create_sprite( -300, -300, 'o', 0 );
	set_sprite_angle( split_ball_id[n], s_angle);
	set_sprite_timer( split_ball_id[n], split_ball_timer );
	show_sprite( split_ball_id[n] );
}
}

void setup_split_ball() {
	create_split_ball();
	split_ball_timer = create_timer(S_UPDATE_TIME );
}
void reset_split_ball() {
for ( int n = 0; n < 9; n++ ) {
	set_sprite_angle( split_ball_id[n], 180 );
	set_sprite_timer( split_ball_id[n], split_ball_timer );
	move_sprite_to( split_ball_id[n], -300, -300 );
	show_sprite( split_ball_id[n] );
	}
}

bool update_split_ball() {
	
	if ( !move_sprites_by_timer( split_ball_timer ) ) {
		return FALSE;
	}

	const screen_dimensions screen = get_screen_size();

		screen_position paddle_pos = get_sprite_screen_loc( rpaddle_id );
		screen_position plus_pos = get_sprite_screen_loc( plus_id );
		screen_position minus_pos = get_sprite_screen_loc( minus_id );
		screen_position wind_pos = get_sprite_screen_loc( wind_id );
		screen_position splitter_pos = get_sprite_screen_loc( splitter_id );
		screen_position stage_pos = get_sprite_screen_loc(stage_paddle_id);
		screen_position ai_pos = get_sprite_screen_loc(ai_paddle_id);
				screen_position munch_pos = get_sprite_screen_loc(munch_id);
		bool paddle_collision = FALSE;
		
		
		for ( int n = 0; n < 9; n++ ) {
		screen_position split_ball_pos = get_sprite_screen_loc( split_ball_id[n] );

		if ( split_ball_pos.y < 3 || split_ball_pos.y >= screen.height ) {
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_horizontal( split_ball_id[n] );
			paddle_collision = TRUE;
		}
		
		if ( split_ball_pos.x < 0 || split_ball_pos.x >= screen.width ) {
			bounce_sprite_vertical( split_ball_id[n] );
			move_sprite_to( split_ball_id[n], -300, -300 );
			set_sprite_angle(split_ball_id[n], (rand() %140 )+ 110);
		}
		
		if(!active_2){
		for ( int i = 0; i < paddle_height+1; i++ ) {
		if ( split_ball_pos.y == paddle_pos.y + i && split_ball_pos.x == paddle_pos.x) {
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_vertical( split_ball_id[n] );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		}
		else if(active_2){
		for ( int i = 0; i < paddle_height+1; i++ ) {
		if ( split_ball_pos.y == paddle_pos.y + i && split_ball_pos.x == paddle_pos.x) {
			set_sprite_angle( split_ball_id[n], (210-(60*i)/(paddle_height-1)));
			move_sprite_backward( split_ball_id[n] );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		}
		
		for ( int i = 0; i < 6; i++ ) {
		if ( split_ball_pos.y == ai_pos.y + i && split_ball_pos.x == ai_pos.x) {
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_vertical( split_ball_id[n] );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		
		for ( int i = 0; i < 5; i++ ) {
		if ((split_ball_pos.y == plus_pos.y || (split_ball_pos.y == plus_pos.y+1))&& split_ball_pos.x == plus_pos.x+i) {
			move_sprite_to(plus_id, (rand() %73) +4, (rand() %21) +3);
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_horizontal( split_ball_id[n] );
			if (paddle_height < screen.height){
			paddle_height = paddle_height + 2;
			}
			paddle_collision = TRUE;
		}
		}
		
		for ( int i = 0; i < 5; i++ ) {
		if ((split_ball_pos.y == minus_pos.y || (split_ball_pos.y == minus_pos.y+1))&& split_ball_pos.x == minus_pos.x+i) {
			move_sprite_to(minus_id, (rand() %73) +4, (rand() %21) +3);
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_horizontal( split_ball_id[n] );
			if (paddle_height > 1){
			paddle_height = paddle_height - 2;
			paddle_collision = TRUE;
			}
		}
		}

		for ( int i = 0; i < 5; i++ ) {
		if ((split_ball_pos.y == splitter_pos.y || (split_ball_pos.y == splitter_pos.y+1))&& split_ball_pos.x == splitter_pos.x+i) {
			move_sprite_to(split_ball_id[split_number], split_ball_pos.x, split_ball_pos.y);
			move_sprite_to(splitter_id, (rand() %73) +4, (rand() %21) +3);
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_horizontal( split_ball_id[n] );
			paddle_collision = TRUE;
		}
		}
		
		for ( int i = 0; i < 5; i++ ) {
		if ((split_ball_pos.y == wind_pos.y || (split_ball_pos.y == wind_pos.y+1))&& split_ball_pos.x == wind_pos.x+i) {
			move_sprite_to(wind_id, (rand() %73) +4, (rand() %21) +3);
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_horizontal( split_ball_id[n] );
			paddle_collision = TRUE;
			}
		}
		
		for ( int i = 0; i < screen.height; i++ ) {
		if ( split_ball_pos.y == stage_pos.y + i && split_ball_pos.x == stage_pos.x) {
			move_sprite_backward( split_ball_id[n] );
			bounce_sprite_vertical( split_ball_id[n] );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		
		for (int x = 0; x<10; x++) {
		screen_position bumper_pos = get_sprite_screen_loc(bumper_id[x]);
		for ( int i = 0; i < 2; i++ ) {
		if( split_ball_pos.y == bumper_pos.y+i && split_ball_pos.x == bumper_pos.x+i){
		move_sprite_to(bumper_id[x],(rand() %73) +4, (rand() %21) +3);
		move_sprite_backward( split_ball_id[n] );
		score_increase();
		bounce_sprite_vertical( split_ball_id[n] );
		}
		}
		}

		if ( paddle_collision ) {
			move_sprite_forward( split_ball_id[n] );
		}
		for ( int i = 0; i < 4; i++ ) {
		if ((split_ball_pos.y == munch_pos.y || (split_ball_pos.y == munch_pos.y+2))&& split_ball_pos.x == munch_pos.x+i) {
			move_sprite_to( split_ball_id[n], -300, -300);
			set_sprite_angle(split_ball_id[n], (rand() %140 )+ 110);
		}
		}
		}
		
		lives_depleted();
	return TRUE;
}


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


#define BALL_UPDATE_TIME (60)
/*
 *	Use of timers was adjusted from the ZDK library
 */

sprite_id ball_id;
timer_id ball_timer;

void create_ball() {
srand (time(NULL));
angle = ((rand() %140 )+ 110 );
	ball_id = create_sprite( 40, 12, 'o', 0 );
	set_sprite_angle( ball_id, angle);
	set_sprite_timer( ball_id, ball_timer );
	show_sprite( ball_id );
}

void setup_ball() {
	create_ball();
	ball_timer = create_timer(BALL_UPDATE_TIME );
}
void reset_ball() {
	screen_dimensions screen = get_screen_size();
	set_sprite_angle( ball_id, (rand() %140 )+ 110 );
	set_sprite_timer( ball_id, ball_timer );
	move_sprite_to( ball_id, screen.width / 2, screen.height / 2 );
	show_sprite( ball_id );
	
}

bool update_ball() {
	
	if ( !move_sprites_by_timer( ball_timer ) ) {
		return FALSE;
	}

	const screen_dimensions screen = get_screen_size();

		screen_position paddle_pos = get_sprite_screen_loc( rpaddle_id );
		screen_position plus_pos = get_sprite_screen_loc( plus_id );
		screen_position minus_pos = get_sprite_screen_loc( minus_id );
		screen_position wind_pos = get_sprite_screen_loc( wind_id );
		screen_position splitter_pos = get_sprite_screen_loc( splitter_id );
		screen_position ball_pos = get_sprite_screen_loc( ball_id );
		screen_position stage_pos = get_sprite_screen_loc(stage_paddle_id);
		screen_position ai_pos = get_sprite_screen_loc(ai_paddle_id);
		screen_position munch_pos = get_sprite_screen_loc(munch_id);
		bool paddle_collision = FALSE;

		if ( ball_pos.y < 3 || ball_pos.y >= screen.height ) {
			move_sprite_backward( ball_id );
			bounce_sprite_horizontal( ball_id );
			paddle_collision = TRUE;
		}
		
		if ( ball_pos.x < 0 || ball_pos.x >= screen.width ) {
			bounce_sprite_vertical( ball_id );
			move_sprite_to( ball_id, screen.width / 2, screen.height / 2 );
			set_sprite_angle(ball_id, (rand() %140 )+ 110);
			lives_decrease();
		}
		
		if(!active_2){
		for ( int i = 0; i < paddle_height+1; i++ ) {
		if ( ball_pos.y == paddle_pos.y + i && ball_pos.x == paddle_pos.x) {
			move_sprite_backward( ball_id );
			bounce_sprite_vertical( ball_id );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		}
		else if(active_2){
		for ( int i = 0; i < paddle_height+1; i++ ) {
		if ( ball_pos.y == paddle_pos.y + i && ball_pos.x == paddle_pos.x) {
			set_sprite_angle( ball_id, (210-(60*i)/(paddle_height-1)));
			move_sprite_backward( ball_id );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		}
		
		for ( int i = 0; i < 6; i++ ) {
		if ( ball_pos.y == ai_pos.y + i && ball_pos.x == ai_pos.x) {
			move_sprite_backward( ball_id );
			bounce_sprite_vertical( ball_id );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		
		for ( int i = 0; i < 5; i++ ) {
		if ((ball_pos.y == plus_pos.y || (ball_pos.y == plus_pos.y+1))&& ball_pos.x == plus_pos.x+i) {
			move_sprite_to(plus_id, (rand() %73) +4, (rand() %21) +3);
			move_sprite_backward( ball_id );
			bounce_sprite_horizontal( ball_id );
			if (paddle_height < screen.height){
			paddle_height = paddle_height + 2;
			}
			paddle_collision = TRUE;
		}
		}
		
		for ( int i = 0; i < 5; i++ ) {
		if ((ball_pos.y == minus_pos.y || (ball_pos.y == minus_pos.y+1))&& ball_pos.x == minus_pos.x+i) {
			move_sprite_to(minus_id, (rand() %73) +4, (rand() %20) +3);
			move_sprite_backward( ball_id );
			bounce_sprite_horizontal( ball_id );
			if (paddle_height > 1){
			paddle_height = paddle_height - 2;
			paddle_collision = TRUE;
			}
		}
		}
		
		for ( int i = 0; i < 4; i++ ) {
		if ((ball_pos.y == munch_pos.y || (ball_pos.y == munch_pos.y+2))&& ball_pos.x == munch_pos.x+i) {
			move_sprite_to( ball_id, screen.width / 2, screen.height / 2 );
			set_sprite_angle(ball_id, (rand() %140 )+ 110);
			lives_decrease();
		}
		}

		for ( int i = 0; i < 5; i++ ) {
		if ((ball_pos.y == splitter_pos.y || (ball_pos.y == splitter_pos.y+1))&& ball_pos.x == splitter_pos.x+i) {
			move_sprite_to(splitter_id, (rand() %73) +4, (rand() %20) +3);
			move_sprite_to(split_ball_id[split_number], ball_pos.x, ball_pos.y);
			set_sprite_angle( split_ball_id[split_number], (360-angle));
			move_sprite_backward( ball_id );
			bounce_sprite_horizontal( ball_id );
			paddle_collision = TRUE;
			split_number++;
		}
		}
		
		for ( int i = 0; i < 5; i++ ) {
		if ((ball_pos.y == wind_pos.y || (ball_pos.y == wind_pos.y+1))&& ball_pos.x == wind_pos.x+i) {
			move_sprite_to(wind_id, (rand() %73) +4, (rand() %20) +3);
			move_sprite_backward( ball_id );
			bounce_sprite_horizontal( ball_id );
			paddle_collision = TRUE;
			}
		}
		
		for ( int i = 0; i < screen.height; i++ ) {
		if ( ball_pos.y == stage_pos.y + i && ball_pos.x == stage_pos.x) {
			move_sprite_backward( ball_id );
			bounce_sprite_vertical( ball_id );
			paddle_collision = TRUE;
			score_increase();
		}
		}
		
		for (int x = 0; x<10; x++) {
		screen_position bumper_pos = get_sprite_screen_loc(bumper_id[x]);
		for ( int i = 0; i < 2; i++ ) {
		if((ball_pos.y == bumper_pos.y+i+1 || ball_pos.y == bumper_pos.y-1 )&& ball_pos.x == bumper_pos.x+i){
		move_sprite_to(bumper_id[x],(rand() %73) +4, (rand() %20) +3);
		move_sprite_backward( ball_id );
		score_increase();
		bounce_sprite_horizontal( ball_id );
		if( ball_pos.y == bumper_pos.y+i && ball_pos.x == bumper_pos.x+i && angle == 180){
		move_sprite_to(bumper_id[x],(rand() %73) +4, (rand() %20) +3);
		move_sprite_backward( ball_id );
		score_increase();
		bounce_sprite_vertical( ball_id );
		}
		}
		}
		}

		if ( paddle_collision ) {
			move_sprite_forward( ball_id );
		}
		
		if(wind_count == 1){
		if ( ball_pos.y < 10 || ball_pos.y >= screen.height-10 ) {
		move_sprite(ball_id, 0, -1);
				if ( ball_pos.y <3 ) {
			move_sprite_to(ball_id, ball_pos.x, 4);
		}
		}
		}
		if(wind_count == 2){
		if ( ball_pos.x < 2 || ball_pos.x >= screen.width-2 ) {
		move_sprite(ball_id, 1, 0);
		}
		}
		if(wind_count == 3){
		if ( ball_pos.y < 5 || ball_pos.y >= screen.height-5 ) {
		move_sprite(ball_id, 0, 1);
		if ( ball_pos.y >screen.height-2 ) {
			move_sprite_to(ball_id, ball_pos.x, screen.height-1);
		}
		}
		}
		if(wind_count == 4){
		if ( ball_pos.x < 2|| ball_pos.x >= screen.width-2 ) {
		move_sprite(ball_id, -1, 0);
		}
		}
		
		if (m_cycle == 170) {
			move_sprite_to( munch_id, -10, -10);
			m_cycle = 70;
			
		}
		
		if (active_8){
		if ( m_cycle == 110 ) {
			move_sprite_to( munch_id, 10, (rand() %19) +3);
		}
		}
		
		change_sprite();
		m_cycle++;
		lives_depleted();
		
	return TRUE;
}


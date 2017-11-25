#include "game.h"

void setup_game() {
	auto_refresh_sprites = FALSE;
	auto_sprite_delay = FALSE;
	auto_wrap_sprites = FALSE;

	setup_screen();
	setup_right_paddle();
	setup_ball();
	setup_split_ball();
	setup_stage();
	setup_global();
	setup_toggle();
	setup_options();
	setup_munch();
	reset_split_ball();
	refresh();
}


void reset_game() {
	reset_screen();
	reset_right_paddle( );
	reset_ball();
	reset_split_ball();
	reset_stage();
	reset_size();
	reset_munch();
	setup_toggle();
	setup_global();
	refresh( );
}


int play_turn() {
	if ( update_screen() ) {
		reset_game();
		return TURN_OK;
	}

	/* If we have a key, process it immediately. */
	int key_code = getch();

	if ( key_code == 'q' || key_code == 'Q' ) {
		return TURN_GAME_OVER;
	}
	else if ( key_code == 'r' || key_code == 'R' ) {
		reset_game();
		return TURN_OK;
	}

	if ( update_right_paddle( key_code ) ) {
		return TURN_SCREEN_CHANGED;
	}
	if ( update_ball() ) {
		return TURN_SCREEN_CHANGED;
	}
	if ( update_split_ball() ) {
		return TURN_SCREEN_CHANGED;
	}
	if ( update_toggle(key_code) ) {
		return TURN_SCREEN_CHANGED;
	}
	if ( update_stage_paddle() ) {
		return TURN_SCREEN_CHANGED;
	}

	return TURN_OK;
}

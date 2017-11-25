#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "global.h"
#include "right_paddle.h"
#include "toggle.h"
#include "stage.h"
#include <unistd.h>
#include <time.h>

// INSERT GLOBAL VARIABLES HERE

sprite_id stage_paddle_id;
sprite_id ai_paddle_id;
timer_id ai_timer;


//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE

#define TURN_SCREEN_CHANGED 1
#define TURN_OK 0
#define TURN_GAME_OVER -1
#define BUMPER_COUNT 10
#define AI_UPDATE_TIMER 60

//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_stage() {
	const screen_dimensions screen = get_screen_size();
	stage_collumn = 2;
	ai_collumn = -1;
	stage_paddle_id = create_big_sprite(stage_collumn,3,1,screen.height-3, paddle_char);
	ai_paddle_id = create_big_sprite(-1,0,1,5, paddle_char);
	set_sprite_timer( ai_paddle_id, ai_timer );
	
}

void reset_stage() {
move_sprite_to(stage_paddle_id,2,3);
show_sprite(stage_paddle_id);
move_sprite_to(ai_paddle_id,-1,0);
show_sprite(ai_paddle_id);

}

bool update_stage_paddle() {

	screen_position ball_pos = get_sprite_screen_loc( ball_id );
	screen_position ai_pos = get_sprite_screen_loc(ai_paddle_id);

	
	if (ai_pos.y > ball_pos.y) {
			move_sprite( ai_paddle_id, 0, -1 );
	}
	else if (ai_pos.y < ball_pos.y-4) {
		move_sprite( ai_paddle_id, 0, 1 );
	}
	
return TRUE;
}

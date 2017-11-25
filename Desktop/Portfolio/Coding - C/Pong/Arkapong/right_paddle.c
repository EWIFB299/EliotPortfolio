#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "right_paddle.h"


// INSERT GLOBAL VARIABLES HERE

sprite_id rpaddle_id;
char paddle_char[]=
	"|"	
	"|"
	"|"
	"|"
	"|"
	"|"	
	"|"
	"|"
	"|"
	"|"
	"|"	
	"|"
	"|"
	"|"
	"|"
	"|"	
	"|"
	"|"
	"|"
	"|"
	"|"	
	"|"
	;

//-----------------------------------------------------------------------------
//  Function declarations.
//-----------------------------------------------------------------------------

// INSERT DECLARATIONS FOR HELPER FUNCTIONS HERE

#define TURN_SCREEN_CHANGED 1
#define TURN_OK 0
#define TURN_GAME_OVER -1


//-----------------------------------------------------------------------------
//  Function implementations.
//-----------------------------------------------------------------------------


void setup_right_paddle() {
	screen_dimensions screen = get_screen_size();

paddle_height = 5;
paddle_width = 1;

	rpaddle_id = create_big_sprite(screen.width-2,7,paddle_width,paddle_height,paddle_char);
}

void reset_right_paddle() {
		screen_dimensions screen = get_screen_size();
move_sprite_to(rpaddle_id,screen.width-2,7);
show_sprite( rpaddle_id );
}

bool update_right_paddle( int key_code ) {
	
	set_sprite_image(rpaddle_id, 1, paddle_height, paddle_char);
	
	bool right_paddle_moved = FALSE;
	
	screen_position paddle_pos = get_sprite_screen_loc( rpaddle_id );
	screen_dimensions screen = get_screen_size();

	if (key_code == KEY_UP && paddle_pos.y> 3 && paddle_pos.y < screen.height) {
		move_sprite( rpaddle_id, 0, -1 );
	}
	else if (key_code == KEY_DOWN && paddle_pos.y> -1 && paddle_pos.y < screen.height - paddle_height) {
		move_sprite( rpaddle_id, 0, 1 );
	}

	return right_paddle_moved;
}


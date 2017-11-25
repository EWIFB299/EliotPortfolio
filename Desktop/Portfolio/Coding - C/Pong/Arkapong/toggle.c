#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "toggle.h"
#include "stage.h"
#include "global.h"
#include "munch.h"
#include "ball.h"
#include "right_paddle.h"
#include "bounce.h"

void setup_toggle() {
active_1 = FALSE;
mvprintw(1,3,"1: OFF");

active_2 = FALSE;
mvprintw(1,10,"2: OFF");

active_3 = FALSE;
mvprintw(1,17,"3: OFF");

active_4 = FALSE;
mvprintw(1,24,"4: OFF");

active_5 = FALSE;
mvprintw(1,31,"5: OFF");

active_6 = FALSE;
mvprintw(1,38,"6: OFF");

active_7 = FALSE;
wind_count=0;
mvprintw(1,45,"7: OFF");

active_8 = FALSE;
mvprintw(1,52,"8: OFF");
}

void move_paddle(){
	move_sprite_to( stage_paddle_id, stage_collumn, 3);	
}

bool update_toggle(int key_code) {

bool changed = FALSE;

if (key_code == '1'){
	active_1 = !active_1;
	if (active_1){
	mvprintw(1,3,"1: ON ");
	stage_collumn = -1;
	ai_collumn = 2;
	move_paddle();
	move_sprite( ai_paddle_id, 3, 0);	
	}
	if(!active_1){
	mvprintw(1,3,"1: OFF");
	stage_collumn = 2;
	ai_collumn = 1;
	move_paddle();
	move_sprite( ai_paddle_id, -3, 0);
	}
	changed = TRUE;
}
if (key_code == '2'){
	active_2 = !active_2;
	if (active_2){
	mvprintw(1,10,"2: ON ");
	}
	if (!active_2){
	mvprintw(1,10,"2: OFF");
	}
	changed = TRUE;
}
if (key_code == '3'){
	active_3 = !active_3;
	if (active_3){
	mvprintw(1,17,"3: ON ");
	move_bounce();
	}
	if (!active_3){
	mvprintw(1,17,"3: OFF");
	reset_bounce();
	}
	changed = TRUE;
}
if (key_code == '4'){
	active_4 = !active_4;
	if (active_4){
	move_plus();
	mvprintw(1,24,"4: ON ");
	}
	if (!active_4){
	reset_plus();
	paddle_height = 5;
	mvprintw(1,24,"4: OFF");
	}
	changed = TRUE;
}	
if (key_code == '5'){
	active_5 = !active_5;
	if (active_5){
	move_minus();
	mvprintw(1,31,"5: ON ");
	}
	if (!active_5){
	reset_minus();
	mvprintw(1,31,"5: OFF");
	}
	changed = TRUE;
}
if (key_code == '6'){
	active_6 = !active_6;
	if (active_6){
	move_splitter();
	mvprintw(1,38,"6: ON ");
	}
	if (!active_6){
	mvprintw(1,38,"6: OFF");
	reset_splitter();
	split_number= 0;
	}
	changed = TRUE;
}
if (key_code == '7'){
	wind_count = wind_count+1;
	if (wind_count >= 5){
	mvprintw(1,69,"W:       " );
	wind_count = 0;
	}
	if(wind_count == 1){
	move_wind();
	mvprintw(1,69,"W: UP " );
	}
	if(wind_count == 2){
	mvprintw(1,69,"W: RIGHT " );
	}
	if(wind_count == 3){
	mvprintw(1,69,"W: DOWN " );
	}
	if(wind_count == 4){
	mvprintw(1,69,"W: LEFT " );
	}
	if (wind_count > 0){
	mvprintw(1,45,"7: ON ");
	}
	else if (wind_count == 0){
	reset_wind();
	mvprintw(1,45,"7: OFF ");
	mvprintw(1,69,"     ");
	}
	changed = TRUE;
	}

if (key_code == '8'){
	active_8 = !active_8;
	if (active_8){
	move_munch();
	mvprintw(1,52,"8: ON ");
	}
	if (!active_8){
	reset_munch();
	mvprintw(1,52,"8: OFF");
	}
	changed = TRUE;
}
return changed;
}

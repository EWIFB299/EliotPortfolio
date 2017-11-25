#include <stdlib.h>
#include <time.h>

#include "ball.h"
#include "split.h"
#include "cab202_simple_sprite.h"
#include "cab202_timer.h"
#include "cab202_screen.h"

#define BUMPER_COUNT 10
#define M_UPDATE_TIME (60)
sprite_id bumper_id[10];
sprite_id plus_id;
sprite_id minus_id;
sprite_id splitter_id;
sprite_id wind_id;

/*		POINT	BUMPER		 */

void setup_bounce(){
char reflect_char[]=
"##"
"##"
;
for (int x = 0; x< BUMPER_COUNT; x++){
bumper_id[x] = create_big_sprite(-4,-4,2,2, reflect_char);
}
}

void move_bounce(){
srand (time(NULL));
for (int x = 0; x< BUMPER_COUNT; x++) {
	move_sprite_to(bumper_id[x], (rand() %73) +4, (rand() %20) +3);
	}
}

void reset_bounce(){
for (int x = 0; x< BUMPER_COUNT; x++){
	move_sprite_to(bumper_id[x], -4, -4);
	}
}

/*		SIZE	BLOCKS	  */

void setup_size(){
char plus_char[]=
"#+++#"
;
plus_id= create_big_sprite(-4,-4,5,1, plus_char);
char minus_char[]=
"#---#"
;
minus_id= create_big_sprite(-4,-4,5,1, minus_char);
}

void move_plus(){
srand (time(NULL));
	move_sprite_to(plus_id, (rand() %73) +4, (rand() %21) +3);
}

void move_minus(){
srand (time(NULL));
	move_sprite_to(minus_id, (rand() %73) +4, (rand() %21) +3);
}

void reset_plus(){
	move_sprite_to(plus_id, -4, -4);
}
void reset_minus(){
	move_sprite_to(minus_id, -4, -4);
}
void reset_size(){
reset_plus();
reset_minus();
}

/*		WIND	BLOCK	 */

void setup_wind(){
char wind_char[]=
"@WIW@"
"@@I@@"
;
wind_id= create_big_sprite(-4,-4,5,2, wind_char);
}

void move_wind(){
srand (time(NULL));
	move_sprite_to(wind_id, (rand() %70) +4, (rand() %21) +3);
}

void reset_wind(){
	move_sprite_to(wind_id, -4, -4);
}
 
 
/*		SPLITTER	BLOCK		 */

void setup_splitter(){
char splitter_char[]=
"%%%%%"
"%%%%%"
;
splitter_id = create_big_sprite(-4,-4,5,2, splitter_char);
}

void move_splitter(){
srand (time(NULL));
	move_sprite_to(splitter_id, (rand() %70) +4, (rand() %21) +3);
}

void reset_splitter(){
	move_sprite_to(splitter_id, -4, -4);
}
			
			
void setup_options() {
setup_bounce();
setup_size();
setup_wind();
setup_splitter();
}
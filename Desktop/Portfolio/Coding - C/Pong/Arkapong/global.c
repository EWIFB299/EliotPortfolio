#include "cab202_simple_sprite.h"
#include "cab202_screen.h"

#include "global.h"
#include "right_paddle.h"
#include "ball.h"
#include "right_paddle.h"
#include "stage.h"

// INSERT GLOBAL VARIABLES HERE
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


void setup_global() {
screen_dimensions screen = get_screen_size();
score = 0;
lives = 3;
paddle_height = 5;
mvprintw(0,3,"SCORE: %d", score);
mvprintw(0,68,"LIVES: %d", lives);
for ( int i = 0; i < screen.width; i++ ) {
mvprintw(2,i,"_", score);
}
}

int increase_score(){
score = score +1;
return score;
}

void score_increase() {
		increase_score();
		mvprintw(0,3,"SCORE: %d", score);
}

int decrease_lives(){
lives = lives -1;
return lives;
}

void lives_decrease() {
		decrease_lives();
		mvprintw(0,68,"LIVES: %d", lives);
}


void lives_depleted(){
if(lives == 0){
end_game();
}
}

void end_game(){
screen_dimensions screen = get_screen_size();
print_centre_string( "Can't even win at PONG! Press 'r' to try again. Or 'q' to quit.",screen.width / 2, screen.height / 2 );
hide_sprite(ball_id);
}
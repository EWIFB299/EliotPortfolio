#define F_CPU 8000000UL
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_8MHz 0x01

#define NUM_ITEMS 2
#define ZOMBIE_COUNT 8
#define MAX_CLOCK_COUNTER_FOR_100MSECOND 3

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <math.h>
#include <util/delay.h> 
#include <stdlib.h>

#include "sprite.h"
#include "setup.h"
#include "lcd.h"
#include "graphics.h"

void Init(void);
void TimerInit(void);
void PinChangeInit(void);
void update_sprite( Sprite * sprite );
void stage_collision( Sprite * sprite );
void sprite_angle_change(Sprite * sprite );
void update_bomb(void);
void update_weapon(void);
void update_zombies(void);
void hero_collision(void);
void draw_pit(void);
void reset_game(void);
void check_collison(void);
void draw_stage(void);


volatile double border1[] = {19,20,38,20};  //19 pixels
volatile double border2[] = {38,20,38,41};  //21 pixels
volatile double border3[] = {43,30,60,30};  //17 pixels
volatile double border4[] = {73,10,83,10};	 //10 pixels
volatile double border5[] = {73,20,83,20};	 //10 pixels
volatile double border6[] = {73,30,83,30};  //10 pixels
volatile double border7[] = {73,40,83,40};  //10 pixels
volatile double border8[] = {52,40,65,40};	 //13 pixels


 
volatile int newPosX = 0;
volatile int newPosY = 0;
volatile int grePosX = 30;
volatile int grePosY = 30;
volatile int upgrade = 0;
volatile int held = 0;
volatile int active = 0;
volatile int jumpingCount = -1;
volatile int explosionTime = 5;
volatile int cooldown = 0;
volatile int seedcount = 1;
volatile int pincount= 0;
volatile int buttonPressed = 0;
volatile int lives = 3;
volatile int items[NUM_ITEMS];
volatile int item_pos[NUM_ITEMS * 2];
volatile int pit_points[4] = { 30, 5, 50, 15};
volatile int gameOver = 0;
volatile int gameOverCount = ZOMBIE_COUNT;
volatile int globalCounter = 0;
volatile int scoreCounter = 0;
volatile int clockCounter = 0;
volatile int tagged = 0;
volatile double swit =0.1;
Sprite sprite;
	byte bithero[] = {
		BYTE( 11100000 ),
		BYTE( 10100000 ),
		BYTE( 11100000 ),
	};
	
Sprite zombies[ZOMBIE_COUNT];
	byte bitzom[] = {
		BYTE( 11100000 ),
		BYTE( 11100000 ),
		BYTE( 11100000 ),
	};
	
Sprite sword;

	byte bitsword[] = {
		BYTE( 11100000 ),
		BYTE( 01000000 ),
		BYTE( 11100000 ),
	};
	byte bitswordside[] = {
		BYTE( 10100000 ),
		BYTE( 11100000 ),
		BYTE( 10100000 ),
	};
	
Sprite bomb;

	byte bitbomb[] = {
		BYTE( 01000000 ),
		BYTE( 11100000 ),
		BYTE( 11100000 ),
	};
	byte bitexplosion[] = {
		BYTE( 01001111 ),
		BYTE( 11111110 ),
		BYTE( 11011110 ),
		BYTE( 01111100 ),
		BYTE( 01111110 ),
		BYTE( 11111010 ),
		BYTE( 01111111 ),
		BYTE( 00101110 ),
	};

int main(void)
{
	//Initialize
	CPU_PRESCALE(CPU_8MHz);
	Init();
	PinChangeInit();
	title_screen();	
	TimerInit();
	
	clear();
	init_sprite(&sprite, ((LCD_X/2)+5), LCD_Y/2, 3, 3, bithero );
	sprite.is_visible=1;
	sprite.dx=-1;
	draw_sprite(&sprite);
	
for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
	int tempX=45;
	int tempY=22;
	srand(pincount* i* seedcount);
	
	while(tempX > 35 && tempX < 55){
		tempX = 18 + rand() %70;
		seedcount++;
	}
	while(tempY > 12 && tempY< 23){
		tempY = 2+ rand() %30;
		seedcount++;
	}
	swit=-swit;
	init_sprite(&zombies[i], tempX, tempY, 3, 3, bitzom );
	zombies[i].is_visible=1;
	zombies[i].dx=-swit;
	zombies[i].dy=swit;
	draw_sprite(&zombies[i]);
	seedcount++;
}

	init_sprite(&sword, sprite.x, ((sprite.y)-3), 3, 3, bitsword );
	sword.is_visible=1;
	sword.dx= sprite.dx;
	sword.dy= sprite.dy;
	draw_sprite(&sword);
		
	init_sprite(&bomb, grePosX, grePosY, 3, 3, bitbomb );
	bomb.is_visible=1;
	draw_sprite(&bomb);
	
	while(!gameOver)
	{
	}
	clear();
	if(gameOver==1){
		draw_string("GAME OVER!", LCD_X/2-25, LCD_Y/2-5);
	}
	if(gameOver==2){
		draw_string("YOU WIN!", LCD_X/2-25, LCD_Y/2-5);
	}
	refresh();
		
	return 0;
}

void Init()
{
	DDRB |= (1<<PB2)|(1<<PB3);	//LED0 and LED1 as outputs
	DDRB &= ~((1<<PB0)|(1<<PB1));	//Switch0 and Switch1 as input
	PORTB = 0x00; 	// Turn everything off to start with
	LCDInitialise( LCD_DEFAULT_CONTRAST );
	clear();
	refresh();
}

void TimerInit(void)
{
	//Set to Normal Timer Mode using TCCR0A and TCCR0B
	TCCR0A &= ~((1<<WGM01)|(WGM00));
	TCCR0B &= ~((1<<WGM02));
	
	//Set Prescaler using TCCR0B, using Clock Speed find timer speed = 1/(Clock Speed/Prescaler)
	//Prescaler = 1024
	//Timer Speed = 128 nano seconds
	//Timer Overflow Speed = 32640 nano seconds (Timer Speed * 255) - (255 since 8-bit timer)
	TCCR0B |= (1<<CS02)|(1<<CS00);
	TCCR0B &= ~((1<<CS01));
	
	//Enable TOIE0 interrupt in the TIMSK0 register
	TIMSK0 |= (1<<TOIE0);
	
	//Ensure to enable global interrupts as well.
	sei();
}

void PinChangeInit(void)
{
	//Enable PCINT0 and PCINT1 (both buttons) in the PCMSK0 register
	PCMSK0 |= (1<<PCINT0);
	PCMSK0 |= (1<<PCINT1);

	//Enable Pin change interrupts in the Pin Change Interrupt Control Register
	PCICR |= (1<<PCIE0);
	
	//Set the PCINT0 and PCINT1 interrupts to trigger on rising edge
	EICRA |= ((1<<ISC00)&&(1<<ISC01)&&(1<<ISC10)&&(1<<ISC11));
		
	//Ensure to enable global interrupts as well.
	sei();
}

void update_sprite( Sprite * sprite ) {

	sprite->x += sprite->dx;
	sprite->y += sprite->dy;
	
if ( sprite->x >= LCD_X - sprite->width){
		sprite->x = sprite->x-1;
	}
if (sprite->x < 15 ){
		sprite->x = sprite->x+1;
}
		
if ( sprite->y >= LCD_Y - sprite->height){
		sprite->y = sprite->y-1;
	}
if (sprite->y < 0){
		sprite->y = sprite->y+1;
}	
	if ( sprite->x <= -1){
		sprite->x=-50;
	}
	if ( sprite->y <= -1){
		sprite->y=-50;
	}
}

void stage_collision( Sprite * sprite ) {
	
if ( sprite->y+1 == border1[1]){
		if ((sprite->x >= border1[0]) && (sprite->x <= border1[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y-(sprite->dy);
			}
	}
}
if ( sprite->x+1 == border2[0]){
		if ((sprite->y >= border2[1]) && (sprite->y <= border2[3])){
			if(sprite->dx > 0){
				sprite->x = sprite->x-(sprite->dx);
			}
			else if(sprite->dx < 0){
				sprite->x = sprite->x-(sprite->dx);
			}
	}
}

if ( sprite->y+1 == border3[1]){
		if ((sprite->x >= border3[0]) && (sprite->x <= border3[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y-(sprite->dy);
			}
}
}

if ( sprite->y+1 == border4[1]){
		if ((sprite->x >= border4[0]) && (sprite->x <= border4[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y-(sprite->dy);
			}
}
}

if ( sprite->y+1 == border5[1]){
		if ((sprite->x >= border5[0]) && (sprite->x <= border5[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y-(sprite->dy);
			}
		}
}

if ( sprite->y+1 == border6[1]){
		if ((sprite->x >= border6[0]) && (sprite->x <= border6[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y-(sprite->dy);
			}
}
}

if ( sprite->y+1 == border7[1]){
		if ((sprite->x >= border7[0]) && (sprite->x <= border7[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y-(sprite->dy);
			}
}
}
if ( sprite->y+1 == border8[1]){
		if ((sprite->x >= border8[0]) && (sprite->x <= border8[2])){
			if(sprite->dy > 0){
				sprite->y = sprite->y-(sprite->dy);
			}
			else if(sprite->dy < 0){
				sprite->y = sprite->y+(sprite->dy);
			}
}
}
}

void z_stage_collision() {
	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		if ( (zombies[i].y+1 > border1[1]-1) && (zombies[i].y-1 < border1[1])){
				if ((zombies[i].x >= border1[0]) && (zombies[i].x <= border1[2])){
					zombies[i].dy= -zombies[i].dy;
			}
		}
		if ( (zombies[i].y+1 > border2[0]-1) && (zombies[i].y-1 < border2[0])){
				if ((zombies[i].y >= border2[1]) && (zombies[i].y <= border2[3])){
					zombies[i].dx= -zombies[i].dx;
			}
		}

		if ( (zombies[i].y+1 > border3[1]-1) && (zombies[i].y-1 < border3[1])){
				if ((zombies[i].x >= border3[0]) && (zombies[i].x <= border3[2])){
					zombies[i].dy= -zombies[i].dy;
		}
		}

		if ( (zombies[i].y+1 > border4[1]-1) && (zombies[i].y-1 < border4[1])){
				if ((zombies[i].x >= border4[0]) && (zombies[i].x <= border4[2])){
					zombies[i].dy= -zombies[i].dy;
		}
		}

		if ( (zombies[i].y+1 > border5[1]-1) && (zombies[i].y-1 < border5[1])){
				if ((zombies[i].x >= border5[0]) && (zombies[i].x <= border5[2])){
					zombies[i].dy= -zombies[i].dy;
				}
		}

		if ( (zombies[i].y+1 > border6[1]-1) && (zombies[i].y-1 < border6[1])){
				if ((zombies[i].x >= border6[0]) && (zombies[i].x <= border6[2])){
					zombies[i].dy= -zombies[i].dy;
		}
		}

		if ( (zombies[i].y+1 > border7[1]-1) && (zombies[i].y-1 < border7[1]+1)){
				if ((zombies[i].x >= border7[0]) && (zombies[i].x <= border7[2])){
					zombies[i].dy= -zombies[i].dy;
		}
		}
		if ( (zombies[i].y+1 > border8[1]-1) && (zombies[i].y-1 < border8[1])){
				if ((zombies[i].x >= border8[0]) && (zombies[i].x <= border8[2])){
					zombies[i].dy= -zombies[i].dy;
		}
		}
		}
}

void update_bomb(){
	
	if((sprite.x > bomb.x -1 && sprite.x < bomb.x + 2 )&& (sprite.y > bomb.y -1 && sprite.y < bomb.y + 2)){
			active=2;
			bomb.x=-10;
			bomb.y=-10;
		}
		
	if(active > 1){
		draw_character('o', 4 ,19);
	}
	
	if(active==2){
		if(jumpingCount > 8){
			bomb.x = sprite.x;
			bomb.y = sprite.y;
			active=1;
		}
	}
	if(active==1){	
		if(jumpingCount==0){
			bomb.bitmap=bitexplosion;
			bomb.width=10;
			bomb.height=10;
			bomb.x= bomb.x-1;
			bomb.y= bomb.y-1;
			explosionTime=5;
		}
		if(explosionTime==0){
			active=0;
			bomb.bitmap=bitbomb;
			bomb.width=3;
			bomb.height=3;
			srand(clockCounter + (seedcount * globalCounter));
			grePosX=45;
			grePosY=22;
	
			while(grePosX > 35 && grePosX < 55){
				grePosX = 18 + rand() %60;
			}
			while(grePosY > 12 && grePosY< 23){
				grePosY = 2+ rand() %30;
			}
			
			bomb.x=grePosX;
			bomb.y=grePosY;
		}
	}
	
}

void update_weapon(){
	
if(upgrade==0){
	
	if(tagged==0){
	int tempX=45;
	int tempY=22;
	srand(seedcount * globalCounter);
	
	while(tempX > 35 && tempX < 55){
		tempX = 18 + rand() %60;
		seedcount++;
	}
	
	while(tempY > 12 && tempY< 23){
		tempY = 2+ rand() %30;
		seedcount++;
	}
		sword.dx=0;
		sword.dy=0;
		sword.x = tempX;
		sword.y = tempY;
		tagged=1;
	}
		
		if((sprite.x > sword.x -1 && sprite.x < sword.x + 2 )&& (sprite.y > sword.y -1 && sprite.y < sword.y + 2)){
			upgrade=1;
			scoreCounter = scoreCounter+3;
			held=1;
		}
		}
	
	if(upgrade==1){
		if(sprite.dx==1){
			sword.bitmap = bitswordside;
			sword.x = ((sprite.x)+3);
			sword.y = sprite.y;
		}
		if(sprite.dx==-1){
			sword.bitmap = bitswordside;
			sword.x = ((sprite.x)-3);
			sword.y = sprite.y;
		}
		if(sprite.dy==1){
			sword.bitmap = bitsword;
			sword.y = ((sprite.y)+3);
			sword.x = sprite.x;
		}
		if(sprite.dy==-1){
			sword.bitmap = bitsword;
			sword.y = ((sprite.y)-3);
			sword.x = sprite.x;
		}
			sword.dx = sprite.dx;
			sword.dy = sprite.dy;
	}
}

void pit_collision( Sprite * sprite){
	
	for ( int i = pit_points[1]; i < pit_points[3]; i++ ) {
		if ( sprite->y == i){
			if ( sprite->x == ((pit_points[2]) +1)) {
				sprite->x = sprite->x-5;
			}
		}
	}
	for ( int i = pit_points[1]; i < pit_points[3]; i++ ) {
		if ( sprite->y == i){
			if ( sprite->x == ((pit_points[0]) -1)) {
				sprite->x = sprite->x+5;
			}
		}
	}
	for ( int i = pit_points[0]; i < pit_points[2]; i++ ) {
		if ( sprite->x == i){
			if ( sprite->y == ((pit_points[1]) -1)) {
				sprite->y = sprite->y+5;
			}
		}
	}
	for ( int i = pit_points[0]; i < pit_points[2]; i++ ) {
		if ( sprite->x == i){
			if ( sprite->y == ((pit_points[3]) +1)) {
				sprite->y = sprite->y-5;
			}
		}
	}	
	if ( (sprite->x > pit_points[0]) && sprite->x < pit_points[2] ) {
		if ( (sprite->y > pit_points[1]-1 && sprite->y < pit_points[1]+1)|| (sprite->y > pit_points[3]-1 && sprite->y < pit_points[3]+1) ) {
			sprite->dy = -sprite->dy;
	}
	}
	if ( (sprite->y > pit_points[1]) && sprite->y < pit_points[3] ) {
		if ( (sprite->x > pit_points[0]-1 && sprite->x < pit_points[0]+1)|| (sprite->x > pit_points[2]-1 && sprite->x < pit_points[2]+1) ) {
			sprite->dx = -sprite->dx;
		}
	}
}

void hero_collision( ){
	if(jumpingCount <= 0){
	pit_collision(&sprite);
	}
} 

void update_zombies( ) {
	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		update_sprite(&zombies[i]);
		if(zombies[i].x <16){
			zombies[i].dx = -zombies[i].dx;
		}
		if ( zombies[i].x > (LCD_X - zombies[i].width)-1){
			zombies[i].dx = -zombies[i].dx;
		}
		if(zombies[i].y <1){
			zombies[i].dy = -zombies[i].dy;
		}
		if ( zombies[i].y > (LCD_Y - zombies[i].height)-1){
			zombies[i].dy = -zombies[i].dy;
		}
		draw_sprite(&zombies[i]);
	}
}

void sprite_angle_change(Sprite * sprite ) {
		srand(globalCounter * seedcount);
		int temp = rand() %100;
		if(temp > 94){
			if(sprite->dx > 0){
				sprite->dx = sprite->dx -1;
			}
			if(sprite->dx < 0){
				sprite->dx = sprite->dx +1;
			}
		}
		else if(temp < 6){
			if(sprite->dy > 0){
				sprite->dy = sprite->dy -1;
			}
			if(sprite->dy < 0){
				sprite->dy = sprite->dy +1;
			}
		}
}

void draw_pit(){
		draw_line(pit_points[0],pit_points[1],pit_points[2],pit_points[1]);
		draw_line(pit_points[0],pit_points[1],pit_points[0],pit_points[3]);
		draw_line(pit_points[0],pit_points[3],pit_points[2],pit_points[3]);
		draw_line(pit_points[2],pit_points[1],pit_points[2],pit_points[3]);
}

void reset_game() {
	sprite.x =((LCD_X/2)+5);
	sprite.y = LCD_Y/2;
for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
	srand(clockCounter + (i * globalCounter));
	int tempX=45;
	int tempY=22;
	
	while(tempX > 35 && tempX < 55){
		tempX = 18 + rand() %60;
	}
	while(tempY > 12 && tempY< 23){
		tempY = 2+ rand() %30;
	}
	zombies[i].x = tempX;
	zombies[i].y = tempY;
	zombies[i].is_visible=1;
}
}

void check_collison() {
	for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
	int zomX = zombies[i].x;
	int zomY = zombies[i].y;
		if(zomX == sprite.x && zomY == sprite.y){
			reset_game();
			if(cooldown < 0){
			lives--;
			held=0;
			upgrade=0;
			gameOverCount= ZOMBIE_COUNT;
			cooldown=50;
		}
	}
	}
	
	if(held==1){
		for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		int tempX = zombies[i].x;
		int tempY = zombies[i].y;
			if((tempX > sword.x -1 && tempX < sword.x + 2 )&& (tempY > sword.y -1 && tempY < sword.y + 2)){
				zombies[i].x=-10;
				zombies[i].y=-10;
				scoreCounter = scoreCounter+2;
				gameOverCount--;
		}
	}
}
	if(explosionTime > 0){
		for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
		int tempX = zombies[i].x;
		int tempY = zombies[i].y;
			if((tempX > bomb.x && tempX < bomb.x + 10 )&& (tempY > bomb.y && tempY < bomb.y + 10)){
				zombies[i].x=-10;
				zombies[i].y=-10;
				scoreCounter = scoreCounter+2;
				gameOverCount--;
		}
	}
}
}

void draw_stage() {
	draw_line(border1[0],border1[1],border1[2],border1[3]);
	draw_line(border2[0],border2[1],border2[2],border2[3]);
	draw_line(border3[0],border3[1],border3[2],border3[3]);
	draw_line(border4[0],border4[1],border4[2],border4[3]);
	draw_line(border5[0],border5[1],border5[2],border5[3]);
	draw_line(border6[0],border6[1],border6[2],border6[3]);
	draw_line(border7[0],border7[1],border7[2],border7[3]);
	draw_line(border8[0],border8[1],border8[2],border8[3]);
}

ISR(PCINT0_vect)
{
	pincount++;
	if(gameOver==0){
	if(stage==0){
	if ((PINB>>0)&1){
		chosen=1;
	}
	if ((PINB>>1)&1){
		if (choice==1){
			choice = 2;
			draw_character(' ',34,20);
			draw_character('*',0,20);	
			refresh();
		}	
		else if (choice==2){
			choice = 1;
			draw_character('*',34,20);
			draw_character(' ',0,20);
			refresh();
		}
	}
	refresh();
	}
if(stage == 1){
	buttonPressed=0;
	if ((PINB>>0)&1){
		buttonPressed = 1;
	}
	if ((PINB>>1)&1){
		if (buttonPressed){
			buttonPressed = 3;
		} else {
			buttonPressed = 2;
		}
	}
	if (buttonPressed==1){
		if(sprite.dx == 1){
			sprite.dx = 0;
			sprite.dy = -1;
		}
		else if( sprite.dx == -1){
			sprite.dx = 0;
			sprite.dy = 1;
		}
		else if( sprite.dy == 1){
			sprite.dx = 1;
			sprite.dy = 0;
		}
		else if( sprite.dy == -1){
			sprite.dx = -1;
			sprite.dy = 0;

		}
	} else if (buttonPressed==2){
		if(sprite.dx == 1){
			sprite.dx = 0;
			sprite.dy = 1;
		}
		else if( sprite.dx == -1){
			sprite.dx = 0;
			sprite.dy = -1;
		}
		else if( sprite.dy == 1){
			sprite.dx = -1;
			sprite.dy = 0;
		}
		else if( sprite.dy == -1){
			sprite.dx = 1;
			sprite.dy = 0;

		}
	}
	if ((PINB>>0)&1){
		if ((PINB>>1)&1){
		jumpingCount=10;	
		}
	}
	refresh();
	}
	

	}
}

ISR(TIMER0_OVF_vect)
{
	if(gameOver==0){
	if(stage==1){
	refresh();
	TIFR0 |= (1<<TOV0);
	clockCounter++;
	
	if(clockCounter >= MAX_CLOCK_COUNTER_FOR_100MSECOND)
	{		
		jumpingCount--;
		explosionTime--;
	
		
		clear();
		globalCounter++;
		if(globalCounter==20){
			scoreCounter = scoreCounter+1;
			globalCounter=0;
		}
		
		for (int i=0; i<lives; i++){
		draw_character(' ', 4 ,(6 * (i+1)));
		draw_character('*', 4, (6 * i));
		}
				
		if(items[0] == 1){
		draw_character('o', 4 ,19);
		}
		else if(items[0] == 0){
		draw_character(' ', 4 ,19);
		}
		if(upgrade == 1){
		draw_character('|', 4 ,28);
		}
		else if(upgrade == 0){
		draw_character(' ', 4 ,28);
		}
		
		draw_line(14,0,14,47);
		draw_line(83,0,83,47);
		draw_line(14,0,83,0);
		draw_line(14,47,83,47);
		draw_pit();
		
		clockCounter = 0;
		
			if (lives <= 0){
				gameOver=1;
			}
			if (gameOverCount <= 0){
				gameOver=2;
			}
		}

		update_sprite(&sprite);
		update_weapon();
		update_bomb();
		
		for ( int i = 0; i < ZOMBIE_COUNT; i++ ) {
			pit_collision(&zombies[i]);
		}
 		
		z_stage_collision();
		hero_collision();
		stage_collision(&sprite);
		draw_sprite(&sprite);
		draw_sprite(&sword);
		draw_sprite(&bomb);
		draw_stage();
		cooldown--;
		
		update_zombies();
		
		check_collison();
		
		char score[15];
		sprintf(score, "%d", scoreCounter);
		draw_string(score, 0, 39);
		
		refresh();
	}
	}
}
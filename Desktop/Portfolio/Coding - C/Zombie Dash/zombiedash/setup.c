
#include <avr/io.h> 
#include <util/delay.h> 
#include <graphics.h>
#include <stdint.h>
#include <avr/interrupt.h>

#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"
#include "friendly_ports.h"
#include "setup.h"

volatile int stage = 0;
volatile int choice = 1;
volatile int chosen = 0;

void setup_teensy() {
	set_clock_speed( CPU_16MHz );
	LCDInitialise( LCD_DEFAULT_CONTRAST );
	clear();
}

int title_screen() {
	
stage = 0;
choice = 1;
chosen = 0;

	clear();
	draw_string( "Zombie", 25, 0 );
	draw_string( "Fear the Humans!", 0, 10 );
	draw_character('*',0,20);
	draw_string( "Easy", 6, 20 );
	draw_string( "Hard", 40, 20 );
	draw_string( "Eliot Wilson", 0, 30 );
	draw_string( "n9175504", 0, 40 );
	refresh();

	while(!chosen)
	{
	}
	clear();
	draw_string( "3", 40, 20 );
	refresh();
	_delay_ms( 1000 );
	clear();
	draw_string( "2", 40, 20 );
	refresh();
	_delay_ms( 1000 );
	clear();
	draw_string( "1", 40, 20 );
	refresh();
	_delay_ms( 1000 );
	stage = 1;
	return 0;
}
/* 			
void init()
{
	DDRB |= (1<<PB2)|(1<<PB3);	//LED0 and LED1 as outputs
	DDRB &= ~((1<<PB0)|(1<<PB1));	//Switch0 and Switch1 as input
	PORTB = 0x00; 	// Turn everything off to start with
	LCDInitialise( LCD_DEFAULT_CONTRAST );
	clear();
	refresh();
}		
			
void pin_change_init(void)
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

ISR(PCINT0_vect)
{
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
} */
#ifndef __SETUP__
#define __SETUP__

volatile int stage;
volatile int choice;
volatile int chosen;
void setup_teensy( void );
int title_screen( void );
void draw_boundary( void );

#endif
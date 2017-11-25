
//Decleration of Sound files
import processing.sound.*;

//Input and sound for Scare the Bear
Amplitude amp;
AudioIn in;
SoundFile growl;
SoundFile fright;

//Sound for Shave a Pigman
SoundFile clean;

//Sound for Rocket Can
SoundFile engine;
SoundFile launch;

// Decleration of classes
playerPointer playHand;
bearPlay bearHand;
groomTools groomHand;
Shaveable[] headHair = new Shaveable[7];
Shaveable[] moustacheHair = new Shaveable[7];
Shaveable[] noseHair = new Shaveable[2];
Shaveable[] lintShave = new Shaveable[13];
Shaveable cornShave;

//Decleration of Images
PImage pointer, logo, panel1, panel2, panel3, rocket, arm, map, instructions;
PFont condensed;

//Decleration of game 
int gameStage =0;
boolean rules = true;

void setup() {
  size(800, 600);
  noStroke();
  amp = new Amplitude(this);
  in = new AudioIn(this, 0);
  in.start();
  amp.input(in); 
  growl = new SoundFile(this, "growl.mp3");
  fright = new SoundFile(this, "fright.mp3");
  clean = new SoundFile(this, "clean.mp3");
  engine = new SoundFile(this, "engine.mp3");
  launch = new SoundFile(this, "launch.mp3");
  condensed = createFont("GILLUBCD.TTF", 150);
  pointer = loadImage("pointer.png");
  instructions = loadImage("instru.png");
  logo = loadImage("logo.png");
  panel1 = loadImage("panel1.png");
  panel2 = loadImage("panel2.png");
  panel3 = loadImage("panel3.png");
  rocket = loadImage("rocket.png");
  arm = loadImage("arm.png");
  map = loadImage("map.png");
  hair = loadImage("hair.png");
  nosehair = loadImage("nosehair.png");
  playHand = new playerPointer(width/2, height-(height/4), 6);
  bearHand = new bearPlay(color(255, 0, 0), 40, height-(height/3)-10, 3);

  groomSetup();

  textFont(condensed);
}
/*

 draw function calls other game functions based upon the int gameStage
 gameStage 0 calls main menu
 gameStage 1 calls Scare the Bear
 gameStage 2 calls Shave a Pig Man
 gameStage 3 calls Rocket Can
 */
void draw() {
  if (gameStage==0) {
    backgroundBoard(203, 193, 58);
    drawMenu();
    playHand.drive();
    playHand.display();
  }
  if (gameStage==1) {
    stageOneBackground();
    if (rules) {
      gameRules();
    }
    if (!rules) {
      bearGame();
    }
  }
  if (gameStage==2) {
    backgroundBoard(100, 100, 100);
    stageTwoBackground();
    if (rules) {
      gameRules();
    }
    if (!rules) {
      groomGame();
    }
  }
  if (gameStage==3) {
    stageThreeBackground();
    if (rules) {
      gameRules();
    }
    if (!rules) {
      rocketGame();
    }
  }
}
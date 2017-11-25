/*
Sound base retrieved from Public Domain.
 http://soundbible.com/1141-Comet.html
 
 Alterations and public use allowed.
 */

int count = 0;
int incricount = 0;
int increase=0;
int secondcrease=0;
int finalY=0;
float maxSpeed = 0;
float speed = 0;
boolean RgameComplete = false;

void rocketGame() {
  playHand.ypos=height-(height/6);
  textSize(12);
  rectMode(CENTER);
  countcheck();
  if (increase<16) {
    shakeRocket(width-(width/3), mouseY, pmouseX, pmouseY);
  }
  if (increase >= 16) {
    fill(165, 10, 63);
    rect(width/2, (height/2) -30, 500, 200);
    fill(255);
    if (maxSpeed < 900) {
      text("The rocket failed to launch", width/4, (height/2) - 80);
      text("Press R to restart", width/4, (height/2) - 60);
      fill(0);
      image(rocket, (width/2) + (width/6), finalY +(secondcrease)*5);
      if (keyPressed) {
        if (key =='r') {
          increase = -1;
          maxSpeed = 0;
          secondcrease = 0;
        }
      }
    }
    if (maxSpeed >= 900) {
      textSize(32);
      text("The Rocket Launched!", width/4, (height/2) - 80);
      textSize(12);
      text("Your Score:", width/4, (height/2) - 40);
      text(maxSpeed * 2, (width/4) + 70, (height/2) - 40);
      text("Press Q to quit", width/4, (height/2) - 20);
      fill(0);
      image(rocket, (width/2) + (width/6), height - 100 -(secondcrease)*10);      
      if (keyPressed) {
        if (key =='q') {
          RgameComplete = true;
          increase = -1;
          maxSpeed = 0;
          secondcrease = 0;
          gameStage = 0;
        }
      }
    }
  }
}

/*
Timer function incriments and counts 17 seconds for 15 seconds shake and 2 seconds delay before launch.
 If after the 17 seconds, the player has had a minimum mouse speed of 900, the launch noise is played.
 */
void countcheck() {
  incricount = second();
  if (increase < 17) {
    if (incricount > count) {
      increase++;
    }
  }
  if (increase >=17) {
    secondcrease++;
    if (secondcrease == 1) {
      if (maxSpeed >=900) {
        launch.play();
      }
    }
  }
  count = second();
}

/*
stageThreeBackground calls the background board draws the sidepanel seen in Rocket Can.
 Using the function countcheck, this function also draws a series of circles to represent the timer.
 */
void stageThreeBackground() {
  backgroundBoard(0, 40, 80);
  fill(46, 84, 20);
  rect(width/4, height - (30), width*2, 60);
  fill(68, 127, 30);
  rect(width/4, height - (50), width*2, 40);
  fill(180, 180, 180);
  rect(0, 0, width/2, height*2);
  fill(140, 140, 140);
  rect((width/4), 0, 50, height*2);
  rect((width/8)-10, (height - 80), 130, 50);
  fill(238, 255, 79);
  rect((width/4)-20, 0, 20, height*2);
  fill(255, 0, 0); 
  if (increase >= 2) {
    ellipse(width/10, 60, 30, 30);
  }
  if (increase >= 6) {
    ellipse(width/10, 100, 30, 30);
  }
  if (increase >= 10) {
    ellipse(width/10, 140, 30, 30);
  }
  if (increase >= 13) {
    fill(255, 129, 0); 
    ellipse(width/10, 180, 30, 30);
  }
  if (increase >= 14) {
    fill(255, 238, 54); 
    ellipse(width/10, 260, 50, 50);
  }
  if (increase >= 15) {
    fill(0, 255, 0); 
    ellipse(width/10, 350, 70, 70);
  }
}


void shakeRocket(int x, int y, int px, int py) {
  noStroke(); 
  if (speed == 0) {
    engine.play();
  }
  //calculates the speed of the mouse by comparing the mouses current position as opposed to its position in the previous frame.
  speed = abs(x-px) + abs(y-py); 
  if (speed> maxSpeed) {
    maxSpeed = speed;
  }
  //print statement used for bug testsing
  println(speed);
  fill(0); 
  image(rocket, x, y); 
  image(arm, x+(width/4) -30, y+5); 
  finalY=y;
}
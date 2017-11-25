/*
playerPointer class object. Class contains x and y co-ordinates as well as the movement speed.
 playerPointer uses collision detection to determine the value of int gameStage.
 */
class playerPointer {
  float xpos;
  float ypos;
  float xspeed;

  playerPointer(float tempXpos, float tempYpos, float tempXspeed) { 
    xpos = tempXpos;
    ypos = tempYpos;
    xspeed = tempXspeed;
  }

  void display() {
    fill(0);
    textSize(50);
    stroke(0);
    imageMode(CENTER);
    rectMode(CENTER);
    image(pointer, xpos, ypos);
  }
  void drive() {
    if (keyPressed) {
      if (key =='w') {
        ypos = ypos - xspeed;
      }
      if (key =='s') {
        ypos = ypos + xspeed;
      }
      if (key =='d') {
        xpos = xpos + xspeed;
      }
      if (key =='a') {
        xpos = xpos - xspeed;
      }
    }
    /*
    If object position is between areas specified below, then the variables for the corresponding game are reset and integer gameStage is changed. 
     */
    if (xpos >  (width/6) -50 && xpos < (width/6)+50) {
      if (ypos >  (height/2) -25 && ypos < (height/2) +25 ) {
        fill(255, 0, 0);
        rules = true;
        bearPoint = 400;
        increase = 0;
        bearStage=0;
        scared = false;
        gameStage=1;
      }
    } 
    if (xpos >  (width/2) -50 && xpos < (width/2)+50) {
      if (ypos >  (height/2) -25 && ypos < (height/2) +25 ) {
        fill(255, 0, 0);
        rules = true;
        gameStage=2;
      }
    } 
    if (xpos >  width-((width/6)) -50 && xpos < width-((width/6))+50) {
      if (ypos >  (height/2) -25 && ypos < (height/2) +25 ) {
        fill(255, 0, 0);
        rules = true;
        gameStage=3;
        speed = 0;
      }
    } 

    if (xpos > width) {
      xpos = 0;
    } else if (xpos < 0) {
      xpos = width;
    }
    if (ypos > height) {
      ypos = 0;
    }
    if (ypos < 0) {
      ypos = height;
    }
  }
}
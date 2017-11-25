/*
Sound retrieved from Public Domain
 
 http://soundbible.com/241-Bear-Growl-And-Roar.html
 
 Alterations and public use allowed.
 */
boolean scared = false;
int bearPoint = 400;
boolean soundPlay = true;
boolean SgameComplete = false;
int awake = 0;
int bearStage =0;
/*
 awake == 0 means asleep
 awake == 1 means awake
 awake == 2 means faking sleep
 */

int bearcount = 1;

/*
bearPlay class object. Class contains x and y co-ordinates as well as the movement speed.
 
 bearPlay is represented as a small red square.
 */
class bearPlay {
  color c;
  float xpos;
  float ypos;
  float xspeed;

  bearPlay(color tempC, float tempXpos, float tempYpos, float tempXspeed) { 
    c = tempC;
    xpos = tempXpos;
    ypos = tempYpos;
    xspeed = tempXspeed;
  }

  void display() {
    fill(0);
    textSize(50);
    stroke(0);
    fill(c);
    rectMode(CENTER);
    rect(xpos, ypos, 20, 20);
  }
  void update() {
    if (keyPressed) {
      if (key =='d') {
        xpos = xpos + xspeed;
      }
      if (key =='a') {
        xpos = xpos - xspeed;
      }
    }

    if (xpos > width) {
      xpos = xpos-xspeed;
    } else if (xpos < 0) {
      xpos = xpos+xspeed;
    }
    if (xpos>=(width-50)) {
      float scare = amp.analyze();
      scare = scare*1000;
      println(scare);
      if (scare > 30) {
        scared = true;
      }
      if (scared == true) {
        SgameComplete = true;
        if (bearStage == 0) {
          fright.play();
          bearStage = 1;
        }
        if (bearStage == 1) {
          fill(165, 10, 63);
          rect(width/2, (height/2) -30, 500, 200);
          fill(255);
          text("You Scared the Bear!", width/5, (height/2) - 60);
          textSize(12);
          text("What did he do to you?", width/4, (height/2)-20);
          text("Press Q to exit.", width/4, (height/2)-3);
          if (keyPressed) {
            if (key == 'q') {
              xpos = 40;
              gameStage=0;
            }
          }
        }
      }
    }
  }
  //Checks to see if the player is hidden.
  void checkHidden() {
    if (scared== false) {
      if (awake ==1 ||awake == 2) {
        if (!((xpos > 20  && xpos < 70) ||(xpos > (width/3)-20  && xpos < (width/3) +40 ) ||(xpos > (width-(width/6))-20  && xpos < (width-(width/6))+40))) {
          playerFound();
        }
      }
    }
  }
  //If the player is found, moves player x poisition and displays the corresponding UI and instructions.
  void playerFound() {
    xpos = -20;
    awake = 1;
    fill(165, 10, 63);
    rect(width/2, (height/2) -30, 500, 200);
    fill(255);
    text("He saw you!", width/4, (height/2) - 60);
    textSize(12);
    text("Be careful, the bear might not really be asleep.", width/4, (height/2)-20);
    text("Press Q to try again.", width/4, (height/2)-3);
    if (keyPressed) {
      if (key == 'q') {
        xpos = 40;
      }
    }
  }
}

/*
Incrimental time counter used to change global int "awake".
 
 */

void sleepCount() {
  incricount = second();
  if (incricount > count) {
    bearcount++;
  }
  count = second();
  if (scared== false) {
    if (awake == 1) {
      if (soundPlay == true) {
        growl.play();
        soundPlay = false;
      }
      if (bearcount >= 6) {
        awake = 2;
        bearcount = 0;
      }
    } 
    if (awake == 2) {
      soundPlay = true;
      if (bearcount >= 2) {
        awake = 0;
        bearcount = 0;
      }
    }
    if (awake == 0) {
      if (bearcount >= 3) {
        growl.play();
        bearcount = 0;
        awake = 1;
      }
    }
  }
}
/*
drawBear uses basic shapes to draw the bear in the background and gives visual identification of the bears "awake" status.
 If game is complete, the bear's position is incrimentally decreased to simulate bear running off stage scared.
 */
void drawBear() {
  fill(116, 38, 9);
  ellipse(bearPoint, height-(height/4), width/2, height/2);
  fill(166, 54, 13);
  ellipse((bearPoint)-width/8, height/3, 70, 70);
  ellipse((bearPoint)+width/8, height/3, 70, 70);
  fill(116, 38, 9);
  ellipse((bearPoint)-width/8, height/3, 40, 40);
  ellipse((bearPoint)+width/8, height/3, 40, 40);
  fill(166, 54, 13);
  ellipse(bearPoint, height/2, width/4, height/2);
  if (awake == 1) {
    fill(229, 229, 229);
    ellipse((bearPoint) -40, (height/3)+30, 30, 80);
    ellipse((bearPoint) +40, (height/3)+30, 30, 80);
    rect((bearPoint), (height/2)+30, 80, 10);
  }
  if (awake == 2) {
    fill(229, 229, 229);
    ellipse((bearPoint) -40, (height/3)+30, 35, 40);
    ellipse((bearPoint) +40, (height/3)+30, 35, 40);
    rect((bearPoint), (height/2)+30, 80, 10);
  }

  if (awake ==0) {
    fill(229, 229, 229);
    rect((bearPoint) -40, (height/3)+30, 30, 10);
    rect((bearPoint) +40, (height/3)+30, 30, 10);
    rect((bearPoint), (height/2)+30, 80, 10);
  }
  if (bearStage == 1) {
    bearPoint = bearPoint -2;
  }
}

/*
stageOneBackground calls the background board draws the base and hiding points for Scare the Bear.
 */
void stageOneBackground() {
  backgroundBoard(43, 13, 38);
  drawBear();
  noStroke();
  fill(237, 217, 241);
  rect(0, height-(height/6), 100000, height/3);
  fill(193, 177, 196);
  rect(40, height-(height/3)-30, 50, 60);
  rect(width/3, height-(height/3)-30, 60, 60);
  rect(width-(width/6), height-(height/3)-30, 60, 60);
  rect(width-50, height- 215, 5, 33);
  ellipse(width-50, height- 225, 10, 15);
}

void bearGame() {
  playHand.ypos=height-(height/6);
  sleepCount();
  bearHand.update();
  bearHand.display();
  bearHand.checkHidden();
}
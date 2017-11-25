PImage hair, nosehair;
int item = 1;
int shavepoints = 0;
boolean GgameComplete = false;
/*
Shaveable class objects. Class contains x and y co-ordinates as well as the fall speed of the object and a integer "type".
 Type correlates to the type of object shavable will be visually represented as in the display function.
 type = 1 == hair
 type = 2 == nosehair
 type = 3 == lint
 type = 4 == teethcorn
 */
class Shaveable {
  float xpos;
  float ypos;
  float speed;
  int type;
  boolean falling = false;

  Shaveable(float tempXpos, float tempYpos, float fallSpeed, int cleanType) { 
    xpos = tempXpos;
    ypos = tempYpos;
    speed = fallSpeed;
    type = cleanType;
  }

  void display() {
    if (type == 1) {
      image(hair, xpos, ypos);
    }
    if (type == 2) {
      image(nosehair, xpos, ypos);
    }
    if (type == 3) {
      fill(220);
      rect(xpos, ypos, 20, 5);
    }
    if (type == 4) {
      fill(236, 255, 12);
      rect(xpos, ypos, 15, 20);
    }
    if (type==5) {
      noStroke();
      fill(117, 67, 41);
      ellipse(xpos, ypos, 40, 20);
    }

    if ((item == 1 && (type == 1 || type ==2 || type ==5)) || (item ==2 && type == 4) || (item ==3 & type == 3) ) {
      if (((ypos >= groomHand.ypos -40) && (ypos <= groomHand.ypos -10)) && ((xpos >= groomHand.xpos -20) && (xpos <= groomHand.xpos +20))) {
        clean.play();
        falling =true;
        shavepoints++;
      }
    }
    if (falling ==true) {
      ypos = ypos + speed;
    }
  }
}

/*
groomTools class objects. Class contains x and y co-ordinates as well as the fall speed of the object and uses the global integer "item" to determing it's visual representation.
 The global integer was used to allow for collions to occur with this class object and the multiple other instances of objects in class type Shavable.
 item = 1 == razor
 item = 2 == toothbrush
 item = 3 == lint roller
 */
class groomTools {
  float xpos;
  float ypos;
  float speed;

  groomTools(float tempXpos, float tempYpos, float tempSpeed) { 
    xpos = tempXpos;
    ypos = tempYpos;
    speed = tempSpeed;
  }

  void display() {
    fill(0);
    textSize(50);
    stroke(0);
    imageMode(CENTER);
    rectMode(CENTER);
    if (item ==1) {
      fill(150, 150, 150);
      rect(xpos-10, ypos-10, 20, 50);
      fill(200, 200, 200);
      rect(xpos-10, ypos-25, 50, 20);
    }
    if (item ==2) {
      fill(240, 240, 240);
      rect(xpos, ypos-10, 20, 30);
      fill(68, 143, 153);
      rect(xpos-10, ypos, 10, 60);
    }
    if (item ==3) {
      fill(240, 240, 240);
      rect(xpos-15, ypos, 30, 15);
      fill(227, 44, 0);
      rect(xpos, ypos, 20, 60);
    }
  }
  void move() {
    if (keyPressed) {
      if (key =='w') {
        ypos = ypos - speed;
      }
      if (key =='s') {
        ypos = ypos + speed;
      }
      if (key =='d') {
        xpos = xpos + speed;
      }
      if (key =='a') {
        xpos = xpos - speed;
      }
      if (key == '1') {
        item = 1;
      }
      if (key == '2') {
        item = 2;
      }
      if (key == '3') {
        item = 3;
      }
      if (shavepoints > 1) {
        if (key == 'q') {
          GgameComplete = true;
          playHand.ypos=height-(height/6);
          gameStage=0;
          shavepoints = 0;
          groomSetup();
        }
        if (key == 'r') {
          xpos=30;
          shavepoints = 0;
          groomSetup();
        }
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

/*stageTwoBackground function inserts the pigman and instrcution images int the background 
 */
void stageTwoBackground() {
  image(map, width/2, height/2);
  image(instructions, 125, height/3);
}

void groomGame() {
  fill(255);
  textSize(20);
  if (shavepoints> 1) {
    text("Press Q to Finish", width-200, 40);
    text("Press R to Restart", width-200, 80);
  }
  groomHand.move();
  groomHand.display();
  cornShave.display();
  for (int i = 1; i < 7; i++) {
    headHair[i].display();
  }
  for (int i = 1; i < 7; i++) {
    moustacheHair[i].display();
  }
  for (int i = 0; i < 2; i++) {
    noseHair[i].display();
  }
  for (int i = 0; i < 12; i++) {
    lintShave[i].display();
  }
}

/*groomSetup declares all the objects required for Shave a Pigman.
 Including, tools and shaveable objects
 */
void groomSetup() {
  groomHand = new groomTools(width/8, height/8, 6);
  cornShave = new Shaveable((width/2) - 20, height - (height/3) - 20, 7, 4);
  for (int i = 1; i < 7; i++) {
    headHair[i] = new Shaveable((width/3) + 30+(i* 40), (height/8)+20, 7, 1);
  }
  for (int i = 1; i < 7; i++) {
    moustacheHair[i] = new Shaveable((width/2) -60 +(i* 20), (height/2) + 20, 7, 5);
  }
  for (int i = 0; i < 2; i++) {
    noseHair[i] = new Shaveable(((width/2) - 30) +(i* 70), height/2, 7, 2);
  }
  for (int i = 0; i < 12; i++) {
    lintShave[i] = new Shaveable(((width/8)+50) +random(550), height -(height/6) - (i*random(10)), 7, 3);
  }
}
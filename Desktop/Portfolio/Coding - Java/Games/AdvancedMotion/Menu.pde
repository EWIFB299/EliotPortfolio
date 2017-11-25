int boxsize =150;

/*
backgroundBoard draws a checkboard pattern across the screen with
 colours based off the r,g,b input.
 */
void backgroundBoard(int red, int green, int blue) {
  for (int i = 0; i < width+20; i += 50) { 
    for (int j = 0; j < height+20; j += 50) {  
      if ((i+j) % 20 ==0) {   
        fill(red+31, green+31, blue+50);
      } else {  
        fill(red, green, blue);
      }
      rect (i, j, 50, 50);
    }
  }
} 

/*
drawMenu draws the user interface and instructions at the beggining of the game depending on the int gameStage 
 */
void drawMenu() {
  strokeWeight(10);
  stroke(73, 73, 73);
  textSize(20);
  fill(0);
  text("Please Keep Capslock Off!", (width/2) - 120, (height)-height/8);
  text("Use WASD to move pointer", (width/2) - 125, (height)-height/12);
  fill(0, 104, 56);
  textSize(64);
  text("Alternative", 250, (height/4)-70);
  noFill();
  image(logo, 400, height/4);
  image(panel1, width/6, height/2);
  rect(width/6, height/2, boxsize, boxsize);
  image(panel3, width/2, height/2);
  rect(width/2, height/2, boxsize, boxsize);
  image(panel2, (width -(width/6)), height/2);
  rect(width -(width/6), height/2, boxsize, boxsize);
  noStroke();
  strokeWeight(0);
}

void gameRules() {
  textSize(13);
  if (gameStage ==1) {
    fill(250, 250, 250);
    rect((width/2)-30, (height/2) -130, 530, 230);
    fill(165, 10, 63);
    rect(width/2, (height/2) -30, 500, 200);
    fill(255);
    text("Get to the speaker at the right and scare the bear!", width/4, (height/2) - 80);
    text("Use the A and D keys to move left and right and your voice to scare.", width/4, (height/2) - 40);
    text("But be sure to avoid the gaze of the bear, he can be tricky!", width/4, (height/2)-20);
    text("Wait until his eyes are fully closed", width/4, (height/2)-3);
    text("Press the Q key to play!", width/4, (height/2)+30);
    fill(0);
    textSize(60);
    text("Scare the Bear!", width/6, (height/2) -150);
  }
  if (gameStage ==2) {
    fill(250, 250, 250);
    rect((width/2)-30, (height/2) -130, 530, 230);
    fill(165, 10, 63);
    rect(width/2, (height/2) -30, 500, 200);
    fill(255);
    text("Be the envy of all your friends and shave a pig man!", width/4, (height/2) - 80);
    text("Use the different tools at your disposal to make him clean.", width/4, (height/2) - 60);
    text("Use the WASD keys to move the tools and 1, 2 and 3 to select your tools.", width/4, (height/2)-40);
    text("Shave him as much as you want!", width/4, (height/2)-20);
    text("Press Q to start!", width/4, (height/2)+20);
    fill(0);
    textSize(60);
    text("Shave a Pig Man!", width/6, (height/2) -150);
  }
  if (gameStage ==3) {
    fill(250, 250, 250);
    rect((width/2)-30, (height/2) -130, 530, 230);
    fill(165, 10, 63);
    rect(width/2, (height/2) -30, 500, 200);
    fill(255);
    text("Shake to the moon!", width/4, (height/2) - 80);
    text("Use the mouse to shake the rocket and blast off!", width/4, (height/2) - 40);
    text("You only have 15 seconds to shake", width/4, (height/2)-20);
    text("Press the Q key to play!", width/4, (height/2)+20);
    fill(0);
    textSize(60);
    text("Rocket Can", width/4, (height/2) -150);
  }
  if (keyPressed) {
    if (key=='q') {
      rules = false;
    }
  }
}
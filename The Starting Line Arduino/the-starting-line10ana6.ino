//The Sarting Line
//by Lauren Race and Terrick Gutierrez
//november 16th 2017
// updated Dec 5
//there is one moderator that can initialize, update question, and finalize
//there are two players, each one with a mat, each mat with a yes/no state

//at first, the state is idle
//when the moderator button is pressed, the game starts, isStarted = true;

//when all the questions are answered, the game is over, isOver = false;

//has the game started
boolean isStarted = false;
//is the game over
boolean isOver = false;
int player1ans = 0; //1 is yes and 2 is no
int player2ans = 0; //1 is yes and 2 is no

// questions
int currentQuestion = 0;
int numberOfQuestions = 10;

//2 players, each one with yes and no
//first pair are yes and no buttons for player0
//second pair are yes and no buttons for player1
//at first no button is pressed, so everything is false
boolean answers[]  = {false, false, false, false};
int numberOfAnswers = 4;

//physical side, TODO: confirm that these are the actual pins
//pin2 connected to yes / player0
//pin3 connected to  no / player0
//pin4 connected to yes / player1
//pin5 connected to no / player1
//pin6 connected to moderatorButton
int pinReading = 6;
int numberOfPins = 4;
int pinReading1[] = {A5, A4, A3, A2};

//it stores the current answers for the question
//it starts at 0, because at first no one has answered
//it goes to 1, when anyone answers
//it goes to 2 when both participants answer
//when it reaches 2, we send info to p5 and we reset the humber to 0
int answersPerQuestion = 0;

//button that the moderator has
//it is false if not pressed
//it is true if it is pressed
boolean moderatorButton = false;

//int for number of yes and scores
//for each player, player0 and player1
int yes[] = {0, 0};
int numberOfYes = 2;
int scores[] = {0, 0};
int scoreMultiplier = 10;


long int lastSent;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  setupPins();
  lastSent = millis();
}

void loop() {
  if (answers[0] || answers[1] || answers[2] || answers[3]) {


    Serial.print (answers[0]);
    Serial.print (',');
    Serial.print (answers[1]);
    Serial.print (',');
    Serial.print (answers[2]);
    Serial.print (',');
    Serial.println (answers[3]);
  }

  //check answers from players and button from moderator
  //if(millis() - lastSent > 5000){
  checkButtons();
  //  }

  ///check if continue to next question
  updateQuestion();
}

//setting up digital pins to be read
void setupPins() {
  for (int i = 0; i < numberOfPins; i++) {
    pinMode(pinReading1[i], INPUT);
  }
}

void checkButtons() {

  //read all of the pins to detect the answers
  for (int i = 0; i < numberOfAnswers; i++) {
    //make the answer true if the corresponding button is pressed
    //Serial.println(analogRead(pinReading1[i]));
    if (analogRead(pinReading1[i]) > 700) {
      //Serial.print("PRESSED");
      //Serial.println(i);

      //this button was pressed
      answers[i] = true;
    }
  }

  if (answers[0]) {
    player1ans = 1;
  }
  else if (answers[1]) {
    player1ans = 2;
  }
  if (answers[2]) {
    player2ans = 1;
  }
  else if (answers[3]) {
    player2ans = 2;
  }


  //read the moderator button
  //CAUTION: pinReading.length is 5, answers is 4
  //because we are storing the last pin reading in moderatorButton
  //so that answers from players are in an array and moderatorButton is a loner boolean
  if (digitalRead(pinReading) == HIGH) {
    moderatorButton = true;

    Serial.print(player1ans);
    Serial.print(',');
    Serial.println(player2ans);
    player1ans = 0;
    player2ans = 0;
    answers[3] = false;
    answers[2] = false;
    answers[1] = false;
    answers[0] = false;

    lastSent = millis();

  } else {
    moderatorButton = false;
  }



  //reset answersPerQuestion
  answersPerQuestion = 0;

  //update answersPerQuestion
  for (int i = 0; i < numberOfAnswers; i++) {
    //for every true answer, add 1 to answersPerQuestion
    // Serial.println("counting answers");
    if (answers[i] == true) {
      //  Serial.print("updating answersPerQuestion ");
      answersPerQuestion = answersPerQuestion + 1;
    }
  }
}

//check if we need to move the next question
void updateQuestion() {
  //if both participants answered AND the moderator pressed the button, move to next question
  if (answersPerQuestion == 2 && moderatorButton) {
    currentQuestion = currentQuestion + 1;

    //update the current score according to the answers from the current question
    updateScores();

    //reset the answers
    for (int i = 0; i < numberOfAnswers; i++) {
      answers[i] = false;
    }
  }
}


//function for updating scores everytime we go to the next question
void updateScores() {

  //check yes for every player
  //check first player
  if (answers[0]) {
    //increment yes
    yes[0]++;
  }

  //skip answers[1]
  //because it is player0 no

  //check second player
  if (answers[2]) {
    //increment yes
    yes[1]++;
  }

  //skip answers[3]
  //because it is player1 no

  //actually update scores
  //according to yes[]
  for (int i = 0; i < numberOfYes; i++) {
    //calculate corresponding score
    scores[i] = yes[i] * scoreMultiplier;

  }
}

// The Starting Line Game
// By Lauren Race and Terrick Gutierrez
// runs on p5.js, tested on the alpha editor, chrome, macbook
// November 2017
// with array for images
// with serial
// with images changing as moderator button is pressed

// red value #e50022

//add "Yes" and/or "No" on the screen after ppl answer


let serial;
let portName = '/dev/cu.usbmodem1411';

let noOfQuestions = 10;
let currentQuestion = 1;
let score = [0, 0];

let timeNow = 0;
let timePressed = 0;
let img = [];
let imageIndex = 0;

let percentage1 = 0;
let percentage2 = 0;

let myFont;



// preload the imgages (img[0] is not working... make sure to debug)
function preload() {
  img[0] = loadImage("TSL/SL0.png");
  img[1] = loadImage("TSL/SL1.png");
  img[2] = loadImage("TSL/SL2.png");
  img[3] = loadImage("TSL/SL3.png");
  img[4] = loadImage("TSL/SL4.png");
  img[5] = loadImage("TSL/SL5.png");
  img[6] = loadImage("TSL/SL6.png");
  img[7] = loadImage("TSL/SL7.png");
  img[8] = loadImage("TSL/SL8.png");
  img[9] = loadImage("TSL/SL9.png");
  img[10] = loadImage("TSL/SL10.png");
  img[11] = loadImage("TSL/SL11.png");
  myFont = loadFont('RobotoMono-Bold.ttf');
}


function setup() {
  createCanvas(windowWidth, windowHeight);
  serial = new p5.SerialPort(); // make a new instance of the serialport library
  serial.open(portName); // open a serial port
  serial.on('data', serialEvent); // callback for when new data arrives

}


function draw() {
  background(220);


  var auxHeight = height;
  print(auxHeight);
  var headerRatio = 3000 / 1688;
  // var headerRatio = ;
  image(img[imageIndex], 0, 0, auxHeight * headerRatio, auxHeight);
  textFont(myFont);
  textSize(250);
  textAlign(CENTER);
  if (imageIndex > 10) {
    fill('#e50022');
    text(percentage1 + '%', windowWidth * 1 / 4, windowHeight * 2 / 7);
     fill('#1c4587');
    text(percentage2 + '%', windowWidth * 3 / 4, windowHeight * 2 / 7);
  }
  noStroke();
  textAlign(LEFT);
  fill(255);
  
  if (imageIndex <= 10) {
      
    rect(windowWidth/16 - 13, windowHeight * 3/5 +2, percentage1 * 5, 21);
    rect(windowWidth * 9/16 - 85 , windowHeight * 3/5 +2, percentage2 * 5, 21);
  }
}

function serialEvent() {
  var data = serial.readLine();
 
  if (data.length > 0) {
    data = data.split(',');
    
    if(data.length==2) {
      timeNow = new Date().getTime();
      if (timeNow - timePressed > 1000) {


        calculateScore(data);
        timePressed = new Date().getTime();
      }
    }
  }
}

function calculateScore(data) {
  if (data[0] == 1)
    score[0]++;


  if (data[1] == 1)
    score[1]++;
  console.log(score);
  currentQuestion++;
  imageIndex++;
  if (imageIndex > 11) {
    imageIndex = 0;
    score[0] = 0;
    score[1] = 0;

  }


  // if we are on imageIndex 11 print percentage at this location for both players
  percentage1 = score[0] * 10;
  percentage2 = score[1] * 10;
}
//for resizing the canvas when window is resized
function windowResized() {
  resizeCanvas(windowWidth, windowHeight);

}
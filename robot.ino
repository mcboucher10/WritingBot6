#include <Servo.h>
/*
  Writing Robot Arduino Code
   This program controls a small robot that can draw letters
  on paper using two DC motors (to move and turn) 
  and one servo motor (to lift and lower a marker)
*/

Servo myservo;

// wiring - each motor uses one PWM pin (speed) and two direction pins.
// Motor 1
int motor1Speed = 3;
int motor1D1 = 4;
int motor1D2 = 5;

// Motor 1
int motor2Speed = 11;
int motor2D2 = 8;
int motor2D1 = 7;

int servoPin = 10;

// speed values that seemed to minimize the error within our turns
int speed1 = 100;
int speed2 = 120;

// initial servo orientation (penup), marker on servo is off the ground & to the side
int pos = 40;

/* The index "i" represents how far to move.
when the robot is told to move forward "i" units or backwards "i" units,
it looks up the time value at index i and runs the motors for that long.*/
// note: index 0 is mapped to a small value used for fine adjustment & small movements, not 0 units
//forward movement times (miliseconds)
float fdistances[7] = {75,150,240,320,425,450,550};
//backward movement times (miliseconds)
float bdistances[7] = {75,110,225,300,375,425,525};

// The index i represents how many 45-degree steps to turn.
// i = 0, 0 degrees 
// i = 1, 45 degrees
// i = 2,  90 degrees
// i = 3, 135 degrees
// i = 4,  180 degrees
//each value is the number of milliseconds the motors should run to turn that angle
//left turn times (miliseconds)
int lefts[5] = {0,255,430,610,785};
//right turn times (miliseconds)
int rights[5] = {0,250,415,600,810};

// index i corresponds to a turn of 45 * i degrees.
// pre-offsets move the robot forward slightly before a 45 * i degree turn.
// -1 means no adjustment; 0 or higher means move forward that many small units.
int lpreoffsets[5] = {-1,1,1,-1,-1};
int rpreoffsets[5] = {-1,1,1,-1,-1};

// pndex i corresponds to a turn of 45 * i degrees.
// post-offsets move the robot forward slightly after a 45 * i degree turn.
// -1 means no adjustment; 0 or higher means move forward that many small units.
int lpostoffsets[5] = {-1,-1,0,-1,-1};
int rpostoffsets[5] = {-1,-1,0,-1,-1};

/*
We describe each letter as a set of commands, each 2 characters long

The first character is the TYPE of command:
    F = Forward while drawing (pendown)
    U = Forward travel move (penup)
    B = Backward while drawing (pendown)
    A = Backward travel move (penup)
    L = Turn Left (penup)
    R = Turn Right (penup)

The second character is the STRENGTH of the command (e.g. 1 unit, 2 * 45 degrees)
    - for F, U, B, A commands, the strength is an index into fdistances[] or bdistances[]
      (so it controls how long to drive the motors, which controls distance).
    - for L and R commands, the strength is an index into lefts[] or rights[]
      and also means 45 * strength degrees of a turn.
*/
String letters[27] = {
    // a
    "L2U4R2F3R2F4R2F3R2F2R2F3R2U2L2U1",
    // b
    "L2F5A2R2F3R2F3R2F3L2L2U4",
    // c
    "U3L2U3L2F3L2F3L2F3U1",
    // d
    "L2U4R2U3R2F4R2F3R2F2R2F3R2U2L2U1",
    // e
    "L2U2R2F3L2F1L2F3L2F3L2F3U1",
    // f
    "L2F5R2F3A3R2U2L2F2R2U3L2U2",
    // g
    "R2U2L2F2L2F4L2F2L2F2L2F2U2",
    // h
    "L2F5A2R2F3R2F3L2U1",
    // i
    "L2F3U1F0A4R2U1",
    // j
    "R2U1F1L2F2L2F3U1F0A3R2U1",
    // k
    "L2F4A3R1F1A1R2F1A1R1U1L2U2",
    // l
    "L2F5A5R2U1",
    // m
    "L2F3R2F1R2F2A2L2F1R2F3L2U1",
    // n
    "L2F3R2F3R2F3L2U1",
    // o
    "F3L2F3L2F3L2F3L2U4",
    // p
    "L2B2U2F3R2F3R2F3L2B3U4",
    // q
    "L2F3R2F3R2F5A2L2B3U4",
    // r
    "L2F3R2F3R2F1U2L2U1",
    // s
    "F2L2F1L2F2R2F1R2F2R2U2L2U1",
    // t
    "L2U2R2F2A1L2F1A1B2R2U2",
    // u
    "L2F3R2U3R2F3L2B3U4",
    // v
    "L2U2R2R1F2L2F2R1R2U2L2U1",
    // w
    "L2F3A3R2F1L2F1A1R2F1L2F3A3R2U1",
    // x
    "L1F4A2R2B2U2F2L1U1",
    // y
    "R2U2L2F2L2F4L2U2L2F2L2F2U2",
    // z
    "L2U2R2F2L1B3R1F2U1"
    };

void setup() {
    myservo.attach(servoPin); //connect the servo to its pin so we can control the marker
    myservo.write(pos); // move servo to initial position

    // sets all motor control pins as outputs
  //motor 1
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor1D1, OUTPUT);
    pinMode(motor1D2, OUTPUT);

  //motor 2
    pinMode(motor2Speed, OUTPUT);
    pinMode(motor2D1, OUTPUT);
    pinMode(motor2D2, OUTPUT);
}

void loop() {
  // use commands like write_letter() or write_word() in the loop
  write_word("mnopqrstuwy");
  while(1); // stop the program
}

// move the robot forward [strength] units
// the actual distance is controlled by a timed delay (miliseconds)
void forward(int strength) {
  // setting motor directions so both wheels move forward
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);
  
// run the motors for a calibrated amount of miliseconds
  delay(fdistances[strength]);

  stop();
}

// move the robot backward [strength] units
void backward(int strength) {
   // set motor directions so both wheels move backward
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, HIGH);
  digitalWrite(motor2D2, LOW);

  // run the motors for a calibrated amount of miliseconds
  delay(bdistances[strength]);

  stop();
}

// stop the robot & and waits so it does not drift
void stop() {
  // stop motor 1
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, LOW);
  
 // stop motor 2
  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, LOW);

  // pause for 500 miliseconds to allow the robot to fully stop
  delay(500);
}

// turn the robot left [strength * 45] degrees
void left(int strength) {
  if (lpreoffsets[strength] == -2) {
    //move backward slightly
    backward(0);
  } else {
    // normal case, move forward slightly before turning
    forward(lpreoffsets[strength]);
  }
  
  // set motor directions so the robot turns left
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  // turn for a calibrated amount of miliseconds
  // lefts[strength] is associated to 45 × strength degrees
  delay(lefts[strength]);

  stop();

  // apply a small adjustment forward after the turn
  forward(lpostoffsets[strength]);
}

// turn the robot right [strength * 45] degrees
void right(int strength) {
  if (strength != -1) {
    // apply a small forward adjustment before the turn
    forward(rpreoffsets[strength]);

    // Set motor directions so the robot turns right
    //motor 1
    analogWrite(motor1Speed, speed1);
    digitalWrite(motor1D1, LOW);
    digitalWrite(motor1D2, HIGH);

    //motor 2 
    analogWrite(motor2Speed, speed2);
    digitalWrite(motor2D1, HIGH);
    digitalWrite(motor2D2, LOW);

    // turn for a calibrated amount of miliseconds
    delay(rights[strength]);

    stop();

    // apply a small correction forward after the turn
    forward(rpostoffsets[strength]);
  }
}

// raise the pen off the paper
void penup() {
  for (pos = pos; pos <= 40; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(100);
}

// lower the pen onto the paper
void pendown() {
  for (pos = pos; pos >= 10; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(100);
}

// given a letter, parse the command and execute the correct functions
void write_letter(char letter) {

    // convert the letter into an index
    //  'a' -> 0, 'b' ->1, ..., 'z' -> 25
    String movement_string = letters[letter - 'a'];

  // read the movement string two characters at a time
    // each pair is one command: [type][strength]
    for (int i = 0; i < movement_string.length(); i += 2) {

      // extract  one command (2 characters)
      String step = movement_string.substring(i, i+2);

      // convert the strength character (0 to 9) into a number
      int strength = step.charAt(1) - '0';

      // execute the command based on its type
      if (step.charAt(0) == 'L') {
        left(strength);
        
      } else if (step.charAt(0) == 'R') {
        right(strength);
        
      } else if (step.charAt(0) == 'F') {
        // draw forward pen down while moving
        pendown();
        forward(strength);
        penup();
        
      } else if (step.charAt(0) == 'U') {
        // move forward without drawing
        forward(strength);
        
      } else if (step.charAt(0) == 'B') {
        // draw backward: pen down while moving
        pendown();
        backward(strength);
        penup();
        
      } else if (step.charAt(0) == 'A') {
        // move backward without drawing
        backward(strength);
      }
    }
}

// given a word, write it letter by letter
void write_word(String word) {
  // loop through each character in the word
  for (int i = 0; i < strlen(word); i++) {
    write_letter(word.charAt(i));
  }
}

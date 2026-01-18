#include <Servo.h>

Servo myservo;

// wiring
int motor1Speed = 3;
int motor1D1 = 4;
int motor1D2 = 5;

int motor2Speed = 11;
int motor2D2 = 8;
int motor2D1 = 7;

int servoPin = 10;

// speed values that seemed to minimize the error within our turns
int speed1 = 100;
int speed2 = 120;

// initial servo orientation (penup)
int pos = 40;

// for an index i, to go forward/backward i units, move for x ms
// note: index 0 is mapped to a small adjustment, not 0 units
float fdistances[7] = {75,150,240,320,425,450,550};
float bdistances[7] = {75,110,225,300,375,425,525};

// for an index i, to turn 45 * i degrees, move for x ms
int lefts[5] = {0,255,430,610,785};
int rights[5] = {0,250,415,600,810};

// for an index i, to turn 45 * i degrees, account for turn error by moving forward x units before the turn
// note: -1 is used to indicate no adjustment, as forward(0) is a small correction
int lpreoffsets[5] = {-1,1,1,-1,-1};
int rpreoffsets[5] = {-1,1,1,-1,-1};

// for an index i, to turn 45 * i degrees, account for turn error by moving forward x units after the turn
// note: -1 is used to indicate no adjustment, as forward(0) is a small correction
int lpostoffsets[5] = {-1,-1,0,-1,-1};
int rpostoffsets[5] = {-1,-1,0,-1,-1};

/*
We describe each letter as a set of commands, each 2 characters long

The first character is the TYPE of command:
  F: Forward (pendown)
  U: Forward (penup)
  B: Backward (pendown)
  A: Backward (penup)
  L: Left (penup)
  R: Right (penup)

The second character is the STRENGTH of the command (e.g. 1 unit, 2 * 45 degrees)
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
    myservo.attach(servoPin); // connect to servo
    myservo.write(pos); // move servo to initial position

    // setup to motor pins
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor1D1, OUTPUT);
    pinMode(motor1D2, OUTPUT);
    
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
void forward(int strength) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  delay(fdistances[strength]);

  stop();
}

// move the robot backward [strength] units
void backward(int strength) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, HIGH);
  digitalWrite(motor2D2, LOW);

  delay(bdistances[strength]);

  stop();
}

// stop the robot
void stop() {
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, LOW);

  delay(500);
}

// turn the robot left [strength * 45] degrees
void left(int strength) {
  if (lpreoffsets[strength] == -2) {
    backward(0);
  } else {
    forward(lpreoffsets[strength]);
  }

  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);
  
  delay(lefts[strength]);

  stop();
  forward(lpostoffsets[strength]);
}

// turn the robot right [strength * 45] degrees
void right(int strength) {
  if (strength != -1) {
    forward(rpreoffsets[strength]);

    analogWrite(motor1Speed, speed1);
    digitalWrite(motor1D1, LOW);
    digitalWrite(motor1D2, HIGH);

    analogWrite(motor2Speed, speed2);
    digitalWrite(motor2D1, HIGH);
    digitalWrite(motor2D2, LOW);

    delay(rights[strength]);

    stop();

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
    String movement_string = letters[letter - 'a'];
    for (int i = 0; i < movement_string.length(); i += 2) {
      String step = movement_string.substring(i, i+2);
      int strength = step.charAt(1) - '0';
      if (step.charAt(0) == 'L') {
        left(strength);
      } else if (step.charAt(0) == 'R') {
        right(strength);
      } else if (step.charAt(0) == 'F') {
        pendown();
        forward(strength);
        penup();
      } else if (step.charAt(0) == 'U') {
        forward(strength);
      } else if (step.charAt(0) == 'B') {
        pendown();
        backward(strength);
        penup();
      } else if (step.charAt(0) == 'A') {
        backward(strength);
      }
    }
}

// given a word, write it letter by letter
void write_word(String word) {
  for (int i = 0; i < strlen(word); i++) {
    write_letter(word.charAt(i));
  }
}

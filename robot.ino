#include <Servo.h>

Servo myservo;

int motor1Speed = 3;
int motor1D1 = 4;
int motor1D2 = 5;

int motor2Speed = 11;
int motor2D2 = 8;
int motor2D1 = 7;
int speed1 = 100;
int speed2 = 120;

int scale = 100;

float pi = 3.14159;

int pos = 40;

float fdistances[7] = {0.75,1.5,2.4,3.2,4.25,4.5,5.5};
float bdistances[7] = {0.75,1.1,2.25,3,3.75,4.25,5.25};
int lefts[5] = {0,255,430,610,785};
int rights[5] = {0,250,415,600,810};
int lpreoffsets[5] = {-1,1,1,-1,-1};
int rpreoffsets[5] = {-1,1,1,-1,-1};
int lpostoffsets[5] = {-1,-1,0,-1,-1};
int rpostoffsets[5] = {-1,-1,0,-1,-1};

/*
Fx - Forward x units
P0 - Penup
P1 - Pendown
Dx - Forward xsqrt(2) units
Rx - Right 45x degrees
Lx - Left 45x degrees
Ux - Forward x units (penup)
Ax - Backward x units (penup)
Cx - Backward xsqrt(2) units (penup)
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
    myservo.attach(10);
    myservo.write(pos);
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor1D1, OUTPUT);
    pinMode(motor1D2, OUTPUT);
    
    pinMode(motor2Speed, OUTPUT);
    pinMode(motor2D1, OUTPUT);
    pinMode(motor2D2, OUTPUT);
}

void loop() {
  write_word("mnopqrstuwy");
  while(1);
}

void forward(int strength) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  delay(fdistances[strength] * scale);

  stop();
}

void backward(int strength) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, HIGH);
  digitalWrite(motor2D2, LOW);

  delay(bdistances[strength] * scale);

  stop();
}

void stop() {
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, LOW);

  delay(500);
}

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

void penup() {
  for (pos = pos; pos <= 40; pos += 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(100);
}

void pendown() {
  for (pos = pos; pos >= 10; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  delay(100);
}

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

void write_word(String word) {
  for (int i = 0; i < strlen(word); i++) {
    write_letter(word.charAt(i));
  }
}

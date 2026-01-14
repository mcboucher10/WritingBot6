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
    "L2F3R2F3R2F5A1L2B4U5",
    // b
    "L2F5A2R2F3R2F3R2F3L2L2U5",
    // c
    "U3L2U3L2F3L2F3L2F3U2",
    // d
    "L2F3R2F3L2F2B5L2F3R2R2U5",
    // e
    "U1L2U1R2F1L2F1L2F3L2F3L2F3U2",
    // f
    "L2F5R2F3A3R2F2L2F2A2R2U3L2U5",
    // g
    "F3A3L2F3R2F3R2F5R2F3R2U3R2U5",
    // h
    "R2F5A3R2F3R2F3L2U2",
    // i
    "L2F3U1F0A4R2U2",
    // j
    "L2F1A1R2F3L2F3U1F0A4R2U2",
    // k
    "L2F5A4R1D2C2R2D2L1U2",
    // l
    "L2F5A5R2U2",
    // m
    "L2F3R2F1R2F2A2L2F1R2F3L2U2",
    // n
    "L2F3R2F3R2F3L2U2",
    // o
    "F3L2F3L2F3L2F3L2U5",
    // p
    "F3L2F3L2F3L2F5A2L2U5",
    // q
    "L2F3R2F3R2F5A2L2B3U5",
    // r
    "L2F3R2F3R2U3L2U2",
    // s
    "F3L2F1L2F3R2F1R2F3R2U3L2U2",
    // t
    "L2U2R2F2A1L2F1B3R2U3",
    // u
    "F3L2F3L2U3L2F3L2U5",
    // v
    "L2U1R2R1D1L2D1R2U1L2U2",
    // w
    "L2F3A3R2F1L2F2A2R2F1L2F3A3R2U2",
    // x
    "L1D"
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
  pendown();
  forward(1);
  penup();
  forward(2);
  pendown();
  forward(3);
  pendown();
  forward(5);
  penup();
  forward(6);
  delay(1000);
}

float distances[7] = {0,1.5,2.25,3,3.5,4.5,5.25};

void forward(float distance) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  if (int(distance) == distance) {
    delay(distances[int(distance)] * scale);
  } else {
    delay(distance * scale);
  }

  stop();
}

void diagonal(float distance) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  if (int(distance) == distance) {
    delay(distances[int(distance)] * 1.41 * scale);
  } else {
    delay(distance * 1.41 * scale);
  }

  stop();
}

void backward(float distance) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, HIGH);
  digitalWrite(motor2D2, LOW);

  if (int(distance) == distance) {
    delay((distances[int(distance)]- 0.5) * scale);
  } else {
    delay(distance * scale);
  }

  stop();
}

void stop() {
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, LOW);
}

void left(float theta) {
  forward(1);
  delay(500);
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);
  
  if (theta == pi / 4) {
    delay(255);
  }
  else if (theta == pi / 2) {
    delay(425);
  }
  else if (theta == pi) {
    delay(785); 
  } else {
    delay(theta);
  }

  stop();
}

void right(float theta) {
  forward(2);
  delay(500);
  analogWrite(motor1Speed, speed1);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, speed2);
  digitalWrite(motor2D1, HIGH);
  digitalWrite(motor2D2, LOW);

  if (theta == pi / 4) {
    delay(250);
  }
  else if (theta == pi / 2) {
    delay(385);
  }
  else if (theta == pi) {
    delay(810);
  } else {
    delay(theta);
  }

  stop();
  forward(1);
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
        left(pi / 4 * strength);
      } else if (step.charAt(0) == 'R') {
        right(pi / 4 * strength);
      } else if (step.charAt(0) == 'F') {
        pendown();
        forward(strength);
        penup();
      } else if (step.charAt(0) == 'D') {
        pendown();
        forward(1.41 * strength);
        penup();
      } else if (step.charAt(0) == 'U') {
        forward(strength);
      } else if (step.charAt(0) == 'B') {
        pendown();
        backward(strength);
        penup();
      } else if (step.charAt(0) == 'A') {
        backward(strength);
      } else if (step.charAt(0) == 'C') {
        forward(1.41 * strength);
      }
      delay(1000);
    }
}

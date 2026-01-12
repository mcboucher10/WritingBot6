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
*/

String letters[27] = {
    "L2F4R2F4L2F2L2F4L2F2L2U3R2F4L2U2",
    "L2F6R2F3R2F3R2F3B5L2F3R2F5L2L2U6",
    "F3L2L2U3R2F4R2F3R2U4L2U2"};

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
  /*left(pi / 2);
  pendown();
  forward(4);
  penup();
  right(pi / 2);
  pendown();
  forward(4);
  penup();
  left(pi / 2);
  pendown();
  forward(2);
  penup();
  left(pi / 2);
  pendown();
  forward(4);
  penup();
  left(pi / 2);
  pendown();
  forward(2);
  penup();
  left(pi / 2);
  delay(500);
  forward(4);
  delay(500);
  right(390);
  pendown();
  forward(4);
  penup();
  left(pi / 2);
  forward(1);*/
  write_letter('B');
  delay(1000);
}

void forward(float distance) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  int distances[7] = {0,1.5,2.25,3,3.5,4.5,5.25};
  if (int(distance) == distance) {
    delay(distances[int(distance)] * scale);
  } else {
    delay(distance * scale);
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

  int distances[7] = {0,1.5,2.25,3,3.5,4.5,5.25};
  if (int(distance) == distance) {
    delay(distances[int(distance)] * scale);
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
    delay(400);
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
    String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    String movement_string = letters[alphabet.indexOf(letter)];
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
      }
      delay(1000);
    }
}

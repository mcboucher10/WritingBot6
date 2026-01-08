#include <Servo.h>

Servo myservo;

int motor1Speed = 3;
int motor1D1 = 4;
int motor1D2 = 5;

int motor2Speed = 9;
int motor2D2 = 8;
int motor2D1 = 7;
int speed1 = 100;
int speed2 = 120;

int scale = 100;

float pi = 3.14159;

/*
Fx - Forward x units
P0 - Penup
P1 - Pendown
Dx - Forward xsqrt(2) units
Rx - Right 45x degrees
Lx - Left 45x degrees
*/

String letters[27] = {
    // A
  	"P1L2F6R2F3R2F3R2F3R4F3R2F3P0L2F1",

    //B
    "L2P1F7R2F3R2F3R2F3R4F4R2F4R2F4P0R4F3",

    //C
    "F5L4P1F3R2F6R2F3P0R2F6L2F1",

    //D
    "L2P1F6R2F3R1D1R1F4R1D1R1F3P0R4F5",

    //E
    "L2P1F6R2F4R4F4L2F3L2F3R4F3L2F3L2F4P0F1",

    //F
    "L2P1F6R2F4R4F4L2F3L2F3P0R2F3L2F3",

    //G
    "F4L2F6L2P1F5L2F6L2F5L2F2L2F3P0R4F3R2F2L2F3",

    //H
    "P1L2F6R4F3L2F3L2F3R4F6P0L2F1",

    // I
    "P1F1L2F6R2F1R4F2R4F1R2F6L2F1P0F2",

    //J
    "P0L2F2P1R4F2L2F2L2F7P0R4F7L2F2",

    // K
    "P1L2F6P0R4F3P1L3D3P0R4D3P1L2D3P0L1F1",
    
    //L
    "P1L2F6R4F6L2F3P0F1",
    
    //M
    "P1L2F6R3D3L2D3R3F6P0L2F1",
    
    //N
    "P1L2F6R3D6L3F6P0R4F6L2F1",
    
    //O
    "P1L2F6R2F3R2F6R2F3P0R4F4",
    
    //P
    "P1L2F6R2F3R2F3R2F3P0L2F3L2F4",
    
    // Q
    "P1L2F6R2F3R2F6R2F3P0R4F3P1R1D1P0L2F2R1",

    //R 
    "P1L2F6R2F3R2F3R2F3P1L3D3P0L1F1",

    //S 
    "P1F3L2F3L2F3R2F3R2F3P0R2F6L2F1",

    // T
    "P0L2F6R2P1F4P0R4F2P1L2F6P0L2F3",

    //U
    "P1L2F6R4F6L2F3L2F6P0R4F6L2F1",

    //V
    "P0L2F6P1R3D5L2D5P0R3F5L2F1",

    // W
    "P0L2F6P1R4F6L3F3R2F3L3F6P0R4F6L2F2",

    //X
    "P0L2F6P1R3D6P0L3F6P1L3D6P0L3F7",

    // Y
    "P0L2F6P1R3D3L2D3P0R4D3L1P1F3P0L2F3",

    // Z
    "P0F2L2F6R2P1F4R3D6L3F4P0F3",

    //SPACE 
    "P0F2"
    
};

void setup() {
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor1D1, OUTPUT);
    pinMode(motor1D2, OUTPUT);
    
    pinMode(motor2Speed, OUTPUT);
    pinMode(motor2D1, OUTPUT);
    pinMode(motor2D2, OUTPUT);
    Serial.begin(9600);
}

void loop() {
}

void forward(float distance) {
  analogWrite(motor1Speed, 100);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, 105);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  int distances[6] = {0,1.5,2.25,3,3.5,4.5};
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
    delay(445);
  }
  else if (theta == pi) {
    delay(785);
  }

  stop();
}

void right(float theta) {
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
    delay(420);
  }
  else if (theta == pi) {
    delay(855);
  }

  stop();
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
        forward(strength);
      } else if (step.charAt(0) == 'D') {
        forward(1.41 * strength);
      } // add P0 and P1 for penup and pendown respectively
      delay(1000);
    }
}

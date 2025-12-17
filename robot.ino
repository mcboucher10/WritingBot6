int motor1Speed = 3;
int motor1D1 = 4;
int motor1D2 = 5;

int motor2Speed = 9;
int motor2D2 = 8;
int motor2D1 = 7;
int speed = 100;

int scale = 10;

float pi = 3.14159;

float turn_constant = pi / (speed * 550 * 2);

String letters[27] = {
    "0000051636454303434050", 
    "0000063645443303334241300050", 
    "0001051636453616050110304150",
    "000006364541300050",
    "0000064606033303004050",
    "00000646060333030050",
    "0001051636453616050110304143234350",
    "0000060343464050",
    "0006462620400050",
    "00464130100150",
    "0000060346034050",
    "0006004050",
    "00000623464050",
    "000006404650",
    "0010304145361605011050",
    "00000636454433030050",
    "001001051636454220102031224050",
    "0000063645443303234050",
    "0001103041423313040516364550",
    "000646262050",
    "0006011030414650",
    "0006204650",
    "00061024304650",
    "00064023460050",
    "00062346232050",
    "000646004050",
    "0050"};

void setup() {
    Serial.begin(9600);
}

void loop() {
  write_letter('A');
}

void forward(float distance) {
  analogWrite(motor1Speed, speed);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, speed);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  delay(distance * scale);

  stop();
}

void stop() {
  analogWrite(motor1Speed, speed);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, LOW);
}

void left(float theta) {
  analogWrite(motor1Speed, speed);
  digitalWrite(motor1D1, HIGH);
  digitalWrite(motor1D2, LOW);

  analogWrite(motor2Speed, speed);
  digitalWrite(motor2D1, LOW);
  digitalWrite(motor2D2, HIGH);

  delay(550 / (pi / 2) * theta);

  stop();
}

void right(float theta) {
  analogWrite(motor1Speed, speed);
  digitalWrite(motor1D1, LOW);
  digitalWrite(motor1D2, HIGH);

  analogWrite(motor2Speed, speed);
  digitalWrite(motor2D1, HIGH);
  digitalWrite(motor2D2, LOW);

  delay(550 / (pi / 2) * theta);

  stop();
}

float point_to_point(float rotation, int p0[], int p1[]) {
    float dx = p1[0] - p0[0];
    float dy = p1[1] - p0[1];

    float dist = sqrt(dx * dx + dy * dy);
    float angle = atan2(dy, dx);
    float delta = angle - rotation;
    if (delta < -1 * pi || delta > 0 && delta < pi) {
      right(abs(delta));
    } else {
      left(abs(delta));
    }

    forward(dist);

    return angle;
}

void write_letter(char letter) {
    String alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    String movement_string = letters[alphabet.indexOf(letter)];
    float rot = point_to_point(0, movement_string[0], movement_string[1]);
    delay(1000);
    for (int i = 2; i < movement_string.length()-2; i+=2) {
        rot = point_to_point(rot, movement_string[i], movement_string[i+1]);
        delay(1000);
    }

    rot = point_to_point(rot, movement_string[movement_string.length()-2],movement_string[movement_string.length()-1]);
}

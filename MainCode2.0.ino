//bluetooth module pins
//bluetooth output pin
int tx = 1;
//bluetoth input pin
int rx = 0;
//bluetooth power input pin
int btp = 3;

//motor pins
//motor A
int enA = 10;
int in1 = 9;
int in2 = 8;
//motor B
int enB = 5;
int in3 = 7;
int in4 = 6;

//driving direction
int dd = 0;

void setup() {
  //start communication with serialboard or bluetoothboard
  Serial.begin(9600);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
  //start power for bluetooth module
  digitalWrite(btp, HIGH);
  //set motor pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //set all outputs on LOW
  allmotorpinslow();
  start();
}

//function to "test bluetoth connection" by checking if start pressing on smartphone gives the arduino a 1
void start() {
  Serial.println("Drücken Sie 'Start' um zu beginnen");
  Serial.println("");
  while (Serial.available() <= 0) 
  {;
  }
  if (Serial.available() > 0) {
    int Start = Serial.read();
    Start = (Start - '0');
    if (Start == 1) {
      Serial.println("STARTING...");
      Serial.println("");
      delay(3000);
      Serial.println("FERTIG!");
      Serial.println("Sie können nun den Roboter steuern, indem sie die Pfeiltasten drücken!");
      Serial.println("");
    }
    else {
      start();
      }
   }
}

//function to stop the arduino-robot completely, to make sure it doesnt do sth unexpectetly, and to avoid in different situations, that sth will go/ goes wrong 
void allmotorpinslow() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, 0);
  analogWrite(enB, 0);
}
  

//function to stop motors
void stopmotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}


//function will be reapeted all the time
void loop() {
  //read input
  int dd = Serial.read();
  dd = (dd - '0');

  //drvingdirection 0 - stop
  if (dd == 0) {
    stopmotors();
    //stop motors to be ready for new direction
    allmotorpinslow();
    Serial.println("STOPPT");
    Serial.println("");
  }
  
  //drivingdirection 1 - forward
  if (dd == 1) {
    //stop motors to be ready for new direction
    allmotorpinslow();
    //set the  motors in the right directions
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    //accelerate the motors from zero to 200, then stays on 200
    Serial.println("VORWÄRTS");
    Serial.println("");
    for (int x = 0; x <= 200; x++) {
      analogWrite(enA, x);
      analogWrite(enB, x);
      delay(20);
      //if theres a new input (other driving direction) it stops the function "forward"
      if (Serial.available() > 0) {
        break;
      }
    }
  }

  //drivingdirection 2 - right
  if (dd == 2) {
    //stop motors to be ready for new direction
    allmotorpinslow();
    //set the  motors in the right directions
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    Serial.println("Nach Rechts drehen...");
    Serial.println("");
    //accelerate the motors from zero to 100, then stays on 100
    for (int y = 0; y <= 100; y++) {
      analogWrite(enA, y);
      analogWrite(enB, y);
      delay(10);
      //if theres a new input (other driving direction) it stops the function "right"
      if (Serial.available() > 0) {
        break;
      }
    }
  }

  //drivingdirection 3 - backwards
  if (dd == 3) {
    //stop motors to be ready for new direction
    allmotorpinslow();
    //set the  motors in the right directions
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    Serial.println("RÜCKWÄRTS");
    Serial.println("");
    //accelerate the motors from zero to 150, then stays on 150
    for (int z = 0; z <= 150; z++) {
      analogWrite(enA, z);
      analogWrite(enB, z);
      delay(25);
      //if theres a new input (other driving direction) it stops the function "backwards"
      if (Serial.available() > 0) {
        break;;
      }
    }   
  }

  //drivingdirection 4 - left
  if (dd == 4) {
    //stop motors to be ready for new direction
    allmotorpinslow();
    //set the  motors in the right directions
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    Serial.println("Nach Links drehen...");
    Serial.println("");
    //accelerate the motors from zero to 100, then stays on 100
    for (int v = 0; v <= 100; v++) {
      analogWrite(enA, v);
      analogWrite(enB, v);
      delay(10);
      //if theres a new input (other driving direction) it stops the function "left"
      if (Serial.available() > 0) {
        break;
      }
    }
  }
}

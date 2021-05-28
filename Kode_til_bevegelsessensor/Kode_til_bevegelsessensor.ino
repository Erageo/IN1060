int ledLys1 = 3;               //Pins som LED-lysene er koblet til
int ledLys2 = 4;
int ledLys3 = 5;

int sensor = 2;                 //Pin som PIR-SENSOR er koblet til
int sensorState = 0;            //Variabel som lagrer PIR-SENSORens status

void setup() {
  //Starter LED-lysene som en output
  pinMode(ledLys1, OUTPUT);
  pinMode(ledLys2, OUTPUT);
  pinMode(ledLys3, OUTPUT);
  
  //Starter PIR-SENSOR som en input
  pinMode(sensor, INPUT);

  //Starter PIR-SENSOR
  Serial.begin(9600);
}

void loop() {
  pirSensor();
  
  //Setter et delay slik at maskinen ikke sjekker unoedvendig
  delay(1000);
}

void pirSensor() {
  //PIR-SENSOR
  sensorState = digitalRead(sensor);
  
  //Hvis bevegelse oppdages..
  if (sensorState == HIGH) {
    
    digitalWrite(ledLys1, HIGH);
    digitalWrite(ledLys2, HIGH);
    digitalWrite(ledLys3, HIGH);
    
    //Setter et delay slik at LEDene ikke skrurs av med en gang
    delay(2000);
    
  } else {
    
    digitalWrite(ledLys1, LOW);
    digitalWrite(ledLys2, LOW);
    digitalWrite(ledLys3, LOW);
  }
}

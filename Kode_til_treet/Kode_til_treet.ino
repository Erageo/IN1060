#include <Adafruit_NeoPixel.h>

//Neopixel til treet
#define PIN 2                 //Input pin som Neopixel er koblet til
#define NUMPIXELS 12          //Antall neopixels i strip'en
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//Variabler til Neopixel
int redColor = 0;
int greenColor = 0;
int blueColor = 0;

//Variabler til potentiometer
int const potPin = A0;        //Pin som potentiometeret er koblet til
int potVal;                   //Variabel som lagrer potentiometerets verdi
int angle;                    //Variabel som lagrer vinkelen til potentiometeret

//Variabler til photoresistor
int const photoPin = A1;      //Pin som photoresistoren er koblet til
int photoState = 0;           //Variabel som lagrer photoresistorens verdi


void setup() {
  //Starter opp NeoPixel biblioteket
  pixels.begin();

  //Sikre at alle NeoPixels er av hvis RESET trykkes
  pixels.clear();
  pixels.show();
 
  //Potentiometer og photoresistor
  Serial.begin(9600);
  //Starter Potentiometeret som en input
  pinMode(potPin, INPUT);
}

void loop() {
  //Kaller paa modulen photoresistor() som sjekker om photoresistoren er paa eller ikke
  photoresistor();

  //Setter et delay slik at maskinen ikke sjekker unoedvendig
  delay(1000);
}

void photoresistor() {
  //Leser og lagrer verdien fra photoresistoren
  photoState = analogRead(photoPin);

   //Hvis det er lyst saa kalles det paa readPot() som sjekker hvilken verdi potentiometeret er paa
   //og videre starter en oekt som tilsvarer med verdien til potentiometeret
  if (photoState > 450) {
      Serial.println("Skrur paa oekter.");
      readPot();
  //Hvis det er moerkt saa skrus lysene av
  } else {
      Serial.println("Skrur av oekter.");
      pixels.clear();
      pixels.show();
  }
}

void turnOnPixel(long delayval) {
//For-lokken gaar gjennom alle Neopixelene, gir dem farge og skrur de paa
  for (int i=0; i < NUMPIXELS; i++) {
      //pixels.Color tar RBG verdier fra 0 til 255
      pixels.setPixelColor(i, pixels.Color(16, 24, 8));

      //Lager en long variabel som kan holde paa antall NUMPIXELS
      long pix = NUMPIXELS;

      //Her settes det et delay der hvor antall totale millisekunder deles paa antall Neopixeler
      delay(delayval/pix);
      Serial.print(delayval/pix);
    
      //Sender oppdatert pixelfarge til Neopixelene
      pixels.show();
  
  }
  //Setter et delay slik at lysene ikke skrur seg av med en gang
  delay(2000);

  //Deretter skrus lysene av
  pixels.clear();
  pixels.show();
}

void readPot() {
  //Leser og lagrer verdien fra potentiometeret
  potVal = analogRead(potPin);
  Serial.print("potVal: ");
  Serial.print(potVal);

  //map-funksjonen gjoer det lettere for oss aa bruke verdiene fra potentiometeret
  //Her tar den verdiene fra potentiometeret og gjoer dem om til grader (0-179)
  angle = map(potVal, 0, 1023, 0, 179);
  Serial.print(" , angle: ");
  Serial.print(angle);

  //Hvis vinkelen paa potentiometeret er mindre eller lik 60 grader saa fylles lysene
  //i loepet av 20 sekunder
  if (angle <= 60) {
    turnOnPixel(20000);

  //Hvis vinkelen paa potentiometeret er mindre eller lik 120 grader saa fylles lysene
  //i loepet av 40 sekunder
  } else if (angle <= 120) {
    turnOnPixel(40000);

  //Hvis vinkelen paa potentiometeret er mer enn 120 grader saa fylles lysene
  //i loepet av 60 sekunder
  } else {
    turnOnPixel(60000);
  }
}

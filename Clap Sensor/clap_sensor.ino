int micPin = A0;          // pin that the mic is attached to
int gndPin = A1;
int powerPin = A2;
int micValue1 = 0;  
int micValue2 = 0; // the Microphone value
int led1 = 13;
boolean lightOn = false;
int aplauso = 0;
int tiempo = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(powerPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  pinMode(micPin, INPUT);
  digitalWrite(gndPin,LOW);
  delay(500);
  digitalWrite(powerPin,HIGH);
  Serial.begin(9600);  //for test the input value initialize serial
}

void loop() {
  if ((micValue1-micValue2 > 500||micValue2-micValue1 > 500)&&aplauso == 0){
  aplauso = 1;
  delay(200);
  }
  micValue1 = analogRead(micPin);  // read pin value
  Serial.println(micValue1);
  delay(5);
  micValue2 = analogRead(micPin);
  Serial.println(micValue2);
  if (aplauso == 1) tiempo ++;
  if (tiempo == 10){
    aplauso = 0;
    tiempo = 0;
  }
  if ((micValue1-micValue2 > 500||micValue2-micValue1 > 500)&&aplauso == 1){
    lightOn = !lightOn;
    digitalWrite(led1, lightOn);
    tiempo = 0;
    aplauso = 0;
    
  }
} 

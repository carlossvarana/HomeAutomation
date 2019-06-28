#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "fca9c6912d554838bc49a3d077856874"; //You will get this Auth Token in Gmail if you signin Blynk app with your Gmail ID

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CSTEPHANO "; //Enter your WIFI Name
char pass[] = "19022227";//Enter your WIFI Password

WidgetBridge bridge1(V3);

void notifyOnButtonPress()
{
  // Invert state, since button is "Active LOW"
  int isButtonPressed = !digitalRead(2);
  if (isButtonPressed) {
  digitalWrite(0,HIGH);
  bridge1.virtualWrite(V0,"encender luz sala");
  delay(1000);
  bridge1.virtualWrite(V0,"c");
  }
  else{
  digitalWrite(0,LOW);
  bridge1.virtualWrite(V0,"apagar luz sala");
  delay(1000);
  bridge1.virtualWrite(V0,"c");
  }
  delay(500);
}

BLYNK_CONNECTED() {
  // Place the AuthToken of the second hardware here
  bridge1.setAuthToken("fa45e3f1246248559310a4017b8e5dd8"); 
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(0,OUTPUT);


  Blynk.begin(auth, ssid, pass);
  
  // Other Time library functions can be used, like:
  //   timeStatus(), setSyncInterval(interval)...
  // Read more: http://www.pjrc.com/teensy/td_libs_Time.html
  
  // Setup notification button on pin 2

  digitalWrite(0,LOW);
  // Attach pin 2 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(2), notifyOnButtonPress, CHANGE);
}

void loop()
{
  Blynk.run();
}

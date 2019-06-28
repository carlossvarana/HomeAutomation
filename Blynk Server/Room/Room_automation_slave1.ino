#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "9693a0df7995411cb24f984808f9a344"; //You will get this Auth Token in Gmail if you signin Blynk app with your Gmail ID

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CSTEPHANO "; //Enter your WIFI Name
char pass[] = "19022227";//Enter your WIFI Password

WidgetBridge bridge_luz_cuarto(V2);

void notifyOnButtonPress()
{
  // Invert state, since button is "Active LOW"
  int isButtonPressed = digitalRead(0);
  if (isButtonPressed) {
  digitalWrite(2,HIGH);
  bridge_luz_cuarto.virtualWrite(V1,"elc");
  delay(1000);
  }
  else{
  digitalWrite(2,LOW);
  bridge_luz_cuarto.virtualWrite(V1,"alc");
  delay(1000);
  }
}

BLYNK_CONNECTED() {
  // Place the AuthToken of the second hardware here
  bridge_luz_cuarto.setAuthToken("fa45e3f1246248559310a4017b8e5dd8"); 
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(0,INPUT);
  pinMode(2,OUTPUT);


  Blynk.begin(auth, ssid, pass);
  
  // Other Time library functions can be used, like:
  //   timeStatus(), setSyncInterval(interval)...
  // Read more: http://www.pjrc.com/teensy/td_libs_Time.html
  
  // Setup notification button on pin 2

  digitalWrite(2,LOW);
  // Attach pin 2 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(0), notifyOnButtonPress, CHANGE);
}

void loop()
{
  Blynk.run();
}


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

IPAddress    apIP(42, 42, 42, 42);  // Defining a static IP address: local & gateway
                                    // Default IP in AP mode is 192.168.4.1

/* This are the WiFi access point settings. Update them to your likin */
const char *ssid = "ESP8266";
const char *password = "12345678";
  String texto = "asdf";

// Define a web server at port 80 for HTTP
ESP8266WebServer server(80);

void handleer() {
  texto = server.arg("tetete");
  Serial.print("               ");
  Serial.print("               ");
  Serial.print(texto);
  Serial.print('{');
char textual[1024];
strcpy(textual, texto.c_str());
  char html[1000];

// Build an HTML page to display on the web-server root address
  snprintf ( html, 1000,

"<html>\
  <head>\
    <title>ESP8266 WiFi Network</title>\
    <style>\
      body { font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #AA0000;  font-size: 1.5em;}\
      h1 { font-size: 1.5em;}\
    </style>\
  </head>\
  <body>\
    <h1>EL TEXTO FUE ENVIADO</h1>\
    <h2>%s<h2>\
</form>\
  </body>\
</html>",

    textual
  );
  server.send ( 200, "text/html", html );
}
void handleRoot() {
  
  char html[1000];

// Build an HTML page to display on the web-server root address
  snprintf ( html, 1000,

"<html>\
  <head>\
    <title>PROYECTO FINAL</title>\
    <style>\
      body { font-family: Arial, Helvetica, Sans-Serif; font-size: 1.5em; Color: #000000; }\
      h1 { Color: #AA0000; align: 'center';}\
      input[type=text]:focus{ border: 2px solid #555;}\
    </style>\
  </head>\
  <body>\
    <h1>PROYECTO FINAL MC 2018-02</h1>\
    <p>Ingrese el texto que desea visualizar en el Display (Max. 32)</p>\
    <form action='/action_page' method='post'>\
    <input maxlength='1000' height:450px type='textarea' name='tetete' placeholder='Texto aleatorio'><br>\
<input width: 100% background-color: #4CAF50 type='submit' value='Submit'>\
</form>\
  </body>\
</html>"
  );
  server.send ( 200, "text/html", html );
}

void handleNotFound() {
  digitalWrite ( LED_BUILTIN, 0 );
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += ( server.method() == HTTP_GET ) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for ( uint8_t i = 0; i < server.args(); i++ ) {
    message += " " + server.argName ( i ) + ": " + server.arg ( i ) + "\n";
  }

  server.send ( 404, "text/plain", message );
  digitalWrite ( LED_BUILTIN, 1 ); //turn the built in LED on pin DO of NodeMCU off
}

void setup() {
  
  delay(1000);
  Serial.begin(19200);
  Serial.println();
  Serial.println("Configuring access point...");

  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));   // subnet FF FF FF 00  
  
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
//  server.on ( "/", handleRoot );
//  server.on("/action_post", HTTP_POST, handleer);
  server.on("/", HTTP_GET, handleRoot);        // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/action_page", HTTP_POST, handleer); // Call the 'handleLogin' function when a POST request is made to URI "/login"
  server.onNotFound(handleNotFound);           // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"
  server.on ( "/inline", []() {
    server.send ( 200, "text/plain", "this works as well" );
  } );
  
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

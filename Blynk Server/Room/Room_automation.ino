
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "fa45e3f1246248559310a4017b8e5dd8"; //You will get this Auth Token in Gmail if you signin Blynk app with your Gmail ID

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "CSTEPHANO "; //Enter your WIFI Name
char pass[] = "19022227";//Enter your WIFI Password

// Estados físicos en variables
bool luz_cuarto = 0;
bool luz_cuarto_mesa = 0;

// Variable que almacena el comando
bool externoInterno = 1;
int comando_n = 0;

// Para separar las líneas de comandos
int cmd_1=0;
int cmd_2=0;
int cmd_3=0;
String comando1;
String comando2;
String comando3;
String comando4;

// Para almacenar la hora
String currentTime;
String currentDate;


WidgetTerminal terminal(V0);
WidgetBridge bridge_luz_cuarto(V2);
WidgetBridge bridge_luz_cuarto_mesa(V3);
BlynkTimer timer;
WidgetRTC rtc;


void dividirComando(String comandop);
void validarComando();
void ejecutarComando(int comando_np);
//void notifyOnButtonPress()
//{
//  // Invert state, since button is "Active LOW"
//  int isButtonPressed = !digitalRead(D2);
//  if (isButtonPressed) {
//    //Serial.println("Button is pressed.");
//
//    // Note:
//    //   We allow 1 notification per 5 seconds for now.
//    Blynk.notify("Prueba de interrupcion en {DEVICE_NAME}\nEl boton esta presionado");
//
//    // You can also use {DEVICE_NAME} placeholder for device name,
//    // that will be replaced by your device name on the server side.
//    //Blynk.notify("Yaaay... {DEVICE_NAME}  button is pressed!");
//  }
//  else{
//    Blynk.notify("Prueba de interrupcion en {DEVICE_NAME}\nEl boton no esta presionado");
//  }
//}



// You can send commands from Terminal to your hardware. Just use
// the same Virtual Pin as your Terminal Widget
BLYNK_WRITE(V1){
  
  //borrar variables
  comando1="";  comando2="";  comando3="";  comando4="";
  
  String comando_wifi = param.asStr();
  if (comando_wifi == "elc") comando_n=103;
  else if(comando_wifi == "alc") comando_n=3;
  else if(comando_wifi == "elcm") comando_n=104;
  else if(comando_wifi == "alcm") comando_n=4;
  externoInterno=0;
  ejecutarComando(comando_n);
  terminal.flush();
}
BLYNK_WRITE(V0)
{
  // String("") == param.asStr()
  
  String comando = param.asStr();
  externoInterno=1;
  dividirComando(comando);
  validarComando();
  ejecutarComando(comando_n);
  // Ensure everything is sent
  terminal.flush();
}

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
  
  // Place the AuthToken of the second hardware here
  bridge_luz_cuarto.setAuthToken("9693a0df7995411cb24f984808f9a344"); 
  
  // Place the AuthToken of the second hardware here
  bridge_luz_cuarto_mesa.setAuthToken("xxxxxxxxxxxxxxxxxxxxxxx"); 
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(D1,OUTPUT);
  pinMode(D2,INPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  pinMode(D5,OUTPUT);
  pinMode(D6,OUTPUT);
  pinMode(D7,OUTPUT);
  pinMode(D8,OUTPUT);

  digitalWrite(D1,LOW);
  // digitalWrite(D2,HIGH);
  digitalWrite(D3,LOW);
  digitalWrite(D4,HIGH);
  digitalWrite(D5,LOW);
  digitalWrite(D6,LOW);
  digitalWrite(D7,LOW);
  digitalWrite(D8,LOW);
  
  

  Blynk.begin(auth, ssid, pass);
  
  // Other Time library functions can be used, like:
  //   timeStatus(), setSyncInterval(interval)...
  // Read more: http://www.pjrc.com/teensy/td_libs_Time.html

//  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds
  //timer.setInterval(1000L, clockDisplay);

  
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  terminal.clear();
  terminal.println(F("Blynk v" BLYNK_VERSION ": Servidor iniciado"));
  terminal.println(F("-------------"));
  terminal.flush();
  
//  // Setup notification button on pin 2
//  pinMode(D2, INPUT_PULLUP);
//  // Attach pin 2 interrupt to our handler
//  attachInterrupt(digitalPinToInterrupt(D2), notifyOnButtonPress, CHANGE);
}


  
                              ///////////////////////////////////////////////////
                              ////// PARTE 1 DIVIDIR EL COMANDO EN 4 PARTES  ////
                              ///////////////////////////////////////////////////
                              
void dividirComando(String comandop){
  //borrar variables
  Serial.println(comando_n);
  comando1="";  comando2="";  comando3="";  comando4="";
  cmd_2=0;  cmd_3=0;
  cmd_1=comandop.indexOf(" ");
  if(cmd_1>0){
    cmd_2=comandop.indexOf(" ",cmd_1+1);
    if(cmd_2>0){
      cmd_3=comandop.indexOf(" ",cmd_2+1);
      if(cmd_3>0){
        comando1=comandop.substring(0,cmd_1);
        comando2=comandop.substring(cmd_1+1,cmd_2);
        comando3=comandop.substring(cmd_2+1,cmd_3);
        comando4=comandop.substring(cmd_3+1);
      }else{
        comando1=comandop.substring(0,cmd_1);
        comando2=comandop.substring(cmd_1+1,cmd_2);
        comando3=comandop.substring(cmd_2+1);
      }
    }else{
      comando1=comandop.substring(0,cmd_1);
      comando2=comandop.substring(cmd_1+1);
    }
  }else{
    comando1=comandop;
  }
}

  
                              /////////////////////////////////////////////
                              ////// PARTE 2 VALIDACIÓN DE COMANDOS  //////
                              /////////////////////////////////////////////
void validarComando(){
  if      (comando1.equalsIgnoreCase("clr") || comando1.equalsIgnoreCase("limpiar") || comando1.equalsIgnoreCase("c"))  {comando_n = 5000;  }
  else if (comando1.equalsIgnoreCase("help") || comando1.equalsIgnoreCase("ayuda") || comando1.equalsIgnoreCase("h"))   {comando_n = 5001;  }
  else if (comando1.equalsIgnoreCase("exit") || comando1.equalsIgnoreCase("salir") || comando1.equalsIgnoreCase("e"))   {comando_n = 5002;  }
  else if (comando1.equalsIgnoreCase("time") || comando1.equalsIgnoreCase("tiempo") || comando1.equalsIgnoreCase("t"))  {comando_n = 5003;  }
  
  else if (comando1.equalsIgnoreCase("apagar") || (comando_n>0 && comando_n<100)){    //APAGAR
  Serial.println(comando_n);
    if(comando2=="luz" || comando1=="luz" ||(comando_n>1 && comando_n<20)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=3;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=4; }  }
      else if(comando3=="todas" || comando2=="todas" || comando1=="todas"){                                               
        comando_n=19;
        }
      else{                                                                           
        comando_n=2;}
    }else{                                                                     
      comando_n=1;}
  }
  else if(comando1.equalsIgnoreCase("encender") || (comando_n>100 && comando_n<200)){   //ENCENDER
  Serial.println(comando_n);
    if(comando2=="luz" || comando1=="luz" ||(comando_n>101 && comando_n<120)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=103;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=104; }  }
      else{                                                                           
        comando_n=102;}
    }else{                                                                     
      comando_n=101;}
  }
  else if(comando1.equalsIgnoreCase("estado") || (comando_n>200 && comando_n<300)){   //ESTADO
    if(comando2=="luz" || comando1=="luz" ||(comando_n>201 && comando_n<220)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=203;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=204; }  }
      else if(comando3=="todas" || comando2=="todas" || comando1=="todas"){                                               
        comando_n=219;}
      else{                                                                           
        comando_n=202;}
    }else{                                                                     
      comando_n=201;}
  }
  
  
//  /*
  Serial.println("**FOR DEBUGGING**");
  Serial.print(comando1);  Serial.print(" /./ ");
  Serial.print(comando2);  Serial.print(" /./ ");
  Serial.print(comando3);  Serial.print(" /./ ");
  Serial.print(comando4);  Serial.print(" /./ ");
  Serial.println(comando_n);
  Serial.println("**FOR DEBUGGING**");Serial.println(" ");
//  */
  
}

                              /////////////////////////////////////////////
                              ////// PARTE 3 EJECUCIÓN DE COMANDOS    /////
                              /////////////////////////////////////////////
void ejecutarComando(int comando_np){
  
  Serial.println(comando_np);
  switch(comando_np){
    case 1:   // APAGAR
    case 101: // ENCENDER
    case 201: // ESTADO
      terminal.println("  -luz (...)");
      break;
      
    case 2: // APAGAR LUZ
    case 102: // ENCENDER LUZ
    case 202: // ESTADO LUZ
      terminal.println("  -cuarto");
      terminal.println("  -cuarto mesa");
      if(comando_n!=102)terminal.println("  -todas");
      break;
      
    case 3: //APAGAR LUZ CUARTO
      if (externoInterno){ if (luz_cuarto==0){terminal.println("La luz está apagada");}
      else{  terminal.println("Listo");  luz_cuarto = 0;  bridge_luz_cuarto.digitalWrite(2,LOW);}}
      else{ if(luz_cuarto==1) {luz_cuarto=0; Blynk.notify("La luz del cuarto se apagó");}}
      comando_n=0;     break; 
      
    case 4: // APAGAR LUZ CUARTO MESA
      if (externoInterno){ if (luz_cuarto_mesa==0){terminal.println("La luz está apagada");}
      else{  terminal.println("Listo"); luz_cuarto_mesa = 0;  bridge_luz_cuarto_mesa.digitalWrite(2,LOW);}}
      else{ if(luz_cuarto_mesa==1) {luz_cuarto_mesa=0; Blynk.notify("La luz de mesa del cuarto se apagó");}}
      comando_n=0;     break;
      
    case 19: // APAGAR LUZ TODAS
      if (luz_cuarto_mesa || luz_cuarto)terminal.println("Listo"); 
      else{terminal.println("Las luces están apagadas");}
      luz_cuarto_mesa = 0;  bridge_luz_cuarto_mesa.digitalWrite(2,LOW);  
      luz_cuarto = 0;       bridge_luz_cuarto.digitalWrite(2,LOW);
      comando_n=0;     break;
      
    case 103: //ENCENDER LUZ CUARTO
      if (externoInterno){ if (luz_cuarto==1){terminal.println("La luz está encendida") ;}
      else{  terminal.println("Listo") ;  luz_cuarto = 1;  bridge_luz_cuarto.digitalWrite(2,HIGH);}}
      else{ if(luz_cuarto==0) {luz_cuarto=1; Blynk.notify("La luz del cuarto se encendió");}}
      comando_n=0;     break;
      
    case 104: // ENCENDER LUZ CUARTO MESA
      if (externoInterno){ if (luz_cuarto_mesa==1){terminal.println("La luz está encendida") ;}
      else{  terminal.println("Listo") ;  luz_cuarto_mesa = 1;  digitalWrite(2,HIGH);}}
      else{ if(luz_cuarto_mesa==0) {luz_cuarto_mesa=1; Blynk.notify("La luz de mesa del cuarto se encendió");}}
      comando_n=0;     break;
      
    case 203: //ESTADO LUZ CUARTO
      if (luz_cuarto==0){terminal.println("La luz está apagada");}
      else{  terminal.println("La luz está encendida");}
      comando_n=0;     break;
      
    case 204: // ESTADO LUZ CUARTO MESA
      if (luz_cuarto_mesa==0){terminal.println("La luz está apagada");}
      else{  terminal.println("La luz está encendida");}
      comando_n=0;     break;
      
    case 219: // ESTADO LUZ TODAS
      terminal.println("Estado luces:"); 
      terminal.print("  -cuarto:      ");
      if(luz_cuarto)terminal.println("encendida");
      else terminal.println("apagada");
      terminal.print("  -cuarto mesa: ");
      if(luz_cuarto_mesa)terminal.println("encendida");
      else terminal.println("apagada");
      comando_n=0;     break;
      
    case 5000: // CLEAR 
      terminal.clear();
      terminal.println(F("Blynk v" BLYNK_VERSION ": Servidor iniciado"));
      terminal.println(F("-------------"));
      comando_n=0;     break;
      
    case 5001: // HELP
      terminal.clear();
      terminal.println(F("Blynk v" BLYNK_VERSION ": Servidor iniciado"));
      terminal.println(F("-------------"));
      terminal.println("MENU AYUDA");
      terminal.println("  Escribe alguno de los comandos presentados\n  a continuación para iniciar:\n\t\t-apagar\n\t\t-encender\n\t\t-estado\n");
      terminal.println("  Si deseas salir del menu debes escribir\n  'salir' o 'e'.");
      terminal.println("  Si deseas limpiar la pantalla debes \n  escribir 'limpiar' o 'c'.");
      comando_n=0;     break;
      
    case 5002: // EXIT
      terminal.println("ok");
      delay(100);
      terminal.clear();
      terminal.println(F("Blynk v" BLYNK_VERSION ": Servidor iniciado "));
      terminal.println(F("-------------"));
      comando_n=0;     break;
      
    case 5003: // TIME
      currentTime = String(hour()) + ":" + minute() + ":" + second();
      currentDate = String(day()) + "/" + month() + "/" + year();
      terminal.print("Tiempo actual: ");
      terminal.print(currentTime);
      terminal.print(" ");
      terminal.print(currentDate);
      terminal.println();
      comando_n=0;     break;
      
    default:
      comando_n=0;
      terminal.println("?");
      break;
  }
  Serial.println(comando_n);                   
}

void loop()
{
  Blynk.run();
}

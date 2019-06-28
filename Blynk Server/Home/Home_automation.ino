
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
bool luz_sala = 0;
bool luz_comedor = 0;
bool ventilador1 = 0;
bool ventilador2 = 0;

// Variable que almacena el comando
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
WidgetBridge bridge_luz_sala(V3);
BlynkTimer timer;
WidgetRTC rtc;


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
BLYNK_WRITE(V0)
{
  // String("") == param.asStr()


  
                          ///////////////////////////////////////////////////
                          ////// PARTE 1 DIVIDIR EL COMANDO EN 4 PARTES  ////
                          ///////////////////////////////////////////////////
  
  String comando = param.asStr();
  //borrar variables
  comando1="";  comando2="";  comando3="";  comando4="";
  cmd_2=0;  cmd_3=0;
  cmd_1=comando.indexOf(" ");
  if(cmd_1>0){
    cmd_2=comando.indexOf(" ",cmd_1+1);
    if(cmd_2>0){
      cmd_3=comando.indexOf(" ",cmd_2+1);
      if(cmd_3>0){
        comando1=comando.substring(0,cmd_1);
        comando2=comando.substring(cmd_1+1,cmd_2);
        comando3=comando.substring(cmd_2+1,cmd_3);
        comando4=comando.substring(cmd_3+1);
      }else{
        comando1=comando.substring(0,cmd_1);
        comando2=comando.substring(cmd_1+1,cmd_2);
        comando3=comando.substring(cmd_2+1);
      }
    }else{
      comando1=comando.substring(0,cmd_1);
      comando2=comando.substring(cmd_1+1);
    }
  }else{
    comando1=comando;
  }


  
                                /////////////////////////////////////////////
                                ////// PARTE 2 VALIDACIÓN DE COMANDOS  //////
                                /////////////////////////////////////////////

  if      (comando1.equalsIgnoreCase("clr") || comando1.equalsIgnoreCase("limpiar") || comando1.equalsIgnoreCase("c"))  {comando_n = 5000;  }
  else if (comando1.equalsIgnoreCase("help") || comando1.equalsIgnoreCase("ayuda") || comando1.equalsIgnoreCase("h"))   {comando_n = 5001;  }
  else if (comando1.equalsIgnoreCase("exit") || comando1.equalsIgnoreCase("salir") || comando1.equalsIgnoreCase("e"))   {comando_n = 5002;  }
  else if (comando1.equalsIgnoreCase("time") || comando1.equalsIgnoreCase("tiempo") || comando1.equalsIgnoreCase("t"))  {comando_n = 5003;  }
  
  else if (comando1.equalsIgnoreCase("apagar") || (comando_n>0 && comando_n<100)){    //APAGAR
    if(comando2=="luz" || comando1=="luz" ||(comando_n>1 && comando_n<20)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=3;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=4; }  }
      else if(comando3=="todas" || comando2=="todas" || comando1=="todas"){                                               
        comando_n=19;
        }
      else if(comando3=="sala" || comando2=="sala" || comando1=="sala"){
        comando_n=5;
      }
      else if(comando3=="comedor" || comando2=="comedor" || comando1=="comedor"){
        comando_n=6;
      }
      else{                                                                           
        comando_n=2;}
    }else if(comando2=="ventilador" || comando1=="ventilador" ||(comando_n>19 && comando_n<24)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=21;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=22; }  }
      else if(comando3=="todos" || comando2=="todos" || comando1=="todos"){                                               
        comando_n=23;}
      else{                                                                           
        comando_n=20;}
    }else{                                                                     
      comando_n=1;}
  }
  else if(comando1.equalsIgnoreCase("encender") || (comando_n>100 && comando_n<200)){   //ENCENDER
    if(comando2=="luz" || comando1=="luz" ||(comando_n>101 && comando_n<120)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=103;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=104; }  }
      else if(comando3=="sala" || comando2=="sala" || comando1=="sala"){
        comando_n=105;
      }
      else if(comando3=="comedor" || comando2=="comedor" || comando1=="comedor"){
        comando_n=106;
      }
      else{                                                                           
        comando_n=102;}
    }else if(comando2=="ventilador" || comando1=="ventilador" ||(comando_n>119 && comando_n<123)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=121;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=122; }  }
      else{                                                                           
        comando_n=120;}
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
      else if(comando3=="sala" || comando2=="sala" || comando1=="sala"){
        comando_n=205;      }
      else if(comando3=="comedor" || comando2=="comedor" || comando1=="comedor"){
        comando_n=206;      }
      else{                                                                           
        comando_n=202;}
    }else if(comando2=="ventilador" || comando1=="ventilador" ||(comando_n>219 && comando_n<224)){
      if(comando3=="cuarto" || comando2=="cuarto" || comando1=="cuarto"){                 
        comando_n=221;
        if(comando4=="mesa" || comando3=="mesa" || comando2=="mesa"){                                             
          comando_n=222; }  }
      else if(comando3=="todos" || comando2=="todos" || comando1=="todos"){                                               
        comando_n=223;}
      else{                                                                           
        comando_n=220;}
    }else{                                                                     
      comando_n=201;}
  }
  
  
  /*
  Serial.println("**FOR DEBUGGING**");
  Serial.print(comando1);  Serial.print(" /./ ");
  Serial.print(comando2);  Serial.print(" /./ ");
  Serial.print(comando3);  Serial.print(" /./ ");
  Serial.print(comando4);  Serial.print(" /./ ");
  Serial.println(comando_n);
  Serial.println("**FOR DEBUGGING**");Serial.println(" ");
  */



                                /////////////////////////////////////////////
                                ////// PARTE 3 EJECUCIÓN DE COMANDOS    /////
                                /////////////////////////////////////////////
  
  switch(comando_n){
    case 1:   // APAGAR
    case 101: // ENCENDER
    case 201: // ESTADO
      terminal.println("  -luz (...)");
      terminal.println("  -ventilador (...)");
      break;
      
    case 2: // APAGAR LUZ
    case 102: // ENCENDER LUZ
    case 202: // ESTADO LUZ
      terminal.println("  -cuarto");
      terminal.println("  -cuarto mesa");
      terminal.println("  -sala");
      terminal.println("  -comedor");
      if(comando_n!=102)terminal.println("  -todas");
      break;
      
    case 3: //APAGAR LUZ CUARTO
      if (luz_cuarto==0){terminal.println("La luz está apagada");}
      else{  terminal.println("Jajajaja dale dale");  luz_cuarto = 0;  digitalWrite(D1,LOW);}
      comando_n=0;     break;
      
    case 4: // APAGAR LUZ CUARTO MESA
      if (luz_cuarto_mesa==0){terminal.println("La luz está apagada");}
      else{  terminal.println("Jajajaja dale dale"); luz_cuarto_mesa = 0;  digitalWrite(D3,LOW);}
      comando_n=0;     break;
      
    case 5: // APAGAR LUZ SALA
      if (luz_sala==0){terminal.println("La luz está apagada");}
      else{  terminal.println("Jajajaja dale dale"); luz_sala = 0;  bridge_luz_sala.digitalWrite(0,LOW);}
      comando_n=0;     break;
      
    case 6: // APAGAR LUZ COMEDOR
      if (luz_comedor==0){terminal.println("La luz está apagada");}
      else{  terminal.println("Jajajaja dale dale"); luz_comedor = 0;  digitalWrite(D6,LOW);}
      comando_n=0;     break;
      
    case 19: // APAGAR LUZ TODAS
      if (luz_cuarto_mesa || luz_cuarto || luz_sala || luz_comedor)terminal.println("Jajajaja dale dale"); 
      else{terminal.println("Las luces están apagadas");}
      luz_cuarto_mesa = 0;  digitalWrite(D3,LOW);  
      luz_cuarto = 0;       digitalWrite(D1,LOW);
      luz_sala = 0;         bridge_luz_sala.digitalWrite(0,LOW);  
      luz_comedor = 0;      digitalWrite(D6,LOW);
      comando_n=0;     break;

    case 20: //APAGAR VENTILADOR
    case 120://ENCENDER VENTILADOR
    case 220://ESTADO VENTILADOR
      terminal.println("  -cuarto");
      terminal.println("  -cuarto mesa");
      if(comando_n!=120)terminal.println("  -todos");
      break;
      
    case 21:    //APAGAR VENTILADOR CUARTO
      if (ventilador1==0){terminal.println("El ventilador está apagado");}
      else{  terminal.println("Jajajaja dale dale"); ventilador1 = 0;  digitalWrite(D7,LOW);}
      comando_n=0;     break;
      
    case 22:    //APAGAR VENTILADOR CUARTO MESA
      if (ventilador2==0){terminal.println("El ventilador está apagado");}
      else{  terminal.println("Jajajaja dale dale"); ventilador2 = 0;  digitalWrite(D8,LOW);}
      comando_n=0;     break;
      
    case 23: // APAGAR VENTILADOR TODOS
      if (ventilador1 || ventilador2)terminal.println("Jajajaja dale dale"); 
      else{terminal.println("Los ventiladores están apagados");}
      ventilador1 = 0;       digitalWrite(D7,LOW);  
      ventilador2 = 0;       digitalWrite(D8,LOW);
      comando_n=0;     break;
      
    case 103: //ENCENDER LUZ CUARTO
      if (luz_cuarto==1){terminal.println("La luz está encendida") ;}
      else{  terminal.println("Jajaja dale dale") ;  luz_cuarto = 1;  digitalWrite(D1,HIGH);}
      comando_n=0;     break;
      
    case 104: // ENCENDER LUZ CUARTO MESA
      if (luz_cuarto_mesa==1){terminal.println("La luz está encendida") ;}
      else{  terminal.println("Jajaja dale dale") ;  luz_cuarto_mesa = 1;  digitalWrite(D3,HIGH);}
      comando_n=0;     break;
      
    case 105: // ENCENDER LUZ SALA
      if (luz_sala==1){terminal.println("La luz está encendida");}
      else{  terminal.println("Jajajaja dale dale"); luz_sala = 1;  bridge_luz_sala.digitalWrite(0,HIGH);}
      comando_n=0;     break;
      
    case 106: // ENCENDER LUZ COMEDOR
      if (luz_comedor==1){terminal.println("La luz está encendida");}
      else{  terminal.println("Jajajaja dale dale"); luz_comedor = 1;  digitalWrite(D6,HIGH);}
      comando_n=0;     break;
      
    case 121:   //ENCENDER VENTILADOR CUARTO
      if (ventilador1==1){terminal.println("El ventilador está encendido");}
      else{  terminal.println("Jajajaja dale dale"); ventilador1 = 1;  digitalWrite(D7,HIGH);}
      comando_n=0;     break;
      
    case 122:   //ENCENDER VENTILADOR CUARTO MESA
      if (ventilador2==1){terminal.println("El ventilador está encendido");}
      else{  terminal.println("Jajajaja dale dale"); ventilador2 = 1;  digitalWrite(D8,HIGH);}
      comando_n=0;     break;
      
    case 203: //ESTADO LUZ CUARTO
      if (luz_cuarto==0){terminal.println("La luz está apagada");}
      else{  terminal.println("La luz está encendida");}
      comando_n=0;     break;
      
    case 204: // ESTADO LUZ CUARTO MESA
      if (luz_cuarto_mesa==0){terminal.println("La luz está apagada");}
      else{  terminal.println("La luz está encendida");}
      comando_n=0;     break;
      
    case 205: // ENCENDER LUZ SALA
      if (luz_sala==0){terminal.println("La luz está apagada");}
      else{  terminal.println("La luz está encendida");}
      comando_n=0;     break;
      
    case 206: // ENCENDER LUZ COMEDOR
      if (luz_comedor==0){terminal.println("La luz está apagada");}
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
      terminal.print("  -sala:        ");
      if(luz_sala)terminal.println("encendida");
      else terminal.println("apagada");
      terminal.print("  -comedor:     ");
      if(luz_comedor)terminal.println("encendida");
      else terminal.println("apagada");
      comando_n=0;     break;
      
    case 221: //ESTADO VENTILADOR CUARTO
      if (ventilador1==0){terminal.println("El ventilador está apagado");}
      else{  terminal.println("El ventilador está encendido");}
      comando_n=0;     break;
      
    case 222: // ESTADO VENTILADOR CUARTO MESA
      if (ventilador2==0){terminal.println("El ventilador está apagado");}
      else{  terminal.println("El ventilador está encendido");}
      comando_n=0;     break;
      
    case 223: // ESTADO VENTILADOR TODOS
      terminal.println("Estado ventiladores:"); 
      terminal.print("  -cuarto:      ");
      if(ventilador1)terminal.println("encendido");
      else terminal.println("apagado");
      terminal.print("  -cuarto mesa: ");
      if(ventilador2)terminal.println("encendido");
      else terminal.println("apagado");
      comando_n=0;     break;
      
    case 5000: // CLEAR 
      terminal.clear();
      terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
      terminal.println(F("-------------"));
      comando_n=0;     break;
      
    case 5001: // HELP
      terminal.clear();
      terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
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
      terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
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
  // Ensure everything is sent
  terminal.flush();
}

BLYNK_CONNECTED() {
  // Synchronize time on connection
  rtc.begin();
  // Place the AuthToken of the second hardware here
  bridge_luz_sala.setAuthToken("fca9c6912d554838bc49a3d077856874"); 
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

  setSyncInterval(10 * 60); // Sync interval in seconds (10 minutes)

  // Display digital clock every 10 seconds
  //timer.setInterval(1000L, clockDisplay);

  
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);
  terminal.clear();
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(F("-------------"));
  terminal.flush();
  
//  // Setup notification button on pin 2
//  pinMode(D2, INPUT_PULLUP);
//  // Attach pin 2 interrupt to our handler
//  attachInterrupt(digitalPinToInterrupt(D2), notifyOnButtonPress, CHANGE);
}



void loop()
{
  Blynk.run();
}

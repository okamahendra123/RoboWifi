/* 
 * Mert Arduino and Tech - YouTube
 * WiFi Robot controlled by Phone (WiFibot/Android/IoT/ESP8266)
 * NodeMCU ESP8266 Tutorial 03
 * Please Subscribe for Support - https://goo.gl/RLT6DT
 */


/* include library */
#include <ESP8266WiFi.h>

/*
 * If you have no idea about this library, you can watch the tutorial below
 * NodeMCU ESP8266 Tutorial 01: Programming NodeMCU ESP-12E Using Arduino IDE
 * https://youtu.be/NtyFx1frYB0
 */

/* define port */
WiFiClient client;
WiFiServer server(80);

/* WIFI settings */
const char* ssid = "YOUR_SSID"; /* change with your ssid */
const char* password = "YOUR_PASSWORD"; /* change with your password */

/* data received from application */
String  data =""; 

/* define L298N or L293D motor control pins */

/* 1st H-BRIGDE */
int rightMotorForward = 0;   /* GPIO0(D3) -> IN1  */
int rightMotorBackward = 4;  /* GPIO4(D2) -> IN2  */
int leftMotorForward = 5;     /* GPIO5(D1) -> IN3   */
int leftMotorBackward = 16;    /* GPIO16(D0) -> IN4   */

/* 2nd H-BRIGDE */
int rightMotorCW = 15;   /* GPIO15(D8) -> IN1  */
int rightMotorCCW = 13;  /* GPIO13(D7) -> IN2  */
int leftMotorCW = 12;     /* GPIO12(D6) -> IN3   */
int leftMotorCCW = 14;    /* GPIO14(D5) -> IN4   */


/* define L298N or L293D enable pins */
int rightMotorENB = 1; /* GPIO01 -> Motor-right Enable */
int leftMotorENB = 3;  /* GPIO03(S3) -> Motor-left Enable */


void setup()
{
  /* initialize motor control pins as output */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(leftMotorBackward, OUTPUT);  
  pinMode(rightMotorBackward, OUTPUT);
  pinMode(leftMotorCW, OUTPUT);
  pinMode(rightMotorCW, OUTPUT); 
  pinMode(leftMotorCCW, OUTPUT);  
  pinMode(rightMotorCCW, OUTPUT);


  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  /* initilize serial communication */
  Serial.begin(115200);

  /* Connect to wifi*/
  connectWiFi();

  /* start server communication */
  server.begin();
}

void loop()
{
    /* If the server available, run the "checkClient" function */  
    client = server.available();
    if (!client) return; 
    data = checkClient ();

/************************ Run function according to incoming data from application *************************/

    /* If the incoming data is "forward", run the "MotorForward" function */
    if (data == "forward") MotorForward();
    /* If the incoming data is "backward", run the "MotorBackward" function */
    else if (data == "backward") MotorBackward();
    /* If the incoming data is "left", run the "TurnLeft" function */
    else if (data == "left") TurnLeft();
    /* If the incoming data is "right", run the "TurnRight" function */
    else if (data == "right") TurnRight();
    else if (data == "leftforward") MotorLeftForward();
    else if (data == "rightforward") MotorRightForward();
    else if (data == "leftbackward") MotorLeftBackward();
    else if (data == "rightbackward") MotorRightBackward();
    
    
    /* If the incoming data is "stop", run the "MotorStop" function */
    else if (data == "stop") MotorStop();
    else if (data == "stophand") MotorHandStop();
    
    else if (data == "leftcw") MotorLeftCW();
    else if (data == "leftccw") MotorLeftCCW();
    else if (data == "rightcw") MotorRightCW();
    else if (data == "rightccw") MotorRightCCW();
    

    
    
} 

/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
    digitalWrite(leftMotorENB,HIGH); 
    digitalWrite(rightMotorENB,HIGH);
    digitalWrite(leftMotorForward,HIGH);
    digitalWrite(rightMotorForward,HIGH);
    digitalWrite(leftMotorBackward,LOW);
    digitalWrite(rightMotorBackward,LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
    digitalWrite(leftMotorENB,HIGH); 
    digitalWrite(rightMotorENB,HIGH);
    digitalWrite(leftMotorForward,LOW);
    digitalWrite(rightMotorForward,LOW);
    digitalWrite(leftMotorBackward,HIGH);
    digitalWrite(rightMotorBackward,HIGH);
}


void MotorLeftForward(void)   
{
    analogWrite(leftMotorENB,900); 
    digitalWrite(rightMotorENB,HIGH);
    digitalWrite(leftMotorForward,HIGH);
    digitalWrite(rightMotorForward,HIGH);
    digitalWrite(leftMotorBackward,LOW);
    digitalWrite(rightMotorBackward,LOW);
}

void MotorRightForward(void)   
{
    analogWrite(rightMotorENB,900); 
    digitalWrite(leftMotorENB,HIGH);
    digitalWrite(leftMotorForward,HIGH);
    digitalWrite(rightMotorForward,HIGH);
    digitalWrite(leftMotorBackward,LOW);
    digitalWrite(rightMotorBackward,LOW);
}

void MotorLeftBackward(void)   
{
    analogWrite(leftMotorENB,900); 
    digitalWrite(rightMotorENB,HIGH);
    digitalWrite(leftMotorForward,LOW);
    digitalWrite(rightMotorForward,LOW);
    digitalWrite(leftMotorBackward,HIGH);
    digitalWrite(rightMotorBackward,HIGH);
}

void MotorRightBackward(void)   
{
    analogWrite(rightMotorENB,900); 
    digitalWrite(leftMotorENB,HIGH);
    digitalWrite(leftMotorForward,LOW);
    digitalWrite(rightMotorForward,LOW);
    digitalWrite(leftMotorBackward,HIGH);
    digitalWrite(rightMotorBackward,HIGH);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  analogWrite(leftMotorENB,750); 
  analogWrite(rightMotorENB,750);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
  digitalWrite(leftMotorBackward,HIGH);  
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  analogWrite(leftMotorENB,750); 
  analogWrite(rightMotorENB,750);
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  digitalWrite(leftMotorENB,LOW); 
  digitalWrite(rightMotorENB,LOW);
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

void MotorHandStop(void)
{
  digitalWrite(leftMotorCW,LOW);
  digitalWrite(leftMotorCCW,LOW);
  digitalWrite(rightMotorCW,LOW);
  digitalWrite(rightMotorCCW,LOW);
}

/********************************************* STOP *****************************************************/
void MotorLeftCW(void)   
{
  digitalWrite(leftMotorCW,HIGH);
  digitalWrite(leftMotorCCW,LOW);
  digitalWrite(rightMotorCW,LOW);
  digitalWrite(rightMotorCCW,LOW);
}

void MotorRightCW(void)   
{
  digitalWrite(leftMotorCW,LOW);
  digitalWrite(leftMotorCCW,LOW);
  digitalWrite(rightMotorCW,HIGH);
  digitalWrite(rightMotorCCW,LOW);
}

void MotorLeftCCW(void)   
{
  digitalWrite(leftMotorCW,LOW);
  digitalWrite(leftMotorCCW,HIGH);
  digitalWrite(rightMotorCW,LOW);
  digitalWrite(rightMotorCCW,LOW);
}

void MotorRightCCW(void)   
{
  digitalWrite(leftMotorCW,LOW);
  digitalWrite(leftMotorCCW,LOW);
  digitalWrite(rightMotorCW,LOW);
  digitalWrite(rightMotorCCW,HIGH);
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

/********************************** RECEIVE DATA FROM the APP ******************************************/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}

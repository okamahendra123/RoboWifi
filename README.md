# RoboWifi
ESP8266 Robo Wifi source code.
Compiled and programmed to with Arduino IDE. 

Build your own Wifi Robots:

Materials:
1. ESP8266 Board
2. L293D IC or L298 Motor driver board (H-BRIDGE)
3. Robot Chassis with Motors (I used 500 rpm motors)
4. Breadboard or PCB (If you prefer to solder)
5. 6v AA Battery Pack 

Detailed instruction:
https://www.instructables.com/id/ESP8266-Wifi-Controlled-Robot/

This is a modified ESP8266 source code to make robot has two hands.

PIN Connection:

/* 1st H-BRIGDE - WHEEL */

GPIO0(D3) -> IN1  
GPIO4(D2) -> IN2  
GPIO5(D1) -> IN3   
GPIO16(D0) -> IN4   
GPIO01 -> Motor-right Enable

GPIO03 -> Motor-left Enable 

/* 2nd H-BRIGDE - HANDS */

GPIO15(D8) -> IN1  
GPIO13(D7) -> IN2  
GPIO12(D6) -> IN3   
GPIO14(D5) -> IN4   


Enjoy it. 

Oka Mahendra

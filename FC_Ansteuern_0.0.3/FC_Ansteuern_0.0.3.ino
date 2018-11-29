/*
  ESC_Calibration
    It's important to calibrate the ESC with the values (uS / microseconds) he will expect to be for Min and Max speed.
    This one require a little procedure:  
      1 - Load the sketch to your Arduino board
      2 - Connect your ESC to the Arduino board
      3 - Power your Arduino board
      4 - Once the LED (LED_PIN) is HIGH/ON connect the power to your ESC, you have 5sec to do so
      5 - Once the LED is LOW/OFF the calibration should be done
      6 - Should now be calibrated between 1000us and 2000us
    
  27 April 2017
  by Eric Nantel
  
  Servo & Knob links
  http://www.arduino.cc/en/Tutorial/Knob
  http://people.interaction-ivrea.it/m.rinott
 */
#include "ESC.h"
#define LED_PIN (13)              // Pin for the LED 

int t = 100;
int thr_s = 1100;
int rud_p = 1500;
int ail_p = 1500;
int ele_p = 1500;

int thr_s_last = 0;
int rud_p_last = 0;
int ail_p_last = 0;
int ail_p_last = 0;

int max_thr_s = 1500;
int curspd = 0;
int spd = 0;

ESC thr (9, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC rud (10, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC ail (6, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC ele (5, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC aux (11, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
//1100 = -100; 1900=+100; 1500=0;
  
void setup() {
  Serial.begin(9600);
  Serial.println("Starting the Autocopter ---");
  pinMode(LED_PIN, OUTPUT);       // LED Visual Output (can be removed)
  digitalWrite(LED_PIN, HIGH);    // LED High while signal is High (can be removed)
  caliball();
  stopall();
  digitalWrite(LED_PIN, LOW);     // LED Low when the calibration is done (can be removed)
}

void loop() {
 // ARM
 arming();
 
 // Starting  
 Serial.println("Starting...");
 for(thr_s = 1100; thr_s <= max_thr_s; thr_s += 1){
  motorspeed(thr_s, rud_p, ail_p, ele_p);
  //Serial.println(thr_s);
  delay(10);
 }
 
 // Starting done going to try hover
 Serial.println("++++++++++++++++++++++++++++++++++++");
 Serial.println("Starting done");
 Serial.println("might rise higher and higher and fly away!!!");
 Serial.println("Going to unsecure Hovering...");
 motorspeed(thr_s, rud_p, ail_p, ele_p);
 delay(10000);
 stopall();
 delay(10000);
 
// Disarm
disarm(); 
}
//--------------------------------------------------------------
//------------------ Motorspeed ------------------------------
void motorspeed(int thr_s, int rud_p, int ail_p, int ele_p){
  thr.speed(thr_s);
  Serial.println(thr_s);
  rud.speed(rud_p);
  Serial.println(rud_p);
  ail.speed(ail_p);
  Serial.println(ail_p);
  ele.speed(ele_p);
  Serial.println(ele_p);
}
//------------------- CALIBALL -------------------------------
void caliball(){
  thr.calib();                  
  rud.calib(); 
  ail.calib();                  
  ele.calib();                
}

//-------------------- STOP ----------------------------------
void stopall(){
  thr.stop(); 
  rud.stop();
  ail.stop(); 
  ele.stop();
}

//-------------------- ARM ----------------------------------
void arming(){
 Serial.println("Arming....");
 motorspeed(1100, 1100, 1500, 1500);
 delay(1000);
 Serial.println("Arming done!");
}

//-------------------- Disarm ---------------------------------
void disarm(){
 Serial.println("Disarming....");
 motorspeed(1100, 1900, 1500, 1500);
 Serial.println("Disarming done!");
 delay(1000);
}

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
int rud_s = 1900;

ESC thr (9, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC rud (10, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC ail (11, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC ele (5, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
ESC aux (6, 1100, 1900, 500);   // ESC_Name (ESC PIN, Minimum Value, Maximum Value, Arm Value)
//1100 = -100; 1900=+100; 1500=0;
  
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);       // LED Visual Output (can be removed)
  digitalWrite(LED_PIN, HIGH);    // LED High while signal is High (can be removed)
  thr.calib();                  // Calibration of the Max and Min value the ESC is expecting
  rud.calib(); // Stop the ESC to avoid damage or injuries
  thr.stop(); 
  rud.stop(); 
  digitalWrite(LED_PIN, LOW);     // LED Low when the calibration is done (can be removed)
}

void loop() {
 motorspeed(1100, 1100, 1100, 1100);
}

void motorspeed(int thr_s, int rud_s, int ail_s, int ele_s){
  thr.speed(thr_s);
  Serial.println(thr_s);
  rud.speed(rud_s);
  Serial.println(rud_s);
  ail.speed(ail_s);
  Serial.println(ail_s);
  ele.speed(ele_s);
  Serial.println(ele_s);
}

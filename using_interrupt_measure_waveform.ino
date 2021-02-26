/* How to use interrupts to measure the period of a square wave input
 *  
 *  Features:
 *    - Duty Cycle independent
 * 
 * 
 * 
 * Written by Declan Heard
 * 
 * 26/02/2021
 * 
 */



#define INPUT_PIN 2




bool detect_high;
bool have_detected;


void setup() {
  Serial.begin(115200);
  pinMode (INPUT_PIN, INPUT);
  attachInterrupt (digitalPinToInterrupt (INPUT_PIN), isr , CHANGE);   // interrupt 0 is pin 2
}



uint32_t detected_high;
uint32_t detected_low;
uint32_t period_high;
uint32_t period_low;
uint32_t period_total;

void loop() {
  if (have_detected) {
    if (detect_high) {
      detected_high = millis();
      period_high =  detected_high - detected_low;
    } else {
      detected_low = millis();
      period_low =  detected_low - detected_high;      
    }
    period_total = period_high + period_low;
    Serial.println(period_total);
    have_detected = false;
  }
}




void isr () {
  if (digitalRead(INPUT_PIN)) {
    detect_high = true;
  } else {
    detect_high = false;
  }
  have_detected = true;
}

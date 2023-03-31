#include <TB6612_ESP32.h>

/*pinout 
 * motor A: in1 = 12, in2 = 13, PWM 14
 *  encoder: c1 = 15,  c2 = 16
 *  
 * motor B: in1 = 25, in2 = 26, PWM 2
 *  encoder: c1 = 17,  c2 = 18
 *  
 * mpu6050: scl = 22, sda = 21
 * 
 * led: 19
*/

// - OUTPUT PINS -
#define AIN1 12 // ESP32 Pin D13 to TB6612FNG Pin AIN1
#define BIN1 25 // ESP32 Pin D12 to TB6612FNG Pin BIN1
#define AIN2 13 // ESP32 Pin D14 to TB6612FNG Pin AIN2
#define BIN2 26 // ESP32 Pin D27 to TB6612FNG Pin BIN2
#define PWMA 14 // ESP32 Pin D26 to TB6612FNG Pin PWMA
#define PWMB 2  // ESP32 Pin D25 to TB6612FNG Pin PWMB
#define STBY 33 // ESP32 Pin D33 to TB6612FNG Pin STBY

#define SCL 22 // SCL pin connected to mpu
#define SDA 21 // SDA pin connected to mpu
#define LED 19

// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

Motor m1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY,5000 ,8,1 );
Motor m2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY,5000 ,8,2 );

void setup() {
  // motors input
//  pinMode(AIN1, OUTPUT);
//  pinMode(AIN2, OUTPUT);
//  pinMode(BIN1, OUTPUT);
//  pinMode(BIN2, OUTPUT);
//
//  pinMode(PWMA, OUTPUT);
//  pinMode(PWMB, OUTPUT);
}

void loop() {
  m1.drive(200);
  m2.drive(200);
  delay(1000);

  m1.break();
  m2.break();
}

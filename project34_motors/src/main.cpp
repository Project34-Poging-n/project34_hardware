#include <Arduino.h>
#include <Stepper.h>

#define STEPPER_A_PIN_1         0
#define STEPPER_A_PIN_2         1
#define STEPPER_A_PIN_3         2
#define STEPPER_A_PIN_4         3
#define STEPPER_B_PIN_1         4
#define STEPPER_B_PIN_2         5
#define STEPPER_B_PIN_3         6
#define STEPPER_B_PIN_4         7
#define STEPPER_C_PIN_1         8
#define STEPPER_C_PIN_2         9
#define STEPPER_C_PIN_3         10
#define STEPPER_C_PIN_4         11

#define STEPS_PER_REVOLUTION    1048


String yomama;
int result[15] = {0};
int *lalala = nullptr;
int divs[3] = { 50, 20, 5 };

/*
  Stepper motor A is voor het 50 euro biljet
  Stepper motor B is voor het 20 euro biljet
  Stepper motor C is voor het 
*/
Stepper stepperA = Stepper(STEPS_PER_REVOLUTION, STEPPER_A_PIN_1, STEPPER_A_PIN_2, STEPPER_A_PIN_3, STEPPER_A_PIN_4);
Stepper stepperB = Stepper(STEPS_PER_REVOLUTION, STEPPER_B_PIN_1, STEPPER_B_PIN_2, STEPPER_B_PIN_3, STEPPER_B_PIN_4);
Stepper stepperC = Stepper(STEPS_PER_REVOLUTION, STEPPER_C_PIN_1, STEPPER_C_PIN_2, STEPPER_C_PIN_3, STEPPER_C_PIN_4);


/**
 * Function to chop a number in a selection of smaller numbers
 * 
 * @param number
 * @param dividers
 * @param last_divider
 * @return int
*/
int *chop_number_smaller(int number, int *dividers, int last_divider)
{   
    int rest = number;

    int rp = 0;
    int dp = 0;
    
    while (rest != 0) {
        if (rest > dividers[dp]) {
            int temp = rest;
            rest = rest % dividers[dp];
            int total = (temp - rest) / dividers[dp];
            for (int i = 0; i < total; i++) {
                result[rp] = dividers[dp];
                rp++;
            }
        } else if (rest < dividers[dp]) {
            if (dividers[dp] == last_divider) {
                rest = rest + last_divider - rest;
            } else {
                dp++;    
            }
        } else {
            result[rp] = dividers[dp];
            rest = rest % dividers[dp];
            rp++;
        }
    }
       
    return result;
}


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  // init steppers
  stepperA.setSpeed(5);
  stepperB.setSpeed(5);  
  stepperC.setSpeed(5);
}


void loop() 
{
  yomama = "";
  // put your main code here, to run repeatedly:
  if (Serial.available()) {
    char n = Serial.read();
    yomama+=n;

    Serial.println(yomama.toInt());

    // if (yomama.endsWith("\r") || yomama.endsWith("\n")) {
    //   Serial.println("[info]\tsend: " + yomama);
    // }
  }

  if (yomama.toInt() != 0) {
    lalala = chop_number_smaller(yomama.toInt(), divs, 5);

    Serial.print("[");
    for (int i = 0; i < 10; i++) {
      Serial.print(lalala[i]);
      Serial.print(", ");
    }
    Serial.println("]");

    for (int i = 0; i < 10; i++) {
      if (lalala[i] != 0) {
        switch (lalala[i])
        {
          case 50: 
            stepperA.step(STEPS_PER_REVOLUTION);
            break;
          case 20:
            stepperB.step(STEPS_PER_REVOLUTION);
            delay(500);
            break;
          case 5:
            stepperC.step(STEPS_PER_REVOLUTION);
            delay(500);
            break;
        }
      }
    }
  }
}
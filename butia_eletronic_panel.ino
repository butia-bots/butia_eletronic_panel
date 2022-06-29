/*
 * Low Voltage Cutoff code
 * FurgBot Team, @home category - FURG
 * Author: Luís Felipe Milczarek Quadros
 * e-mail: luis.milczarek@hotmail.com
 * license: ?????
 */

#define V_MAX 27.7272727273
#define POT_MAX V_MAX
#define POT_MIN 24
#define POT_INPUT_PIN A1
#define RELAY_OUTPUT 13
#define SET_PIN 2
#define RESET_PIN 3
#define VOLTAGE_METER A0

bool state = false;
float targetVoltage = 0.0f;

void setup() {
  pinMode(RELAY_OUTPUT, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(SET_PIN), setInterrupt, RISING);
  attachInterrupt(digitalPinToInterrupt(RESET_PIN), resetInterrupt, RISING);
  digitalWrite(RELAY_OUTPUT, HIGH);
}

void loop() {
  if(state)
  {
    if(floatMap(analogRead(VOLTAGE_METER), 0.0f, 1023.0f, 0.0f, V_MAX) < targetVoltage)
    {
      digitalWrite(RELAY_OUTPUT, LOW);
    }
    else
    {
      digitalWrite(RELAY_OUTPUT, HIGH);
    }
  }

  Serial.print("Baterry Voltage = ");
  Serial.print(floatMap(analogRead(VOLTAGE_METER), 0.0f, 1023.0f, 0.0f, V_MAX));
  Serial.print("V, CutOff voltage = ");
  Serial.print(targetVoltage);
  Serial.print(", New CutOff voltage = ");
  Serial.print(floatMap(analogRead(POT_INPUT_PIN), 0, 1023, POT_MIN, POT_MAX));
  Serial.print("V, State = ");
  if(state)
  {
    Serial.println("ON");
  }
  else
  {
    Serial.println("OFF");
  }
  
  delay(100);
}

void setInterrupt()
{
  targetVoltage = floatMap(analogRead(POT_INPUT_PIN), 0, 1023, POT_MIN, POT_MAX);
  state = true;
}

void resetInterrupt()
{
  state = false;
  targetVoltage = 0.0f;
  digitalWrite(RELAY_OUTPUT, HIGH);
}

float floatMap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

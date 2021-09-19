#include <Arduino.h>

unsigned turnCount;
unsigned lastTurnAt;
unsigned lastReported;

void IRAM_ATTR onTurn()
{
  unsigned now = millis();
  if (now != lastTurnAt){
    turnCount += 1; 
    lastTurnAt = now;
  }
}

void RPM()
{
  unsigned now = millis();
  unsigned elapsedMillis = now - lastReported;
  if (elapsedMillis == 0){
    return;
  }
  double rpm = (turnCount * 1000 * 60) / elapsedMillis;
  Serial.printf("%u turns in %u millis: %f rpm\n", turnCount, elapsedMillis, rpm);
  turnCount = 0;
  lastReported = now;
}

void setup()
{
  turnCount = 0;
  lastReported = millis();
  lastTurnAt = lastReported;
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(D2), onTurn, RISING);

}


void loop()
{
  RPM();
  delay(1000);
}

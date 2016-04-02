#include "Touchpad.h"

Touchpad TP;
void setup()
{
  Serial.begin(115200);
  TP.begin();
  Serial.print("End Setup");
  TP.setPW("1111");
}

void loop()
{
  TP.updateData();
  if(TP.isPWAccepted())
  {
    Serial.print("Password was accepted");
    delay(1000);
    TP.setPWAcceptedFalse();
  }
}


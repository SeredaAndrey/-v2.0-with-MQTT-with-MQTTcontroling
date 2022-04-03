
#include "set_library.h"
#include "Const_variable.h"


void loop ()
{
  currentMillis = millis();
  PressKeys();
  handleMQTT ();
  Activate_init();
  Led_init();
  HTTP.handleClient();
  ds18b20_read();
  SendData();
  delay (1);
  dnsServer.processNextRequest();
  ResetESP();
}

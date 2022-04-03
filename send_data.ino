void SendData ()
{
  if ( currentMillis - SendDataMillis > SendDataInterval )
  {
    SendDataMillis = currentMillis;
    Serial.println ( "attempt to send to MQTT" );
    MQTTcall ();
    if ( flagFailMQTTconnect == 1 && flagActivURLcontrols == "1" ) 
    { 
      SendTemperature ();
      sendActivity ();
    }
  }
}

String getURL (String urls)
{
  String answer = "";
  HTTPClient http;
  http.begin ( urls );
  int httpCode = http.GET ();
  if ( httpCode == HTTP_CODE_OK )
  {
    answer = http.getString ();
  }
  http.end ();
  return answer;
}

void SendTemperature ()
{
  String urls = "http://";
  urls += IPRoomHost;
  urls += "/Temperature" + NumberOfHomeSystemController + "?Temperature" + NumberOfHomeSystemController + "=" + _Tnow;
  getURL(urls);
}
void sendActivity ()
{
  int _Activate;
  if      ( ( Activate == 1 && Mode == 1 ) || Mode == 2 ) _Activate = 1;
  else if ( ( Activate == 0 && Mode == 1 ) || Mode == 3 ) _Activate = 0;
  String urls = "http://";
  urls += IPBoolerHost;
  urls += "/Activity" + NumberOfHomeSystemController + "?Activity" + NumberOfHomeSystemController + "=" + _Activate;
  getURL(urls);
}

void WIFIinit() 
{
  HTTP.on ( "/Temperature", HTTP_GET, []()             // --------------------Получаем Tmax, deltaT & flagControllTemp со страницы
  {
    jsonWrite ( SetupMode, "Tmax", HTTP.arg ( "Tmax" ) );
    jsonWrite ( SetupMode, "deltaT", HTTP.arg ( "deltaT" ) );
    _Tmax = HTTP.arg ( "Tmax" ); Tmax = atof ( _Tmax.c_str () );
    _deltaT = HTTP.arg ( "deltaT" ); deltaT = atof ( _deltaT.c_str () );
    saveSetupMode ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/flagControllTemp", HTTP_GET, []()             // --------------------Получаем Tmax, deltaT & flagControllTemp со страницы
  {
    jsonWrite ( SetupMode, "flagControllTemp", HTTP.arg ( "flagControllTemp" ) );
    String _flagControllTemp = HTTP.arg ( "flagControllTemp" ); flagControllTemp = _flagControllTemp.toInt();
    saveSetupMode ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/Commands", HTTP_GET, []()                 // --------------------Получаем ComandON & ComandOFF со страницы
  {
    jsonWrite ( Names, "ComandON", HTTP.arg ( "ComandON" ) );
    jsonWrite ( Names, "ComandOFF", HTTP.arg ( "ComandOFF" ) );
    ComandON = HTTP.arg ( "ComandON" );
    ComandOFF = HTTP.arg ( "ComandOFF" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/IPRoomHost", HTTP_GET, []()                 // --------------------Получаем IPRoomHost со страницы
  {
    jsonWrite ( IPadresses, "IPRoomHost", HTTP.arg ( "IPRoomHost" ) );
    IPRoomHost = HTTP.arg ( "IPRoomHost" ); 
    saveIPs ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/IPBoolerHost", HTTP_GET, []()                 // --------------------Получаем MQTTip со страницы
  {
    jsonWrite ( IPadresses, "IPBoolerHost", HTTP.arg ( "IPBoolerHost" ) );
    IPBoolerHost = HTTP.arg ( "IPBoolerHost" ); 
    saveIPs ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/flagActivURLcontrols", HTTP_GET, []()   // --------------------Получаем flagActivURLcontrols со страницы
  {
    jsonWrite ( Variables, "flagActivURLcontrols", HTTP.arg ( "flagActivURLcontrols" ) );
    flagActivURLcontrols = HTTP.arg ( "flagActivURLcontrols" ); 
    saveVariables ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/NumberOfHomeSystemController", HTTP_GET, []()   // --------------------Получаем flagActivURLcontrols со страницы
  {
    jsonWrite ( Names, "NumberOfHomeSystemController", HTTP.arg ( "NumberOfHomeSystemController" ) );
    NumberOfHomeSystemController = HTTP.arg ( "NumberOfHomeSystemController" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/MQTTip", HTTP_GET, []()                 // --------------------Получаем MQTTip со страницы
  {
    jsonWrite ( IPadresses, "MQTTip", HTTP.arg ( "MQTTip" ) );
    _MQTTip = HTTP.arg ( "MQTTip" ); 
    saveIPs ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/topics", HTTP_GET, []()               // --------------------Получаем pubtopic & subtopic со страницы
  {
    jsonWrite ( Names, "pubtopic", HTTP.arg ( "pubtopic" ) );
    pubtopic = HTTP.arg ( "pubtopic" ); 
    jsonWrite ( Names, "subtopic", HTTP.arg ( "subtopic" ) );
    subtopic = HTTP.arg ( "subtopic" ); 
    jsonWrite ( Names, "hosttopic", HTTP.arg ( "hosttopic" ) );
    hosttopic = HTTP.arg ( "hosttopic" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssdp", HTTP_GET, []()                   // --------------------Получаем SSDP со страницы
  {
    jsonWrite ( Names, "ssdp", HTTP.arg ( "ssdp" ) );
    SSDP_Name = HTTP.arg ( "ssdp" ); 
    saveNames ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
  HTTP.on ( "/ssid", HTTP_GET, []()               // --------------------Получаем SSDP со страницы
  {
    jsonWrite ( Autorisation, "ssid", HTTP.arg ( "ssid" ) );
    jsonWrite ( Autorisation, "password", HTTP.arg ( "password" ) );
    ssid = HTTP.arg ( "ssid" ); password = HTTP.arg ( "password" );
    saveAutorisation ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
  });
 
  HTTP.on ( "/ssidap", HTTP_GET, []()             // --------------------Получаем SSDP со страницы  
  {
    jsonWrite ( Autorisation, "ssidAP", HTTP.arg ( "ssidAP"   ));
    jsonWrite ( Autorisation, "passwordAP", HTTP.arg ( "passwordAP" ) );
    ssidAP = HTTP.arg ( "ssidAP" ); passwordAP = HTTP.arg ( "passwordAP" );
    saveAutorisation ();                
    HTTP.send(200, "text/plain", "OK"); 
  });
  HTTP.on ( "/Mode", HTTP_GET, []() 
  {
    jsonWrite ( SetupMode, "Mode", HTTP.arg ( "Mode" ) );
    saveSetupMode ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
    String ModeS = HTTP.arg ( "Mode" ); Mode = ModeS.toInt ();
  });
  HTTP.on ( "/Activate", HTTP_GET, []() 
  {
    jsonWrite ( Variables, "Activate", HTTP.arg ( "Activate" ) );
    saveVariables ();                 
    HTTP.send ( 200, "text/plain", "OK" ); 
    String ActivateS = HTTP.arg ( "Activate" ); Activate = ActivateS.toInt ();
  }); 
  HTTP.on("/invertActivate", HTTP_GET, []() 
  {
    jsonWrite ( SetupMode, "invertActivate", HTTP.arg ( "invertActivate" ) );
    saveSetupMode ();                
    HTTP.send ( 200, "text/plain", "OK" ); 
    String invertActivateS = HTTP.arg ( "invertActivate" ); invertActivate = invertActivateS.toInt ();
  }); 
  // Попытка подключения к точке доступа
  WiFi.mode(WIFI_STA);
  byte tries = 11;
  if (ssid == "" && password == "" ) 
  {
    WiFi.begin();
  }
  else 
  {   
    WiFi.begin(ssid.c_str(), password.c_str());
  }
  while (--tries && WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(1000);
  }
  if (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("");
    Serial.println("WiFi up AP");
    StartAPMode();
  }
  else 
  {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
}

bool StartAPMode() 
{
  IPAddress apIP(192, 168, 4, 1);
  IPAddress staticGateway(192, 168, 4, 1);
  IPAddress staticSubnet(255, 255, 255, 0);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, staticGateway, staticSubnet);
  ssidAP = jsonRead ( Autorisation, "ssidAP" ); Serial.print ("Loading from SPIFFS ssidAP = "); Serial.println( ssidAP );
  passwordAP = jsonRead ( Autorisation, "passwordAP" ); Serial.print ("Loading from SPIFFS passwordAP = "); Serial.println( passwordAP );
  WiFi.softAP ( ssidAP.c_str(), passwordAP.c_str() );
  Mode = 2;
  ResetFlag = 1;
  ResetESPMillis = currentMillis;
  return true;
}

void ResetESP ()
{
  if ( ResetFlag == 1 )
  {
    if ( currentMillis - ResetESPMillis > ResetESPInterval)
    {
       ESP.restart();
    }
  }
}

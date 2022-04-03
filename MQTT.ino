// mosquitto_pub -h localhost -t "SmartHome/Living-Rooms/Room-Controller/Temperature" -m 21.0 сделать публикацию в топике
// mosquitto_sub -h localhost -t "SmartHome/Living-Rooms/Room-Controller/Activate"            подписаться на топик              

void handleMQTT ()
{
  IPAddress ip_MQTTip ( MQTTip[0], MQTTip[1], MQTTip[2], MQTTip[3] ); 
  String _topic = "/SmartHome"; _topic += pubtopic; _topic += subtopic;
  String _topicActiv = _topic + "/Activate";
  String _topicMode = _topic + "/Mode";
  String _topicInvAct = _topic + "/InvertActivate";
  String _topicTempAct = _topic + "/TempActivate"; 
  String _topicdTempAct = _topic + "/dTempActivate";
  String _topicControlTemp = _topic + "/ControlTemp";  
  if ( WiFi.status () == WL_CONNECTED )
  {
    PubSubClient client(ip_MQTTip, 1883, wclient);
    //Serial.println ( "Connect to WiFi - ACCEPT" );
    if ( !client.connected () )
    {
      //Serial.println ( "Connect to MQTT - ACCEPT" );
    if ( client.connect ( SSDP_Name ) )
      {
        client.set_callback ( callback );
        client.subscribe ( _topicActiv );
        client.subscribe ( _topicMode );
        client.subscribe ( _topicInvAct );
        client.subscribe ( _topicTempAct );
        client.subscribe ( _topicdTempAct );
        client.subscribe ( _topicControlTemp );
      }
    }
    else flagFailMQTTconnect = 1;
    if ( client.connected () )
    {
      client.loop ();
    }
    SendData ();
  }
}

void MQTTcall ()
{
  String _Activate; String _ActivateForHost = NumberOfHomeSystemController; 
  String _Mode;
  String _invertActivate;
  String _flagControllTemp;
  String _topic = "/SmartHome"; _topic += pubtopic; _topic += subtopic;
  String _topicTemp = _topic + "/temperature";
  String _topicActivForHost = "/SmartHome"; _topicActivForHost += hosttopic;
        if      ( ( Activate == 0 && Mode == 1 ) || Mode == 3 ) { _ActivateForHost += "-"; _ActivateForHost += ComandOFF;}
        else if ( ( Activate == 1 && Mode == 1 ) || Mode == 2 ) { _ActivateForHost += "-"; _ActivateForHost += ComandON;}
  String _topicActiv = _topic + "/Activate"; 
        if      ( Activate == 0 )       _Activate = "0";//"Device inactive"; 
        else if ( Activate == 1 )       _Activate = "1";//"Device active"; 
        else                            _Activate = "wrong status active";
  String _topicMode = _topic + "/Mode"; 
        if      ( Mode == 1 )           _Mode = "1";//"Automatic mode"; 
        else if ( Mode == 2 )           _Mode = "2";//"Always on"; 
        else if ( Mode == 3 )           _Mode = "3";//"Always off"; 
        else                            _Mode = "wrong status mode";
  String _topicInvAct = _topic + "/InvertActivate"; 
        if      ( invertActivate == 0 ) _invertActivate = "0";//"Invert mode inactive"; 
        else if ( invertActivate == 1 ) _invertActivate = "1";//"Invert mode active"; 
        else                            _invertActivate = "wrong status invertactive";
  String _topicTempAct = _topic + "/TempActivate"; 
  String _topicdTempAct = _topic + "/dTempActivate";
  String _topicControlTemp = _topic + "/ControlTemp";
        if      ( flagControllTemp == 0 ) _flagControllTemp = "0";//"ControllTemp mode inactive"; 
        else if ( flagControllTemp == 1 ) _flagControllTemp = "1";//"ControllTemp mode active"; 
        else                              _flagControllTemp = "wrong status flagControllTemp";
  Serial.print   ( "Connect to MQTT with SSDP_Name "    ); Serial.print ( SSDP_Name  ); Serial.println ( " - ACCEPT" ); flagFailMQTTconnect = 0;
  client.publish ( _topicTemp,                    _Tnow ); Serial.print ( "Publish " ); Serial.print ( _topicTemp         ); Serial.print ( " " ); Serial.println ( _Tnow            );
  //client.publish ( _topicActiv,               _Activate ); Serial.print ( "Publish " ); Serial.print ( _topicActiv        ); Serial.print ( " " ); Serial.println ( _Activate        );
  client.publish ( _topicActivForHost, _ActivateForHost ); Serial.print ( "Publish " ); Serial.print ( _topicActivForHost ); Serial.print ( " " ); Serial.println ( _ActivateForHost );
  client.publish ( _topicMode,                    _Mode ); Serial.print ( "Publish " ); Serial.print ( _topicMode         ); Serial.print ( " " ); Serial.println ( _Mode            );
  client.publish ( _topicInvAct,        _invertActivate ); Serial.print ( "Publish " ); Serial.print ( _topicInvAct       ); Serial.print ( " " ); Serial.println ( _invertActivate  );
  client.publish ( _topicTempAct,                 _Tmax ); Serial.print ( "Publish " ); Serial.print ( _topicTempAct      ); Serial.print ( " " ); Serial.println ( Tmax             );
  client.publish ( _topicdTempAct,              _deltaT ); Serial.print ( "Publish " ); Serial.print ( _topicdTempAct     ); Serial.print ( " " ); Serial.println ( deltaT           );
  client.publish ( _topicControlTemp, _flagControllTemp ); Serial.print ( "Publish " ); Serial.print ( _topicControlTemp  ); Serial.print ( " " ); Serial.println ( _flagControllTemp);
  client.set_callback ( callback );
 /* client.subscribe ( _topicActiv );
  client.subscribe ( _topicMode );
  client.subscribe ( _topicInvAct );
  client.subscribe ( _topicTempAct );
  client.subscribe ( _topicdTempAct );
  client.subscribe ( _topicControlTemp );*/
//  Serial.println ( client.subscribe ( _topicActiv ) );
  flagFailMQTTconnect = 0;
}

void callback(const MQTT::Publish& pub) 
//void callback() 
{
  String _topic = "/SmartHome"; _topic += pubtopic; _topic += subtopic;
  String _topicActiv = _topic + "/Activate"; 
  String _topicMode = _topic + "/Mode";
  String _topicInvAct = _topic + "/InvertActivate";
  String _topicTempAct = _topic + "/TempActivate"; 
  String _topicdTempAct = _topic + "/dTempActivate";
  String _topicControlTemp = _topic + "/ControlTemp";
  String payload = pub.payload_string();
  String Variable;
  if ( String ( pub.topic () ) == _topicActiv )                                         // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    if      ( Variable == ComandON   ) 
    { 
      Activate = 1; 
      jsonWrite ( Variables, "Activate", Activate ); 
      saveVariables (); 
      Serial.println ( Variable ); 
    }
    else if ( Variable == ComandOFF ) 
    { 
      Activate = 0; 
      jsonWrite ( Variables, "Activate", Activate ); 
      saveVariables ();
      Serial.println ( Variable );  
    }
  }
  if ( String ( pub.topic () ) == _topicMode )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    if ( Variable == "1" ) 
    { 
      Mode = 1; 
      jsonWrite ( SetupMode, "Mode", "1" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
    else if ( Variable == "2" ) 
    { 
      Mode = 2; 
      jsonWrite ( SetupMode, "Mode", "2" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
    else if ( Variable == "0" ) 
    { 
      Mode = 0; 
      jsonWrite ( SetupMode, "Mode", "0" ); 
      saveSetupMode ();
      Serial.println ( Mode );  
    }
  }
  if ( String ( pub.topic () ) == _topicInvAct )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    if ( Variable == "1" ) 
    { 
      invertActivate = 1; 
      jsonWrite ( SetupMode, "invertActivate", "1" ); 
      saveSetupMode ();
      Serial.println ( invertActivate );  
    }
    else if ( Variable == "0" ) 
    { 
      invertActivate = 0; 
      jsonWrite ( SetupMode, "invertActivate", "0" ); 
      saveSetupMode ();
      Serial.println ( invertActivate );  
    }
  }
  if ( String ( pub.topic () ) == _topicTempAct )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    _Tmax = Variable;
    Tmax = atof ( Variable.c_str () );
    jsonWrite ( SetupMode, "Tmax", Variable );
    saveSetupMode ();
  }
  if ( String ( pub.topic () ) == _topicdTempAct )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    _deltaT = Variable;
    deltaT = atof ( Variable.c_str () );
    jsonWrite ( SetupMode, "deltaT", Variable );
    saveSetupMode ();
  }
  if ( String ( pub.topic () ) == _topicControlTemp )                                          // Проверяем из нужного ли нам топика пришли данные
  {
    Variable = payload;                                                                 // Преобразуем полученные данные 
    Serial.print ( "Incoming mesage " ); Serial.print ( Variable );                     // Отправляем данные по COM порту 
    if ( Variable == "1" ) 
    { 
      flagControllTemp = 1; 
      jsonWrite ( SetupMode, "flagControllTemp", "1" ); 
      saveSetupMode ();
      Serial.println ( flagControllTemp );  
    }
    else if ( Variable == "0" ) 
    { 
      flagControllTemp = 0; 
      jsonWrite ( SetupMode, "flagControllTemp", "0" ); 
      saveSetupMode ();
      Serial.println ( flagControllTemp );  
    }
  }
}

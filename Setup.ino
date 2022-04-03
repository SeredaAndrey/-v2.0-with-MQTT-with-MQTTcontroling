void setup()
{
  pinMode(PinRelay, OUTPUT);
  pinMode(PinLed, OUTPUT);
  pinMode(PinButtons, INPUT_PULLUP);
  Wire.begin();
  Serial.begin(115200);
  Serial.println("");
  Serial.println("Start FS");          FS_init();
  Serial.println("Loading 'Setup.json'");  SetupMode = readFile("SetupMode.json", 4096);  
  Serial.println("Loading 'Names.json'");  Names = readFile("Names.json", 4096);  
  Serial.println("Loading 'Autorisation.json'");  Autorisation = readFile("Autorisation.json", 4096);  
  Serial.println("Loading 'Variables.json'");  Variables = readFile("Variables.json", 4096);  
  Serial.println("Loading 'IPadresses.json'");  IPadresses = readFile("IPadresses.json", 4096);  
  LoadVariable ();
  Serial.println("Start WIFI");        WIFIinit();
  Serial.println("Start begin Time");  Time_init(); 
  Serial.println("Start SSDP");        SSDP_init();
  Serial.println("Start WebServer");   HTTP_init();
  Serial.println("Load Mode Work");    HTTP_init();

}

void LoadVariable ()
{
  _MQTTip = jsonRead ( IPadresses, "MQTTip" ); Serial.print ("Loading from SPIFFS MQTTip = "); Serial.println( _MQTTip );
  SSDP_Name = jsonRead ( Names, "ssdp" ); Serial.print ("Loading from SPIFFS SSDP_Name = "); Serial.println( SSDP_Name );
  pubtopic = jsonRead ( Names, "pubtopic" ); Serial.print ("Loading from SPIFFS pubtopic = "); Serial.println( pubtopic );
  subtopic = jsonRead ( Names, "subtopic" ); Serial.print ("Loading from SPIFFS subtopic = "); Serial.println( subtopic );
  hosttopic = jsonRead ( Names, "hosttopic" ); Serial.print ("Loading from SPIFFS hosttopic = "); Serial.println( hosttopic );
  Mode = jsonReadtoInt ( SetupMode, "Mode" ); Serial.print ("Loading from SPIFFS Mode = "); Serial.println( Mode );
  Activate = jsonReadtoInt ( Variables, "Activate" ); Serial.print ("Loading from SPIFFS Activate = "); Serial.println( Activate );
  invertActivate = jsonReadtoInt ( SetupMode, "invertActivate" ); Serial.print ("Loading from SPIFFS invertActivate = "); Serial.println( invertActivate );
  ssid = jsonRead ( Autorisation, "ssid" ); Serial.print ("Loading from SPIFFS ssid = "); Serial.println( ssid );
  password = jsonRead ( Autorisation, "password" ); Serial.print ("Loading from SPIFFS password = "); Serial.println( password );
  IPRoomHost = jsonRead ( IPadresses, "IPRoomHost" ); Serial.print ("Loading from SPIFFS IPRoomHost = "); Serial.println( IPRoomHost );
  IPBoolerHost = jsonRead ( IPadresses, "IPBoolerHost" ); Serial.print ("Loading from SPIFFS IPBoolerHost = "); Serial.println( IPBoolerHost );
  NumberOfHomeSystemController = jsonRead ( Names, "NumberOfHomeSystemController" ); Serial.print ("Loading from SPIFFS NumberOfHomeSystemController = "); Serial.println( NumberOfHomeSystemController );
  flagActivURLcontrols = jsonReadtoInt ( Variables, "flagActivURLcontrols" ); Serial.print ("Loading from SPIFFS flagActivURLcontrols = "); Serial.println( flagActivURLcontrols );
  ComandON = jsonRead ( Names, "ComandON" ); Serial.print ("Loading from SPIFFS ComandON = "); Serial.println( ComandON );
  ComandOFF = jsonRead ( Names, "ComandOFF" ); Serial.print ("Loading from SPIFFS ComandOFF = "); Serial.println( ComandOFF );
  _Tmax = jsonRead ( SetupMode, "Tmax" ); Tmax = atof ( _Tmax.c_str () ); Serial.print ("Loading from SPIFFS Tmax = "); Serial.println( Tmax );
  _deltaT = jsonRead ( SetupMode, "deltaT" ); deltaT = atof ( _deltaT.c_str () ); Serial.print ("Loading from SPIFFS deltaT = "); Serial.println( deltaT );
  flagControllTemp = jsonReadtoInt ( SetupMode, "flagControllTemp" ); Serial.print ("Loading from SPIFFS flagControllTemp = "); Serial.println( flagControllTemp );
  String ip = _MQTTip; 
  int i = ip.indexOf( "." );                                                                    String _ip = ip.substring( 0, i ); MQTTip [ 0 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 1 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 2 ] = _ip.toInt();
      i = ip.indexOf( "." ); _ip = ip.substring( 1, i+1 ); ip.replace(_ip, ""); i = ip.indexOf( "." ); _ip = ip.substring( 1, i ); MQTTip [ 3 ] = _ip.toInt();
  IPAddress ip_MQTTip ( MQTTip[0], MQTTip[1], MQTTip[2], MQTTip[3] ); 
  Serial.print ( MQTTip[0] ); Serial.print ( "," ); Serial.print ( MQTTip[1] ); Serial.print ( "," ); Serial.print ( MQTTip[2] ); Serial.print ( "," ); Serial.println ( MQTTip[3] );
}

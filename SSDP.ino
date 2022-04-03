void SSDP_init (void) 
{
  SSDP.setSchemaURL ( "description.xml" );
  SSDP.setHTTPPort (80);
  SSDP.setName ( SSDP_Name );
  SSDP.setSerialNumber( "00000000001");
  SSDP.setURL( "/" );
  SSDP.setModelName( SSDP_Name );
  SSDP.setModelNumber( "000000000001" );
  SSDP.setModelURL( "" );
  SSDP.setManufacturer( "Sereda Andrey" );
  SSDP.setManufacturerURL( "http://www.esp8266-arduinoide.ru" );
  SSDP.begin ();
}

void outTemp()
{
  jsonWrite ( Variables, "temperature", _Tnow );
  saveVariables ();   
}
void outData() 
{
  jsonWrite ( Variables, "time", GetTime () );
  jsonWrite ( Variables, "date", GetDate () );
  saveVariables ();   
}

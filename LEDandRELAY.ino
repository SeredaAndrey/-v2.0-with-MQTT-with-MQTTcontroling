void Activate_init ()
{
  if ( currentMillis - ActivateRefreshMillis  >= ActivateRefresh  )                        // |режим| внешняя |активация по|инверт|ИТОГ |
  {                                                                                        // |     |активация|температуре |релле |     |
    ActivateRefreshMillis =  currentMillis;                                                // -------------------------------------------
    if      ( Mode == 1 && Activate == 0 && invertActivate == 0                          ) // |  1  |    0    |     -      |  0   |  0  | 
    { digitalWrite( PinRelay, LOW  ); }                                                    // -------------------------------------------
    else if ( Mode == 1 && Activate == 0 && invertActivate == 1                          ) // |  1  |    0    |     -      |  1   |  1  |
    { digitalWrite( PinRelay, HIGH ); }                                                    // -------------------------------------------
    else if ( Mode == 1 && Activate == 1 && invertActivate == 0 && flagControllTemp == 0 ) // |  1  |    1    |     0      |  0   |  1  |
    { digitalWrite( PinRelay, HIGH ); }                                                    // -------------------------------------------
    else if ( Mode == 1 && Activate == 1 && invertActivate == 0 && flagControllTemp == 1 ) // |  1  |    1    |     1      |  0   |progr|
    { CalkTemp (); }                                                                       // -------------------------------------------
    else if ( Mode == 1 && Activate == 1 && invertActivate == 1 && flagControllTemp == 0 ) // |  1  |    1    |     0      |  1   |  0  |
    { digitalWrite( PinRelay, LOW  ); }                                                    // -------------------------------------------
    else if ( Mode == 1 && Activate == 1 && invertActivate == 1 && flagControllTemp == 1 ) // |  1  |    1    |     0      |  1   |progr|
    { CalkTemp (); }                                                                       // -------------------------------------------
    else if ( Mode == 2 &&                  invertActivate == 0 && flagControllTemp == 0 ) // |  2  |    -    |     0      |  0   |  1  |
    { digitalWrite( PinRelay, HIGH ); }                                                    // -------------------------------------------
    else if ( Mode == 2 &&                  invertActivate == 0 && flagControllTemp == 1 ) // |  2  |    -    |     1      |  0   |progr|
    { CalkTemp (); }                                                                       // -------------------------------------------
    else if ( Mode == 2 &&                  invertActivate == 1 && flagControllTemp == 0 ) // |  2  |    -    |     0      |  1   |  0  |
    { digitalWrite( PinRelay, LOW  ); }                                                    // -------------------------------------------
    else if ( Mode == 2 &&                  invertActivate == 1 && flagControllTemp == 1 ) // |  2  |    -    |     1      |  1   |progr|
    { CalkTemp (); }                                                                       // -------------------------------------------
    else if ( Mode == 0 &&                  invertActivate == 0                          ) // |  0  |    -    |     -      |  0   |  0  |
    { digitalWrite( PinRelay, LOW  ); }                                                    // ------------------------------------------- 
    else if ( Mode == 0 &&                  invertActivate == 1                          ) // |  0  |    -    |     -      |  1   |  1  |
    { digitalWrite( PinRelay, HIGH ); }                                                    // ------------------------------------------- 
    yield();
  } 
}

void CalkTemp ()
{
  if      ( Tnow <  ( Tmax - ( deltaT / 2 ) ) )
  {
    if      ( invertActivate == 0 ) digitalWrite( PinRelay, HIGH );
    else if ( invertActivate == 1 ) digitalWrite( PinRelay, LOW );
  }
  else if ( Tnow >= ( Tmax + ( deltaT / 2 ) ) )
  {
    if      ( invertActivate == 0 ) digitalWrite( PinRelay, LOW );
    else if ( invertActivate == 1 ) digitalWrite( PinRelay, HIGH );
  }
}

void Led_init()
{
  int StatusLed;
  if      ( Mode == 0                  ) StatusLed = 0;
  else if ( Mode == 1 && Activate == 0 ) StatusLed = 3;
  else if ( Mode == 1 && Activate == 1 ) StatusLed = 4;
  else if ( Mode == 2                  ) StatusLed = 6;
  else                                   StatusLed = 1;
  if ( StatusLed !=0 ) 
  {
    static unsigned long prevTime;
    static int blink_loop; 
    byte blink_mode = modes [ StatusLed ];
    if ( millis () - prevTime > 125 )
    {
      prevTime=millis();
      if ( blink_mode & 1 << ( blink_loop&0x07 ) ) digitalWrite ( PinLed, LOW ); // Режим светодиода ищем по битовой маске
      else  digitalWrite ( PinLed, HIGH );
      blink_loop++; 
      if ( blink_loop > 8 ) 
      {
        blink_loop = 0;
        StatusLed = 0;
        digitalWrite( PinLed, HIGH );  
      }
    }
  } 
}

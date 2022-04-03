void PressKeys()
{
   bool pin_state = digitalRead(PinButtons);
// Фиксируем нажатие кнопки   
   if ( pin_state  == LOW && !button_state && ( millis() - ms_button ) > 50 )
   {
      button_state      = true;
      button_auto_state = false;  
   }
// После 2000 мс нажатия кнопки каждые 500 мс фиксируем событие нажатия  
   if ( pin_state  == LOW && ( millis() - ms_button ) > 2000 && ( millis() - ms_auto_click )>500 )
   {
      button_auto_state = true;
      ms_auto_click     = millis();
      Serial.println("Auto press key");  
   }
// Фиксируем отпускание кнопки   
   if ( pin_state == HIGH && button_state && ( millis() - ms_button ) > 50  )
   {
      button_state      = false;   
      ms_button         = millis();
      if( !button_auto_state )Serial.println("Press key");
      Mode++;
      if ( Mode > 2 ) Mode = 0;
      String _Mode;
      if ( Mode == 1 ) _Mode = "1"; else if ( Mode == 2 ) _Mode = "2"; else if ( Mode == 0 ) _Mode = "0"; else _Mode = "1";
      jsonWrite (SetupMode, "Mode", _Mode );
      saveSetupMode ();               
   }
}

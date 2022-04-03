void HTTP_init(void) 
{
  HTTP.on("/SetupMode.json", HTTP_GET, []() 
  {
    HTTP.send(200, "application/json", SetupMode);
  });
  HTTP.on("/Names.json", HTTP_GET, []() 
  {
    HTTP.send(200, "application/json", Names);
  });
  HTTP.on("/Autorisation.json", HTTP_GET, []() 
  {
    HTTP.send(200, "application/json", Autorisation);
  });
  HTTP.on("/Variables.json", HTTP_GET, []() 
  {
    HTTP.send(200, "application/json", Variables);
    outData();
  });
  HTTP.on("/IPadresses.json", HTTP_GET, []() 
  {
    HTTP.send(200, "application/json", IPadresses);
  });
  // -------------------Выдаем данные configSetup
  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");          // Получаем значение device из запроса
    if (restart == "ok") {                         // Если значение равно Ок
      HTTP.send(200, "text / plain", "Reset OK"); // Oтправляем ответ Reset OK
      ESP.restart();                                // перезагружаем модуль
    }
    else {                                        // иначе
      HTTP.send(200, "text / plain", "No Reset"); // Oтправляем ответ No Reset
    }
  });
  // Добавляем функцию Update для перезаписи прошивки по WiFi при 1М(256K SPIFFS) и выше
  httpUpdater.setup(&HTTP);
  // Запускаем HTTP сервер
  HTTP.begin();
}

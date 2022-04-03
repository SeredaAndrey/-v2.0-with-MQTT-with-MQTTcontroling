////////////////////////////// SSID & password //////////////////////////////
String ssid       = "Pushkina15_2.4GHz"; 
String password   = "Sereda19792004"; 
////////////////////////////// SSIDAP & passwordIP //////////////////////////////
String ssidAP     = "WiFi_ESP_for_Config";   
String passwordAP = "Sereda19792004";
////////////////////////////// IPs //////////////////////////////
String _MQTTip  = "192.168.10.100";
String IPRoomHost  = "192.168.10.150";
String IPBoolerHost  = "192.168.10.110";
int myip   [4] = { 192, 168, 10,  152 };         
int mask   [4] = { 255, 255, 255, 0  };
int gate   [4] = { 192, 168, 10,  1  }; 
int MQTTip [4] = { 192, 168, 10, 100 };
////////////////////////////// HTTP, MQTT & UDP //////////////////////////////
int port = 80;
int timeZone = 2;  
String pubtopic = "/Kitchdn-Rooms";
String subtopic = "/Controller-2";
String hosttopic = "/Boller-Controller/Devices-Status";
String flagActivURLcontrols = "1";   //Флаг активации режима при котором при отсутсвии подключения к MQTT упарвление через URL запросы
bool flagFailMQTTconnect = 0;
String NumberOfHomeSystemController = "152";
String ComandON = "DeviceON!";
String ComandOFF = "DeviceOFF!";
////////////////////////////// Names //////////////////////////////
String SSDP_Name   = "Kitchen-Rooms-HF-2"; 
////////////////////////////// FS //////////////////////////////
String IPadresses = "{}";            //"{"MQTTip":"192.168.10.100", "IPRoomHost":"192.168.10.150", "IPBoolerHost":"192.168.10.110"}"
String Names = "{}";                 //"{"SSDP_Name":"Parents-Rooms-Hot-Panel-1","pubtopic":"/Kitchdn-Rooms","subtopic":"/Controller-2"}";
String SetupMode = "{}";             //Запись состояний MODE & InvertActivate
String Variables = "{}";             //Запись состояний Activate, TimeZone & Temperature
String Autorisation = "{}";          //"{"ssid":"Pushkina15_2.4GHz","password":"Sereda19792004","ssidAP":"WiFi_ESP_for_Config","passwordAP":"Sereda19792004"}";
////////////////////////////// Modes //////////////////////////////
String _Tnow;
double Tnow;
double Tmax = 35;                    //Максимальная температура устройства при активной функции контроля температуры
String _Tmax = "35";
double deltaT = 1.5;                 //Дельта Т при активной функции контроля температуры
String _deltaT = "1.5";
bool flagControllTemp = 0;           // Флаг активации функции контроля температуры
int Mode = 1;                        // Режим работы устройства 1-автоматический, 2-всегда вкдючен, 3-всегда выключен
bool Activate = 0;                   // Состояние устройства 1-включено, 0-выключено (активно когда Mode=1)s
bool invertActivate = 1;             // Инвертирование состояния устройства (0 - неактивно, 1 - активно)
bool ResetFlag = 0;                  // флаг активирующий таймер перезагрузки контроллера
////////////////////////////// TIMERS //////////////////////////////
unsigned long currentMillis;
#define ds18b20interval 3000        // опрос датчика температуры каждые 3 секунды (3 000мс) 
#define SendDataInterval 30000       // отсылка данных на хост каждые 3 минуты (180 000мс) 
#define ResetESPInterval 300000      // перезагрузка ESP через 5 минут после загрузки в АР режиме (300000мс) - должно хватить для настройки в режим клиента 
#define ActivateRefresh 1000
long ActivateRefreshMillis = 0;
long SendDataMillis = 0;
long ResetESPMillis = 0;
long ds18b20readMillis = 0;          // счетчик прошедшего времени для интервала чтения с датчика температуры
////////////////////////////// GPIO //////////////////////////////
#define PinButtons 0
#define PinRelay 12
#define PinLed LED_BUILTIN           // для sonoff выставить в инструментах pin 13
bool     button_state      = false;
bool     button_auto_state = false;
uint32_t ms_button         = 0;
uint32_t ms_auto_click     = 0;
////////////////////////////// LED //////////////////////////////
byte modes[] = 
{
   0B00000000,                      //Светодиод выключен
   0B11111111,                      //Горит постоянно
   0B00001111,                      //Мигание по 0.5 сек
   0B00000001,                      //Короткая вспышка раз в секунду
   0B00000101,                      //Две короткие вспышки раз в секунду
   0B00010101,                      //Три короткие вспышки раз в секунду
   0B01010101                       //Частые короткие вспышки (4 раза в секунду)
};

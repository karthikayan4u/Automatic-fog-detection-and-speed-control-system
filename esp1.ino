#include<SoftwareSerial.h>

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "XybDlG4QYIcI_QWp0-mUak8W-j_nLEK1";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "vivo 1713";
char pass[] = "leelee5678";
SoftwareSerial SUART(4, 5); //SRX=Dpin-D2; STX-DPin-D1
//-------------------------
#include <SimpleDHT.h>
int temperature;
int humidity;
BlynkTimer timer;
//--------------------------------------------
WidgetLCD lcd(V4);
void setup()
{
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(2000, sendSensor);

}

void sendSensor()
{
  byte n = SUART.available(); //n != 0 means a character has arrived
  if (n != 0)
  {
    float humidity = SUART.read();  //read character
    float temperature = SUART.read();
    float dewpoint = SUART.read(); 
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
    Serial.print(humidity);        //show character on Serial Monitor
    Serial.print(" ");
    Serial.print(temperature);
    Serial.print(" ");
    Serial.print(dewpoint);
    Serial.println();
    Blynk.virtualWrite(V5, humidity);
    Blynk.virtualWrite(V6, temperature);
    Blynk.virtualWrite(V7, dewpoint);
    if(dewpoint<=2.50){
      lcd.clear();
      lcd.print(6,0,"FOG");
    }
    else{
      lcd.clear();
      lcd.print(5,0,"NOT FOG");
    }
  }
}
void loop()
{
  Blynk.run();
  timer.run();
}

#include<SoftwareSerial.h>
#include <DHT.h>
#include <AFMotor.h> 


AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(3, MOTOR34_64KHZ);
SoftwareSerial SUART(2, 3); //SRX=Dpin-2; STX-DPin-3
//-------------------------
#define DHTPIN A0          // What digital pin we're connected to

#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321

DHT dht(DHTPIN, DHTTYPE);
//--------------------------------------------

void setup()
{
  Serial.begin(115200); //enable Serial Monitor
  SUART.begin(115200); //enable SUART Port
  dht.begin();
  motor1.setSpeed(200);
  motor2.setSpeed(200);

}



void loop()
{ 
  //---acquire Temp and Humidity signal and save in variables
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
  float ts = t - ((100 - h)/5.);
    //---show temp and humidity on Serial moniotr
  Serial.print("Temperature = "); Serial.print(t); Serial.print(" degC");
  Serial.print("  ");  //space
  Serial.print("Humidity = "); Serial.print(h); Serial.print(" %H ");
  if((t-ts )<=2.5){
      Serial.println("fog");
      
      motor1.setSpeed(200);
      motor2.setSpeed(200);
      
      motor1.run(FORWARD);
      motor2.run(FORWARD); 
      }
    else{
      Serial.println("Not fog");
      
      motor1.setSpeed(255);    
      motor2.setSpeed(255); 
      //Serial.print("tick");
      
      motor1.run(FORWARD);  
      motor2.run(FORWARD); 
      }
  
  //----Send Temp and Humidity signal to NodeMCU via SUART port----
  SUART.print((float)t);
  SUART.println();
  SUART.print((float)h);
  SUART.println();
  SUART.print((float)ts);
  SUART.println();
  delay(2000);
}

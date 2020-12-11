//  The circuit:
//  - Arduino Nano 33 BLE Sense
// @Johny_Ln ESILV Promo 2021 IoT & Big Data

//Pression
#include <Arduino_LPS22HB.h>
//Temperature and humidity
#include <Arduino_HTS221.h>

byte IRPinYellow = 2;



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(IRPinYellow, INPUT);

  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
  
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("New Measure -------------------------- ");
  //IR Sensor
  Serial.print("\nPresnece : ");
  Serial.print(IR_Sensor_Data(IRPinYellow));

  //Pressure Sensor
  Serial.print("\nPressure = ");
  Serial.print(Pressure_Sensor());
  Serial.print(" kPa");
  delay(3000);

  //Temp and Hum Sensor
  float * temp_hum = Temp_Hum_Sensor();
  Serial.print("\nTemp : ");
  Serial.print(temp_hum[0]);
  Serial.print(" | Humidity : ");
  Serial.print(temp_hum[1]);
  Serial.print(" %");

  

  Serial.print("\n--------------------------------------  \n\n");


}

#pragma region Region_IRPresence

//From  https://wiki.seeedstudio.com/Grove-IR_Distance_Interrupter_v1.2/
//For Arduino Nano Sense 33
// Black - GND
// Red - 3.3V
// White - x
// Yellow - D2 Arduino

bool IR_Sensor_Data(byte IRPinYellow)
{
  bool presence = false;
  if (digitalRead(IRPinYellow) == LOW)
  {
    //Serial.println("IR Presence : Somebody is here");
    presence = true;
  }
  else
  {
    //Serial.println("IR Presence : Nobody");
  }
  return  presence;
}

#pragma endregion Region_IRPresence


#pragma region Region_Pressure

//  This example reads data from the on-board LPS22HB sensor of the
//  Nano 33 BLE Sense and prints the pressure sensor value to the
//  Serial Monitor once a second.

float Pressure_Sensor()
{
  float pressure = BARO.readPressure();

  // print the sensor value
  //Serial.print("Pressure = ");
  //Serial.print(pressure);
  //Serial.println(" kPa");

  // print an empty line
  //Serial.println();
  return pressure;
}
#pragma endregion Region_Pressure



#pragma region Region_Temp_Pre

float *Temp_Hum_Sensor()
{
  float temperature = HTS.readTemperature();
  float humidity    = HTS.readHumidity();
  float *array_t_h = new float [2];
  array_t_h[0] = temperature;
  array_t_h[1] = humidity;
  
  return array_t_h;
}

#pragma endregion Region_Temp_Pre

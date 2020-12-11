//From https://rootsaid.com/arduino-ble-example/
//For Arduino Nano SENSE 33

#include <ArduinoBLE.h>


//_____________________________________________________
// IR Grove

// Black - GND
// Red - 3.3V
// White - x
// Yellow - D2
int pinYellow = 2;



//On déclare une instnace d'un nouveau service BLE -> ici la batterie
//On lui donne 2 permissions : BLERead and BLENotify
BLEService presenceService("8638cf0d-be1e-4684-9465-f5c9bda4f6d4");//UUID of Service -> Universally Unique ID
//https://ladvien.com/arduino-nano-33-bluetooth-low-energy-setup/
//UUID Generator -> https://www.guidgenerator.com/online-guid-generator.aspx
//There are several different ways to initialize a characteristic


BLEBoolCharacteristic presenceBool("174f6e16-2005-4e8e-a558-7f12406edb79", BLERead | BLENotify);
//BLEDescriptor presenceDescrip("722761c6-11c2-4acf-b835-8e7dc3c05b543","Presence");

//BLERead – allows remote devices to read the characteristic value
//BLEWrite – allows remote devices to write, while expecting an acknowledgement the write was successful
//BLENotify – allows a remote device to be notified anytime the characteristic’s value is update


//Here it will initialize the Serial Communication and BLE and wait for serial monitor to open. 
void setup() {
Serial.begin(9600);

//Grove
pinMode(pinYellow,INPUT);

while (!Serial);

pinMode(LED_BUILTIN, OUTPUT);
if (!BLE.begin()) 
{
Serial.println("starting BLE failed!");
while (1);
}


//Set a local name for the BLE device. 
//This name will appear in advertising packets and can be used by remote devices to identify this BLE device.
BLE.setLocalName("Presence_Grove_IR");
BLE.setAdvertisedService(presenceService);
//presenceBool.addDescriptor(presenceDescrip);
presenceService.addCharacteristic(presenceBool);
BLE.addService(presenceService);


//Here we will add and set the value for the Service UUID and the Characteristic.
BLE.advertise();
Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() 
{
  
//And here, we will Start advertising BLE.  It will start continuously transmitting BLE advertising packets 
//and will be visible to remote BLE central devices until it receives a new connection.
BLEDevice central = BLE.central();

if (central) 
{
Serial.print("Connected to central: ");
Serial.println(central.address());
digitalWrite(LED_BUILTIN, HIGH);

//And here, the loop function. 
//Once everything is setup and have started advertising, 
//the device will wait for any central device. Once it is connected, 
//it will display the MAC address of the device and it will turn on the builtin LED.
while (central.connected()) {

//Now, it will start to read analog voltage from A0, which will be a value in between 0 and 1023 
      bool presence_send = presence();
      presenceBool.writeValue(presence_send);
      delay(200);
}
}

//Once it is disconnected, a message will be shown on the central device and LED will be turned off. 
digitalWrite(LED_BUILTIN, LOW);
Serial.print("Disconnected from central: ");
Serial.println(central.address());
}


bool presence() {
  bool presence = false;
  if(digitalRead(pinYellow)==LOW)  {
            Serial.println("Somebody is here.");
            presence = true;
        }
        else  {
            Serial.println("Nobody.");
        }

        return presence;
}

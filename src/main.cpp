#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <Arduino.h>

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;



// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
    }
};



void setup() {
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  pinMode(GPIO_NUM_0, OUTPUT);
  pinMode(GPIO_NUM_1, OUTPUT);
  pinMode(GPIO_NUM_2, OUTPUT);
  pinMode(GPIO_NUM_3, OUTPUT);
  pinMode(GPIO_NUM_4, OUTPUT);
  pinMode(GPIO_NUM_5, OUTPUT);
  pinMode(GPIO_NUM_6, OUTPUT);
  pinMode(GPIO_NUM_7, OUTPUT);
  pinMode(GPIO_NUM_8, OUTPUT);
  pinMode(GPIO_NUM_9, OUTPUT);
  pinMode(GPIO_NUM_10, OUTPUT);
  pinMode(GPIO_NUM_18, OUTPUT);
  pinMode(GPIO_NUM_19, OUTPUT);

  
  // Create the BLE Device
  BLEDevice::init("ESP32");

  // Create the BLE Server
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ   |
                      BLECharacteristic::PROPERTY_WRITE  |
                      BLECharacteristic::PROPERTY_NOTIFY |
                      BLECharacteristic::PROPERTY_INDICATE
                    );

  // https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.descriptor.gatt.client_characteristic_configuration.xml
  // Create a BLE Descriptor
  pCharacteristic->addDescriptor(new BLE2902());

  // Start the service
  pService->start();

  // Start advertising
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);  // set value to 0x00 to not advertise this parameter
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

bool enChip1 = false; //gpio_0
bool enChip2 = false; //gpio_1
bool enChip3 = false; //gpio_2
bool enChip4 = false; //gpio_3
bool enChip5 = false; //gpio_10
bool enChip6 = false; //gpio_18
bool A = false; //gpio_4
bool B = false; //gpio_5


void offMotors() {
  enChip1 = false;
  enChip2 = false;
  enChip3 = false;
  enChip4 = false;
  enChip5 = false;
  enChip6 = false;
  A = false;
  B = false;
  digitalWrite(GPIO_NUM_0, enChip1);
  digitalWrite(GPIO_NUM_1, enChip2);
  digitalWrite(GPIO_NUM_2, enChip3);
  digitalWrite(GPIO_NUM_3, enChip4);
  digitalWrite(GPIO_NUM_10, enChip5);
  digitalWrite(GPIO_NUM_18, enChip6);
  digitalWrite(GPIO_NUM_4, A);
  digitalWrite(GPIO_NUM_5, B);
}
void rotateMotors(bool enChip1, bool enChip2, bool enChip3, bool enChip4, bool enChip5, bool enChip6, bool A, bool B) {
  digitalWrite(GPIO_NUM_0, enChip1);
  digitalWrite(GPIO_NUM_1, enChip2);
  digitalWrite(GPIO_NUM_2, enChip3);
  digitalWrite(GPIO_NUM_3, enChip4);
  digitalWrite(GPIO_NUM_10, enChip5);
  digitalWrite(GPIO_NUM_18, enChip6);
  digitalWrite(GPIO_NUM_4, A);
  digitalWrite(GPIO_NUM_5, B);
}
void onReceive() {
  char command[20] = {0};
  std::string value = pCharacteristic->getValue();
  strcpy(command, value.c_str());
  
  if(value.size() != 0) {
  /*
   if (strstr(command, "on") != NULL) {
      digitalWrite(LED_BUILTIN, true);
      Serial.println(value.c_str());
      //digitalWrite(GPIO_NUM_6, HIGH);
      digitalWrite(GPIO_NUM_2, HIGH);
      
    }
    else if (strstr(command, "off") != NULL) {
      digitalWrite(LED_BUILTIN, LOW);
      Serial.println(value.c_str());
      //digitalWrite(GPIO_NUM_6, LOW);
      digitalWrite(GPIO_NUM_2, LOW);
    }
    */
    if (strstr(command, "on1") != NULL) {
      Serial.println(value.c_str());
      rotateMotors(true, false, false, false, false, false, true, false);     
    }
    else if (strstr(command, "on2") != NULL) {
      Serial.println(value.c_str());
      rotateMotors(false, true, false, false, false, false, true, false);
    }
    else if (strstr(command, "on3") != NULL) {
      Serial.println(value.c_str());
      rotateMotors(false, false, true, false,false, false, true, false);
    }
    else if (strstr(command, "on4") != NULL) {
      Serial.println(value.c_str());
      rotateMotors(false, false, false, true, false, false, true, false);
    }
    else if (strstr(command, "on5") != NULL) {
      Serial.println(value.c_str());
      rotateMotors(false, false, false, false, true, false, true, false);
    }
    else if (strstr(command, "on6") != NULL) {
      Serial.println(value.c_str());
      rotateMotors(false, false, false, false, false, true, true, false);
    }
    else if (strstr(command, "off") != NULL) {
      Serial.println(value.c_str());
      offMotors();
    }
    else { // unknown command
      Serial.println("Unknown command:");
      Serial.println(value.c_str());
    } 

  }
}

void loop() {
    if (deviceConnected) {
        //Check input
        onReceive();   

        //Reset input to wait for new value  
        pCharacteristic->setValue("");
        delay(50); // bluetooth stack will go into congestion with too small delay(6ms max)
    }

    // disconnecting
    if (!deviceConnected && oldDeviceConnected) {
        delay(500); // give the bluetooth stack the chance to get things ready
        pServer->startAdvertising(); // restart advertising
        Serial.println("start advertising");
        oldDeviceConnected = deviceConnected;
    }
    // connecting
    if (deviceConnected && !oldDeviceConnected) {
        // do stuff here on connecting
        oldDeviceConnected = deviceConnected;
        Serial.println("Connected");
    }
}

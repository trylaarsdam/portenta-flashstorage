#include <Arduino.h>
#include "FlashKeyValue.h"
#include "mbed.h"

using namespace mbed;

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  //  Wait for terminal to come up
  delay(1000);

  Serial.println("Portenta Key-Value flash storage test");

  Serial.print("Initializing TDBStore: ");
  int result = FlashKeyValue::init();
  Serial.println(result == 1 ? "OK" : "Failed");
  if (result != 1)
    while (true); // Stop the sketch if an error occurs

  // Previous value
  FlashKeyValueStruct previousValue;

	// Get previous values from the key-value store
  Serial.println("Retrieving values from flash");
  result = FlashKeyValue::get(&previousValue);

  if (result == MBED_SUCCESS) {
    Serial.println("Previous Value");
    Serial.print("\Boolean value: ");
    Serial.println(previousValue.booleanValue);
    Serial.print("\Double value: ");
    Serial.println(previousValue.doubleValue);

  } else if (result == MBED_ERROR_ITEM_NOT_FOUND) {
    Serial.println("No previous data was found.");
		previousValue = { false, 0.0};
  } else {
		Serial.println(result);
    Serial.println("Error reading from key-value store.");
    while (true);
  }

  // Update the stats and save them to the store
  FlashKeyValueStruct currentValue { 
		!previousValue.booleanValue, previousValue.doubleValue + 0.1
	};  
  result = FlashKeyValue::set(currentValue);
  
  if (result == MBED_SUCCESS) {
    Serial.println("Value updated");
  } else {
    Serial.println("Error while saving to key-value store");
    while (true);
  }

	// OPTIONAL: Erase the data
	// FlashKeyValue::erase();
}

void loop() {
  // put your main code here, to run repeatedly:
}
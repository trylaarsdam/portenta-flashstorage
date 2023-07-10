# Portenta Flash Storage

This library allows you to easily use the flash storage of the Portenta H7. It is based on the flash optimized key value store example from Arduino, but provides a nice wrapper around it.

## Guide

### Defining your data structure
In the library there is a header called `FlashStruct.h`, which contains a default struct that looks like this:
```cpp
struct FlashKeyValueStruct
{
	bool booleanValue;
	double doubleValue;
};
```
More than likely this is not the format of data you want to store, so first modify the struct to match your data structure. In most PlatformIO installations this file can be found in the following directory inside your project:
```
.pio/libdeps/portenta_h7_m7/portenta-flashstorage/src/FlashStruct.h
```
You do not need to change any other part of the library to make your struct compatible. The library will automatically read the in-memory size of your struct and use it accordingly. **Do not change the name of the struct.**

This guide will use the default struct provided, so make sure to modify your references to the struct when they come up.

### Initializing the flash
You must initialize the flash before using it, otherwise reading/writing will return error codes. To do this, call the `FlashKeyValue::init()` function like this:
```cpp
int result = FlashKeyValue::init();
// optional - test for successful initialization
Serial.println(result == 1 ? "OK" : "Failed");
if (result != 1)
	while (true); // Stop the firmware if an error occurs
```

### Reading from flash
To read from flash, you must first create a variable of your struct type. Then call the `FlashKeyValue::get` function with a pointer to your variable like this:
```cpp
// Will store the value currently in flash
FlashKeyValueStruct value;

int result = FlashKeyValue::get(&previousValue);
```

You should always handle the following conditions of `result`, since they determine whether or not `value` has any actual data in it. Here are the values you should test for:
| Result Code | Meaning |
| ----------- | ------- |
| `MBED_SUCCESS` | The value was successfully read from flash |
| `MBED_ERROR_ITEM_NOT_FOUND` | The key was not found in flash, but flash is working properly |
| `MBED_ERROR_NOT_READY` | Flash was not initialized  |
| `MBED_ERROR_READ_FAILED` | Flash is not working properly |
| `MBED_ERROR_INVALID_ARGUMENT` | An internal error occurred |
| `MBED_ERROR_INVALID_DATA_DETECTED` | Your data does not match the previous data stored in flash. Try using `FlashKeyValue::erase` to reset flash |

Here's a sample of how to appropriately handle these conditions:
```cpp
if (result == MBED_SUCCESS) {
	// We can now read our data, just as if it was a normal variable
	Serial.println("Values from flash");
	Serial.print("\Boolean value: ");
	Serial.println(previousValue.booleanValue);
	Serial.print("\Double value: ");
	Serial.println(previousValue.doubleValue);
} else if (result == MBED_ERROR_ITEM_NOT_FOUND) {
	Serial.println("No data was found.");
	// You can initialize your data here if you want
	previousValue = { false, 0.0 };
} else {
	// Another error occurred, handle it here
	Serial.print("Error reading from key-value store with code: ");
	Serial.println(result);
	while (true);
}
```

### Storing to flash
To store to flash, you must first create a variable of your struct type. Then call the `FlashKeyValue::set` function with a pointer to your variable like this:
```cpp
FlashKeyValueStruct newValue { 
	true, 0.2
};  

int result = FlashKeyValue::set(newValue);
```

To make sure your data was successfully stored in flash, you should test for the following conditions of `result`:
| Result Code | Meaning |
| ----------- | ------- |
| `MBED_SUCCESS` | The value was successfully written to flash |
| Other | An error occurred on the mbed level. Make sure flash is properly initialized |

Here's a sample of how to appropriately handle these conditions:
```cpp
if (result == MBED_SUCCESS) {
	Serial.println("Value set");
} else {
	Serial.println("Error while saving to key-value store");
	while (true);
}
```

### Erasing flash contents
To erase the contents of flash, call the `FlashKeyValue::erase` function like this:
```cpp
FlashKeyValue::erase();
```

## Examples
You can see a complete working example in the examples/basic-usage directory.

## API
### `bool init();`
Initializes the flash storage. This must be called before any other functions are called. Returns `true` if successful, otherwise returns `false`.
### `int get(FlashKeyValueStruct* value);`
Reads the value from flash into the provided struct using the default key. Returns an mbed error code.
### `int get(const char* key, FlashKeyValueStruct* value);`
Reads the value from flash into the provided struct using the provided key. Returns an mbed error code.
### `int set(FlashKeyValueStruct value);`
Writes the provided struct to flash using the default key. Returns an mbed error code.
### `int set(const char* key, FlashKeyValueStruct value);`
Writes the provided struct to flash using the provided key. Returns an mbed error code.
### `int erase();`
Erases the contents of flash. Returns `0` if successful.
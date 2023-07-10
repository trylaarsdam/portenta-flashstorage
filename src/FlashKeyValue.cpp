#include "FlashKeyValue.h"
#include "FlashStruct.h"

// using namespace mbed;

namespace FlashKeyValue
{
	auto iapLimits { getFlashIAPLimits() };
	FlashIAPBlockDevice blockDevice(iapLimits.start_address, iapLimits.available_size);
	TDBStore store(&blockDevice);
	const char defaultKey[] { "portenta" };

	bool init()
	{
		int result = store.init();
		if (result != MBED_SUCCESS)
		{
			Serial.println("Error initializing TDBStore");
			return false;
		}

		return true;
	}

	int get(const char* key, FlashKeyValueStruct* value)
	{
		TDBStore::info_t info;
		int result = store.get_info(key, &info);

		if(result == MBED_ERROR_ITEM_NOT_FOUND)
		{
			return result;
		}
		else if(result != MBED_SUCCESS)
		{
			Serial.println("Error getting info");
			Serial.println(result);
			return result;
		}

		uint8_t buffer[info.size] {};
		size_t actual_size;

		result = store.get(key, buffer, sizeof(buffer), &actual_size);
		if(result != MBED_SUCCESS)
		{
			return result;
		}

		memcpy(value, buffer, sizeof(FlashKeyValueStruct));
		return result;
	}

	int get(FlashKeyValueStruct* value) 
	{
		return get(defaultKey, value);
	}

	int set(const char* key, FlashKeyValueStruct value)
	{
		return store.set(key, reinterpret_cast<uint8_t*>(&value), sizeof(FlashKeyValueStruct), 0);
	}

	int set(FlashKeyValueStruct value)
	{
		return set(defaultKey, value);
	}

	int erase()
	{
		store.reset();
		blockDevice.erase(iapLimits.start_address, iapLimits.available_size);
		return 0;
	}
}
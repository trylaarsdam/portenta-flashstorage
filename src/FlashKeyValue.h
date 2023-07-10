#pragma once
#include "FlashStruct.h"
#include "mbed.h"
#include "TDBStore.h"
#include "FlashIAPBlockDevice.h"
#include "FlashIAPLimits.h"

using namespace mbed;

/**
 * @brief Namespace for the flash key-value store
 * \defgroup FlashKeyValue
*/
namespace FlashKeyValue
{
	extern FlashIAPBlockDevice blockDevice;
	extern TDBStore store;

	/**
	 * @brief Initializes the flash key-value store
	 * @param None
	 * @return True if successful, false otherwise
	 * \ingroup FlashKeyValue
	*/
	bool init();
	/**
	 * @brief Gets the stored value of a key
	 * @param key The key to get the value of
	 * @param value The value to store the retrieved value in
	 * @return 0 if successful, MBED_ERROR_ITEM_NOT_FOUND if the key was not found, or another error code
	*/
	int get(const char* key, FlashKeyValueStruct* value);
	/**
	 * @brief Gets the stored value of the default key
	 * @param value The value to store the retrieved value in
	 * @return 0 if successful, MBED_ERROR_ITEM_NOT_FOUND if the key was not found, or another error code
	*/
	int get(FlashKeyValueStruct* value);
	/**
	 * @brief Sets the value of a key
	 * @param key The key to set the value of
	 * @param value The value to set
	 * @return 0 if successful, or another error code
	*/
	int set(const char* key, FlashKeyValueStruct value);
	/**
	 * @brief Sets the value of the default key
	 * @param value The value to set
	 * @return 0 if successful, or another error code
	*/
	int set(FlashKeyValueStruct value);
	/**
	 * @brief Erases the flash key-value store
	 * @param None
	 * @return 0 if successful, or another error code
	*/
	int erase();
}
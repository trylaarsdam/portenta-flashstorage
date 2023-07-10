/**
Helper functions for calculating FlashIAP block device limits
**/

// Ensures that this file is only included once
#pragma once 

#include <Arduino.h>
#include <FlashIAP.h>
#include <FlashIAPBlockDevice.h>

using namespace mbed;

// A helper struct for FlashIAP limits
struct FlashIAPLimits {
  size_t flash_size;
  uint32_t start_address;
  uint32_t available_size;
};

// Get the actual start address and available size for the FlashIAP Block Device
// considering the space already occupied by the sketch (firmware).
FlashIAPLimits getFlashIAPLimits();
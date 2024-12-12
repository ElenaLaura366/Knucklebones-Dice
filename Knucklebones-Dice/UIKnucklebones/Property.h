#pragma once

#include <cstdint>


enum class Property : uint8_t
{
	BUTTON_SELECTED
};

const char* GetPropertyName(Property property);

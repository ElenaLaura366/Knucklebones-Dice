#include "Property.h"

#include <stdexcept>


const char* GetPropertyName(Property property)
{
	switch (property)
	{
	case Property::BUTTON_SELECTED:
		return "selected";
	default:
		throw std::runtime_error("Invalid property");
	}
}

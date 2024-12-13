#include "Property.h"

#include <stdexcept>


const char* GetPropertyName(Property property)
{
	switch (property)
	{
	case Property::QButton_selected:
		return "selected";
	case Property::QLabel_highlight:
		return "highlight";
	default:
		throw std::runtime_error("Invalid property");
	}
}

QVariant GetPropertyVariant(PropertyValue value)
{
	switch (value)
	{
	case PropertyValue::QLabel_highlight_none:
		return "none";
	case PropertyValue::QLabel_highlight_low:
		return "low";
	case PropertyValue::QLabel_highlight_full:
		return "full";
	default:
		throw std::runtime_error("Invalid property value");
	}
}

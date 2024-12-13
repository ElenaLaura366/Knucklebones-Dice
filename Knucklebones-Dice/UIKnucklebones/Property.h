#pragma once

#include <cstdint>
#include <QVariant>


enum class Property : uint8_t
{
	QButton_selected,
	QLabel_highlight,
};

enum class PropertyValue : uint8_t
{
	QLabel_highlight_none,
	QLabel_highlight_low,
	QLabel_highlight_full,
};

const char* GetPropertyName(Property property);
QVariant GetPropertyVariant(PropertyValue value);

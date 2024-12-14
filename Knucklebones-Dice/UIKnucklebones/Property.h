#pragma once

#include <cstdint>
#include <QVariant>


namespace ui
{
	/*!
	*	\brief Custom properties that can be set to widgets. The name of the property uses the pattern
	*	[ElementType]_[PropertyName], where ElementType and PropertyName are declared in the .qss
	*	file currently loaded like so: ElementName[PropertyName="ValueString"].
	*/
	enum class Property : uint8_t
	{
		QButton_selected,	/*!< true, false */
		QLabel_highlight,	/*!< "none", "low", "full" */
	};

	/*!
	*	\brief Custom values that can be set to the custom properties. The name of the property uses the pattern
	*	[ElementType]_[PropertyName]_[ValueString], where ElementType, PropertyName and ValueString are declared 
	*	in the .qss file currently loaded like so: ElementName[PropertyName="ValueString"].
	*/
	enum class PropertyValue : uint8_t
	{
		QLabel_highlight_none,	/*!< representing QLabel[highlight="none"] */
		QLabel_highlight_low,	/*!< representing QLabel[highlight="low"] */
		QLabel_highlight_full,	/*!< representing QLabel[highlight="full"] */
	};

	/*!
	*	\brief Returns the name of the property enum parameter as a string.
	*	\param property - the property enum value to get the name of
	*	\sa ui::Property
	*/
	const char* GetPropertyName(Property property);

	/*!
	*	\brief Returns the QVariant value of the PropertyValue enum parameter.
	*	\param value - the PropertyValue enum value to get the QVariant value of
	*	\sa ui::PropertyValue
	*/
	QVariant GetPropertyVariant(PropertyValue value);
}

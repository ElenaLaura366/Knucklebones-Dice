#pragma once

#include "Property.h"

#include <QWidget>


namespace ui
{
	class MainWindow;


	/*!
	*	\brief Base class for all the main widgets of the application. A main widget is defined as the single
	*	widget that is displayed at a time in the `ui::MainWindow`. It defines the content of the window.
	*/
	class BaseMainWidget : public QWidget
	{
		Q_OBJECT

	public:
		BaseMainWidget(MainWindow* parent);

	protected:
		/*!
		*	\brief Method to access the `ui::MainWindow` that contains this widget.
		*/
		MainWindow* GetParentWindow() const;

		/*!
		*	\brief Method to set a custom property to a widget and update its style.
		*	\param target - the widget to set the property to
		*	\param property - the custom property to set
		*	\param value - the value to set the property to
		*	\sa ui::Property
		*	\sa ui::GetPropertyName
		*/
		void SetProperty(QWidget* target, Property property, QVariant value);

		/*!
		*	\brief Method to set a custom property to a widget and update its style.
		*	\param target - the widget to set the property to
		*	\param property - the custom property to set
		*	\param value - the value to set the property to
		*	\sa ui::Property
		*	\sa ui::GetPropertyName
		*	\sa ui::GetPropertyVariant
		*/
		void SetProperty(QWidget* target, Property property, PropertyValue value);

		/*!
		*	\brief Method to set a custom property to all the widgets in a list and update their style.
		*	\param targets - the widgets to set the property to
		*	\param property - the custom property to set
		*	\param value - the value to set the property to
		*	\sa ui::Property
		*	\sa ui::GetPropertyName
		*/
		void SetProperty(const QVector<QWidget*>& targets, Property property, QVariant value);

		/*!
		*	\brief Method to set a custom property to all the widgets in a list and update their style.
		*	\param targets - the widgets to set the property to
		*	\param property - the custom property to set
		*	\param value - the value to set the property to
		*	\sa ui::Property
		*	\sa ui::GetPropertyName
		*	\sa ui::GetPropertyVariant
		*/
		void SetProperty(const QVector<QWidget*>& targets, Property property, PropertyValue value);

	private:
		MainWindow* m_uiParentWindow = nullptr;
	};
}

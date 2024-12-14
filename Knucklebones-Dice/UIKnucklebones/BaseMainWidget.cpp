#include "BaseMainWidget.h"

#include "MainWindow.h"

#include <QStyle>


ui::BaseMainWidget::BaseMainWidget(MainWindow* parent)
	: QWidget(parent)
	, m_uiParentWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
}

ui::MainWindow* ui::BaseMainWidget::GetParentWindow() const
{
	return m_uiParentWindow;
}

void ui::BaseMainWidget::SetProperty(QWidget* target, Property property, QVariant value)
{
	const char* propertyName = GetPropertyName(property);
	target->setProperty(propertyName, value);
	target->style()->unpolish(target);
	target->style()->polish(target);
}

void ui::BaseMainWidget::SetProperty(QWidget* target, Property property, PropertyValue value)
{
	SetProperty(target, property, GetPropertyVariant(value));
}

void ui::BaseMainWidget::SetProperty(const QVector<QWidget*>& targets, Property property, QVariant value)
{
	for (QWidget* target : targets)
	{
		SetProperty(target, property, value);
	}
}

void ui::BaseMainWidget::SetProperty(const QVector<QWidget*>& targets, Property property, PropertyValue value)
{
	SetProperty(targets, property, GetPropertyVariant(value));
}

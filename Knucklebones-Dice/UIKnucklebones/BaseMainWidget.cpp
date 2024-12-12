#include "BaseMainWidget.h"

#include "MainWindow.h"

#include <QStyle>


BaseMainWidget::BaseMainWidget(MainWindow* parent)
	: QWidget(parent)
	, m_uiParentWindow(parent)
{
	setAttribute(Qt::WA_DeleteOnClose);
}

MainWindow* BaseMainWidget::GetParentWindow() const
{
	return m_uiParentWindow;
}

void BaseMainWidget::SetProperty(QWidget* target, Property property, QVariant value)
{
	const char* propertyName = GetPropertyName(property);
	target->setProperty(propertyName, value);
	target->style()->unpolish(target);
	target->style()->polish(target);
}

void BaseMainWidget::SetProperty(const QVector<QWidget*>& targets, Property property, QVariant value)
{
	for (QWidget* target : targets)
	{
		SetProperty(target, property, value);
	}
}

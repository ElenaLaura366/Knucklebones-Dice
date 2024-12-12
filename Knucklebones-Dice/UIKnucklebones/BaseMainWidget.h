#pragma once

#include "Property.h"

#include <QWidget>


class MainWindow;


class BaseMainWidget : public QWidget
{
	Q_OBJECT

public:
	BaseMainWidget(MainWindow* parent);

protected:
	MainWindow* GetParentWindow() const;
	void SetProperty(QWidget* target, Property property, QVariant value);
	void SetProperty(const QVector<QWidget*>& targets, Property property, QVariant value);

private:
	MainWindow* m_uiParentWindow = nullptr;
};

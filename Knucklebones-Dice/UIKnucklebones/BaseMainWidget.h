#pragma once

#include <QWidget>


class MainWindow;


class BaseMainWidget : public QWidget
{
	Q_OBJECT

public:
	BaseMainWidget(MainWindow* parent);

protected:
	MainWindow* GetParentWindow() const;

private:
	MainWindow* m_uiParentWindow = nullptr;
};

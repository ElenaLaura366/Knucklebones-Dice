#pragma once
#include <QtWidgets>
#include <QPushButton>
#include <QCloseEvent>
#include <QApplication>
#include <QMainWindow>

class UIGameWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit UIGameWindow(QWidget* parent = nullptr);
	~UIGameWindow() = default;

protected:
    void closeEvent(QCloseEvent* event) override;
};

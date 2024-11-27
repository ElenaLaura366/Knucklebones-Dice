#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_UIKnucklebones.h"

class UIKnucklebones : public QMainWindow
{
    Q_OBJECT

public:
    UIKnucklebones(QWidget *parent = nullptr);
    ~UIKnucklebones();

private:
    Ui::UIKnucklebonesClass ui;
};

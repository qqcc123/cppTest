#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtEventLoop.h"

class QtEventLoop : public QMainWindow
{
    Q_OBJECT

public:
    QtEventLoop(QWidget *parent = nullptr);
    ~QtEventLoop();

private:
    Ui::QtEventLoopClass ui;
};

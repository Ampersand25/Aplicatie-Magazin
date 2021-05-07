#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MagazinGUI.h"

class MagazinGUI : public QMainWindow
{
    Q_OBJECT

public:
    MagazinGUI(QWidget *parent = Q_NULLPTR);

private:
    Ui::MagazinGUIClass ui;
};

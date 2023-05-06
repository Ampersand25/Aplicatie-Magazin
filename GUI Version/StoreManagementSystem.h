#pragma once

#include <QtWidgets/QWidget>
#include "ui_StoreManagementSystem.h"

class StoreManagementSystem : public QWidget
{
    Q_OBJECT

public:
    StoreManagementSystem(QWidget *parent = nullptr);
    ~StoreManagementSystem();

private:
    Ui::StoreManagementSystemClass ui;
};

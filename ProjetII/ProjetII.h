#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjetII.h"

class ProjetII : public QMainWindow
{
	Q_OBJECT

public:
	ProjetII(QWidget *parent = Q_NULLPTR);

private:
	Ui::ProjetIIClass ui;
};

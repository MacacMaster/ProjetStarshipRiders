#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjetII.h"
#include<QSceneModel.h>
#include<QSceneViewController.h>
#include<QShuttle.h>
#include<QPolygonalBody.h>
#include<QShuttleKeyboardController.h>
#include<QShuttleFuelTank.h>
#include<QShuttleThruster.h>
#include<QThrusterKeyboardController.h>
#include <QPainter>


class ProjetII : public QMainWindow
{
	Q_OBJECT

public:
	ProjetII(QWidget *parent = Q_NULLPTR);


private:
	Ui::ProjetIIClass ui;

	QSceneModel mSceneModel;
	QSceneViewController *mSceneController;

};



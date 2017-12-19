#ifndef PROJETII_H
#define PROJETII_H

#include <QtWidgets/QMainWindow>
#include "ui_ProjetII.h"
#include "QSceneViewController.h"
#include "QSceneModel.h"
#include "QShuttle.h"
#include "QPolygonalBody.h"
#include "QShuttleKeyboardController.h"
#include "QShuttleThruster.h"
#include "QShuttleFuelTank.h"
#include "QThrusterKeyboardController.h"
#include "QPolygonEditor.h"
#include "QPolygonFactory.h"
#include "QTimer.h"
#include "QColorBox.h"
#include "QRealValueBox.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCombobox>
#include "OngletNav.h"
#include "OngletVehicule.h"
#include "OngletReservoir.h"
#include "OngletPropulseurs.h"
#include <iostream>

class ProjetII
	: public QMainWindow
{
	Q_OBJECT

public:
	ProjetII(QWidget *parent = Q_NULLPTR);
	void createTab();
	void generate_Horizon_6t_k();
	void addNewThruster(QSceneModel * model,
		QShuttleFuelTank * fuelTank,
		qreal thrusterSize,
		qreal massFlowRate,
		qreal massEjectSpeed,
		QPointF const & position,
		qreal orientationDegrees,
		QBrush const & brush,
		QPen const & pen,
		QKeySequence const & key);

	QShuttle *shuttle() { return mShuttle; }
	//void paint();


private:
	Ui::ProjetIIClass ui;

	QSizeF mSceneSize;
	QSceneModel mSceneModel;
	QSceneViewController *mSceneControl;
	QShuttle *mShuttle;
	
	QPolygonEditor *mShuttleEditor;
	QShuttleKeyboardController *mShuttleController;
	QShuttleFuelTank *mShuttleFuelTank;
	QTabWidget *mTabWidget;

	OngletNav *ongletNav;
	OngletVehicule *mOngletVeh;
	OngletReservoir *mOngletRes;
	OngletPropulseurs *mOngletPropulseurs;

	QColorBox *colorBox;
	QTimer mTimer;


private slots:
	void tic();

protected slots:
	void updateShuttleFromGUI();
	void updateThrustersFromGUI();
	void createNav();
};

#endif //PROJETII_H
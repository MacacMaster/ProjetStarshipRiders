#ifndef ONGLET_RESERVOIR_H
#define ONGLET_RESERVOIR_H

#include <QtWidgets/QMainWindow>
#include "QShuttle.h"
#include "QPolygonalBody.h"
#include "QPolygonEditor.h"
#include "QPolygonFactory.h"
#include "QColorBox.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "QRealValueBox.h"
#include <QtWidgets/QLineEdit>
#include "OngletVehicule.h"
#include <QShuttleFuelTank.h>
#include<QIntValueBox.h>



class OngletReservoir : public QWidget
{
	Q_OBJECT

public:
	OngletReservoir(QShuttle * shuttle, QWidget *parent = nullptr);
	~OngletReservoir();

	void tankInitialize(QShuttle *shuttle);

private:
	QVBoxLayout *mWidgetLayout;
	QHBoxLayout *mTankLayout, *mOutlineLayout, *mFuelLayout;
	QLabel *mTankLabel, *mOutlineLabel, *mFuelLabel;
	QShuttleFuelTank *mShuttleFuelTank;
	QIntValueBox *mCapacity;
	QRealValueBox *mLevel;
	QRealValueBox *mWidth, *mHeight, *mHPosition, *mVPosition, *mOrientation;
	QColorBox *mColorTank, *mColorOutline, *mColorFuel;

signals:
	void valueChanged();
};

#endif //ONGLET_RESERVOIR_H


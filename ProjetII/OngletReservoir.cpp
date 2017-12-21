#include "OngletReservoir.h"
#include <QShuttleFuelTankShape.h>
#include <MathUtil.h>



OngletReservoir::OngletReservoir(QShuttle * shuttle, QWidget *parent)
	: QWidget(parent)
{

	mShuttleFuelTank = shuttle->fuelTanks().at(0);



	mCapacity = new QIntValueBox;
	mCapacity->addTitle("Capacite de carburant : ", 120);
	mCapacity->addUnit("kg", 50);
	mCapacity->setSpinFixedWidth(75);
	mCapacity->setRange(0, 1000000);

	mLevel = new QRealValueBox;
	mLevel->addTitle("Niveau de carburant", 120);
	mLevel->addUnit("-", 50);
	mLevel->setSpinFixedWidth(75);
	mLevel->setRange(0, 1);

	mWidth = new QRealValueBox;
	mWidth->addTitle("Largeur", 120);
	mWidth->addUnit("m", 50);
	mWidth->setSpinFixedWidth(75);
	mWidth->setRange(0, 1);

	mHeight = new QRealValueBox;
	mHeight->addTitle("Hauteur", 120);
	mHeight->addUnit("m", 50);
	mHeight->setSpinFixedWidth(75);
	mHeight->setRange(0, 1);

	mHPosition = new QRealValueBox;
	mHPosition->addTitle("Position horizontale", 120);
	mHPosition->addUnit("m", 50);
	mHPosition->setSpinFixedWidth(75);
	mHPosition->setRange(-1, 1);

	mVPosition = new QRealValueBox;
	mVPosition->addTitle("Position verticale", 120);
	mVPosition->addUnit("m", 50);
	mVPosition->setSpinFixedWidth(75);
	mVPosition->setRange(-1, 1);

	mOrientation = new QRealValueBox(1);
	mOrientation->addTitle("Orientation", 120);
	mOrientation->addUnit("°", 50);
	mOrientation->setSpinFixedWidth(75);
	mOrientation->setRange(0, 360);


	//Couleurs
	mTankLayout = new QHBoxLayout;
	mTankLabel = new QLabel("Couleur du reservoir : ");
	mColorTank = new QColorBox;
	mColorTank->setMaximumWidth(100);
	mTankLayout->addWidget(mTankLabel);
	mTankLayout->addWidget(mColorTank);

	mOutlineLayout = new QHBoxLayout;
	mOutlineLabel = new QLabel("Couleur du contour : ");
	mColorOutline = new QColorBox;
	mColorOutline->setMaximumWidth(100);
	mOutlineLayout->addWidget(mOutlineLabel);
	mOutlineLayout->addWidget(mColorOutline);

	mFuelLayout = new QHBoxLayout;
	mFuelLabel = new QLabel("Couleur du carburant : ");
	mColorFuel = new QColorBox;
	mColorFuel->setMaximumWidth(100);
	mFuelLayout->addWidget(mFuelLabel);
	mFuelLayout->addWidget(mColorFuel);


	//Widget de l'onglet
	mWidgetLayout = new QVBoxLayout;

	mWidgetLayout->addWidget(mCapacity);
	mWidgetLayout->addWidget(mLevel);
	mWidgetLayout->addWidget(mWidth);
	mWidgetLayout->addWidget(mHeight);
	mWidgetLayout->addWidget(mHPosition);
	mWidgetLayout->addWidget(mVPosition);
	mWidgetLayout->addWidget(mOrientation);

	mWidgetLayout->addLayout(mTankLayout);
	mWidgetLayout->addLayout(mOutlineLayout);
	mWidgetLayout->addLayout(mFuelLayout);

	setMaximumHeight(350);
	setLayout(mWidgetLayout);

	//Connections 


	//Initialisation
	tankInitialize(shuttle);
}


OngletReservoir::~OngletReservoir()
{
}

void OngletReservoir::tankInitialize(QShuttle * shuttle)
{

	mCapacity->setValue(mShuttleFuelTank->capacity());
	mLevel->setValue(mShuttleFuelTank->fuelLevel());
	mWidth->setValue(static_cast<QShuttleFuelTankShape*>(shuttle->shape())->width());
	mHeight->setValue(static_cast<QShuttleFuelTankShape*>(shuttle->shape())->height());
	mHPosition->setValue(shuttle->linearPosition().rx());
	mVPosition->setValue(shuttle->linearPosition().ry());
	mOrientation->setValue(Trigo<>::deg2rad(shuttle->angularPosition()));

	mColorTank->setColor(shuttle->shape()->brush().color());
	mColorOutline->setColor(shuttle->shape()->pen().color());
	mColorFuel->setColor(mShuttleFuelTank->fuelColor());
}

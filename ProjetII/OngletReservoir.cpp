#include "OngletReservoir.h"
#include <QShuttleFuelTankShape.h>
#include <MathUtil.h>



OngletReservoir::OngletReservoir(OngletVehicule *shuttleTab, QWidget *parent)
	: QWidget(parent),
	mShuttle{ shuttleTab->shuttle() },
	mShuttleFuelTank{ shuttleTab->shuttle()->fuelTanks().at(0) },
	mShuttleEditor {shuttleTab->polygonEditor()}

{

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
	mWidth->setRange(0.001, 1);

	mHeight = new QRealValueBox;
	mHeight->addTitle("Hauteur", 120);
	mHeight->addUnit("m", 50);
	mHeight->setSpinFixedWidth(75);
	mHeight->setRange(0.001, 1);

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
	mOrientation->setRange(-360, 360);


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

	//Initialisation
	tankInitialize(mShuttle);
	
	//Connections 
	connect(mCapacity, &QIntValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mLevel, &QRealValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mWidth, &QRealValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mHeight, &QRealValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mHPosition, &QRealValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mVPosition, &QRealValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mOrientation, &QRealValueBox::valueChanged, this, &OngletReservoir::changeTank);
	connect(mColorTank, &QColorBox::colorChanged, this, &OngletReservoir::changeTank);
	connect(mColorOutline, &QColorBox::colorChanged, this, &OngletReservoir::changeTank);
	connect(mColorFuel, &QColorBox::colorChanged, this, &OngletReservoir::changeTank);
	

}


OngletReservoir::~OngletReservoir()
{
}

void OngletReservoir::tankInitialize(QShuttle * shuttle)
{
	mColorFuel->blockSignals(true);
	
	mCapacity->setValueQuiet(shuttle->fuelTanks()[0]->capacity());
	mLevel->setValueQuiet(shuttle->fuelTanks()[0]->fuelLevel());
	mWidth->setValueQuiet(static_cast<QRectangularBody*>(shuttle->fuelTanks()[0]->shape())->width()/mShuttleEditor->outputScale());
	mHeight->setValueQuiet(static_cast<QRectangularBody*>(shuttle->fuelTanks()[0]->shape())->height()/mShuttleEditor->outputScale());
	mHPosition->setValueQuiet(shuttle->fuelTanks()[0]->linearPosition().rx()/mShuttleEditor->outputScale());
	mVPosition->setValueQuiet(shuttle->fuelTanks()[0]->linearPosition().ry()/mShuttleEditor->outputScale());
	mOrientation->setValueQuiet(Trigo<>::rad2deg(shuttle->fuelTanks()[0]->angularPosition()));
	mColorFuel->setColor(shuttle->fuelTanks()[0]->fuelColor());
	mColorTank->setColor(shuttle->fuelTanks()[0]->shape()->brush().color());
	mColorOutline->setColor(shuttle->fuelTanks()[0]->shape()->pen().color());

	mColorFuel->blockSignals(false);
}

void OngletReservoir::changeTank() {
	
	mShuttleFuelTank->setCapacity(mCapacity->value());
	mShuttleFuelTank->fill(mLevel->value());
	static_cast<QRectangularBody*>(mShuttleFuelTank->shape())->setWidth(mWidth->value()*mShuttleEditor->outputScale());
	static_cast<QRectangularBody*>(mShuttleFuelTank->shape())->setHeight(mHeight->value()*mShuttleEditor->outputScale());
	mShuttleFuelTank->setLinearPosition(QPointF(mHPosition->value()*mShuttleEditor->outputScale(), mVPosition->value()*mShuttleEditor->outputScale()));
	mShuttleFuelTank->setAngularPosition(Trigo<>::deg2rad(mOrientation->value()));

	mShuttleFuelTank->shape()->setBrush(mColorTank->color());
	mShuttleFuelTank->shape()->setPen(mColorOutline->color());
	mShuttleFuelTank->setFuelColor(mColorFuel->color());
}
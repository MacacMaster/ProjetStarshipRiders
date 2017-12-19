#include "OngletPropulseurs.h"
#include <QShuttleThruster.h>
#include <QThrusterKeyboardController.h>

/*
TODO : Set Massflow
*/

OngletPropulseurs::OngletPropulseurs(QShuttle * shuttle, QWidget *parent)
	: QWidget(parent)
{
	
	//Propulsion
	mPropulsion = new QGroupBox(tr("Propulsion"));
	mPropulsion->setLayout(new QVBoxLayout);
	mNombrePropulseurs = new QIntValueBox;
	mNombrePropulseurs->addTitle("Nombre de propulseurs : ", 120);
	mNombrePropulseurs->setSpinFixedWidth(50);
	mNombrePropulseurs->setRange(1, 10);
	mPropulsion->layout()->addWidget(mNombrePropulseurs);
	mPropulsion->layout()->setMargin(0);


	//Propulseur
	mPropulseur = new QGroupBox(tr("Propulseur"));
	mPropulseur->setLayout(new QVBoxLayout);
	
	//prop combobox
	QWidget * propulseurCombo=new QWidget;
	propulseurCombo->setLayout(new QHBoxLayout);
	mSelectPropulseurLabel = new QLabel;
	mSelectPropulseurLabel->setText("Sélection du propulseur :");
	mSelectPropulseurLabel->setAlignment(Qt::AlignLeft);
	mSelectPropulseurLabel->setFixedWidth(170);
	
	mSelectPropulseurValue = new QComboBox;
	propulseurCombo->layout()->setMargin(0);
	propulseurCombo->layout()->addWidget(mSelectPropulseurLabel);
	propulseurCombo->layout()->addWidget(mSelectPropulseurValue);
	mPropulseur->layout()->addWidget(propulseurCombo);

	//Separator
	QFrame* line = new QFrame();
	line->setFrameShape(QFrame::HLine);
	line->setFrameShadow(QFrame::Sunken);
	mPropulseur->layout()->addWidget(line);

	//RealValueBoxes
	mThrust=new QRealValueBox;
	createReal(mThrust, "Thrust : ", " - ",0.001,1000.000);

	mMasseSurfacique=new QRealValueBox;
	createReal(mMasseSurfacique, "Masse Surfacique : ", "kg / m²", 0.001, 1000.000);

	mDebitCarb=new QRealValueBox;
	createReal(mDebitCarb, "Débit massique du carburant : ", "kg² / s", 1.0, 250.0,1);

	mEjectionCarb=new QRealValueBox;
	createReal(mEjectionCarb, "Vitesse d'éjection du carburant : ", "m / s", 1.0, 250.0, 1);

	mPositionH=new QRealValueBox;
	createReal(mPositionH, "Position Horizontale : ", "m",-1000,1000);

	mPositionV=new QRealValueBox;
	createReal(mPositionV, "Position Verticale : ", "m", -1000, 1000);

	mOrientation=new QRealValueBox;
	createReal(mOrientation, "Orientation : ", "°", -360,360);

	//Keyboard Shortcut
	QWidget * keyShortcut = new QWidget;
	keyShortcut->setLayout(new QHBoxLayout);

	mToucheControleLabel = new QLabel;
	mToucheControleLabel->setText("Touche de contrôle :");
	mToucheControleLabel->setAlignment(Qt::AlignLeft);
	mToucheControleLabel->setFixedWidth(170);
	mToucheControleValue = new QKeySequenceEdit;

	keyShortcut->layout()->setMargin(0);
	keyShortcut->layout()->addWidget(mToucheControleLabel);
	keyShortcut->layout()->addWidget(mToucheControleValue);
	mPropulseur->layout()->addWidget(keyShortcut);
	//static_cast<QVBoxLayout*>(mPropulseur->layout())->addStretch();

	//Forme des Propulseurs
	mPolygonEditor = new QPolygonEditor(200);
	mFormePropulseur = new QGroupBox(tr("Forme du Propulseur"));
	mFormePropulseur->setLayout(new QVBoxLayout);
	mFormePropulseur->layout()->addWidget(mPolygonEditor);

	mMainLayout = new QVBoxLayout;
	setLayout(mMainLayout);
	mMainLayout->addWidget(mPropulsion);
	mMainLayout->addWidget(mPropulseur);
	mMainLayout->addWidget(mFormePropulseur);

	shuttleInitialize(shuttle);

	connect(mSelectPropulseurValue, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &OngletPropulseurs::thrusterChanged);
	//connect(mToucheControleValue, &QKeySequenceEdit::editingFinished, this, &OngletPropulseurs::polygonChanged);
	connect(mPolygonEditor, &QPolygonEditor::polygonUpdated, this, &OngletPropulseurs::polygonChanged);

}

//DRY
void OngletPropulseurs::createReal(QRealValueBox * qReal,QString title, QString unit, qreal rangeMin,qreal rangeMax, int32_t precision) {
	qReal->addTitle(title, 170);
	qReal->addUnit(unit, 50);
	qReal->setSpinFixedWidth(80);
	qReal->layout()->setMargin(0);
	qReal->setRange(rangeMin,rangeMax);
	qReal->setDecimals(precision);
	connect(qReal, &QRealValueBox::valueChanged, this, &OngletPropulseurs::polygonChanged);
	mPropulseur->layout()->addWidget(qReal);

}


OngletPropulseurs::~OngletPropulseurs()
{
}

//Updates Shuttle from GUI
void OngletPropulseurs::shuttleChange(QShuttle * shuttle)
{
	QShuttleThruster *temp = shuttle->thrusters()[mSelectPropulseurValue->currentIndex()];
	
	temp->setLinearPosition(QPointF(mPositionH->value(), mPositionV->value()));
	temp->setAngularPosition(Trigo<>::deg2rad(mOrientation->value()));
	static_cast<QPolygonalBody*>(temp->shape())->setPolygon(mPolygonEditor->polygon());
	temp->setSurfaceMass(mMasseSurfacique->value());
	//temp->setController(new QThrusterKeyboardController(mToucheControleValue->keySequence()));
	

	//
	//temp->setThrusterEfficiency();
	temp->setThrustLevel(mThrust->value());
	//mDebitCarb->setValueQuiet(temp->massFlowRate());
	//mEjectionCarb->setValueQuiet(temp->massEjectedSpeed());
}

//Sets Shuttle Info to GUI
void OngletPropulseurs::shuttleInitialize(QShuttle * shuttle)
{
	mShuttle = shuttle;
	int32_t i{ 0 };
	for (auto a : shuttle->thrusters()) {
		mSelectPropulseurValue->addItem(QString("Propulseur %1").arg(i));
		//mSelectPropulseurValue->addItem(a->name());
		++i;
	}
	mNombrePropulseurs->setValue(i);
	thrusterChanged(0);
}

void OngletPropulseurs::thrusterChanged(int index) {
	mPolygonEditor->blockSignals(true);
	mToucheControleValue->blockSignals(true);
	QShuttleThruster *temp = mShuttle->thrusters()[index];
	mPolygonEditor->setPolygon(static_cast<QPolygonalBody*>(temp->shape())->polygon());
	mPolygonEditor->setBrush(temp->shape()->brush());	//sychronize colorBox color with shuttle color
	mPolygonEditor->setPen(temp->shape()->pen());
	
	
	//???
	mThrust->setValueQuiet(temp->thrustLevel());

	mMasseSurfacique->setValueQuiet(temp->surfaceMass());
	mToucheControleValue->setKeySequence(static_cast<QThrusterKeyboardController*>(temp->controller())->linkedKey());
	mDebitCarb->setValueQuiet(temp->massFlowRate());
	mEjectionCarb->setValueQuiet(temp->massEjectedSpeed());
	mPositionH->setValueQuiet(temp->linearPosition().x());
	mPositionV->setValueQuiet(temp->linearPosition().y());
	mOrientation->setValueQuiet(Trigo<>::rad2deg(temp->angularPosition()));

	mPolygonEditor->blockSignals(false);
	mToucheControleValue->blockSignals(false);
}
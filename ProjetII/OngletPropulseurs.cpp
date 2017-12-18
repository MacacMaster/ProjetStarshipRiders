#include "OngletPropulseurs.h"



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


	QString p(QString("Propulseur %1").arg(3));
	
	//prop combobox
	QWidget * propulseurCombo=new QWidget;
	propulseurCombo->setLayout(new QHBoxLayout);
	mSelectPropulseurLabel = new QLabel;
	mSelectPropulseurLabel->setText("Sélection du propulseur :");
	mSelectPropulseurLabel->setAlignment(Qt::AlignLeft);
	mSelectPropulseurLabel->setFixedWidth(170);
	//mSelectPropulseurLabel->setFixedSize();
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
	mDimension=new QRealValueBox;
	createReal(mDimension, "Dimension : ", " - ");

	mMasseSurfacique=new QRealValueBox;
	createReal(mMasseSurfacique, "Masse Surfacique : ", "kg / m²");

	mDebitCarb=new QRealValueBox;
	createReal(mDebitCarb, "Débit massique du carburant : ", "kg² / s");

	mEjectionCarb=new QRealValueBox;
	createReal(mEjectionCarb, "Vitesse d'éjection du carburant : ", "m / s");

	mPositionH=new QRealValueBox;
	createReal(mPositionH, "Position Horizontale : ", "m");

	mPositionV=new QRealValueBox;
	createReal(mPositionV, "Position Verticale : ", "m");

	mOrientation=new QRealValueBox;
	createReal(mOrientation, "Orientation : ", "°");

	//Keyboard Shortcut
	QWidget * keyShortcut = new QWidget;
	keyShortcut->setLayout(new QHBoxLayout);

	mToucheControleLabel = new QLabel;
	mToucheControleLabel->setText("Touche de contrôle :");
	mToucheControleLabel->setAlignment(Qt::AlignLeft);
	mToucheControleLabel->setFixedWidth(170);
	mToucheControleValue = new QLineEdit;
	mToucheControleValue->setPlaceholderText("Press Keyboard Shortcut");

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

}

//DRY
void OngletPropulseurs::createReal(QRealValueBox * qReal,QString title, QString unit) {
	qReal->addTitle(title, 170);
	qReal->addUnit(unit, 50);
	qReal->setSpinFixedWidth(80);
	//qReal->setFixedHeight(40);
	qReal->layout()->setMargin(0);
	mPropulseur->layout()->addWidget(qReal);

}


OngletPropulseurs::~OngletPropulseurs()
{
}

//Updates Shuttle from GUI
void OngletPropulseurs::shuttleChange(QShuttle * shuttle)
{
	//static_cast<QPolygonalBody*>(shuttle->shape())->setPolygon(mPolygonEditor->polygon());
	//shuttle->shape()->setBrush(mPolygonEditor->brush());
	//shuttle->shape()->setPen(mPolygonEditor->pen());
	//shuttle->setName(mLineNom->text());
	//shuttle->setSurfaceMass(mMasseSurfacique->value());
}

//Sets Shuttle Info to GUI
void OngletPropulseurs::shuttleInitialize(QShuttle * shuttle)
{
	
	//
	//mPolygonEditor->setPolygon(static_cast<QPolygonalBody*>(shuttle->shape())->polygon());
	//mLineNom->setText(shuttle->name());
	//mMasseSurfacique->setValue(shuttle->surfaceMass());
	//mPolygonEditor->setBrush(shuttle->shape()->brush());	//sychronize colorBox color with shuttle color
	//mPolygonEditor->setPen(shuttle->shape()->pen());
}
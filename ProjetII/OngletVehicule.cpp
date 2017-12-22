#include "OngletVehicule.h"

OngletVehicule::OngletVehicule(QShuttle * shuttle,QWidget *parent)
	:	QWidget(parent),
		mShuttle{shuttle}
{

	//PolygonEditor (Needs Resize)
	mPolygonEditor = new QPolygonEditor(200);
	
	mPolygonEditorGB = new QGroupBox(tr("Forme"));
	mPolygonEditorGB->setLayout(new QVBoxLayout);
	mPolygonEditorGB->layout()->addWidget(mPolygonEditor);

	//Characteristiques
	mCharacteristiquesGB = new QGroupBox(tr("Characteristiques"));
	mCharacteristiquesGB->setLayout(new QVBoxLayout);
	//Nom
	mNomVaisseau = new QWidget;
	mNomVaisseau->setLayout(new QHBoxLayout);
	mLabelNom = new QLabel;
	mLabelNom->setText("Nom:");
	mLabelNom->setAlignment(Qt::AlignLeft);
	mLabelNom->setMinimumWidth(100);
	mLineNom = new QLineEdit;
	mNomVaisseau->layout()->addWidget(mLabelNom);
	mNomVaisseau->layout()->addWidget(mLineNom);

	//MasseSurfacique
	mMasseSurfacique = new QRealValueBox;
	mMasseSurfacique->addTitle("Masse Surfacique", 100);
	mMasseSurfacique->addUnit("kg", 20);
	//mMasseSurfacique

	mCharacteristiquesGB->layout()->addWidget(mNomVaisseau);
	mCharacteristiquesGB->layout()->addWidget(mMasseSurfacique);
	//Tab  Vehicule
	setLayout(new QVBoxLayout);
	layout()->addWidget(mCharacteristiquesGB);
	layout()->addWidget(mPolygonEditorGB);

	connect(mPolygonEditor, &QPolygonEditor::polygonUpdated, this, &OngletVehicule::polygonChanged);
	connect(mLineNom, &QLineEdit::textChanged, this, &OngletVehicule::polygonChanged);
	connect(mMasseSurfacique, &QRealValueBox::valueChanged, this, &OngletVehicule::polygonChanged);

	shuttleInitialize(shuttle);

}



OngletVehicule::~OngletVehicule()
{
}
//Updates Shuttle from GUI
void OngletVehicule::shuttleChange(QShuttle * shuttle)
{
	static_cast<QPolygonalBody*>(shuttle->shape())->setPolygon(mPolygonEditor->polygon());
	shuttle->shape()->setBrush(mPolygonEditor->brush());
	shuttle->shape()->setPen(mPolygonEditor->pen());
	shuttle->setName(mLineNom->text());
	shuttle->setSurfaceMass(mMasseSurfacique->value());
}

//Sets Shuttle Info to GUI
void OngletVehicule::shuttleInitialize(QShuttle * shuttle)
{
	mPolygonEditor->setPolygon(static_cast<QPolygonalBody*>(shuttle->shape())->polygon());
	//mPolygonEditor->setOutputScale(shuttle->shape()->);
	mLineNom->setText(shuttle->name());
	mMasseSurfacique->setValue(shuttle->surfaceMass());
	mPolygonEditor->setBrush(shuttle->shape()->brush());	//sychronize colorBox color with shuttle color
	mPolygonEditor->setPen(shuttle->shape()->pen());
}

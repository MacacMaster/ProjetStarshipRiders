#include "ongletVehicule.h"



OngletVehicule::OngletVehicule(QPolygonF polygonF,QWidget *parent)
	: QWidget(parent)
{
	//PolygonEditor (Needs Resize)
	mPolygonEditor = new QPolygonEditor(200);
	mPolygonEditor->setPolygon(polygonF);
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

	mCharacteristiquesGB->layout()->addWidget(mNomVaisseau);
	mCharacteristiquesGB->layout()->addWidget(mMasseSurfacique);
	//Tab  Vehicule
	setLayout(new QVBoxLayout);
	layout()->addWidget(mCharacteristiquesGB);
	layout()->addWidget(mPolygonEditorGB);
}



OngletVehicule::~OngletVehicule()
{
}

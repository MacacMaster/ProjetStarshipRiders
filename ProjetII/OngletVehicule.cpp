#include "ongletVehicule.h"



OngletVehicule::OngletVehicule(QWidget *parent)
	: QWidget(parent)
{
	//PolygonEditor (Needs Resize)
	polygonEditor = new QPolygonEditor(200);
	polygonEditorGB = new QGroupBox(tr("Forme"));
	polygonEditorGB->setLayout(new QVBoxLayout);
	polygonEditorGB->layout()->addWidget(polygonEditor);

	//Characteristiques
	characteristiquesGB = new QGroupBox(tr("Characteristiques"));
	characteristiquesGB->setLayout(new QVBoxLayout);
	//Nom
	nomVaisseau = new QWidget;
	nomVaisseau->setLayout(new QHBoxLayout);
	labelNom = new QLabel;
	labelNom->setText("Nom:");
	labelNom->setAlignment(Qt::AlignLeft);
	labelNom->setMinimumWidth(100);
	lineNom = new QLineEdit;
	nomVaisseau->layout()->addWidget(labelNom);
	nomVaisseau->layout()->addWidget(lineNom);


	//MasseSurfacique
	masseSurfacique = new QRealValueBox;
	masseSurfacique->addTitle("Masse Surfacique", 100);
	masseSurfacique->addUnit("kg", 20);

	characteristiquesGB->layout()->addWidget(nomVaisseau);
	characteristiquesGB->layout()->addWidget(masseSurfacique);
	//Tab  Vehicule
	setLayout(new QVBoxLayout);
	layout()->addWidget(characteristiquesGB);
	layout()->addWidget(polygonEditorGB);
}



OngletVehicule::~OngletVehicule()
{
}

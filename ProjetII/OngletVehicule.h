#pragma once

#include "ProjetII.h"

class OngletVehicule : public QWidget
{
public:
	OngletVehicule(QWidget *parent = nullptr);
	~OngletVehicule();

private:
	QGroupBox *characteristiquesGB;
	QPolygonEditor *polygonEditor;
	QGroupBox *polygonEditorGB;
	QWidget *nomVaisseau;
	QLabel *labelNom;
	QLineEdit *lineNom;
	QRealValueBox *masseSurfacique;
};


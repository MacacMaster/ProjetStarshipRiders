#pragma once

#include "ProjetII.h"

class OngletVehicule : public QWidget
{
public:
	OngletVehicule(QPolygonF polygonF,QWidget *parent = nullptr);
	~OngletVehicule();

	//QPolygonEditor * polygonEditor() { return mPolygonEditor; }

private:
	QGroupBox *mCharacteristiquesGB;
	QPolygonEditor *mPolygonEditor;
	QGroupBox *mPolygonEditorGB;
	QWidget *mNomVaisseau;
	QLabel *mLabelNom;
	QLineEdit *mLineNom;
	QRealValueBox *mMasseSurfacique;
};


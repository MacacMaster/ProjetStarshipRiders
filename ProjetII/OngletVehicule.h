#ifndef ONGLET_VEHICULE_H
#define ONGLET_VEHICULE_H

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


class OngletVehicule : public QWidget
{
	Q_OBJECT

public:
	OngletVehicule(QShuttle * shuttle,QWidget *parent = nullptr);
	~OngletVehicule();

	QPolygonEditor * polygonEditor() { return mPolygonEditor; }
	QLineEdit *name() { return mLineNom; }
	QRealValueBox *surfaceMass() { return mMasseSurfacique; }
	QShuttle *shuttle() { return mShuttle; }

	void shuttleChange(QShuttle * shuttle);//Updates Shuttle info from GUI
	void shuttleInitialize(QShuttle * shuttle);//Reads shuttle info and shows in GUI

private:
	QShuttle *mShuttle;
	QGroupBox *mCharacteristiquesGB;
	QPolygonEditor *mPolygonEditor;
	QGroupBox *mPolygonEditorGB;
	QWidget *mNomVaisseau;
	QLabel *mLabelNom;
	QLineEdit *mLineNom;
	QRealValueBox *mMasseSurfacique;

signals:
	void polygonChanged();
};

#endif //ONGLET_VEHICULE_H

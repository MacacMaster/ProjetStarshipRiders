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
#include <OngletNav.h>


class OngletVehicule : public QWidget
{
	Q_OBJECT

public:
	OngletVehicule(QShuttle * shuttle, OngletNav * nav, QWidget *parent = nullptr);
	~OngletVehicule();

	QPolygonEditor * polygonEditor() { return mPolygonEditor; }
	QLineEdit *name() { return mLineNom; }
	QRealValueBox *surfaceMass() { return mMasseSurfacique; }

	void shuttleChange(QShuttle * shuttle);//Updates Shuttle info from GUI
	void shuttleInitialize(QShuttle * shuttle);
	void setShuttleSelectedName(const QString & selected);
	//Reads shuttle info and shows in GUI

private:
	OngletNav * mNav;
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

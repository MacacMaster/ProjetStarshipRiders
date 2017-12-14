#pragma once

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

	void shuttleChange(QShuttle * shuttle);
	void shuttleInitialize(QShuttle * shuttle);

private:
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


#ifndef ONGLET_PROPULSEURS_H
#define ONGLET_PROPULSEURS_H


#include <QtWidgets/QMainWindow>
#include "QShuttle.h"
#include "QPolygonalBody.h"
#include "QPolygonEditor.h"
#include "QPolygonFactory.h"
#include "QColorBox.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "QRealValueBox.h"
#include "QIntValueBox.h"
#include <QtWidgets/QKeySequenceEdit>
#include <QtWidgets/QCombobox>
#include"OngletVehicule.h"
#include <QStringListModel>

class OngletPropulseurs : public QWidget
{
	Q_OBJECT

public:
	OngletPropulseurs(OngletVehicule *shuttleTab, QWidget *parent = nullptr);
	



	~OngletPropulseurs();

	void shuttleChange(QShuttle * shuttle);//Updates Shuttle info from GUI
	void shuttleInitialize(QShuttle * shuttle);
	void addNewThruster();
	void removeThruster();

	//Reads shuttle info and shows in GUI

private:
	QShuttle * mShuttle;
	QVBoxLayout *mMainLayout;
	QGroupBox *mPropulsion;
	QGroupBox *mPropulseur;
	QGroupBox *mFormePropulseur;
	QPolygonEditor *mPolygonEditor, *mShuttleEditor;
	QLabel *mSelectPropulseurLabel;
	QComboBox *mSelectPropulseurValue;
	QLabel *mToucheControleLabel;
	QKeySequenceEdit *mToucheControleValue;
	QRealValueBox *mThrust;
	QRealValueBox *mMasseSurfacique;
	QRealValueBox *mDebitCarb;
	QRealValueBox *mEjectionCarb;
	QRealValueBox *mPositionH;
	QRealValueBox *mPositionV;
	QRealValueBox *mOrientation;
	QIntValueBox *mNombrePropulseurs;
	QStringListModel * thrusterList;
	

	void createReal(QRealValueBox * qReal, QString title, QString unit, qreal rangeMin = 0, qreal rangeMax = 99.99, int32_t precision = 3);
	
protected slots:
	void thrusterChanged(int index);
	void changeThrusterQuantity();

signals:
	void polygonChanged();
};

#endif //ONGLET_PROPULSEURS_H
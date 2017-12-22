#ifndef ONGLET_NAV
#define ONGLET_NAV

#include <QtWidgets/QMainWindow>
#include <QCheckBox>

#include <QStringListModel>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "QRealValueBox.h"
#include <qpushbutton.h>
#include "qcombobox.h"
#include "QSceneViewController.h"


class OngletNav : public QWidget
{
	Q_OBJECT

public:
	OngletNav(QSceneViewController * view, QShuttle * shuttle, QWidget *parent = nullptr);
	~OngletNav();

	void setNavList(QStringList list);

	void setShuttleSelectedName(const QString &);
	void updateStatus(QString status);
	void updateStatus(QString status, QShuttle * shuttle);
	
	QString selectedName();
	QRealValueBox* navBoxTaille() { return mNavBoxTaille; }

private:
	QShuttle * mShuttle;
	QSceneViewController *mView;
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QGroupBox *navSelectionGB;
	QComboBox *mComboBox;
	QRealValueBox *mNavBoxTaille;
	QPushButton *mReinitialize;
	QStringList navettesList;

	QGroupBox *mSimulationOptions;
	QCheckBox *mSimulCenter;

	QGroupBox *mStatusGB;
	QLabel *mStatus;
	QGroupBox *mSelectedShuttleGB;
	QLabel *mSelectedShuttle;
	QStringListModel * shuttleList;

	QGroupBox * mDatabaseGB;
	QGroupBox * mShuttleOptions;
	QPushButton* mLoadShuttle;
	QPushButton* mSaveShuttle;
	QPushButton* mNewShuttle;
	QPushButton* mDeleteShuttle;
protected slots:
	void simulCenter(int state);
	void reinitialize();
signals:
	void navCreated();
	void newShuttleSignal ();
	void loadShuttleSignal();
	void saveShuttleSignal();
	void deleteShuttleSignal();
};
#endif // ONGLET_NAV
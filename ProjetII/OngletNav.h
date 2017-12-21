#ifndef ONGLET_NAV
#define ONGLET_NAV

#include <QtWidgets/QMainWindow>
#include <QCheckBox>


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
	OngletNav(QSceneViewController * view, QWidget *parent = nullptr);
	~OngletNav();

	void setNavList(QStringList list);

	void updateStatus(QString status);
	QRealValueBox* navBoxTaille() { return mNavBoxTaille; }

private:
	QSceneViewController *mView;
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QGroupBox *navSelectionGB;
	QComboBox *mComboBox;
	QRealValueBox *mNavBoxTaille;
	QPushButton *navBtnCreer;
	QStringList navettesList;

	QGroupBox *mSimulationOptions;
	QCheckBox *mSimulCenter;

	QGroupBox *mStatusGB;
	QLabel *mStatus;

	QGroupBox * mDatabaseGB;
	QGroupBox * mShuttleOptions;
	QPushButton* mLoadShuttle;
	QPushButton* mSaveShuttle;
	QPushButton* mNewShuttle;
	QPushButton* mDeleteShuttle;
protected slots:
	void simulCenter(int state);

signals:
	void navCreated();
	void newShuttleSignal ();
	void loadShuttleSignal();
	void saveShuttleSignal();
	void deleteShuttleSignal();
};
#endif // ONGLET_NAV
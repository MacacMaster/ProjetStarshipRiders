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

	void updateStatus(QString status);

	QRealValueBox* navBoxTaille() { return mNavBoxTaille; }

private:
	QSceneViewController *mView;
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QGroupBox *navSelectionGB;
	QComboBox *mComboBox;
	QRealValueBox *mNavBoxTaille;
	QPushButton *navBtnCreer;
	QStringList navettesList{ "Horizon 6TK", "Navette2" };

	QGroupBox *mSimulationOptions;
	QCheckBox *mSimulCenter;

	QGroupBox *mStatusGB;
	QLabel *mStatus;
protected slots:
	void simulCenter(int state);

signals:
	void navCreated();
};
#endif // ONGLET_NAV
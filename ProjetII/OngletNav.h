#ifndef ONGLET_NAV
#define ONGLET_NAV

#include <QtWidgets/QMainWindow>



#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "QRealValueBox.h"
#include <qpushbutton.h>
#include "qcombobox.h"



class OngletNav : public QWidget
{
	Q_OBJECT

public:
	OngletNav(QWidget *parent = nullptr);
	~OngletNav();

	QRealValueBox* navBoxTaille() { return mNavBoxTaille; }

private:
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QGroupBox *navSelectionGB;
	QComboBox *mComboBox;
	QRealValueBox *mNavBoxTaille;
	QPushButton *navBtnCreer;
	QStringList navettesList{ "Horizon 6TK", "Navette2" };


signals:
	void navCreated();
};
#endif // ONGLET_NAV
#pragma once

#include "ProjetII.h"


class OngletNav : public QWidget
{
	//Q_OBJECT

public:
	OngletNav(QWidget *parent = nullptr);
	~OngletNav();


private:
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QGroupBox *navSelectionGB;
	QComboBox *comboBox;
	QRealValueBox *navBoxTaille;
	QPushButton *navBtnCreer;
	QStringList navettesList{ "Horizon 6TK", "Navette2" };
};

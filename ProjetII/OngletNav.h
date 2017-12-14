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
	QRealValueBox *navBoxTaille;
	QPushButton *navBtnCreer;
};

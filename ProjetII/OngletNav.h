#pragma once

#include "ProjetII.h"


class OngletNav : public QWidget
{
	Q_OBJECT

public:
	OngletNav(QWidget *parent = nullptr);
	~OngletNav();

	QComboBox* comboBox() { return mComboBox; }

private:
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QGroupBox *navSelectionGB;
	QComboBox *mComboBox;
	QRealValueBox *navBoxTaille;
	QPushButton *navBtnCreer;
	QStringList navettesList{ "Horizon 6TK", "Navette2" };


signals:
	void navCreated();
};

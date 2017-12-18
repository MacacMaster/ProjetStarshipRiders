#ifndef NAVETTE_PREDETERMINEE_H
#define NAVETTE_PREDETERMINEE_H

#include "ProjetII.h"
class NavettePredeterminee :
	public QWidget
{
public:
	NavettePredeterminee(QWidget *parent = nullptr);
	~NavettePredeterminee();

	QWidget* navWidget() { return mNavWidget; };

private:
	QWidget *mNavWidget, *navTailleWidget;
	QVBoxLayout *navWidgetLayout, *navSelectionLayout;
	QHBoxLayout *navTailleLayout;
	QGroupBox *navSelectionGB;
	QRealValueBox *navBoxTaille;
	QPushButton *navBtnCreer;
	QLabel *navLblTaille, *navLblPixel;
};

#endif //NAVETTE_PREDETERMINEE_H

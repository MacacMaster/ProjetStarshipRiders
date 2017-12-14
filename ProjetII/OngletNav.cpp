#include "OngletNav.h"


OngletNav::OngletNav(QWidget *parent)
	: QWidget(parent)
{

	//Ensemble pour la taille
	navBoxTaille = new QRealValueBox;
	navBoxTaille->addUnit("pixels");
	navBoxTaille->addTitle("Taille:");
	

	//GroupBox Selection
	navSelectionLayout = new QVBoxLayout;
	navSelectionGB = new QGroupBox("Selection");
	navBtnCreer = new QPushButton("Creer");
	navSelectionLayout->addWidget(navBoxTaille);
	navSelectionLayout->addWidget(navBtnCreer);
	navSelectionGB->setLayout(navSelectionLayout);


	//Widget de l'onglet (principal)
	navWidgetLayout = new QVBoxLayout;
	navWidgetLayout->addWidget(navSelectionGB);
	setMaximumHeight(150);
	setLayout(navWidgetLayout);

}

OngletNav::~OngletNav()
{
}

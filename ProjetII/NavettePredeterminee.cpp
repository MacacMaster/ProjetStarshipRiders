#include "NavettePredeterminee.h"



NavettePredeterminee::NavettePredeterminee(QWidget *parent)
	: QWidget(parent)
{
	
	//Ensemble pour la taille
	navTailleWidget = new QWidget;
	navTailleLayout = new QHBoxLayout;
	navLblTaille = new QLabel("Taille");
	navBoxTaille = new QRealValueBox;
	navLblPixel = new QLabel("Pixel");
	navTailleLayout->addWidget(navLblTaille);
	navTailleLayout->addWidget(navBoxTaille);
	navTailleLayout->addWidget(navLblPixel);
	navTailleWidget->setLayout(navTailleLayout);

	//Section Selection
	navSelectionLayout = new QVBoxLayout;
	navSelectionGB = new QGroupBox("Selection");
	navBtnCreer = new QPushButton("Creer");
	navSelectionLayout->addWidget(navTailleWidget);
	navSelectionLayout->addWidget(navBtnCreer);
	navSelectionGB->setLayout(navSelectionLayout);
	
	
	//Widget de l'onglet (principal)
	navWidgetLayout = new QVBoxLayout;
	navWidgetLayout->addWidget(new QLabel("HELLLO"));
	setLayout(navWidgetLayout);

}


NavettePredeterminee::~NavettePredeterminee()
{
}
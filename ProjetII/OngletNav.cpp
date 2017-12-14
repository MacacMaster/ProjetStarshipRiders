#include "OngletNav.h"


OngletNav::OngletNav(QWidget *parent)
	: QWidget(parent)
{

	//Ensemble pour la taille
	mNavBoxTaille = new QRealValueBox;
	mNavBoxTaille->addUnit("pixels");
	mNavBoxTaille->addTitle("Taille:");
	

	//GroupBox Selection
	navSelectionLayout = new QVBoxLayout;
	navSelectionGB = new QGroupBox("Selection");
	navBtnCreer = new QPushButton("Creer");
	mComboBox = new QComboBox(this);
	mComboBox->addItems(navettesList);
	

	navSelectionLayout->addWidget(mComboBox);
	navSelectionLayout->addWidget(mNavBoxTaille);
	navSelectionLayout->addWidget(navBtnCreer);
	navSelectionGB->setLayout(navSelectionLayout);


	//Widget de l'onglet (principal)
	navWidgetLayout = new QVBoxLayout;
	navWidgetLayout->addWidget(navSelectionGB);
	setMaximumHeight(150);
	setLayout(navWidgetLayout);


	connect(navBtnCreer, &QPushButton::clicked, this, &OngletNav::navCreated);
}

OngletNav::~OngletNav()
{
}

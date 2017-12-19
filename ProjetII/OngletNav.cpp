#include "OngletNav.h"


OngletNav::OngletNav(QSceneViewController *view, QWidget *parent)
	: QWidget(parent)
{
	mView = view;
	mView->targetShuttle();
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


	
	//disable cause bugs -> could integrate SQL and just scrap this shit
	navBtnCreer->setEnabled(false);

	navSelectionLayout->addWidget(mComboBox);
	navSelectionLayout->addWidget(mNavBoxTaille);
	navSelectionLayout->addWidget(navBtnCreer);
	navSelectionGB->setLayout(navSelectionLayout);

	//Simulation
	mSimulationOptions = new QGroupBox("Simulation");
	mSimulationOptions->setLayout(new QVBoxLayout);
	mSimulCenter = new QCheckBox("Centrer le vaisseau");
	mSimulCenter->setTristate(false);
	mSimulCenter->setChecked(true);
	mSimulationOptions->layout()->addWidget(mSimulCenter);

	//Widget de l'onglet (principal)
	navWidgetLayout = new QVBoxLayout;
	navWidgetLayout->addWidget(navSelectionGB);
	navWidgetLayout->addWidget(mSimulationOptions);
	navWidgetLayout->addStretch();
	
	
	//setMaximumHeight(350);
	setLayout(navWidgetLayout);

	connect(mSimulCenter, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, &OngletNav::simulCenter);
	/*
Qt::Unchecked	0	The item is unchecked.
Qt::PartiallyChecked	1	The item is partially checked. Items in hierarchical models may be partially checked if some, but not all, of their children are checked.
Qt::Checked	2	The item is checked.
*/
	connect(navBtnCreer, &QPushButton::clicked, this, &OngletNav::navCreated);
}

OngletNav::~OngletNav()
{
}

void OngletNav::simulCenter(int state)
{
	mSimulCenter->blockSignals(true);
	if (state == Qt::Checked) {
		mView->targetShuttle();
	}
	else {
		mView->resetTarget();
	}
	mSimulCenter->blockSignals(false);
}

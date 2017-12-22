#include "OngletNav.h"
#include <ProjetII.h>

OngletNav::OngletNav(QSceneViewController *view, QWidget *parent)
	: QWidget(parent)
{
	
	//navettesList.push_back(static_cast<ProjetII*>(parent)->shuttle()->name());
	mView = view;
	mView->targetShuttle();
	//Ensemble pour la taille
	mNavBoxTaille = new QRealValueBox;
	mNavBoxTaille->addUnit("pixels");
	mNavBoxTaille->addTitle("Taille:");
	

	//GroupBox Selection
	navSelectionLayout = new QVBoxLayout;
	navSelectionGB = new QGroupBox("Selection");
	mComboBox = new QComboBox(this);
	//liste navettes
	shuttleList = new QStringListModel(navettesList);
	mComboBox->setModel(shuttleList);
	navSelectionLayout->addWidget(mComboBox);
	navSelectionLayout->addWidget(mNavBoxTaille);
	navSelectionGB->setLayout(navSelectionLayout);

	//Simulation
	mSimulationOptions = new QGroupBox("Simulation");
	mSimulationOptions->setLayout(new QVBoxLayout);
	mSimulCenter = new QCheckBox("Centrer le vaisseau");
	mSimulCenter->setTristate(false);
	mSimulCenter->setChecked(true);
	mSimulationOptions->layout()->addWidget(mSimulCenter);

	//Status
	mStatusGB = new QGroupBox("Status");
	mStatusGB->setLayout(new QVBoxLayout);
	mStatus = new QLabel;
	mStatusGB->layout()->addWidget(mStatus);

	//Selected Shuttle
	mSelectedShuttleGB = new QGroupBox("Selected Shuttle");
	mSelectedShuttleGB->setLayout(new QVBoxLayout);
	mSelectedShuttle = new QLabel;
	mSelectedShuttleGB->layout()->addWidget(mSelectedShuttle);

	//DB Options
	mDatabaseGB = new QGroupBox("PostgreSQL");
	mDatabaseGB->setLayout(new QVBoxLayout);
	mShuttleOptions = new QGroupBox("Shuttle Options");
	mShuttleOptions->setLayout(new QHBoxLayout);
	mLoadShuttle = new QPushButton("Load");
	mSaveShuttle = new QPushButton("Save");
	mNewShuttle = new QPushButton("Save as New");
	mDeleteShuttle = new QPushButton("Delete");
	mShuttleOptions->layout()->addWidget(mLoadShuttle);
	mShuttleOptions->layout()->addWidget(mSaveShuttle);
	mShuttleOptions->layout()->addWidget(mNewShuttle);
	mShuttleOptions->layout()->addWidget(mDeleteShuttle);
	mDatabaseGB->layout()->addWidget(mShuttleOptions);



	//Widget de l'onglet (principal)
	navWidgetLayout = new QVBoxLayout;
	navWidgetLayout->addWidget(mStatusGB);
	navWidgetLayout->addWidget(mSelectedShuttleGB);
	navWidgetLayout->addWidget(navSelectionGB);
	navWidgetLayout->addWidget(mSimulationOptions);
	navWidgetLayout->addWidget(mDatabaseGB);
	navWidgetLayout->addStretch();
	


	//setMaximumHeight(350);
	setLayout(navWidgetLayout);

	//Connections
	connect(mSimulCenter, static_cast<void(QCheckBox::*)(int)>(&QCheckBox::stateChanged), this, &OngletNav::simulCenter);
	//connect(mComboBox, static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::currentTextChanged), this, &OngletNav::setShuttleSelectedName);
	/*
Qt::Unchecked	0	The item is unchecked.
Qt::PartiallyChecked	1	The item is partially checked. Items in hierarchical models may be partially checked if some, but not all, of their children are checked.
Qt::Checked	2	The item is checked.
*/
	//connect(navBtnCreer, &QPushButton::clicked, this, &OngletNav::navCreated);
	connect(mNewShuttle, &QPushButton::clicked, this,	&OngletNav::newShuttleSignal);
	connect(mLoadShuttle, &QPushButton::clicked, this,	&OngletNav::loadShuttleSignal);
	connect(mSaveShuttle, &QPushButton::clicked, this,	&OngletNav::saveShuttleSignal);
	connect(mDeleteShuttle, &QPushButton::clicked, this,&OngletNav::deleteShuttleSignal);
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
void OngletNav::setNavList(QStringList list) {
	shuttleList->setStringList(list);
	mComboBox->setModel(shuttleList);
}

void OngletNav::setShuttleSelectedName(const QString & selected) {
	mSelectedShuttle->setText(selected);
}
void OngletNav::updateStatus(QString status) {
	mStatus->setText(status);
}

void OngletNav::updateStatus(QString status,QShuttle * shuttle) {	
	setShuttleSelectedName(shuttle->name());
	updateStatus(status);
}

QString OngletNav::selectedName() { return mComboBox->currentText(); }


#include "ProjetII.h"

ProjetII::ProjetII(QWidget *parent)
	:	QMainWindow(parent),
		mSceneModel(QSizeF(500.0,500.0))
{
	ui.setupUi(this);

	

	mSceneController->setSceneModel(&mSceneModel);
	
	
}



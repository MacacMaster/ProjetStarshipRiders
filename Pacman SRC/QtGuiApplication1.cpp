#include "QtGuiApplication1.h"
#include <QPainter> // pas besoin de le mettre dans le .h
#include <QStaticEntity.h>
#include <QDynamicEntity.h>
#include <random>
#include <QBouffe.h>
#include <QPacman.h>
#include <QFantome.h>

QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent),
    mSceneSize(x,y) // initializer list
		// utiliser le constructeur à deux paramètres
{

	for (int i = 0; i < 20; i++)
	{
		mEntities.append(new QPacman(
			20.0,
			QPointF(rand()%x, rand()%y),
			Qt::yellow,
			QPen(Qt::red, 2.0)
		));

		mEntities.append(
			new QBouffe(
				QSizeF(10.0, 10.0),
				QPointF(rand()%x, rand()%y),
				Qt::red,
				QPen(Qt::red, 2.0)));
		
		mEntities.append(new QFantome(
			20.0,
			QPointF(rand() % x, rand() % y),
			Qt::blue,
			QPen(Qt::red, 2.0)
		));
		
	}






	ui.setupUi(this);
	mScene = new QLabel;
	mScene->setFixedSize(mSceneSize);

	


	QPixmap pixmap(mSceneSize);



	QPainter painter(&pixmap); // plusieurs constructeurs. on peut lui passer un QPaintDevice
	painter.setPen(QPen(QColor(0,0,0),1.0)); // Qcolor... objet anynonyme ou objet temporaire même chose pour QPen
	painter.setBrush(QColor(255,0,255)); // le compilateur crée un objet QBrush anonyme, donc pas besoin de créer manuellement un QBrush
	painter.drawRect(10, 200, 200, 10); // left top width height
	





	QStaticEntity cool(
		QSizeF(100.0,200.0),
		QPointF(0.0, 0.0),
		Qt::yellow,
		QPen(Qt::red, 2.0));
		
	//QStaticEntity chill();


	QDynamicEntity chill(
		55.0,
		QPointF(50.0, 200.0),
		Qt::red,
		QPen(Qt::yellow, 2.0)
	);



	chill.paint(painter);
	cool.paint(painter);
	
	
	mScene->setPixmap(pixmap);




	setCentralWidget(mScene);
	
	// connexion pour le tic
	connect(&mTimer, &QTimer::timeout, this, &QtGuiApplication1::tic);
	// connect(&mTimer, &QTimer::timeout, this, QtGuiApplication1::tic());
	mTimer.start(40);
}

void QtGuiApplication1::tic()
{
	for (auto const & entity : mEntities)
	{
		if (dynamic_cast<QPredateur*> (entity) != NULL)
		{
			dynamic_cast<QPredateur*>(entity)->tic(mEntities);
		}
		else if (dynamic_cast<QBouffe*> (entity) != NULL)
		{
			entity->tic();
		}	
	}
	paint(); // redessiner tout
}

QtGuiApplication1::~QtGuiApplication1()
{
	// boucle for pour détruire toutes les entités
	for (auto & entity : mEntities)
	{
		delete entity;
		entity = nullptr;
	}
}

void QtGuiApplication1::paint()
{
	QPixmap pixmap(mSceneSize); // pixmap c'est une surface de dessin
	QPainter painter(&pixmap);
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(Qt::NoPen);
	painter.setBrush(QColor(64, 0, 64));
	painter.drawRect(QRectF(QPointF(0.0,0.0),mSceneSize));// dessiner le background

	// boucle for pour dessiner toutes les entités
	for (auto const & entity : mEntities)
	{
		// if (QBouffe& b == dynamic_cast<QBouffe&>(entity))
		// if (QBouffe& b == dynamic_cast<QBouffe&>(entity))
			// pull et push
			painter.save();
			painter.translate(entity->position());
			painter.rotate(entity->orientation()); // la fonction rotate de qt est en degrés (et non en radians)
			entity->paint(painter);
			painter.restore();
	}
	mScene->setPixmap(pixmap);
}

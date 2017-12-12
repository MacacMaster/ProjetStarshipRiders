#include "QFantome.h"



QFantome::QFantome()
{
}


QFantome::~QFantome()
{
}

QFantome::QFantome(qreal radius, QPointF const & position, QBrush const & brush, QPen const & pen)
	:QPredateur(radius, position, brush, pen)
{
}

void QFantome::tic()
{
	double x{ 1.0 };
	double y{ 1.0 };






	mPosition += QPointF(x, y); // un droite, un bas
}

QEntity * QFantome::typeDeVictime()
{
	return nullptr;
}

void QFantome::tic(QList<QEntity*> mEntities)
{
	QBouffe *b;
	double distance{ 0 };
	QBouffe *tempo;
	double min = 9999999.9;
	for (auto const & entity : mEntities)
	{
		// if (QBouffe& b == dynamic_cast<QBouffe&>(entity))
		// if (QBouffe& b == dynamic_cast<QBouffe&>(entity))
		//if (typeid(entity) == typeid(*typeDeVictime()))
		if (dynamic_cast<QBouffe*> (entity) != NULL)
		{
			b = dynamic_cast<QBouffe*> (entity);
			distance = distanceSeparee(b);
			if (min > distance)
			{
				min = distance;
				tempo = b;
			}
		}
	}

	deplacement(tempo);
}





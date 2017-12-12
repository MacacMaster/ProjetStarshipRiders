#include "QPredateur.h"
#include <typeinfo>

QPredateur::QPredateur()
{
}


QPredateur::~QPredateur()
{
}

QPredateur::QPredateur(qreal radius, QPointF const & position, QBrush const & brush, QPen const & pen)
	:
QDynamicEntity(radius,position,brush,pen)
{

}

double QPredateur::distanceSeparee(QEntity const * bouffe)
{
	double x; 
	double y;
	x = bouffe->position().x() - position().x();
	y = bouffe->position().y() - position().y();
	double distance = sqrt(pow(x, 2) + pow(y, 2));

	return distance;
}




/*
void QPredateur::tic(QList<QEntity*> mEntities)
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
*/

void QPredateur::deplacement(QEntity * tempo)
{
	double x{ 0 };
	double y{ 0 };
	
	if (tempo->position().x() > position().x())
	{
		x = 1;
	}
	else
	{
		x = -1;
	}

	if (tempo->position().y() > position().y())
	{
		y = 1;
	}
	else
	{
		y = -1;
	}
	mPosition += QPointF(x, y);
}

#pragma once
#include "QDynamicEntity.h"
#include "QBouffe.h"
class QPredateur :
	public QDynamicEntity
{
public:
	QPredateur();
	~QPredateur();

	QPredateur(qreal radius, QPointF const & position, QBrush const & brush, QPen const & pen);
	double distanceSeparee(QEntity const * bouffe);
	virtual void tic(QList<QEntity*>) = 0;
	virtual QEntity* typeDeVictime() = 0;
	void deplacement(QEntity*);
};

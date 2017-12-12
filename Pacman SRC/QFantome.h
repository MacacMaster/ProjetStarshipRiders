#pragma once
#include "QPredateur.h"
class QFantome :
	public QPredateur
{
public:
	QFantome();
	~QFantome();

	QFantome(qreal radius, QPointF const & position, QBrush const & brush, QPen const & pen);

	void tic(/*qreal elapsedTime*/);
	virtual QEntity* typeDeVictime() override;
	virtual void tic(QList<QEntity*>) override;
};


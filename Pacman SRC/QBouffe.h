#pragma once
#include "QStaticEntity.h"
class QBouffe :
	public QStaticEntity
{
public:
	QBouffe();
	~QBouffe();

	QBouffe(
		QSizeF const & size,
		QPointF  const & position,
		QBrush const & brush,
		QPen const & pen);

	void tic(/*qreal elapsedTime*/);
};


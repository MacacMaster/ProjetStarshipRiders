#pragma once
#include "QEntity.h"
#include <QRectF>

class QStaticEntity : public QEntity
{
public:
	QStaticEntity();
	QStaticEntity(
		QSizeF const & size,
		QPointF  const & position,
		QBrush const & brush,
		QPen const & pen);
	~QStaticEntity();

	virtual void paint(QPainter &painter) const override;  // surcharge;
	virtual void tic(/*qreal elapsedTime*/) override;

protected:
	QRectF mRect;

};


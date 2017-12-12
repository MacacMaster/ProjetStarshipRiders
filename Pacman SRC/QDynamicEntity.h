#pragma once
#include "QEntity.h"
class QDynamicEntity :
	public QEntity
{
public:
	QDynamicEntity();
	~QDynamicEntity();

	QDynamicEntity(
		qreal radius, // qreal 64 ou 32 bits, mais va aligner vers le bon!
		QPointF  const & position,
		QBrush const & brush,
		QPen const & pen);

	virtual void paint(QPainter &painter) const override;  // surcharge;

	virtual void tic(/*qreal elapsedTime*/) override;
protected:
	qreal mRadius;


};


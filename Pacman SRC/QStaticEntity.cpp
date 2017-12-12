#include "QStaticEntity.h"



QStaticEntity::QStaticEntity() 
	:QStaticEntity(
		QSizeF(50.0,50.0),
		QPointF(200.0, 200.0),
		Qt::white,
		QPen(Qt::black, 1.0))
{
}

QStaticEntity::QStaticEntity(
	QSizeF const & size,
	QPointF  const & position,
	QBrush const & brush,
	QPen const & pen)
	:
	// respecter l'ordre de résolution 
	QEntity(position, brush, pen),
	mRect(
		-size.width() / 2.0,
		-size.height() / 2.0,
		size.width(),
		size.height())
{
}


QStaticEntity::~QStaticEntity()
{
}

void QStaticEntity::paint(QPainter &painter) const 
{
	painter.setBrush(mBrush);
	painter.setPen(mPen);
	painter.drawRect(mRect);
}

void QStaticEntity::tic()
{
	mOrientation += 1.0;
}

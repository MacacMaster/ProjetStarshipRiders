#include "QDynamicEntity.h"



QDynamicEntity::QDynamicEntity()
: QEntity(), mRadius(0.0)
{
}

QDynamicEntity::QDynamicEntity(qreal radius, QPointF const & position, QBrush const & brush, QPen const & pen)
	:
	QEntity(position,brush,pen), mRadius(radius)
{



}


QDynamicEntity::~QDynamicEntity()
{
}

void QDynamicEntity::paint(QPainter &painter) const
{
	painter.setBrush(mBrush);
	painter.setPen(mPen);
	painter.drawEllipse(QPointF(0.0,0.0),mRadius,mRadius);
}

void QDynamicEntity::tic()
{
	mPosition += QPointF(1.0, 1.0); // un droite, un bas
}

#include "QBouffe.h"



QBouffe::QBouffe()
{
}


QBouffe::~QBouffe()
{
}

QBouffe::QBouffe(QSizeF const & size, QPointF const & position, QBrush const & brush, QPen const & pen)
	:
	QStaticEntity(size,position,brush,pen)
{

}

void QBouffe::tic()
{
	mOrientation += 50.0;
}

#include "QEntity.h"

QEntity::QEntity(
	QPointF  const & position,
	QBrush const & brush,
	QPen const & pen)
	: mPosition(position),
	mBrush(brush)
	{}
	//mPatente {5} // plus représentatif que mPatente(5) du code en arriere
	// dire quel constructeur utiliser
	//{
	//	// initialisation ... perte de temps! 
	////this->mPosition = position;
	////this->mBrush = brush;
	////this->mPen = pen;
	//}

	QEntity::QEntity()
	/*:mPosition(QPointF(0.0, 0.0)),
	mBrush(Qt::magenta),
		mPen(Qt::NoPen)*/
	// ce n'est pas DNRY!
	:QEntity(
		QPointF(0.0, 0.0),
		Qt::white, 
		QPen(Qt::black,1.0))
	// excellente facon de programmer
	// feature du cpp 11 constructeur délégué
{

}

QEntity::~QEntity()
{
}

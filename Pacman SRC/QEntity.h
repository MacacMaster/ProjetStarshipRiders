#pragma once
#include <QPointF>
#include <QBrush>
#include <QPen>
#include <QPainter>

class QEntity
{
public:
	QEntity();
	QEntity(
		QPointF  const & position,
		QBrush const & brush,
		QPen const & pen);
	~QEntity();

	virtual void paint(QPainter &painter/*ne pas passer le painter en const, pcq il va être modifié*/) const /*mais le painter ne modifie pas l'objet entité*/= 0;
	virtual void tic(/*qreal elapsedTime*/) = 0; // pour générer des événements dans le temps
	QPointF position() const { return mPosition; }
	qreal orientation() const { return mOrientation; }

protected:
	qreal mOrientation{0.0};
	QPointF mPosition;
	QBrush mBrush;
	QPen mPen;
	

};


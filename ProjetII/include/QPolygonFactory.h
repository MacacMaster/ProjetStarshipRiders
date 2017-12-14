#ifndef Q_POLYGON_FACTORY_H
#define Q_POLYGON_FACTORY_H


#include <QPolygonF>


class QPolygonFactory
{
public:
	QPolygonFactory() = delete;
	~QPolygonFactory() = delete;
	QPolygonFactory(QPolygonFactory const & f) = delete;
	QPolygonFactory& operator=(QPolygonFactory const & f) = delete;
	QPolygonFactory(QPolygonFactory const && f) = delete;
	QPolygonFactory& operator=(QPolygonFactory const && f) = delete;

	static QPolygonF isoscelesTriangle(qreal base, qreal height, bool tipInsteadOfBase = true);
	static QPolygonF equilateralPolygon(size_t n, qreal sideLength, qreal thetaDegrees);
};


#endif // Q_POLYGON_FACTORY_H

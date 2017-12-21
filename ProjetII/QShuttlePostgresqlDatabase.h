#ifndef Q_SHUTTLE_POSTGRESQL_DATABASE_H
#define Q_SHUTTLE_POSTGRESQL_DATABASE_H


/*
ADD PATH
C:\Program Files\PostgreSQL\9.6\lib
C:\Program Files\PostgreSQL\9.6\bin

*/

#include "QShuttleDatabase.h"
#include <QSqlQueryInsertion.h>
class QPolygonalBody;


class QShuttlePostgresqlDatabase : public QShuttleDatabase
{
public:
	QShuttlePostgresqlDatabase();
	~QShuttlePostgresqlDatabase();

	virtual bool connect(QString const & hostName, size_t port, QString const & userName, QString const & password, QString const & databaseName) override;

	virtual QStringList availableShuttles() const override;
	virtual bool isShuttleExists(QString const & name) override;

	virtual bool retrieveShuttle(QShuttle * shuttle, QString const & name, QSceneModel & sceneModel) override;
	virtual bool insertShuttle(QShuttle * shuttle) override;
	virtual bool updateShuttle(QShuttle * shuttle, QString const & name) override;
	virtual bool deleteShuttle(QString const & name) override;

protected:
	bool insertShape(QPolygonalBody * shape, int & newShapeId);
	
private:	

	QSqlQueryInsertion mInsertShuttleQuery;
	QSqlQueryInsertion mInsertShapeQuery;
	QSqlQueryInsertion mInsertFuelTankQuery;
	QSqlQueryInsertion mInsertThrusterQuery;
	void initializePreparedQueries();

};


#endif // Q_SHUTTLE_POSTGRESQL_DATABASE_H

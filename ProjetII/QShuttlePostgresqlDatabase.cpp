#include "QShuttlePostgresqlDatabase.h"


#include <QSqlQuery>
#include <QDebug>

#include <QUtilities.h>

#include <QShuttle.h>
#include <QPolygonalBody.h>
#include <QShuttleFuelTank.h>
#include <QShuttleThruster.h>
#include <QThrusterKeyboardController.h>


QShuttlePostgresqlDatabase::QShuttlePostgresqlDatabase()
{

}

QShuttlePostgresqlDatabase::~QShuttlePostgresqlDatabase()
{
}

bool QShuttlePostgresqlDatabase::connect(QString const & hostName, size_t port, QString const & userName, QString const & password, QString const & databaseName)
{
	mDatabase = QSqlDatabase::addDatabase("QPSQL");
	mDatabase.setHostName(hostName);
	mDatabase.setPort(port);
	mDatabase.setUserName(userName);
	mDatabase.setPassword(password);
	mDatabase.setDatabaseName(databaseName);

	bool dbOpen{ mDatabase.open() };

	if (!dbOpen) {
		qDebug() << "Database connection error : " << mDatabase.lastError().text();
	}
	qDebug() << "Database connection successful!";

	initializePreparedQueries();

	return dbOpen;
}

QStringList QShuttlePostgresqlDatabase::availableShuttles() const
{
	QStringList shuttles;
	QSqlQuery query;
	bool success{ query.exec("SELECT name FROM shuttle;") };

	if (!success) {
		dbOutputDebugError(query);
	} else {
		while (query.next()) {
			shuttles << query.value(0).toString();
		}
	}

	return shuttles;
}

bool QShuttlePostgresqlDatabase::isShuttleExists(QString const & name)
{
	QSqlQuery query;
	query.prepare("SELECT count(*) FROM shuttle WHERE name = ?;");
	query.bindValue(0, name);

	bool success{ query.exec() };
	if (!query.exec()) {
		return false;
	}

	query.next();
	return query.value(0).toInt() == 1;
}

bool QShuttlePostgresqlDatabase::retrieveShuttle(QShuttle * shuttle, QString const & name, QSceneModel const & sceneModel)
{
	// to do PRIORITY
	return false;
}

bool QShuttlePostgresqlDatabase::insertShuttle(QShuttle * shuttle)
{
	mDatabase.transaction();

	// Inserting shuttle's shape
	int insertedShapeId;
	if (!insertShape(static_cast<QPolygonalBody*>(shuttle->shape()), insertedShapeId)) {
		mDatabase.rollback();
		return false;
	}

	// Inserting shuttle's info
	int insertedShuttleId;
	mInsertShuttleQuery.bind(	shuttle->name(),
								insertedShapeId,
								shuttle->surfaceMass(),
								QUtilities::pointToString(shuttle->linearPosition()),
								QUtilities::pointToString(shuttle->linearSpeed()),
								shuttle->angularPosition(),
								shuttle->angularSpeed());
	if (!mInsertShuttleQuery.execute(insertedShuttleId)) {
		mDatabase.rollback();
		return false;
	}

	// Inserting fuel tank's info
	int insertedFuelTankId;
	QShuttleFuelTank * fuelTank{ shuttle->fuelTanks()[0] };
	mInsertFuelTankQuery.bind(	insertedShuttleId,
								fuelTank->capacity(),
								fuelTank->fuelLevelRatio(),
								fuelTank->tankSize().width(),
								fuelTank->tankSize().height(),
								QUtilities::pointToString(fuelTank->linearPosition()),
								fuelTank->angularPosition(),
								QUtilities::colorToInt(fuelTank->fuelColor()));
	if (!mInsertFuelTankQuery.execute(insertedFuelTankId)) {
		mDatabase.rollback();
		return false;
	}

	// Inserting all thrusters
	for (auto const & thruster : shuttle->thrusters()) {
		// Inserting thruster's shape
		if (!insertShape(static_cast<QPolygonalBody*>(thruster->shape()), insertedShapeId)) {
			mDatabase.rollback();
			return false;
		}

		// Inserting thruster's info
		int insertedThrusterId;
		mInsertThrusterQuery.bind(	insertedShuttleId,
									insertedShapeId,
									insertedFuelTankId,
									thruster->massFlowRate(),
									thruster->massEjectedSpeed(),
									QUtilities::pointToString(thruster->linearPosition()),
									thruster->angularPosition(),
									QUtilities::keySequenceToString(static_cast<QThrusterKeyboardController*>(thruster->controller())->linkedKey()));
		if (!mInsertThrusterQuery.execute(insertedThrusterId)) {
			mDatabase.rollback();
			return false;
		}
	}

	mDatabase.commit();
	return false;
}

bool QShuttlePostgresqlDatabase::updateShuttle(QShuttle * shuttle, QString const & name)
{
	// to do
	return false;
}

bool QShuttlePostgresqlDatabase::deleteShuttle(QString const & name)
{
	// to do
	return false;
}

void QShuttlePostgresqlDatabase::initializePreparedQueries()
{
	mInsertShuttleQuery.prepare(mDatabase, "Shuttle", "Name", "Shape", "Surfacemass", "Linearposition", "Linearspeed", "Angularposition", "Angularspeed");
	mInsertShapeQuery.prepare(mDatabase, "Shape", "BrushColor", "PenColor", "PenWidth", "PolygonalShape");
	mInsertFuelTankQuery.prepare(mDatabase, "FuelTank", "Shuttle", "Capacity", "FuelLevel", "TankWidth", "TankHeight", "LinearPosition", "AngularPosition", "FuelColor");
	mInsertThrusterQuery.prepare(mDatabase, "Thruster", "Shuttle", "Shape", "FuelTank", "MassFlowRate", "MassEjectedSpeed", "LinearPosition", "AngularPosition", "KeySequence");
}

bool QShuttlePostgresqlDatabase::insertShape(QPolygonalBody * shape, int & newShapeId)
{
	mInsertShapeQuery.bind(	QUtilities::colorToInt(shape->brush().color()),
							QUtilities::colorToInt(shape->pen().color()),
							shape->pen().width(),
							QUtilities::polygonToString(shape->polygon()));
	return mInsertShapeQuery.execute(newShapeId);
}

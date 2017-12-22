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
	else {
		qDebug() << "Database connection successful!";
	}

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

bool QShuttlePostgresqlDatabase::retrieveShuttle(QShuttle * shuttle, QString const & name, QSceneModel & sceneModel)
{
	mDatabase.transaction();
	// to do PRIORITY
	if (!isShuttleExists(name)) {//Verifies if shuttle exists
		mDatabase.rollback();
		return false;
	}
	//QUERY
	QSqlQuery mSelectShuttleQuery(mDatabase);
	QSqlQuery mSelectFuelTankQuery(mDatabase);
	QSqlQuery mSelectThrusterQuery(mDatabase);
	mSelectShuttleQuery.prepare("SELECT shuttle.id,surfacemass, linearposition, linearspeed, angularposition, angularspeed, brushcolor, pencolor, penwidth, polygonalshape FROM shuttle LEFT OUTER JOIN shape ON(shuttle.shape = shape.id) WHERE name LIKE ?");
	mSelectFuelTankQuery.prepare("SELECT capacity,fuellevel,tankwidth,tankheight,linearposition,angularposition,fuelcolor FROM fueltank WHERE shuttle = ?");
	mSelectThrusterQuery.prepare("SELECT massflowrate, massejectedspeed, linearposition, angularposition, brushcolor, pencolor, penwidth, polygonalshape,keysequence FROM thruster LEFT OUTER JOIN shape ON(thruster.shape = shape.id) WHERE shuttle = ?");


	mSelectShuttleQuery.bindValue(0, name);
	if (!mSelectShuttleQuery.exec()) {
		return false;
		mDatabase.rollback();
		qDebug() << "Shuttle Query failed";
	}
	//set Shuttleshape query with this
	mSelectShuttleQuery.next();
	int shuttleId = mSelectShuttleQuery.value(0).toInt();//shuttleid


	qDebug() <<name;
	qDebug() <<mSelectShuttleQuery.value(0).toString();
	qDebug() <<mSelectShuttleQuery.value(1).toString();
	qDebug() <<mSelectShuttleQuery.value(2).toString();
	qDebug() <<mSelectShuttleQuery.value(3).toString();
	qDebug() <<mSelectShuttleQuery.value(4).toString();
	qDebug() <<mSelectShuttleQuery.value(5).toString();
	qDebug() <<mSelectShuttleQuery.value(6).toString();
	qDebug() <<mSelectShuttleQuery.value(7).toString();
	qDebug() <<mSelectShuttleQuery.value(8).toString();
	qDebug() <<mSelectShuttleQuery.value(9).toString();

	shuttle->setName(name);
	shuttle->setSurfaceMass(mSelectShuttleQuery.value(1).toReal());//surfacemass
	shuttle->setLinearPosition(QUtilities::pointFromString(mSelectShuttleQuery.value(2).toString()));//linearposition
	shuttle->setLinearSpeed(QUtilities::pointFromString(mSelectShuttleQuery.value(3).toString()));//linearspeed
	shuttle->setAngularPosition(mSelectShuttleQuery.value(4).toReal());//angularposition
	shuttle->setAngularSpeed(mSelectShuttleQuery.value(5).toReal());//angularspeed
	shuttle->shape()->setBrush(QUtilities::colorFromInt(mSelectShuttleQuery.value(6).toInt()));//brushcolor
	shuttle->shape()->setPen(QPen(QUtilities::colorFromInt(mSelectShuttleQuery.value(7).toInt()), mSelectShuttleQuery.value(8).toReal()));//pencolor,penwidth
	static_cast<QPolygonalBody*>(shuttle->shape())->setPolygon(QUtilities::polygonFromString(mSelectShuttleQuery.value(9).toString()));//polygonalshape

	//traitement des data
	mSelectFuelTankQuery.bindValue(0, shuttleId);
	if (!mSelectFuelTankQuery.exec()) {
		mDatabase.rollback();
		return false;
	}
	//remove all FTs
	for (QShuttleFuelTank *f : shuttle->fuelTanks()) {
		shuttle->removeFuelTank(f);
	}
	//add new FTs
	for (int i = 0; i < mSelectFuelTankQuery.size(); i++) {
		mSelectFuelTankQuery.next();
		
		qDebug() << (mSelectFuelTankQuery.value(0).toReal());//capacity
		qDebug() << mSelectFuelTankQuery.value(1).toReal();//fuellevel
		qDebug() << mSelectFuelTankQuery.value(2).toReal();//tankwidth
		qDebug() << mSelectFuelTankQuery.value(3).toReal();//tankheight
		qDebug() << QUtilities::pointFromString(mSelectFuelTankQuery.value(4).toString());//linearposition
		qDebug() << mSelectFuelTankQuery.value(5).toReal();//angularposition
		qDebug() << (QUtilities::colorFromInt(mSelectFuelTankQuery.value(6).toInt()));//fuelcolor
		
		QShuttleFuelTank * temp = new QShuttleFuelTank(
			mSelectFuelTankQuery.value(2).toReal(),
			mSelectFuelTankQuery.value(3).toReal(),
			QUtilities::colorFromInt(mSelectFuelTankQuery.value(6).toInt()));
		temp->setCapacity(mSelectFuelTankQuery.value(0).toReal());
		temp->fill(mSelectFuelTankQuery.value(1).toReal());
		shuttle->addFuelTank(
			temp,
			QUtilities::pointFromString(mSelectFuelTankQuery.value(4).toString()), 
			mSelectFuelTankQuery.value(5).toReal()
		);		
	}

	//Thrusters
	mSelectThrusterQuery.bindValue(0, shuttleId);
	if (!mSelectThrusterQuery.exec()) {
		mDatabase.rollback();
		return false;
	}
	//remove all Ts
	for (QShuttleThruster *t : shuttle->thrusters()) {
		shuttle->removeThruster(t);
	}
	QShuttleFuelTank * fuelTank = shuttle->fuelTanks()[0];

	for (int i = 0; i < mSelectThrusterQuery.size(); i++) {
		//if multiple fuel tanks, 1 per thruster
		if (shuttle->fuelTanks().size() >= mSelectThrusterQuery.size()) {
			fuelTank = shuttle->fuelTanks()[i];
		}
		mSelectThrusterQuery.next();
		/*
		mSelectThrusterQuery.value(0).toReal();//massflowrate
		mSelectThrusterQuery.value(1).toReal();//massejectedspeed
		QUtilities::pointFromString(mSelectThrusterQuery.value(2).toString());//linearposition
		mSelectThrusterQuery.value(3).toReal();//angularposition
		QUtilities::colorFromInt(mSelectThrusterQuery.value(4).toInt());//brushcolor
		QUtilities::colorFromInt(mSelectThrusterQuery.value(5).toInt());//pencolor
		mSelectThrusterQuery.value(6).toReal();//penwidth
		QUtilities::polygonFromString(mSelectThrusterQuery.value(7).toString());//polygonalshape
		QUtilities::keySequenceFromString(mSelectThrusterQuery.value(8).toString());//keysequence
		*/

		
		QShuttleThruster * thruster = new QShuttleThruster(new QPolygonalBody);
		// Step 2 - Assign the polygonal shape - in this case, we use an equilateral polygon
		static_cast<QPolygonalBody*>(thruster->shape())->setPolygon(QUtilities::polygonFromString(mSelectThrusterQuery.value(7).toString()));
		// Step 3 - Assign brush and pen to the shape
		thruster->shape()->setBrush(QUtilities::colorFromInt(mSelectThrusterQuery.value(4).toInt()));
		thruster->shape()->setPen(QPen(QUtilities::colorFromInt(mSelectThrusterQuery.value(5).toInt()), mSelectThrusterQuery.value(6).toReal()));
		// Step 4 - Assign model to the thruster
		thruster->setSceneModel(&sceneModel);
		// Step 5 - Assign the fuel tank
		thruster->linkToFuelTank(fuelTank);
		// Step 6 - Set flow rate and eject speed
		thruster->setThrusterEfficiency(mSelectThrusterQuery.value(0).toReal(), mSelectThrusterQuery.value(1).toReal());
		// Step 7 - Create and assign the keyboard controller
		thruster->setController(new QThrusterKeyboardController(QUtilities::keySequenceFromString(mSelectThrusterQuery.value(8).toString())));
		// Step 8 - Assign the thruster to the shuttle
		shuttle->addThruster(
			thruster, 
			QUtilities::pointFromString(mSelectThrusterQuery.value(2).toString()), 
			mSelectThrusterQuery.value(3).toReal()
		);//Trigo<>::deg2rad(orientationDegrees));




	}
	mDatabase.commit();
	return true;
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
	return true;
}

bool QShuttlePostgresqlDatabase::updateShuttle(QShuttle * shuttle, QString const & name)
{
	
	return true;
}

bool QShuttlePostgresqlDatabase::deleteShuttle(QString const & name)
{
	mDatabase.transaction();

	//QList<QVariant> shapeIds;
	QString shapeIds;
	mAllShapesFromShuttle.bindValue(0, name);
	mAllShapesFromShuttle.bindValue(1, name);
	if (!QUtilities::sqlGetIds(mAllShapesFromShuttle, shapeIds)) {
		return false;
	}

	// Delete all thrusters
	mDeleteThrusterFromShuttle.bindValue(0, name);
	if (!mDeleteThrusterFromShuttle.exec()) {
		qDebug() << "QSqlQuery error : " << mDeleteThrusterFromShuttle.lastError().text();
		mDatabase.rollback();
		return false;
	}

	// Delete the fuel tank
	mDeleteFuelTankFromShuttle.bindValue(0, name);
	if (!mDeleteFuelTankFromShuttle.exec()) {
		qDebug() << "QSqlQuery error : " << mDeleteFuelTankFromShuttle.lastError().text();
		mDatabase.rollback();
		return false;
	}

	// Delete the shuttle
	QSqlQuery query4;
	mDeleteShuttle.bindValue(0, name);
	if (!mDeleteShuttle.exec()) {
		qDebug() << "QSqlQuery error : " << mDeleteShuttle.lastError().text();
		mDatabase.rollback();
		return false;
	}

	// Delete all the shapes (including shuttle + thrusters)
	// ... first approach
	//for (auto id : shapeIds) {
	//	mDeleteShapeFromId.bindValue(0, id);
	//	if (!mDeleteShapeFromId.exec()) {
	//		qDebug() << "QSqlQuery error : " << mDeleteShapeFromId.lastError().text();
	//		mDatabase.rollback();
	//		return false;
	//	}
	//}
	// ... second approach
	QString sqlDeleteShapeFromId(QString("DELETE FROM shape WHERE id IN (%1);").arg(shapeIds));
	QSqlQuery queryDeleteShapeFromId;
	if (!queryDeleteShapeFromId.exec(sqlDeleteShapeFromId)) {
		qDebug() << "QSqlQuery error : " << mDeleteShapeFromId.lastError().text();
		mDatabase.rollback();
		return false;
	}

	mDatabase.commit();
	return true;
}

void QShuttlePostgresqlDatabase::initializePreparedQueries()
{
	mInsertShuttleQuery.prepare(mDatabase, "Shuttle", "Name", "Shape", "Surfacemass", "Linearposition", "Linearspeed", "Angularposition", "Angularspeed");
	mInsertShapeQuery.prepare(mDatabase, "Shape", "BrushColor", "PenColor", "PenWidth", "PolygonalShape");
	mInsertFuelTankQuery.prepare(mDatabase, "FuelTank", "Shuttle", "Capacity", "FuelLevel", "TankWidth", "TankHeight", "LinearPosition", "AngularPosition", "FuelColor");
	mInsertThrusterQuery.prepare(mDatabase, "Thruster", "Shuttle", "Shape", "FuelTank", "MassFlowRate", "MassEjectedSpeed", "LinearPosition", "AngularPosition", "KeySequence");

	mAllShapesFromShuttle = QSqlQuery(mDatabase);
	mAllShapesFromShuttle.prepare(R".(
SELECT shape 
	FROM shuttle 
	WHERE name = ?
UNION
SELECT thruster.shape 
	FROM thruster 
		INNER JOIN shuttle 
			ON thruster.shuttle = shuttle.id 
	WHERE shuttle.name = ? 
).");
	mDeleteThrusterFromShuttle = QSqlQuery(mDatabase);
	mDeleteThrusterFromShuttle.prepare(R".(
DELETE FROM thruster 
	WHERE id IN (	SELECT thruster.id 
						FROM thruster 
							INNER JOIN shuttle 
								ON thruster.shuttle = shuttle.id 
						WHERE shuttle.name = ?);
).");
	mDeleteFuelTankFromShuttle = QSqlQuery(mDatabase);
	mDeleteFuelTankFromShuttle.prepare(R".(
DELETE FROM fueltank 
	WHERE id IN (	SELECT fueltank.id 
						FROM fueltank 
							INNER JOIN shuttle 
								ON fueltank.shuttle = shuttle.id 
						WHERE shuttle.name = ?);
).");
	mDeleteShuttle = QSqlQuery(mDatabase);
	mDeleteShuttle.prepare(R".(
DELETE FROM shuttle 
	WHERE name = ?;
).");
	mDeleteShapeFromId = QSqlQuery(mDatabase);
	mDeleteShapeFromId.prepare(R".(
DELETE FROM shape 
	WHERE id = ?;
).");
}

bool QShuttlePostgresqlDatabase::insertShape(QPolygonalBody * shape, int & newShapeId)
{
	mInsertShapeQuery.bind(	QUtilities::colorToInt(shape->brush().color()),
							QUtilities::colorToInt(shape->pen().color()),
							shape->pen().width(),
							QUtilities::polygonToString(shape->polygon()));
	return mInsertShapeQuery.execute(newShapeId);
}

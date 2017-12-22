/********************************************************************************
* M-A Ramsay
* Starship.sql
* BD Creation Script
********************************************************************************/

DROP TABLE IF EXISTS Shuttle,FuelTank,Thruster,Shape CASCADE;

CREATE TABLE IF NOT EXISTS Shuttle (
Id					SERIAL		CONSTRAINT SHUTTLE_PK PRIMARY KEY,
Name				VARCHAR(32) UNIQUE NOT NULL,
Shape				INT			NOT NULL,
Surfacemass			REAL		NOT NULL,
Linearposition		POINT		NOT NULL,
Linearspeed			POINT		NOT NULL,
Angularposition		REAL		NOT NULL,
Angularspeed		REAL		NOT NULL
);

CREATE TABLE IF NOT EXISTS FuelTank (
Id					SERIAL		CONSTRAINT FUELTANK_PK PRIMARY KEY,				
Shuttle				INT			NOT NULL,
Capacity			REAL		NOT NULL,
FuelLevel			REAL		NOT NULL CONSTRAINT FUELLEVEL_CHECK CHECK (FuelLevel >0),
TankWidth			REAL		NOT NULL,
TankHeight			REAL		NOT NULL,
LinearPosition		POINT		NOT NULL,
AngularPosition		REAL		NOT NULL,	
FuelColor			INT			NOT NULL
);

CREATE TABLE IF NOT EXISTS Shape (

Id					SERIAL		CONSTRAINT SHAPE_PK PRIMARY KEY,
BrushColor			INT			NOT NULL,
PenColor			INT			NOT NULL,
PenWidth			REAL		NOT NULL,
PolygonalShape		POLYGON		NOT NULL
);                          
                            
CREATE TABLE IF NOT EXISTS Thruster (
Id					SERIAL		CONSTRAINT THRUSTER_PK PRIMARY KEY,
Shuttle				INT			NOT NULL,
Shape				INT			NOT NULL,
FuelTank			INT			NOT NULL,
MassFlowRate		REAL		NOT NULL,
MassEjectedSpeed	REAL		NOT NULL,
LinearPosition		POINT		NOT NULL,
AngularPosition		REAL		NOT NULL,
KeySequence			VARCHAR(8)	NOT NULL
);

/*Assigning FKs*/
ALTER TABLE Shuttle 	ADD CONSTRAINT SHUTTLE_SHAPE_FK 	FOREIGN KEY (Shape) 	REFERENCES Shape;
ALTER TABLE FuelTank 	ADD CONSTRAINT FUELTANK_SHUTTLE_FK 	FOREIGN KEY (Shuttle) 	REFERENCES Shuttle;
ALTER TABLE Thruster 	ADD CONSTRAINT THRUSTER_SHUTTLE_FK 	FOREIGN KEY (Shuttle) 	REFERENCES Shuttle;
ALTER TABLE Thruster 	ADD CONSTRAINT THRUSTER_SHAPE_FK 	FOREIGN KEY (Shape) 	REFERENCES Shape;
ALTER TABLE Thruster 	ADD CONSTRAINT THRUSTER_FUELTANK_FK FOREIGN KEY (FuelTank)	REFERENCES FuelTank;

/*
	Prepared statements for PostgreSQL
	
	mSelectShuttleQuery
		("SELECT shuttle.id,surfacemass, linearposition, linearspeed, angularposition, angularspeed, brushcolor, pencolor, penwidth, polygonalshape 
		FROM shuttle LEFT OUTER JOIN shape ON(shuttle.shape = shape.id) 
		WHERE name LIKE ?");
		
	mSelectFuelTankQuery
		("SELECT capacity,fuellevel,tankwidth,tankheight,linearposition,angularposition,fuelcolor 
		FROM fueltank 
		WHERE shuttle = ?");
		
	mSelectThrusterQuery
		("SELECT massflowrate, massejectedspeed, linearposition, angularposition, brushcolor, pencolor, penwidth, polygonalshape,keysequence 
		FROM thruster 
		LEFT OUTER JOIN shape ON(thruster.shape = shape.id) 
		WHERE shuttle = ?");
		
	
	mUpdateShuttleQuery.prepare(
		"UPDATE shuttle 
		SET shuttle.id = ?,surfacemass = '?',  linearposition = '?',  linearspeed = '?',  angularposition = '?',  angularspeed = '?',  brushcolor = '?',  pencolor = '?',  penwidth = '?',  polygonalshape = '?'
		LEFT OUTER JOIN shape ON(shuttle.shape = shape.id) 
		WHERE name LIKE ?");
	
	mUpdateFuelTankQuery.prepare(	
		"UPDATE fueltank
		SET capacity = '?', fuellevel = '?', tankwidth = '?', tankheight = '?', linearposition = '?', angularposition = '?', fuelcolor = '?'
		WHERE shuttle = ?");
	
	mUpdateThrusterQuery.prepare(	
		"UPDATE  thruster
		SET massflowrate = '?',  massejectedspeed = '?',  linearposition = '?',  angularposition = '?',  brushcolor = '?',  pencolor = '?',  penwidth = '?',  polygonalshape = '?', keysequence = '?'
		LEFT OUTER JOIN shape ON(thruster.shape = shape.id) 
		WHERE shuttle = ?");

	*/

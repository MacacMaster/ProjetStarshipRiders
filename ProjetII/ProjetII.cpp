#include "ProjetII.h"

ProjetII::ProjetII(QWidget *parent)
	: QMainWindow(parent),
	mSceneSize(500.0, 500.0),
	mSceneModel(mSceneSize),
	mShuttleEditor(new QPolygonEditor())
{
	ui.setupUi(this);

	//Scene
	mSceneControl = new QSceneViewController();
	mSceneControl->setSceneModel(&mSceneModel);

	//Predefini Horizon 6t k
	generate_Horizon_6t_k();

	//ColorBox
	colorBox = new QColorBox;


	setCentralWidget(mSceneControl);


	mTimer.start(30);
	connect(colorBox, &QColorBox::colorChanged, this, &ProjetII::updateShuttleFromGUI); 
	connect(&mTimer, &QTimer::timeout, this, &ProjetII::tic);

	colorBox->setColor(mShuttle->shape()->brush().color());	//sychronize colorBox color with shuttle color
	
	
	//Initialize editor this way

}


void ProjetII::generate_Horizon_6t_k()
{
	qreal size{ mShuttleEditor->outputScale() };

	// Step 1 - Build shuttle with a polygonal shape (instead of the default circular shape)
	mShuttle = new QShuttle(new QPolygonalBody);

	// Step 1.1 - Assign shuttle to the scene model
	mSceneModel.setOneShuttle(mShuttle);

	// Step 1.2 - Create the polygon for the body
	// Step 1.2.1 - Create unit polygon
	QPolygonF shutteShape;
	shutteShape << QPointF(1.000000, 0.000000)
		<< QPointF(1.000000, -0.069444)
		<< QPointF(0.930556, -0.069444)
		<< QPointF(0.868056, -0.111111)
		<< QPointF(0.791667, -0.208333)
		<< QPointF(0.791667, -0.277778)
		<< QPointF(0.743056, -0.298611)
		<< QPointF(0.694444, -0.277778)
		<< QPointF(0.694444, -0.208333)
		<< QPointF(0.597222, -0.138889)
		<< QPointF(0.395833, -0.180556)
		<< QPointF(0.354167, -0.298611)
		<< QPointF(0.354167, -0.388889)
		<< QPointF(0.270833, -0.409722)
		<< QPointF(0.180556, -0.388889)
		<< QPointF(0.180556, -0.305556)
		<< QPointF(0.138889, -0.180556)
		<< QPointF(0.069444, -0.138889)
		<< QPointF(0.000000, -0.138889)
		<< QPointF(0.000000, 0.000000)
		<< QPointF(0.000000, 0.138889)
		<< QPointF(0.069444, 0.138889)
		<< QPointF(0.138889, 0.180556)
		<< QPointF(0.180556, 0.305556)
		<< QPointF(0.180556, 0.388889)
		<< QPointF(0.270833, 0.409722)
		<< QPointF(0.354167, 0.388889)
		<< QPointF(0.354167, 0.298611)
		<< QPointF(0.395833, 0.180556)
		<< QPointF(0.597222, 0.138889)
		<< QPointF(0.694444, 0.208333)
		<< QPointF(0.694444, 0.277778)
		<< QPointF(0.743056, 0.298611)
		<< QPointF(0.791667, 0.277778)
		<< QPointF(0.791667, 0.208333)
		<< QPointF(0.868056, 0.111111)
		<< QPointF(0.930556, 0.069444)
		<< QPointF(1.000000, 0.069444)
		<< QPointF(1.000000, 0.000000);
	shutteShape.translate(-0.5, 0.0);
	size *= 2.0;
	// Step 1.2.2 - Scaling the polygon
	for (auto & point : shutteShape) {
		point *= size;
	}
	// Step 1.2.3 - Assigning the polygon
	static_cast<QPolygonalBody*>(mShuttle->shape())->setPolygon(shutteShape);

	// Step 1.3 - Defining the shape name and color
	mShuttle->setName("Horizon 6t K-Shuttle");
	mShuttle->shape()->setBrush(QColor(95, 125, 185));
	mShuttle->shape()->setPen(QPen(QColor(50, 70, 115), 1.0));

	// Step 1.4 - Adding the shuttle controller
	mShuttleController = new QShuttleKeyboardController;
	mShuttle->setController(mShuttleController);

	// Step 1.5 - Centering and orienting the shuttle
	mShuttle->setLinearPosition(QPointF(mSceneSize.width() / 2.0, mSceneSize.height() / 2.0));
	mShuttle->setAngularPosition(0.0);

	// Step 2 - Creating the fuel tank with width and height
	mShuttleFuelTank = new QShuttleFuelTank(size / 12.5, size / 2.0);

	// Step 2.1 - Assigning the brush and pen of the tank
	mShuttleFuelTank->shape()->setBrush(QColor(128, 128, 128));
	mShuttleFuelTank->shape()->setPen(QPen(Qt::black, 1.0));

	// Step 2.2 - Assigning the fuel color
	mShuttleFuelTank->setFuelColor(QColor(196, 255, 0));

	// Step 2.3 - Set capacity and fill it
	mShuttleFuelTank->setCapacity(500000.0);
	mShuttleFuelTank->fill();

	// Step 2.4 - Add the tank to the shuttle
	mShuttle->addFuelTank(mShuttleFuelTank, QPointF(size / 3.0 - 0.5 * size, 0.0), Trigo<>::deg2rad(90.0));

	// Step 3 - Create and add all thrusters
	QBrush thrusterBrush(QColor(128, 128, 128));
	QPen thrusterPen(QPen(Qt::white, 0.5));
	qreal flowRate{ 100.0 };
	qreal ejectSpeed{ 100.0 };
	addNewThruster(&mSceneModel, mShuttleFuelTank, size / 2.5, flowRate, ejectSpeed, static_cast<QPolygonalBody*>(mShuttle->shape())->polygon()[19], 0.0, thrusterBrush, thrusterPen, QKeySequence("5"));
	addNewThruster(&mSceneModel, mShuttleFuelTank, size / 5.5, flowRate, ejectSpeed, static_cast<QPolygonalBody*>(mShuttle->shape())->polygon()[25], -90.0, thrusterBrush, thrusterPen, QKeySequence("4"));
	addNewThruster(&mSceneModel, mShuttleFuelTank, size / 5.5, flowRate, ejectSpeed, static_cast<QPolygonalBody*>(mShuttle->shape())->polygon()[13], 90.0, thrusterBrush, thrusterPen, QKeySequence("6"));
	addNewThruster(&mSceneModel, mShuttleFuelTank, size / 5.5, flowRate, ejectSpeed, static_cast<QPolygonalBody*>(mShuttle->shape())->polygon()[0], 180.0, thrusterBrush, thrusterPen, QKeySequence("8"));
	addNewThruster(&mSceneModel, mShuttleFuelTank, size / 7.5, flowRate, ejectSpeed, static_cast<QPolygonalBody*>(mShuttle->shape())->polygon()[32], -90.0, thrusterBrush, thrusterPen, QKeySequence("7"));
	addNewThruster(&mSceneModel, mShuttleFuelTank, size / 7.5, flowRate, ejectSpeed, static_cast<QPolygonalBody*>(mShuttle->shape())->polygon()[6], 90.0, thrusterBrush, thrusterPen, QKeySequence("9"));

	// to do - Update all custom widget and interface...
	// ...
	// ...
	// ...  
	mSceneControl->update();
}

void ProjetII::addNewThruster(QSceneModel * model,
	QShuttleFuelTank * fuelTank,
	qreal thrusterSize,
	qreal massFlowRate,
	qreal massEjectSpeed,
	QPointF const & position,
	qreal orientationDegrees,
	QBrush const & brush,
	QPen const & pen,
	QKeySequence const & key)
{
	// Step 1 - Build thruster with a polygonal shape (instead of the default circular shape) 
	QShuttleThruster * thruster = new QShuttleThruster(new QPolygonalBody);
	// Step 2 - Assign the polygonal shape - in this case, we use an equilateral polygon
	static_cast<QPolygonalBody*>(thruster->shape())->setPolygon(QPolygonFactory::equilateralPolygon(3, thrusterSize, 0.0));
	// Step 3 - Assign brush and pen to the shape
	thruster->shape()->setBrush(brush);
	thruster->shape()->setPen(pen);
	// Step 4 - Assign model to the thruster
	thruster->setSceneModel(model);
	// Step 5 - Assign the fuel tank
	thruster->linkToFuelTank(fuelTank);
	// Step 6 - Set flow rate and eject speed
	thruster->setThrusterEfficiency(massFlowRate, massEjectSpeed);
	// Step 7 - Create and assign the keyboard controller
	thruster->setController(new QThrusterKeyboardController(key));
	// Step 8 - Assign the thruster to the shuttle
	mShuttle->addThruster(thruster, position, Trigo<>::deg2rad(orientationDegrees));
}


void ProjetII::tic() {

	mSceneModel.tic(0.03);
	mSceneControl->update();
}

void ProjetII::updateShuttleFromGUI(){

	//...

	mShuttle->shape()->setBrush(colorBox->color());

}
#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setSamples(16);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);
	this->setFormat(format);

	this->setFocus();

	mazeGrid = make_shared<Algorithms>();
	mazeGrid->helper(10, 10);

	updateTimer.setInterval(0);
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(update()));
	updateTimer.start();
	
}


MazeGLWidget::~MazeGLWidget() {

	makeCurrent();
	for (int i = 0; i < gameObjects->size(); i++) {
		delete gameObjects->at(i);
	}
	delete gameObjects;
	delete camera;
	
}

void MazeGLWidget::initializeGL() {

	initializeOpenGLFunctions();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	camera = new Camera(
		QVector3D(0.0f, 0.0f, 1.0f),
		QVector3D(0.0f, 0.0f, -1.0f),
		QVector3D(0.0f, 1.0f, 0.0f),
		100.0f, width(), height(), 0.1f, 100.f
	);
	camera->setSpeed(0.5);

	playerObjShader = make_unique<ShaderProgram>(this);
	playerObjShader->loadShaders(
		":/vertexShader",
		":/fragShader"
	);

	/*
		INSTANSTIATE playerObject
	*/
	initializeGLfromGrid();
}



void MazeGLWidget::initializeGLfromGrid() {
	gameObjects = new vector<GameObject *>();


	GameObject *playerObject = new PlayerObject(false);
	playerObject->loadObject(QString(":/cubeObj"), QString(":/erdeMitGrassTexture"));
	playerObject->setTranslation(QVector3D(mazeGrid->sx, mazeGrid->sy, 0));
	playerObject->setupModelMatrix(
		QVector3D(
			mazeGrid->sx - mazeGrid->width / 2,
			mazeGrid->sy - mazeGrid->height / 2, 0.1f
		),
		QVector3D(1.0, 1.0, 0.1f)
	);

	playerObject->setupGLBuffers();
	gameObjects->push_back(playerObject);


	/*
		INSTANSTIATE walls
	*/
	vector<int> xyLocation;
	for (int i = 0; i < mazeGrid->width*mazeGrid->height; i++) {
		xyLocation = mazeGrid->indexToxy(i);
		if (mazeGrid->grid->at(i) == 1) {
			GameObject *obj = new WallObject(true);
			obj->loadObject(QString(":/cubeObj"), QString(":/blattTexture"));
			obj->setupModelMatrix(
				QVector3D(
					xyLocation[0] - mazeGrid->width / 2,
					xyLocation[1] - mazeGrid->height / 2, 0
				),
				QVector3D(1.0, 1.0, .05f)
			);
			obj->setupGLBuffers();
			gameObjects->push_back(obj);

		}
	}

	/*
		INSTANSTIATE destination
	*/
	GameObject *destinationObject = new WallObject(false);
	destinationObject->loadObject(QString(":/cubeObj"), QString(":/ziegelsteinTexture"));

	destinationObject->setTranslation(QVector3D(mazeGrid->ex, mazeGrid->ey, 0));
	destinationObject->setupModelMatrix(
		QVector3D(
			mazeGrid->ex - mazeGrid->width / 2,
			mazeGrid->ey - mazeGrid->height / 2, 0.0f
		),
		QVector3D(1.0, 1.0, 0.05f)
	);
	destinationObject->setupGLBuffers();
	gameObjects->push_back(destinationObject);


}


void MazeGLWidget::paintGL() {

	frame += 1;

	glClearColor(0,0,0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	if (mazeGrid->solved) {
		signalGameOver();
		reset(mazeGrid->width, mazeGrid->height);
	}

	for (int i = 0; i < gameObjects->size(); i++) {
		
		playerObjShader->activate();
		playerObjShader->sendMatricesToShader(
			camera->getProjectionMatrix(), 
			camera->getViewMatrix(), 
			gameObjects->at(i)->getModelMatrix()
		);
		gameObjects->at(i)->render(playerObjShader);
		playerObjShader->deactivate();
	}

}

void MazeGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	camera->updateProjectionMatrix(width, height);
}

void MazeGLWidget::reset(unsigned int w, unsigned int h) {
	qDebug() << "reset clicked" << w << " " << h;

	updateTimer.stop();

	mazeGrid->helper(w, h);
	initializeGLfromGrid();

	this->setFocus();

	updateTimer.start();
}

void MazeGLWidget::signalGameOver() {
	emit gameOver();

}

void MazeGLWidget::keyPressEvent(QKeyEvent * event) {
	for (int i = 0; i < gameObjects->size(); i++) {
		gameObjects->at(i)->updateObject(frame, event, mazeGrid);
	}

}

void MazeGLWidget::wheelEvent(QWheelEvent * event) {
	camera->update(event);
}
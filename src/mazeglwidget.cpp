#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setSamples(16);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);
	this->setFormat(format);

	this->setFocus();

	mazeGrid = new Algorithms();
	mazeGrid->helper(10, 10);

}


MazeGLWidget::~MazeGLWidget() {
	for (int i = 0; i < gameObjects->size(); i++) {
		delete gameObjects->at(i);
	}
}

void MazeGLWidget::initializeGL() {

	initializeOpenGLFunctions();

	glDepthMask(GL_TRUE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	
	camera = new Camera(
		QVector3D(0.0f, 0.0f, 1.0f),
		QVector3D(0.0f, 0.0f, -1.0f),
		QVector3D(0.0f, 1.0f, 0.0f),
		100.0f, frameBufferWidth, frameBufferHeight, 0.1f, 100.f
	);
	camera->setSpeed(0.08);

	playerObjShader = new ShaderProgram(this);
	playerObjShader->loadShaders(
		"://vertexShader",
		"://fragShader"
	);

	/*
		INSTANSTIATE playerObject
	*/
	initializeGLfromGrid();
}

void MazeGLWidget::paintGL() {
	frame += 1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int side = qMin(width(), height());
	glViewport((width() - side) / 2, (height() - side) / 2, side, side);

	if (mazeGrid->solved) {
		signalGameOver();
		reset(mazeGrid->width, mazeGrid->height);
	}

	for (int i = 0; i < gameObjects->size(); i++) {
		gameObjects->at(i)->setShaders(playerObjShader);
		playerObjShader->sendMatricesToShader(
			*camera, 
			gameObjects->at(i)->getModelMatrix()
		);
		playerObjShader->sendColorToShader(
			gameObjects->at(i)->getColor()
		);
		gameObjects->at(i)->render();
		
	}

}

void MazeGLWidget::resizeGL(int width, int height)
{
	QSizeF designSize = QSizeF(width, height);
	QSizeF scaledSize = QSizeF(size());

	scaledSize.scale(designSize, Qt::KeepAspectRatioByExpanding);

	frameBufferWidth = scaledSize.width();
	frameBufferHeight = scaledSize.height();

	aspect_ratio = frameBufferWidth*1.0 / frameBufferHeight;

	camera->updateProjectionMatrix(frameBufferWidth, frameBufferHeight);
}

void MazeGLWidget::reset(unsigned int w, unsigned int h) {
	qDebug() << "reset clicked" << w << " " << h;

	mazeGrid->helper(w, h);
	initializeGLfromGrid();
	update();
	this->setFocus();
}


void MazeGLWidget::initializeGLfromGrid() {
	gameObjects = new vector<GameObject *>();


	GameObject *playerObject = new PlayerObject(
		false,
		QString("://cubeObj"),
		QVector3D(0.22, 0.557, 0.23)
	);
	playerObject->setTranslation(QVector3D(mazeGrid->sx, mazeGrid->sy, 0));
	playerObject->setupModelMatrix(
		QVector3D(
			mazeGrid->sx - mazeGrid->width / 2,
			mazeGrid->sy - mazeGrid->height / 2, 0.1f
		),
		QVector3D(
		(2.0 / (mazeGrid->width)),
			(2.0 / (mazeGrid->width)), 0.1f
		)
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
			GameObject *obj = new WallObject(
				true,
				QString("://cubeObj"),
				QVector3D(0.961, 0.486, 0)
			);
			obj->setupModelMatrix(
				QVector3D(
					xyLocation[0] - mazeGrid->width / 2,
					xyLocation[1] - mazeGrid->height / 2, 0
				),
				QVector3D(
				(2.0 / (mazeGrid->width)),
					(2.0 / (mazeGrid->width)),
					.05f
				)
			);
			obj->setupGLBuffers();
			gameObjects->push_back(obj);

		}
	}

	/*
		INSTANSTIATE destination
	*/
	GameObject *destinationObject = new WallObject(
		false,
		QString("://cubeObj"),
		QVector3D(0.098, 0.463, 0.824)
	);
	destinationObject->setTranslation(QVector3D(mazeGrid->ex, mazeGrid->ey, 0));
	destinationObject->setupModelMatrix(
		QVector3D(
			mazeGrid->ex - mazeGrid->width / 2,
			mazeGrid->ey - mazeGrid->height / 2, 0.0f
		),
		QVector3D(
		(2.0 / (mazeGrid->width)),
			(2.0 / (mazeGrid->width)), 0.05f
		)
	);
	destinationObject->setupGLBuffers();
	gameObjects->push_back(destinationObject);


}

void MazeGLWidget::signalGameOver() {
	emit gameOver();

}

void MazeGLWidget::keyPressEvent(QKeyEvent * event) {
	for (int i = 0; i < gameObjects->size(); i++) {
		gameObjects->at(i)->updateObject(frame, event, mazeGrid);
	}

	update();
}
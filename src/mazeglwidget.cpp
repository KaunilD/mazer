#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setSamples(16);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);
	this->setFormat(format);

	this->setGeometry(0, 0, width(), height());
	this->setFocus();

	mazeGrid = new Algorithms(10, 10);
	mazeGrid->helper(5, 6);
	mazeGrid->printGrid();

}


MazeGLWidget::~MazeGLWidget() {}

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
		90.0f, width() / (float)height(), 0.1f, 100.f
	);
	camera->setSpeed(0.08);

	playerObjShader = new ShaderProgram(this);
	playerObjShader->loadShaders(
		"://vertexShader",
		"://fragShader"
	);


	GameObject *playerObject = new PlayerObject(
		false, 
		QString("://slrCameraObj"), 
		QVector3D(0.0, 1.0, 1.0)
	);
	playerObject->setTranslation(QVector3D(mazeGrid->sx, mazeGrid->sy, 0));
	playerObject->setupModelMatrix(
		QVector3D(
			mazeGrid->sx + 0.5 - mazeGrid->width / 2,
			mazeGrid->sy + 0.5 - mazeGrid->height / 2, 0.0f
		),
		QVector3D(
			(2.0 / (mazeGrid->width)),
			(2.0 / (mazeGrid->height)), 0.1f
		)
	);

	playerObject->setupGLBuffers();
	gameObjects.push_back(playerObject);


	vector<int> xyLocation;
	for (int i = 0; i < mazeGrid->width*mazeGrid->height; i++) {
		xyLocation = mazeGrid->indexToxy(i);
		GameObject *obj = new WallObject(
			true, 
			QString("://cubeObj"), 
			QVector3D(1.0, 0, 0.00)
		);
		obj->setupModelMatrix(
			QVector3D(
				xyLocation[0] + 0.5 - mazeGrid->width / 2,
				xyLocation[1] + 0.5 - mazeGrid->height / 2, 0
			),
			QVector3D(
				(2.0 / (mazeGrid->width)),
				(2.0 / (mazeGrid->height)), 
				.10f
			)
		);
		obj->setupGLBuffers();
		gameObjects.push_back(obj);
	}
}

void MazeGLWidget::paintGL() {

	frame += 1;
	glViewport(0, 0, width(), height());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	gameObjects[0]->setShaders(playerObjShader);
	playerObjShader->sendMatricesToShader(
		*camera, 
		gameObjects[0]->getModelMatrix()
	);
	playerObjShader->sendColorToShader(
		gameObjects[0]->getColor()
	);
	gameObjects[0]->render();

	
	for (int i = 0; i < mazeGrid->width*mazeGrid->height; i++) {
		if (mazeGrid->grid[i] == 1) {
			gameObjects[i+1]->setShaders(playerObjShader);
			playerObjShader->sendMatricesToShader(
				*camera, 
				gameObjects[i + 1]->getModelMatrix()
			);
			playerObjShader->sendColorToShader(
				QVector3D(1.0, 0.0, 1.0)    
			);
			qDebug() << gameObjects[i + 1]->getColor();
			gameObjects[i+1]->render();
		}
	}

}

void MazeGLWidget::resize() {
	qDebug() << "resize";
	QSizeF designSize = QSizeF(mazeGrid->width, mazeGrid->height);
	QSizeF scaledSize = QSizeF(size());

	scaledSize.scale(designSize, Qt::KeepAspectRatioByExpanding);

	_width = scaledSize.width();
	_height = scaledSize.height();

}

void MazeGLWidget::resizeGL(int width, int height)
{
	aspect_ratio = width / (float)height;
	int side = qMin(width, height);
	glViewport(0, 0, width, height);
}



void MazeGLWidget::keyPressEvent(QKeyEvent * event) {

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->updateObject(frame, event, mazeGrid);
	}
	camera->updateViewMatrix();

	update();

}
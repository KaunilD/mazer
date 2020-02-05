#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setSamples(16);
	format.setProfile(QSurfaceFormat::CompatibilityProfile);
	this->setFormat(format);

	this->setFocus();

	mazeGrid = new Algorithms(20, 20);
	mazeGrid->helper(4, 6);
	//mazeGrid->printGrid();


}


MazeGLWidget::~MazeGLWidget() {
	for (int i = 0; i < gameObjects.size(); i++) {
		delete gameObjects[i];
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
		100.0f, width() / (float)height(), 0.1f, 100.f
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
	GameObject *playerObject = new PlayerObject(
		false, 
		QString("://cubeObj"), 
		QVector3D(1.0, 0.50, 1.0)
	);
	playerObject->setTranslation(QVector3D(mazeGrid->sx, mazeGrid->sy, 0));
	playerObject->setupModelMatrix(
		QVector3D(
			mazeGrid->sx - mazeGrid->width / 2,
			mazeGrid->sy - mazeGrid->height / 2, 0.1f
		),
		QVector3D(
			(2.0 / (mazeGrid->width)),
			(2.0 / (mazeGrid->height)), 0.1f
		)
	);

	playerObject->setupGLBuffers();
	gameObjects.push_back(playerObject);


	/*
		INSTANSTIATE walls
	*/
	vector<int> xyLocation;
	for (int i = 0; i < mazeGrid->width*mazeGrid->height; i++) {
		xyLocation = mazeGrid->indexToxy(i);
		if (mazeGrid->grid[i] == 1) {

			qDebug() << xyLocation;
			GameObject *obj = new WallObject(
				true,
				QString("://cubeObj"),
				QVector3D(0.1, 1.0, 1.00)
			);
			obj->setupModelMatrix(
				QVector3D(
					xyLocation[0] - mazeGrid->width / 2,
					xyLocation[1] - mazeGrid->height / 2, 0
				),
				QVector3D(
				(2.0 / (mazeGrid->width)),
					(2.0 / (mazeGrid->height)),
					.05f
				)
			);
			obj->setupGLBuffers();
			gameObjects.push_back(obj);

		}
	}

	/*
		INSTANSTIATE destination
	*/
	GameObject *destinationObject = new WallObject(
		false,
		QString("://cubeObj"),
		QVector3D(1.0, .50, 1.0)
	);
	destinationObject->setTranslation(QVector3D(mazeGrid->ex, mazeGrid->ey, 0));
	destinationObject->setupModelMatrix(
		QVector3D(
			mazeGrid->ex - mazeGrid->width / 2,
			mazeGrid->ey - mazeGrid->height / 2, 0.0f
		),
		QVector3D(
			(2.0 / (mazeGrid->width)),
			(2.0 / (mazeGrid->height)), 0.05f
		)
	);
	destinationObject->setupGLBuffers();
	gameObjects.push_back(destinationObject);
	qDebug() << "Rendered destination";

}

void MazeGLWidget::paintGL() {

	frame += 1;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int side = qMin(width(), height());
	glViewport((width() - side) / 2, (height() - side) / 2, side, side);


	/*
		RENDER playerObject
	
	gameObjects[0]->setShaders(playerObjShader);
	playerObjShader->sendMatricesToShader(
		*camera, 
		gameObjects[0]->getModelMatrix()
	);
	playerObjShader->sendColorToShader(
		gameObjects[0]->getColor()
	);
	gameObjects[0]->render();
	qDebug() << "PLAYEROBJECT ";
	*/

	/*
		RENDER destination
	gameObjects[gameObjects.size()-1]->setShaders(playerObjShader);
	playerObjShader->sendMatricesToShader(
		*camera,
		gameObjects[gameObjects.size() - 1]->getModelMatrix()
	);
	playerObjShader->sendColorToShader(
		gameObjects[gameObjects.size() - 1]->getColor()
	);
	gameObjects[gameObjects.size() - 1]->render();
	qDebug() << "DESTINATION";
	*/
	/*
		RENDER walls
	*/

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects[i]->setShaders(playerObjShader);
		playerObjShader->sendMatricesToShader(
			*camera, 
			gameObjects[i]->getModelMatrix()
		);
		playerObjShader->sendColorToShader(
			gameObjects[i]->getColor()
		);
		gameObjects[i]->render();
		
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

}



void MazeGLWidget::keyPressEvent(QKeyEvent * event) {

	for (int i = 0; i < gameObjects.size(); i++) {
		gameObjects.at(i)->updateObject(frame, event, mazeGrid);
	}
	camera->updateViewMatrix();

	update();

}
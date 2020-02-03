#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setSamples(16);
	this->setFormat(format);

	this->setGeometry(0, 0, width(), height());

	projectionMatrix = new QMatrix4x4();
	projectionMatrix->setToIdentity();
	projectionMatrix->perspective(90.0, _width/_height, .10f, 100.);

	viewMatrix = new QMatrix4x4();
	viewMatrix->setToIdentity();
	viewMatrix->lookAt(
		QVector3D(0.0f, 0.0f, 1.0f), 
		QVector3D(0.0f, 0.0f, 0.0f), 
		QVector3D(0.0f, 1.0f, 0.0f)
	);


	algorithm = new Algorithms(20, 20);
	algorithm->backtrackRecursively(2, 2);
}


MazeGLWidget::~MazeGLWidget() {}

void MazeGLWidget::initializeGL() {
	initializeOpenGLFunctions();

	glDepthMask(GL_TRUE);
	/* clear the depth */
	//glClearDepth(1.0f);
	/* enable the depth test */
	glEnable(GL_DEPTH_TEST);
	/* enable cullmode CCW (counter clockwise) */
	glEnable(GL_CULL_FACE);
	/* sets the color the screen needs to be cleared with */
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	playerObjShader = new ShaderProgram(this);
	playerObjShader->loadShaders(
		"://vertexShader",
		"://fragShader"
	);


	playerObj = new GameObject(false, QString("://slrCameraObj"));
	playerObj->setupModelMatrix(
		QVector3D(0.0, 0.0, 0.0), 
		QVector3D(1.0, 1.0, 1.0)
	);
	playerObj->setupGLBuffers();

	vector<int> xyLocation;
	mazeBlocks = new vector<GameObject *>(algorithm->grid.size());
	for (int i = 0; i < mazeBlocks->size(); i++) {
		if (algorithm->grid[i] == 1) {

			xyLocation = algorithm->indexToxy(i);
			qDebug() << (xyLocation[0] / (float)(algorithm->width));
			GameObject *obj = new GameObject(true, QString("://cubeObj"));
			obj->setupModelMatrix(
				QVector3D(
					xyLocation[0]+0.5 - algorithm->width/2,
					xyLocation[1]+0.5 - algorithm->height/2, 0
				), 
				QVector3D(
					(2.0/(algorithm->width)), 
					(2.0/(algorithm->height)), .10f
				)
			);

			obj->setupGLBuffers();
			mazeBlocks->at(i) = obj;
		}
	}
}

void MazeGLWidget::paintGL() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	
	playerObj->attachShaders(playerObjShader);

	playerObjShader->program->setUniformValue(
		playerObjShader->projectionMatrix,
		*projectionMatrix
	);
	playerObjShader->program->setUniformValue(
		playerObjShader->viewMatrix,
		*viewMatrix
	);
	playerObjShader->program->setUniformValue(
		playerObjShader->modelMatrix,
		playerObj->getModelMatrix()
	);

	//playerObj->render();
	
	for (int i = 0; i < mazeBlocks->size(); i++) {
		if (algorithm->grid[i] == 1) {
			mazeBlocks->at(i)->attachShaders(playerObjShader);

			playerObjShader->program->setUniformValue(
				playerObjShader->projectionMatrix,
				*projectionMatrix
			);
			playerObjShader->program->setUniformValue(
				playerObjShader->viewMatrix,
				*viewMatrix
			);

			playerObjShader->program->setUniformValue(
				playerObjShader->modelMatrix,
				mazeBlocks->at(i)->getModelMatrix()
			);
			mazeBlocks->at(i)->render();

		}
	}
	
}

void MazeGLWidget::resize() {
	qDebug() << "resize";
	QSizeF designSize = QSizeF(algorithm->width, algorithm->height);
	QSizeF scaledSize = QSizeF(size());

	scaledSize.scale(designSize, Qt::KeepAspectRatioByExpanding);

	_width = scaledSize.width();
	_height = scaledSize.height();

	update();

}

void MazeGLWidget::resizeGL(int w, int h) {
	qDebug() << "glwidget resize";
	aspect_ratio = h ? w / (float)h : 1;
	int side = qMin(w, h);
	glViewport(0, 0, w, h);
}

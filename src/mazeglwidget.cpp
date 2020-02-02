#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
	QSurfaceFormat format;
	format.setSamples(16);
	this->setFormat(format);
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
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	

	playerObjShader = new ShaderProgram(this);
	playerObjShader->loadShaders(
		"://vertexShader",
		"://fragShader"
	);

	playerObj = new ObjLoader();
	playerObj->loadObject("://slrCameraObj");
	playerObj->setupModelMatrix();
	playerObj->setupGLBuffers();

}

void MazeGLWidget::paintGL() {
	playerObj->attachShaders(playerObjShader);
	playerObj->render();
}

void MazeGLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
}

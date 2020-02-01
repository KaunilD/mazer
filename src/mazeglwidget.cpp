#include "mazeglwidget.hpp"

MazeGLWidget::MazeGLWidget(QWidget *parent): QOpenGLWidget(parent)
{

}


MazeGLWidget::~MazeGLWidget()
{

}

void MazeGLWidget::initializeGL() {
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST | GL_LIGHT0 | GL_LIGHTING | GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void MazeGLWidget::paintGL() {
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-0.5, -0.5, 0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.5, -0.5, 0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.5, 0);
	glEnd();

}

void MazeGLWidget::resizeGL(int w, int h) {
	glViewport(0, 0, w, h);
}
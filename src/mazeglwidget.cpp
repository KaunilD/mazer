#include "mazeglwidget.hpp"
// GL
#include <GL/glew.h>
#include <GLFW/glfw3.h>
// GLM
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>


MazeGLWidget::MazeGLWidget(QWidget *parent): QOpenGLWidget(parent)
{

}


MazeGLWidget::~MazeGLWidget()
{

}

void MazeGLWidget::initializeGL() 
{
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST | GL_LIGHT0 | GL_LIGHTING | GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

void MazeGLWidget::paintGL() 
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

}

void MazeGLWidget::resizeGL(int w, int h) 
{
	glViewport(0, 0, w, h);
}
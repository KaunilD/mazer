#ifndef MAZEGLWIDGET_H
#define MAZEGLWIDGET_H
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
// ObjectLoader
#include "objectLoader.hpp"
// Qt
#include <QWidget>
#include <QOpenGLWidget>


class MazeGLWidget : public QOpenGLWidget
{
public:
	MazeGLWidget(QWidget *parent = 0);
	~MazeGLWidget();

	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

private:



	GLuint m_posAttr;
	GLuint m_colAttr;
	GLuint m_matrixUniform;
	int m_frame;
};

#endif
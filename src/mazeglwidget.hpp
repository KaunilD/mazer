#ifndef MAZEGLWIDGET_H
#define MAZEGLWIDGET_H

#include <QWidget>
#include <QOpenGLWidget>

#include <gl/GLU.h>
#include <gl/GL.h>

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

#endif //MAZEGLWIDGET_H
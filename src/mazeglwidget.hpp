#ifndef MAZEGLWIDGET_H
#define MAZEGLWIDGET_H
// ObjectLoader
#include "objLoader.hpp"
// shaderprogram
#include "shaderprogram.hpp"
// Qt
#include <QWidget>
#include <QOpenGLWidget>


class MazeGLWidget : public QOpenGLWidget, protected QAbstractOpenGLFunctions
{
public:
	MazeGLWidget(QWidget *parent = 0);
	~MazeGLWidget();


	ObjLoader * playerObj;
	ShaderProgram * playerObjShader;

	void initializeGL();
	void paintGL();
	void resizeGL(int w, int h);

private:

	int m_frame;
	void loadShader(const char * vs, const char * fs);
};

#endif
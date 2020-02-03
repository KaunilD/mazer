#ifndef MAZEGLWIDGET_H
#define MAZEGLWIDGET_H
// shaderprogram
#include "shaderprogram.hpp"
// Qt
#include <QWidget>
#include <QOpenGLWidget>
// algorithms
#include "gameobject.hpp"
#include "algorithms.hpp"


class MazeGLWidget : public QOpenGLWidget, protected QAbstractOpenGLFunctions
{
public:
	MazeGLWidget(QWidget *parent = 0);
	~MazeGLWidget();


	GameObject * playerObj;
	ShaderProgram * playerObjShader;

	Algorithms * algorithm;
	vector<GameObject *> * mazeBlocks;
	QMatrix4x4 * projectionMatrix, *viewMatrix;
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	float _width, _height;
	float aspect_ratio{1.0};
	void resize();
private:

	int m_frame;
	void loadShader(const char * vs, const char * fs);
};

#endif
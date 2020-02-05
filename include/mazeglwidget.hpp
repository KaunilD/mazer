#ifndef MAZEGLWIDGET_H
#define MAZEGLWIDGET_H
// shaderprogram
#include "shaderprogram.hpp"
// Qt

#include <QKeyEvent>
#include <QWidget>
#include <QOpenGLWidget>
// algorithms
#include "gameobject/gameobject.hpp"
#include "gameobject/playerobject.hpp"
#include "gameobject/wallobject.hpp"
#include "algorithms.hpp"
#include "camera.hpp"

class MazeGLWidget : public QOpenGLWidget, protected QAbstractOpenGLFunctions
{
public:
	MazeGLWidget(QWidget *parent = 0);
	~MazeGLWidget();


	ShaderProgram * playerObjShader;

	Algorithms * mazeGrid;
	vector<GameObject *> * mazeBlocks;
	vector<GameObject *> gameObjects;
	QMatrix4x4 * projectionMatrix, *viewMatrix;
	Camera *camera;
	
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	float _width, _height;
	float aspect_ratio{1.0};
	void resize();
	bool isWall();
private:
	int frame{0};
	void loadShader(const char * vs, const char * fs);

protected:
	void keyPressEvent(QKeyEvent *);

};

#endif
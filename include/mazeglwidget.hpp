#ifndef MAZEGLWIDGET_H
#define MAZEGLWIDGET_H
// Qt
#include <QKeyEvent>
#include <QWidget>
#include <QTimer>
#include <QOpenGLWidget>
// yours truly
#include "gameobject/gameobject.hpp"
#include "gameobject/playerobject.hpp"
#include "gameobject/wallobject.hpp"
#include "algorithms.hpp"
#include "camera.hpp"
#include "libs.hpp"
#include "shaderprogram.hpp"

class MazeGLWidget : public QOpenGLWidget, protected QAbstractOpenGLFunctions
{
	Q_OBJECT

public:

	MazeGLWidget(QWidget *parent = 0);
	~MazeGLWidget();


	shared_ptr<ShaderProgram> playerObjShader;

	shared_ptr<Algorithms> mazeGrid;

	vector<GameObject *> * gameObjects;
	
	unique_ptr<Camera> camera;
	
	void initializeGL() override;
	void paintGL() override;
	void resizeGL(int w, int h) override;
	void resize();
	bool isWall();
	void reset(unsigned int w, unsigned int h);
	void signalGameOver();
	void initializeGLfromGrid();
private:
	int frame{0};
	QTimer updateTimer;
	void loadShader(const char * vs, const char * fs);
signals:
	void gameOver();
protected:
	void keyPressEvent(QKeyEvent *);
	void wheelEvent(QWheelEvent *);
};

#endif
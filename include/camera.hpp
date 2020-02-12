#ifndef CAMERA_H
#define CAMERA_H

#include "libs.hpp"
#include <QMatrix4x4>
#include <QVector3D>
#include <QWheelEvent>

enum Movement {
	W,
	A,
	S,
	D
};

class Camera {
protected:
	unique_ptr<QMatrix4x4> projectionMatrix, viewMatrix;

public:
	float fov;
	float _near;
	float _far;

	int frameBufferWidth, frameBufferHeight;

	double speed;

	QVector3D posVector, upVector, frontVector;

	Camera();
	Camera(
		QVector3D posVector, QVector3D frontVector, QVector3D upVector, 
		float fov, int fbW, int fbH, float _near, float _far
	);
	~Camera();

	void setSpeed(double speed);
	void processKB(Movement mov, float speed);

	void updateViewMatrix();
	void updateProjectionMatrix(int frameBufferWidth, int frameBufferHeight);
	void resetProjectionMatrix();

	// view and projection matrices should be only modified from within the 
	// class
	const  QMatrix4x4 & getProjectionMatrix() const;
	const QMatrix4x4 & getViewMatrix() const;

	void update(QWheelEvent *);
};

#endif
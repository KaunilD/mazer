#ifndef CAMERA_H
#define CAMERA_H


#include <QMatrix4x4>
#include <QVector3D>

enum Movement {
	W,
	A,
	S,
	D
};

class Camera {
public:
	float fov;
	float _near;
	float _far;

	double aspect_ratio{ 1.3 };

	double speed;

	QMatrix4x4 *projectionMatrix, *viewMatrix;

	QVector3D posVector, upVector, frontVector;

	Camera();
	Camera(
		QVector3D posVector, QVector3D frontVector, QVector3D upVector, 
		float fov, float aspect_ratio, float _near, float _far
	);
	~Camera();

	void setSpeed(double speed);
	void processKB(Movement mov, float speed);

	void updateViewMatrix();
	void updateProjectionMatrix();
	QMatrix4x4 getProjectionMatrix();
	QMatrix4x4 getViewMatrix();
};

#endif
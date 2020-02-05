#include "camera.hpp"

Camera::Camera(){}

Camera::Camera(
	QVector3D posVector, QVector3D frontVector, QVector3D upVector, 
	float fov, float aspect_ratio, float near, float far
): posVector(posVector), frontVector(frontVector), upVector(upVector), fov(fov), aspect_ratio(aspect_ratio), _near(near), _far(far) {
	
	viewMatrix = new QMatrix4x4();
	viewMatrix->setToIdentity();

	projectionMatrix = new QMatrix4x4();
	projectionMatrix->setToIdentity();

	updateViewMatrix();
	updateProjectionMatrix();
}

void Camera::setSpeed(double _speed) {
	speed = _speed;
}

void Camera::processKB(Movement movement, float speed){
	if (movement == W) {
		posVector += speed * frontVector;
	}
	if (movement == S) {
		posVector -= speed * frontVector;
	}
	if (movement == D) {
		posVector += speed * upVector;
	}
	if (movement == A) {
		posVector -= speed * upVector;
	}
}


void Camera::updateViewMatrix() {

	viewMatrix->setToIdentity();
		viewMatrix->lookAt(
		posVector, posVector + frontVector, upVector
	);
	
}


void Camera::updateProjectionMatrix() {
	projectionMatrix->setToIdentity();
	projectionMatrix->perspective(
		fov,
		aspect_ratio,
		_near, _far
	);
}

QMatrix4x4 Camera::getProjectionMatrix() {
	return *projectionMatrix;
}

QMatrix4x4 Camera::getViewMatrix() {
	return *viewMatrix;
}

Camera::~Camera() {

}
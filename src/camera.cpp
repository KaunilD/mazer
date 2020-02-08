#include "camera.hpp"

Camera::Camera(){}

Camera::Camera(
	QVector3D posVector, QVector3D frontVector, QVector3D upVector, 
	float fov, int fbW, int fbH, float near, float far
): posVector(posVector), frontVector(frontVector), upVector(upVector), fov(fov), frameBufferWidth(fbW), frameBufferHeight(fbH), _near(near), _far(far) {
	
	viewMatrix = new QMatrix4x4();
	viewMatrix->setToIdentity();

	projectionMatrix = new QMatrix4x4();
	projectionMatrix->setToIdentity();

	updateViewMatrix();
	updateProjectionMatrix(fbW, fbH);
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


void Camera::updateProjectionMatrix(int _frameBufferWidth, int _frameBufferHeight) {
	projectionMatrix->setToIdentity();
	projectionMatrix->perspective(
		fov,
		_frameBufferWidth*1.0/_frameBufferHeight,
		_near, _far
	);
}

void Camera::resetProjectionMatrix() {
	projectionMatrix->setToIdentity();
	projectionMatrix->perspective(
		fov,
		frameBufferWidth*1.0 / frameBufferHeight,
		_near, _far
	);
}

QMatrix4x4 Camera::getProjectionMatrix() {
	return *projectionMatrix;
}

QMatrix4x4 Camera::getViewMatrix() {
	return *viewMatrix;
}

void Camera::update(QWheelEvent * event) {
	if (event->delta() < 0)
		fov += speed;
	else if (fov > 1)
		fov -= speed;

	resetProjectionMatrix();

}

Camera::~Camera() {

}
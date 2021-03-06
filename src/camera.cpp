#include "camera.hpp"

Camera::Camera(){}

Camera::Camera(
	QVector3D posVector, QVector3D frontVector, QVector3D upVector, 
	float fov, int fbW, int fbH, float Cnear, float Cfar
): posVector(posVector), frontVector(frontVector), upVector(upVector), fov(fov), frameBufferWidth(fbW), frameBufferHeight(fbH), _near(Cnear), _far(Cfar) {
	
	viewMatrix = make_unique<QMatrix4x4>();
	projectionMatrix = make_unique<QMatrix4x4>();
	
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
	frameBufferWidth = _frameBufferWidth;
	frameBufferHeight = _frameBufferHeight;

	reComputeProjectionMatrix();
}

void Camera::reComputeProjectionMatrix() {
	projectionMatrix->setToIdentity();
	projectionMatrix->perspective(
		fov,
		frameBufferWidth/ (float) frameBufferHeight,
		_near, _far
	);
}

const QMatrix4x4 & Camera::getProjectionMatrix() const{
	return *projectionMatrix;
}

const QMatrix4x4 & Camera::getViewMatrix() const{
	return *viewMatrix;
}

void Camera::update(QWheelEvent * event) {
	
	if (event->delta() < 0)
		fov += speed;
	else if (fov > 1)
		fov -= speed;

	reComputeProjectionMatrix();

}

Camera::~Camera() {
}
#include "shaderprogram.hpp"

ShaderProgram::ShaderProgram(QObject *parent){
	std::cout << "Shader Created" << std::endl;
	program = new QOpenGLShaderProgram(parent);

};

void ShaderProgram::loadShaders(const char * vsPath, const char * fsPath) {
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(vsPath));
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(fsPath));
	program->link();

	modelMatrix = program->uniformLocation("modelMatrix");
	projectionMatrix = program->uniformLocation("projectionMatrix");
	viewMatrix = program->uniformLocation("viewMatrix");
	colorVec3 = program->uniformLocation("u_vs_color");
}


void ShaderProgram::sendMatricesToShader(Camera camera, QMatrix4x4 _modelMatrix) {
	program->setUniformValue(
		projectionMatrix,
		camera.getProjectionMatrix()
	);
	program->setUniformValue(
		viewMatrix,
		camera.getViewMatrix()
	);
	program->setUniformValue(
		modelMatrix,
		_modelMatrix
	);

}

void ShaderProgram::sendColorToShader(QVector3D color) {
	program->setUniformValue(
		colorVec3,
		color
	);
}

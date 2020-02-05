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
}


void ShaderProgram::sendMatricesToShader(Camera camera) {
	program->setUniformValue(
		projectionMatrix,
		camera.getProjectionMatrix()
	);
	program->setUniformValue(
		viewMatrix,
		camera.getViewMatrix()
	);

}


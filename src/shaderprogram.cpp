#include "shaderprogram.hpp"

ShaderProgram::ShaderProgram(){}

ShaderProgram::ShaderProgram(QObject *parent){
	program = make_unique<QOpenGLShaderProgram>(parent);
};

void ShaderProgram::loadShaders(const char * vsPath, const char * fsPath) {
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString(vsPath));
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString(fsPath));
	
	program->link();

	modelMatrix = program->uniformLocation("modelMatrix");
	projectionMatrix = program->uniformLocation("projectionMatrix");
	viewMatrix = program->uniformLocation("viewMatrix");

	program->release();
}

void ShaderProgram::deactivate() {
	if (this->program->isLinked()) {
		this->program->release();
	}
}

bool ShaderProgram::activate() {
	if (this->program->isLinked()) {
		return this->program->bind();
	}
	return false;
}

void ShaderProgram::sendMatricesToShader(const QMatrix4x4 & projectionMatrix, const QMatrix4x4 & viewMatrix, const QMatrix4x4 & modelMatrix) {
	program->setUniformValue(
		this->projectionMatrix,
		projectionMatrix
	);
	program->setUniformValue(
		this->viewMatrix,
		viewMatrix
	);
	program->setUniformValue(
		this->modelMatrix,
		modelMatrix
	);
}


ShaderProgram::~ShaderProgram() {
}
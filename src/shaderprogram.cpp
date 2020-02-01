#include "shaderprogram.hpp"

ShaderProgram::ShaderProgram(QObject *parent){
	std::cout << "Shader Created" << std::endl;
	program = new QOpenGLShaderProgram(parent);

};

void ShaderProgram::loadShaders(const char * vsPath, const char * fsPath) {
	program->addShaderFromSourceFile(QOpenGLShader::Vertex, vsPath);
	program->addShaderFromSourceFile(QOpenGLShader::Fragment, fsPath);
	program->link();
}

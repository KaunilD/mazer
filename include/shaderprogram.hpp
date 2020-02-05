#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include "libs.hpp"
#include "camera.hpp"
#include <QOpenGLShaderProgram>
#include <QObject>

class ShaderProgram {
	public:
		
		QOpenGLShaderProgram * program;
		
		ShaderProgram(QObject * parent);

		GLuint modelMatrix;
		GLuint viewMatrix;
		GLuint projectionMatrix;

		void loadShaders(const char * vs_path, const char * fs_path);

		void sendMatricesToShader(Camera camera);
};

#endif // SHADERPROGRAM_H
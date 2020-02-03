#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "libs.hpp"
#include "vertex.hpp"

#include <QVector>
#include <QFile>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "shaderprogram.hpp"

class GameObject: protected QOpenGLFunctions {
public:

	bool npc;
	
	GameObject();
	GameObject(bool npc, const QString & filePath);
	~GameObject();
	

	void scale(QVector3D scale);
	void translate(QVector3D translate);
	void setupModelMatrix(QVector3D translate, QVector3D scale);
	void attachShaders(ShaderProgram *);
	void setupGLBuffers();
	void render();
	void loadObject(const QString &);
	QMatrix4x4 & getModelMatrix();
	QMatrix4x4 & getProjectionMatrix();

	QOpenGLShaderProgram * program;
	QVector<Vertex> vertices;
	QVector<GLsizei> indices;
	QVector<QVector3D> rawVertices;
	QVector<QVector2D> rawTextures;
	QVector<QVector3D> rawNormals;
	std::vector<int> vertesIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;
	QOpenGLBuffer attributeBuffer, indexBuffer;
	QMatrix4x4 * modelMatrix, * projectionMatrix;



};

#endif
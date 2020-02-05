#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "libs.hpp"
#include "vertex.hpp"
#include "shaderprogram.hpp"
#include "algorithms.hpp"
#include <QVector>
#include <QFile>
#include <QMatrix4x4>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QKeyEvent>

class GameObject: protected QOpenGLFunctions {


protected:
	bool npc;
	QOpenGLShaderProgram * program;
	QMatrix4x4 * modelMatrix, *projectionMatrix;
	QVector3D color;
	QVector3D translation;
	QVector<Vertex> vertices;
	QVector<GLsizei> indices;
	QVector<QVector3D> rawVertices;
	QVector<QVector2D> rawTextures;
	QVector<QVector3D> rawNormals;
	std::vector<int> vertesIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;
	QOpenGLBuffer attributeBuffer, indexBuffer;

public:
	GameObject();
	GameObject(bool npc, const QString & filePath, QVector3D color);
	virtual ~GameObject();

	void setShaders(ShaderProgram *);
	QMatrix4x4 & getModelMatrix();
	QMatrix4x4 & getProjectionMatrix();
	void setupModelMatrix(QVector3D translate, QVector3D scale);

	void setColor(QVector3D color);

	void scale(QVector3D scale);
	void translate(QVector3D translate);
	void setTranslation(QVector3D translate);

	void setupGLBuffers();
	void render();
	void loadObject(const QString &);

	virtual void updateObject(int frames, QKeyEvent * event, Algorithms * mazeGrid) = 0;


	};
#endif
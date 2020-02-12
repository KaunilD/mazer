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
#include <QImage>
#include <QOpenGLTexture>

class GameObject: protected QOpenGLFunctions {


protected:
	bool npc;

	QMatrix4x4 * modelMatrix;
	QVector3D color;
	QOpenGLTexture * texture;
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
	GameObject(bool npc);
	virtual ~GameObject();

	const QMatrix4x4 * getModelMatrix() const;
	
	void setupModelMatrix(QVector3D translate, QVector3D scale);
	void scale(QVector3D scale);
	void translate(QVector3D translate);
	void setTranslation(QVector3D translate);


	void setColor(QVector3D color);
	QVector3D getColor() { return this->color; };
	
	
	void setupGLBuffers();
	void render(shared_ptr<ShaderProgram> & shaderProgram);
	void loadObject(const QString & objFile, const QString & textureImage);

	virtual void updateObject(int frames, QKeyEvent * event, const shared_ptr<Algorithms> & mazeGrid) = 0;


	};
#endif
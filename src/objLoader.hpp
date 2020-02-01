#include "libs.hpp"
#include "vertex.hpp"
// Boost
#define BOOST_FILESYSTEM_NO_DEPRECATED
#include <boost/filesystem.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <QVector>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include "shaderprogram.hpp"
/*
	Indexed v, vt, vn read from file using
	faces (f) section of the .obj file
*/

class ObjLoader: protected QOpenGLFunctions {
public:
	QVector<Vertex> vertices;
	QVector<GLsizei> indices;

	// raw data read from file line by line
	QVector<QVector3D> rawVertices;
	QVector<QVector2D> rawTextures;
	QVector<QVector3D> rawNormals;

	std::vector<int> vertesIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;

	ObjLoader();
	~ObjLoader();
	void loadObject(const char * obj_path);

	QOpenGLShaderProgram * program;
	GLuint shaderID;
	GLuint VAO, VBO, EBO;

	QOpenGLBuffer attributeBuffer, indexBuffer;

	glm::mat4 modelMatrix = glm::mat4(1.0f);

	void setupModelMatrix();
	void attachShaders(ShaderProgram *);
	void setupGLBuffers();
	void render();

};
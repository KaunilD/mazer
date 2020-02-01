#include "objLoader.hpp"

ObjLoader::ObjLoader() {
	initializeOpenGLFunctions();
};

void ObjLoader::loadObject(const char * obj_path) {
	std::ifstream objFile;
	std::string line;
	// ensure ifstream objects can throw exceptions:
	objFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		objFile.open(obj_path);
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::OBJLOADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	while (!objFile.eof()) {
		std::getline(objFile, line);
		std::istringstream ss(line);
		std::string token;

		std::getline(ss, token, ' ');
		//std::cout << line << std::endl;

		if (token == "v") {
			QVector3D vertex;
			for (int i = 0; i < 3; i++) {
				std::getline(ss, token, ' ');
				//std::cout << token << std::endl;
				vertex[i] = std::stof(token);
			}
			rawVertices.push_back(vertex);
		}
		else if (token == "vt") {
			QVector2D texture;
			for (int i = 0; i < 2; i++) {
				std::getline(ss, token, ' ');
				texture[i] = std::stof(token);
			}
			rawTextures.push_back(texture);
		}
		else if (token == "vn") {
			QVector3D normal;
			for (int i = 0; i < 3; i++)
			{
				std::getline(ss, token, ' ');
				normal[i] = std::stof(token);
			}
			rawNormals.push_back(normal);
		}
		else if (token == "f") {
			// f 1/1/1 2/2/2 3/3/3
			for (int i = 0; i < 3; i++) {
				std::getline(ss, token, ' ');
				std::istringstream ss2(token);
				std::string index;

				std::getline(ss2, index, '/');
				vertesIndices.push_back(std::stoul(index));

				std::getline(ss2, index, '/');
				textureIndices.push_back(std::stoul(index));

				std::getline(ss2, index, '/');
				normalIndices.push_back(std::stoul(index));
			}
		}
	}
	std::cout << vertesIndices.size() << std::endl;
	for (int i = 0; i < vertesIndices.size(); i++) {
		vertices.push_back(Vertex{
				rawVertices[vertesIndices[i] - 1],
				rawNormals[normalIndices[i] - 1],
				rawTextures[textureIndices[i] - 1],
				QVector3D(1.0f, 1.0f, 1.0f),
				QVector3D(1.0f, 1.0f, 1.0f),
				QVector3D(1.0f, 1.0f, 1.0f),
			});
		indices.push_back(i);
	}

	std::cout << "Loaded " << vertices.size() << " points.";

}

void ObjLoader::attachShaders(ShaderProgram * _program){
	program = _program->program;
};


void ObjLoader::setupModelMatrix() {

	modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f, 0.0f, 0.0f));
}

void ObjLoader::setupGLBuffers() {

	attributeBuffer.create();
	attributeBuffer.bind();
	attributeBuffer.allocate(
		vertices.constData(), 
		vertices.count()*static_cast<int>(sizeof(Vertex))
	);

	indexBuffer = QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
	indexBuffer.create();
	indexBuffer.bind();
	indexBuffer.allocate(
		indices.constData(),
		indices.count() * static_cast<int>(sizeof(GL_UNSIGNED_INT))
	);

}

void ObjLoader::render() {

	if (program == NULL) {
		return;
	}
	program->bind();

	qDebug() << "Rendering";
	indexBuffer.bind();
	attributeBuffer.bind();

	// POSITION
	GLuint positionAttribLoc = program->attributeLocation("vertex_position");
	program->enableAttributeArray(positionAttribLoc);
	program->setAttributeBuffer(positionAttribLoc, GL_FLOAT, (int)offsetof(Vertex, position), 3, sizeof(Vertex));
	// COLOR
	GLuint colorAttribLoc = program->attributeLocation("vertex_color");
	program->enableAttributeArray(colorAttribLoc);
	program->setAttributeBuffer(colorAttribLoc, GL_FLOAT, (int)offsetof(Vertex, color), 3, sizeof(Vertex));
	// NORMAL
	GLuint normalAttribLoc = program->attributeLocation("vertex_normal");
	program->enableAttributeArray(normalAttribLoc);
	program->setAttributeBuffer(colorAttribLoc, GL_FLOAT, (int)offsetof(Vertex, normals), 3, sizeof(Vertex));


	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);


	glDisableVertexAttribArray(positionAttribLoc);
	glDisableVertexAttribArray(colorAttribLoc);
	glDisableVertexAttribArray(normalAttribLoc);

	program->release();
}

ObjLoader::~ObjLoader() {
	indexBuffer.destroy();
	attributeBuffer.destroy();
}
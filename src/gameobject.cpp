#include "gameObject/gameObject.hpp"

GameObject::GameObject() {}

GameObject::GameObject(bool npc, const QString & filePath, QVector3D color):
	npc(npc), translation(QVector3D(1.0f, 1.0f, 1.0f)), color(QVector3D(0.0, 1.0, 1.0)) {

	initializeOpenGLFunctions();
	loadObject(filePath);
}

void GameObject::loadObject(const QString & filePath) {
	qDebug() << "ObjLoader:: Reading " << filePath;

	QFile obj_file(filePath);
	obj_file.open(QIODevice::ReadOnly);

	QTextStream textStream(&obj_file);


	if (obj_file.isOpen()) {
		while (!textStream.atEnd()) {
			QString line = textStream.readLine();
			QStringList list = line.split(" ");
			bool isTexture = list.count() == 4 ? false : true;
			if (list[0] == "v" && !isTexture) {
				QVector3D vertex;
				for (int i = 1; i < list.count(); i++) {
					vertex[i - 1] = list[i].toFloat();
				}
				//qDebug() << vertex;
				rawVertices.push_back(vertex);
			}
			else if (list[0] == "vt" && isTexture) {
				QVector2D texture;
				for (int i = 1; i < list.count(); i++) {
					texture[i - 1] = list[i].toFloat();
				}
				//qDebug() << texture;
				rawVertices.push_back(texture);
			}
			else if (list[0] == "vn" && !isTexture) {
				QVector3D normal;
				for (int i = 1; i < list.count(); i++) {
					normal[i - 1] = list[i].toFloat();
				}
				//qDebug() << normal;
				rawNormals.push_back(normal);
			}
			else if (list[0] == "f" && !isTexture) {
				// f 1/1/1 2/2/2 3/3/3
				for (int i = 1; i < list.count(); i++) {
					QStringList indexGroup = list[i].split("/");
					vertesIndices.push_back(indexGroup[0].toInt());
					textureIndices.push_back(indexGroup[1].toInt());
					normalIndices.push_back(indexGroup[2].toInt());
				}
				//qDebug() << list;
			}

		}
	}

	for (int i = 0; i < vertesIndices.size(); i++) {
		vertices.push_back(Vertex{
				rawVertices[vertesIndices[i] - 1],
				rawNormals[normalIndices[i] - 1],
				rawTextures[textureIndices[i] - 1],
				color,
				QVector3D(1.0f, 1.0f, 1.0f),
				QVector3D(1.0f, 1.0f, 1.0f),
			});
		indices.push_back(i);
	}

}


void GameObject::setShaders(ShaderProgram * _program) {
	program = _program->program;
	program->bind();

};

void GameObject::setColor(QVector3D _color) {
	color = _color;
}

void GameObject::setTranslation(QVector3D translate) {
	translation = translate;
}

void GameObject::translate(QVector3D translate) {
	modelMatrix->translate(translate);
}

void GameObject::scale(QVector3D scale) {
	modelMatrix->scale(scale);
}

void GameObject::setupModelMatrix(QVector3D _translate, QVector3D _scale) {
	modelMatrix = new QMatrix4x4();
	modelMatrix->setToIdentity();
	scale(_scale);
	translate(_translate);

}
void GameObject::setupGLBuffers() {

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

void GameObject::updateObject(int frame, QKeyEvent * event, Algorithms * mazeGrid) {

}

void GameObject::render() {

	if (program == NULL) {
		return;
	}

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

QMatrix4x4 & GameObject::getModelMatrix() {
	return *modelMatrix;
}

GameObject::~GameObject() {

	indexBuffer.destroy();
	attributeBuffer.destroy();
}

#pragma once

#include <GL3/gl3.h>
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "SceneObject.h"

class RenderedModel : public SceneObject {

private:

	Model* model;
	Texture* texture;

	GLuint vertexArrayID;
	GLuint bufferArrayID;

	GLfloat* modifiedVertices;

public:

	RenderedModel() {

		model = nullptr;
		texture = nullptr;
	}

	RenderedModel(Model* model, Texture* texture) {

		this->model = model;
		this->texture = texture;

		glGenVertexArrays(1, &vertexArrayID);
		glBindVertexArray(vertexArrayID);

		glGenBuffers(1, &bufferArrayID);
		glBindBuffer(GL_ARRAY_BUFFER, bufferArrayID);

		glBufferData(GL_ARRAY_BUFFER, model->sizeofModel(), model->getModel(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), NULL);

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_TRUE, 8 * sizeof(GLfloat), (const GLvoid*)(5 * sizeof(GLfloat)));

		glBindVertexArray(0);

//        modifiedVertices = new GLfloat[model->getNbrVertices()];
//
//        int end = (int) (model->sizeofModel() / sizeof(GLfloat));
//        unsigned int pos = 0;
//        GLfloat* modelArray = model->getModel();
//
//        for (int i = 0; i < end; ) {
//
//            for (int j = 0; j < 3; ++j)
//                modifiedVertices[pos++] = modelArray[i++];
//
//            i += 5;
//        }

	}

	void show(bool shadowMAP) {

		if (!shadowMAP) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->getID());
		}

		glBindVertexArray(vertexArrayID);

		glDrawArrays(GL_TRIANGLES, 0, model->getNbrFaces());

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	Texture* getTexture() {

		return texture;
	}
};

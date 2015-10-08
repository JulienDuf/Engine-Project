#pragma once
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "RenderObject3D.h"

class RenderedModel : public RenderObject3D {

private:

	Model* model;
	Shader* shader;
	Texture* texture;

	GLuint vertexArrayID;
	GLuint bufferArrayID;

public:

	RenderedModel() {

		model = nullptr;
		shader = nullptr;
		texture = nullptr;
	}

	RenderedModel(Model* model, Shader* shader, Texture* texture) {

		this->model = model;
		this->texture = texture;
		this->shader = shader;

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
	}

	void show(int w, int h, float* camera) {

		shader->use();

		shader->setUniformMatrix4x4("transform", 1, false, transform);
		shader->setUniformMatrix4x4("camera", 1, false, camera);

		glBindTexture(GL_TEXTURE_2D, texture->getID());
		glBindVertexArray(vertexArrayID);

		glEnable(GL_TEXTURE_2D);

		glDrawArrays(GL_TRIANGLES, 0, model->getNbrFaces());

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		shader->stopUse();
	}

	Texture* getTexture() {

		return texture;
	}

	Shader* getShader() {

		return shader;
	}
};

#pragma once
#include "Texture.h"
#include "Model.h"
#include "Shader.h"
#include "RenderObject3D.h"

struct Light {

	Vector3f position;
	Vector3f intensities;
};

class RenderedModel : public RenderObject3D {

private:

	Model* model;
	Shader* shader;
	Texture* texture;
	Light light;

	GLuint vertexArrayID;
	GLuint bufferArrayID;

public:

	RenderedModel() {

		model = nullptr;
		shader = nullptr;
		texture = nullptr;
	}

	RenderedModel(Model* model, Shader* shader, Texture* texture, Light light) {

		this->model = model;
		this->texture = texture;
		this->shader = shader;
		this->light = light;

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

	void show(int w, int h, float* camera, Vector3f pos) {

		shader->use();

		shader->setUniformMatrix4x4("transform", 1, false, transform);
		shader->setUniformMatrix4x4("camera", 1, false, camera);
		shader->setUniformVector3("light.position", pos);
		shader->setUniformVector3("light.intensities", light.intensities);

		glBindTexture(GL_TEXTURE_2D, texture->getID());
		glBindVertexArray(vertexArrayID);

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

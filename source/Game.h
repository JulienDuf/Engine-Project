#pragma once
#include "Engine.h"
#include "RenderedModel.h"
#include "Button.h"
#include "ScrollBar.h"
#include "Label.h"
#include "TextBox.h"
#include "TextContainer.h"

class Game {

public:

	static void start() {
		
		Engine::createWindow(1366, 768);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

		RenderedModel* model = new RenderedModel(new Model("Ressources/crate.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/crate.png"));
		RenderManager::getInstance().addObject(model);
		model->setPosition(Vector3d(0,0,-1.9));

		//RenderedModel* salle = new RenderedModel(new Model("Ressources/salle.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/salle.png"));
		//salle->setPosition(Vector3d(0,-6,0));

		//RenderManager::getInstance().addObject(salle);

		while (Engine::window->windowState()) {

			Engine::renderAndEvent();
		}
	}
};

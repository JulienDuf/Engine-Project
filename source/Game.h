#pragma once
#include "Engine.h"
#include "RenderedModel.h"
#include "Button.h"
#include "ScrollBar.h"
#include "Label.h"
#include "TextBox.h"
#include "TextContainer.h"
#include "Chrono.h"

class Game {

public:

	static void scene() {

		Scene* scene = new Scene(Engine::isShaderExist("directionalLight", "Ressources/directionalLight.frag", "Ressources/directionalLight.vert"), new ShadowMap(Engine::isShaderExist("shadowMap", "Ressources/shadowMap.frag", "Ressources/shadowMap.vert")), new DirectionalLight(Vector3f(3,5,1), Vector3f(1,1,1), 60, Vector3f(0, -1, 0)));

		RenderedModel* plane = new RenderedModel(new Model("Ressources/plane.obj"), new Texture("Ressources/ceramics.png"));
		plane->setPosition(Vector3d(0, 0.0, 0));

		RenderedModel* tower = new RenderedModel(new Model("Ressources/tower.obj"), new Texture("Ressources/tower.png"));
		tower->setPosition(Vector3d(0, 0.0, 0));

		scene->addObject(plane);
		scene->addObject(tower);

		RenderManager::getInstance().addScene(scene);
	}

	static void start() {

		Engine::createWindow(1920, 1080);

		float frameTime = 0;

        Timer* fpsTimer = new Timer(1);

		Chrono* time = new Chrono();
		time->repartir();

		scene();

		Engine::window->setWindowFullScreen();

        Text* fps = new Text(new TextTexture("INFINITY fps", {255, 255, 255, 255}, Engine::isFontExist("arial25", "Ressources/arial.ttf", 25)), Vector2f(5.0, 5.0));
        RenderManager::getInstance().addObject(fps);
        std::string fpsString;

		while (Engine::window->windowState()) {

			Engine::renderAndEvent();
			frameTime = (float) time->repartir().enSecondes();

            if (fpsTimer->isFinished()) {
                fpsString.clear();

                fpsString += std::to_string((int)(1 / frameTime));
                fpsString += " fps";

                fps->getTexture()->setText(fpsString.c_str());
                fpsTimer->restart();
            }
		}
	}
};

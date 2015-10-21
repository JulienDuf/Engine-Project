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

	static void begin() {

		RenderedModel* salle = new RenderedModel(new Model("Ressources/SalleDebut.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/SalleDebut.png"), {{1,1,1}, {1,1,1}});
		RenderManager::getInstance().addObject(salle);

		RenderedModel* porte = new RenderedModel(new Model("Ressources/portePlate.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/portePlate.png"), {{1,1,1}, {1,1,1}});
		porte->setPosition(Vector3d(4.1, 0, 2.57));
		porte->setRotation(Vector3d(0, 90, 0));
		RenderManager::getInstance().addObject(porte);

		RenderedModel* lit = new RenderedModel(new Model("Ressources/lit.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/lit.png"), {{1,1,1}, {1,1,1}});
		lit->setPosition(Vector3d(2.5, 1.0, -10.9));
		lit->setRotation(Vector3d());
		RenderManager::getInstance().addObject(lit);

		RenderedModel* lavabo = new RenderedModel(new Model("Ressources/lavabo.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/Lavabo.png"), {{1,1,1}, {1,1,1}});
		lavabo->setPosition(Vector3d(5.0, 1.3, -1.5));
		lavabo->setRotation(Vector3d());
		RenderManager::getInstance().addObject(lavabo);

		RenderedModel* bureau = new RenderedModel(new Model("Ressources/bureau.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/bureau.png"), {{1,1,1}, {1,1,1}});
		bureau->setPosition(Vector3d(-4.9, 0.0, -3.0));
		bureau->setRotation(Vector3d(0, -90, 0));
		RenderManager::getInstance().addObject(bureau);

		RenderedModel* poubelle = new RenderedModel(new Model("Ressources/poubelle.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/poubelle.png"), {{1,1,1}, {1,1,1}});
		poubelle->setPosition(Vector3d(-4.3, 0.0, -0.75));
		poubelle->setRotation(Vector3d());
		RenderManager::getInstance().addObject(poubelle);

		RenderedModel* etagere = new RenderedModel(new Model("Ressources/etagere.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/etagere.png"), {{1,1,1}, {1,1,1}});
		etagere->setPosition(Vector3d(-1.7, 0.0, 1.55));
		etagere->setRotation(Vector3d(0, 180, 0));
		RenderManager::getInstance().addObject(etagere);

		RenderedModel* tabledechevet = new RenderedModel(new Model("Ressources/TableDeChevet.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/TableDeChevet.png"), {{1,1,1}, {1,1,1}});
		tabledechevet->setPosition(Vector3d(1.0, 1.0, -10.5));
		tabledechevet->setRotation(Vector3d());
		RenderManager::getInstance().addObject(tabledechevet);

		RenderedModel* masque = new RenderedModel(new Model("Ressources/masqueAGaz.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/masqueAGaz.png"), {{1,1,1}, {1,1,1}});
		masque->setPosition(Vector3d(1.0, 1.82, -10.5));
		masque->setRotation(Vector3d(0, -90 , 0));
		RenderManager::getInstance().addObject(masque);
	}

	static void start() {
		
		Engine::createWindow(1920, 1080);

		//RenderedModel* model = new RenderedModel(new Model("Ressources/avion.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/avion.png"), {{1,1,1}, {1,1,1}});
		//RenderManager::getInstance().addObject(model);
		//model->setPosition(Vector3d(0,0,-1.9));

		//RenderedModel* salle = new RenderedModel(new Model("Ressources/salle.obj"), new Shader("Ressources/defaultFrag.frag", "Ressources/defaultVert.vert"), new Texture("Ressources/salle.png"));
		//salle->setPosition(Vector3d(0,-6,0));

		//RenderManager::getInstance().addObject(salle);

		float angle = 0;
		float degreePerSecond = .01;

		float frameTime = 0;

		Chrono* time = new Chrono();
		time->repartir();

		begin();

		while (Engine::window->windowState()) {

			Engine::renderAndEvent();
			frameTime = time->obtTempsEcoule().enSecondes();
			angle += (degreePerSecond * frameTime);
			//model->setRotation(Vector3d(0, angle, 0));
		}
	}
};

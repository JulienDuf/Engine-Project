#pragma once
#include <iostream>
#include <time.h>
#include <sstream>
#include "Math.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "RessourceManager.h"
#include "TextTexture.h"
#include "Model.h"
#include "Shader.h"
#include "Texture.h"
#include "SocketException.h"

namespace Engine {

	Window* window;
	Server* server;
	ServerClient* client;
	Thread* threads[4];

	void init() {

		SDL_Init(SDL_INIT_VIDEO);
		TTF_Init();
		IMG_Init(IMG_INIT_PNG);
		Mix_Init(MIX_INIT_OGG);
		SDLNet_Init();

		for (int i = 0; i < 4; ++i)
			threads[i] = nullptr;
	}

	void close() {
		SDL_Quit();
		TTF_Quit();
		IMG_Quit();
		Mix_Quit();
		SDLNet_Quit();
	}

	void renderAndEvent() {

		RessourceManager::getInstance().laodRessources();

		EventManager::getInstance().checkEvent();
		window->clearWindow();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		RenderManager::getInstance().render(window->getSize().x, window->getSize().y);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		window->renderWindow();
	}

	void createWindow(unsigned int w, unsigned int h) {

		window = new Window(w, h, "");
		RenderManager::getInstance().init(w, h);

		std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	}

	Font* isFontExist(std::string name, const char* path, int size) {

		Font* font = dynamic_cast<Font*>(RessourceManager::getInstance().getRessource(name));

		if (font == nullptr) {
			font = new Font(path, size);
			RessourceManager::getInstance().addRessource(name, font);
		}
		return font;
	}

	TextTexture* isTextExist(std::string name, const char* text, SDL_Color color, Font* font) {

		TextTexture* texture = dynamic_cast<TextTexture*>(RessourceManager::getInstance().getRessource(name));

		if (texture == nullptr) {
			texture = new TextTexture(text, color, font);
			RessourceManager::getInstance().addRessource(name, texture);
		}
		return texture;
	}

	Shader* isShaderExist(std::string name, const char* fragPath, const char* vertexPath) {

		Shader* shader = dynamic_cast<Shader*>(RessourceManager::getInstance().getRessource(name));

		if (shader == nullptr) {
			shader = new Shader(fragPath, vertexPath);
			RessourceManager::getInstance().addRessource(name, shader);
		}
		return shader;
	}

	void getTextSize(const char* text, Font* font, int &w, int &h) {

		SDL_Surface* surface = TTF_RenderText_Blended(font->getFont(), text, { 0, 0, 0, 255 });
		w = surface->w;
		h = surface->h;
		SDL_FreeSurface(surface);
	}

	/*
	Create a thread if possible.
	*/
	bool createThread(int function(void*), const char* name, void* parameter) {

		for (int i = 0; i < 4; ++i) {
			if (threads[i] == nullptr) {
				threads[i] = new Thread(function, name, parameter);
				return true;
			}
		}
		return false;
	}

	int runServer(void* ptr) {

		while (!server->getShutdownStatus()){

			server->checkForConnections();
			server->checkForActivity();
		}
		return 0;
	}

	int runClient(void* ptr) {

		try {
			client->connectToServer();

			std::string receivedMessage = "";

			// Run the main loop...
			while (!client->getShutdownStatus())
				client->checkForIncomingMessages();

		}
		catch (SocketException e)
		{
			std::cerr << "Caught an exception in the main loop..." << std::endl;
			std::cerr << e.what() << std::endl;
			std::cerr << "Terminating application." << std::endl;
		}

		window->closeWindow();
		return 0;
	}

	/*
	The server will be put on a thread. Only one server per execution...
	*/
	void createServer(void reaction(Server*, ClientInfo), std::string hostName) {

		server = new Server(950035, 512, 5, reaction, hostName);
		createThread(runServer, "server", (void*)NULL);
	}

	/*
	The server will be put on a thread. Only one server per execution...
	*/
	void createClient(std::string serverAddress,void reaction(ServerInfo), std::string clientName) {

		client = new ServerClient(serverAddress, 950035, 512, reaction, clientName);
		createThread(runClient, "client", (void*)NULL);
	}

	template<class T>
	std::string toString(const T& thing) {
		std::ostringstream stream;
		stream << thing;
		return stream.str();
	}

	namespace Physic {


	}
}
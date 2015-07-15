#pragma once
#include "Button.h"
#include "ScrollBar.h"
#include "Label.h"
#include "TextBox.h"
#include "TextContainer.h"

void enter_textBox(Control* sender) {

	TextContainer* container;
	TextBox* textBox = dynamic_cast<TextBox*>(sender);
	std::string message;

	if (Event::keybord.lastKeyUp == KEY_ENTER && Engine::server != nullptr) {

		message.append("You : ");
		message += textBox->getText();
		ServerInfo info;
		info.clientName = Engine::server->getHostName();
		info.message = new std::string(textBox->getText());

		container = dynamic_cast<TextContainer*>(Engine::window->getControl("textContainerChat"));
		container->addText(message);
		Engine::server->sendToClient(info);
		textBox->setText(std::string(" "));
	}

	else if (Event::keybord.lastKeyUp == KEY_ENTER && Engine::server == nullptr){

		ClientInfo info;
		info.name = Engine::client->getClientName();
		info.message = new std::string(textBox->getText());

		Engine::client->sendToServer(info);
		textBox->setText(std::string(" "));
	}
}

void enter_textBoxName(Control* sender) {

	TextBox* tmp;
	Label* name;

	if (Event::keybord.lastKeyUp == KEY_ENTER) {

		tmp = dynamic_cast<TextBox*>(sender);
		name = dynamic_cast<Label*>(Engine::window->getControl("labelName"));

		name->setText(tmp->getText().c_str());
		name->setPosition(Vecteur2f((Engine::window->getSize().x - name->getText()->getTexture()->getSurface()->w) / 2, 160));
		tmp->setText(std::string(" "));
	}
}

void enter_textBoxIP(Control* sender) {

	TextBox* tmp;
	Label* IP;

	if (Event::keybord.lastKeyUp == KEY_ENTER) {

		tmp = dynamic_cast<TextBox*>(sender);
		IP = dynamic_cast<Label*>(Engine::window->getControl("labelIP"));

		IP->setText(tmp->getText().c_str());
		IP->setPosition(Vecteur2f((Engine::window->getSize().x - IP->getText()->getTexture()->getSurface()->w) / 2, 160));
		tmp->setText(std::string(" "));
	}
}

void createRoom() {

	TextBox* box = new TextBox(new Image(new Texture("Ressources/box.png"), Vecteur2f(30, 450)), Engine::isFontExist("arial25", "Ressources/arial.ttf", 25));
	box->addReaction(SDL_KEYUP, enter_textBox);
	Engine::window->addControl("textBoxChat", box);

	TextContainer* texts = new TextContainer(new Image(new Texture("Ressources/textContainer.png"), Vecteur2f(30, 20)), Engine::isFontExist("arial25", "Ressources/arial.ttf", 25));
	Engine::window->addControl("textContainerChat", texts);
}

void serverReaction(Server* server, ClientInfo info) {

	ServerInfo infoOfServer;
	infoOfServer.clientName = info.name;
	infoOfServer.message = info.message;
	std::string message;

	if ((*info.message != QUIT_SIGNAL) && (*info.message != SHUTDOWN_SIGNAL) && (info.name != "New client")) {
		message = info.name;
		message.append(": ");
		message += *info.message;
		TextContainer* container = dynamic_cast<TextContainer*>(Engine::window->getControl("textContainerChat"));
		container->addText(message);
	}

	server->sendToClient(infoOfServer);
}

void clientReaction(ServerInfo info) {

	std::string message;

	if ((*info.message != QUIT_SIGNAL) && (*info.message != SHUTDOWN_SIGNAL) && (info.clientName != "New client")) {
		message = info.clientName;
		message.append(": ");
		message += *info.message;
		TextContainer* container = dynamic_cast<TextContainer*>(Engine::window->getControl("textContainerChat"));
		container->addText(message);
	}
}

void createServer_click(Control* sender) {

	Label* name = dynamic_cast<Label*>(Engine::window->getControl("labelName"));

	Engine::createServer(serverReaction, name->getText()->getTexture()->getText());
	Engine::window->clearControls();
	createRoom();
}

void joinServer_click(Control* sender) {

	Label* name = dynamic_cast<Label*>(Engine::window->getControl("labelName"));
	Label* IP = dynamic_cast<Label*>(Engine::window->getControl("labelIP"));
	
	Engine::createClient(IP->getText()->getTexture()->getText(), clientReaction, name->getText()->getTexture()->getText());
	Engine::window->clearControls();
	createRoom();
	if (Engine::client->getShutdownStatus())
		Engine::window->closeWindow();
}

void createRoom_click(Control* sender) {

	Engine::window->clearControls();

	Label* yourName = new Label(new Text(new TextTexture("Your Name", { 0, 0, 0, 255 }, Engine::isFontExist("arial45", "Ressources/arial.ttf", 45)), Vecteur2f(80, 100)));
	Label* name = new Label(new Text(new TextTexture(" ", { 0, 0, 0, 255 }, Engine::isFontExist("arial35", "Ressources/arial.ttf", 35)), Vecteur2f(50, 160)));
	Engine::window->addControl("labelYourName", yourName);
	Engine::window->addControl("labelName", name);

	TextBox* box = new TextBox(new Image(new Texture("Ressources/box.png"), Vecteur2f(30, 210)), Engine::isFontExist("arial25", "Ressources/arial.ttf", 25));
	box->addReaction(SDL_KEYUP, enter_textBoxName);
	Engine::window->addControl("textBoxName", box);

	Button* create = new Button(Vecteur2f(50, 300), "Create Room", Engine::isFontExist("arial50", "Ressources/arial.ttf", 50), { 0, 0, 0, 255 }, { 215, 55, 110 }, { 0, 0, 0, 255 });
	create->addReaction(SDL_MOUSEBUTTONUP, createServer_click);
	Engine::window->addControl("createServerButton", create);
}

void joinRoom_click(Control* sender) {

	Engine::window->clearControls();

	Label* yourName = new Label(new Text(new TextTexture("Your Name", { 0, 0, 0, 255 }, Engine::isFontExist("arial45", "Ressources/arial.ttf", 45)), Vecteur2f(80, 40)));
	Label* name = new Label(new Text(new TextTexture(" ", { 0, 0, 0, 255 }, Engine::isFontExist("arial35", "Ressources/arial.ttf", 35)), Vecteur2f(50, 100)));
	Engine::window->addControl("labelYourName", yourName);
	Engine::window->addControl("labelName", name);

	TextBox* box = new TextBox(new Image(new Texture("Ressources/box.png"), Vecteur2f(30, 160)), Engine::isFontExist("arial25", "Ressources/arial.ttf", 25));
	box->addReaction(SDL_KEYUP, enter_textBoxName);
	Engine::window->addControl("textBoxName", box);

	Label* serverIP = new Label(new Text(new TextTexture("Server Address", { 0, 0, 0, 255 }, Engine::isFontExist("arial45", "Ressources/arial.ttf", 45)), Vecteur2f(45, 240)));
	Label* IP = new Label(new Text(new TextTexture(" ", { 0, 0, 0, 255 }, Engine::isFontExist("arial35", "Ressources/arial.ttf", 35)), Vecteur2f(50, 300)));
	Engine::window->addControl("labelServerIP", serverIP);
	Engine::window->addControl("labelIP", IP);

	TextBox* boxIP = new TextBox(new Image(new Texture("Ressources/box.png"), Vecteur2f(30, 360)), Engine::isFontExist("arial25", "Ressources/arial.ttf", 25));
	boxIP->addReaction(SDL_KEYUP, enter_textBoxIP);
	Engine::window->addControl("textBoxIP", boxIP);

	Button* create = new Button(Vecteur2f(70, 420), "Join Room", Engine::isFontExist("arial50", "Ressources/arial.ttf", 50), { 0, 0, 0, 255 }, { 215, 55, 110 }, { 0, 0, 0, 255 });
	create->addReaction(SDL_MOUSEBUTTONUP, joinServer_click);
	Engine::window->addControl("joinServerButton", create);
}

class Game {

public:

	static void start() {
		
		Engine::createWindow(400, 500);
		Button* b1 = new Button(Vecteur2f(50, 100), "Create Room", Engine::isFontExist("arial50", "Ressources/arial.ttf", 50), { 0, 0, 0, 255 }, { 215, 55, 110 }, { 0, 0, 0, 255 });
		b1->addReaction(SDL_MOUSEBUTTONUP, createRoom_click);
		Engine::window->addControl("createRoomButton", b1);

		Button* b2 = new Button(Vecteur2f(70, 250), "Join Room", Engine::isFontExist("arial50", "Ressources/arial.ttf", 50), { 0, 0, 0, 255 }, { 215, 55, 110 }, { 0, 0, 0, 255 });
		b2->addReaction(SDL_MOUSEBUTTONUP, joinRoom_click);
		Engine::window->addControl("joinRoomButton", b2);

		while (Engine::window->windowState()) {

			Engine::renderAndEvent();
		}
	}
};

#pragma once

#define QUIT_SIGNAL "/quit"
#define CONNECTION_TIMEOUT_PERIOD 5000
#define SOCKET_SET_POLL_PERIOD 10

class ServerClient {
private:

	unsigned int serverPort;
	unsigned int bufferSize;

	std::string serverHostname;
	IPaddress serverIP;
	std::string clientName;
	TCPsocket clientSocket;

	char* buffer;

	SDLNet_SocketSet socketSet;
	bool shutdownClient;

	void(*newMessageReaction)(ServerInfo);

public:

	ServerClient(std::string serverAddress, unsigned int serverPort, unsigned int bufferSize, void reaction(ServerInfo), std::string name) {

		this->shutdownClient = false;
		this->serverHostname = serverAddress;
		newMessageReaction = reaction;

		this->serverPort = serverPort;
		this->bufferSize = bufferSize;
		clientName = name;

		buffer = new char[bufferSize];
		socketSet = SDLNet_AllocSocketSet(2);
	}

	~ServerClient(){

		SDLNet_TCP_Close(clientSocket);
		SDLNet_FreeSocketSet(socketSet);

		delete[] buffer;
	}

	void connectToServer(){

		int hostResolved = SDLNet_ResolveHost(&serverIP, serverHostname.c_str(), serverPort);
		
		clientSocket = SDLNet_TCP_Open(&serverIP);
		if (clientSocket) {

			SDLNet_TCP_AddSocket(socketSet, clientSocket);
			int activeSockets = SDLNet_CheckSockets(socketSet, CONNECTION_TIMEOUT_PERIOD);

			int gotServerResponse = SDLNet_SocketReady(clientSocket);

			if (gotServerResponse != 0) {

				int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, buffer, bufferSize);
				newMessageReaction(ServerInfo(buffer));
			}
		}
		else {
			shutdownClient = true;
		}
	}

	void checkForIncomingMessages(){

		ServerInfo info;
		int activeSockets = SDLNet_CheckSockets(socketSet, SOCKET_SET_POLL_PERIOD);

		if (activeSockets != 0) {

			int gotMessage = SDLNet_SocketReady(clientSocket);

			if (gotMessage != 0) {
				int serverResponseByteCount = SDLNet_TCP_Recv(clientSocket, buffer, bufferSize);

				if (serverResponseByteCount != 0) {
					info = ServerInfo(buffer);

					if (*info.message == SHUTDOWN_SIGNAL)
						shutdownClient = true;
					else
						newMessageReaction(info);
				}
			}
		}
	}

	void sendToServer(ClientInfo info) {

		std::string str;
		info.convertToString(str);
		const char* message = str.c_str();

		unsigned int msgLength = strlen(message) + 1;

		SDLNet_TCP_Send(clientSocket, (void *)message, msgLength);
	}

	bool getShutdownStatus() {
		return shutdownClient;
	}

	std::string getClientName() {
		return clientName;
	}
};
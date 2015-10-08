
#if defined(__APPLE__) && defined(__MACH__)
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2/SDL_opengl.h>
#elif defined _WIN32
#pragma comment ( lib,"opengl32.lib")
#pragma comment ( lib,"SDL2main.lib")
#pragma comment ( lib,"SDL2.lib")
#pragma comment ( lib,"SDL2_image.lib")
#pragma comment ( lib,"SDL2_ttf.lib")
#pragma comment ( lib,"SDL2_mixer.lib")
#pragma comment ( lib,"SDL2_net.lib")
#pragma comment ( lib,"glew32.lib")
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#include <GL\glew.h>
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#include <SDL2\SDL_net.h>
#elif defined __linux__
#define GL3_PROTOTYPES 1
#include <GL3/gl3.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_net.h>
#endif

#include <algorithm>
#include "Server.h"
#include "ServerClient.h"
#include "Thread.h"
#include "Engine.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Engine::init();
	Game::start();
	Engine::close();
	return 0;
}

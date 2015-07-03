
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
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")
#pragma comment(linker, "/NODEFAULTLIB:msvcrt.lib")
#include <GL\glew.h>
#include <SDL2\SDL_opengl.h>
#include <SDL2\SDL.h>
#include <SDL2\SDL_image.h>
#include <SDL2\SDL_ttf.h>
#include <SDL2\SDL_mixer.h>
#endif

#include "Engine.h"
#include "Game.h"

int main(int argc, char* argv[]) {

	srand(time(NULL));

	Engine::init();
	Game::start();
	Engine::close();
	return 0;
}
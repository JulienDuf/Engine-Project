#pragma once
#include "Vecteur2.h"
#include "Ressource.h"
#include <string>

class Texture : public Ressource{
protected:
	SDL_Surface* surface;
	GLuint ID;
public:

	Texture() {
		surface = nullptr;
		glGenTextures(1, &ID);
	}

	Texture(const char* path) {
		glGenTextures(1, &ID);
		load(path);
	}

	Texture(SDL_Surface* surface) {
		this->surface = surface;
		glGenTextures(1, &ID);
		load();
	}

	~Texture() {
		if (surface != nullptr){
			if (surface->format != nullptr)
				SDL_FreeSurface(surface);
			surface = nullptr;
			glDeleteTextures(1, &ID);
		}
	}

	bool load(const char* path){
		surface = IMG_Load(path);
		return load();
	}

	bool load() {
		if (surface != nullptr){
			glBindTexture(GL_TEXTURE_2D, ID);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

#if defined(__APPLE__) && defined(__MACH__)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE, surface->pixels);
#elif defined _WIN32 || defined(__linux__)
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
#endif
		}
		return (surface != nullptr);
	}

	void changeSurface(SDL_Surface* surface) {
		this->surface = surface;
		load();
	}

	GLuint getID(){
		return ID;
	}

	Vecteur2d getSize() {
		return Vecteur2d(surface->w, surface->h);
	}

	SDL_Surface* getSurface() {
		return surface;
	}

};
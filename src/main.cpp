#include "stdafx.h"
#include "PhongException.h"
#include "Phong.h"

int main(int argc, char **argv) {
	try {
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Animacao POC Versao 0.1");

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando SDL");
		if (SDL_Init(SDL_INIT_VIDEO) != 0) {
			std::ostringstream ss;
			ss << "Falha ao inicializar SDL : [" << SDL_GetError() << "]";
			throw PhongException(ss.str());
		}

		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando SDL/IMG");
		int imgFlags = IMG_INIT_PNG;
		if (IMG_Init(imgFlags) != imgFlags) {
			std::ostringstream ss;
			ss << "Falha ao inicializar SDL/IMG: [" << IMG_GetError() << "]";
			throw PhongException(ss.str());
		}

		Phong phong(640, 480);
		phong.init();
		phong.run();
	} catch (PhongException &e) {
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", e.what());
	}

	IMG_Quit();
	SDL_Quit();

	SDL_Delay(5000);

	return 0;
}

#pragma once

#include "stdafx.h"
#include "Sprite.h"

class Phong {
public:
	Phong(int windowWidth, int windowHeight);
	void init();
	void run();

private:
	void _drawBorders();

	int _windowWidth;
	int _windowHeight;

	SDL_Window *_window;
	SDL_Renderer *_renderer;

	bool _finish;

	Sprite _wall;
	Sprite _corner;
};

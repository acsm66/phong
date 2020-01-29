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
	void _drawPlayers();
	void _drawBall();

	int _windowWidth;
	int _windowHeight;

	SDL_Window *_window;
	SDL_Renderer *_renderer;

	bool _finish;

	Sprite _wall;
	Sprite _corner;
	Sprite _player;
	Sprite _ball;

	SDL_Point _gameAreaMin;
	SDL_Point _gameAreaMax;
};

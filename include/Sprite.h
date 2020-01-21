#pragma once

#include "stdafx.h"

class Sprite {
public:
	Sprite();
	virtual ~Sprite();

	void init(SDL_Renderer *renderer, const std::string &path);
	void render(int x, int y, double angle, SDL_RendererFlip flip);

	inline const int getWidth() const { return _width; }
	inline const int getHeight() const { return _height; }

private:
	SDL_Renderer *_renderer;
	SDL_Texture *_texture;

	int _width;
	int _height;
};

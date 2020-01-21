#include "stdafx.h"
#include "PhongException.h"
#include "Sprite.h"

Sprite::Sprite() : _renderer(NULL), _texture(NULL), _width(0), _height(0) {}

Sprite::~Sprite() {
	// nao destroi renderer pois eh so uma referencia
	if (_texture != NULL) {
		SDL_DestroyTexture(_texture);
	}
}

void Sprite::init(SDL_Renderer *renderer, const std::string &path) {
	if (renderer == NULL) {
		throw PhongException("Renderizador invalido");
	}
	_renderer = renderer;

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Carregando textura no arquivo: [%s]", path.c_str());
	_texture = IMG_LoadTexture(renderer, path.c_str());
	if (_texture == NULL) {
		std::ostringstream ss;
		ss << "Falha ao carregar textura: [" << IMG_GetError() << "]";
		throw PhongException(ss.str());
	}

	SDL_QueryTexture(_texture, NULL, NULL, &_width, &_height);
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Tamanho da textura: [%d x %d]", _width, _height);
}

void Sprite::render(int x, int y, double angle, SDL_RendererFlip flip) {
	SDL_Rect dstRect = { x, y, getWidth(), getHeight() };
	SDL_Point center = { 0, 0 };
	if (SDL_RenderCopyEx(_renderer, _texture, NULL, &dstRect, angle, &center, flip) != 0) {
		std::ostringstream ss;
		ss << "Falha ao carregar renderizar textura: [" << SDL_GetError() << "]";
		throw PhongException(ss.str());
	}
}

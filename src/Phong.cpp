#include "stdafx.h"
#include "FrameTimer.h"
#include "PhongException.h"
#include "Phong.h"

Phong::Phong(int windowWidth, int windowHeight) : _windowWidth(windowWidth), _windowHeight(windowHeight),
	_window(NULL), _renderer(NULL), _finish(false), _wall(), _corner() {}

void Phong::init() {
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando janela");
	_window = SDL_CreateWindow("Phong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _windowWidth, _windowHeight,
		SDL_WINDOW_SHOWN);
	if (_window == NULL) {
		std::ostringstream ss;
		ss << "Falha ao criar janela: [" << SDL_GetError() << "]";
		throw PhongException(ss.str());
	}

	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Inicializando renderizador");
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	if (_renderer == NULL) {
		std::ostringstream ss;
		ss << "Falha ao criar renderizador: [" << SDL_GetError() << "]";
		throw PhongException(ss.str());
	}

	_wall.init(_renderer, "resources/wall.png");
	_corner.init(_renderer, "resources/corner.png");
	_player.init(_renderer, "resources/player.png");
	_ball.init(_renderer, "resources/ball.png");

	_gameAreaMin.x = _gameAreaMin.y = _wall.getWidth();
	_gameAreaMax.x = _windowWidth - _wall.getWidth();
	_gameAreaMax.y = _windowHeight - _wall.getWidth();
}

void Phong::run() {
	SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Iniciando loop de execucao");

	SDL_ShowWindow(_window);

	SDL_Event event;
	FrameTimer timer(60);
	while (!_finish) {
		try {
			SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0);
			SDL_RenderClear(_renderer);

			_drawBorders();
			_drawPlayers();
			_drawBall();

			if (SDL_PollEvent(&event) != 0) {
				switch (event.type) {
					case SDL_QUIT:
						_finish = true;
						break;
				}
			}

			SDL_RenderPresent(_renderer);
			timer.waitNextFrame();
		}
		catch (PhongException &e) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erro no loop de execucao: [%s]", e.what());
			_finish = true;
		}
	}
}

void Phong::_drawBorders() {
	int wallWidth = _wall.getWidth();
	int wallHeight = _wall.getHeight();

	// teto
	_wall.render(0, wallWidth, 270, SDL_FLIP_NONE);
	_wall.render(wallHeight, wallWidth, 270, SDL_FLIP_NONE);
	_wall.render((wallHeight * 2), wallWidth, 270, SDL_FLIP_NONE);
	_wall.render((wallHeight * 3), wallWidth, 270, SDL_FLIP_NONE);

	// piso
	int floorY = (wallHeight * 3);
	_wall.render(0, floorY, 270, SDL_FLIP_HORIZONTAL);
	_wall.render(wallHeight, floorY, 270, SDL_FLIP_HORIZONTAL);
	_wall.render((wallHeight * 2), floorY, 270, SDL_FLIP_HORIZONTAL);
	_wall.render((wallHeight * 3), floorY, 270, SDL_FLIP_HORIZONTAL);

	// parede esquerda
	_wall.render(0, 0, 0, SDL_FLIP_HORIZONTAL);
	_wall.render(0, wallHeight, 0, SDL_FLIP_HORIZONTAL);
	_wall.render(0, (wallHeight * 2), 0, SDL_FLIP_HORIZONTAL);

	// parede direita
	int wallRightX = _windowWidth - wallWidth;
	_wall.render(wallRightX, 0, 0, SDL_FLIP_NONE);
	_wall.render(wallRightX, wallHeight, 0, SDL_FLIP_NONE);
	_wall.render(wallRightX, (wallHeight * 2), 0, SDL_FLIP_NONE);

	int cornerWidth = _corner.getWidth();
	int cornerHeight = _corner.getHeight();

	// quinas
	int cornerRightX = _windowWidth - cornerWidth;
	int cornerBottomY = _windowHeight - cornerHeight;
	SDL_RendererFlip flipBoth = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	_corner.render(0, 0, 0, SDL_FLIP_NONE);
	_corner.render(0, cornerBottomY, 0, SDL_FLIP_VERTICAL);
	_corner.render(cornerRightX, 0, 0, SDL_FLIP_HORIZONTAL);
	_corner.render(cornerRightX, cornerBottomY, 0, flipBoth);
}

void Phong::_drawPlayers() {
	const int p1X = _gameAreaMin.x + 50;
	const int p2X = _gameAreaMax.x - 50 - _player.getWidth();
	const int centerY = (_gameAreaMax.y - _gameAreaMin.y) / 2;
	const int playerCenterY = _player.getHeight() / 2;

	_player.render(p1X, (centerY - playerCenterY), 0, SDL_FLIP_NONE);
	_player.render(p2X, (centerY - playerCenterY), 0, SDL_FLIP_NONE);
}

void Phong::_drawBall() {
	const int centerX = (_gameAreaMax.x - _gameAreaMin.x) / 2;
	const int centerY = (_gameAreaMax.y - _gameAreaMin.y) / 2;
	const int ballCenterX = _ball.getWidth() / 2;
	const int ballCenterY = _ball.getHeight() / 2;

	_ball.render((centerX - ballCenterX), (centerY - ballCenterY), 0, SDL_FLIP_NONE);
}

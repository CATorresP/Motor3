#pragma once

#include <SDL/SDL.h>
#include <GL/eglew.h>
#include <iostream>
#include <stdexcept>

#include "Sprite.h"
#include "GLS_Program.h"
#include "ErrorManager.h"
enum class GameState {
	PLAY, EXIT
};
enum INIT_ERROR {
	SDL_SUBSYSTEM_INIT_ERROR,
	SDL_GL_WINDOWS_ERROR,
	SDL_GL_CONTEXT_ERROR,
	GL_EXTENTION_LOAD_ERROR,

};

class MainGame {
	Sprite sprite;
	int width;
	int height;
	SDL_Window* window;
	GLS_Program program;
	float time;
	float move;
	GLuint timeLocation;
	GLuint moveLocation;

public:
	GameState gameState;

private:
	int init();
	void initShaders();
	void processInput();
public:
	MainGame();
	~MainGame();
	void run();
	void draw();
	void update();
};
#include "MainGame.h"


MainGame::MainGame() : time(0), move(0)
{
	window = nullptr;
	width = 800;
	height = 600;
	gameState = GameState::PLAY;
}

MainGame::~MainGame()
{
	SDL_Quit();
}


int MainGame::init()
{
	// Inicializar todos los subsistemas de SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		//throw std::runtime_error("Error al inicializar SDL");
		ErrorManager::handleError("Error al iniciar SDL.");
		return 1;
	}

	// Crear una ventana optimizada para OpenGL
	window = SDL_CreateWindow(
		"GAMEa",				// título
		SDL_WINDOWPOS_CENTERED, // posición de referencia x
		SDL_WINDOWPOS_CENTERED, // posición de referencia y
		width,					// largo
		height,					// alto
		SDL_WINDOW_OPENGL		// Flags de configuración
	);
	if (window == NULL) {
		ErrorManager::handleSDLError(SDL_GetError());
		SDL_Quit();
		return 2;
	}

	// Crear un contexto OpenGL 
	SDL_GLContext glContext = SDL_GL_CreateContext(window);
	if (glContext == NULL) {
		ErrorManager::handleSDLError(SDL_GetError());
		SDL_Quit();
		return 3;
	}

	// Cargar extensiones de OpenGL
	GLenum error = glewInit();
	if (error != GLEW_OK) {
		// Validar el estado del Glew
		return 4;
	}
	// Configurar atributo de buffer doble como verdadero (1)
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Color establecido tras borrado del buffer
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Profundidad establecido tras borrado del buffer
	glClearDepth(1.0);
	// Iniciarlizar shaders
	initShaders();
}

void MainGame::processInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) 
	{
		switch (event.type)
		{
		case SDL_QUIT:
			gameState = GameState::EXIT;
			break;
		case SDL_MOUSEMOTION:
			std::cout << "Posición X: " << event.motion.x <<
				" Y: " << event.motion.y << std::endl;
			break;
		}
	}
}

void MainGame::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	program.use();
	glUniform1f(timeLocation, time);
	glUniform1f(moveLocation, move);
	sprite.draw();
	program.unuse();
	SDL_GL_SwapWindow(window);
	move = 0;
	time += 0.0002;
	if (int(time) % 2 == 0) {
		move = 1;
	}
}

void MainGame::update()
{
	while (gameState != GameState::EXIT) 
	{
		processInput();
		draw();
	}
}

void MainGame::run()
{
	init();
	sprite.init(-1, -1, 1, 1);
	update();
}

void MainGame::initShaders()
{
	program.compileShaders(
		"Shaders/colorShaderVert.txt",
		"Shaders/colorShaderFrag.txt"
	);
	program.addAttribute("vertexPosition");
	program.addAttribute("vertexColor");
	program.linkShader();
	timeLocation = program.getUniformLocation("time");
	moveLocation = program.getUniformLocation("move");

}




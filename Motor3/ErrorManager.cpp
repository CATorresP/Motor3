#include "ErrorManager.h"

void ErrorManager::handleError(const char* message)
{
	std::cerr << "Error: " << message << std::endl;
}

void ErrorManager::handleSDLError(const char* message)
{
	std::cerr << "SDL Error: " << message << std::endl;
	SDL_ClearError();
}

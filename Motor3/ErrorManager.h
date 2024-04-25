#pragma once
#include <iostream>
#include <SDL/SDL.h>

class ErrorManager 
{
public:
	static void handleError(const char* message);
	static void handleSDLError(const char* message);
};
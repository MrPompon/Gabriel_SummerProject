// main.cpp

#include "stdafx.h"
#include "Engine.hpp"

int main(int argc, char* argv[])
{
	spaceshooter::Engine engine;
	if (engine.Initialize())
		engine.Run();
	engine.Shutdown();
	return 0;
}

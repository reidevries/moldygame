#include <raylib.h>
#include "gameworld.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const int screen_w = 1280;	//size of viewport in pixels
	const int screen_h = 720;
	
	char* debugenv = getenv("MOLDDEBUG");
	bool debug = false;
	if (debugenv != NULL) {
		if (strncmp(debugenv, "true", 4) == 0) {
			debug = true;
			std::cout << "DEBUG MODE ON" << std::endl;
		}
	}
	
    InitWindow(screen_w, screen_h, "moldygame");
    GameWorld gameworld(screen_w, screen_h, debug);
    SetTargetFPS(60);
	
    while (!WindowShouldClose()) {
		gameworld.render(GetFrameTime());
    }
    
    CloseWindow();              // Close window and OpenGL context

    return 0;
}

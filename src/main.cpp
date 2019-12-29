#include <raylib.h>
#include "gameworld.h"

int main(void)
{
    const int screenwidth = 1280;	//size of viewport in pixels
	const int screenheight = 720;

    InitWindow(screenwidth, screenheight, "raylib [texture] example - image text drawing");
    GameWorld* gameworld = new GameWorld(screenwidth, screenheight);
	SetTargetFPS(60);
	
    while (!WindowShouldClose()) {
		gameworld->render();
    }

    delete gameworld;
    
    CloseWindow();              // Close window and OpenGL context

    return 0;
}

#include "gameworld.h"
#include "blobobject.h"

GameWorld::GameWorld(int screenwidth, int screenheight) {
	this->screenwidth = screenwidth;
	this->screenheight = screenheight;
	screenscale = screenheight/WORLDHEIGHT;
	worldwidth = WORLDHEIGHT*(screenwidth/screenheight);


	font = LoadFontEx("font/Andika/Andika-R.ttf", int(6*screenscale), 0, 0);
	
	Image parrots = LoadImage("texture/fairy/wink.png");
	texturebuffer.emplace_back(LoadTextureFromImage(parrots));
	UnloadImage(parrots);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM
	
	VectorFan* v = new VectorFan((Vector2){20,20}, 7, 5);
	BlobObject* b = new BlobObject(*v, 1, screenscale);
	gameobjectbuffer.push_back(b);
}

void GameWorld::render() {
	BeginDrawing();

	ClearBackground(RAYWHITE);
	for (std::vector<GameObject*>::iterator it = gameobjectbuffer.begin(); it != gameobjectbuffer.end(); it++) {
		(*it)->draw();
	}
	
	for (std::vector<TextureSprite>::iterator it = uitexturebuffer.begin(); it != uitexturebuffer.end(); it++) {
		it->draw((Vector2){ (float)(worldwidth/2 - 20), (float)(WORLDHEIGHT/2 - 20)});
	}

	// Draw text directly using sprite font
	DrawTextEx(font, "hellooo popyp", (Vector2){ 2, 30}, (float)font.baseSize, 0.0f, BLACK);

	EndDrawing();
}

GameWorld::~GameWorld() {
	gameobjectbuffer.clear();
	UnloadFont(font);           // Unload custom spritefont
}

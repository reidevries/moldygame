#include "gameworld.h"
#include "blobobject.h"
#include <sstream>
#include <iostream>

GameWorld::GameWorld(int screen_w, int screen_h, bool debug) {
	this->debug = debug;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	screen_scale = screen_h/WORLD_H;
	world_w = WORLD_H*(screen_w/screen_h);

	level_loader = LevelLoader(0);
	font = LoadFontEx("font/Andika/Andika-R.ttf", int(6*screen_scale), 0, 0);
	
	Polygon v((Vector2){20,20}, 7, 5);
	object_buf.emplace_back(new BlobObject(v, 1, screen_scale));
	if (debug) std::cout << "i am happy" << std::endl;
}

void GameWorld::update(float dt) {
	for (auto&& object : object_buf) {
		object->update(level_loader.getCurrentLevel(), dt);
	}
}

void GameWorld::render(float dt) {
	BeginDrawing();
	
	ClearBackground(RAYWHITE);
	for (auto&& object : object_buf) {
		object->draw();
	}
	
	for (auto ui : ui_buf) {
		ui.draw((Vector2){ static_cast<float>(world_w/2 - 20), static_cast<float>(WORLD_H/2 - 20)});
	}

	if (debug) {
		level_loader.getCurrentLevel()->debugRenderFood(screen_scale);
		
		std::stringstream debugtxt;
		debugtxt << "Debug text " << dt;
		// Draw text directly using sprite font
		DrawTextEx(font, debugtxt.str().c_str(), (Vector2){ 2, 30}, static_cast<float>(font.baseSize), 0.0f, BLACK);
	}

	EndDrawing();
}

GameWorld::~GameWorld() {
	object_buf.clear();
	UnloadFont(font);           // Unload custom spritefont
}

#include "ILevel.h"
#include <raylib.h>

const int screenWidth = 1920;
const int screenHeight = 1080;


void FRender (Camera3D camera) {
	Image image = LoadImage("src/res/menu.png");	
	Texture2D bg = LoadTextureFromImage(image);
	UnloadImage(image);
	DrawTexture(bg, screenWidth/2 - bg.width/2, screenHeight/2 - bg.height/2, WHITE);
	DrawText("press space to connect", screenWidth / 2 - MeasureText("press space to connect", 32) / 2, 3 * screenHeight / 4, 40, WHITE);
}

void menu (Camera3D camera) {
	ILevel menu;
	menu.n = 0;
	menu.render = FRender;
	menu.render(camera);
}

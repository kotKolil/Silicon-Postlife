#include "Scene.h"
#include <stddef.h>
#include <raylib.h>
#include <stdint.h>

const int screenWidth = 1920;
const int screenHeight = 1080;

static Font customFont;
static bool FontLoaded = false;


void  MRender (uint8_t *levelN, Camera3D *cam) {
	if (!FontLoaded) {
		customFont = LoadFontEx("./res/fonts/ShareTechMono-Regular/ShareTechMono-Regular.ttf", 32, NULL, 0);
		FontLoaded = true;
	}
    ClearBackground(BLACK);
	DrawText("press space to connect", screenWidth / 2 - MeasureText("press space to connect", GetScreenHeight()/35) / 2, 3 * screenHeight / 4, 40, WHITE);
	SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
	DrawTextEx(customFont, "Silicon Postlife", (Vector2){GetScreenWidth()/16, GetScreenHeight()/2}, 100, 2.0f, GREEN);
	if ( IsKeyPressed(KEY_SPACE) )  {
		(*levelN)++; 
	}
}

Scene menu =  { 
	.n = 0,
	.render = MRender,
};

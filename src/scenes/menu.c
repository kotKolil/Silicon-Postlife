#include "Scene.h"
#include <stddef.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>


int screenTextDelta(char text[], int font_size, bool dim);
    
void MRender(int *levelN, Camera3D *cam) {
    const char* menu[] = {
        "start",
        "options",
        "quit"
    };

	static int option = 1;
    ClearBackground(BLACK);
    
    int font_size = (GetScreenHeight() >> 4) - 11;
    if (font_size < 10) font_size = 10;

    DrawText(
        "Silicon Postlife",
        screenTextDelta("Silicon Postlife", font_size << 2, true) >> 1,
        screenTextDelta("Silicon Postlife", font_size << 2, false) >> 1,
        font_size << 2,
        GREEN
    );

    int startX = GetScreenWidth() / 6;
    int startY = (screenTextDelta("start", font_size, true) >> 3) + (GetScreenHeight() >> 1);
    int spacing = 50 + (50 >> 2);

    int num_options = sizeof(menu) / sizeof(menu[0]);

    for (int i = 0; i < num_options; i++) {
        DrawText(menu[i], startX, startY + (spacing * i), font_size, GREEN);
    }

	DrawText(">", startX - (font_size << 1), startY + (spacing * (option - 1)), font_size, GREEN);

    if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        if (option == 1) {
            (*levelN)++;
        }
        else if (option == 2) {
        	//enter here number of options scene
        }
        else if (option == 3) {
        	CloseWindow();
        }
    }
	if (IsKeyPressed(KEY_UP))   option--;
	if (IsKeyPressed(KEY_DOWN)) option++;
	
	if (option < 1) option = 3;
	if (option > 3) option = 1;
}

__attribute__((visibility("default"))) Scene menu =  { 
	.n = 0,
	.render = MRender,	
};

int screenTextDelta(char text[], int font_size, bool dim) {
	// if dim true -> width, tho  height
	// 1 function better 2
	int delta;
	if (dim) {
		delta = GetScreenWidth() - MeasureText( text, font_size);
		return delta;
	}
	else {
		delta = GetScreenHeight() - font_size;
		return delta;
	}
}

	



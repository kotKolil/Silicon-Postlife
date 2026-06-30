#include "Scene.h"
#include <stddef.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>


int screenTextDelta(char text[], int font_size, bool dim);

void  MRender (int *levelN, Camera3D *cam) {
    ClearBackground(BLACK);
	DrawText(
		"Silicon Postlife",
			screenTextDelta("Silicon Postlife", 100, true) / 2,
				screenTextDelta("Silicon Postlife", 100, false) / 2,
						100,
							GREEN
								);

	int startX = GetScreenWidth() / 6;
	int startY = (screenTextDelta("start", 50, false) / 2) + startY;

	int optionsX = 100;
	int optionsY = startY + 120; 
	int quitX = 100;

	int quitY = optionsY + 120;
	DrawText("start", startX, startY, 50, GREEN);
	DrawRectangleLines(
	    startX - 30, 
	    startY - 15, 
	    MeasureText("start", 50) + 60, 
	    90, 
	    RED
	);


	DrawText("options", startX, startY + 200, 50, GREEN);
	DrawRectangleLines(
	    startX - 30, 
	    startY - 185, 
	    MeasureText("options", 50) + 60, 
	    90, 
	    RED
	);

	DrawText("quit", startX, startY + 300, 50, GREEN);
	DrawRectangleLines(
	    startX - 30, 
	    startY - 285, 
	    MeasureText("quit", 50) + 60, 
	    90, 
	    RED
	);

	
	if ( IsKeyPressed(KEY_SPACE) )  {
		(*levelN)++; 
	}
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

	



#include "raylib.h"
#include "string.h"
#include "stdio.h"

#include "actor.h"

void scan_char(int *levelCurrent, Camera3D *camera, actor *player) {
	static char code[5] = "\0";
	char currentChar = GetCharPressed();	
	while  (currentChar > 0) {
		if (currentChar >= 32 && currentChar <= 172) {
			memmove(code, code + 1, 3);
			code[3] = (char)currentChar;
			code[4] = '\0';

			//checking codes
				//jmp  NeXT level
			if (strcmp(code, "next") == 0) {
				(*levelCurrent)++;
				code[0] = 0;
			}
		}
		currentChar = GetCharPressed();
	}
}

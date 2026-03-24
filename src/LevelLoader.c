#include <stdint.h>
#include <stdio.h>
#include <raylib.h>
#include "menu.h"

void LoadLevel(uint8_t *n, Camera3D camera) {
	printf("loading level %d\n", n);
	switch (*n) {
		case 0:
			printf("menu");
			menu(&camera);
		default:
			printf("loading normal level");
	}
}

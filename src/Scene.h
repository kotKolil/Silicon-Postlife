#pragma once
#include <stdint.h>

typedef struct Camera3D Camera3D;


typedef struct {
	int n;
	void (*render)(uint8_t *levelCurrent, Camera3D *cam);
	char name[64];
} Scene;

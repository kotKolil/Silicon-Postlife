#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "Scene.h"
#include <string.h>
#include <dlfcn.h>

static const int  levelMax = 7;

Scene *scenes = NULL;

void LoadLevel(int *levelCurrent, Camera3D *camera) {
    printf("loading level %d\n", *levelCurrent);
	scenes[*levelCurrent].render( levelCurrent, camera);
}


void InitLevels() {
	FILE *f = fopen("scenes/scenes.inf","r");
	if (!f) {
		printf("error, scenes.inf not found\n");
	 	return;
	 }
	
	char name[64];
	int id = 0;
	int LevelsN = 0;
	char path[256] = "scenes/";
	
	while (  fscanf(f, "%s %d",name, &id ) == 2 ) {
		LevelsN ++;
		Scene *temp = realloc(scenes, LevelsN * sizeof(Scene));
		if (temp != NULL) {
			scenes = temp;
			strncpy(scenes[LevelsN - 1].name, name, sizeof(scenes[LevelsN - 1].name) - 1);
			snprintf(path, sizeof(path), "scenes/%s.so", name); 
			void* handle = dlopen(path, RTLD_LAZY);
			printf("loading binary lib \n");		
			if (!handle) {
				printf("Failed to load Scene: %s\n", dlerror());
				return;
			}
			Scene * temp_scene = dlsym(handle, scenes[LevelsN - 1].name);
			printf("loading level %s\n", name);
			if (temp_scene != NULL) {
				scenes[LevelsN - 1].n = temp_scene->n;
				scenes[LevelsN - 1].render = temp_scene->render;
				printf("Loaded Scene %s, Id %d \n", name, temp_scene->n);
			}
			else {
				printf("failed to load level\n");
			}
		}
	}
}

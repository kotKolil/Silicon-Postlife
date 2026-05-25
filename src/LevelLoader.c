#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>
#include "Scene.h"
#include <string.h>
#include <dlfcn.h>

static const uint8_t levelMax = 7;

Scene *scenes = NULL;

void LoadLevel(uint8_t *levelCurrent, Camera3D *camera) {
    printf("loading level %d\n", *levelCurrent);    
	int temp = 0;
	while ( scenes[temp].n != *levelCurrent && temp < sizeof(*scenes)/sizeof(Scene) ) {
		temp++;
	}
	if (temp == sizeof(*scenes)/sizeof(Scene) ) {
		return;
	}
	char path[256]; 
	snprintf(path, sizeof(path), "bin/scenes/%s.so", scenes[temp].name);
	void* handle = dlopen(path, RTLD_LAZY);
	if (!handle) {
		    printf("Failed to load library: %s\n", dlerror());
		    return;
		}
	Scene temp_scene = dlsym(handle, scenes[temp].name);
	if (level) {
	    temp_scene->render; // ЗАПУСКАЕМ!
	}
}


void InitLevels() {
	FILE *f = fopen("./bin/scenes/scenes.inf","r");
	if (!f) {
		printf("error, scenes.inf not found\n");
	 	return;
	 }
	
	char name[64];
	int id = 0;
	int LevelsN = 0;
	
	while (  fscanf(f, "%s %d",name, &id ) == 2 ) {
		LevelsN ++;
		Scene *temp = realloc(scenes, LevelsN * sizeof(Scene));
		if (temp != NULL) {
			scenes = temp;
			strncpy(scenes[LevelsN - 1].name, name, sizeof(scenes[0].name) - 1);
			scenes[LevelsN - 1].name[sizeof(scenes[0].name) - 1] = '\0';
			scenes[LevelsN - 1].n = id;
			printf("loaded %s\n", name);
		}
	}
}

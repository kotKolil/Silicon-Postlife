#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "Scene.h"
#include "c_cam_upd.h"

void testRender(uint8_t *levelN, Camera3D *cam) {
	BeginMode3D(*cam);
	ClearBackground(BLACK);
    Camera2D camera2d = { 0 };
    camera2d.target = (Vector2){ 0.0f, 0.0f };      // Точка, на которую смотрит камера
    camera2d.offset = (Vector2){ 1920/2, 1080/2 };  // Центрируем камеру на экране 1920x1080
    camera2d.rotation = 0.0f;                       // Угол поворота
    camera2d.zoom = 1.0f; 
    
    for (int i = -24; i < 24; i += 1) {
        DrawLine3D(
            (Vector3){i, 0, -24},
            (Vector3){i, 0, 24},
            GREEN
        );  
    }
    
    for (int i = -24; i < 24; i += 1) {
        DrawLine3D(
            (Vector3){-24, 0, i},
            (Vector3){24, 0, i},
            GREEN                   
        );
    }
    
    EndMode3D();
    BeginMode2D(camera2d);
    
    char str[20];
    sprintf(str, "%d", GetFPS());
    DrawText(str, 20, 20, 10, GREEN);
	EndMode2D();
}

Scene test = {
	.n = 2,
	.render = testRender,
};

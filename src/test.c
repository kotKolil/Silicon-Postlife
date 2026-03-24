#include <raylib.h>
#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include "ILevel.h"
#include "c_cam_upd.h"

void RenderTest(Camera3D camera) {
    BeginMode3D(camera);
    
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
    
    char str[20];
    sprintf(str, "%d", GetFPS());
    DrawText(str, 20, 20, 10, GREEN);
}

void test(Camera3D camera) {
    ILevel menu;
    menu.render = RenderTest;
    
    if (menu.render != NULL) {
        menu.render(camera);
    }
}

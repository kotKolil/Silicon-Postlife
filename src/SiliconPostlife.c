/*
 * Silicon Postlife
 * Copyright (C) 2026  treska <ldxi1991@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include "c_cam_upd.h"
#include "ILevel.h"
#include "LevelLoader.h"

#define T_FPS 60
#define C_FOV 45.0f
#define CAMERA_SENSITIVITY 0.5
#define CAMERA_SPEED 0.5
#define MAP_H 24
#define MAP_W 24

#define KEY_FORWARD KEY_W
#define KEY_BACK KEY_S
#define KEY_LEFT KEY_A
#define KEY_RIGHT KEY_D
#define KEY_UP KEY_SPACE
#define KEY_DOWN KEY_LEFT_SHIFT




int main(void)
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;
	uint8_t currentLevel = 0;
	uint8_t lastLevel = 0;

    InitWindow(screenWidth, screenHeight, "Silicon Postlife");
	SetWindowState(FLAG_FULLSCREEN_MODE);
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 2.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = C_FOV;
    camera.projection = CAMERA_PERSPECTIVE;
    DisableCursor();
    SetTargetFPS(T_FPS);
    while (!WindowShouldClose())
    {
        CustomCameraUpdate(&camera);
        BeginDrawing();
        if (currentLevel != lastLevel || currentLevel == 00 ) {
     		LoadLevel(&currentLevel, camera);		
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

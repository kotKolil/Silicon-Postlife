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
#include "c_cam_upd.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

// game settings

#define T_FPS 60
#define C_FOV 45.0f
#define CAMERA_SENSITIVITY 0.5
#define CAMERA_SPEED 0.5
#define MAP_H 24
#define MAP_W 24

// bindings
#define KEY_FORWARD KEY_W
#define KEY_BACK KEY_S
#define KEY_LEFT KEY_A
#define KEY_RIGHT KEY_D
#define KEY_UP KEY_SPACE
#define KEY_DOWN KEY_LEFT_SHIFT




int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Silicon Postlife");

    // Define the camera to look into our 3d world
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 2.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = C_FOV;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    DisableCursor();                    // Limit cursor to relative movement inside the window

    SetTargetFPS(T_FPS);             // Set game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------




    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        CustomCameraUpdate(&camera);

        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

            BeginMode3D(camera);

				//drawing x lines
				for (int i = -MAP_H; i < MAP_H; i += 1) {
					DrawLine3D(
						(Vector3){i, 0, -MAP_H},
						(Vector3){i, 0, MAP_H},
						GREEN
					);	
				}
                //drawing y lines
                for (int i = -MAP_W;i < MAP_W; i += 1) {
                	DrawLine3D(
						(Vector3){MAP_W, 0, i},
						(Vector3){-MAP_W, 0, i},
						GREEN               		
                	);
                }
            EndMode3D();
            char str[20];
            sprintf(str, "%d", GetFPS());
            DrawText( str, 20, 20, 10, GREEN );
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

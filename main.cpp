#include <iostream>
#include <cmath>
#include "Camera.hpp"
#include "Player.hpp"

const int screenWidth = 1920;
const int screenHeight = 1080;

char modelFileName[128] = "mytest.m3d";

Model model;
ModelAnimation current;
ModelAnimation *anims;
CameraManager camManager((Vector3){ 10.0f, 12.5f, 10.0f }, (Vector3){ 0.0f, 0.0f, 0.0f },
                        (Vector3){ 0.0f, 3.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);
Player localplayer((Vector3){ 0.0f, 0.0f, 0.0f }, 0.1f);


void UpdateGame()
{
    camManager.zoomControl();

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        camManager.rayCasting(localplayer.characterPosition, &(localplayer.targetPoint), &(localplayer.moveDirection));

        localplayer.setAnimation(RUNNING);
        localplayer.rotateToDirection();
    }

    localplayer.moveCharacter();
}

void DrawGame()
{
    BeginDrawing();
    ClearBackground(RAYWHITE);
    BeginMode3D(camManager.camera);
    DrawGrid(10, 1.0f);
    EndMode3D();
    DrawFPS(10, 10);
    EndDrawing();
}

int main()
{
    InitWindow(screenWidth, screenHeight, "Isometric Camera Example");
    
    localplayer.loadMesh(modelFileName);
    SetTargetFPS(55);                   

    while (!WindowShouldClose())
    {
        UpdateGame();
        if(localplayer.animsCount)
        {
            localplayer.animFrameCounter++;
            if(localplayer.animFrameCounter >= localplayer.current.frameCount)
            {
                localplayer.animFrameCounter = 0;
            }
            UpdateModelAnimation(localplayer.model, localplayer.current, localplayer.animFrameCounter);
            localplayer.animPlaying = true;
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camManager.camera);

        if(localplayer.drawMesh)
        { 
            DrawModel(localplayer.model, localplayer.characterPosition, 1.0f, WHITE);
        }
        
        DrawGrid(10, 1.0f);         
        EndMode3D();
        EndDrawing();
    }
    
    CloseWindow();
    
    return 0;
}

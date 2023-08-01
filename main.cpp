#include <iostream>
#include <cmath>
#include "Camera.hpp"

const int screenWidth = 1920;
const int screenHeight = 1080;

Vector3 characterPosition = { 0.0f, 0.0f, 0.0f };
Vector3 moveDirection = characterPosition;
Vector3 targetPoint = characterPosition;
float x_dist, z_dist = 0.0f;
float yawAngle = 0.0f;
const float characterSpeed = 0.1f;

const float cameraSpeed = 0.5f;
const float cameraZoomSpeed = 1.25f;
const float cameraMinZoom = 0.01;
const float cameraMaxZoom = 2.5f;
char modelFileName[128] = "mytest.m3d";

Model model;
ModelAnimation current;
ModelAnimation *anims;
CameraManager camManager((Vector3){ 10.0f, 12.5f, 10.0f }, (Vector3){ 0.0f, 0.0f, 0.0f },
                        (Vector3){ 0.0f, 3.0f, 0.0f }, 45.0f, CAMERA_PERSPECTIVE);


void UpdateGame()
{
    camManager.zoomControl();

    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        camManager.rayCasting(characterPosition, &targetPoint, &moveDirection);

        current = anims[1];
        yawAngle = atan2f(moveDirection.x, moveDirection.z);
        model.transform = MatrixRotateY(yawAngle);
    }
    x_dist = std::abs(characterPosition.x - targetPoint.x);
    z_dist = std::abs(characterPosition.z - targetPoint.z);

    if(!(x_dist < 0.05 && z_dist < 0.05))
    {
        characterPosition = Vector3Add(characterPosition, Vector3Scale(moveDirection, characterSpeed));
        moveDirection = Vector3Normalize(Vector3Subtract(targetPoint, characterPosition));

        model.transform = MatrixRotateY(yawAngle);

        TraceLog(LOG_INFO, "Target Position: %.2f, %.2f, %.2f", targetPoint.x, targetPoint.y, targetPoint.z);
        TraceLog(LOG_INFO, "Atual: %.2f, %.2f, %.2f", characterPosition.x, characterPosition.y, characterPosition.z);
        TraceLog(LOG_INFO, "Diference: %.2f, %.2f, %.2f", x_dist, targetPoint.y, z_dist);
    }
    else
    {
        characterPosition = targetPoint;
        current = anims[2];
    }
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
    bool drawMesh = 1;
    bool drawSkeleton = 1;
    bool animPlaying = false;   // Store anim state, what to draw
    unsigned int animsCount = 0;
    int animFrameCounter = 0, animId = 0;
        


    char modelFileName[128] = "mytest.m3d";
    model = LoadModel(modelFileName); 
    anims = LoadModelAnimations(modelFileName, &animsCount); 
    current = anims[2];

    SetTargetFPS(55);                   


    while (!WindowShouldClose())
    {
        UpdateGame();
        if (animsCount)
        {
            animFrameCounter++;
            if(animFrameCounter >= current.frameCount) animFrameCounter = 0;
            
            UpdateModelAnimation(model, current, animFrameCounter);
            animPlaying = true;
        }
            BeginDrawing();

                ClearBackground(RAYWHITE);

                BeginMode3D(camManager.camera);

                    if (drawMesh) DrawModel(model, characterPosition, 1.0f, WHITE);

                    DrawGrid(10, 1.0f);         

                EndMode3D();

            EndDrawing();
        }

    CloseWindow();

    return 0;
}

#include "Camera.hpp"

CameraManager::CameraManager(Vector3 camPosition, Vector3 target, Vector3 up,
                            float fovy, int camProjection)
{
    camera.position = camPosition, camera.target = target;
    camera.up = up, camera.fovy = fovy, camera.projection = camProjection;
}

void CameraManager::zoomControl()
{
    mouseScroll = GetMouseWheelMove() * cameraZoomSpeed;
    camera.fovy -= mouseScroll;

    if (camera.fovy < 1.0f) camera.fovy = 1.0f;
    if (camera.fovy > 45.0f) camera.fovy = 45.0f;
}

void CameraManager::rayCasting(Vector3 characterPosition, Vector3 *targetPoint, Vector3 *moveDiretion)
{
    this->ray = GetMouseRay(GetMousePosition(), camera);
    float t = -camera.position.y / ray.direction.y;
    *targetPoint = Vector3Add(camera.position, Vector3Scale(this->ray.direction, t));
    *moveDiretion = Vector3Normalize(Vector3Subtract(*targetPoint, characterPosition));
}
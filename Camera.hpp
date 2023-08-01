#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <raylib.h>
#include <raymath.h>

class CameraManager
{
    public:

        Camera3D camera;
        CameraManager(Vector3 camPosition, Vector3 target, Vector3 up,
                      float fovy, int camProjection);
        void zoomControl();
        void rayCasting(Vector3 characterPosition, Vector3 *targetPoint, Vector3 *moveDiretion);

    private:
        const float cameraSpeed = 0.5f;
        const float cameraZoomSpeed = 1.25f;
        const float cameraMinZoom = 0.01;
        const float cameraMaxZoom = 2.5f;
        float mouseScroll;
        Ray ray;

};

#endif
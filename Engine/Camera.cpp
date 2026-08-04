#include "Camera.h"

Camera::Camera() {
    position = { 2.0f, 0.0f, -2.0f };
    target   = { 0.0f, 0.0f, 0.0f };
    up       = { 0.0f, 1.0f, 0.0f };
}

void Camera::Move(float x, float y, float z) {
    position.x += x;
    position.y += y;
    position.z += z;
}

XMMATRIX Camera::GetViewMatrix() {
    return XMMatrixLookAtLH(
        XMLoadFloat3(&position), 
        XMLoadFloat3(&target), 
        XMLoadFloat3(&up)
    );
}

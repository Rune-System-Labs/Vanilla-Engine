#pragma once
#include <DirectXMath.h>

using namespace DirectX;

class Camera {
public:
    Camera();
    void Move(float x, float y, float z);
    XMMATRIX GetViewMatrix();

private:
    XMFLOAT3 position;
    XMFLOAT3 target;
    XMFLOAT3 up;
};

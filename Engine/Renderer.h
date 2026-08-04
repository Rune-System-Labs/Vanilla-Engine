#pragma once

#include "Camera.h"

class Graphics;
class Shader;
class Texture;

class Renderer final {
public:
    Renderer(const Graphics& graphics, const Shader& shader, const Texture& texture);

    void ClearScreen(float red, float green, float blue) const;
    void RenderEntity();
    void Present() const;

private:
    void UpdateTransforms();

    const Graphics& graphics_;
    const Shader& shader_;
    const Texture& texture_;
    Camera camera_;
    float rotation_ = 0.0f;
};

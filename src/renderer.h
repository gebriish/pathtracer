#pragma once
#include "geometry.h"
#include "image.h"
#include "ray.h"
#include <cstddef>

struct Camera
{
  float fov;

  vec3 position;
  vec3 lookat;
  vec3 up;
};

class Renderer
{
public:
	Renderer();
	~Renderer();
  
  void createRenderTarget(int width, int height);
  void clearRenderTarget();
  void deleteRenderTarget();

  void renderScene(const Scene& scene, const Camera& camera);

  Image* getRenderTarget();

private:
  struct {
    int width, height;
  } m_Resolution;

	Image* m_RenderTarget = nullptr;
  Image* m_DepthBuffer = nullptr;

  int SAMPLES = 512;
};

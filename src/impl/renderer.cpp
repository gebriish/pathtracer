#include "../renderer.h"
#include "../pt_utils.h"
#include <cmath>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
  deleteRenderTarget();
}

vec3 sample_square() {
  return vec3(random_float() - 0.5, random_float() - 0.5, 0);
}

void Renderer::createRenderTarget(int width, int height)
{
  m_Resolution.width = width;
  m_Resolution.height = height;
  m_RenderTarget = image_allocate(width, height, 3);
}

void Renderer::clearRenderTarget()
{
  if(!m_RenderTarget) return;

  for(int y=0; y<m_Resolution.height; ++y)
  {
    for(int x=0; x<m_Resolution.width; ++x)
    {
      PixelHandle pixel = image_get_pixel_handle(m_RenderTarget,
          x, y);
      image_pixel_write(pixel, 0, 0);
      image_pixel_write(pixel, 1, 0);
      image_pixel_write(pixel, 2, 0);
    }
  }
}

vec3 get_ray_direction(int x, int y, int width, int height, float fov)
{ 
  vec3 offset = sample_square();
  float pixel_x = x + offset.x();
  float pixel_y = y + offset.y();

  float x_component = (pixel_x / width) * 2.0 - 1.0;
  float y_component = 1.0 - (pixel_y / height) * 2.0;

  return vec3(x_component, y_component, 1/std::tan(fov/2.0));
}

vec3 ray_color(const Scene& scene, const ray& r, int depth) {
  if (depth <= 0)
    return vec3(0,0,0);

  HitRecord rec;

  if(scene.hit(r, 0.01f, 1000, rec))
  {
    const auto& material = scene.getMaterial(rec.materialIndex);

    if(material.type == MaterialType::EMISSION)
      return vec3(3,3,3);

    vec3 direction = normalize(random_unit_vector() + rec.normal);
    return  0.9 * ray_color(scene, ray(rec.point, direction), depth - 1);
  }

  vec3 unit_direction = normalize(r.direction());
  auto a = 0.5*(unit_direction.y() + 1.0);
  return (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
}

void Renderer::renderScene(const Scene& scene, const Camera& camera)
{
  vec3 camera_forward = normalize(camera.lookat - camera.position);
  vec3 camera_right = normalize(cross(camera_forward, camera.up));
  vec3 camera_up = normalize(cross(camera_right, camera_forward));

  const float aspect_ratio = (float) m_Resolution.width / m_Resolution.height;

  const float fov_radian = degrees_to_radians(camera.fov);

  for(int y=0; y<m_Resolution.height; ++y)
  {
    std::clog << "\rScanlines remaining: " << (m_Resolution.height - y) << ' ' << std::flush;

    for(int x=0; x<m_Resolution.width; ++x)
    {
      vec3 color(0, 0, 0);
      for(int i=0; i<SAMPLES; i++)
      {
        vec3 local_ray_direction = get_ray_direction(x, y, m_Resolution.width, m_Resolution.height, fov_radian);
        vec3 ray_direction = normalize(camera_forward * local_ray_direction.z() + 
            camera_right * local_ray_direction.x() * aspect_ratio + 
            camera_up * local_ray_direction.y());
        ray rd(camera.position, ray_direction);

        color += ray_color(scene, rd, 4);
      }
      color /= (float) SAMPLES;


      PixelHandle pixel = image_get_pixel_handle(m_RenderTarget,
          x, y);
      image_pixel_write(pixel, 0, color[0]);
      image_pixel_write(pixel, 1, color[1]);
      image_pixel_write(pixel, 2, color[2]);
    }
  }

  std::cout << "\n\rDone!\n";
}

void Renderer::deleteRenderTarget()
{
  image_free(m_RenderTarget);
}

Image* Renderer::getRenderTarget() 
{
  return m_RenderTarget;
}

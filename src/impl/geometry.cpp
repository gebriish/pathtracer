#include "../geometry.h"


bool hit_triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, 
    const ray& r, float t_min, float t_max, HitRecord& rec) 
{
  vec3 edge1 = v1.position - v0.position;
  vec3 edge2 = v2.position - v0.position;

  vec3 h = cross(r.direction(), edge2);
  float a = dot(edge1, h);

  if (fabs(a) < 1e-8) return false;

  float f = 1.0 / a;
  vec3 s = r.origin() - v0.position;
  float u = f * dot(s, h);

  // Check if u is outside the triangle
  if (u < 0.0 || u > 1.0) return false;

  vec3 q = cross(s, edge1);
  float v = f * dot(r.direction(), q);

  // Check if v is outside the triangle
  if (v < 0.0 || u + v > 1.0) return false;

  // Compute the intersection point along the ray
  float t = f * dot(edge2, q);

  // Check if t is within the acceptable range
  if (t < t_min || t > t_max) return false;

  // Populate the hit record
  rec.t = t;
  rec.point = r.at(t); // Compute the hit point

  float w = 1.0f - u - v; // Barycentric coordinate for v0

  rec.normal = normalize(w * v0.normal + u * v1.normal + v * v2.normal);

  return true;
}

bool Scene::hit(const ray& ray, float ray_tmin, float ray_tmax, HitRecord& record) const 
{
  HitRecord tempRecord;
  bool hitAnything = false;
  float closest_so_far = ray_tmax;

  for(int j=0; j<meshes.size(); ++j) {
    const auto& mesh = meshes[j];
    for (int i=mesh.triangleBegin; i<mesh.numTriangles + mesh.triangleBegin; i++) {
      const auto& tri  = triangles[i];
      const Vertex& v0 = vertices[tri.i0];
      const Vertex& v1 = vertices[tri.i1];
      const Vertex& v2 = vertices[tri.i2];

      if (hit_triangle(v0, v1, v2, ray, ray_tmin, closest_so_far, tempRecord)) {
        hitAnything = true;
        closest_so_far = tempRecord.t;
        record = tempRecord;
        record.materialIndex = mesh.materialIndex;
      }
    }
  }

  return hitAnything;
}

int Scene::addVertex(const Vertex& v)
{
  vertices.push_back(v);
  return vertices.size() - 1;
}

void Scene::addTriangle(const Triangle& t)
{
  triangles.push_back(t);
}

void Scene::addMesh(const Mesh& mesh)
{
  meshes.push_back(mesh);
}

void Scene::addMaterial(const Material& mat)
{
  materials.push_back(mat);
}

void Scene::clear()
{
  materials.clear();
  meshes.clear();
  triangles.clear();
  vertices.clear();
}

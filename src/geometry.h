#pragma once
#include <vector>
#include "ray.h"
#include "vec3.h"
#include "material.h"

struct HitRecord
{
  vec3 point;
  vec3 normal;
  float t;
  int materialIndex;
};

struct Vertex
{
  vec3 position;
  vec3 normal;
};

struct Triangle
{
  unsigned int i0, i1, i2;
};

struct Mesh
{
  int triangleBegin;
  int numTriangles;
  int materialIndex;
};

struct Scene
{
public:
  bool hit(const ray& r, float ray_tmin, 
      float ray_tmax, HitRecord& record) const;

  int addVertex(const Vertex& v);
  void addTriangle(const Triangle& t);
  void addMesh(const Mesh& mesh);
  void addMaterial(const Material& mat);

  void clear();

  inline const Material& getMaterial(int index) const { return materials[index]; }

  inline int numTriangles() const { return triangles.size(); }
  inline int numVertices() const { return vertices.size(); }
  inline int numMaterials() const { return materials.size(); }
  inline int numMeshes() const { return meshes.size(); }

private:
  std::vector<Vertex> vertices;
  std::vector<Triangle> triangles;
  std::vector<Mesh> meshes;
  std::vector<Material> materials;
};


bool hit_triangle(const Vertex& v0, const Vertex& v1, const Vertex& v2, 
    const ray& r, float t_min, float t_max, HitRecord& rec);

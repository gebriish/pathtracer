#include "geometry.h"
#include "material.h"
#include "renderer.h"
#include "io.h"
#include "vec3.h"
#include <fstream>
#include <sstream>
#include <string>


void loadObj(const char* path, Scene& scene, int materialIndex)
{
  std::ifstream input_file(path);
  if (!input_file.is_open())
  {
    std::cout << "Failed to load .obj\n";
    return;
  }

  int trianglesBegin = scene.numTriangles();

  std::string line;
  std::vector<vec3> vertices;
  std::vector<vec3> normals;
  std::vector<vec3> texCoords;

  int vertex_index = scene.numVertices();

  while (std::getline(input_file, line))
  {
    std::istringstream stream(line);
    std::string prefix;
    stream >> prefix;

    if (prefix == "v")
    {
      vec3 vertex;
      stream >> vertex[0] >> vertex[1] >> vertex[2];
      vertices.push_back(vertex);
    }
    else if (prefix == "vn")
    {
      vec3 normal;
      stream >> normal[0] >> normal[1] >> normal[2];
      normals.push_back(normal);
    }
    else if (prefix == "vt") // Texture coordinate
    {
      vec3 texCoord;
      stream >> texCoord[0] >> texCoord[1];
      texCoords.push_back(texCoord);
    }
    else if (prefix == "f") // Face
    {
      std::string vertexData;
      Triangle triangle;

      for (int i = 0; i < 3; ++i)
      {
        stream >> vertexData;

        std::istringstream vertexStream(vertexData);
        std::string index;
        int posIndex, texIndex = 0, normIndex = 0;

        if (std::getline(vertexStream, index, '/')) posIndex = std::stoi(index) - 1;
        if (std::getline(vertexStream, index, '/')) texIndex = std::stoi(index) - 1;
        if (std::getline(vertexStream, index)) normIndex = std::stoi(index) - 1;

        scene.addVertex(Vertex{vertices[posIndex],
            normIndex >= 0 ? normals[normIndex] : vec3(0.0f, 0.0f, 1.0f)});
      }

      triangle.i0 = vertex_index;
      triangle.i1 = vertex_index + 1;
      triangle.i2 = vertex_index + 2;

      vertex_index += 3;

      scene.addTriangle(triangle);
    }
  }

  scene.addMesh(Mesh{trianglesBegin, scene.numTriangles() - trianglesBegin, materialIndex});

  input_file.close();
}

int main() {
  Renderer rndr;

  Scene scene;

  scene.addMaterial(Material{MaterialType::DIFFUSE});
  scene.addMaterial(Material{MaterialType::EMISSION});

  loadObj("res/torus.obj", scene, 1);
  loadObj("res/icosphere.obj", scene, 0);

  Camera renderCamera;
  renderCamera.fov = 45.0;
  renderCamera.position = {0, 0, 2};
  renderCamera.lookat = {0, 0, 0};
  renderCamera.up = {0, 1, 0};

  rndr.createRenderTarget(640, 400);
  rndr.renderScene(scene, renderCamera);

  io_image_write("output.png", rndr.getRenderTarget());
}

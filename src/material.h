#pragma once

enum class MaterialType
{
  DIFFUSE,
  EMISSION
};

struct Material {
  MaterialType type;
};

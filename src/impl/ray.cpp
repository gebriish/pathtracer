#include "../ray.h"

ray::ray(const vec3& origin, const vec3& direction)
	: m_Direction(direction), m_Origin(origin)
{
}

vec3 ray::at(float t) const
{
	return m_Origin + m_Direction * t;
}

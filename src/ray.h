#pragma once
#include "vec3.h"

struct ray
{
public:
 	ray();
	ray(const vec3& origin, const vec3& direction);

	const vec3& origin() const { return m_Origin; } 
	const vec3& direction() const { return m_Direction; } 

	vec3 at(float t) const;

private:
	vec3 m_Origin;
	vec3 m_Direction;
};

#ifndef RAY_HPP
#define RAY_HPP
#include "vec3.hpp"

inline bool refract(const vec3& v , const vec3& n , float ni_over_nt , vec3& refracted) {
	vec3 uv = unit_vector(v);
	float dt = dot(uv , n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1.0 - dt*dt);
	if(discriminant > 0) {
		refracted = ni_over_nt*(uv - dt*n) - sqrt(discriminant)*n;
		return true;
	}
	else
	    return false;
}

float schlick(float cosine , float ref_idx) {
	float r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 = r0*r0;
	return r0 + (1-r0)*pow((1-cosine) , 5);
}

class ray
{
public:
  vec3 _origin;
  vec3 _direction;
  ray() {}
  ray(const vec3 &origin, const vec3 &direction) : _origin(origin), _direction(direction) {}
  vec3 origin() const { return _origin; }
  vec3 direction() const { return _direction; }
  vec3 point_at_parameter(float t) const
  {
    return _origin + _direction * t;
  }
};

#endif
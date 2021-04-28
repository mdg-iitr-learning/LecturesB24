#ifndef RAYH
#define RAYH
#include "vec3.h"

class ray
{
	public:
		ray() {}
	    ray(const vec3& a , const vec3& b) {A = a ; B = b;}
    	vec3 origion() const {return A;}
    	vec3 direction() const {return B;}
    	vec3 point_at_parameter(float t) const {return A + t*B;}

    	vec3 A;
	    vec3 B;
};
inline vec3 reflect(const vec3& v , const vec3& n ) {
	return v -2*dot(v,n)*n;
}

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

#endif
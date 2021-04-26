#ifndef CAMERAH
#define CAMERAH

#include "ray.h"

class camera {
	public:
		camera(){
			bottom_left_corner = vec3(-2.0 , -1.0 , -1.0);
			x_motion = vec3(4.0 , 0.0 , 0.0);
			y_motion = vec3(0.0 , 2.0 , 0.0);
			origin = vec3(0.0 , 0.0 , 0.0);
		}
		
		ray get_ray(float u , float v) {
			return ray(origin , bottom_left_corner + u*x_motion + v*y_motion - origin);
		}
		
		vec3 origin;
		vec3 bottom_left_corner;
		vec3 x_motion;
		vec3 y_motion;
};

#endif

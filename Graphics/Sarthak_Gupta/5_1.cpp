#include<fstream>
#include "ray.h"

float hit_sphere(const vec3& center , float radius , const ray& r)
{
    vec3 oc = r.origion() - center;
	float a = dot(r.direction() , r.direction());
	float b = 2.0 * dot(oc , r.direction());
	float c = dot(oc , oc) - radius*radius;
	float discriminant = b*b - 4.0*a*c;
	if (discriminant < 0) {
		return -1.0;
	}
	else return (-b - sqrt(discriminant)) / (2.0*a);
}

vec3 color(const ray& r){
	float t = hit_sphere(vec3(0.0 , 0.0 , -1.0) , 0.5 , r);
	if(t > 0.0){
		vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0.0 , 0.0 , -1.0));
		return 0.5*vec3(N.x() + 1 , N.y() + 1 , N.z() + 1);
	}
	
	vec3 unit_direction = unit_vector(r.direction());
	float yd = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - yd)*vec3(1.0 , 1.0 , 1.0) + yd*vec3(0.5 , 0.7 , 1.0);
}

int main(){
	int npx = 200;
	int npy = 100;
	ofstream ofs("Fifth.ppm" , ios::out | ios::app);
	ofs << "P3\n" << npx << " " << npy << "\n255" <<endl;
	vec3 bottom_left_corner(-2.0 , -1.0 , -1.0);
	vec3 x_motion(4.0 , 0.0 , 0.0);
	vec3 y_motion(0.0 , 2.0 , 0.0);
	vec3 origin(0.0 , 0.0 , 0.0);
	
	for(int j = npy-1 ; j >= 0 ; j--)
	{
		for(int i = 0 ; i < npx ; i++)
		{
			float u = float(i)/float(npx);
			float v = float(j)/float(npy);
			ray r(origin , bottom_left_corner + u*x_motion + v*y_motion);
			vec3 col = color(r).toColor();
			ofs << col.e[0] << " " << col.e[1] << " " << col.e[2] << endl;
		}
	}
	
	ofs.close();
}

/* we added a normal vector and assigned color acc to it so as to get some shading! */

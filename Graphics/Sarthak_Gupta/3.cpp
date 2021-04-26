#include<fstream>
#include "ray.h"

vec3 color(const ray& r){
	vec3 unit_direction = unit_vector(r.direction());
	float yd = 0.5*(unit_direction.y() + 1.0);
//	float xd = 0.5*(unit_direction.x() + 1.0);
//	return (1-yd-xd)*vec3(1.0 , 0.4 , 0.8) + yd*vec3(1.0 , 0.5 , 0.2);
    return (1.0 - yd)*vec3(1.0 , 1.0 , 1.0) + yd*vec3(0.5 , 0.7 , 1.0);
}

int main(){
	int npx = 200;
	int npy = 100;
	ofstream ofs("Third.ppm" , ios::out | ios::app);
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

/* Made use of ray and uderstood how to use eye/camera and how to move form point to point using ray
also addeda function to ray.h to suit my use case scenario
*/

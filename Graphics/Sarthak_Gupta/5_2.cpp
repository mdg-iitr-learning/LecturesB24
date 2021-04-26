#include<fstream>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"

vec3 color(const ray& r , hitable *world){
	hit_record rec;
	if( world->hit(r , 0.0 , FLT_MAX , rec)) {
		return 0.5*vec3(rec.normal.x() +1 , rec.normal.y() +1 , rec.normal.z() +1 );
	}
	else{
		vec3 unit_direction = unit_vector(r.direction());
	    float yd = 0.5*(unit_direction.y() + 1.0);
	    return (1.0 - yd)*vec3(1.0 , 1.0 , 1.0) + yd*vec3(0.5 , 0.7 , 1.0);
	}
}

int main() {
	int npx = 200;
	int npy = 100;
	ofstream ofs("Fifth-final.ppm" , ios::out | ios::app);
	ofs << "P3\n" << npx << " " << npy << "\n255" <<endl;
	vec3 bottom_left_corner(-2.0 , -1.0 , -1.0);
	vec3 x_motion(4.0 , 0.0 , 0.0);
	vec3 y_motion(0.0 , 2.0 , 0.0);
	vec3 origin(0.0 , 0.0 , 0.0);
	hitable *list[2];
	list[0] = new sphere(vec3(0 , 0 , -1) , 0.5);
	list[1] = new sphere(vec3(0 , -100.5 , -1) , 100);
	hitable *world = new hitable_list(list , 2);
	
	for(int j = npy-1 ; j >= 0 ; j--)
	{
		for(int i = 0 ; i < npx ; i++)
		{
			float u = float(i)/float(npx);
			float v = float(j)/float(npy);
			ray r(origin , bottom_left_corner + u*x_motion + v*y_motion);
			
			vec3 col = color(r,world).toColor();
			ofs << col.e[0] << " " << col.e[1] << " " << col.e[2] << endl;
	    }
	}
}

/*created hitable class, hitable list class, sphere classs and used them to have an image showing two spheres using the concepts of OOP! */

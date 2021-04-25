#include<fstream>
#include<stdlib.h>

#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"

vec3 random_in_unit_sphere() {
	vec3 p;
	do{
		p = 2.0*vec3(float(rand() % 1000) / float(1000), float(rand() % 1000) / float(1000) , float(rand() % 1000) / float(1000)) - vec3(1,1,1);
	} while (p.square_length() >= 1.0);
	return p;
}

vec3 color(const ray& r , hitable *world){
	hit_record rec;
	if( world->hit(r , 0.0 , FLT_MAX , rec)) {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color( ray(rec.p , target-rec.p) , world ); 
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
	int ns = 100;
	ofstream ofs("Seventh2.ppm" , ios::out | ios::app);
	ofs << "P3\n" << npx << " " << npy << "\n255" <<endl;

	hitable *list[2];
	list[0] = new sphere(vec3(0 , 0 , -1) , 0.5);
	list[1] = new sphere(vec3(0 , -100.5 , -1) , 100);
	hitable *world = new hitable_list(list , 2);
	camera cam;
	
	for(int j = npy-1 ; j >= 0 ; j--)
	{
		for(int i = 0 ; i < npx ; i++)
		{
			vec3 col(0 , 0 , 0);
			for(int s = 0; s < ns; s++){
				float x_s = float(rand() % 1000) / float(1000);
				float y_s = float(rand() % 1000) / float(1000);
//				cout<< x_s << " " << y_s << endl;
				float u = float(i + x_s)/ float(npx);
				float v = float(j + y_s)/ float(npy);
				ray r = cam.get_ray(u,v);
				col += color(r,world);
			}
			col /= float(ns);
			col = vec3( sqrt(col[0]) , sqrt(col[1]) , sqrt(col[2]));
			col = col.toColor();
			ofs << col.e[0] << " " << col.e[1] << " " << col.e[2] << endl;
	    }
	}
}

/* implement gamma2 correction*/

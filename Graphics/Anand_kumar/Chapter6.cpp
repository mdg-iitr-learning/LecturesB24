#include<iostream>
#include<fstream>
#include<float.h>
#include"material.h"

using namespace std;

vec3 color(const ray &r , hitable *world){
    hit_record rec;
    if(world -> hit(r, 0.0 , FLT_MAX , rec)){
        return 0.5*vec3(rec.normal.x() + 1 , rec.normal.y() + 1 , rec.normal.z() + 1);
    }
    else{
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5*(unit_direction.y() + 1.0);
        return (1.0-t)*vec3(1.0 , 1.0 , 1.0) + t*vec3(0.5 , 0.7 , 1.0);
    }
}

int main(){
    int x = 200;
    int y = 100;
    int s = 100;
    ofstream ostream;
    ostream.open("Chapter6.ppm");
    ostream << "P3\n" << x << " " << y << "\n255\n";
    hitable *list[2];
    list[0] = new sphere(vec3(0,0,-1) , 0.5 , new lambertian(vec3(0.8,0.6,0.8)));
    list[1] = new sphere(vec3(0,-100.5 ,-1) , 100 ,  new lambertian(vec3(0.8,0.6,0.8)));
    hitable *world = new hitable_list(list,2);
    camera cam;
    for(int j = y-1 ; j >= 0 ; j--){
        for(int i = 0 ; i < x ; i++){
            vec3 colors(0,0,0);
            for(int k = 0 ; k < s ; k++){
                float u = float(i + ((double)rand()/(RAND_MAX)))/float(x);
                float v = float(j + ((double)rand()/(RAND_MAX)))/float(y);
                ray r = cam.get_ray(u,v);
                colors = colors + color(r,world);
            }
            colors = colors / float(s);
            int ir = int(255.99*colors[0]);
            int ig = int(255.99*colors[1]);
            int ib = int(255.99*colors[2]);

            ostream << ir << " " << ig << " " << ib << "\n";
        }
    }
    ostream.close();
    return 0;
}
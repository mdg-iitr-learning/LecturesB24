#include<iostream>
#include<fstream>
#include<float.h>
#include"material.h"
using namespace std;

vec3 color(const ray &r , hitable *world , int depth){
    hit_record rec;
    if(world -> hit(r, 0.001 , FLT_MAX , rec)){
        ray scattered;
        vec3 attenuation;
        if(depth < 50 && rec.mat_ptr->scatter(r , rec , attenuation , scattered)){
            return attenuation*color(scattered , world , depth+1);
        }
        else{
            return vec3(0,0,0);
        }
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
    ostream.open("Chapter9.ppm");
    ostream << "P3\n" << x << " " << y << "\n255\n";
    hitable *list[5];
    list[0] = new sphere(vec3(0,0,-1) , 0.5 , new lambertian(vec3(0.8 , 0.3 , 0.3)));
    list[1] = new sphere(vec3(0,-100.5 ,-1) , 100 , new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1) , 0.5 , new metal(vec3(0.8,0.6,0.2) , 0.3));
    list[3] = new sphere(vec3(-1,0,-1) , 0.5 , new dielectric(1.5));
    list[4] = new sphere(vec3(-1,0,-1) , -0.45 , new dielectric(1.5));
    hitable *world = new hitable_list(list,5);
    camera cam;
    for(int j = y-1 ; j >= 0 ; j--){
        for(int i = 0 ; i < x ; i++){
            vec3 colors(0,0,0);
            for(int k = 0 ; k < s ; k++){
                float u = float(i + ((double)rand()/(RAND_MAX)))/float(x);
                float v = float(j + ((double)rand()/(RAND_MAX)))/float(y);
                ray r = cam.get_ray(u,v);
                colors = colors + color(r,world, 0);
            }
            colors = colors / float(s);
            colors = vec3( sqrt(colors[0]) , sqrt(colors[1]) , sqrt(colors[2]));
            int ir = int(255.99*colors[0]);
            int ig = int(255.99*colors[1]);
            int ib = int(255.99*colors[2]);

            ostream << ir << " " << ig << " " << ib << "\n";
        }
    }
    ostream.close();
    return 0;
}
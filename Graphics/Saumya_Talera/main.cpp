#include <iostream>
#include <bits/stdc++.h>
#include "sphere.h"
#include "hitable_list.h"
#include "float.h"
#include "camera.h"
#include "lodepng.h"
#include "material.h"
using namespace std;

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
    LodePNGColorType colorType = LCT_RGB;
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height,colorType);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}


vec3 color(const ray& r, hitable *world, int depth) {
    hit_record rec;
    if(world->hit(r, 0.001, FLT_MAX, rec)) {
        ray scattered;
        vec3 attenuation;
        if(depth<50 && rec.mat_ptr->scatter(r,rec,attenuation,scattered)) {
            return attenuation*color(scattered,world,depth+1);
        } else {
            return vec3(0,0,0);
        }
    }
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}


int main() {
    int nx=200;
    int ny=100;
    int ns=100; //number of random trials per pixel
    vector<unsigned char> image;
    image.resize(nx*ny*3);
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    hitable *list[4];
    list[0] = new sphere(vec3(0,0,-1), 0.5, new lambertian(vec3(0.8,0.3,0.3)));
    list[1] = new sphere(vec3(0,-100.5,-1), 100, new lambertian(vec3(0.8,0.8,0.0)));
    list[2] = new sphere(vec3(1,0,-1), 0.5, new metal(vec3(0.8, 0.6, 0.2),0.3));
    list[3] = new sphere(vec3(-1,0,-1), 0.5, new metal(vec3(0.8, 0.8, 0.8),1.0));
    hitable *world = new hitable_list(list,4);
    camera cam;
    for(int j=ny-1;j>=0;j--) {
        for(int i=0;i<nx;i++) {
            vec3 col(0,0,0);
            for(int s=0;s<ns;s++) {
                float u = ((float)i+drand())/(float)nx;
                float v = ((float)j+drand())/(float)ny;
                ray r = cam.get_ray(u,v);
                vec3 p =r.point_at_parameter(2.0);
                col += color(r,world,0);
            }
            col /= (float)ns;
            col = vec3(sqrt(col[0]),sqrt(col[1]),sqrt(col[2]));
            int ir = (int)(255.99*col[0]);
            int ig = (int)(255.99*col[1]);
            int ib = (int)(255.99*col[2]);
            image[3*nx*(ny-1-j)+3*i+0] = (char)ir;
            image[3*nx*(ny-1-j)+3*i+1] = (char)ig;
            image[3*nx*(ny-1-j)+3*i+2] = (char)ib;
            cout<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }
    encodeOneStep("Chapter8.png", image, nx, ny);
    return 0;
}

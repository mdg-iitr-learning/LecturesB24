#include <iostream>
#include <bits/stdc++.h>
#include "ray.h"
#include "lodepng.h"
using namespace std;

void encodeOneStep(const char* filename, std::vector<unsigned char>& image, unsigned width, unsigned height) {
    LodePNGColorType colorType = LCT_RGB;
  //Encode the image
  unsigned error = lodepng::encode(filename, image, width, height,colorType);

  //if there's an error, display it
  if(error) std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
}

float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin()-center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0*dot(oc, r.direction());
    float c = dot(oc,oc)-radius*radius;
    float discriminant = b*b-4*a*c;
    if(discriminant<0.0){
        return (-1.0);
    }
    else {
        return (-b-sqrt(discriminant))/(2.0*a);
    }
}

vec3 color(const ray& r) {
    float t = hit_sphere(vec3(0,0,-1), 0.5, r);
    cout<<t<<endl;
    if(t>0.0) {
        vec3 N = unit_vector(r.point_at_parameter(t)-vec3(0,0,-1));
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5*(unit_direction.y()+1.0);
    return (1.0-t)*vec3(1.0,1.0,1.0) + t*vec3(0.5,0.7,1.0);
}

int main() {
    int nx=200;
    int ny=100;
    vector<unsigned char> image;
    image.resize(nx*ny*3);
    cout<<"P3\n"<<nx<<" "<<ny<<"\n255\n";
    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0 ,0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    for(int j=ny-1;j>=0;j--) {
        for(int i=0;i<nx;i++) {
            float u = (float)i/(float)nx;
            float v = (float)j/(float)ny;
            ray r(origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = (int)(255.99*col[0]);
            int ig = (int)(255.99*col[1]);
            int ib = (int)(255.99*col[2]);
            image[3*nx*(ny-1-j)+3*i+0] = (char)ir;
            image[3*nx*(ny-1-j)+3*i+1] = (char)ig;
            image[3*nx*(ny-1-j)+3*i+2] = (char)ib;
            cout<<ir<<" "<<ig<<" "<<ib<<"\n";
        }
    }
    encodeOneStep("Chapter5.png", image, nx, ny);
}


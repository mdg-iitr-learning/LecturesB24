#include <iostream>
#include "vec3.hpp"
#include "ray.hpp"
#include "material.hpp"
#include "sphere.hpp"
#include "hitable_list.hpp"
#include "camera.hpp"
#include <cfloat>

#define srand48() ((double)rand() / RAND_MAX)

vec3 color_ray(const ray &r, hitable *world, int depth)
{
  const vec3 white = vec3(2.0, 2.0, 2.0);  //correct values white = vec3(2.0, 2.0, 2.0)
  const vec3 blue = vec3(1.5, 1.7, 2.0);   //blue = vec3(1.5, 1.7, 2.0)

  hit_record record;
  if (world->hit(r, 0.000001, FLT_MAX, record))
  {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && record.mat != nullptr && record.mat->scatter(r, record, attenuation, scattered))
    {
      return attenuation * color_ray(scattered, world, depth + 1);
    }
    else
    {
      return vec3(0, 0, 0);
    }
  }
  else
  {
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * white + t * blue;
  }
}

int main()
{
  int nx = 400;
  int ny = 200;
  int ns = 32;
  std::cout << "P3\n"
            << nx << " " << ny << "\n255\n";

  hitable *list[4];
  list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
  list[1] = new sphere(vec3(0, -100.5f, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
  list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.1));
  list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(0.5));
  hitable *world = new hitable_list(list, 4);
  camera cam;

  for (int j = ny - 1; j >= 0; j--)
  {
    std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
    for (int i = 0; i < nx; i++)
    {
      vec3 color(0, 0, 0);
      for (int s = 0; s < ns; s++)
      {
        float u = float(i + srand48()) / float(nx);
        float v = float(j + srand48()) / float(ny);
        ray r = cam.get_ray(u, v);
        color += color_ray(r, world, 0);
      }
      color /= float(ns);
      color = vec3(sqrt(color.r()), sqrt(color.g()), sqrt(color.b()));
      int ir = int(255.99 * color.r());
      int ig = int(255.99 * color.g());
      int ib = int(255.99 * color.b());
      std::cout << ir << " " << ig << " " << ib << "\n";
    }
  }
  std::cerr << "\nDone.\n";
  return 0;
}
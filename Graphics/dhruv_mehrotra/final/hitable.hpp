#ifndef HITABLE_HPP
#define HITABLE_HPP

#include "ray.hpp"

class material;

class hit_record
{
public:
  float t;
  vec3 p;
  vec3 normal;
  material *mat = nullptr;
};

class hitable
{
public:
  virtual bool hit(const ray &r, float t_min, float t_max, hit_record &record) const = 0;
};

#endif

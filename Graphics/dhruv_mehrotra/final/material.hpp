#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <iostream>
#include "ray.hpp"
#include "hitable.hpp"

#define srand48() ((double)rand() / RAND_MAX)

class material
{
public:
  virtual bool scatter(const ray &r_in, const hit_record &record, vec3 &attenuation, ray &scattered) const = 0;
};

vec3 random_in_unit_sphere();
vec3 reflect(const vec3 &v, const vec3 &normal);

class lambertian : public material
{
public:
  // albedo is the fraction of light reflected from the material a.k.a reflectance
  vec3 albedo;

  lambertian(const vec3 &a) : albedo(a) {}
  virtual bool scatter(const ray &r_in, const hit_record &record, vec3 &attenuation, ray &scattered) const
  {
    vec3 target = record.p + record.normal + random_in_unit_sphere();
    scattered = ray(record.p, target - record.p);
    attenuation = albedo;
    return true;
  }
};

class metal : public material
{
public:
  vec3 albedo;
  float fuzz;

  metal(const vec3 &a, float f) : albedo(a)
  {
    if (f <= 1)
    {
      fuzz = f;
    }
    else
    {
      fuzz = 1;
      std::cout << "\n"
                << std::endl;
    }
  }
  virtual bool scatter(const ray &r_in, const hit_record &record, vec3 &attenuation, ray &scattered) const
  {
    vec3 reflected = reflect(unit_vector(r_in.direction()), record.normal);
    scattered = ray(record.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.direction(), record.normal) > 0);
  }

private:
};
class dielectric : public material {
	public:
		dielectric(float ri): ref_idx(ri) {}
		virtual bool scatter(const ray& r_in , const hit_record& rec , vec3& attenuation , ray& scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction() , rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0 , 1.0 ,1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;
		if(dot(r_in.direction() , rec.normal) > 0) {
			outward_normal = (-1.0)*rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction() , rec.normal) / r_in.direction().length();
		}
		else{
			outward_normal = rec.normal;
			ni_over_nt = 1.0/ref_idx;
			cosine = (-1.0)*dot(r_in.direction() , rec.normal) / r_in.direction().length();
		}

		if(refract(r_in.direction() , outward_normal , ni_over_nt , refracted)) {
			reflect_prob = schlick(cosine , ref_idx);
		}
		else{
			scattered = ray(rec.p , reflected);
			reflect_prob = 1.0;
		}

		if ( (float(rand() % 1000) / float(1000)) < reflect_prob) {
			scattered = ray(rec.p , reflected);
		}
		else{
			scattered = ray(rec.p , refracted);
		}

		return true;
		}

		float ref_idx;
};

vec3 reflect(const vec3 &v, const vec3 &normal)
{
  return v - 2 * dot(v, normal) * normal;
}

vec3 random_in_unit_sphere()
{
  vec3 p;
  do
  {
    p = vec3(srand48(), srand48(), srand48());
  } while (p.squared_length() >= 1.0);
  return p;
}
#endif
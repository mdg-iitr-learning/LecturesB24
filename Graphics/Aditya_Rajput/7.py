import numpy as np
import random

#generic
v = np.array
l = lambda x : np.linalg.norm(x)
u = lambda v : v/l(v)
M = 10**100



#classes
class Ray:
    def __init__(self, o, d):
        self.origin = o
        self.direction = d

    def __getitem__(self, t):
        return self.origin + t*self.direction

class Camera:
    def __init__(self):
        self.llc = v([-2.0, -1, -1])
        self.hori = v([4.0, 0, 0])
        self.vert = v([0, 2.0, 0])
        self.orig = v([0.0, 0, 0])

    def get_ray(self, u, v):
        return Ray(self.orig, self.llc + u*self.hori + v*self.vert)



#hitable objects
class Hitable:
    def hit(self, ray, t_min, t_max, reco):
        pass

class Sphere(Hitable):
    def __init__(self, c, r):
        self.center = c
        self.radius = r

    def hit(self, ray, t_min, t_max, reco):
        AO = ray.origin - self.center
        a = l(ray.direction)**2
        b = 2*AO.dot(ray.direction)
        c = l(AO)**2 - self.radius**2
        if b**2 <= 4*a*c:
            return (False,reco)
        soln = (-b -pow(b**2 - 4*a*c, 0.5))/(2*a)
        if t_min < soln < t_max:
            reco.t = soln
            reco.p = ray[soln]
            reco.norm = u(reco.p - self.center)
            return (True,reco)
        soln = (-b +pow(b**2 - 4*a*c, 0.5))/(2*a)
        if t_min < soln < t_max:
            reco.t = soln
            reco.p = ray[soln]
            reco.norm = u(reco.p - self.center)
            return (True,reco)
        return (False,reco)

class HitableList(Hitable):
    def __init__(self, l):
        self.list = l

    def hit(self, ray, t_min, t_max, reco):
        hit_anything = False
        closest_yet = t_max
        temp = HitRecorder(0, v([0.0, 0, 0]), v([0.0, 0, 0]))
        
        for obj in self.list:
            h,temp = obj.hit(ray, t_min, closest_yet, temp)
            if h:
                hit_anything = True
                closest_yet = temp.t
                reco = temp
        if hit_anything:
            return True,reco
        return False,None

#bundle to record hit event
class HitRecorder:
    def __init__(self, t, p, norm):
        self.t = t
        self.p = p
        self.norm = norm







def color(ray, world):
    reco = HitRecorder(0, v([0.0, 0, 0]), v([0.0, 0, 0]))
    h,reco =  world.hit(ray, 0.00001, M, reco)
    if h:
        targ = reco.p + reco.norm + rando()
        return color(Ray(reco.p, targ - reco.p), world)/2
    t = (u(ray.direction)[1]+1)/2
    return (1-t)*v([1.0, 1, 1]) + t*v([0.5, 0.7, 1])

def rando():
    p = v([2.0, 0, 0])
    while l(p)**2 >= 1:
        p = np.random.random(3)
    return p

#main program
nx = 200
ny = 100
ns = 100

with open('7.ppm', 'w') as f:
    print('P3\n{0} {1}\n255\n'.format(nx, ny), file = f)
    camera = Camera()
    world = HitableList([
        Sphere(v([0.0, 0, -1]), 0.5),
        Sphere(v([0, -100.5, -1]), 100),
        ])
    
    for j in range(ny - 1, -1, -1):
        for i in range(nx):
            col = v([0.0, 0, 0])
            for k in range(ns):
                ray = camera.get_ray((i+random.random())/nx, (j+random.random())/ny)
                col += color(ray, world)
            col = ((col/ns)**0.5)*255.99
            print('{0} {1} {2}'.format(col[0], col[1], col[2]), file = f)
        print(j)

print('END')

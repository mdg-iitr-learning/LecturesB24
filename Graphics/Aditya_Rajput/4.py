import numpy as np

v = np.array
l = lambda x : np.linalg.norm(x)

class Ray:    
    def __init__(self, o, d):
        self.origin = o
        self.direction = d

    def __getitem__(self, t):
        return self.origin + t*self.direction

def color(ray):
    if hit_sphere(v([0.0, 0, -1]), 0.5, ray):
        return v([1.0, 0, 0])
    u = ray.direction/np.linalg.norm(ray.direction)
    t = (u[1]+1)/2
    return (1-t)*v([1.0, 1, 1]) + t*v([0.5, 0.7, 1])

def hit_sphere(center, radius, ray):
    AO = ray.origin - center
    a = l(ray.direction)**2
    b = 2*AO.dot(ray.direction)
    c = l(AO)**2 - radius**2
    return b**2 > 4*a*c



nx = 200
ny = 100

with open('4.ppm', 'w') as f:
    print('P3\n{0} {1}\n255\n'.format(nx, ny), file = f)
    
    llc = v([-2.0, -1, -1])
    hori = v([4.0, 0, 0])
    vert = v([0, 2.0, 0])
    orig = v([0.0, 0, 0])
    
    for j in range(ny - 1, -1, -1):
        for i in range(0, nx, 1):
            ray = Ray(orig, llc + (i/nx)*hori + (j/ny)*vert)
            col = color(ray) * 255.99
            print('{0} {1} {2}'.format(col[0], col[1], col[2]), file = f)

print('END')

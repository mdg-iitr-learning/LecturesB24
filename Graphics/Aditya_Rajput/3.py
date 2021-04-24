import numpy as np

class Ray:    
    def __init__(self, o, d):
        self.origin = o
        self.direction = d

    def __getitem__(self, t):
        return self.origin + t * self.direction

def color(r):
    u = r.direction / np.linalg.norm(r.direction)
    t = (u[1] + 1) / 2
    return (1 - t) * np.array([1.0, 1, 1]) + t * np.array([0.5, 0.7, 1])

nx = 200
ny = 100
with open('3.ppm', 'w') as f:
    print('P3\n{0} {1}\n255\n'.format(nx, ny), file = f)
    
    llc = np.array([-2.0, -1, -1])
    hori = np.array([4.0, 0, 0])
    vert = np.array([0, 2.0, 0])
    orig = np.array([0.0, 0, 0])
    
    for j in range(ny - 1, -1, -1):
        for i in range(0, nx, 1):
            ray = Ray(orig, llc + (i / nx) * hori + (j / ny) * vert)
            col = color(ray) * 255.99
            print('{0} {1} {2}'.format(col[0], col[1], col[2]), file = f)

print('END')

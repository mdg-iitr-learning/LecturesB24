import numpy as np

nx = 200
ny = 100
with open('2.ppm', 'w') as f:
    print('P3\n{0} {1}\n255\n'.format(nx, ny), file = f)
    for j in range(ny - 1, -1, -1):
        for i in range(0, nx, 1):
            c = np.array([i/nx, j/ny, 0.2])
            c *= 255.99
            print('{0} {1} {2}'.format(c[0], c[1], c[2]), file = f)

print('END')

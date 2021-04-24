nx = 200
ny = 100
with open('1.ppm', 'w') as f:
    print('P3\n{0} {1}\n255\n'.format(nx, ny), file = f)
    for j in range(ny-1, -1, -1):
        for i in range(0, nx, 1):
            print('{0} {1} {2}'.format(255.99 * i / nx, 255.99 * j / ny, 255.99 * 0.2), file = f)

print('END')

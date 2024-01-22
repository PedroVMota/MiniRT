import random
spheres = []

class Sphere:
    def __init__(self, x, y, z, r, g, b):
        self.x = x
        self.y = y
        self.z = z
        self.r = r
        self.g = g
        self.b = b
        


for i in range(100000):
    print(i)
    x = random.uniform(-10, 10)
    y = random.uniform(-10, 10)
    z = random.uniform(-10, 10)

    r = random.uniform(0, 255)
    g = random.uniform(0, 255)
    b = random.uniform(0, 255)

    spheres.append(Sphere(x, y, z, r, g, b))

with open('spheres.txt', 'w') as f:
    for sphere in spheres:
        f.write(f'sp {sphere.x},{sphere.y},{sphere.z} 1 {sphere.r},{sphere.g},{sphere.b}\n')

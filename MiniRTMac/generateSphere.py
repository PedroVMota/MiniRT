import random
spheres = []

class Sphere:
    def __init__(self, x, y, z, r, g, b, radius):
        self.x = x
        self.y = y
        self.z = z
        self.r = r
        self.g = g
        self.b = b
        self.rd = radius
    def renerate(self):
       string: str = f"sp {int(self.x)},{int(self.y)},{int(self.z)} {int(self.rd)} {int(self.r)},{int(self.g)},{int(self.b)}\n"
       return string



        


for i in range(25):
    x = random.uniform(-10, 10)
    y = random.uniform(-10, 10)
    z = random.uniform(-10, 10)
    r = random.uniform(0, 255)
    g = random.uniform(0, 255)
    b = random.uniform(0, 255)
    rad = random.uniform(0, 2)
    spheres.append(Sphere(x,y,z,r,g,b, rad))

with open('spheres.txt', 'w') as f:
    for sphere in spheres:
        f.write(sphere.renerate())

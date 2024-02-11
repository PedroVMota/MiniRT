import random

class Sphere:
    def __init__(self, radius):
        self.radius = radius
        self.coords = (0, 0, 0)
        self.color = (255, 255, 255)

    def set_coords(self, x, y, z):
        self.coords = (x, y, z)
    
    def set_color(self, r, g, b):
        self.color = (r, g, b)

list_of_spheres = []


for i in range(100):
    s = Sphere(1)
    s.set_coords(random.randint(-10, 10), random.randint(-10, 10), random.randint(-10, 10))
    s.set_color(random.randint(0, 255), random.randint(0, 255), random.randint(0, 255))

    list_of_spheres.append(s)

with open('spheres.txt', 'w') as f:
    for s in list_of_spheres:
        f.write(f'sp {s.coords[0]},{s.coords[1]},{s.coords[2]} {s.radius} {s.color[0]},{s.color[1]},{s.color[2]} 32 0\n')

    f.close()


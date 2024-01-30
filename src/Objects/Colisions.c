#include <center.h>

tValues sphereColision(Sphere *s, Ray rayData)
{
    tValues t;
    Vec3 oc = Sub(rayData.o, s->o);
    double a = Dot(rayData.d, rayData.d);
    double b = 2 * Dot(oc, rayData.d);
    double c = Dot(oc, oc) - (s->diameter);
    double discriminant = b * b - 4 * a * c;
    if(discriminant < 0)
    {
        t.t0 = INFINITY;
        t.t1 = INFINITY;
        return t;
    }
    t.t0 = (-b - sqrt(discriminant)) / (2 * a);
    t.t1 = (-b + sqrt(discriminant)) / (2 * a);
    return t;
}

tValues planeColision(Plane *plane, Ray ray)
{
    double numerator = 0;
    tValues t;

    numerator = 0;
    numerator = plane->d.x * (ray.o.x - plane->o.x);
    numerator += plane->d.y * (ray.o.y - plane->o.y);
    numerator += plane->d.z * (ray.o.z - plane->o.z);

    numerator *= -1;
    t.t0 = numerator / (plane->d.x * ray.d.x + plane->d.y * ray.d.y + plane->d.z * ray.d.z);
    t.t1 = 0;
    return t;
}

tValues cylinderColision(Cylinder *cylinder, Ray ray)
{
    tValues t;
    Vec3 oc = Sub(ray.o, cylinder->o);
    double a = Dot(ray.d, ray.d) - Dot(ray.d, cylinder->d) * Dot(ray.d, cylinder->d);
    double b = 2 * (Dot(ray.d, oc) - Dot(ray.d, cylinder->d) * Dot(oc, cylinder->d));
    double radius = cylinder->diameter / 2;
    double c = Dot(oc, oc) - Dot(oc, cylinder->d) * Dot(oc, cylinder->d) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    if(discriminant < 0)
    {
        t.t0 = INFINITY;
        t.t1 = INFINITY;
        return t;
    }
    t.t0 = (-b - sqrt(discriminant)) / (2 * a);
    t.t1 = (-b + sqrt(discriminant)) / (2 * a);
    Vec3 P1 = Add(ray.o, Mul(ray.d, t.t0));
    Vec3 P2 = Add(ray.o, Mul(ray.d, t.t1));

    double h1 = Dot(Sub(P1, cylinder->o), cylinder->d);
    double h2 = Dot(Sub(P2, cylinder->o), cylinder->d);
    //double d = Dot(Sub(P, cylinder->o), cylinder->d);
    if(h1 < 0 || h1 > cylinder->height)
        t.t0 = INFINITY;
    if (h2 < 0 || h2 > cylinder->height)
        t.t1 = INFINITY;
    return t;
}

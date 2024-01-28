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

tValues planeColision(Plane *plane, Ray *ray)
{
    double numerator = 0;
    tValues t;

    numerator = 0;
    numerator = plane->d.x * (ray->o.x - plane->o.x);
    numerator += plane->d.y * (ray->o.y - plane->o.y);
    numerator += plane->d.z * (ray->o.z - plane->o.z);

    numerator *= -1;
    t.t0 = numerator / (plane->d.x * ray->d.x + plane->d.y * ray->d.y + plane->d.z * ray->d.z);
    t.t1 = INFINITY;
    return t;
}

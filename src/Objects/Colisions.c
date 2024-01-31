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

static tValues planeColisionCylinder(Vec3 planePoint, Vec3 planeNormal, Ray ray) {
    tValues t;
    double denominador = Dot(ray.d, planeNormal);

    // Se o raio é paralelo ao plano, não há interseção
    if (fabs(denominador) < 0.001)
    {
        t.t0 = INFINITY;
        t.t1 = INFINITY;
        return t;
    }

    double numerator = Dot(Sub(planePoint, ray.o), planeNormal);
    t.t0 = numerator / denominador;
    t.t1 = INFINITY; // Um plano tem apenas um ponto de interseção
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
    }
    else
    {
        t.t0 = (-b - sqrt(discriminant)) / (2 * a);
        t.t1 = (-b + sqrt(discriminant)) / (2 * a);
    }
    Vec3 P1 = Add(ray.o, Mul(ray.d, t.t0));
    Vec3 P2 = Add(ray.o, Mul(ray.d, t.t1));

    double h1 = Dot(Sub(P1, cylinder->o), cylinder->d);
    double h2 = Dot(Sub(P2, cylinder->o), cylinder->d);

    if(h1 < 0 || h1 > cylinder->height)
        t.t0 = INFINITY;
    if (h2 < 0 || h2 > cylinder->height)
        t.t1 = INFINITY;
    Normalize(cylinder->d);
    Vec3 topCenter = Add(cylinder->o, Mul(cylinder->d, cylinder->height));
    tValues top = planeColisionCylinder(topCenter, cylinder->d, ray);
    tValues bot = planeColisionCylinder(cylinder->o, cylinder->d, ray);

    if (Length(Sub(ray.o, Add(ray.d, Mul(ray.d, top.t0)))) <= cylinder->diameter / 2)
        t.t0 = top.t0;
    if (Length(Sub(ray.o, Add(ray.d, Mul(ray.d, bot.t0)))) <= cylinder->diameter / 2)
        t.t1 = bot.t0;

    if(t.t0 == INFINITY && t.t1 == INFINITY)
    {
        return t;
    }
    else
    {
        tValues result;
        result.t0 = t.t0;
        result.t1 = t.t1;
        return result;
    }
}
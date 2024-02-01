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

tValues planeColisionCylinder(Vec3 planePoint, Vec3 planeNormal, Ray ray, double radius) 
{
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
    Vec3 intersectionPoint = Add(ray.o, Mul(ray.d, t.t0));

    // Verifique se o ponto de interseção está dentro do raio do disco
    double distance = Length(Sub(intersectionPoint, planePoint));
    if (distance > radius)
        t.t0 = INFINITY;
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

    Vec3 topCenter = Add(cylinder->o, Mul(cylinder->d, cylinder->height));
    Vec3 botCenter = cylinder->o;
    tValues top = planeColisionCylinder(topCenter, cylinder->d, ray, cylinder->diameter / 2);
    tValues bot = planeColisionCylinder(botCenter, cylinder->d, ray, cylinder->diameter / 2);

    Vec3 Ptop = Add(ray.o, Mul(ray.d, top.t0));
    Vec3 Pbot = Add(ray.o, Mul(ray.d, bot.t0));

    if (Length(Sub(Ptop, topCenter)) > radius)
        top.t0 = INFINITY;
    if (Length(Sub(Pbot, botCenter)) > radius)
        bot.t0 = INFINITY;

    if(t.t0 == INFINITY && t.t1 == INFINITY && top.t0 == INFINITY && bot.t0 == INFINITY)
    {
        return t;
    }
    else
    {
         tValues result;
        result.t0 = Min(t.t0, Min(top.t0, bot.t0));
        result.t1 = t.t1;
        // Calculate normals
        Vec3 normal0 = Sub(P1, cylinder->o);
        double dot0 = Dot(normal0, cylinder->d);
        result.normal0 = Normalize(Sub(normal0, Mul(cylinder->d, dot0)));

        Vec3 normal1 = Sub(P2, cylinder->o);
        double dot1 = Dot(normal1, cylinder->d);
        result.normal1 = Normalize(Sub(normal1, Mul(cylinder->d, dot1)));

        return result;
    }
}

#include <math.h>

double solve_plane(Vec3 o, Vec3 d, Vec3 p, Vec3 normal) {
    double denom = Dot(d, normal);
    if (fabs(denom) > 1e-6) {
        Vec3 p0l0 = Sub(p, o);
        double t = Dot(p0l0, normal) / denom;
        return t;
    }
    return INFINITY;
}

double vcos(Vec3 a, Vec3 b) {
    return Dot(a, b) / (Length(a) * Length(b));
}

int p_is_outside(Vec3 p1, Vec3 p2, Vec3 p3, Vec3 ip) {
    Vec3 v1 = Sub(p2, p1);
    Vec3 v2 = Sub(p3, p1);
    Vec3 vp = Sub(ip, p1);
    if (vcos(Cross(v1, v2), Cross(v1, vp)) < 0)
        return 1;
    return 0;
}

// Função para calcular a interseção de um raio com um triângulo
double rayTriangleIntersect(Vec3 rayOrigin, Vec3 rayDirection, Vec3 v0, Vec3 v1, Vec3 v2) {
    Vec3 edge1 = Sub(v1, v0);
    Vec3 edge2 = Sub(v2, v0);
    Vec3 h = Cross(rayDirection, edge2);
    double a = Dot(edge1, h);
    if (a > -0.00001 && a < 0.00001)
        return(INFINITY);
    double f = 1.0/a;
    Vec3 s = Sub(rayOrigin, v0);
    double u = f * Dot(s, h);
    if (u < 0.0 || u > 1.0)
        return(INFINITY);
    Vec3 q = Cross(s, edge1);
    double v = f * Dot(rayDirection, q);
    if (v < 0.0 || u + v > 1.0)
        return(INFINITY);
    // At this stage we can compute t to find out where the intersection point is on the line.
    double t = f * Dot(edge2, q);
    if (t > 0.00001) // ray intersection
        return t;
    else // This means that there is a line intersection but not a ray intersection.
        return INFINITY;
}

// Função para calcular a interseção de um raio com uma pirâmide
// Função para calcular a interseção de um raio com uma pirâmide
tValues pyramidCollision(Pyramid *pyramid, Ray ray) {
    tValues result;
    result.t0 = INFINITY;
    result.t1 = INFINITY;

    // Agora temos 5 faces na pirâmide, incluindo a base.
    // Agora temos 4 faces na pirâmide, excluindo a base.
for (int i = 1; i <= 4; i++) {
    // Cada face da pirâmide é um triângulo formado por três vértices.
    Vec3 v0 = pyramid->vertices[0]; // Top vertex is common for all faces
    Vec3 v1 = pyramid->vertices[i];
    Vec3 v2 = pyramid->vertices[i % 4 + 1]; // Changed from (i + 2) % 5 to i % 4 + 1

    // Calcula a interseção do raio com o triângulo.
    double t = rayTriangleIntersect(ray.o, ray.d, v0, v1, v2);

    // Se o raio intersecta o triângulo e a interseção está mais próxima do que a interseção atual,
    // atualiza a interseção e a normal.
    if (t < result.t0) {
        result.t0 = t;
        result.normal0 = pyramid->normals[i-1];
        }
    }

    // Check intersection with the base of the pyramid
    Vec3 v0 = pyramid->vertices[1];
    Vec3 v1 = pyramid->vertices[2];
    Vec3 v2 = pyramid->vertices[3];
    Vec3 v3 = pyramid->vertices[4];
    double t1 = rayTriangleIntersect(ray.o, ray.d, v0, v1, v3); // Changed v2 to v3
    double t2 = rayTriangleIntersect(ray.o, ray.d, v1, v2, v3); // Changed v0 to v1
    double t = (t1 < t2) ? t1 : t2;
    if (t < result.t0) {
        result.t0 = t;
        result.normal0 = pyramid->normals[4];
    }

    return result;
}
#include <center.h>

static tValues	quadraticSolver(double a, double b, double c)
{
	tValues		t;
	double		discriminant;

	discriminant = b * b - 4 * a * c;
	if(discriminant > 0)
		return (tValues){( \
			-b - sqrt(discriminant)) / \
			(2 * a), (-b + sqrt(discriminant)) / \
			(2 * a)};
	return (tValues){INFINITY, INFINITY};
}

tValues	sphereColision(Sphere *s, Ray rayData)
{
	tValues		t;
	Vec3		oc;

	oc = Sub(rayData.o, s->o);
	t = quadraticSolver(Dot(rayData.d, rayData.d), 2 * Dot(oc, rayData.d), Dot(oc, oc) - (s->diameter));
	return (t);
}

tValues	planeColision(Plane *plane, Ray ray)
{
	double	numerator;
	tValues	t;

	numerator = 0;
	numerator = plane->d.x * (ray.o.x - plane->o.x);
	numerator += plane->d.y * (ray.o.y - plane->o.y);
	numerator += plane->d.z * (ray.o.z - plane->o.z);

	numerator *= -1;
	t.t0 = numerator / (plane->d.x * \
		ray.d.x + plane->d.y * \
		ray.d.y + plane->d.z * \
		ray.d.z);
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

tValues calculateTValues(Vec3 oc, Ray ray, Cylinder *cylinder) 
{
    tValues t;
    double radius = cylinder->diameter / 2;

	return (quadraticSolver(Dot(ray.d, ray.d) - Dot(ray.d, cylinder->d)\
		* Dot(ray.d, cylinder->d)
		, 2 * (Dot(ray.d, oc) - Dot(ray.d, cylinder->d) * \
		Dot(oc, cylinder->d))
		, Dot(oc, oc) - Dot(oc, cylinder->d) * Dot(oc, cylinder->d) \
		- radius * radius));

}

void checkHeight(tValues *t, Vec3 P1, Vec3 P2, Cylinder *cylinder) 
{
    double h1 = Dot(Sub(P1, cylinder->o), cylinder->d);
    double h2 = Dot(Sub(P2, cylinder->o), cylinder->d);
    if(h1 < 0 || h1 > cylinder->height)
        t->t0 = INFINITY;
    if (h2 < 0 || h2 > cylinder->height)
        t->t1 = INFINITY;
}

tValues calculateTopPlaneColision(Ray ray, Cylinder *cylinder) 
{
    Vec3 topCenter = Add(cylinder->o, Mul(cylinder->d, cylinder->height));
    return planeColisionCylinder(topCenter, cylinder->d, ray, cylinder->diameter / 2);
}

tValues calculateBotPlaneColision(Ray ray, Cylinder *cylinder)
{
    Vec3 botCenter = cylinder->o;
    return planeColisionCylinder(botCenter, cylinder->d, ray, cylinder->diameter / 2);
}

tValues calculatePlaneColisions(Ray ray, Cylinder *cylinder) 
{
    tValues top = calculateTopPlaneColision(ray, cylinder);
    tValues bot = calculateBotPlaneColision(ray, cylinder);
    tValues result;
    result.t0 = minval(top.t0, bot.t0);
    result.t1 = INFINITY;
    return result;
}

Vec3 calculateNormal0(tValues t, Vec3 P1, Cylinder *cylinder) 
{
    Vec3 normal0 = Sub(P1, cylinder->o);
    double dot0 = Dot(normal0, cylinder->d);
    return Normalize(Sub(normal0, Mul(cylinder->d, dot0)));
}

Vec3 calculateNormal1(tValues t, Vec3 P2, Cylinder *cylinder) 
{
    Vec3 normal1 = Sub(P2, cylinder->o);
    double dot1 = Dot(normal1, cylinder->d);
    return Normalize(Sub(normal1, Mul(cylinder->d, dot1)));
}

tValues calculateNormals(tValues t, Vec3 P1, Vec3 P2, Cylinder *cylinder) 
{
    tValues result;
    result.t0 = t.t0;
    result.t1 = t.t1;
    result.normal0 = calculateNormal0(t, P1, cylinder);
    result.normal1 = calculateNormal1(t, P2, cylinder);
    return result;
}

tValues cylinderColision(Cylinder *cylinder, Ray ray) {
    Vec3 oc = Sub(ray.o, cylinder->o);
    tValues t = calculateTValues(oc, ray, cylinder);
    Vec3 P1 = Add(ray.o, Mul(ray.d, t.t0));
    Vec3 P2 = Add(ray.o, Mul(ray.d, t.t1));
    checkHeight(&t, P1, P2, cylinder);
    tValues planeColisions = calculatePlaneColisions(ray, cylinder);
    t.t0 = minval(t.t0, planeColisions.t0);
    return calculateNormals(t, P1, P2, cylinder);
}

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
	if (t > 0.001) // ray intersection
		return t;
	else // This means that there is a line intersection but not a ray intersection.
		return INFINITY;
}

// Função para calcular a interseção de um raio com uma pirâmide
// Função para calcular a interseção de um raio com uma pirâmide
tValues pyramidCollision(Pyramid *pyramid, Ray ray)
{
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